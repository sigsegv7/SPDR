/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Local APIC driver
 * Author:      Chloe M.
 */

#include <machine/lapic.h>
#include <machine/msr.h>
#include <machine/cpuid.h>
#include <drivers/acpi/acpi.h>
#include <drivers/acpi/tables.h>
#include <mm/vmm.h>
#include <ex/trace.h>
#include <ke/knot.h>
#include <stdef.h>

#define DTRACE(Fmt, ...) \
    TRACE("[ LAPIC ]: " Fmt, ##__VA_ARGS__)

/*
 * Returns true if the processor contains a Local APIC
 * unit.
 */
static inline BOOL
LapicIsPresent(VOID)
{
    ULONG Edx, Unused;

    CPUID(0x01, Unused, Unused, Unused, Edx);
    return ISSET(Edx, BIT(9)) != 0;
}

/*
 * Obtain the base address of the Local APIC unit
 */
static VOID *
LapicGetBase(VOID)
{
    ACPI_MADT *Madt;

    Madt = AcpiQuery("APIC");
    if (Madt == NULL) {
        return NULL;
    }

    return PMA_TO_VMA((UQUAD)Madt->LapicAddr);
}

VOID
MdLapicInit(KPCR *Kpcr)
{
    VOID *LapicBase;
    MCB *Mcb;

    if (Kpcr == NULL) {
        return;
    }

    /*
     * SystemPaw requires the presence of a Local APIC unit, if we
     * don't have it, knot.
     */
    if (!LapicIsPresent()) {
        KeKnot("Processor does not include Local APIC unit\n");
    }

    Mcb = &Kpcr->CoreData;
    Mcb->LapicBase = LapicGetBase();
    DTRACE("mmio space available @ %p\n", Mcb->LapicBase);
}
