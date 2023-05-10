//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Aug. 22 1995"
// Version: 1.0

#ifndef _triadmin_h
#define _triadmin_h

#include "rtr/objid.h"
#include "rtr/rtstring.h"
#include "rtr/sfevnotf.h"

class RTRServerSharedMemoryRoot;
class RTRShmMOServerMemPool;
class RTRSharedMemoryStats;
class RTRShmConfigMgmtActionCntrl;

// Synopsis:
// #include"rtr/triadmin.h"
//
// Description:
// A base class for Triarch process admin classes. A utility class which
// sets up the shared memory distribution of managed objects and variables.
//
// This class cannot be instantiated directly.
//
// See Also:
// RTRServerSharedMemoryRoot, RTRShmMOServerMemPool, RTRSharedMemoryStats
// RTRShmConfigMgmtActionCntrl
//
// Inherits:
//

class RTRTriarchProcessAdmin
{ 
public:
// Destructor
	virtual ~RTRTriarchProcessAdmin();
		// _TAG Destructor

// State
	inline RTRBOOL error() const;
		// _TAG01 State

// Attributes
	inline const RTRString& text() const;
		// _TAG02 Attributes

	inline RTRServerSharedMemoryRoot *sharedMemory() const;
		// The shared memory partition.
		// _TAG02 Attributes

	inline RTRShmMOServerMemPool *managedObjectServer() const;
		// The server in charge of populating shared memory with 
		// managed objects and variables.
		// _TAG02 Attributes

	inline RTRSharedMemoryStats *memoryStats() const;
		// Variables showing shared memory usage.
		// _TAG02 Attributes

	inline RTRShmConfigMgmtActionCntrl *memoryLogAction() const;
		// Log action which records mgmt events in shared memory.
		// _TAG02 Attributes

// Static data
	static RTRString defaultSharedMemorySize;
	static RTRString defaultMaxClients;
	static RTRString defaultMaxSemaphores;
	static RTRString defaultEnableMemoryStats;
	static RTRString defaultEnableMemoryLogging;
		// Static data 

protected:
// Constructor
	RTRTriarchProcessAdmin(
		const RTRObjectId& classId, 	// Descendant class 
		const RTRObjectId& contextId,	// Descendant instance
		const char *name = "",		// Instance name for admin
		RTRSafeEventNotifier *notif = RTRSafeEventNotifier::instance,
		const char* sharedMemoryKey = NULL,
		const char* semaphoreKey = NULL
		);

// Data
	RTRBOOL _error;
	RTRString _text;
	RTRServerSharedMemoryRoot *_sharedMemory;
	RTRShmMOServerMemPool *_managedObjectServer;
	RTRSharedMemoryStats *_memoryStats;
	RTRShmConfigMgmtActionCntrl *_memoryLogAction;

private:
		// Do not define
	RTRTriarchProcessAdmin(const RTRTriarchProcessAdmin&);
	RTRTriarchProcessAdmin& operator=(const RTRTriarchProcessAdmin&);
}; 

inline 
RTRBOOL RTRTriarchProcessAdmin::error() const
{
	return _error;
}

inline 
const RTRString& RTRTriarchProcessAdmin::text() const
{
	return _text;
}

inline 
RTRServerSharedMemoryRoot *RTRTriarchProcessAdmin::sharedMemory() const
{
	return _sharedMemory;
}

inline 
RTRShmMOServerMemPool *RTRTriarchProcessAdmin::managedObjectServer() const
{
	return _managedObjectServer;
}

inline 
RTRSharedMemoryStats *RTRTriarchProcessAdmin::memoryStats() const
{
	return _memoryStats;
}

inline
RTRShmConfigMgmtActionCntrl *RTRTriarchProcessAdmin::memoryLogAction() const
{
	return _memoryLogAction;
}

#endif
