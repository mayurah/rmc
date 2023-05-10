//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 07 1995"
// Version: 1.0
//
// Modified: "Jul. 24 1997"
// Author: 	T. Zhang
// Version: 2.0

#ifndef _shrdmem_h
#define _shrdmem_h

#include <sys/types.h>

#include "rtr/semaset.h"
#include "rtr/semlock.h"
#include "rtr/rtstring.h"
#include "rtr/timercmd.h"
#include "rtr/objid.h"
#include "rtr/portipc.h"
#include "rtr/sfevnotf.h"

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

class RTRSharedMemoryHdr;
class RTRSharedMemoryPartitionIterator;

// Synopsis:
// #include"rtr/shrdmem.h"
//
// Description:
// The encapsulation of the server side of a server/client shared memory
// relationship. An instance of RTRServerSharedMemoryRoot is constructed
// with a key and will then attempt to allocate the shared memory using
// with that key. If memory already exists with that key then the memory
// server will examine that memory to determine whether or not it can
// safely be reinitialized. If the memory header matches that which the
// server would create (version, size etc) and the memory appears to no
// longer be in use, then the server will re-initialize the existing memory.
// If the memory could be used but has not yet timed-out (based on data
// extracting from the existing memory) then the server will periodically
// retry the allocation process.
//
// Once memory has been successfully allocated or re-initialized then the
// server will implement a handshaking scheme with any clients which attach
// to the memory segment.
//
// Options:
//
// By setting the public static data member "fixedAddress" prior to
// construction the mapping of the shared memory into the process address
// space can be controlled. It is up to the caller to ensure that the given
// address is appropriate.
//
// See Also: 
//	RTRSharedMemoryHdr, RTRServerSemaphoreSet
//
// Inherits:
//	RTRTimerCmd
//

class RTRServerSharedMemoryRoot :
	public RTRTimerCmd
{ 
public:
// Constructor
	RTRServerSharedMemoryRoot(
			const RTRObjectId& context,	// id context
			const char *name,		// id name
			const RTRString& mk, 		// memory key
			const RTRString& sk, 		// semaphore key
			int s, 				// number of semaphores
			unsigned int long, 		// user bytes required
			int m,				// max clients
			RTRSafeEventNotifier *notif = RTRSafeEventNotifier::instance
			);
		// Allocate sh. mem so that s bytes are available for use.
		// _TAG Constructor

// Destructor
	~RTRServerSharedMemoryRoot();
		// _TAG Destructor

// Identity
	inline const RTRObjectId& instanceId() const;
		// _TAG01 Identity

// Attibutes
	inline const RTRString& text() const;
		// Text explaning the state of this shared memory root.
		// _TAG02 Attributes

	RTRString& key();
		// Key of this memory segment.
		// _TAG02 Attributes

	inline HANDLE id() const;
		// The id assigned by the system to this memory allocation.
		// REQUIRE : !error()
		// _TAG02 Attributes

	inline RTRSharedMemoryHdr *header() const;
		// The header overlaid on the memory segment.
		// _TAG02 Attributes

	inline RTRServerSemaphoreSet *semaphoreSet() const;
		// The set of semaphores associated with this segment.
		// _TAG02 Attributes

// State
	virtual RTRBOOL error() const;
		// Is this segment in an error state?
		// _TAG03 State

// Access
	RTRSharedMemoryPartitionIterator partitionIterator() const;
		// _TAG04 Access

// Event processing
	void processTimerEvent();
		// _TAG05 Event processing

// Static data
	static int heartbeatInterval;
		// The interval at which client handshaking will occurr.
		
	static char *fixedAddress;
		// Defaults to 0, meaning that system will assign the mapping
		// address for you. Modify this prior to construction to control
		// the mapping yourself.

protected:
// Data
	RTRString _key;
	pid_t _pid;			// Saved for periodic sanity checking
	HANDLE _id;
	RTRObjectId _instanceId;
	RTRString _text;
	RTRReadWriteLock *_lock;
	RTRSharedMemoryHdr *_header;
	RTRServerSemaphoreSet *_semaphoreSet;
	const char *_data;

// Operations
	void attach();
		// Attach to shared memory.

// Friends
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&,
									const RTRServerSharedMemoryRoot&);
#else
public:
	void print(FILE*);
#endif
		// Friends
};

inline 
const RTRObjectId& RTRServerSharedMemoryRoot::instanceId() const
{
	return _instanceId;
}

inline 
const RTRString& RTRServerSharedMemoryRoot::text() const
{
	return _text;
}

inline 
HANDLE RTRServerSharedMemoryRoot::id() const 
{ 
	RTPRECONDITION ( !error() );
	return _id; 
}

inline 
RTRSharedMemoryHdr *RTRServerSharedMemoryRoot::header() const
{
	return _header;
}

inline 
RTRServerSemaphoreSet *RTRServerSharedMemoryRoot::semaphoreSet() const
{
	return _semaphoreSet;
}

#endif
