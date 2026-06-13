/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Interrupt descriptor table
 * Author:      Chloe M.
 */

#include <machine/idt.h>
#include <machine/gdt.h>

 #define IDT_VECTOR_SHIFT 4

    .text
    .globl MdIdtSetEntry
MdIdtSetEntry:
    /*
     * Set an IDT entry
     *
     * @[RDI]: Interrupt vector of entry to set
     * @[RSI]: Interrupt service routine base
     * @[RDX]: Interrupt gate type
     * @[RCX]: Interrupt stack table index
     */

    push %r12
    push %r13
    push %r14
    push %r15
    push %rbx

    shl $IDT_VECTOR_SHIFT, %rdi     /* Scale the vector by IDT size */
    lea IdtTable(%rip), %rbx        /* IDT base -> RBX */
    add %rdi, %rbx                  /* Obtain the entry */

    mov %rsi, %rax                  /* ISR base -> RAX */
    and $0xFFFF, %rax               /* Obtain ISR[15:0] */
    mov %ax, 0(%rbx)                /* Set the ISR base */

    movw $GDT_KCODE, 2(%rbx)        /* Set the code selector */
    xor %rax, %rax                  /* Clear out RAX */
    and $0x3, %cl                   /* Ensure we only have 3 bits */
    or %cl, %al                     /* Merge it with RAX */

    and $0xF, %rdx                  /* Ensure we only get 4 bits */
    shl $8, %rdx                    /* Prepare to merge it */
    or %rdx, %rax                   /* Merge it */
    or $1<<15, %rax                 /* Mark as present */

    cmpb $IDT_USER_GATE, %dl        /* Is this DPL3? */
    jne 1f                          /* No, skip .Dpl3 */

.Dpl3:
    or $3<<13, %rax                 /* Set DPL 3 */
1:  mov %rsi, %r12                  /* Copy ISR base to R12 */
    shr $16, %r12                   /* Obtain the middle 16-bits */
    and $0xFFFF, %r12               /* Isolate it */
    shl $16, %r12                   /* Shift it back up */
    or %r12, %rax                   /* Merge it */

    mov %rax, 4(%rbx)               /* Set the second dword */
    mov %rsi, %r12                  /* Copy ISR base to R12 */
    shr $32, %r12                   /* Isolate the upper dword */
    mov %r12, 8(%rbx)               /* Write it */

    pop %rbx
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    retq

    .globl MdIdtLoad
MdIdtLoad:
    lea Idtr(%rip), %rax
    lidt (%rax)
    retq

    .section .data
Idtr:
    .word 4095
    .quad IdtTable

    .section .bss
    .align 8
IdtTable:
    .skip 4096, 0
