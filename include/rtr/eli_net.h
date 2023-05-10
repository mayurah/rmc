/*
*	(C) Copyright 1992 Reuters, Oak Brook IL., All Rights Reserved.
*/

#ifndef __ELI_NET
#define __ELI_NET

#include "rtr/platform.h"
#include "rtr/rtdataty.h"

#define ELI_MOVE_8(d,s) \
    ((char*)(d))[0] = ((char*)(s))[0];

#ifdef DEV_LITTLE_ENDIAN
    /* The following are for LE machines (i.e. low-byte to high-byte ordering) */

#define ELI_MOVE_16(d,s) \
    ((char*)(d))[0] = ((char*)(s))[1];\
    ((char*)(d))[1] = ((char*)(s))[0]
#define ELI_MOVE_32(d,s) \
    ((char*)(d))[0] = ((char*)(s))[3];\
    ((char*)(d))[1] = ((char*)(s))[2];\
    ((char*)(d))[2] = ((char*)(s))[1];\
    ((char*)(d))[3] = ((char*)(s))[0]
#define ELI_MOVE_SHORT_8(d,s)\
    ((char*)(d))[0] = ((char*)(s))[0]
#define ELI_MOVE_SHORT_32(d,s)\
    ((char*)(d))[0] = 0;\
    ((char*)(d))[1] = 0;\
    ((char*)(d))[2] = ((char*)(s))[1];\
    ((char*)(d))[3] = ((char*)(s))[0]
#define ELI_MOVE_LONG_8(d,s)\
    ((char*)(d))[0] = ((char*)(s))[0]
#define ELI_MOVE_LONG_16(d,s)\
    ((char*)(d))[0] = ((char*)(s))[1];\
    ((char*)(d))[1] = ((char*)(s))[0]
#define ELI_MOVE_FLOAT(d,s)\
    ((char*)(d))[0] = ((char*)(s))[3];\
    ((char*)(d))[1] = ((char*)(s))[2];\
    ((char*)(d))[2] = ((char*)(s))[1];\
    ((char*)(d))[3] = ((char*)(s))[0]
#define ELI_MOVE_DOUBLE(d,s)\
    ((char*)(d))[0] = ((char*)(s))[7];\
    ((char*)(d))[1] = ((char*)(s))[6];\
    ((char*)(d))[2] = ((char*)(s))[5];\
    ((char*)(d))[3] = ((char*)(s))[4];\
    ((char*)(d))[4] = ((char*)(s))[3];\
    ((char*)(d))[5] = ((char*)(s))[2];\
    ((char*)(d))[6] = ((char*)(s))[1];\
    ((char*)(d))[7] = ((char*)(s))[0]

#ifdef DEV_SMALL_INT
    /* The following are for LE machines with 16 bit integers */

#define ELI_MOVE_INT_32(d,s) \
    ((char*)(d))[0] = 0;\
    ((char*)(d))[1] = 0;\
    ((char*)(d))[2] = ((char*)(s))[1];\
    ((char*)(d))[3] = ((char*)(s))[0]
#define ELI_MOVE_INT_16(d,s) \
    ((char*)(d))[0] = ((char*)(s))[1];\
    ((char*)(d))[1] = ((char*)(s))[0]
#define ELI_MOVE_INT_8(d,s) \
    ((char*)(d))[0] = ((char*)(s))[0]
#define ELI_MOVE_32_INT(d,s) \
    ((char*)(d))[0] = ((char*)(s))[3];\
    ((char*)(d))[1] = ((char*)(s))[2]

#else /* 32-bit integer */
    /* The following are for LE machines with 32 bit integers */

#define ELI_MOVE_INT_32(d,s) \
    ((char*)(d))[0] = ((char*)(s))[3];\
    ((char*)(d))[1] = ((char*)(s))[2];\
    ((char*)(d))[2] = ((char*)(s))[1];\
    ((char*)(d))[3] = ((char*)(s))[0]
