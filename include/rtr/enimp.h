//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// EVENT_NOTIFIER_IMP
//
// Author: A. MacGaffey
// Created: "Dec. 28 1993"
// Version: 1.0

#ifndef _enimp_h 
#define _enimp_h

#include "rtr/evtnotif.h"
#include "rtr/aslist.h"
#include "rtr/dlinkl.h"
#include "rtr/rtarray.h"
#include "rtr/ioevtmgr.h"
#include "rtr/tmintvl.h"
#include "rtr/rtrdefs.h"
#include "rtr/lock.h"

//
// Synopsis:
// #include"rtr/enimp.h"
//
// Description:
//	RTREventNotifierImp is an intermediate base class for implementations of
//	the RTREventNotifier abstraction. It implements most of what is required
//	and leaves some specific implementation details for descendants.
// 
//	This class is only relevant to designers of new implementations of
//	RTREventNotifier.
//
//  Note for thread-safety:
//  If an application has multiple threads that share same instance of notifier,
//  then, that notifier must be made MT-safe for its public methods such as 
//  addReadClient() and protected methods add/cancelEvent() which are called by 
//  frient class RTRTimerCmd.
//  The thread-safety for this base class here is only meant to synchronize the 
//  activities of register/unregister the IO and timer events. 
//  It is believed that such kind of multi-thread application hardly make any 
//  sense unless in its non-notifier-threads some meaningful things are being 
//  accomplished while the notifier-thread is processing its call-back 
//  functions, i.e. processIORead() or processTimerCmd(). In this scenario, 
//  the application should take the responsibilities to coordinate the calls 
//  that are happening in these different threads. One practice is that, a 
//  condition-variable is used in the call-back function to signal the 
//  non-notifier-thread and invoke actions there therefore the notifier-thread 
//  could be non-blocking for its events.
//
// See Also:
//	RTRXtEventNotifier, RTRXViewEventNotifier, 
//	RTRWindowsNotifier, RTRSelectNotifier
//
// Inherits:
//	RTREventNotifier
//

