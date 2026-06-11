/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Kernel initialization
 * Author:      Chloe M.
 */

#include <stdef.h>
#include <ke/bpal.h>
#include <hal/kpcr.h>
#include <hal/serial.h>
#include <drivers/bootvid/fbio.h>

/* Boot background */
#define BOOT_BG_RGB 0xA9A9A9

/* Globals */
static KPCR BootstrapCore;

VOID
KernelEntry(VOID)
{
    /* Initialize the BPAL layer */
    KeBpalInit();

    /* Phase 1 init of bootstrap core */
    HalKpcrP1Init(&BootstrapCore);

    /* Initialize the serial driver */
    HalSerialInit();

    /* Initialize bootvid */
    BootVidInit();

    /* Some visual indicator that the system is booting */
    BootVidClear(BOOT_BG_RGB);
}
