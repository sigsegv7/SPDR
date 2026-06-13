/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Interrupt Vector entries
 * Author:      Chloe M.
 */

#include <machine/idt.h>
#include <machine/kfence.h>

    .macro SetTrap, Vector, Isr, Ist
        mov $\Vector, %rdi
        lea \Isr(%rip), %rsi
        mov $IDT_TRAP_GATE, %rdx
        mov $\Ist, %rcx
        call MdIdtSetEntry
    .endm

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

    .text
    .globl MdVectorInit
MdVectorInit:
    push %r12
    push %r13
    push %r14
    push %r15
    push %rbx
    push %rbp

    SetTrap 0x00, DivErr, 0
    SetTrap 0x01, DebugExcept, 0
    SetTrap 0x02, Nmi, 0
    SetTrap 0x03, Breakpoint, 0
    SetTrap 0x04, Overflow, 0
    SetTrap 0x05, BoundRange, 0
    SetTrap 0x06, InvalidOpcode, 0
    SetTrap 0x07, NoCoproc, 0
    SetTrap 0x08, DoubleFault, 0
    SetTrap 0x0A, InvalidTss, 0
    SetTrap 0x0B, SegNp, 0
    SetTrap 0x0C, StackSegFault, 0
    SetTrap 0x0D, Gpf, 0
    SetTrap 0x0E, PageFault, 0

    pop %rbp
    pop %rbx
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    retq

    .text
    .extern MdTrapDispatch
    .align 8
DivErr:
    KFENCE
    PushFrame 0x00
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE
1:  cli
    hlt
    jmp 1b

DebugExcept:
    KFENCE
    PushFrame 0x1
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE
1:  cli
    hlt
    jmp 1b

Nmi:
    KFENCE
    PushFrame 0x2
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE
1:  cli
    hlt
    jmp 1b

Breakpoint:
    KFENCE
    PushFrame 0x3
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE
1:  cli
    hlt
    jmp 1b

Overflow:
    KFENCE
    PushFrame 0x4
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE
1:  cli
    hlt
    jmp 1b

BoundRange:
    KFENCE
    PushFrame 0x5
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE
1:  cli
    hlt
    jmp 1b

InvalidOpcode:
    KFENCE
    PushFrame 0x6
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE
1:  cli
    hlt
    jmp 1b

NoCoproc:
    KFENCE
    PushFrame 0x7
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE
1:  cli
    hlt
    jmp 1b

DoubleFault:
    KFENCE_EC
    PushFrame 0x8
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE_EC
1:  cli
    hlt
    jmp 1b

InvalidTss:
    KFENCE_EC
    PushFrame 0xA
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE_EC
1:  cli
    hlt
    jmp 1b

SegNp:
    KFENCE_EC
    PushFrame 0xB
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE_EC
1:  cli
    hlt
    jmp 1b

StackSegFault:
    KFENCE_EC
    PushFrame 0xC
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE_EC
1:  cli
    hlt
    jmp 1b

Gpf:
    KFENCE_EC
    PushFrame 0xD
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE_EC
1:  cli
    hlt
    jmp 1b

PageFault:
    KFENCE_EC
    PushFrame 0xE
    mov %rsp, %rdi
    call MdTrapDispatch
    KFENCE_EC
1:  cli
    hlt
    jmp 1b
    hlt
