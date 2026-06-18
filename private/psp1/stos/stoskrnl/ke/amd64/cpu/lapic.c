/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Local APIC driver
 * Author:      Chloe M.
 */

#include <machine/lapic.h>
#include <machine/lapicreg.h>
#include <machine/msr.h>
#include <machine/cpuid.h>
#include <drivers/acpi/acpi.h>
#include <drivers/acpi/tables.h>
#include <hal/mmio.h>
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
 * Returns true if the Local APIC unit is x2APIC
 * capable
 */
static inline BOOL
LapicHasX2Apic(VOID)
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

/*
 * Read a value from a Local APIC register
 *
 * @Mcb:        Machine core block of current processor
 * @Register:   Register to read
 */
static UQUAD
LapicRead(MCB *Mcb, USHORT Register)
{
    ULONG *RegBase;
    UQUAD Value;

    if (Mcb == NULL) {
        return 0;
    }

    if (Mcb->HasX2Apic) {
        Register >>= 4;
        Value = MdRdmsr(x2APIC_MSR_BASE + Register);
    } else {
        RegBase = PTR_OFFSET(Mcb->LapicBase, Register);
        Value = MMIORead32(RegBase);
    }

    return Value;
}

/*
 * Write a value to a Local APIC register
 *
 * @Mcb:        Machine core block
 * @Register:   Register to read
 * @Value:      Value to write
 */
static VOID
LapicWrite(MCB *Mcb, USHORT Register, UQUAD Value)
{
    ULONG *RegBase;

    if (Mcb == NULL) {
        return;
    }

    if (Mcb->HasX2Apic) {
        Register >>= 4;
        MdWrmsr(x2APIC_MSR_BASE + Register, Value);
    } else {
        RegBase = PTR_OFFSET(Mcb->LapicBase, Register);
        MMIOWrite32(RegBase, (ULONG)Value);
    }
}

/*
 * Enable the Local APIC unit
 */
static VOID
LapicEnable(MCB *Mcb)
{
    UQUAD ApicBase;
    ULONG Svr, VersionReg;
    UCHAR Version;
    const CHAR *ApicType = "integrated apic";
    const CHAR *ApicMode = "xapic";

    Mcb->HasX2Apic = LapicHasX2Apic();
    if (Mcb->HasX2Apic) {
        ApicMode = "x2apic";
    }

    /* Hardware enable the Local APIC */
    ApicBase = MdRdmsr(IA32_APIC_BASE_MSR);
    ApicBase |= LAPIC_HW_ENABLE;
    ApicBase |= Mcb->HasX2Apic << x2APIC_ENABLE_SHIFT;
    MdWrmsr(IA32_APIC_BASE_MSR, ApicBase);

    /* Software enable the Local APIC */
    Svr = LapicRead(Mcb, LAPIC_SVR);
    Svr |= LAPIC_SW_ENABLE;
    LapicWrite(Mcb, LAPIC_SVR, Svr);

    /* Obtain the version */
    VersionReg = LapicRead(Mcb, LAPIC_VERSION);
    Version = VersionReg & 0xFF;

    if (Version == 0) {
        ApicType = "discrete 82489DX";
    }

    DTRACE("%s enabled in %s mode\n", ApicType, ApicMode);
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

    /* Obtain the Local APIC MMIO base */
    Mcb = &Kpcr->CoreData;
    Mcb->LapicBase = LapicGetBase();
    DTRACE("mmio space available @ %p\n", Mcb->LapicBase);

    /* Enable the Local APIC unit */
    LapicEnable(Mcb);
}
