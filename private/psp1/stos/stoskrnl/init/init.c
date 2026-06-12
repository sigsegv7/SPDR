/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Kernel initialization
 * Author:      Chloe M.
 */

#include <stdef.h>
#include <ke/bpal.h>
#include <ex/trace.h>
#include <ex/cmdline.h>
#include <ex/pbi.h>
#include <hal/kpcr.h>
#include <hal/mmio.h>
#include <hal/serial.h>
#include <drivers/bootvid/fbio.h>

/* Globals */
static KPCR BootstrapCore;

static VOID
Version(VOID)
{
    TRACE(":::: SPDR DR // Slut Technology ::::\n");
    TRACE("::::         v0.0.1             ::::\n");
}

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

    /* Parse the command line */
    ExCmdLineInit();

    /* Initialize the pre-boot image */
    ExPbiInit();

    /* Draw splash if bootcons is disabled */
    if (!BootVidConsEn()) {
        BootVidSplash();
    }

    /* Print version information */
    Version();
}
