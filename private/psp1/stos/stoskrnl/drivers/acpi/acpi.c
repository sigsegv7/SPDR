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
#include <mm/vmm.h>
#include <ke/bpal.h>
#include <ke/knot.h>
#include <string.h>

#define DTRACE(Fmt, ...) \
    TRACE("[ ACPI ]: " Fmt, ##__VA_ARGS__)

static ACPI_RSDP *Rsdp;
static ACPI_ROOT_SDT *RootSdt;
static USIZE RootSdtEntries;

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

VOID *
AcpiQuery(const CHAR *Signature)
{
    BOOL IsMatch;
    ACPI_HEADER *Header;
    UPTR Pma;
    USIZE Idx;

    if (Signature == NULL) {
        return NULL;
    }

    for (Idx = 0; Idx < RootSdtEntries; ++Idx) {
        Pma = (UPTR)RootSdt->Tables[Idx];
        Header = (ACPI_HEADER *)PMA_TO_VMA(Pma);
        IsMatch = !RtlMemCmp(
            Header->Signature,
            Signature,
            sizeof(Header->Signature)
        );

        if (IsMatch) {
            return (VOID *)Header;
        }
    }

    return NULL;
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

    /* Select the correct root sdt */
    if (Rsdp->Revision < 2) {
        DTRACE("using rsdt as root sdt\n");
        RootSdt = PMA_TO_VMA((UPTR)Rsdp->RsdtAddr);
        RootSdtEntries = (RootSdt->Header.Length - sizeof(RootSdt->Header)) / 4;
    } else {
        DTRACE("using xsdt as root sdt\n");
        RootSdt = PMA_TO_VMA((UPTR)Rsdp->XsdtAddr);
        RootSdtEntries = (RootSdt->Header.Length - sizeof(RootSdt->Header)) / 8;
    }
}
