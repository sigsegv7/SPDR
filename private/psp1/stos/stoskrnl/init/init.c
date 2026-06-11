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

/* Globals */
static KPCR BootstrapCore;

NO_RETURN VOID
KernelEntry(VOID)
{
    /* Initialize the BPAL layer */
    KeBpalInit();

    /* Phase 1 init of bootstrap core */
    HalKpcrP1Init(&BootstrapCore);

    for (;;);
}
