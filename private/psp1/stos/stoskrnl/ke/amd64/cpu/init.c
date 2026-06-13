/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Low-level processor initialization
 * Author:      Chloe M.
 */

#include <hal/kpcr.h>
#include <hal/intr.h>
#include <ex/trace.h>
#include <machine/cpuid.h>
#include <machine/msr.h>

#define DTRACE(fmt, ...) \
    TRACE("[ CPU ]: " fmt, ##__VA_ARGS__)

/* Externs */
extern VOID MdCpuInit(VOID);

VOID
CpuIdentify(MCB *Mcb)
{
    ULONG Eax, Unused;
    UCHAR ModelLow, ModelHigh;
    UCHAR FamilyLow;
    USHORT FamilyHigh;

    if (Mcb == NULL) {
        return;
    }

    CPUID(0x01, Eax, Unused, Unused, Unused);

    /* Set the model ID */
    ModelLow = (Eax >> 4) & 0xF;
    ModelHigh = (Eax >> 16) & 0xF;
    Mcb->Model = (ModelHigh << 4) | ModelLow;

    /* Set the family ID */
    FamilyLow = (Eax >> 8) & 0xF;
    FamilyHigh = (Eax >> 20) & 0xFFF;
    Mcb->Family = (FamilyHigh << 4) | FamilyLow;

    /* Some informational logging */
    DTRACE("model  : 0x%x\n", Mcb->Model);
    DTRACE("family : 0x%x\n", Mcb->Family);
}

VOID
HalKpcrP1Init(KPCR *Kpcr)
{
    if (Kpcr == NULL) {
        return;
    }

    /*
     * We should default to an ID of zero here, this should
     * be overriden by the component initializing the processors.
     */
    Kpcr->CoreId = 0;

    /* We default to nothing blocked */
    Kpcr->Irql = IRQL_NONE;

    /* Initialize machine specific bits */
    MdCpuInit();

    /* Set as the current processor */
    MdWrmsr(IA32_GS_BASE, (UPTR)Kpcr);
}

VOID
HalKpcrP2Init(KPCR *Kpcr)
{
    MCB *Mcb;

    if (Kpcr == NULL) {
        return;
    }

    Mcb = &Kpcr->CoreData;
    CpuIdentify(Mcb);
}

KPCR *
HalKpcrSelf(VOID)
{
    return (KPCR *)MdRdmsr(IA32_GS_BASE);
}
