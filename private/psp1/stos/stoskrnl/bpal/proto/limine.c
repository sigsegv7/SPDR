/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Boot Protocol Abstraction Layer
 * Author:      Chloe M.
 */

#include <ke/bpal.h>
#include <lib/limine.h>

#define FRAMEBUFFER FbResp->framebuffers[0]

/* HHDM request */
static struct limine_hhdm_response *HHDMResp = NULL;
static volatile struct limine_hhdm_request HHDMReq = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

/* Framebuffer request */
static struct limine_framebuffer_response *FbResp = NULL;
static struct limine_framebuffer_request FbReq = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

/* Command line request */
static struct limine_executable_cmdline_response *CmdLineResp = NULL;
static struct limine_executable_cmdline_request CmdLineReq = {
    .id = LIMINE_EXECUTABLE_CMDLINE_REQUEST,
    .revision = 0
};

VOID
BpalInitFramebuffer(KE_BPAL_HANDLE *Handle)
{
    KE_BPAL_FRAMEBUFFER *Framebuffer;

    if (Handle == NULL) {
        return;
    }

    Framebuffer = &Handle->Framebuffer;
    Framebuffer->Address = FRAMEBUFFER->address;
    Framebuffer->Width = FRAMEBUFFER->width;
    Framebuffer->Height = FRAMEBUFFER->height;
    Framebuffer->Pitch = FRAMEBUFFER->pitch;
    Framebuffer->RedMaskSize = FRAMEBUFFER->red_mask_size;
    Framebuffer->RedMaskShift = FRAMEBUFFER->red_mask_shift;
    Framebuffer->GreenMaskSize = FRAMEBUFFER->green_mask_size;
    Framebuffer->GreenMaskShift = FRAMEBUFFER->green_mask_shift;
    Framebuffer->BlueMaskSize = FRAMEBUFFER->blue_mask_size;
    Framebuffer->BlueMaskShift = FRAMEBUFFER->blue_mask_shift;
}

ST_STATUS
KeBpalLimineInit(KE_BPAL_HANDLE *Handle)
{
    if (Handle == NULL) {
        return STATUS_INVALID_PARAM;
    }

    HHDMResp = HHDMReq.response;
    FbResp = FbReq.response;
    CmdLineResp = CmdLineReq.response;

    BpalInitFramebuffer(Handle);
    Handle->StLoadBase = HHDMResp->offset;
    Handle->CommandLine = CmdLineResp->cmdline;
    return STATUS_SUCCESS;
}
