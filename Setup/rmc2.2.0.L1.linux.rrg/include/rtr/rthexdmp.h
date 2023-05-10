//
//|---------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//	author:		Robert Bonaguro
//	created:	April 22, 1994
//	version:	1.1
//

#ifndef __RTR_HEX_DUMP
#define __RTR_HEX_DUMP

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
//  As can be seen there are 60 characters per line needed. If any of
//  the below sprintf's are changed, you must reflect this in the
//  `char_per_line' definintion. Hopefully
//  any class that uses hex_dump calls buffer_size_needed() first to
//  get the correct amount of memory needed first.
//
// See Also:
//	RTRBuffer
//

class RTRHexDump
{
private:

protected:

	// Number of characters per line in the hex dump output.
	int		char_per_line;
	int		eobyte;
	char	outchar[20];


	short check_size(	unsigned long start,
						unsigned long current,
						int max );

	unsigned long startline(	unsigned long loc,
								unsigned long cursor );
	
	unsigned long addline(	unsigned long location,
							unsigned char byte );


public:

	RTRHexDump() : eobyte( 0 ), char_per_line( 60 ) {}

	int	buffer_size_needed( int len );
		// Size of the buffer needed.
		// _TAG01 Other

	void hex_dump(	const char *in_buf, int in_buf_len,
					const char *out_buf, int out_buf_len );
	    // Hex dump from `in_buf' and put output into `out_buf'.
		// _TAG01 Other

};

#endif
