//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "May 25 2001"
// Version: 1.0

#ifndef _rtr_tibrvenimp_h
#define _rtr_tibrvenimp_h

#include "tibrv/tibrvcpp.h"

#include "rtr/rtrnotif.h"
#include "rtr/enimp.h"

class TibrvQueue;
class RTRTibrvEventNotifierReadHandler;
class RTRTibrvEventNotifierWriteHandler;
class RTRTibrvEventNotifierExceptHandler;

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

class RTRTibrvEventNotifier :
	public RTREventNotifierImp,
	public TibrvTimerCallback
{ 
public:
// Constructor
	RTRTibrvEventNotifier();
		// _TAG Constructor

// Destructor
	virtual ~RTRTibrvEventNotifier();
		// _TAG Destructor

// Operations
	static void setQueue(TibrvQueue&);
		// _TAG07 Operations

	void enable();
		// _TAG07 Operations

	void disable();
		// _TAG07 Operations

// Event processing
	void onTimer(TibrvTimer*);
		// _TAG08 Event processing -- from TibrvTimerCallback

// Static methods
	static void run();

// Static data
	static tibrv_f64 maxWaitIntervalSec;

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
		// Called by RTREventNotifierImp to enable/disable read
		// notification on the given file descriptor. The method static
		// method _readIOToEvents() (see above) is passed to X.

	void enableWriteNotification(int fd);
	void disableWriteNotification(int fd);
		// Called by RTREventNotifierImp to enable/disable write
		// notification on the given file descriptor. The method static
		// method _writeIOToEvents() (see above) is passed to X.

	void enableExceptNotification(int fd);
	void disableExceptNotification(int fd);
		// Called by RTREventNotifierImp to enable/disable exception 
		// notification on the given file descriptor. The method static
		// method _exceptIOToEvents() (see above) is passed to X.

// Utilities
	void _readIOToEvents(int fd);
	void _writeIOToEvents(int fd);
	void _exceptIOToEvents(int fd);

// Static data
	static TibrvQueue* NotifRVqueue;

// Data
	RTRBOOL _enabled;
	TibrvTimer* _timer;

	static RTRTibrvEventNotifier *instance;

// Friends
friend class RTRTibrvEventNotifierReadHandler;
friend class RTRTibrvEventNotifierWriteHandler;
friend class RTRTibrvEventNotifierExceptHandler;

private:
// Don't implement
	RTRTibrvEventNotifier(const RTRTibrvEventNotifier&);
	RTRTibrvEventNotifier& operator=(const RTRTibrvEventNotifier&);
}; 

class RTRTibrvEventNotifierReadHandler :
	public TibrvIOCallback
{
public:
// Constructor
	RTRTibrvEventNotifierReadHandler(RTRTibrvEventNotifier&, int fd);
		// _TAG Constructor

// Destructor
	~RTRTibrvEventNotifierReadHandler();
		// _TAG Destructor

// Operations
	void setIO(TibrvIOEvent*);
		// _TAG07 Operations

// Event processing -- from RvIOCallback
	virtual void onIOEvent(TibrvIOEvent* invoker);
		// _TAG08 Event processing -- from TibrvIOCallback

protected:
// Data
	TibrvIOEvent *_invoker;
	int _fd;
	RTRTibrvEventNotifier& _rvNotifier;
		// Data
};

class RTRTibrvEventNotifierWriteHandler :
	public TibrvIOCallback
{
public:
// Constructor
	RTRTibrvEventNotifierWriteHandler(RTRTibrvEventNotifier&, int fd);
		// _TAG Constructor

// Destructor
	~RTRTibrvEventNotifierWriteHandler();
		// _TAG Destructor

// Operations
	void setIO(TibrvIOEvent*);
		// _TAG07 Operations

// Event processing -- from TibrvIOCallback
	virtual void onIOEvent(TibrvIOEvent* invoker);
		// _TAG08 Event processing -- from TibrvIOCallback

protected:
// Data
	TibrvIOEvent *_invoker;
	int _fd;
	RTRTibrvEventNotifier& _rvNotifier;
		// Data
};

class RTRTibrvEventNotifierExceptHandler :
	public TibrvIOCallback
{
public:
// Constructor
	RTRTibrvEventNotifierExceptHandler(RTRTibrvEventNotifier&, int fd);
		// _TAG Constructor

// Destructor
	~RTRTibrvEventNotifierExceptHandler();
		// _TAG Destructor

// Operations
	void setIO(TibrvIOEvent*);
		// _TAG07 Operations

// Event processing -- from TibrvIOCallback
	virtual void onIOEvent(TibrvIOEvent* invoker);
		// _TAG08 Event processing -- from TibrvIOCallback

protected:
// Data
	TibrvIOEvent *_invoker;
	int _fd;
	RTRTibrvEventNotifier& _rvNotifier;
		// Data
};

#endif
