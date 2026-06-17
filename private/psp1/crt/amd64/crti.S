/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: C runtime entry
 * Author:      Chloe M.
 */

    .text
    .globl _start
_start:
    xor %rbp, %rbp      /* Terminate callstack */
    call Main
1:  pause
    jmp 1b
