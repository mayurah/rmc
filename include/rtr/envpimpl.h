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
//  version:       1.0

#ifndef __envpimpl_h 
#define __envpimpl_h 

#include "rtr/dlinkl.h"
#include "rtr/ldlinkl.h"
#include "rtr/timercmd.h"
#include "rtr/sfevnotf.h"
#include "rtr/rtrnotif.h"
#include "rtr/tmintvl.h"
#include "rtr/lnsrctbl.h"
#include "rtr/rtrdefs.h"
#include "rtr/rtrcondvar.h"
#include "rtr/rtrhierthr.h"
#include "rtr/pollthrd.h"
#include "rtr/envptype.h"
#include "rtr/timerthrd.h"


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



class RTREvtPollNotImpl : 
	public RTRSafeEventNotifier,
	public RTRPlatHierThread
{
public:

// Constructor
	RTREvtPollNotImpl(bool singleton = true);
		// _TAG Constructor

// Desctructor
	virtual ~RTREvtPollNotImpl();
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

// Timers - from RTREventNotifier
		virtual void addEvent(RTRTimerCmd&);
		virtual void cancelEvent(RTRTimerCmd&);

/////////////////////////
// Thread Safe Operations
// Thread Query
	virtual RTRBOOL hasThrdSafeControlThread(RTRThrdSafeControlThread& client);
	virtual RTRBOOL unsafeHasThrdSafeControlThread(RTRThrdSafeControlThread& client) const;

// Thread Insert
	virtual void addThrdSafeControlThread(RTRThrdSafeControlThread& client);
	virtual void unsafeAddThrdSafeControlThread(RTRThrdSafeControlThread& client);

// Thread Removal
	virtual void dropThrdSafeControlThread(RTRThrdSafeControlThread& client);
	virtual void unsafeDropThrdSafeControlThread(RTRThrdSafeControlThread& client);

// Locking/Unlocking
	virtual void lockThrdSafeControlThread();
	virtual void unlockThrdSafeControlThread();


/////////////////////////
// Signal Safe Operations
// Signal Query
	virtual RTRBOOL hasSigSafeControlThread(RTRSigSafeControlThread& client) const;
	virtual RTRBOOL unsafeHasSigSafeControlThread(RTRSigSafeControlThread& client) const;

// Signal Insert
	virtual void addSigSafeControlThread(RTRSigSafeControlThread& client);
	virtual void unsafeAddSigSafeControlThread(RTRSigSafeControlThread& client);

// Signal Remove
	virtual void dropSigSafeControlThread(RTRSigSafeControlThread& client);
	virtual void unsafeDropSigSafeControlThread(RTRSigSafeControlThread& client);


/////////////////////////
// Unsafe Control Operations
// Unsafe Control Query
	virtual RTRBOOL hasUnsafeControlThread(RTRUnsafeControlThread& client) const;

// Unsafe Control Insert
	virtual void addUnsafeControlThread(RTRUnsafeControlThread& client, int priority);

// Unsafe Control Removal
	virtual void dropUnsafeControlThread(RTRUnsafeControlThread& client);


// Operations
	virtual void enable();
		// _TAG04 From RTREventNotifier

	virtual void disable();
		// _TAG04 From RTREventNotifier

// Main Loop
	static void run();
		// _TAG05 Main Loop


	inline void addIntEvent(RTREvtNotImplEvent& event)
	{
		_eventCondVar.lock();
		if (!event.RTRDLink0::isActive())
		{
			_eventList.putLast(&event);
			_eventCondVar.signal();
		}
		_eventCondVar.unlock();
	};

	inline void removeIntEvent(RTREvtNotImplEvent& event)
	{
		_eventCondVar.lock();
		if (event.RTRDLink0::isActive())
		{
			_eventList.remove(&event);
		}
		_eventCondVar.unlock();
	};

	inline void unsafeRemoveIntEvent(RTREvtNotImplEvent& event)
	{
		_eventList.remove(&event);
	};

	static RTREvtPollNotImpl* instance;
protected:

// Implementation
	static const int defaultResolution;

// Select information
	RTRBOOL				_enabled;
	int					_resolution;
	int					_doExtraProc;

// Poll Threads management
	RTRDLinkList<RTREvNotPollThrd,RTRDLink0>	_pollThreads;

// IO client management
	RTRLinSrchTbl		*_fdMgr;
	int					_fdMask;

	RTRDLinkList<RTREvtNotImplEvent,RTRDLink0>	_eventList;
	RTRPlatCondVar								_eventCondVar;
	RTRDLinkList<RTRTimerCmd,RTRDLinkTC>		_timerList;
	RTRDLinkList<RTREvNotThreadEntry,RTRDLink0>	_freeThreadList;

	RTRDLinkList<RTREvNotTimerEntry,RTRDLink1>	_freeTimers;


	RTRLiteDLinkList<RTRUnsafeControlThread,RTRDLink7> _controlList;
	RTRLiteDLinkList<RTRSigSafeControlThread,RTRDLink8> _sigControlList;

	RTRUnsafeControlThread *_current,*_next;
	RTRSigSafeControlThread *_sigCurrent,*_sigNext;
	int _controlThreadsPerInvocation;

	int					_curFd;

	RTREvNotTimerThrd	_timerThread;
	RTRTimeInterval		minimumInterval;


// Extra Processing
	virtual void extraProc();

// Attributes
	virtual int resolution();

// Local Member Functions
	void addToPollThread(RTREvNotPollEntry& entry);

	void processEventList();
		// REQUIRE : isThisThread()

// From RTRPlatHierThread
	virtual void runThread();
		// REQUIRE : isThisThread()
		// Main function of the thread.


private:

// Object Assignment ** DON'T DEFINE THIS!
	RTREvtPollNotImpl& operator=(const RTREvtPollNotImpl& rhs);

// Copy constructor ** DON'T DEFINE THIS!
	RTREvtPollNotImpl(const RTREvtPollNotImpl& other);

};


#endif

