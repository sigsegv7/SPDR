/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: ACPI init
 * Author:      Chloe M.
 */

#include <drivers/acpi/acpi.h>
#include <drivers/acpi/tables.h>
#include <ex/trace.h>
#include <ke/bpal.h>
#include <ke/knot.h>

#define DTRACE(Fmt, ...) \
    TRACE("[ ACPI ]: " Fmt, ##__VA_ARGS__)

static ACPI_RSDP *Rsdp;

static VOID
AcpiPrintVendor(VOID)
{
    UCHAR Revision;

    /*
     * On certain emulators this may become zero, just bump it up to
     * one because its behaviors are the same.
     */
    Revision = Rsdp->Revision;
    if (Revision == 0) {
        ++Revision;
    }

    DTRACE("detected acpi %d.0 by %.6s\n", Revision, Rsdp->Oemid);
}

static VOID
RsdpVerify(VOID)
{
    UCHAR Checksum = 0;
    USIZE Idx;

    for (Idx = 0; Idx < Rsdp->Length; ++Idx) {
        Checksum += ((UCHAR *)Rsdp)[Idx];
    }

    if ((Checksum & 0xFF) != 0) {
        KeKnot("Got bad checksum %x for ACPI RSDP\n", Checksum);
    }

    DTRACE("checksum ok\n");
}

VOID
AcpiInit(VOID)
{
    KE_BPAL_HANDLE BpalHandle;
    ST_STATUS Status;

    Status = KeBpalGet(&BpalHandle);
    if (Status != STATUS_SUCCESS) {
        KeKnot("Unable to fetch BPAL handle for ACPI\n");
    }

    Rsdp = BpalHandle.RsdpBase;
    AcpiPrintVendor();
    RsdpVerify();
}
