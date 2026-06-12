/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Pre-boot image manager
 * Author:      Chloe M.
 */

#ifndef _EX_PBI_H_
#define _EX_PBI_H_ 1

#include <stapi/status.h>
#include <stdef.h>

/*
 * Represents an BPI file
 *
 * @Data: Actual raw data
 * @Size:   Byte count
 */
typedef struct {
    VOID *Data;
    USIZE Size;
} EX_BPI_FILE;

/*
 * Look up a file from the pre-boot image
 *
 * @Path: Path to file to lookup
 * @Result: Result is written here
 */
ST_STATUS ExPbiLookup(CHAR *Path, EX_BPI_FILE *Result);

/*
 * Initialize the pre-boot image manaer
 */
ST_STATUS ExPbiInit(VOID);

#endif  /* !_EX_PBI_H_ */
