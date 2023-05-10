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
//
//  description:
//


#ifndef __pollthrd_h
#define __pollthrd_h

#include "rtr/socket.h"
#include "rtr/platform.h"
#include "rtr/dlinkl.h"
#include "rtr/rtrhierthr.h"
#include "rtr/rtrcondvar.h"
#include "rtr/envptype.h"

class RTREvtPollNotImpl;

#ifndef _WIN32
#include <sys/poll.h>
#ifdef sun4_SunOS_41X
extern int poll(struct pollfd *,unsigned long,int);
#endif
#endif


class RTREvNotPollThrd :
	public RTRPlatHierThread,
	public RTRDLink0
{
public:

// Constructor
	RTREvNotPollThrd(RTREvtPollNotImpl &notif);

// Destructor
	~RTREvNotPollThrd();

// Parent Thread
	RTRBOOL isParentThread();
		// Is the thread calling this function the
		// parent threads (RTREvtPollNotImpl) indentifier?

// Used to set up entries
	RTRBOOL addEntry(RTREvNotPollEntry& entry);
	void changeEntry(RTREvNotPollEntry& entry);
	void deleteEntry(RTREvNotPollEntry& entry);

// Finished Event
	void eventComplete(RTREvNotPollEntry& entry);

protected:

// Data Members
	RTREvtPollNotImpl&	_notif;
	RTRPlatMutex		_lock;
	int					_numEntries;
	int					_numEventsPending;

	RTRDLinkList<RTREvNotPollEntry,RTRDLink1>		_modifyList;

	RTRPlatCondVar		_pendingEvents;

		// This thread of execution will only modify the following
		// array. The actual entries are modified in the main thread.
	RTREvNotPollEntry	**_entryMap;

#ifdef _WIN32
	WSAEVENT			*_events;		// Array of event handles
	SOCKET				*_sockets;		// Array of socket Ids
	int					_numEvents;		// Size of above two arrays
#else

	int					_pipe[2];
	int					_infoOnPipe:1;

		// Modified by this thread only.
	struct pollfd		*_pollFds;
	int					_pollMaxIdx;

#endif

// Local Member Functions
	void unsafeDropFd(RTREvNotPollEntry& entry);
	void checkChangeList();


// From RTRPlatHierThread
	virtual void runThread();
		// REQUIRE : isThisThread()
		// Main function of the thread.

};

#endif
