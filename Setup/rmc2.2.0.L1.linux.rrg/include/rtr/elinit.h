//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Nov. 23 1998"
// Version: 1.0

#ifndef _rtr_elinit_h
#define _rtr_elinit_h

//
// Synopsis:
// #include "rtr/elinit.h"
//
// RTREventLoopInit loop;
// loop.run();
//
// Description:
// Used to protect applications from having to access static defined in DLLs.
// The implementation of run is provided in the DLL which implements the
// global main loop of choice (some implementation of RTREventNotifier).
// 
// See Also:
// RTREventNotifier
//
// Inherits:
//

class RTREventLoopInit
{ 
public:
	RTREventLoopInit();

// Operations
	void run();
		// Run the event loop. N.B. may block depending on implementation.
		// _TAG07 Operations

private:
// Don't implement
	RTREventLoopInit(const RTREventLoopInit&);
	RTREventLoopInit& operator=(const RTREventLoopInit&);
}; 

#endif
