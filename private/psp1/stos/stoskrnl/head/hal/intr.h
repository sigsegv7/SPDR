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
#define IPL_NONE  0     /* Don't defer any interrupts */
#define IPL_BIO   1     /* Defer I/O */
#define IPL_CLOCK 2     /* Defer clock interrupts */
#define IPL_HIGH  3     /* Defer everything */

#define SERVICE_ROUTINE(ISR) \
    ((UPTR)(ISR))

/*
 * Interrupt handler descriptor
 *
 * @ServiceRoutine: Interrupt service routine base
 * @Priority:       Interrupt priority
 */
typedef struct {
    UPTR ServiceRoutine;
    UCHAR Priority : 4;
} INTR_HANDLER;

#endif  /* !_HAL_INTR_H_ */
