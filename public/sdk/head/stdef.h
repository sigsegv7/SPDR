/*
 * Copyright (c) 2026, Chloe M.
 * Provided under the BSD-3 clause.
 *
 * Description: Basic global definitions and types
 * Author:      Chloe M.
 */

#ifndef _SDK_STDEF_H_
#define _SDK_STDEF_H_ 1

/* Boolean values */
#define true 1
#define false 0

#if !defined(__cplusplus)
#define NULL  ((void *)0)
#else
#if __cplusplus >= 201103L
#define NULL  nullptr
#else
#define NULL ((void *)0)
#endif  /* __cplusplus >= 201103L */
#endif  /* __cplusplus */

/* Compiler specific definitions */
#define ASMV              __asm__ __volatile__
#define ATTR(X)           __attribute__((x))
#define SECTION(X)        ATTR(section((x)))
#define ALIGN(N)          ATTR(aligned((n)))
#define PACKED            ATTR(packed)
#define NO_RETURN         ATTR(noreturn)
#define ALWAYS_INLINE     ATTR(always_inline)
#define BARRIER()         ASMV("" ::: "memory")

/* Pointer offset macros */
#define PTR_OFFSET(p, off) ((void *)(char *)(p) + (off))
#define PTR_NOFFSET(p, off) ((void *)(char *)(p) - (off))

/* Bit related macros */
#define BIT(n) (1ULL << (n))
#define ISSET(v, f)  ((v) & (f))

/* Align up/down a value */
#define ALIGN_DOWN(value, align)      ((value) & ~((align)-1))
#define ALIGN_UP(value, align)        (((value) + (align)-1) & ~((align)-1))

/* Bitmap helper macros */
#define SETBIT(a, b) ((a)[(b) >> 3] |= BIT(b % 8))
#define CLRBIT(a, b) ((a)[(b) >> 3] &= ~BIT(b % 8))
#define TESTBIT(a, b) (ISSET((a)[(b) >> 3], BIT(b % 8)))

/* Min/max macros */
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

/* Get number of array elements */
#define NELEM(a) (sizeof(a) / sizeof(a[0]))

/* Basic types */
typedef void VOID;
typedef _Bool BOOL;

/* Basic signed types */
typedef char CHAR;
typedef short SHORT;
typedef int LONG;
typedef long long QUAD;
typedef QUAD SSIZE;

/* Basic unsigned types */
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int ULONG;
typedef unsigned long long UQUAD;
typedef UQUAD USIZE;
typedef UQUAD UPTR;

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
typedef __builtin_va_list __gnuc_va_list;
#endif      /* __GNUC_VA_LIST */

typedef __gnuc_va_list va_list;

#define va_start(ap, last)  __builtin_va_start((ap), last)
#define va_end(ap)          __builtin_va_end((ap))
#define va_arg(ap, type)    __builtin_va_arg((ap), type)

#endif  /* !_SDK_STDEF_H_ */
