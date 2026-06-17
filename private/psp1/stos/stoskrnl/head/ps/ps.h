/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: High-level process management
 * Author:      Chloe M.
 */

#ifndef _PS_PS_H_
#define _PS_PS_H_ 1

#include <stapi/status.h>
#include <se/token.h>
#include <stdef.h>

/* Maximum length of process name */
#define PROCESS_NAMESZ 32

/* For allocations */
#define PS_POOL_TAG 'PS'

/* Default per-process policy */
#define DEFAULT_SEC_POLICY TOKEN_MAC

/*
 * Represents a process
 *
 * @Name: Process name
 * @ProcessId: ID of process
 * @SecKey:    Security key associated with process
 */
typedef struct {
    CHAR Name[PROCESS_NAMESZ];
    UQUAD ProcessId;
    SECURITY_KEY SecKey;
} EPROCESS;

/*
 * Create a new process
 *
 * @Name:   Name of process to create
 * @Flags:  Process init flags
 * @Result: Result is written here
 */
ST_STATUS PsCreateProcess(const CHAR *Name, USHORT Flags, EPROCESS **Result);

#endif  /* !_PS_PS_H_ */
