//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#include "rtr/timercmd.h"
#include "rtr/pmo.h"

// Synopsis:
//	timedObject.h
//
// Description:
//	A class which activates a timer to trigger an event
// 	at every _poll seconds.
//
// See Also:
//
// Inherits:
//	RTRPublicObject
//	RTRTimerCmd

class TimedObject :
	public RTRPublicObject,
	public RTRTimerCmd
{
public:
	// Constructor
	TimedObject(RTRPublicObject& parent, const char* cname);
	~TimedObject();

protected:
	//Utilities
	void processTimerEvent();
	void update();

	//Data
	int _poll;
	RTRPublicNumeric	_num;	
	RTRPublicLargeNumeric	_lnum;
};
