//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro,
//                 Zbigniew Minciel - adapted to use epoll & devpoll
//  created:       September 16, 1996
//  version:       1.0

#ifndef _epenimpl_h
#define _epenimpl_h

#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#ifdef sun4_SunOS_5X
#include <sys/devpoll.h>
#else
#include <sys/epoll.h>
#endif
#include <sys/types.h>

#include "rtr/aslist.h"
#include "rtr/dlinkl.h"
#include "rtr/timercmd.h"
#include "rtr/evtnotif.h"
#include "rtr/rtrnotif.h"
#include "rtr/tmintvl.h"
#include "rtr/rtrdefs.h"
#include "rtr/rtstring.h"


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


class RTREvtNotEPollEntry :
	public RTRDLink0	// events pending registration list
{
public:
	RTREvtNotEPollEntry() :
		fd(-1),
		readClient(0),
		writeClient(0),
		exceptClient(0)
	{}

	int	fd;			// valid fd or -1 if not set
	int events;		// current set of user requested events
	RTRIOClient	*readClient;
	RTRIOClient	*writeClient;
	RTRIOClient	*exceptClient;
};

class FDMgr
{
public:
	FDMgr(int maxFd);
	~FDMgr();

	RTREvtNotEPollEntry *add(int fd)
	{
		RTREvtNotEPollEntry *entry;
		if ( fd > _maxFd) resize(fd);
		if ((fd <= _maxFd) && (fd >= 0))
		{
			entry = _fdTable[fd];
			if (!entry)
			{
				entry = new RTREvtNotEPollEntry();
				_fdTable[fd] = entry;
			}
			if (entry)
			{
				entry->fd = fd;
				entry->events = 0;
				entry->readClient = 0;
				entry->writeClient = 0;
				entry->exceptClient = 0;
				_count++;
			}
			return entry;
		}
		else
			return 0;
	}

	RTREvtNotEPollEntry *get(int fd) const
	{
		RTREvtNotEPollEntry *entry;
		if ((fd <= _maxFd) && (fd >= 0))
		{
			entry = _fdTable[fd];
			if (entry && (entry->fd >= 0))
				return entry;
			else
				return 0;
		}
		else
			return 0;
	}

	bool remove(int fd)
	{
		RTREvtNotEPollEntry *entry;
		if ((fd <= _maxFd) && (fd >= 0))
		{
			entry = _fdTable[fd];
			if (entry)
			{
				entry->fd = -1;
				entry->events = 0;
				entry->readClient = 0;
				entry->writeClient = 0;
				entry->exceptClient = 0;

				if (entry->RTRDLink0::isActive())
					_fdPendList.remove(entry);
				_count--;
			}
			return true;
		}
		else
			return false;
	}

	int count() { return _count; }
	int maxFd() { return _maxFd; }

	int resize(int maxFd);

	void addPend(RTREvtNotEPollEntry *entry)
	{
		if (!entry->RTRDLink0::isActive())
			_fdPendList.putLast(entry);
	}

//protected:

	RTREvtNotEPollEntry **_fdTable;
	int _maxFd;		// max FD id
	int _count;		// fd count

	RTRDLinkList<RTREvtNotEPollEntry, RTRDLink0> _fdPendList;
};

class RTREvtEPollNotImpl :
	public RTRTimerCmd,
	public virtual RTREventNotifier
{
public:

// Constructor
	RTREvtEPollNotImpl();
		// _TAG Constructor

// Desctructor
	virtual ~RTREvtEPollNotImpl();
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
	static RTREvtEPollNotImpl* instance;

// State
	bool _error;
	RTRString _errorText;

// IO client management
	FDMgr _fdMgr;
	int _epollfd;
	int _maxFd;		// max FD id
	int _maxOsFd;	// max number of FDs limited be OS

#ifdef sun4_SunOS_5X
	struct pollfd *_epollEvents; // <fds, events> returned by devpoll
	struct pollfd *_pendFDs; // table of <fds,events> to be written to devpoll before DP_POLL
	int _maxPendFDsCnt;
	int _maxPendFDs; // helper var, == _maxPendFDsCnt/2
#else
	struct epoll_event *_epollEvents;
	int _maxPendFDsCnt;
	int _maxPendFDs; // helper var, == _maxPendFDsCnt/2
#endif

	int	_resolution;
	int	_doExtraSigProc;
	int	_doExtraThreadProc;
	int	_doExtraUnsafeProc;
	RTRBOOL	_dataOnLastSelect;

// Timer implementation attributes
	RTRTimeInterval		currentTime;
	RTRTimeInterval		minimumInterval;
	RTRTimeInterval		systemTime;

// Timer list implementation
	RTRDLinkList<RTRTimerCmd,RTRDLinkTC> nullEventList;
	RTRDLinkList<RTRTimerCmd,RTRDLinkTC> hrEventList;
	RTRAscSortList<RTRTimerCmd,RTRDLinkTC> eventList;

// Information
   	struct timeval	_timerExpirationTime;
	RTRBOOL			_enabled;
	char			_sleeping;

// For RTRTimerCmd 
	RTRBOOL				_enableTimer;
	struct timeval		_beginTime;
	struct timeval		_lastTime;
	long				_numTimerEvents;
	long				_numTimerEventsHistogram[13];
	int					_numTimerEventBuckets;
	int					_timerEventsPerSecond;

// Calculate information

// Calculate information
	int getMaxFid();

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

// DevPoll/EPoll notifying
#ifdef sun4_SunOS_5X
	void notifyIO( FDMgr& mgr, struct pollfd *epollEvents,
							int numEpollEvenets);
#else
	void notifyIO( FDMgr& mgr, struct epoll_event *epollEvents,
							int numEpollEvenets);
#endif

#ifdef sun4_SunOS_5X
	int epoll_add_pend(RTREvtNotEPollEntry *entry);
	int epoll_write(int devpollfd, struct pollfd *fdTable, int fdTableCnt);
	int epoll_write_pend();
	bool epoll_check_fd(int devpollfd, int fd, int events);
	int epoll_delete(int epollfd, int fd);
#else
	int epoll_add(RTREvtNotEPollEntry *entry);
	int epoll_remove(RTREvtNotEPollEntry *entry);
	int epoll_delete(int epollfd, int fd);
#endif


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
	RTREvtEPollNotImpl& operator=(const RTREvtEPollNotImpl& rhs);

// Copy constructor ** DON'T DEFINE THIS!
	RTREvtEPollNotImpl(const RTREvtEPollNotImpl& other);

// Friends
friend class RTREventNotifierInit;
};

inline RTRBOOL RTREvtEPollNotImpl::notifying()
{
	return (_notifyingIO || _notifyingTimer );
};

#endif

