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
#include "flanterm.h"
#include "flanterm_backends/fb.h"

/* Bootcons attributes */
#define DEFAULT_BG 0x000000
#define DEFAULT_FG 0xAFE1AF

/* Boot background */
#define BOOT_BG_RGB 0xA9A9A9

static KE_BPAL_FRAMEBUFFER Framebuffer;
static struct flanterm_context *FtCtx = NULL;
static BOOL BootConsEnabled = false;

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
BootVidInitCons(VOID)
{
    ULONG Foreground, Background;

    if (BootConsEnabled) {
        return;
    }

    Foreground = DEFAULT_FG;
    Background = DEFAULT_BG;

    FtCtx = flanterm_fb_init(
        NULL,
        NULL,
        Framebuffer.Address,
        Framebuffer.Width,
        Framebuffer.Height,
        Framebuffer.Pitch,
        Framebuffer.RedMaskSize,
        Framebuffer.RedMaskShift,
        Framebuffer.GreenMaskSize,
        Framebuffer.GreenMaskShift,
        Framebuffer.BlueMaskSize,
        Framebuffer.BlueMaskShift,
        NULL,
        NULL,
        NULL,
        &Background,
        &Foreground,
        NULL,
        NULL,
        NULL,
        0, 0, 0,
        0, 0, 0, 0
    );

    BootConsEnabled = true;
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

VOID
BootVidConsWrite(const CHAR *String, USIZE Length)
{
    if (String == NULL || Length == 0) {
        return;
    }

    if (!BootConsEnabled) {
        return;
    }

    flanterm_write(FtCtx, String, Length);
}

VOID
BootVidSplash(VOID)
{
    BootVidClear(BOOT_BG_RGB);
}

BOOL
BootVidConsEn(VOID)
{
    return BootConsEnabled;
}