class RTREventNotifierImp : 
	public virtual RTREventNotifier
{
public:

// Constructor
	RTREventNotifierImp( int size, int defRes = defaultResolution );
		// _TAG Constructor

// Desctructor
	~RTREventNotifierImp();
		// _TAG Destructor

// Access
	virtual RTRIOClient* registeredReadClient(int fd) const;
		// The client registered for read events on file descriptor fd?
		// MT-unsafe interface
		// _TAG01 Access

	virtual RTRIOClient* registeredWriteClient(int fd) const;
		// The client registered for write events on file descriptor fd?
		// MT-unsafe interface
		// _TAG01 Access

	virtual RTRIOClient* registeredExceptionClient(int fd) const;
		// The client registered for exception events on file descriptor fd?
		// MT-unsafe interface
		// _TAG01 Access

// Insert
	virtual void addReadClient(RTRIOClient& client, int fd);
		// Register the given client for read events on file descriptor fd.
		// <Synchronized>
		// REQUIRE : !hasReadClient(fd) 
		// ENSURE : hasReadClient(fd) 
		// ENSURE : registeredReadClient(fd) == &client
		// _TAG02 Insert

	virtual void addWriteClient(RTRIOClient& client, int fd);
		// Register the given client for write events on file descriptor fd.
		// <Synchronized>
		// REQUIRE : !hasWriteClient(fd) 
		// ENSURE : hasWriteClient(fd) 
		// ENSURE : registeredWriteClient(fd) == &client
		// _TAG02 Insert

	virtual void addExceptionClient(RTRIOClient& client, int fd);
		// Register the given client for exception events on file descriptor fd.
		// <Synchronized>
		// REQUIRE : !hasExceptionClient(fd) 
		// ENSURE : hasExceptionClient(fd) 
		// ENSURE : registeredExceptionClient(fd) == &client
		// _TAG02 Insert

// Remove
	virtual void dropReadClient(int fd);
		// De-register the client current registered for read events on 
		// file descriptor fd.
		// <Synchronized>
		// ENSURE : !hasReadClient(fd)
		// _TAG03 Remove

	virtual void dropWriteClient(int fd);
		// De-register the client current registered for write events on 
		// file descriptor fd.
		// <Synchronized>
		// ENSURE : !hasWriteClient(fd)
		// _TAG03 Remove

	virtual void dropExceptionClient(int fd);
		// De-register the client current registered for exception events on 
		// file descriptor fd.
		// <Synchronized>
		// ENSURE : !hasExceptionClient(fd)
		// _TAG03 Remove

// Implementation
	void notifyReadPending(int fd);
		// Called by descendants when an I/O read event is pending on
		// the given file descriptor. This method will invoke the appropriate
		// method of the RTRIOClient instance which is registered for
		// the given descriptor.
		// _TAG04 Implementation

	void notifyWritePending(int fd);
		// Called by descendants when an I/O write event is pending on
		// the given file descriptor. This method will invoke the appropriate
		// method of the RTRIOClient instance which is registered for
		// the given descriptor.
		// _TAG04 Implementation

	void notifyExceptPending(int fd);
		// Called by descendants when an I/O exception event is pending on
		// the given file descriptor. This method will invoke the appropriate
		// method of the RTRIOClient instance which is registered for
		// the given descriptor.
		// _TAG04 Implementation

	void expireEvents();
		// Called by descendants when the current timer has expired.
		// _TAG04 Implementation

protected:

	RTRBOOL _handleExternalNotification;

	static const int defaultResolution;

// IO client management
	RTRIOEventMgr *readMgr;
	RTRIOEventMgr *writeMgr;
	RTRIOEventMgr *exceptionMgr;

// Timer implementation attributes
	RTRTimeInterval intervalToEvent;
	RTRTimeInterval nextInterval;
	RTRTimeInterval minimumInterval;
	RTRTimeInterval intervalToNextCallBack;
	RTRTimeInterval _installedTimerSystemTime; // system time at which
											  // currently installed timer
											  // will go off.
	RTRDLinkList<RTRTimerCmd,RTRDLinkTC> nullEventList;
	RTRAscSortList<RTRTimerCmd,RTRDLinkTC> eventList;
	int _resolution;
	RTRTimeInterval systemTime;

// Lock for thread-safety
	RTRLockableObj _lock; 	// lock used to synchronize the access of its 
					 		// eventList/nullEventList as well as its three 
							// RTRIOEventMgr instances


// Timers - from RTREventNotifier
	void addEvent(RTRTimerCmd&);
		// <Synchronized>
	void cancelEvent(RTRTimerCmd&);
		// <Synchronized>

// Attributes
	int resolution();

// Timer implementation methods
	void requestNextCallBack();
	void flushNullTimers();
	RTRBOOL eventsDone();
	RTRBOOL allExpired();
	RTRBOOL isTimerInstalled(); 	// Is there a timer installed with the system?

// IO implementation methods
	RTRBOOL isIOClientInstalled(); 	// Are there any IO clients currently installed?

// System specific methods - deferred
	virtual void enableTimer(long secs, int msecs) = 0;
	virtual void disableTimer() = 0;

	virtual void enableReadNotification(int fd) = 0;
	virtual void disableReadNotification(int fd) = 0;

	virtual void enableWriteNotification(int fd) = 0;
	virtual void disableWriteNotification(int fd) = 0;

	virtual void enableExceptNotification(int fd) = 0;
	virtual void disableExceptNotification(int fd) = 0;


// Implementation flags
	RTRBOOL _notifyingTimer;// Will this control thread go back through expireEvents()?
	RTRBOOL _notifyingIO;   // Will this control thread go back through notifyXXXPending()? 
	RTRBOOL notifying();	// This is used to optimize setting timers. As long as
							// this returns RTRFALSE, no timers will be set with 
							// the notifier implementation (Xt, select, etc.). 
							// The assumption is that if the thread of control will
							// go back through this notifier, the requestNextCallBack()
							// method will be called at that time to install the
							// next timer.


private:

// Object Assignment ** DON'T DEFINE THIS!
	RTREventNotifierImp& operator=(const RTREventNotifierImp& rhs);

// Copy constructor ** DON'T DEFINE THIS!
	RTREventNotifierImp(const RTREventNotifierImp& other);

};

inline RTRBOOL RTREventNotifierImp::notifying()
{
	return (_notifyingIO || _notifyingTimer );
};

inline RTRBOOL RTREventNotifierImp::isTimerInstalled()
{
	return _installedTimerSystemTime > 0;
};
#endif
