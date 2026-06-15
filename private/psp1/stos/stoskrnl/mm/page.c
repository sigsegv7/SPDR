/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Page management
 * Author:      Chloe M.
 */

#include <mm/page.h>
#include <mm/vad.h>

/* Globals */
extern MM_VAD_LIST gVadPool;
static MM_VAD *ScanLast = NULL;

VOID *
MmRequestPages(USIZE Count)
{
    MM_VAD *VadIter, *VadStart = NULL;
    USIZE FoundCount = 0;

    if (Count == 0) {
        return 0;
    }

    if (ScanLast == NULL) {
        ScanLast = gVadPool.First;
    }

    VadIter = ScanLast;
    while (VadIter != NULL && FoundCount < Count) {
        ++FoundCount;
        VadIter = VadIter->Next;
    }

    ScanLast->Next = VadIter;
    VadStart = ScanLast;
    ScanLast = ScanLast->Next;
    return VadStart;
}
