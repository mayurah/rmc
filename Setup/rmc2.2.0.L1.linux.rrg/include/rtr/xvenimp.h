//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jul. 07 1994"
// Version: 1.0

#ifndef RTR_XVIEW_NOTIFIER
#define RTR_XVIEW_NOTIFIER

#include "rtr/xenimp.h"
#include <xview/xview.h>

// Synopsis:
// #include"rtr/xvenimp.h"
//
// Frame RTRXViewNotifier::baseFrame = 0;
// 
// main()
// {
//	 Frame base_frame = ...
//	 RTRXViewNotifier::baseFrame = base_frame;
//	 xv_main_loop(base_frame);
// }
//
// Description:
//
// 	An implementation of an RTREventNotifierImp (RTREventNotifier) based on the
// 	XView library. The application must initialize the static class member
// 	appContext. It is of type Frame. The initialition must occur
// 	before any methods of the notifier are invoked by any part of the system.
//
// 	I/O (read, write, exception) events are implemented as in a
// 	straight forward manner in which this class is just translating from the
// 	abstract calls (inherited from RTREventNotifierImp) to the equivalent
// 	underlying XView calls.
//
// 	Because XView uses a signal to implement timer events, this classes needs
// 	to "synchronize" timer events with I/O events (we don't want to be
// 	interrupting ongoing processing of I/O events). The mechanism used to
// 	synchronize timer events involves the use of a pipe. The  pipe is created
// 	by this class (actually by RTRXEventNotifier, an ancestor)
// 	and is both written into and read from by this class.
//
// 	RTREventNotifierImp maintains a record of all requested timers, only one
// 	of which is outstanding at a given time.
// 	When a timer event is requested, RTREventNotifierImp will eventually
// 	decide what the next timer interval is and invoke enableTimer(). This method
// 	is implemented here to register the method _timer_to_io() with X as a timer
// 	handling function. When the timer expires X will invoke _timer_to_io()
// 	which in turn writes a byte into the pipe. This class has registered the
// 	method _io_to_events() for read notification on the "other end" of the
// 	pipe. Once any current I/O processing is completed, _io_to_events() will be
// 	invoked (by X) and will trigger processing of timer events by invoking
// 	RTREventNotifier::expireEvents()
//
// See Also:
//	RTRXtNotifier, RTREventNotifierImp,
//	RTRSelectNotifier, RTRWindowsNotifier
//
// Inherits:
//	RTRXEventNotifier
//

class RTRXViewNotifier :
	public RTRXEventNotifier
{
protected:

// Static member functions for C callbacks
	static void _timer_to_io();
		// This method registered with XView as a timer callback. Writes a 
		// byte into a pipe.

	static void _io_to_events();
		// This method registered with XView to read data from pipe.

	static void _readIOToEvents(void *, int fd);
		// This method registered with XView to receive read events for
		// file descriptors for IO cmd.s registered via 
		// RTREventNotifier::addReadIOCmd()

	static void _writeIOToEvents(void *, int fd);
		// This method registered with XView to receive write events for
		// file descriptors for IO cmd.s registered via 
		// RTREventNotifier::addWriteIOCmd()

	static void _exceptIOToEvents(void *, int fd);
		// This method registered with XView to receive exception events for
		// file descriptors for IO cmd.s registered via 
		// RTREventNotifier::addExceptIOCmd()

// From RTREventNotifierImp
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
		// _readIOToEvents() (see above) is passed to XView.

	void enableWriteNotification(int fd);
	void disableWriteNotification(int fd);
		// Called by RTREventNotifierImp to enable/disable write notification
		// on the given file descriptor. The method static method 
		// _writeIOToEvents() (see above) is passed to XView.

	void enableExceptNotification(int fd);
	void disableExceptNotification(int fd);
		// Called by RTREventNotifierImp to enable/disable exception 
		// notification on the given file descriptor. The method static method 
		// _exceptIOToEvents() (see above) is passed to XView.

public:
// Constructor
	RTRXViewNotifier();
		// _TAG Constructor

// Destructor

	// _TAG Destructor
	virtual ~RTRXViewNotifier() {};

// From RTREventNotifier
	
	// _TAG01 From RTREventNotifier	
	void enable()
	{
		xv_main_loop(baseFrame);
	};
		
	// _TAG01 From RTREventNotifier
	void disable()
	{
		notify_stop();
	};

// Static attributes
	static Frame baseFrame;
		// Base frame (must be initialized by the application).

};

#endif