#define ELI_MOVE_INT_16(d,s) \
    ((char*)(d))[0] = ((char*)(s))[1];\
    ((char*)(d))[1] = ((char*)(s))[0]
#define ELI_MOVE_INT_8(d,s) \
    ((char*)(d))[0] = ((char*)(s))[0]
#define ELI_MOVE_32_INT(d,s) \
    ((char*)(d))[0] = ((char*)(s))[3];\
    ((char*)(d))[1] = ((char*)(s))[2];\
    ((char*)(d))[2] = ((char*)(s))[1];\
    ((char*)(d))[3] = ((char*)(s))[0]
#endif /* 16-bit or 32-bit integer */

/*
 *	The following macros put, up to a 15 bit value, for transmission
 *	over a network. If the value is less than 128, it can be transmitted
 *	in one byte. Anything 128 and over is transmitted in two bytes.
 *	When parsing, the high order bit of the first byte tells you
 *	if there is another byte for this value.
 *    Value - Transmitted as
 *	Ex. 1 - 01
 *  Ex. 127  -  7F
 *  Ex. 128  -  8080
 *	Max value : 32767 - FFFF
 */
#define ELI_PUT_CHAIN_U15(d,s) \
	( ( *((u_16*)s) <= 0x7F ) ? \
		( ((char*)(d))[0] = ((char*)(s))[0], 1 ) : \
			( ((char*)(d))[1] = ((char*)(s))[0], \
				((char*)(d))[0] = (((char*)(s))[1] | 0x80), 2 ) )

#define ELI_GET_CHAIN_U15(d,s) \
	( ( (unsigned char)((char*)(s))[0] & 0x80 )  ? \
		( ((char*)(d))[1] = (((char*)(s))[0] & 0x7F), \
			((char*)(d))[0] = ((char*)(s))[1], 2 ) : \
				( ((char*)(d))[0] = ((char*)(s))[0], ((char*)(d))[1] = 0, 1 ) )


#else /* DEV_BIG_ENDIAN */
    /* The following are for BE machines (i.e. high-byte to low-byte ordering) */

#define ELI_MOVE_16(d,s) \
    ((char*)(d))[0] = ((char*)(s))[0];\
    ((char*)(d))[1] = ((char*)(s))[1]
#define ELI_MOVE_32(d,s) \
    ((char*)(d))[0] = ((char*)(s))[0];\
    ((char*)(d))[1] = ((char*)(s))[1];\
    ((char*)(d))[2] = ((char*)(s))[2];\
    ((char*)(d))[3] = ((char*)(s))[3]
#define ELI_MOVE_SHORT_8(d,s)\
    ((char*)(d))[0] = ((char*)(s))[1]
#define ELI_MOVE_SHORT_32(d,s)\
    ((char*)(d))[0] = 0;\
    ((char*)(d))[1] = 0;\
    ((char*)(d))[2] = ((char*)(s))[0];\
    ((char*)(d))[3] = ((char*)(s))[1]
#define ELI_MOVE_LONG_8(d,s)\
    ((char*)(d))[0] = ((char*)(s))[3]
#define ELI_MOVE_LONG_16(d,s)\
    ((char*)(d))[0] = ((char*)(s))[2];\
    ((char*)(d))[1] = ((char*)(s))[3]
#define ELI_MOVE_FLOAT(d,s)\
    ((char*)(d))[0] = ((char*)(s))[0];\
    ((char*)(d))[1] = ((char*)(s))[1];\
    ((char*)(d))[2] = ((char*)(s))[2];\
    ((char*)(d))[3] = ((char*)(s))[3]
#define ELI_MOVE_DOUBLE(d,s)\
    ((char*)(d))[0] = ((char*)(s))[0];\
    ((char*)(d))[1] = ((char*)(s))[1];\
    ((char*)(d))[2] = ((char*)(s))[2];\
    ((char*)(d))[3] = ((char*)(s))[3];\
    ((char*)(d))[4] = ((char*)(s))[4];\
    ((char*)(d))[5] = ((char*)(s))[5];\
    ((char*)(d))[6] = ((char*)(s))[6];\
    ((char*)(d))[7] = ((char*)(s))[7]

