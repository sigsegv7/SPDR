/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: RtlStrLen() implementation
 * Author:      Chloe M.
 */

#include <string.h>

USIZE
RtlStrLen(const CHAR *String)
{
    USIZE Length = 0;

    if (String == NULL) {
        return 0;
    }

    while (String[Length++] != '\0')
        ;

    return Length;
}
