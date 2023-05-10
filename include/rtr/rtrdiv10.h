/*
 *|---------------------------------------------------------------
 *|                Copyright (C) 2005 Reuters,                  --
 *|         1111 West 22nd Street, Oak Brook, IL. 60523         --
 *| All rights reserved. Duplication or distribution prohibited --
 *|---------------------------------------------------------------
 *
 * Author:	Robert Bonaguro
 * Date:	January 27, 2005
 *
 * Decsription:
 * This header file defines a macro that implements that fastest 
 * unsigned long division by 10 including the remainder. It may be
 * different per operating system.
 * __rtr_u32div10(value,quo,rem)
 * 		value - unsigned long value to divide by 10.
 * 		quo - unsigned long quotient of result.
 * 		rem - unsigned long remainder of result.
 *
 * The above macro uses the ones defined below depending on OS.
 *
 * Division by 10, let the compiler optimize.
 * __rtr_comp_u32div10(value,quo,rem)
 * 		value - unsigned long value to divide by 10.
 * 		quo - unsigned long quotient of result.
 * 		rem - unsigned long remainder of result.
 *
 * Division by 10 using decimal in c-code.
 * __rtr_hand_u32div10(value,quo,rem)
 * 		value - unsigned long value to divide by 10.
 * 		quo - unsigned long quotient of result.
 * 		rem - unsigned long remainder of result.
 *
 * Division by 10 using decimal in assembler.
 * __rtr_asm_u32div10(value,quo,rem)
 * 		value - unsigned long value to divide by 10.
 * 		quo - unsigned long quotient of result.
 * 		rem - unsigned long remainder of result.
 *
 */

#ifndef __RTR_DIVIDE10_H
#define __RTR_DIVIDE10_H

#include "rtr/os.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN64
	extern  void __rtr_asm_u32mul10_X64(void *);
#endif


/* Compiler optimized unsigned division by 10.
 * value - unsigned long value to divide by 10.
 * quo - quotient of result.
 * rem - remainder of result.
 */
#define __rtr_comp_u32div10( value, quo, rem ) \
	quo = value/10; rem = value - quo * 10


 /*
 * This header file defines macros that implements division by
 * 10 using a multiply and a shift. This is much more efficient than
 * division.
 * It works by using decimal arithmetic in binary. In effect a
 * 32 bit division can be turned into a 64 bit multiply and shift.
 * BASE10_MULTIPLIER represents the binary 1/10, after shift and
 * rounding.
 */
#define BASE10_MULTIPLIER   0xcccccccdUL
#define BASE10_POSTSHIFT    3


#ifdef RTR_I64

/* By hand optimized unsigned division by 10.
 * value - unsigned long value to divide by 10.
 * quo - quotient of result.
 * rem - remainder of result.
	quo = (unsigned long)((((unsigned RTR_LONGLONG)value * BASE10_MULTIPLIER) >> BASE10_POSTSHIFT) + 32);\
 */
#define __rtr_hand_u32div10( value, quo, rem ) \
	quo = (unsigned long)((unsigned RTR_LONGLONG)(((unsigned RTR_LONGLONG)value * (unsigned RTR_LONGLONG)BASE10_MULTIPLIER) >> (BASE10_POSTSHIFT + 32)));\
	rem = value - quo * 10
#endif


#ifdef Linux

#define __rtr_asm_u32mul10(value, quo, mult) \
    __asm__ ("mov %%ecx, %%eax; mul %%ebx;shr $0x3,%%edx" \
                    : "=d" (quo)        \
                    : "b" (value),      \
                      "c" (mult) : "%eax")

					  
/* Assembler optimized unsigned division by 10.
 * value - unsigned long value to divide by 10.
 * quo - quotient of result.
 * rem - remainder of result.
 */
#define __rtr_asm_u32div10(value, quo, rem) \
	__rtr_asm_u32mul10(value,quo,BASE10_MULTIPLIER); \
	rem = value - quo * 10

#endif


#ifdef _WIN32

#ifdef _WIN64
#define __rtr_asm_u32mul10(quo, value)  \
	struct{ \
		unsigned long BM; \
		unsigned long quo; \
		unsigned long value; \
	} ca; \
	ca.BM = BASE10_MULTIPLIER; \
	ca.quo = quo; \
	ca.value = value; \
	__rtr_asm_u32mul10_X64(&ca); \
	quo = ca.quo; \
	value = ca.value; 
#else
#define __rtr_asm_u32mul10(quo, value) __asm \
{ \
	__asm mov esi, BASE10_MULTIPLIER \
	__asm mov eax, dword ptr value \
	__asm mul esi \
	__asm shr edx, BASE10_POSTSHIFT \
	__asm mov dword ptr quo,edx \
}
#endif

/* Assembler optimized unsigned division by 10.
 * value - unsigned long value to divide by 10.
 * quo - quotient of result.
 * rem - remainder of result.
 */
#define __rtr_asm_u32div10(value, quo, rem) \
{ \
	__rtr_asm_u32mul10(quo, value); \
	rem = value - quo * 10; \
}

#endif



#if defined(Linux)
#ifdef COMPILE_64BITS
/* Hand Multiply optimized unsigned division by 10 is fastest for this OS. */
#define __rtr_u32div10(___value, ___quo, ___rem) __rtr_hand_u32div10(___value, ___quo, ___rem)
#else
/* Assembler optimized unsigned division by 10 is fastest for this OS. */
#define __rtr_u32div10(___value, ___quo, ___rem) __rtr_asm_u32div10(___value, ___quo, ___rem)
#endif
#endif


#ifdef _WIN64
/* Hand multiply optimized unsigned division is fastest for this OS. */
#define __rtr_u32div10(___value, ___quo, ___rem) __rtr_hand_u32div10(___value, ___quo, ___rem)
#elif defined (_WIN32)
/* Assembler optimized unsigned division is fastest for this OS. */
#define __rtr_u32div10(___value, ___quo, ___rem) __rtr_asm_u32div10(___value, ___quo, ___rem)
#endif


#if defined(SOLARIS2)
/* Hand multiply optimized unsigned division is fastest for this OS. */
#define __rtr_u32div10(___value, ___quo, ___rem) __rtr_hand_u32div10( ___value, ___quo, ___rem )
#endif


#ifndef __rtr_u32div10
#define __rtr_u32div10(___value, ___quo, ___rem) __rtr_comp_u32div10( ___value, ___quo, ___rem )
#endif



#ifdef __cplusplus
};
#endif

#endif
