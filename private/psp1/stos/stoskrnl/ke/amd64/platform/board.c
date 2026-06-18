/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Platform board helpers
 * Author:      Chloe M.
 */

#include <hal/board.h>
#include <machine/hpet.h>
#include <stdef.h>

VOID
HalBoardInit(VOID)
{
    /* Initialize the platform HPET */
    MdHpetInit();
}
