/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Trap frame defs
 * Author:      Chloe M.
 */

#ifndef _MACHINE_FRAME_H_
#define _MACHINE_FRAME_H_ 1

#ifndef __ASSEMBLER__
#include <stdef.h>
#endif /* !__ASSEMBLER__ */

#ifndef __ASSEMBLER__
typedef struct PACKED {
    UQUAD Vector;
    UQUAD Rax;
    UQUAD Rbx;
    UQUAD Rcx;
    UQUAD Rdx;
    UQUAD Rsi;
    UQUAD Rdi;
    UQUAD Rbp;
    UQUAD R8;
    UQUAD R9;
    UQUAD R10;
    UQUAD R11;
    UQUAD R12;
    UQUAD R13;
    UQUAD R14;
    UQUAD R15;
    /* Pushed by hardawre */
    UQUAD ErrorCode;
    UQUAD Rip;
    UQUAD CodeSeg;
    UQUAD Rflags;
    UQUAD Rsp;
    UQUAD StackSeg;
} TRAP_FRAME;
#else
.macro PushFrame Vector
    .if \Vector == 10 || \Vector == 11 || \Vector == 12 || \Vector == 13 \
        || \Vector == 14
        subq $8, %rsp
    .endif

    push %r15
    push %r14
    push %r13
    push %r12
    push %r11
    push %r10
    push %r9
    push %r8
    push %rbp
    push %rdi
    push %rsi
    push %rdx
    push %rcx
    push %rbx
    push %rax
    push $\Vector
.endm

.macro PopFrame Vector
    .if \Vector == 10 || \Vector == 11 || \Vector == 12 || \Vector == 13 \
        || \Vector == 14
        addq $8, %rsp
    .endif

    add $8, %rsp
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rbp
    pop %rdi
    pop %rsi
    pop %rdx
    pop %rcx
    pop %rbx
    pop %rax
.endm
#endif /* !__ASSEMBLER__ */
#endif  /* !_MACHINE_FRAME_H_ */
