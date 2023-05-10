//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "Oct. 07 1997"
// Version: 2.0

#ifndef _shclnmgr_h
#define _shclnmgr_h

#include "rtr/timercmd.h"
#include "rtr/cshrdmem.h"
#include "rtr/objid.h"
#include "rtr/memparti.h"
#include "rtr/clnmgr.h"

class RTRMOShmemHeader;
class RTRMOServerReply;
class RTRMOCloneRequest;
class RTRReadWriteLock;
class RTRBinarySemaphore;
class RTRSemaphoreFlag;

// Synopsis:
// #include"rtr/shclnmgr.h"
//
// Description:
// 	An instance of RTRShmCloneMgr monitors a shared memory partition which
// 	contains managed object data provided by a server (of type
// 	RTRShmMOServerMemPool). The clone manager allocates and deallocates
// 	clone root objects as necessary, cloning the server object structure within
// 	the local process. Clone objects create other objects in turn and also
// 	allocate variables as necessary. Clone objects have the same class and
// 	instance identifiers as the original objects. Clone variables have the
// 	same name and type as the original variables.
//
//	Changes in the object structure (additions/deletions) are detected
//	efficiently by means of transaction levels which are polled at an interval
//	specified by the public static data member pollInterval.
// 
//	NOTE: There may be more than one instance of RTRShmCloneMgr within an
//	application, each instance monitoring a different segment of shared memory.
//
// See Also:
//	RTRClientSharedMemoryRoot, RTRShmMOServerMemPool, RTRManagedObject
//
// Inherits:
//	RTRTimerCmd
//

class RTRShmCloneMgr :
	public RTRMemCloneMgr,
	public RTRTimerCmd
{
public:
// Constructor
	RTRShmCloneMgr(
			const RTRObjectId& iid,
			RTRClientSharedMemoryRoot&, 
			RTRBOOL readOnly = RTRFALSE,
			const char *prefix = ""
			);
		// A new clone managed object manager using the given client partition.
		// If deadEnabled and shared memory server is/becomes not active then 
		// clone managed objects will be created/marked dead.
		// ** Prefix is for debugging and not normally relevant
		// (avoids duplicate instance id.s when working in one process)
		// _TAG Constructor

// Destructor
	~RTRShmCloneMgr();
		// _TAG Destructor

// Attributes
	inline const RTRClientSharedMemoryRoot& sharedMemoryRoot() const;
		// The shared memory being used by this manager.
		// _TAG02 Attributes

	inline RTRClientPartition *memoryPartition();
		// The memory partition being used by this manager.
		// _TAG02 Attributes

// Event processing - RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG06 Event processing - RTRTimerCmd

// Operations -- used by clone parameters
	virtual RTRBOOL	setParameter(
			const RTRObjectId&,	// Id of containing object
			const char *,		// name of variable
			const char*, 		// value as string
			RTRString* = 0		// return txt, storage provided by caller
			);
		// _TAG08 Operations - used by clone parameters

	virtual RTRBOOL setParameter(
			const RTRObjectId&,	// Id of containing object
			const char *,		// name of variable
			long,			// value of numeric var
			RTRString* = 0      // return txt, storage provided by caller
			);
		// _TAG08 Operations - used by clone parameters

// Static data
	static int pollInterval;
		// The interval at which the shared memory segment is polled for
		// changes. Defaults to 1 (second).

protected:
// Operations
	void init();
	void cleanUp();
	void update();
	void markRootsDead(const char*);

// Data
	RTRObjectId _prefix;
	RTRBOOL _debugEnabled;
	RTRClientSharedMemoryRoot& _sharedMemoryRoot;
	RTRClientPartition *_partition;

	RTRMOShmemHeader* _header;
	RTRReadWriteLock *_moReadWriteLock;
	RTRBinarySemaphore *_transactionSemaphore;
	RTRReadWriteLock *_msgReadWriteLock;
	RTRSemaphoreFlag *_replyFlag;

	RTRBOOL _readOnly;

// Friends
	friend class RTRShmClientMgr;
};

inline 
const RTRClientSharedMemoryRoot& RTRShmCloneMgr::sharedMemoryRoot() const
{
	return _sharedMemoryRoot;
}
	
inline 
RTRClientPartition *RTRShmCloneMgr::memoryPartition()
{
	return _partition;
}

#endif
