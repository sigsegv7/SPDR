/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Virtual memory management
 * Author:      Chloe M.
 */

#include <mm/vmm.h>
#include <ex/trace.h>
#include <ke/knot.h>
#include <stdef.h>

#define DTRACE(Fmt, ...) \
    TRACE("[ VMM ]: " Fmt, ##__VA_ARGS__)

extern UPTR __KernelStart;
extern UPTR __KernelEnd;

void
MmVmmInit(VOID)
{
    UPTR Start, End;

    Start = (UPTR)__KernelStart;
    End = (UPTR)__KernelEnd;
    DTRACE("stoskrnl.sys occupies 0x%X bytes\n", End - Start);

    if (End >= VALLOC_BASE) {
        KeKnot("stoskrnl.sys overlaps VALLOC_BASE [0x%X]\n", VALLOC_BASE);
    }
}
