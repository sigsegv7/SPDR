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
 * Boot console attributes
 *
 * @Background: Console background color
 * @Foreground: Console foreground color
 */
typedef struct {
    ULONG Background;
    ULONG Foreground;
} BOOTCONS_ATTR;

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
 * Render the boot splash
 */
VOID BootVidSplash(VOID);

/*
 * Initialize the boot console
 *
 * @Attr: Attributes to set [NULL for default]
 */
VOID BootVidInitCons(BOOTCONS_ATTR *Attr);

/*
 * Returns true if the boot console is enabled
 */
BOOL BootVidConsEn(VOID);

#endif  /* !_BOOTVID_FBIO_H_ */
