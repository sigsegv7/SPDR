/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Low-level processor initialization
 * Author:      Chloe M.
 */

#include <hal/kpcr.h>

/* Externs */
extern VOID MdCpuInit(VOID);

VOID
HalKpcrP1Init(KPCR *Kpcr)
{
    if (Kpcr == NULL) {
        return;
    }

    /*
     * We should default to an ID of zero here, this should
     * be overriden by the component initializing the processors.
     */
    Kpcr->CoreId = 0;

    /* Initialize machine specific bits */
    MdCpuInit();
}
