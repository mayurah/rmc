//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 13 1995"
// Version: 1.0
//
// Author: T. Zhang
// Modified: "Jul. 3 1997"
// Version: 2.0


#ifndef _shmmosvr_h
#define _shmmosvr_h

#include "rtr/timercmd.h"
#include "rtr/memparti.h"
#include "rtr/semaset.h"
#include "rtr/sfevnotf.h"

#ifndef _RDEV_NO_STL_

#else
	#include <stdio.h>
#endif

class RTRMOCloneRequest;
class RTRMOServerReply;
class RTRManagedShmAllocator;
class RTRMOShmemHeader;
class RTRSharedMemoryStats;
class RTRReadWriteLock;
class RTRBinarySemaphore;
class RTRSemaphoreFlag;
class RTRServerSharedMemoryRoot;

// Synopsis:
// #include"rtr/shmmosvr.h"
//
// Description:
//
// 	RTRShmMOServerMemPool is an implementation of the abstract base class
// 	RTRMOServerMemPool which uses shared memory to allocate storage
// 	for managed objects and variables allocated by the application(server).
//
// 	The object structure defined by the application is reproduced in
// 	shared memory and used by clients (instances of RTRShmProxyMgr)
// 	to clone managed objects and variables in the client process.
//
// 	The memory management scheme is pseudo dynamic. Shared memory storage
// 	is allocated dynamically (based on demand from the application) as
// 	storage for either an object or some type of variable. Once allocated for
// 	a particular purpose, it will never be freed for general purpose use,
// 	When storage is freed it is placed on a free list with other storage of
// 	the same type (same size and layout).
//
// 	In general, modification of shared memory must be synchronized with access
// 	with other processes. Allocated objects and variables cannot be attached
// 	to or removed from the existing shared memory layout without acquiring a
// 	lock. For efficiency, allocation is done on demand but attach and remove
// 	operations are done in batches. Allocation does not need to be synchronized
// 	because there is only one reader and writer of the free lists, the server.
// 	Lists of objects and variables which need to attached or removed are
// 	maintained  by the server and serviced at regular intervals. This means
// 	that the server does not have to obtain a semaphore lock every time an
// 	object is allocated or deleted.
//
// 	If no memory (or no memory of the requested type) is available the sever
// 	returns a null pointer to the caller (usually an instance of an object or
// 	variable implementation class). It is assumed that the caller will
// 	detect this and allocate memory from the heap as necessary.
//
// 	The server also detects and processes parameter operations requested
// 	by clients.
//
// 	If a fatal error is encountered during initialization, error() will be
// 	true and text() will contain an explanation of the problem.
//
// See Also:
//	RTRShmProxyMgr, RTRServerPartition, RTRServerSemaphoreSet
//
// Inherits:
//	RTRMOServerMemPool, RTRTimerCmd, RTRMOServerMemPoolClient
//

class RTRShmMOServerMemPool :
	public RTRTimerCmd,
	public RTRThrdSafeControlThread
{ 
public:
// Constructor
	RTRShmMOServerMemPool(
			RTRServerSharedMemoryRoot&, 
			RTRServerSemaphoreSet&,
			int maxClients,
			unsigned long size,
			RTRSafeEventNotifier *notif = RTRSafeEventNotifier::instance
			);
		// _TAG Constructor

// Destructor
	~RTRShmMOServerMemPool();
        	// _TAG Destructor

// State
	inline RTRBOOL error() const;
        	// _TAG01 State

// Attributes
	inline const RTRString& text() const;
		// REQUIRE : error()
      	// _TAG02 Attributes

	inline RTRServerPartition& partition();
      	// _TAG02 Attributes

// Util
	void useStats(RTRSharedMemoryStats*);
		// _TAG03 Util
	inline RTRSharedMemoryStats* stats(){return _stats;};

	void safeActivateTimer();

// Event processing
	void processTimerEvent();
        	// _TAG06 Event processing

	void pollForMessages();
        	// _TAG06 Event processing

		// from RTRThrdSafeControlThread
	virtual RTRBOOL processThrdSafeControlThread();

// Static data
	static int timerSeconds;
		// default 1
	static int timerMilliSeconds;
		// default 0

protected: // Nested class
	class MessageTimer : public RTRTimerCmd
	{
		RTRShmMOServerMemPool& _server;
	public:
		static int timerSeconds;
		static int timerMilliSeconds;
		MessageTimer(RTRShmMOServerMemPool&, RTRSafeEventNotifier *notif);
		virtual ~MessageTimer();
		void processTimerEvent();
	};

protected:
// Data
	RTRBOOL _error;
	RTRString _text;
	RTRServerSharedMemoryRoot& _sharedMemoryRoot;
	RTRServerPartition _partition;

	RTRSharedMemoryStats *_stats;

	RTRManagedShmAllocator* _allocator;
	RTRMOCloneRequest* _requestMsg;
	RTRMOServerReply* _replyMsg;

	RTRReadWriteLock *_moReadWriteLock;
	RTRBinarySemaphore *_transactionSemaphore;
	RTRReadWriteLock *_msgReadWriteLock;
	RTRSemaphoreFlag *_replyFlag;
	MessageTimer _messageTimer;
	RTRSafeEventNotifier *_safe_notifier;
	int _tid; // thread id of shm owner

	friend class RTRSharedMemoryStats;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMOServerMemPool&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
RTRBOOL RTRShmMOServerMemPool::error() const
{
	return _error;
}

inline 
const RTRString& RTRShmMOServerMemPool::text() const
{
	return _text;
}

inline 
RTRServerPartition& RTRShmMOServerMemPool::partition()
{
	return _partition;
}


#endif
