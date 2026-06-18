/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: HPET timer driver
 * Author:      Chloe M.
 */

#include <machine/hpet.h>
#include <drivers/acpi/tables.h>
#include <drivers/acpi/acpi.h>
#include <hal/mmio.h>
#include <ex/trace.h>
#include <ke/knot.h>

#define DTRACE(Fmt, ...) \
    TRACE("[ HPET ]: " Fmt, ##__VA_ARGS__)

VOID
MdHpetInit(VOID)
{
    ACPI_HPET *Hpet;
    ACPI_GAS *HpetGas;

    Hpet = AcpiQuery("HPET");
    if (Hpet == NULL) {
        KeKnot("could not detect HPET\n");
    }

    /* Print some informational logs */
    DTRACE("pci vendor : 0x%X\n", Hpet->PciVendorId);
    DTRACE("comparator count : %d\n", Hpet->ComparatorCount);
    DTRACE("revision : %d\n", Hpet->HardwareRevId);
    DTRACE("minimum tick : %x\n", Hpet->Gas.AddressSpaceId);

    HpetGas = &Hpet->Gas;
    DTRACE("hpet register width : %d bits\n", HpetGas->RegisterBitWidth);
}
