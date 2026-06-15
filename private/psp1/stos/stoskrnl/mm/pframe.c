/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Page frame manager
 * Author:      Chloe M.
 */

#include <mm/pframe.h>
#include <mm/vmm.h>
#include <ex/trace.h>
#include <ke/bpal.h>
#include <ke/spinlock.h>
#include <stdef.h>
#include <units.h>

#define MEM_SCAN_START 0x00100000
#define PAGESIZE 4096

#define DTRACE(fmt, ...) \
    TRACE("[ PFRAME ]: " fmt, ##__VA_ARGS__)

/* Use to convert type constants to strings */
#define MEM_TYPE(TYPE)          \
    ((TYPE) < NELEM(TypeTab))   \
        ? TypeTab[(TYPE)]       \
        : "invalid"

/*
 * Memory type constant to human readable
 * string table.
 */
static const char *TypeTab[] = {
    [MEMORY_USABLE]         = "usable",
    [MEMORY_RESERVED]       = "reserved",
    [MEMORY_ACPI_RECLAIM]   = "acpi reclaimable",
    [MEMORY_ACPI_NVS]       = "acpi nvs",
    [MEMORY_BAD]            = "bad*",
    [MEMORY_BOOTLOADER]     = "bootloader",
    [MEMORY_KERNEL]         = "stoskrnl.sys",
    [MEMORY_FRAMEBUFFER]    = "framebuffer",
    [MEMORY_ACPI_TABLES]    = "acpi tables"
};

/*
 * Represents a frame free list entry
 *
 * @Next: Next entry in free list
 * @Prev: Previous entry in free list
 */
typedef struct _FREE_LIST_ENTRY {
    struct _FREE_LIST_ENTRY *Next;
    struct _FREE_LIST_ENTRY *Prev;
} FREE_LIST_ENTRY;

/*
 * Allocation freelist
 *
 * @First: First entry in free list
 * @Last:  Last entry in free list
 * @Lock:  Lock protecting this free list
 */
typedef struct {
    FREE_LIST_ENTRY *First;
    FREE_LIST_ENTRY *Last;
    KE_SPINLOCK Lock;
} FREE_LIST;

static FREE_LIST FreeList;
static USIZE MemoryFree = 0;

/*
 * Print memory units in a human readable format
 */
static inline VOID
PrintMemUnits(const CHAR *Title, USIZE Length)
{
    if (Title == NULL) {
        return;
    }

    if (Length >= UNIT_GIB) {
        DTRACE("%s: %d GiB\n", Title, Length / UNIT_GIB);
    } else if (Length >= UNIT_MIB) {
        DTRACE("%s: %d MiB\n", Title, Length / UNIT_MIB);
    } else {
        DTRACE("%s: %d bytes\n", Title, Length);
    }
}

/*
 * Append a memory entry to a free list
 *
 * @List: Free list to append to
 * @VmaBase: Virtual memory base to add
 */
static VOID
FreeListAppend(FREE_LIST *List, VOID *VmaBase)
{
    FREE_LIST_ENTRY *Entry, *Last;

    if (List == NULL || VmaBase == NULL) {
        return;
    }

    Entry = (FREE_LIST_ENTRY *)VmaBase;
    Entry->Next = NULL;
    Entry->Prev = NULL;

    if (List->First == NULL || List->Last == NULL) {
        List->First = Entry;
        List->Last = Entry;
    } else {
        Last = List->Last;
        Last->Next = Entry;
        List->Last = Entry;
        Entry->Prev = Last;
    }
}

/*
 * Pop an entry from an allocation free list
 *
 * @List: Free list to pop from
 */
static FREE_LIST_ENTRY *
FreeListPop(FREE_LIST *List)
{
    FREE_LIST_ENTRY *Entry;

    if (List == NULL) {
        return NULL;
    }

    if (List->Last == NULL) {
        return NULL;
    }

    Entry = List->Last;
    List->Last = Entry->Prev;
    Entry->Prev->Next = NULL;
    return Entry;
}

/*
 * Scan physical memory for available regions
 */
static VOID
PFrameScan(VOID)
{
    ST_STATUS Status;
    KE_MEMMAP_ENTRY Entry;
    USIZE Idx;
    VOID *Base, *Vma;

    for (Idx = 0;; ++Idx) {
        Status = KeBpalMemEntry(Idx, &Entry);
        if (Status != STATUS_SUCCESS) {
            break;
        }

        DTRACE(
            "%p ... %p : %s\n",
            Entry.Base,
            Entry.Base + Entry.Length,
            MEM_TYPE(Entry.Type)
        );

        /* Usable entries only from this point */
        if (Entry.Type != MEMORY_USABLE) {
            continue;
        }

        Base = PMA_TO_VMA(Entry.Base);
        for (USIZE Off = 0; Off < Entry.Length; Off += PAGESIZE) {
            Vma = PTR_OFFSET(Base, Off);
            FreeListAppend(&FreeList, Vma);
        }

        MemoryFree += Entry.Length;
    }

    PrintMemUnits("memory available", MemoryFree);
}

UPTR
MmRequestFrame(VOID)
{
    FREE_LIST_ENTRY *Entry;
    UPTR Base = 0;

    KeSpinLockAcq(&FreeList.Lock, true);
    Entry = FreeListPop(&FreeList);
    if (Entry == NULL) {
        goto out;
    }

    Base = VMA_TO_PMA(Entry);
out:
    KeSpinLockRel(&FreeList.Lock);
    return Base;
}

VOID
MmPFrameInit(VOID)
{
    DTRACE("sniffing out physical memory...\n");
    PFrameScan();
}
