/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Boot video driver
 * Author:      Chloe M.
 */

#include <drivers/bootvid/fbio.h>
#include <ke/bpal.h>
#include <ex/pbi.h>
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
static BOOTCONS_ATTR DefaultConsAttr = {
    .Foreground = DEFAULT_FG,
    .Background = DEFAULT_BG
};

/*
 * Splash screen header
 *
 * @Width: Width of splash
 * @Height: Height of splash
 */
typedef PACKED struct {
    ULONG Width;
    ULONG Height;
} SPLASH_HEADER;

/*
 * Pack RGB bits so it fits the framebuffer format
 *
 * @Red: Red value
 * @Green: Green value
 * @Blue: Blue value
 */
static inline ULONG
BootVidPackRgb(UCHAR Red, UCHAR Green, UCHAR Blue)
{
    return ((ULONG)Red << Framebuffer.RedMaskShift)
         | ((ULONG)Green << Framebuffer.GreenMaskShift)
         | ((ULONG)Blue << Framebuffer.BlueMaskShift);
}

/*
 * Blit the splash onto the screen
 *
 * @Fb: Framebuffer descriptor
 * @Hdr: Splash header
 * @FileSize: Splash file size
 */
static BOOL
BlitSplash(KE_BPAL_FRAMEBUFFER *Fb, SPLASH_HEADER *Hdr, USIZE FileSize)
{
    volatile ULONG *Row;
    UCHAR *Pixels, *Base;
    USIZE StartX, StartY;
    USIZE SrcX, SrcY;
    USIZE DrawW, DrawH;
    USIZE PixelBytes;
    ULONG Background;
    USIZE ImgX, ImgY;
    USIZE Off, Red;
    UCHAR Green, Blue;
    UCHAR Alpha;

    if (Hdr->Width == 0 || Hdr->Height == 0) {
        return false;
    }

    PixelBytes = (USIZE)Hdr->Width * (USIZE)Hdr->Height * 4;
    if (FileSize < sizeof(SPLASH_HEADER) + PixelBytes) {
        return false;
    }

    if (Fb->Address == NULL || Fb->Pitch == 0) {
        return false;
    }

    Pixels = (UCHAR *)Hdr + sizeof(SPLASH_HEADER);
    Base = Fb->Address;

    DrawW = Hdr->Width;
    DrawH = Hdr->Height;
    StartX = 0;
    StartY = 0;
    SrcX = 0;
    SrcY = 0;

    if (DrawW < Fb->Width) {
        StartX = (Fb->Width - DrawW) / 2;
    } else if (DrawW > Fb->Width) {
        SrcX = (DrawW - Fb->Width) / 2;
        DrawW = Fb->Width;
    }

    if (DrawH < Fb->Height) {
        StartY = (Fb->Height - DrawH) / 2;
    } else if (DrawH > Fb->Height) {
        SrcY = (DrawH - Fb->Height) / 2;
        DrawH = Fb->Height;
    }

    /* Actually blit the splash */
    for (USIZE Y = 0; Y < DrawH; Y++) {
        Row = (volatile ULONG *)(Base + ((StartY + Y) * Fb->Pitch));
        for (USIZE X = 0; X < DrawW; X++) {
            ImgX = SrcX + X;
            ImgY = SrcY + Y;
            Off = (ImgY * Hdr->Width + ImgX) * 4;
            Red = Pixels[Off + 0];
            Green = Pixels[Off + 1];
            Blue = Pixels[Off + 2];
            Alpha = Pixels[Off + 3];
            Row[StartX + X] = BootVidPackRgb(Red, Green, Blue);
        }
    }

    return true;
}

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
BootVidInitCons(BOOTCONS_ATTR *Attr)
{
    if (BootConsEnabled) {
        BootVidDeInitCons();
    }

    if (Attr == NULL) {
        Attr = &DefaultConsAttr;
    }

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
        &Attr->Background,
        &Attr->Foreground,
        NULL,
        NULL,
        NULL,
        0, 0, 0,
        0, 0, 0, 0
    );

    BootConsEnabled = true;
}

VOID
BootVidDeInitCons(VOID)
{
    if (!BootConsEnabled) {
        return;
    }

    flanterm_deinit(FtCtx, NULL);
    FtCtx = NULL;
    BootConsEnabled = false;
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
    ST_STATUS Status;
    EX_BPI_FILE File;
    SPLASH_HEADER *Hdr;

    Status = ExPbiLookup("/boot/splash.rgba", &File);
    if (Status != STATUS_SUCCESS) {
        BootVidClear(BOOT_BG_RGB);
        return;
    }

    Hdr = File.Data;
    if (!BlitSplash(&Framebuffer, Hdr, File.Size)) {
        BootVidClear(BOOT_BG_RGB);
    }
}

BOOL
BootVidConsEn(VOID)
{
    return BootConsEnabled;
}
