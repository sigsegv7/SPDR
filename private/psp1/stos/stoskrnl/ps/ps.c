/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: High-level process management
 * Author:      Chloe M.
 */

#include <ps/ps.h>
#include <ex/pool.h>
#include <ke/spinlock.h>
#include <string.h>

static USIZE NextPid = 0;
static KE_SPINLOCK PidLock;

/*
 * Allocate a new process ID
 */
static USIZE
AllocatePid(VOID)
{
    USIZE Pid;

    KeSpinLockAcq(&PidLock, false);
    Pid = NextPid++;
    KeSpinLockRel(&PidLock);
    return Pid;
}

ST_STATUS
PsCreateProcess(const CHAR *Name, USHORT Flags, EPROCESS **Result)
{
    SECURITY_KEY SecKey;
    EPROCESS *Process;
    USIZE NameLen;
    ST_STATUS Status;

    if (Name == NULL) {
        return STATUS_INVALID_PARAM;
    }

    NameLen = RtlStrLen(Name);
    if (NameLen >= PROCESS_NAMESZ - 1) {
        return STATUS_NAME_TOO_LONG;
    }

    Status = SeSetKeyPolicy(&SecKey, DEFAULT_SEC_POLICY);
    if (Status != STATUS_SUCCESS) {
        return Status;
    }

    Process = ExAllocatePoolWithTag(
        NON_PAGED_POOL,
        sizeof(*Process),
        PS_POOL_TAG
    );

    if (Process == NULL) {
        return STATUS_NO_MEMORY;
    }

    RtlMemSet(Process, 0, sizeof(*Process));
    RtlMemCpy(Process->Name, Name, NameLen);

    Process->ProcessId = AllocatePid();
    Process->SecKey = SecKey;

    *Result = Process;
    return STATUS_SUCCESS;
}
