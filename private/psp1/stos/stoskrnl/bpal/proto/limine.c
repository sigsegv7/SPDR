/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Boot Protocol Abstraction Layer
 * Author:      Chloe M.
 */

#include <ke/bpal.h>
#include <lib/limine.h>
#include <string.h>

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

/* Module request */
static struct limine_module_response *ModResp = NULL;
static volatile struct limine_module_request ModReq = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0
};

/* Memory map request */
static struct limine_memmap_response *MapResp = NULL;
static volatile struct limine_memmap_request MapReq = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

/* RSDP request */
static struct limine_rsdp_response *RsdpResp = NULL;
static volatile struct limine_rsdp_request RsdpReq = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};

static ST_STATUS
LimineModuleLookup(CHAR *Path, KE_BPAL_MODULE *Result)
{
    struct limine_file *Module;
    USIZE PathLen;

    if (Path == NULL || Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (ModResp == NULL) {
        return STATUS_NOT_FOUND;
    }

    PathLen = RtlStrLen(Path);
    for (USIZE Idx = 0; Idx < ModResp->module_count; ++Idx) {
        Module = ModResp->modules[Idx];
        if (*Module->path != *Path) {
            continue;
        }

        if (RtlMemCmp(Module->path, Path, PathLen) == 0) {
            Result->Data = Module->address;
            Result->Length = Module->size;
            return STATUS_SUCCESS;
        }
    }

    return STATUS_NOT_FOUND;
}

static ST_STATUS
LimineMemEntryIdx(USIZE Idx, KE_MEMMAP_ENTRY *Result)
{
    struct limine_memmap_entry *Entry;

    if (Idx >= MapResp->entry_count) {
        return STATUS_NOT_FOUND;
    }

    Entry = MapResp->entries[Idx];
    Result->Base = Entry->base;
    Result->Length = Entry->length;
    Result->Type = Entry->type;
    return STATUS_SUCCESS;
}

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
    ModResp = ModReq.response;
    MapResp = MapReq.response;
    RsdpResp = RsdpReq.response;

    BpalInitFramebuffer(Handle);
    Handle->StLoadBase = HHDMResp->offset;
    Handle->CommandLine = CmdLineResp->cmdline;
    Handle->ModuleLookup = LimineModuleLookup;
    Handle->MemEntryIdx = LimineMemEntryIdx;
    Handle->RsdpBase = RsdpResp->address;
    return STATUS_SUCCESS;
}
