/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Interrupt management interface
 * Author:      Chloe M.
 */

#ifndef _HAL_INTR_H_
#define _HAL_INTR_H_ 1

#include <stdef.h>
#include <machine/intr.h>

/* Interrupt priority levels */
#define IRQL_NONE  0     /* Don't defer any interrupts */
#define IRQL_BIO   1     /* Defer I/O */
#define IRQL_CLOCK 2     /* Defer clock interrupts */
#define IRQL_HIGH  3     /* Defer everything */

#define SERVICE_ROUTINE(ISR) \
    ((UPTR)(ISR))

/*
 * Interrupt handler descriptor
 *
 * @ServiceRoutine: Interrupt service routine base
 * @Priority:       Interrupt priority
 * @Present:        Must be set to be valid
 *
 * XXX: The present bit is set by HalRegisterIntr() and does
 *      not need to be set manually.
 */
typedef struct {
    UPTR ServiceRoutine;
    UCHAR Priority : 4;
    UCHAR Present  : 1;
} INTR_HANDLER;

/*
 * Register an interrupt handler
 *
 * @Handler: Handler to register
 *
 * Returns interrupt vector on success
 */
UCHAR HalRegisterIntr(INTR_HANDLER *Handler);

/*
 * Raise the IRQL for the current processor
 *
 * @Irql: IRQL to raise to
 *
 * Returns the previous IRQL before being raised
 */
UCHAR HalRaiseIrql(UCHAR Irql);

/*
 * Lower the IRQL for the current processor
 *
 * @Irql: IRQL to lower to
 *
 * Returns the previous IRQL before being lowered
 */
UCHAR HalLowerIrql(UCHAR Irql);

#endif  /* !_HAL_INTR_H_ */
