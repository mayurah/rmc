//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  version:       1.0
//
//  description:
//


#ifndef __timerthrd_h
#define __timerthrd_h

#include "rtr/platform.h"
#include "rtr/envptype.h"
#include "rtr/aslist.h"
#include "rtr/dlinkl.h"
#include "rtr/rtrhierthr.h"
#include "rtr/rtrcondvar.h"
class RTREvtPollNotImpl;



class RTREvNotTimerThrd :
	public RTRPlatHierThread
{
public:

// Constructor
	RTREvNotTimerThrd(RTREvtPollNotImpl &notif);
		// _TAG Constructor

// Destructor
	~RTREvNotTimerThrd();
		// _TAG Destructor

// Operations
	void addEvent(RTREvNotTimerEntry & newT);
		// _TAG02 Operations
		// REQUIRE : !isThisThread()
		// Add a timing event to the timer list.

	void removeEvent(RTREvNotTimerEntry & timer);
		// _TAG02 Operations
		// Add a timing event to the timer list.

protected:

// Data Members
	RTRAscSortList<RTREvNotTimerEntry,RTRDLink1>	_eventList;
		// The sorted list of when timer events need
		// to expire. We need to have a temporary
		// object store the actual RTRTimerCmd because
		// of the threads.

	RTRPlatCondVar		_condVar;

	RTREvtPollNotImpl&	_notif;

// Expire timer events.
	void expireEvents();
		// REQUIRE : isThisThread()
		// Expire any timing events that need to go off.
		// They are put into the event list in RTREvtPollNotImpl
		// to notify the timer clients in the notifier thread
		// of control.


// From RTRPlatHierThread
	virtual void runThread();
		// REQUIRE : isThisThread()
		// Main function of the thread.

};

#endif
