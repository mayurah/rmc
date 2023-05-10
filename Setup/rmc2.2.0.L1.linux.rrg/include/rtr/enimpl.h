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
//  created:       September 16, 1996
//  version:       1.0

#ifndef _enimpl_h 
#define _enimpl_h

// Current Solaris, select 2.6 and below, has a hard coded limit
// on 1024 in the system call.
//#ifdef sun4_SunOS_5X
//#define FD_SETSIZE 2048
//#endif

#include <sys/types.h>
#ifndef _WIN32
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#include "rtr/socket.h"
#include "rtr/aslist.h"
#include "rtr/dlinkl.h"
#include "rtr/timercmd.h"
#include "rtr/evtnotif.h"
#include "rtr/rtrnotif.h"
#include "rtr/tmintvl.h"
#include "rtr/lnsrctbl.h"
#include "rtr/rtrdefs.h"


// Synopsis:
//
// Description:
//	This version of the event notifier has been built for performance.
//	It is mainly meant for a daemon process and is not meant to
//	be used in conjunction with other notifiers (X-notifier).
//	The abstractions which would make it easily extensable have
//	been removed for performance reasons.
//
// See Also:
//

class RTREvtNotImpl : 
	public RTRTimerCmd,
	public virtual RTREventNotifier
{
public:

// Constructor
	RTREvtNotImpl();
		// _TAG Constructor

// Desctructor
	virtual ~RTREvtNotImpl();
		// _TAG Destructor

// From RTREventNotifier
// Access
	virtual RTRIOClient* registeredReadClient(int fd) const;
		// The client registered for read events on file descriptor fd?
		// _TAG01 Access

	virtual RTRIOClient* registeredWriteClient(int fd) const;
		// The client registered for write events on file descriptor fd?
		// _TAG01 Access

	virtual RTRIOClient* registeredExceptionClient(int fd) const;
		// The client registered for exception events on file descriptor fd?
		// _TAG01 Access


// Insert
	virtual void addReadClient(RTRIOClient& client, int fd);
		// Register the given client for read events on file descriptor fd.
		// REQUIRE : !hasReadClient(fd) 
		// ENSURE : hasReadClient(fd) 
		// ENSURE : registeredReadClient(fd) == &client
		// _TAG02 Insert

	virtual void addWriteClient(RTRIOClient& client, int fd);
		// Register the given client for write events on file descriptor fd.
		// REQUIRE : !hasWriteClient(fd) 
		// ENSURE : hasWriteClient(fd) 
		// ENSURE : registeredWriteClient(fd) == &client
		// _TAG02 Insert

	virtual void addExceptionClient(RTRIOClient& client, int fd);
		// Register the given client for exception events on file descriptor fd.
		// REQUIRE : !hasExceptionClient(fd) 
		// ENSURE : hasExceptionClient(fd) 
		// ENSURE : registeredExceptionClient(fd) == &client
		// _TAG02 Insert

// Remove
	virtual void dropReadClient(int fd);
		// De-register the client current registered for read events on 
		// file descriptor fd.
		// ENSURE : !hasReadClient(fd)
		// _TAG03 Remove

	virtual void dropWriteClient(int fd);
		// De-register the client current registered for write events on 
		// file descriptor fd.
		// ENSURE : !hasWriteClient(fd)
		// _TAG03 Remove

	virtual void dropExceptionClient(int fd);
		// De-register the client current registered for exception events on 
		// file descriptor fd.
		// ENSURE : !hasExceptionClient(fd)
		// _TAG03 Remove

// Operations
	virtual void enable();
		// _TAG04 From RTREventNotifier

	virtual void disable();
		// _TAG04 From RTREventNotifier

// Testing
	void setEnableTimer(RTRBOOL val);

// Main Loop
	static void run();
		// _TAG05 Main Loop


protected:

// Implementation
	static const int defaultResolution;
	static RTREvtNotImpl* instance;

// IO client management
	RTRLinSrchTbl		readMgr;
	RTRLinSrchTbl		writeMgr;
	RTRLinSrchTbl		exceptionMgr;
	int					_maxReadFd;
	int					_maxWrtFd;
	int					_maxExpFd;
	int					_maxFd;

	int					_resolution;
	int 				_doExtraSigProc;
	int 				_doExtraThreadProc;
	int 				_doExtraUnsafeProc;
	RTRBOOL				_dataOnLastSelect;

// Timer implementation attributes
	RTRTimeInterval		currentTime;
	RTRTimeInterval		minimumInterval;
	RTRTimeInterval		systemTime;

// Timer list implementation
	RTRDLinkList<RTRTimerCmd,RTRDLinkTC> nullEventList;
	RTRDLinkList<RTRTimerCmd,RTRDLinkTC> hrEventList;
	RTRAscSortList<RTRTimerCmd,RTRDLinkTC> eventList;

// Select information
	fd_set				_readSocketSet;
	fd_set				_writeSocketSet;
	fd_set				_exceptSocketSet;
	struct timeval			_timerExpirationTime;
	RTRBOOL				_enabled;
	char				_sleeping;

// For RTRTimerCmd 
	RTRBOOL				_enableTimer;
	struct timeval		_beginTime;
	struct timeval		_lastTime;
	long				_numTimerEvents;
	long				_numTimerEventsHistogram[13];
	int					_numTimerEventBuckets;
	int					_timerEventsPerSecond;

// Calculate information
	int getMaxFid(RTRLinSrchTbl&);

// Timers - from RTREventNotifier
	virtual void addEvent(RTRTimerCmd&);
	virtual void cancelEvent(RTRTimerCmd&);

// Extra Processing
	virtual void extraProc();

// Attributes
	virtual int resolution();

// Timer implementation methods
	void requestNextCallBack();
	void expireEvents(long sec,long milli);

// Select notifying
	void notify(RTRLinSrchTbl&,fd_set&,void (RTRIOClient::*func)(int));

// Implementation flags
	RTRBOOL _notifyingTimer;	// Will this control thread go back through
								// expireEvents()?
	RTRBOOL _notifyingIO;		// Will this control thread go back through
								// notifyXXXPending()? 

	inline RTRBOOL notifying();	// This is used to optimize setting timers.
								// As long as this returns RTRFALSE, no timers
								// will be set with the notifier implementation
								// (Xt, select, etc.). The assumption is that
								// if the thread of control will go back
								// through this notifier, the
								// requestNextCallBack() method will be called
								// at that time to install the next timer.

// From RTRTimerCmd
	virtual void processTimerEvent();


private:

// Object Assignment ** DON'T DEFINE THIS!
	RTREvtNotImpl& operator=(const RTREvtNotImpl& rhs);

// Copy constructor ** DON'T DEFINE THIS!
	RTREvtNotImpl(const RTREvtNotImpl& other);

// Friends
friend class RTREventNotifierInit;
};

inline RTRBOOL RTREvtNotImpl::notifying()
{
	return (_notifyingIO || _notifyingTimer );
};

#endif

