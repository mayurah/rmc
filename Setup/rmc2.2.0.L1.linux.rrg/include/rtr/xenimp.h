//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jul. 07 1994"
// Version: 1.0

#ifndef RTR_X_EVENT_NOTIFIER
#define RTR_X_EVENT_NOTIFIER

#include "rtr/rtrnotif.h"
#include "rtr/enimp.h"

// Synopsis:
// #include"rtr/xenimp.h"
//
// Description:
// See Also:
//	RTRXtNotifier, RTRXViewNotifier
//
// Inherits:
//	RTREventNotifierImp
//

class RTRXEventNotifier:
	public RTREventNotifierImp
{

public:

// Constructor
	RTRXEventNotifier(int n);
		// _TAG Constructor

	static RTRXEventNotifier* xNotifier;

	static int fds[2];
		// Array of 2 file descriptors for pipe.

	static int initPipe();
		// _TAG01 Other

	// _TAG01 Other
	static int pipeReadFd()
	{
		return fds[0];
	};
	
	// _TAG01 Other
	static int pipeWriteFd()
	{
		return fds[1];
	};

};

#endif
