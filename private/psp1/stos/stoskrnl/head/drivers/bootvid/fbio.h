/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Boot video driver
 * Author:      Chloe M.
 */

#ifndef _BOOTVID_FBIO_H_
#define _BOOTVID_FBIO_H_ 1

#include <stapi/status.h>
#include <stdef.h>

/*
 * Initialize the boot video driver
 */
ST_STATUS BootVidInit(VOID);

/*
 * Clear the screen with a solid color
 *
 * @Color: Color to clear screen with
 */
VOID BootVidClear(ULONG Color);

/*
 * Write a string to the boot console
 *
 * @String:  String to write
 * @Length:  Length of string
 */
VOID BootVidConsWrite(const CHAR *String, USIZE Length);

/*
 * Initialize the boot console
 */
VOID BootVidInitCons(VOID);

/*
 * Returns true if the boot console is enabled
 */
BOOL BootVidConsEn(VOID);

#endif  /* !_BOOTVID_FBIO_H_ */
