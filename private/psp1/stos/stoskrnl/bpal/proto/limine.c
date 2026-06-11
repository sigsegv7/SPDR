/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Boot Protocol Abstraction Layer
 * Author:      Chloe M.
 */

#include <ke/bpal.h>
#include <lib/limine.h>

/* HHDM request */
static struct limine_hhdm_response *HHDMResp = NULL;
static volatile struct limine_hhdm_request HHDMReq = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

ST_STATUS
KeBpalLimineInit(KE_BPAL_HANDLE *Handle)
{
    if (Handle == NULL) {
        return STATUS_INVALID_PARAM;
    }

    HHDMResp = HHDMReq.response;
    Handle->StLoadBase = HHDMResp->offset;
    return STATUS_SUCCESS;
}
