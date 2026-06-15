/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Virtual memory management
 * Author:      Chloe M.
 */

#include <mm/vmm.h>
#include <mm/vad.h>
#include <mm/pframe.h>
#include <hal/mmu.h>
#include <ex/trace.h>
#include <ke/knot.h>
#include <stdef.h>

#define VADLIST_INIT_PAGES 1024

#define DTRACE(Fmt, ...) \
    TRACE("[ VMM ]: " Fmt, ##__VA_ARGS__)

MM_VAD_LIST gVadPool;
extern UPTR __KernelStart;
extern UPTR __KernelEnd;

void
MmVmmInit(VOID)
{
    UPTR Start, End;
    UPTR FrameTmp;
    VOID *VallocBase, *Cur;
    MMU_VAS Vas;

    Start = (UPTR)__KernelStart;
    End = (UPTR)__KernelEnd;
    DTRACE("stoskrnl.sys occupies 0x%X bytes\n", End - Start);

    if (End >= VALLOC_BASE) {
        KeKnot("stoskrnl.sys overlaps VALLOC_BASE [0x%X]\n", VALLOC_BASE);
    }

    VallocBase = (VOID *)VALLOC_BASE;
    MmVadListInit(&gVadPool);
    HalReadVas(&Vas);

    /* Initialize the VAD list */
    for (USIZE Idx = 0; Idx < VADLIST_INIT_PAGES; ++Idx) {
        Cur = PTR_OFFSET(VallocBase, Idx * PAGESIZE);
        FrameTmp = MmRequestFrame();

        if (FrameTmp == 0) {
            KeKnot("Not enough memory for VAD list");
        }

        HalMapSinglePage(
            &Vas,
            (UPTR)Cur,
            MmRequestFrame(),
            PAGE_READWRITE,
            PAGESIZE_4K
        );

        MmVadListAppend(&gVadPool, Cur);
    }

    DTRACE("vad list initial size : %d pages\n", VADLIST_INIT_PAGES);
}
