//|-------------------------------------------------------
//|              Copyright (C) 1994 Reuters
//|       1400 Kensington Road, Oak Brook IL  60521
//| All rights rsvd.Duplication & distribution prohibited
//|-------------------------------------------------------
//
// Author: J. Arvanites
// Created:
// Version: 1.0
//
//

#ifndef __RTR_INSTANCE
#define __RTR_INSTANCE

#include "rtr/rtobjid.h"

// Synopsis:
//
// Description:
//
// 	The class RTRInstance is-a RTRObjId that set's itself up
// 	as <hostname>.<instance>.<executable>
// 	This is used in all TRIARCH processes.
//
// See Also:
//

class RTRInstance
	:	public RTRObjId
{
protected:

		// return the location of the filename, and not the path
	char *	trimPath(char* _path);

public:
// Constructor
	RTRInstance( int argc, char **argv );
		// Constructor to pass in the Executable name.
		// _TAG Constructor

	RTRInstance( int argc, char **argv, const char *execName );
		// _TAG Constructor

// Destructor
	~RTRInstance();
		// _TAG Destructor
};
#endif