#ifdef DEV_SMALL_INT
    /* The following are for BE machines with 16 bit integers */

#define ELI_MOVE_INT_32(d,s) \
    ((char*)(d))[0] = 0;\
    ((char*)(d))[1] = 0;\
    ((char*)(d))[2] = ((char*)(s))[0];\
    ((char*)(d))[3] = ((char*)(s))[1]
#define ELI_MOVE_INT_16(d,s) \
    ((char*)(d))[0] = ((char*)(s))[0];\
    ((char*)(d))[1] = ((char*)(s))[1]
#define ELI_MOVE_INT_8(d,s) \
    ((char*)(d))[0] = ((char*)(s))[1]
#define ELI_MOVE_32_INT(d,s) \
    ((char*)(d))[0] = ((char*)(s))[2];\
    ((char*)(d))[1] = ((char*)(s))[3]

#else /* 32-bit integer */
    /* The following are for BE machines with 32 bit integers */

#define ELI_MOVE_INT_32(d,s) \
    ((char*)(d))[0] = ((char*)(s))[0];\
    ((char*)(d))[1] = ((char*)(s))[1];\
    ((char*)(d))[2] = ((char*)(s))[2];\
    ((char*)(d))[3] = ((char*)(s))[3]
#define ELI_MOVE_INT_16(d,s) \
    ((char*)(d))[0] = ((char*)(s))[2];\
    ((char*)(d))[1] = ((char*)(s))[3]
#define ELI_MOVE_INT_8(d,s) \
    ((char*)(d))[0] = ((char*)(s))[3]
#define ELI_MOVE_32_INT(d,s) \
    ((char*)(d))[0] = ((char*)(s))[0];\
    ((char*)(d))[1] = ((char*)(s))[1];\
    ((char*)(d))[2] = ((char*)(s))[2];\
    ((char*)(d))[3] = ((char*)(s))[3]
#endif /* 16-bit or 32-bit integer */


/*
 *	The following macros put, up to a 15 bit value, for transmission
 *	over a network. If the value is less than 128, it can be transmitted
 *	in one byte. Anything 128 and over is transmitted in two bytes.
 *	When parsing, the high order bit of the first byte tells you
 *	if there is another byte for this value.
 *    Value - Transmitted as
 *	Ex. 1 - 01
 *  Ex. 127  -  7F
 *  Ex. 128  -  8080
 *	Max value : 32767 - FFFF
 */
#define ELI_PUT_CHAIN_U15(d,s) \
	( ( *((u_16*)s) <= 0x7F ) ? \
		( ((char*)(d))[0] = ((char*)(s))[1], 1 ) : \
			( ((char*)(d))[1] = ((char*)(s))[1], \
				((char*)(d))[0] = (((char*)(s))[0] | 0x80), 2 ) )

#define ELI_GET_CHAIN_U15(d,s) \
	( ( (unsigned char)((char*)(s))[0] & 0x80 )  ? \
		( ((char*)(d))[0] = (((char*)(s))[0] & 0x7F), \
			((char*)(d))[1] = ((char*)(s))[1], 2 ) : \
				( ((char*)(d))[1] = ((char*)(s))[0], ((char*)(d))[0] = 0, 1 ) )



#endif /* LE or BE */


// Define the move short, move int, and move long
// for machines.
#ifdef SHORT_8_BIT
#define ELI_MOVE_SHORT ELI_MOVE_8
#else
#define ELI_MOVE_SHORT ELI_MOVE_16
#endif

#ifdef INT_16_BIT
#define ELI_MOVE_INT ELI_MOVE_16
#else
#define ELI_MOVE_INT ELI_MOVE_32
#endif

#define ELI_MOVE_LONG ELI_MOVE_32

#endif
