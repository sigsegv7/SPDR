/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Boot video driver
 * Author:      Chloe M.
 */

#include <drivers/bootvid/fbio.h>
#include <stdef.h>

/* Globals */
SECTION(".font") static CHAR FontData[4096];

ST_STATUS
BootInit(void)
{
    return STATUS_SUCCESS;
}
