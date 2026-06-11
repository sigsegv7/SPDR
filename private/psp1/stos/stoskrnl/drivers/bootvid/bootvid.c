/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Boot video driver
 * Author:      Chloe M.
 */

#include <drivers/bootvid/fbio.h>
#include <ke/bpal.h>
#include <stdef.h>

/* Globals */
SECTION(".font") static CHAR FontData[4096];
static KE_BPAL_FRAMEBUFFER Framebuffer;

ST_STATUS
BootVidInit(VOID)
{
    ST_STATUS Status;
    KE_BPAL_HANDLE BpalHandle;

    Status = KeBpalGet(&BpalHandle);
    if (Status != STATUS_SUCCESS) {
        return Status;
    }

    Framebuffer = BpalHandle.Framebuffer;
    return STATUS_SUCCESS;
}

VOID
BootVidClear(ULONG Color)
{
    ULONG *Ptr;

    Ptr = Framebuffer.Address;
    for (USIZE Idx = 0; Idx < Framebuffer.Height * Framebuffer.Pitch; ++Idx) {
        Ptr[Idx] = Color;
    }
}
