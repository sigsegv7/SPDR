/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Support package string RTL
 * Author:      Chloe M.
 */

#ifndef _SPKG_STRING_H_
#define _SPKG_STRING_H_ 1

#include <stdef.h>

/*
 * Obtain the length in bytes of a '\0' terminated string
 *
 * @String: String to obtain length from
 *
 * Returns zero on failure
 */
USIZE RtlStrLen(const CHAR *String);

/*
 * Fill n bytes of a buffer with a value
 *
 * @Buffer:     Pointer to buffer to fill
 * @SetValue:   Value to fill with
 * @Length:     Number of bytes to fill
 *
 * Returns @Buffer on success, otherwise NULL on failure
 */
VOID *RtlMemSet(VOID *Buffer, LONG SetValue, USIZE Length);

/*
 * Compare the differences between two strings
 *
 * @Buffer1: First buffer to compare
 * @Buffer2: Second buffer to compare
 * @Length:  Number of bytes to compare
 *
 * Returns the differences
 */
LONG RtlMemCmp(VOID *Buffer1, VOID *Buffer2, USIZE Length);

#endif  /* !_SPKG_STRING_H_ */
