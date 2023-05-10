//
//|---------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  Author:        Robert Bonaguro
//  Created:       April 29, 1997
//  Version:       1.0
//

#ifndef _rtrflagthr_h
#define _rtrflagthr_h

#include "rtr/rtrthread.h"
#include "rtr/rtrcondvar.h"

#ifdef RTR_THREAD_CREATE

//
// Synopsis:
// #include "rtr/rtrflagthr.h"
//
// Description:
// A RTRPlatFlagThread is a RTRPlatThread that addes the capability of flagging
// a thread of control while performing blocking operations (condition variable
// waits, read, write, select, poll, etc). When you flag the thread the blocking
// operation will return and the flagged() attribute will be set. The actual
// implemention is platform specific:
// Posix/Solairs -
//     The way of forcing these blocking operations out of the call is by
//     sending a signal to that thread. So the user of the class must use
//     operations that return when receiving a signal.
//Modified by G.R 
//     Since the Linux threads behave differently when signals are received
//     when a thread is waiting on a conditional variable, this class keeps
//     a pointer to the conditional variable and signals the conditional 
//     variable when the thread needs to be flagged. This implementation
//     has also been adopted for Solaris
// WindowsNT -
//     The way of forcing these blocking operations out of the call is by
//     sending a flag event to the thread. This means that the user must use
//     "asynchronous" calls and then wait on the notifyEvent() along with
//     the operations event used in the call.
//
//
// See Also:
// RTRPlatThread, RTRPlatHierThread, RTRPlatCondVar
//
// Inherits:
// RTRPlatThread
//

class RTRPlatFlagThread :
	public RTRPlatThread
{
public:

// Constructor
	RTRPlatFlagThread(	const char *nm);
		// _TAG Constructor
		// Create a ROOT thread.

// Destructor
	virtual ~RTRPlatFlagThread();
		// _TAG Destructor

// Attributes

	inline RTRBOOL flagged() const
		// _TAG01 Attributes
		// Has this thread been flagged?
	{
		return(_flagged);
	};

// Operations

	virtual void flagThread();
		// _TAG02 Operations
		// Flag this thread. This operation
		// is used to force a blocking operation
		// out of it execution.

	inline void clearFlagged()
	{
		_flagged=RTRFALSE;
	};

// OS Specific Attributes
#ifdef _WIN32
	inline HANDLE notifyEvent()
		// _TAG03 OS Specific Attributes
	{
		return(_notifyEvent);
	}
#endif

	//The following is specific to Linux and Solaris

	void setCondVarFlag(RTRPlatCondVar *);
	
	void unsetCondVarFlag();

	inline RTRBOOL condVarFlagged() const

	{
	   return(_condVarFlag);
	};

protected:

	RTRBOOL				_flagged;
	RTRPlatCondVar     *_condVarPtr;
	RTRBOOL             _condVarFlag;

	virtual void privateThreadInit();

#if defined(sun4_SunOS_5X) || defined(x86_Linux_2X) || defined(x86_Linux_3X) || defined(x86_Linux_4X)
	static RTRBOOL	_sigInit;
	void initSig();
	static RTR_SIG_HANDLER(signalHandler,sig);
#endif
#ifdef _WIN32
	HANDLE				_notifyEvent;
#endif

};

#endif

#endif
