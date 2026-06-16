/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Kernel initialization
 * Author:      Chloe M.
 */

#include <stdef.h>
#include <ke/bpal.h>
#include <ke/knot.h>
#include <ex/trace.h>
#include <ex/cmdline.h>
#include <ex/pbi.h>
#include <ob/object.h>
#include <hal/kpcr.h>
#include <hal/serial.h>
#include <ps/ps.h>
#include <mm/pframe.h>
#include <mm/vmm.h>
#include <drivers/bootvid/fbio.h>

/* Globals */
static KPCR BootstrapCore;

static VOID
Version(VOID)
{
    TRACE(":::: SPDR DR // Slut Technology ::::\n");
    TRACE("::::         v0.0.1             ::::\n\n");
}

static void
CreateRootProc(VOID)
{
    EPROCESS *RootProc;
    ST_STATUS Status;

    Status = PsCreateProcess(
        "KernelRoot",
        0,
        &RootProc
    );

    if (Status != STATUS_SUCCESS) {
        KeKnot("Unable to create root process\n");
    }

    BootstrapCore.CurrentProc = RootProc;
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

    /* Initialize the pageframe manager */
    MmPFrameInit();

    /* Initialize the virtual memory manager */
    MmVmmInit();

    /* Phase 2 init of bootstrap core */
    HalKpcrP2Init(&BootstrapCore);

    /* Initialize the object manager */
    ObManagerInit();

    /* Create the root process */
    CreateRootProc();
}
