/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: MMU management core
 * Author:      Chloe M.
 */

#include <hal/mmu.h>
#include <mm/vmm.h>
#include <mm/pframe.h>
#include <stdef.h>
#include <string.h>

/*
 * Page-Table Entry (PTE) flags
 *
 * See Intel SDM Vol 3A, Section 4.5, Table 4-19
 */
#define PTE_ADDR_MASK   0x000FFFFFFFFFF000
#define PTE_P           BIT(0)        /* Present */
#define PTE_RW          BIT(1)        /* Writable */
#define PTE_US          BIT(2)        /* User r/w allowed */
#define PTE_PWT         BIT(3)        /* Page-level write-through */
#define PTE_PCD         BIT(4)        /* Page-level cache disable */
#define PTE_ACC         BIT(5)        /* Accessed */
#define PTE_DIRTY       BIT(6)        /* Dirty (written-to page) */
#define PTE_PS          BIT(7)        /* Page size */
#define PTE_GLOBAL      BIT(8)        /* Global; sticky */
#define PTE_NX          BIT(63)       /* Execute-disable */

/* 57-bit linear addresses */
#define CR4_LA57 BIT(12)

/*
 * Valid page levels
 */
typedef enum {
    PAGE_LEVEL_PML1,
    PAGE_LEVEL_PML2,
    PAGE_LEVEL_PML3,
    PAGE_LEVEL_PML4,
    PAGE_LEVEL_PML5
} PAGE_LEVEL;

/*
 * Convert protection flags to PTE flags
 */
static inline UQUAD
MmuProtToPte(UCHAR Prot)
{
   switch (Prot) {
   case PAGE_READONLY:
        return PTE_P | PTE_NX;
   case PAGE_READWRITE:
        return PTE_P | PTE_RW | PTE_NX;
   case PAGE_EXECUTE_RW:
        return PTE_P | PTE_RW;
   case PAGE_EXECUTE_READONLY:
        return PTE_P;
   }

   return 0;
}

/*
 * Returns true if the given pagesize is valid
 *
 * @Ps: Pagesize to check
 */
static inline BOOL
MmuPageSizeValid(MMU_PAGESIZE Ps)
{
    switch (Ps) {
    case PAGESIZE_4K:
        return true;
    }

    return false;
}

/*
 * Obtain the toplevel index
 */
static inline PAGE_LEVEL
MmuTopLevel(VOID)
{
    UPTR Cr4;

    ASMV(
        "mov %%cr4, %0"
        : "=r" (Cr4)
        :
        : "memory"
    );

    return ISSET(Cr4, CR4_LA57)
        ? PAGE_LEVEL_PML5
        : PAGE_LEVEL_PML4;
}

/*
 * Obtain the page level index
 *
 * @Vma: Virtual memory address
 * @Level: Page level
 */
static inline UQUAD
MmuLevelIndex(UPTR Vma, PAGE_LEVEL Level)
{
    switch (Level) {
    case PAGE_LEVEL_PML1: return (Vma >> 12)  & 0x1FF;
    case PAGE_LEVEL_PML2: return (Vma >> 21) & 0x1FF;
    case PAGE_LEVEL_PML3: return (Vma >> 30) & 0x1FF;
    case PAGE_LEVEL_PML4: return (Vma >> 39) & 0x1FF;
    case PAGE_LEVEL_PML5: return (Vma >> 48) & 0x1FF;
    default: return 0;
    }
}

static inline VOID
MmuInvlpg(UPTR Vma)
{
    ASMV(
        "invlpg (%0)"
        :
        : "r" (Vma)
        : "memory"
    );
}

/*
 * Extract a specific pagemap level
 *
 * @Vas:        Virtual address space to extract from
 * @Vma:        Virtual memory address used as key
 * @Level:      Level to extract
 * @Allocate:   If true, allocate new levels if not present
 */
static UPTR *
MmuExtractLevel(MMU_VAS *Vas, UPTR Vma, PAGE_LEVEL Level, BOOL Allocate)
{
    UPTR Pma, *Pmap;
    VOID *TmpPtr;
    USIZE Index;
    PAGE_LEVEL CurrentLevel;

    if (Vas == NULL) {
        return NULL;
    }

    CurrentLevel = MmuTopLevel();
    Pmap = PMA_TO_VMA((Vas->TopLevel & PTE_ADDR_MASK));

    while (CurrentLevel > Level) {
        Index = MmuLevelIndex(Vma, CurrentLevel);

        if (ISSET(Pmap[Index], PTE_P)) {
            Pmap = PMA_TO_VMA((Pmap[Index] & PTE_ADDR_MASK));
            --CurrentLevel;
            continue;
        }

        if (!Allocate) {
            return NULL;
        }

        Pma = MmRequestFrame();
        if (Pma == 0) {
            return NULL;
        }

        TmpPtr = PMA_TO_VMA(Pma);
        RtlMemSet(TmpPtr, 0, 4096);
        Pmap[Index] = Pma | (PTE_P | PTE_RW | PTE_US);
        Pmap = TmpPtr;
        --CurrentLevel;
    }

    return Pmap;
}

VOID
HalReadVas(MMU_VAS *Result)
{
    if (Result == NULL) {
        return;
    }

    ASMV(
        "mov %%cr3, %0"
        : "=r" (Result->TopLevel)
        :
        : "memory"
    );
}

VOID
HalWriteVas(MMU_VAS *Vas)
{
    if (Vas == NULL) {
        return;
    }

    ASMV(
        "mov %0, %%cr3"
        :
        : "r" (Vas->TopLevel)
        : "memory"
    );
}

ST_STATUS
HalMapSinglePage(MMU_VAS *Vas, UPTR Vma, UPTR Pma, UCHAR Prot, MMU_PAGESIZE Ps)
{
    UPTR *Tbl;
    UQUAD PteFlags, Index;

    if (Vas == NULL) {
        return STATUS_INVALID_PARAM;
    }

    Tbl = MmuExtractLevel(Vas, Vma, PAGE_LEVEL_PML1, true);
    if (Tbl == NULL) {
        return STATUS_NO_MEMORY;
    }

    Index = MmuLevelIndex(Vma, PAGE_LEVEL_PML1);
    PteFlags = MmuProtToPte(Prot);
    Tbl[Index] = Pma | PteFlags;
    MmuInvlpg(Vma);
    return STATUS_SUCCESS;
}
