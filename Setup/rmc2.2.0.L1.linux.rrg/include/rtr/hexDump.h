//
//|---------------------------------------------------------------
//|                Copyright (C) 2000 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60523          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  description:
//

#ifndef __rtr_hexDump
#define __rtr_hexDump

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

// Synopsis:
// #include"rtr/rthexdmp.h"
//
// Description:
//  General Hex Dump Routine.
//  
//	This routine is setup to print out the following format:
//
//	\verbatim
// Hex dump (16 bytes per line)                  Ascii dump   New line or Null
// xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx    ................
// xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx    ................
//	
// 123456789012345678901234567890123456789012345678901234567890
// 	\endverbatim
//
// See Also:
//

class rtHexDump
{
public:

// Constructor
	rtHexDump();

// Operations
#ifndef _RDEV_NO_STL_
	int hexDump( std::ostream & stream, const char *in_buf, int in_buf_len );
		// Dump the hex representation of in_buf to stream.
		// Returns the number of bytes written.
#else
	int hexDump( FILE* stream, const char *in_buf, int in_buf_len );
		// Dump the hex representation of in_buf to stream.
		// Returns the number of bytes written.
#endif
private:

protected:

	int		eobyte;
	char	outchar[20];

#ifndef _RDEV_NO_STL_
	unsigned long startline( std::ostream &, unsigned long cursor );
	unsigned long addline(std::ostream &, unsigned char byte );
#else
	unsigned long startline( FILE*, unsigned long cursor );
	unsigned long addline(FILE*, unsigned char byte );
#endif
};

#endif
