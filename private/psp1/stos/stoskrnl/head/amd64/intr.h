/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Interrupt management interface
 * Author:      Chloe M.
 */

#ifndef _MACHINE_INTR_H_
#define _MACHINE_INTR_H_ 1

#define IPL_SHIFT 4

/* List of predefined vectors */
#define VECTOR_SYSCALL 0x80
#define VECTOR_SCHED   0x81

#endif  /* !_MACHINE_INTR_H_ */
