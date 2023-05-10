//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Nov. 10 1998"
// Version: 1.0

#ifndef _rtr_rvenimp_h
#define _rtr_rvenimp_h

#include "rvcpp.h"

#include "rtr/rtrnotif.h"
#include "rtr/enimp.h"

class RvSession;
class RTRRvEventNotifierReadHandler;
class RTRRvEventNotifierWriteHandler;
class RTRRvEventNotifierExceptHandler;

//
// Synopsis:
// #include "rtr/rvenimp.h"
//
// Description:
// 
// See Also:
//
// Inherits:
//

class RTRRVEventNotifier :
	public RTREventNotifierImp,
	public RvTimerCallback
{ 
public:
// Constructor
	RTRRVEventNotifier();
		// _TAG Constructor

// Destructor
	virtual ~RTRRVEventNotifier();
		// _TAG Destructor

// Operations
	static void setSession(RvSession&);

	void enable();

	void disable();

// Rv
	void onTimer(RvTimer*);

protected:
// Utilities
	void enableTimer(long secs, int msecs);
		// Called by RTREventNotifierImp to register for a system timer
		// with the given interval.

	void disableTimer();
		// Called by RTREventNotifierImp to de-register the currently
		// installed system timer.

	void enableReadNotification(int fd);
	void disableReadNotification(int fd);
		// Called by RTREventNotifierImp to enable/disable read notification
		// on the given file descriptor. The method static method 
		// _readIOToEvents() (see above) is passed to X.

	void enableWriteNotification(int fd);
	void disableWriteNotification(int fd);
		// Called by RTREventNotifierImp to enable/disable write notification
		// on the given file descriptor. The method static method 
		// _writeIOToEvents() (see above) is passed to X.

	void enableExceptNotification(int fd);
	void disableExceptNotification(int fd);
		// Called by RTREventNotifierImp to enable/disable exception 
		// notification on the given file descriptor. The method static method 
		// _exceptIOToEvents() (see above) is passed to X.

// Utilities
	void _readIOToEvents(int fd);
	void _writeIOToEvents(int fd);
	void _exceptIOToEvents(int fd);

// Static data
	static RvSession* NotifRVsession;

// Data
	RvTimer* _timer;

// Friends
friend class RTRRvEventNotifierReadHandler;
friend class RTRRvEventNotifierWriteHandler;
friend class RTRRvEventNotifierExceptHandler;

private:
// Don't implement
	RTRRVEventNotifier(const RTRRVEventNotifier&);
	RTRRVEventNotifier& operator=(const RTRRVEventNotifier&);
}; 

class RTRRvEventNotifierReadHandler :
	public RvIOCallback
{
public:
// Constructor
	RTRRvEventNotifierReadHandler(RTRRVEventNotifier&, int fd);
		// _TAG Constructor

// Destructor
	~RTRRvEventNotifierReadHandler();
		// _TAG Destructor

// Operations
	void setIO(RvIO*);
		// _TAG07 Operations

// Event processing -- from RvIOCallback
	virtual void onIO(RvIO* invoker);
		// _TAG08 Event processing -- from RvIOCallback

protected:
// Data
	RvIO *_invoker;
	int _fd;
	RTRRVEventNotifier& _rvNotifier;
		// Data
};

class RTRRvEventNotifierWriteHandler :
	public RvIOCallback
{
public:
// Constructor
	RTRRvEventNotifierWriteHandler(RTRRVEventNotifier&, int fd);
		// _TAG Constructor

// Destructor
	~RTRRvEventNotifierWriteHandler();
		// _TAG Destructor

// Operations
	void setIO(RvIO*);
		// _TAG07 Operations

// Event processing -- from RvIOCallback
	virtual void onIO(RvIO* invoker);
		// _TAG08 Event processing -- from RvIOCallback

protected:
// Data
	RvIO *_invoker;
	int _fd;
	RTRRVEventNotifier& _rvNotifier;
		// Data
};

class RTRRvEventNotifierExceptHandler :
	public RvIOCallback
{
public:
// Constructor
	RTRRvEventNotifierExceptHandler(RTRRVEventNotifier&, int fd);
		// _TAG Constructor

// Destructor
	~RTRRvEventNotifierExceptHandler();
		// _TAG Destructor

// Operations
	void setIO(RvIO*);
		// _TAG07 Operations

// Event processing -- from RvIOCallback
	virtual void onIO(RvIO* invoker);
		// _TAG08 Event processing -- from RvIOCallback

protected:
// Data
	RvIO *_invoker;
	int _fd;
	RTRRVEventNotifier& _rvNotifier;
		// Data
};

#endif
