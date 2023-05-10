//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jul. 25 1996"
// Version: 1.0

#ifndef _rtr_dummyml_h
#define _rtr_dummyml_h

#include "rtr/rtrnotif.h"
#include "rtr/enimp.h"

//
// Synopsis:
//
// Description:
//
// RTRDummyMainLoop is a dummy class which satisfies a linker when creating
// dummy executables (e.g. those used for template instantiation)
// 
// See Also:
//

class RTRDummyMainLoop : 
	public RTREventNotifierImp
{ 
public:
// Constructor
	RTRDummyMainLoop();
		// _TAG Constructor

// Destructor
	virtual ~RTRDummyMainLoop();
		// _TAG Destructor

// From RTREventNotifier
	void enable();
		// _TAG01 From RTREventNotifier

	void disable();
		// _TAG01 From RTREventNotifier

protected:
// From RTREventNotifierImp
	void enableTimer(long, int);
	void disableTimer();
	void enableReadNotification(int);
	void disableReadNotification(int);
	void enableWriteNotification(int);
	void disableWriteNotification(int);
	void enableExceptNotification(int);
	void disableExceptNotification(int);
}; 

#endif // _rtr_dummyml_h
