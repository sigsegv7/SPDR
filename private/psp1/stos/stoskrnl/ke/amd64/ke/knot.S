/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Kernel knot handler
 * Author:      Chloe M.
 */

    .text
    .extern KiKnot
    .globl KeKnot
KeKnot:
    cli         /* Don't want to be interrupted */
    cld         /* Just in case */

    /*
     * When fucking and knotting the kernel, it is critical to ensure
     * that only the knotting processor has control over the knot path
     * to avoid a race and getting kernel cum everywhere...
     */
     mov $1, %rax
     xchg %rax, MpLock
     or %rax, %rax
     jnz .LockOut

     /*
      * During knot conditions, we cannot trust the stack as it may be
      * corrupted. We truly don't know the state of the system but we
      * certainly do not want a triple fault.
      */
      lea KnotStackTop(%rip), %rsp
      jmp KiKnot
.LockOut:
    hlt
    jmp .LockOut

    .section .data
MpLock: .quad 0

    .section .bss
KnotStack:
    .skip 4096, 0
KnotStackTop:
