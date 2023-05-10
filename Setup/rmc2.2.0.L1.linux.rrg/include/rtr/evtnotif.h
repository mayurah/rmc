//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Dec. 28 1993"
// Version: 1.0

#ifndef _evtnotif_h 
#define _evtnotif_h

#include "rtr/rtrdefs.h"
#include "rtr/ioclient.h"
#include "rtr/timercmd.h"

// Synopsis:
// #include "rtr/rtrnotif.h"
// 
// "//" RTRIOClient& client;
// "//" int fd;
// RTREventNotifierInit::notifier->addReadClient(client, fd);
// RTREventNotifierInit::notifier->dropReadClient(client, fd);
//
// Description:
//	RTREventNotifier is the abstract base class for event managers which
//	provides facilities whereby clients can register to receive I/O events.
//	Timing events are also implemented by RTREventNotifier but are made
//	available to clients by means of the RTRTimerCmd abstraction.
// 
//	The purpose of this class is to allow components to share system resources
//	(IO, timers) in a cooperative way and to do so without being dependent on any
//	particular implementation of a "main loop".
//
//	There is only one instance of RTREventNotifier in an application. The
//	type of this instance depends on the design of the application. The way in
//	which a main loop is started is implementation specific,
//	hence the "main()" of an application is typically  tied to a particular
//	type of notifier.
//
//	Clients of RTREventNotifier need access the "global" notifier. To
//	do this they include the file "rtr/rtrnotif.h" giving access
//	to a static class of type RTREventNotifierInit. This class implements
//	a reference counting scheme which will automatically construct/destruct a
//	notifier as necessary. This is similar to the mechanism used for making
//	cin and cout when accessing iostreams.  Typically, the source file containing
//	main() includes "rtr/rtrnotif.h", meaning that the notifier is always in
//	existence (until program termination).
//
//	Descendants of RTREventNotifier are purpose built for a specific
//	application environment. For example, an implementation intended for X
//	applications uses calls to an underlying X Window library.
//	Components which have no direct dependence on X (i.e. don't need
//	access to X events) use the abstract notifier interface and are insulated
//	from dependencies on X. Components which need X events (perhaps they're
//	X specific) can interface with the X notifier directly.  The same
//	is true for a Windows based notifier. For non-windowing
//	applications, it is probably appropriate to use an event notifier
//	implementation which is a self contained main loop, perhaps using the
//	select() system call to do its job.
//
// See Also:
//	RTRIOClient, RTRTimerCmd, RTREventNotifierInit,
//	RTRSelectNotifier RTRXtEventNotifier, RTRXViewEventNotifier,
//	RTRWindowsNotifier
//

class RTREventNotifier
{
public:

// Destructor
	virtual ~RTREventNotifier() ;
		// _TAG Destructor

// Query
	inline RTRBOOL isReadClient(RTRIOClient& client, int fd) const;
		// Is the given client registered for read events on file descriptor fd?
		// ENSURE Result == (registeredClient(fd) == &client)
		// _TAG01 Query

	inline RTRBOOL isWriteClient(RTRIOClient& client, int fd) const;
		// Is the given client registered for write events on file descriptor 
		// fd?
		// ENSURE Result == (registeredWriteClient(fd) == &client)
		// _TAG01 Query

	inline RTRBOOL isExceptionClient(RTRIOClient& client, int fd) const;
		// Is the given client registered for exception events on 
		// file descriptor fd?
		// ENSURE Result == (registeredExceptionClient(fd) == &client)
		// _TAG01 Query

	inline RTRBOOL hasReadClient(int fd) const;
		// Is any client registered for read events on file descriptor fd?
		// _TAG01 Query

	inline RTRBOOL hasWriteClient(int fd) const;
		// Is any client registered for write events on file descriptor fd?
		// _TAG01 Query

	inline RTRBOOL hasExceptionClient(int fd) const;
		// Is any client registered for exception events on file descriptor fd?
		// _TAG01 Query

// Access
	virtual RTRIOClient* registeredReadClient(int fd) const = 0;
		// The client registered for read events on file descriptor fd?
		// _TAG02 Access

	virtual RTRIOClient* registeredWriteClient(int fd) const = 0;
		// The client registered for write events on file descriptor fd?
		// _TAG02 Access

	virtual RTRIOClient* registeredExceptionClient(int fd) const = 0;
		// The client registered for exception events on file descriptor fd?
		// _TAG02 Access

// Insert
	virtual void addReadClient(RTRIOClient& client, int fd) = 0;
		// Register the given client for read events on file descriptor fd.
		// REQUIRE : !hasReadClient(fd) 
		// ENSURE : hasReadClient(fd) 
		// ENSURE : registeredReadClient(fd) == &client
		// _TAG03 Insert

	virtual void addWriteClient(RTRIOClient& client, int fd) = 0;
		// Register the given client for write events on file descriptor fd.
		// REQUIRE : !hasWriteClient(fd) 
		// ENSURE : hasWriteClient(fd) 
		// ENSURE : registeredWriteClient(fd) == &client
		// _TAG03 Insert

	virtual void addExceptionClient(RTRIOClient& client, int fd) = 0;
		// Register the given client for exception events on file descriptor fd.
		// REQUIRE : !hasExceptionClient(fd) 
		// ENSURE : hasExceptionClient(fd) 
		// ENSURE : registeredExceptionClient(fd) == &client
		// _TAG03 Insert

// Remove
	virtual void dropReadClient(int fd) = 0;
		// De-register the client current registered for read events on 
		// file descriptor fd.
		// ENSURE : !hasReadClient(fd)
		// _TAG04 Remove

	virtual void dropWriteClient(int fd) = 0;
		// De-register the client current registered for write events on 
		// file descriptor fd.
		// ENSURE : !hasWriteClient(fd)
		// _TAG04 Remove

	virtual void dropExceptionClient(int fd) = 0;
		// De-register the client current registered for exception events on 
		// file descriptor fd.
		// ENSURE : !hasExceptionClient(fd)
		// _TAG04 Remove

// Control
	virtual void disable() = 0;
		// Stop dispatching events. NOTE: This causes control to return
		// to the context which "started" the notifier.  Exact behaviour
		// of this is implementation specific. This feature provided as
		// a convenience for simple programs and for debugging. In general
		// components should not "stop" an application. Descendant 
		// implementations should, in general, cease operation when there
		// are not IO clients and no timers pending.
		// _TAG05 Control

// Control - OBSOLETE - left for compatiblity with older versions.
	virtual void enable() = 0;
		// Enable the notifier. Left here for compatibility. The "enable"
		// of a notifier is implementation specific.
		// _TAG06 Control - OBSOLETE

protected:
// Timers
	virtual void addEvent(RTRTimerCmd&) = 0;
		// Add an event (timer command).

	virtual void cancelEvent(RTRTimerCmd&) = 0;
		// Cancel a timer.

// Attributes
	virtual int resolution() = 0;
		// The shortest timer interval used 
		// (i.e. 0 seconds, resolution() milliseconds)

friend class RTRTimerCmd;

};

inline 
RTRBOOL RTREventNotifier::isReadClient(RTRIOClient& client, int fd) const
{
	return registeredReadClient(fd) == &client ? RTRTRUE : RTRFALSE;
}

inline 
RTRBOOL RTREventNotifier::isWriteClient(RTRIOClient& client, int fd) const
{
	return registeredWriteClient(fd) == &client ? RTRTRUE : RTRFALSE;
}

inline 
RTRBOOL RTREventNotifier::isExceptionClient(RTRIOClient& client, int fd) const
{
	return registeredExceptionClient(fd) == &client ? RTRTRUE : RTRFALSE;
}

inline RTRBOOL RTREventNotifier::hasReadClient(int fd) const
{
	return (registeredReadClient(fd)) ? RTRTRUE : RTRFALSE;
}

inline RTRBOOL RTREventNotifier::hasWriteClient(int fd) const
{
	return (registeredWriteClient(fd)) ? RTRTRUE : RTRFALSE;
}

inline RTRBOOL RTREventNotifier::hasExceptionClient(int fd) const
{
	return (registeredExceptionClient(fd)) ? RTRTRUE : RTRFALSE;
}

#endif
