//|---------------------------------------------------------------------------
//|                        Copyright (c) 2001 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "2001.06.25"
// Version: 1.0

#ifndef _rtr_shmpmod_h
#define _rtr_shmpmod_h

#include "rtr/prxymos.h"
#include "rtr/cshrdmem.h"
#include "rtr/timercmd.h"
#include "rtr/moshmhdr.h"
#include "rtr/memphdr.h"
#include "rtr/modimpl.h"
#include "rtr/dir.h"
#include "rtr/eventgen.h"

#include "rtr/shmpmoh.h"
#include "rtr/shmpmodc.h"
#include "rtr/shmpmodi.h"

class RTRClientPartition;
class RTRReadWriteLock;
class RTRBinarySemaphore;
class RTRSemaphoreFlag;
class RTRMOCloneRequest;
class RTRMOServerReply;

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

class RTRShmProxyManagedObjectDirectory :
	public RTRTimerCmd,
	public RTREventGenerator<RTRShmProxyManagedObjectDirectory, RTRShmProxyManagedObjDirClient>,
	public RTRDirectory<RTRShmProxyManagedObjectHandle>
{ 
public:
// Constructor
	RTRShmProxyManagedObjectDirectory(
			RTRClientSharedMemoryRoot& shm,
			RTRObjectId& context,
			const char *name,
			int pollInterval = 1
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObjectDirectory();
		// _TAG Destructor

// State
	inline RTRBOOL error() const;
		// _TAG03 State

	inline const RTRString& text() const;
		// _TAG03 State

// Access -- Random
	RTRProxyManagedObjectPtr object(
			const RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			);
		// The object with the given handle.
		// _TAG06 Access -- Random


	RTRShmProxyManagedObjDirRootIterator rootIterator();

	RTRBOOL setParameter(
			const RTRObjectId& contextId,
			const char *name,
			const char *value,
			RTRString *returnText = 0
			);

protected:
	inline RTRMOShmemHeader *header() const;
	RTRProxyManagedObjectHandle *rootHandleById(const RTRObjectId&) const;

// Operations
	void addHandle(RTRShmProxyManagedObjectHandle& pmoh);
	void removeHandle(RTRShmProxyManagedObjectHandle& pmoh);
	void init(RTRClientSharedMemoryRoot& shm);
	void update();
	void checkForAddedHandles();
	void checkForRemovedHandles();
	void updateRootHandles();

// Event Processing -- from RTRTimerCmd
	void processTimerEvent();

	void indicateError();
	void indicateHandleAdded(RTRShmProxyManagedObjectHandle&);
	void indicateHandleRemoved(RTRShmProxyManagedObjectHandle&);
	void notifyError(RTRShmProxyManagedObjDirClient&);
	void notifyHandleAdded(RTRShmProxyManagedObjDirClient&);
	void notifyHandleRemoved(RTRShmProxyManagedObjDirClient&);

// Data
	RTRObjectId _instanceId;
	RTRBOOL _error;
	RTRString _text;
	RTRClientPartition *_partition;
	RTRMOShmemHeader *_header;
	RTRMODirImpl *_dirImpl;				// 2000
	RTRReadWriteLock *_moReadWriteLock;
	RTRBinarySemaphore *_transactionSemaphore;
	RTRReadWriteLock *_msgReadWriteLock;
	RTRSemaphoreFlag *_replyFlag;
	RTRMOCloneRequest *_requestMsg;			// 2000
	RTRMOServerReply *_replyMsg;
	unsigned long _numberOfAdds;
	unsigned long _numberOfRemoves;
	unsigned long _pollInterval;
	RTRDLinkList<RTRShmProxyManagedObjectHandle, RTRDLink1> _rootHandles;

	RTRShmProxyManagedObjectHandle *_tmpHandle;

// Friends
	friend class RTRShmProxyManagedObject;
	friend class RTRShmProxyManagedObjectHandle;
	friend class RTRShmProxyManagedObjDirRootIterator;

private:
// Don't implement
	RTRShmProxyManagedObjectDirectory(const RTRShmProxyManagedObjectDirectory&);
	RTRShmProxyManagedObjectDirectory& operator=(const RTRShmProxyManagedObjectDirectory&);
}; 

inline
RTRBOOL RTRShmProxyManagedObjectDirectory::error() const
{
	return _error;
}

inline
const RTRString& RTRShmProxyManagedObjectDirectory::text() const
{
	return _text;
}

inline RTRMOShmemHeader *RTRShmProxyManagedObjectDirectory::header() const
{
	return _header;
}

#endif /* _rtr_shmpmos_h */
