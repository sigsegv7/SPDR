/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Printf bridge
 * Author:      Chloe M.
 */

#include <hal/serial.h>
#include <drivers/bootvid/fbio.h>

void
_putchar(char c)
{
    HalSerialWrite(&c, 1);
    if (BootVidConsEn()) {
        BootVidConsWrite(&c, 1);
    }
}
