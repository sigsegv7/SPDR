/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Page frame manager
 * Author:      Chloe M.
 */

#include <mm/pframe.h>
#include <ex/trace.h>
#include <ke/bpal.h>
#include <stdef.h>

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
 * Scan physical memory for available regions
 */
static VOID
PFrameScan(VOID)
{
    ST_STATUS Status;
    KE_MEMMAP_ENTRY Entry;
    USIZE Idx;

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
    }
}

VOID
MmPFrameInit(VOID)
{
    DTRACE("sniffing out physical memory...\n");
    PFrameScan();
}
