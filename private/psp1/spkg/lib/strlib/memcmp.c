/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: RtlMemCmp() implementation
 * Author:      Chloe M.
 */

#include <string.h>

/*
 * Compare the differences between two strings
 *
 * @Buffer1: First buffer to compare
 * @Buffer2: Second buffer to compare
 * @Length:  Number of bytes to compare
 *
 * Returns the differences
 */
LONG
RtlMemCmp(const VOID *Buffer1, const VOID *Buffer2, USIZE Length)
{
    const UCHAR *Ptr1 = Buffer1;
    const UCHAR *Ptr2 = Buffer2;

    if (Buffer1 == NULL || Buffer2 == NULL) {
        return 0;
    }

    if (Length == 0) {
        return 0;
    }

    do {
        if (*Ptr1++ != *Ptr2++) {
            return (*--Ptr1 - *--Ptr2);
        }
    } while (--Length != 0);

    return 0;
}

