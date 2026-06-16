/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: High-level process management
 * Author:      Chloe M.
 */

#ifndef _PS_PS_H_
#define _PS_PS_H_ 1

#include <stdef.h>

/* Maximum length of process name */
#define PROCESS_NAMESZ 32

/*
 * Represents a process
 *
 * @Name: Process name
 * @ProcessId: ID of process
 */
typedef struct {
    CHAR Name[PROCESS_NAMESZ];
    UQUAD ProcessId;
} EPROCESS;

#endif  /* !_PS_PS_H_ */
