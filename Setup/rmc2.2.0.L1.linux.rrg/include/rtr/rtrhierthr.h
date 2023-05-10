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

#ifndef _rtrhierthr_h
#define _rtrhierthr_h

#include "rtr/rtrflagthr.h"
#include "rtr/lnsrctbl.h"
#include "rtr/rtrmutex.h"

#ifdef RTR_THREAD_CREATE

//
// Synopsis:
// #include "rtr/rtrhierthr.h"
//
// Description:
// A RTRPlatHierThread is a RTRPlatFlagThread that addes the concept of a hierarchy
// of threads for a process. By using this concept of a hierarchy, thread shutdown
// becomes a much easier task. Simply by stopping one thread, you can stop the
// rest of the threads in the hierarchy.
//
// A RTRPlatHierThread may have zero or more children. A RTRPlatHierThread that is
// a root in the hierarchy does not have a parent. All of the RTRPlatHierThread in
// the hierarchy have a parent. Note-You may have mulitiple roots in a process, if
// this is the case then the designed must notify all root on shutdown events.
//
// When a parent thread stops, it will inform all of its children and wait for them
// to stop. A child has to stop when its parent does. However, if a child stops, it
// will inform its parent, it the child is considered a "critical" child, then the
// parent thread will also performs it stop operations.
//
// If a decendant of this class wants to know when a child has stopped, it can
// define the virtual childDead(RTRPlatHierThread&) method. This is called
// whenever a child stops.
//
// If a decendant of this class wants to know when its thread of execution is
// exitting, it can define the virtual threadDead() method. This is called
// right before the thread exits.
//
// See Also:
// RTRPlatThread, RTRPlatFlagThread, RTRPlatCondVar
//
// Inherits:
// RTRPlatFlagThread, RTRPlatThread
//

class RTRPlatHierThread :
	public RTRPlatFlagThread
{
public:

// Constructor
	RTRPlatHierThread(	const char *nm,
						RTRPlatHierThread &parent,
						RTRBOOL crit=RTRFALSE,
						RTRBOOL ackFlagged = RTRFALSE);
		// _TAG Constructor
		// Create a thread with name 'nm' and a parent.
		// Critical 'crit' defines the importance of the
		// child thread. If the child thread is critical,
		// then the parent thread stops if the child thread
		// does.

	RTRPlatHierThread(	const char *nm);
		// Create a ROOT thread.
		// _TAG Constructor

// Destructor
	virtual ~RTRPlatHierThread();
		// _TAG Destructor

// Identity
	inline RTRBOOL isHierRoot()
		// Does this class represent the thread hierarchy root thread?
		// _TAG01 Identity
	{
		return(_thr_parent == 0);
	};

	inline RTRBOOL isParentThread()
		// Is the thread calling this method the same
		// thread as the parent to this class?
		// _TAG01 Identity
	{
		RTPRECONDITION(!isHierRoot());
		RTPRECONDITION(_thr_parent->isAlive());
		return(currentThreadId() == _thr_parent->threadId());
	};

// Attributes
	inline RTRBOOL critical()
		// Is this thread critical to the parent thread?
		// If it is the then the parent will die if the
		// child dies.
		// _TAG02 Attributes
	{
		return(_critical);
	};

	inline RTRBOOL parentFlagged()
		// Has this thread been signalled by its parent?
		// _TAG02 Attributes
	{
		return(_parent_flagged);
	};

	inline RTRBOOL childFlagged()
		// Has this thread been signalled a child?
		// _TAG02 Attributes
	{
		return(_child_flagged);
	};

// Waiting operations
	virtual void waitOnDeath();
		// Blocking wait on information of death
		// of a child or parent.
		// REQUIRE : isThisThread()
		// _TAG03 Waiting operations

// Operations
	void stop();
		// Stop this threads execution.
		// REQUIRE : isThisThread()
		// _TAG04 Operations

	RTRBOOL needToDie();
		// Check to see if we need to die.
		// REQUIRE : isThisThread()
		// _TAG04 Operations

	virtual void childDead(RTRPlatHierThread&);
		// Child has died and thread exited.
		// REQUIRE : isThisThread()
		// _TAG04 Operations

	virtual void threadDead();
		// Local thread ready to exit.
		// REQUIRE : isThisThread()
		// _TAG04 Operations


// Called from other threads to signal this thread
	void flaggedFromParent();
		// Parent is signalling this thread.
	void flaggedFromChild(RTRPlatHierThread&);
		// Child is signalling this thread.
	void killRoot();
		// Root is told to die.


// Debugging
	static void setShutdownDbg();
	static void clearShutdownDbg();

protected:

	rtr_atomic_val		_ack_flagged;
	RTRPlatHierThread	*_thr_parent;
	RTRLinSrchTbl		_children;
	RTRBOOL				_critical;
	RTRBOOL				_parent_flagged;
	RTRBOOL				_child_flagged;
	RTRPlatMutex		_childMutex;

	static RTRBOOL	_thrShutdownDebug;

// Operations
	void addChild(RTRPlatHierThread&);
		// Add a child to the node.

};

#endif

#endif
