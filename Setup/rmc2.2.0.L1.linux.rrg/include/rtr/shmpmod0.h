//|---------------------------------------------------------------------------
//|                        Copyright (c) 2001 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "2001.06.25"
// Version: 1.0

#ifndef _rtr_shmpmod0_h
#define _rtr_shmpmod0_h

#include "rtr/prxymos.h"
#include "rtr/cshrdmem.h"
#include "rtr/timercmd.h"
#include "rtr/moshmhdr.h"
#include "rtr/memphdr.h"
#include "rtr/modimpl.h"
#include "rtr/dir.h"
#include "rtr/eventgen.h"

#include "rtr/shmpmoh0.h"
#include "rtr/shmpmodc0.h"

class RTRClientPartition_Eli;
class RTRReadWriteLock;
class RTRBinarySemaphore;
class RTRSemaphoreFlag;
class RTRMOCloneRequest;
class RTRMOServerReply;
class RTRParameterSetResult_EliF21;
class RTRParameterSetResult;
class RTRShmProxyManagedObjDirRootIterator_EliF21;
class RTRShmProxyManagedObjDirRootIterator_Mdk10;

// Synopsis:
// #include "rtr/shmpmos.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedObjectServer.
//
// See Also:
// RTRProxyManagedObjectServerClient
//
// Inherits:
// RTRProxyManagedObjectServer, RTRSharedMemoryClient, RTRTimerCmd
//

