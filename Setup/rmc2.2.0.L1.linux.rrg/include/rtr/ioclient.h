//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 25 1995"
// Version: 1.0

#ifndef _ioclient_h
#define _ioclient_h

// Synopsis:
// #include "rtr/rtrnotif.h"
// 
// "//" Abstract base class
//
// Description:
//	The abstract base class for application components that wish to register
//	with an RTREventNotifier in order to receive I/O events.
// 
//	Descendants should redefine the event processing functions as
//	appropriate.
//
// See Also:
//	RTREventNotifier
//

class RTRIOClient
{
public:
// Event Handling
	virtual void processIORead(int);
		// Data is available for reading on the device associated with 
		// the given file descriptor.
		// _TAG01 Event Handling 

	virtual void processIOWrite(int);
		// The device associated with given file descriptor is ready for
		// writing.
		// _TAG01 Event Handling 

	virtual void processIOException(int);
		// There has been an exception related to the device associated with 
		// the given file descriptor.
		// _TAG01 Event Handling 

};

#endif
