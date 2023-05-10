//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: M. Schwenk
// Created: "Oct. 13 1994"
// Version: 1.0

#ifndef RTR_SELECT_NOTIFIER
#define RTR_SELECT_NOTIFIER

#ifndef _WIN32
#include <sys/time.h>
#endif
#include <sys/types.h>

#include "rtr/socket.h"
#include "rtr/rtrdefs.h"
#include "rtr/rtrnotif.h"
#include "rtr/enimp.h"
#include "rtr/gettime.h"

// Synopsis:
// #include"rtr/selectni.h"
//
// RTRSelectNotifier::run();
//
// Description:
//	This implementation of RTREventNotifierImp implements a main loop based
//	on the select() system call.
// 
//	RTREventNotifierImp maintains a record of all requested timers, only one
//	of which is outstanding at a given time.
//	When a timer event is requested, RTREventNotifierImp will
//	determine what the next required  timer interval is and invoke enableTimer().
//	This method is implemented here to utilize the select() system call to
//	call-back at the requested interval, unless some I/O event occurs first.
//  
//	RTREventNotifierImp requests I/O notification via calls to
//	enable/disableReadNotification(), etc. These routines are implemented here
//	to use the system select() call to register for I/O events.
// 
// See Also:
//	RTREventNotifier, RTREventNotifierImp,
//	RTRWindowsNotifier, RTRXtNotifier, RTRXViewNotifier
//
// Inherits:
//	RTREventNotifierImp
//

class RTRSelectNotifier : 
	public RTREventNotifierImp
{
public:
// Main Loop
	static void run();
		// _TAG01 Main Loop

// Constructor
	RTRSelectNotifier();
		// _TAG Constructor
	RTRSelectNotifier( long maxWaitInterval, int defRes = defaultResolution );
		// _TAG Constructor
	void init();

// Destructor
	~RTRSelectNotifier();
		// _TAG Destructor

// From RTREventNotifier
	void enable();
		// _TAG02 From RTREventNotifier

	void disable();
		// _TAG02 From RTREventNotifier

// From RTREventNotifierImp
	void enableTimer(long seconds, int milliseconds);
		// Establish a timer for the given time, canceling any previous timer.
		// _TAG03 From RTREventNotifierImp

	void disableTimer();
		// Cancel an installed timer.
        // _TAG03 From RTREventNotifierImp

	void enableReadNotification(int fd);
        // _TAG03 From RTREventNotifierImp

	void disableReadNotification(int fd);
        // _TAG03 From RTREventNotifierImp

	void enableWriteNotification(int fd);
        // _TAG03 From RTREventNotifierImp

	void disableWriteNotification(int fd);
        // _TAG03 From RTREventNotifierImp

	void enableExceptNotification(int fd);
        // _TAG03 From RTREventNotifierImp

	void disableExceptNotification(int fd);
        // _TAG03 From RTREventNotifierImp

	long minWaitIntervalMicroSec;		// the minimum blocking microseconds on select when there is no interested IO happening 
	long maxWaitIntervalMicroSec;		// the maximum blocking microseconds on select when there is no interested IO happening

private:
	fd_set * _readSocketSet;
	fd_set * _writeSocketSet;
	fd_set * _exceptSocketSet;
	fd_set * tmpReadSocketSet;
	fd_set * tmpWriteSocketSet;
	fd_set * tmpExceptSocketSet;
    unsigned int sizeInBytes; // number of bytes in socket sets
	unsigned int FDsetSize;	// min(FD_SETSIZE, maximum number of file descriptors allowed by file system)

	rtr_time_value _timerExpirationTime;

	RTRBOOL _enabled;

	static RTRSelectNotifier* instance;

	void notify(RTRIOEventMgr* mgr, fd_set& set, void (RTRSelectNotifier::*func)(int));
// Friends
friend class RTREventNotifierInit;
};

#endif
