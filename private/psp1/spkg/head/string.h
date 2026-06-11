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

#endif  /* !_SPKG_STRING_H_ */
