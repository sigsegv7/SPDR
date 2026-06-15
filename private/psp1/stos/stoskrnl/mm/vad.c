/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Virtual address descriptor management
 * Author:      Chloe M.
 */

#include <mm/vad.h>
#include <mm/vmm.h>
#include <hal/mmu.h>
#include <stdef.h>

ST_STATUS
MmVadListInit(MM_VAD_LIST *VadList)
{
    if (VadList == NULL) {
        return STATUS_INVALID_PARAM;
    }

    VadList->First = NULL;
    VadList->Last = NULL;
    VadList->VadCount = 0;

    return STATUS_SUCCESS;
}

ST_STATUS
MmVadListAppend(MM_VAD_LIST *List, VOID *Page)
{
    MM_VAD *Vad, *Last;
    MM_VAD *VadIter;
    USIZE Idx = 0;

    if (List == NULL || Page == NULL) {
        return STATUS_INVALID_PARAM;
    }

    Vad = (MM_VAD *)Page;
    Vad->Next = NULL;
    Vad->Prev = NULL;

    if (List->First == NULL || List->Last == NULL) {
        List->First = Vad;
        List->Last = Vad;
    } else {
        Last = List->Last;
        Last->Next = Vad;
        Vad->Prev = Last;
        List->Last = Vad;
    }

    return STATUS_SUCCESS;
}
