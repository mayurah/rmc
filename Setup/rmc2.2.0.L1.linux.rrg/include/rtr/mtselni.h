//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "Feb. 09 1998"
// Version: 1.0

#ifndef _rtr_mtselni_h
#define _rtr_mtselni_h

#ifndef _WIN32
#include <sys/time.h>
#endif
#include <sys/types.h>

#include "rtr/socket.h"
#include "rtr/rtrdefs.h"
#include "rtr/rtrnotif.h"
#include "rtr/evtnotif.h"
#include "rtr/aslist.h"
#include "rtr/dlinkl.h"
#include "rtr/ioevtmgr.h"
#include "rtr/thread.h"
#include "rtr/condvar.h"
#include "rtr/tmintvl.h"


class RTRMTSelectNotifier;

//
// Synopsis:
// #include "rtr/mtselni.h"
//
// Description:
// RTRTimerThread is created by an instance of RTRMTSelectNotifer to manage
// the timer events.
// 
// See Also:
// RTRIOThread, RTRMTSelectNotifier
//
// Inherits:
// RTRThread
//

class RTRTimerThread
	: public RTRThread
{
public:
// Constructor
	RTRTimerThread(RTRMTSelectNotifier& notifier);
		// _TAG Constructor

// Main loop - From RTRThread
	virtual void run();
		// _TAG01 Main loop - From RTRThread

protected:
	RTRMTSelectNotifier& _notifier;
};

//
// Synopsis:
// #include "rtr/mtselni.h"
//
// Description:
// RTRIOThread is created by an instance of RTRMTSelectNotifer to manage
// the IO events.
// 
// See Also:
// RTRTimerThread, RTRMTSelectNotifier
//
// Inherits:
// RTRThread
//

class RTRIOThread
	: public RTRThread
{
public:
// Constructor
	RTRIOThread(RTRMTSelectNotifier& notifier);
		// _TAG Constructor

// Main loop - From RTRThread
	virtual void run();
		// _TAG01 Main loop - From RTRThread

protected:
	struct timeval selectInterval;
	RTRMTSelectNotifier& _notifier;
};


//
// Synopsis:
// #include "rtr/mtselni.h"
//
// Description:
// The implementation of RTREventNotifier implements a main loop based on the
// select() system call as well as thread notification via an instance of 
// RTRConditionVariable. When the run() method is called, one instance of 
// RTRTimerThread and  one instance of RTRIOThread are spawned. While the
// IO thread using select() to watch the file descriptors, the Timer thread
// expire timer eveens in order. The two objects communicate with each other
// via means of RTRConditionVariable. 
// The API for this notifier is MT-safe. It is transparent to user as if it
// were a RTRSelectNotifer.
// 
// See Also:
// RTRSelectNotifer
//
// Inherits:
// RTREventNotifier
//


class RTRMTSelectNotifier : 
	public RTREventNotifier
{
public:
// Constructor
	RTRMTSelectNotifier(int size = 10);
		// _TAG Constructor

// Destructor
	~RTRMTSelectNotifier();
		// _TAG Destructor

// Attributes
	int resolution();
		// _TAG01 Attributes

// State
	RTRBOOL enabled();
		// _TAG02 State

// From RTREventNotifier
	void enable();
		// _TAG03 From RTREventNotifier

	void disable();
		// _TAG03 From RTREventNotifier

// Access
	virtual RTRIOClient* registeredReadClient(int fd) const;
		// The client registered for read events on file descriptor fd?
		// MT-unsafe interface
		// _TAG04 Access

	virtual RTRIOClient* registeredWriteClient(int fd) const;
		// The client registered for write events on file descriptor fd?
		// MT-unsafe interface
		// _TAG04 Access

	virtual RTRIOClient* registeredExceptionClient(int fd) const;
		// The client registered for exception events on file descriptor fd?
		// MT-unsafe interface
		// _TAG04 Access

// Insert
	virtual void addReadClient(RTRIOClient& client, int fd);
		// Register the given client for read events on file descriptor fd.
		// <Synchronized>
		// REQUIRE : !hasReadClient(fd) 
		// ENSURE : hasReadClient(fd) 
		// ENSURE : registeredReadClient(fd) == &client
		// _TAG05 Insert

	virtual void addWriteClient(RTRIOClient& client, int fd);
		// Register the given client for write events on file descriptor fd.
		// <Synchronized>
		// REQUIRE : !hasWriteClient(fd) 
		// ENSURE : hasWriteClient(fd) 
		// ENSURE : registeredWriteClient(fd) == &client
		// _TAG05 Insert

	virtual void addExceptionClient(RTRIOClient& client, int fd);
		// Register the given client for exception events on file descriptor fd.
		// <Synchronized>
		// REQUIRE : !hasExceptionClient(fd) 
		// ENSURE : hasExceptionClient(fd) 
		// ENSURE : registeredExceptionClient(fd) == &client
		// _TAG05 Insert

// Remove
	virtual void dropReadClient(int fd);
		// De-register the client current registered for read events on 
		// file descriptor fd.
		// <Synchronized>
		// ENSURE : !hasReadClient(fd)
		// _TAG06 Remove

	virtual void dropWriteClient(int fd);
		// De-register the client current registered for write events on 
		// file descriptor fd.
		// <Synchronized>
		// ENSURE : !hasWriteClient(fd)
		// _TAG06 Remove

	virtual void dropExceptionClient(int fd);
		// De-register the client current registered for exception events on 
		// file descriptor fd.
		// <Synchronized>
		// ENSURE : !hasExceptionClient(fd)
		// _TAG06 Remove

// Timers - from RTREventNotifier
	void addEvent(RTRTimerCmd&);
		// <Synchronized>
		// _TAG07 Timers - from RTREventNotifie

	void cancelEvent(RTRTimerCmd&);
		// <Synchronized>
		// _TAG07 Timers - from RTREventNotifie

// Main Loop
	static void run();
		// _TAG08 Main Loop

// Static data
	static const int defaultResolution;

	static int maxWaitIntervalSec;
		// the maximum blocking seconds on select when there is no interested 
		// IO happening. This is to ensure that in case other threads register 
		// IO/timer interests, they should get response in a limited time 
		// _TAG09 Static data
		
	static int maxWaitIntervalMicroSec;
		// the maximum blocking microseconds on select when there is no 
		// interested IO happening
		// The actual time should be the sum of the above two 
		// _TAG09 Static data
	
protected:
// Timer implementation methods
	void requestNextCallBack();
	void flushNullTimers();

	RTRBOOL allExpired();

// Implementation
	void expireEvents();

	void notify(fd_set& , fd_set& , fd_set& );

private:
	fd_set _readSocketSet;
	fd_set _writeSocketSet;
	fd_set _exceptSocketSet;
	RTRBOOL _enabled;
	RTRBOOL _notifyingIO;
	RTRIOThread _ioThread;
	RTRTimerThread _timerThread;

	static RTRMTSelectNotifier* instance;

// IO client management
	RTRIOEventMgr *readMgr;
	RTRIOEventMgr *writeMgr;
	RTRIOEventMgr *exceptionMgr;

// Timer implementation attributes
	RTRTimeInterval nextInterval;
	RTRTimeInterval minimumInterval;

	RTRDLinkList<RTRTimerCmd,RTRDLinkTC> nullEventList;
	RTRAscSortList<RTRTimerCmd,RTRDLinkTC> eventList;
	int _resolution;
	RTRTimeInterval systemTime;

// Lock for thread-safety
	RTRConditionVariable _cond;	

// Friends
friend class RTREventNotifierInit;
friend class RTRIOThread;
friend class RTRTimerThread;

};

#endif
