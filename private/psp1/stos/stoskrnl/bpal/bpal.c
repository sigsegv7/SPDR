/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Boot Protocol Abstraction Layer
 * Author:      Chloe M.
 */

#include <ke/bpal.h>
#include <string.h>

/* Globals */
static KE_BPAL_HANDLE BpalHandle;

ST_STATUS
KeBpalGet(KE_BPAL_HANDLE *Result)
{
    if (Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    *Result = BpalHandle;
    return STATUS_SUCCESS;
}

ST_STATUS
KeBpalInit(VOID)
{
    CHAR *BootProtocol = BOOT_PROTOCOL;

    switch (*BootProtocol) {
    case 'l':
        if (RtlMemCmp(BootProtocol, "limine", 6) == 0) {
            return KeBpalLimineInit(&BpalHandle);
        }
    }

    return STATUS_NOT_FOUND;
}