class RTRShmProxyManagedObjectDirectory_EliF21 :
	public RTRTimerCmd,
	public RTREventGenerator<RTRShmProxyManagedObjectDirectory_EliF21, RTRShmProxyManagedObjDirClient_EliF21>,
	public RTRDirectory<RTRShmProxyManagedObjectHandle_EliF21>
{ 
public:
// Constructor
	RTRShmProxyManagedObjectDirectory_EliF21(
			RTRClientSharedMemoryRoot& shm,
			RTRObjectId& context,
			const char *name,
			int pollInterval = 1
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObjectDirectory_EliF21();
		// _TAG Destructor

// State
	inline RTRBOOL error() const;
		// _TAG03 State

	inline const RTRString& text() const;
		// _TAG03 State

	inline const char *base() const;

// Access -- Random
	RTRProxyManagedObjectPtr object(
			const RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			);
		// The object with the given handle.
		// _TAG06 Access -- Random


	RTRShmProxyManagedObjDirRootIterator_EliF21 rootIterator();

	RTRBOOL setParameter(
			const RTRObjectId& contextId,
			const char *name,
			const char *value,
			RTRString *returnText = 0
			);

protected:
// Access
	RTRProxyManagedObjectHandle *rootHandleById(const RTRObjectId&) const;

// Operations
	void addHandle(RTRShmProxyManagedObjectHandle_EliF21& pmoh);
	void removeHandle(RTRShmProxyManagedObjectHandle_EliF21& pmoh);
	void init(RTRClientSharedMemoryRoot& shm);
	void update();
	void checkForAddedHandles();
	void checkForRemovedHandles();
	void updateRootHandles();

// Event Processing -- from RTRTimerCmd
	void processTimerEvent();

	void indicateError();
	void indicateHandleAdded(RTRShmProxyManagedObjectHandle_EliF21&);
	void indicateHandleRemoved(RTRShmProxyManagedObjectHandle_EliF21&);
	void notifyError(RTRShmProxyManagedObjDirClient_EliF21&);
	void notifyHandleAdded(RTRShmProxyManagedObjDirClient_EliF21&);
	void notifyHandleRemoved(RTRShmProxyManagedObjDirClient_EliF21&);

// Data
	RTRObjectId _instanceId;
	RTRBOOL _error;
	RTRString _text;
	RTRClientPartition_Eli *_partition;
	RTRMOMemPoolHeader_EliF21 *_header;
	RTRReadWriteLock *_moReadWriteLock;
	RTRBinarySemaphore *_transactionSemaphore;
	RTRReadWriteLock *_msgReadWriteLock;
	RTRSemaphoreFlag *_replyFlag;
	RTRParameterSetResult_EliF21 *_replyMsg;
	unsigned long _numberOfAdds;
	unsigned long _numberOfRemoves;
	unsigned long _pollInterval;
	RTRDLinkList<RTRShmProxyManagedObjectHandle_EliF21, RTRDLink1> _rootHandles;

	RTRShmProxyManagedObjectHandle_EliF21 *_tmpHandle;

// Friends
	friend class RTRShmProxyManagedObjectHandle_EliF21;
	friend class RTRShmProxyManagedObjDirRootIterator_EliF21;

private:
// Don't implement
	RTRShmProxyManagedObjectDirectory_EliF21(const RTRShmProxyManagedObjectDirectory_EliF21&);
	RTRShmProxyManagedObjectDirectory_EliF21& operator=(const RTRShmProxyManagedObjectDirectory_EliF21&);
}; 

inline
RTRBOOL RTRShmProxyManagedObjectDirectory_EliF21::error() const
{
	return _error;
}

inline
const RTRString& RTRShmProxyManagedObjectDirectory_EliF21::text() const
{
	return _text;
}

/*
inline RTRMOMemPoolHeader_EliF21 *RTRShmProxyManagedObjectDirectory_EliF21::header() const
{
	return _header;
}
*/

inline
const char *RTRShmProxyManagedObjectDirectory_EliF21::base() const
{
	return _partition->baseAddress();
}


class RTRShmProxyManagedObjectDirectory_Mdk10 :
	public RTRTimerCmd,
	public RTREventGenerator<RTRShmProxyManagedObjectDirectory_Mdk10, RTRShmProxyManagedObjDirClient_Mdk10>,
	public RTRDirectory<RTRShmProxyManagedObjectHandle_Mdk10>
{ 
public:
// Constructor
	RTRShmProxyManagedObjectDirectory_Mdk10(
			RTRClientSharedMemoryRoot& shm,
			RTRObjectId& context,
			const char *name,
			int pollInterval = 1
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObjectDirectory_Mdk10();
		// _TAG Destructor

// State
	inline RTRBOOL error() const;
		// _TAG03 State

	inline const RTRString& text() const;
		// _TAG03 State

	inline const char *base() const;

// Access -- Random
	RTRProxyManagedObjectPtr object(
			const RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			);
		// The object with the given handle.
		// _TAG06 Access -- Random


	RTRShmProxyManagedObjDirRootIterator_Mdk10 rootIterator();

	RTRBOOL setParameter(
			const RTRObjectId& contextId,
			const char *name,
			const char *value,
			RTRString *returnText = 0
			);

protected:
// Access
	RTRProxyManagedObjectHandle *rootHandleById(const RTRObjectId&) const;

// Operations
	void addHandle(RTRShmProxyManagedObjectHandle_Mdk10& pmoh);
	void removeHandle(RTRShmProxyManagedObjectHandle_Mdk10& pmoh);
	void init(RTRClientSharedMemoryRoot& shm);
	void update();
	void checkForAddedHandles();
	void checkForRemovedHandles();
	void updateRootHandles();

// Event Processing -- from RTRTimerCmd
	void processTimerEvent();

	void indicateError();
	void indicateHandleAdded(RTRShmProxyManagedObjectHandle_Mdk10&);
	void indicateHandleRemoved(RTRShmProxyManagedObjectHandle_Mdk10&);
	void notifyError(RTRShmProxyManagedObjDirClient_Mdk10&);
	void notifyHandleAdded(RTRShmProxyManagedObjDirClient_Mdk10&);
	void notifyHandleRemoved(RTRShmProxyManagedObjDirClient_Mdk10&);

// Data
	RTRObjectId _instanceId;
	RTRBOOL _error;
	RTRString _text;
	RTRClientPartition_Eli *_partition;
	RTRMOMemPoolHeader *_header;
	RTRReadWriteLock *_moReadWriteLock;
	RTRBinarySemaphore *_transactionSemaphore;
	RTRReadWriteLock *_msgReadWriteLock;
	RTRSemaphoreFlag *_replyFlag;
	RTRParameterSetResult_EliF21 *_replyMsg;
	unsigned long _numberOfAdds;
	unsigned long _numberOfRemoves;
	unsigned long _pollInterval;
	RTRDLinkList<RTRShmProxyManagedObjectHandle_Mdk10, RTRDLink1> _rootHandles;

	RTRShmProxyManagedObjectHandle_Mdk10 *_tmpHandle;

// Friends
	friend class RTRShmProxyManagedObjectHandle_Mdk10;
	friend class RTRShmProxyManagedObjDirRootIterator_Mdk10;

private:
// Don't implement
	RTRShmProxyManagedObjectDirectory_Mdk10(const RTRShmProxyManagedObjectDirectory_Mdk10&);
	RTRShmProxyManagedObjectDirectory_Mdk10& operator=(const RTRShmProxyManagedObjectDirectory_Mdk10&);
}; 

inline
RTRBOOL RTRShmProxyManagedObjectDirectory_Mdk10::error() const
{
	return _error;
}

inline
const RTRString& RTRShmProxyManagedObjectDirectory_Mdk10::text() const
{
	return _text;
}

/*
inline RTRMOMemPoolHeader *RTRShmProxyManagedObjectDirectory_Mdk10::header() const
{
	return _header;
}
*/

inline
const char *RTRShmProxyManagedObjectDirectory_Mdk10::base() const
{
	return _partition->baseAddress();
}

#endif /* _rtr_shmpmod0_h */

