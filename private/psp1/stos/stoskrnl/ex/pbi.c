/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Pre-boot image manager
 * Author:      Chloe M.
 */

#include <ex/pbi.h>
#include <ke/bpal.h>
#include <stdef.h>
#include <string.h>

#define REF_MAGIC "CUMHOLE"
#define REF_MAGIC_LEN 8
#define REF_PATH_LEN 256

static KE_BPAL_MODULE Pbi;

/*
 * A reference is an entry within the table that refers
 * to a block of data after the reference table.
 *
 * @Magic:      Reference magic
 * @Path:       File path
 * @Size:       File size
 * @DataOff:    Data offset
 */
typedef PACKED struct {
    CHAR Magic[REF_MAGIC_LEN];
    CHAR Path[REF_PATH_LEN];
    USIZE Size;
    USIZE DataOff;
} HOLE_REF;

ST_STATUS
ExPbiLookup(CHAR *Path, EX_BPI_FILE *Result)
{
    HOLE_REF *Ref;
    USIZE PathLen;

    if (Path == NULL || Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (*Path != '/') {
        return STATUS_NOT_FOUND;
    }

    ++Path;
    Ref = Pbi.Data;
    PathLen = RtlStrLen(Path);

    for (;;) {
        if (RtlMemCmp(Ref->Magic, REF_MAGIC, REF_MAGIC_LEN) != 0) {
            break;
        }

        if (Ref->Path[0] != *Path) {
            ++Ref;
            continue;
        }

        if (RtlMemCmp(Ref->Path, Path, PathLen) == 0) {
            Result->Data = PTR_OFFSET(Pbi.Data, Ref->DataOff);
            Result->Size = Ref->Size;
            return STATUS_SUCCESS;
        }

        ++Ref;
    }

    return STATUS_NOT_FOUND;
}

ST_STATUS
ExPbiInit(VOID)
{
    ST_STATUS Status;
    KE_BPAL_HANDLE Bpal;

    Status = KeBpalGet(&Bpal);
    if (Status != STATUS_SUCCESS) {
        return Status;
    }

    if (Bpal.ModuleLookup == NULL) {
        return STATUS_NOT_FOUND;
    }

    Status = Bpal.ModuleLookup("/boot/pbi.hole", &Pbi);
    if (Status != STATUS_SUCCESS) {
        return Status;
    }

    return STATUS_SUCCESS;
}
