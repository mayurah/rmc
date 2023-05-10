//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 07 1995"
// Version: 1.0

#ifndef _shprxmgr_h
#define _shprxmgr_h

#include "rtr/rtllist.h"
#include "rtr/cshrdmem.h"
#include "rtr/timercmd.h"
#include "rtr/shmprxo.h"
#include "rtr/shmprxv.h"
#include "rtr/memphdr.h"

class RTRMODescrDictionary;
class RTRParameterSetResult;
class RTRClientPartition_Eli;

// Synopsis:
// #include"rtr/shprxmgr.h"
//
// Description:
// 	An instance of RTRShmProxyMgr monitors a shared memory partition which
// 	contains managed object data provided by a server (of type
// 	RTRShmMOServerMemPool). The proxy manager allocates and deallocates
// 	proxy root objects as necessary, cloning the server object structure within
// 	the local process. Proxy objects create other objects in turn and also
// 	allocate variables as necessary. Proxy objects have the same class and
// 	instance identifiers as the original objects. Proxy variables have the
// 	same name and type as the original variables.
//
//	Changes in the object structure (additions/deletions) are detected
//	efficiently by means of transaction levels which are polled at an interval
//	specified by the public static data member pollInterval.
// 
//	NOTE: There may be more than one instance of RTRShmProxyMgr within an
//	application, each instance monitoring a different segment of shared memory.
//
// See Also:
//	RTRClientSharedMemoryRoot, RTRShmMOServerMemPool, RTRManagedObject
//
// Inherits:
//	RTRTimerCmd
//

class RTRShmProxyMgr :
	public RTRTimerCmd
{
public:
// Constructor
	RTRShmProxyMgr(
			const RTRObjectId& iid,
			RTRClientSharedMemoryRoot&, 
			const char *prefix = ""
			);
		// A new proxy managed object manager using the given client partition.
		// If deadEnabled and shared memory server is/becomes not active then 
		// proxy managed objects will be created/marked dead.
		// ** Prefix is for debugging and not normally relevant
		// (avoids duplicate instance id.s when working in one process)
		// _TAG Constructor

// Destructor
	~RTRShmProxyMgr();
		// _TAG Destructor

// Identity
	inline const RTRObjectId& instanceId() const;
		// _TAG01 Identity

// Attributes
	const RTRString& text() const;
		// The explanation for error
		// REQUIRE : error()
		// _TAG02 Attributes

	inline const RTRClientSharedMemoryRoot& sharedMemoryRoot() const;
		// The shared memory being used by this manager.
		// _TAG02 Attributes

	inline RTRClientPartition_Eli *memoryPartition();
		// The memory partition being used by this manager.
		// _TAG02 Attributes

	inline int shmoVersion();
		// The version of the managed objects on server side 
		// _TAG02 Attributes

// State
	RTRBOOL error() const;
		// Is this proxy mgr. in an error state?
		// _TAG03 State

// Access
	RTRProxyObject *proxyByName(const char *) const;
		// REQUIRE shmoVersion() == 30
		// The proxy root object, if any, with the given name.
		// _TAG04 Access

	RTRProxyObject_EliF14 *proxyByName_14(const char *) const;
		// REQUIRE shmoVersion() == 14
		// The proxy root object, if any, with the given name.
		// _TAG04 Access

	RTRProxyObject_EliF21 *proxyByName_21(const char *) const;
		// REQUIRE shmoVersion() == 21
		// The proxy root object, if any, with the given name.
		// _TAG04 Access

// Query
	RTRBOOL hasProxy(const char *) const;
		// Is this proxy manager maintaining a proxy root with the
		// given name?
		// _TAG05 Query

// Event processing - RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG06 Event processing - RTRTimerCmd

// Operations -- used by proxy parameters
	RTRParameterSetResult& setParameter(
			const RTRObjectId&,	// Id of containing object
			const char *,		// name of variable
			const char* 		// value as string
			);
		// _TAG08 Operations - used by proxy parameters

	RTRParameterSetResult& setParameter(
			const RTRObjectId&,	// Id of containing object
			const char *,		// name of variable
			long			// value of numeric var
			);
		// _TAG08 Operations - used by proxy parameters

	void addToWatchList(RTRProxyVariable& );
		// _TAG08 Operations - used by proxy parameters

	void dropFromWatchList(RTRProxyVariable& );
		// _TAG08 Operations - used by proxy parameters


// Static data
	static int pollInterval;
		// The interval at which the shared memory segment is polled for
		// changes. Defaults to 1 (second).

protected:
// Operations
	void init();
	void cleanUp();
	void update();
		// calls update_14(), update_21() or update_30() accordingly
	void update_14();
	void update_21();
	void update_30();
	void markRootsDead(const char*);

// Data
	RTRObjectId _instanceId;
	RTRBOOL _debugEnabled;
	RTRBOOL _error;
	RTRString _text;
	RTRClientSharedMemoryRoot& _sharedMemoryRoot;
	RTRClientPartition_Eli *_partition;

	int _moVersion;
	union {
		RTRMOMemPoolHeader* _header;
		RTRMOMemPoolHeader_EliF14 *_header14;
		RTRMOMemPoolHeader_EliF21 *_header21;
	};
	union {
		RTRLinkedList<RTRProxyObject> * _proxyRoots;
		RTRLinkedList<RTRProxyObject_EliF14> * _proxyRoots14;
		RTRLinkedList<RTRProxyObject_EliF21> * _proxyRoots21;
	};

	RTRObjectId _prefix;
	int _numberOfAdds;
	int _numberOfRemoves;
#ifdef _WIN32
	RTRReadWriteLock_Eli *_moReadWriteLock0;
	RTRReadWriteLock_Eli *_msgReadWriteLock0;
	RTRBinarySemaphore_Eli *_transactionSemaphore0;
	RTRReadWriteLock *_moReadWriteLock;
	RTRReadWriteLock *_msgReadWriteLock;
	RTRBinarySemaphore *_transactionSemaphore;
#else
	RTRReadWriteLock *_moReadWriteLock;
	RTRReadWriteLock *_msgReadWriteLock;
	RTRBinarySemaphore *_transactionSemaphore;
#endif
	RTRSemaphoreFlag *_replyFlag;
	RTRDLinkList<RTRProxyVariable, RTRDLink2> _varWatchList;

// Friends
friend class RTRShmClientMgr;
};

inline 
const RTRObjectId& RTRShmProxyMgr::instanceId() const
{
	return _instanceId;
}

inline 
const RTRClientSharedMemoryRoot& RTRShmProxyMgr::sharedMemoryRoot() const
{
	return _sharedMemoryRoot;
}
	
inline 
RTRClientPartition_Eli *RTRShmProxyMgr::memoryPartition()
{
	return _partition;
}

#endif
