/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: RtlMemCpy() implementation
 * Author:      Chloe M.
 */

#include <string.h>

VOID *
RtlMemCpy(VOID *Dest, const VOID *Source, USIZE Length)
{
    if (Dest == NULL || Source == NULL) {
        return NULL;
    }

    for (USIZE Idx = 0; Idx < Length; ++Idx) {
        ((UCHAR *)Dest)[Idx] = ((UCHAR *)Source)[Idx];
    }

    return Dest;
}
