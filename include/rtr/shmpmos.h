//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.21"
// Version: 1.0

#ifndef _rtr_shmpmos_h
#define _rtr_shmpmos_h

#include "rtr/prxymos.h"	// RTRProxyManagedObjectServer
#include "rtr/cshrdmem.h"
#include "rtr/shmpmodc.h"	// RTRShmProxyManagedObjDirClient
#include "rtr/shmpmodc0.h"	// RTRShmProxyManagedObjDirClient_EliF21

class RTRShmProxyManagedObjectDirectory;
class RTRShmProxyManagedObjectDirectory_EliF21;
class RTRShmProxyManagedObjectDirectory_Mdk10;

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

class RTRShmProxyManagedObjectServer :
	public RTRProxyManagedObjectServer,
	public RTRSharedMemoryClient,
	public RTRShmProxyManagedObjDirClient,
	public RTRShmProxyManagedObjDirClient_EliF21,
	public RTRShmProxyManagedObjDirClient_Mdk10
{ 
public:
// Constructor
	RTRShmProxyManagedObjectServer(
			RTRClientSharedMemoryRoot& shm,
			RTRObjectId& context,
			const char *name,
			int pollInterval = 1
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObjectServer();
		// _TAG Destructor

// Attributes
	inline RTRShmProxyManagedObjectDirectory* directory() const;
		// _TAG02 Attributes

	inline RTRShmProxyManagedObjectDirectory_EliF21* directoryEli() const;
		// _TAG02 Attributes

	inline RTRShmProxyManagedObjectDirectory_Mdk10* directoryMdk() const;
		// _TAG02 Attributes

	inline const RTRClientSharedMemoryRoot& sharedMemoryRoot() const;
		// The shared memory root monitored by this server.
		// _TAG02 Attributes

// Access -- Random
	virtual RTRProxyManagedObjectPtr object(
			const RTRProxyManagedObjectHandle&
			);
		// The object with the given handle.
		// _TAG06 Access -- Random

// Operations
	RTRBOOL setParameter(
			const RTRObjectId& contextId,
			const char *name,
			const char *value,
			RTRString *returnText = 0
			);
		// _TAG07 Operations

	RTRBOOL setParameter(
			const RTRObjectId& contextId,
			const char *name,
			long value,
			RTRString *returnText = 0
			);
		// _TAG07 Operations

protected:
	void enable(int shmVersion);
	void disable();

// Operations -- from RTRProxyManagedObjectServer
	void cleanUp();
	RTRProxyManagedObject *newObject(
			const RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			) const;

// Event Processing -- from RTRSharedMemoryClient
	void processClientError(RTRClientSharedMemoryRoot&);
	void processServerUp(RTRClientSharedMemoryRoot&);
	void processServerExit(RTRClientSharedMemoryRoot&);
	void processServerInactive(RTRClientSharedMemoryRoot&);
	void processServerRestart(RTRClientSharedMemoryRoot&);

// Event processing -- from RTRShmProxyManagedObjDirClient
	virtual void processProxyManagedObjDirError(
			const RTRShmProxyManagedObjectDirectory& dir );
	virtual void processProxyManagedObjDirHandleAdded(
			const RTRShmProxyManagedObjectDirectory& dir,
			const RTRShmProxyManagedObjectHandle& pmoh );
	virtual void processProxyManagedObjDirHandleRemoved(
			const RTRShmProxyManagedObjectDirectory& dir,
			const RTRShmProxyManagedObjectHandle& pmoh );

// Event processing -- from RTRShmProxyManagedObjDirClient_EliF21
	virtual void processProxyManagedObjDirEliF21Error(
			const RTRShmProxyManagedObjectDirectory_EliF21& dir );
	virtual void processProxyManagedObjDirEliF21HandleAdded(
			const RTRShmProxyManagedObjectDirectory_EliF21& dir,
			const RTRShmProxyManagedObjectHandle_EliF21& pmoh );
	virtual void processProxyManagedObjDirEliF21HandleRemoved(
			const RTRShmProxyManagedObjectDirectory_EliF21& dir,
			const RTRShmProxyManagedObjectHandle_EliF21& pmoh );

// Event processing -- from RTRShmProxyManagedObjDirClient_Mdk10
	virtual void processProxyManagedObjDirMdk10Error(
			const RTRShmProxyManagedObjectDirectory_Mdk10& dir );
	virtual void processProxyManagedObjDirMdk10HandleAdded(
			const RTRShmProxyManagedObjectDirectory_Mdk10& dir,
			const RTRShmProxyManagedObjectHandle_Mdk10& pmoh );
	virtual void processProxyManagedObjDirMdk10HandleRemoved(
			const RTRShmProxyManagedObjectDirectory_Mdk10& dir,
			const RTRShmProxyManagedObjectHandle_Mdk10& pmoh );

// Data
	RTRObjectId _instanceId;
	RTRClientSharedMemoryRoot& _sharedMemoryRoot;
	int _moVersion;
	int _pollInterval;
	RTRShmProxyManagedObjectDirectory *_directory;
	RTRShmProxyManagedObjectDirectory_EliF21 *_directoryEli;
	RTRShmProxyManagedObjectDirectory_Mdk10 *_directoryMdk;

private:
// Don't implement
	RTRShmProxyManagedObjectServer(const RTRShmProxyManagedObjectServer&);
	RTRShmProxyManagedObjectServer& operator=(const RTRShmProxyManagedObjectServer&);
}; 

inline
RTRShmProxyManagedObjectDirectory* RTRShmProxyManagedObjectServer::directory() const
{
	return _directory;
}

inline
RTRShmProxyManagedObjectDirectory_EliF21* RTRShmProxyManagedObjectServer::directoryEli() const
{
	return _directoryEli;
}

inline
RTRShmProxyManagedObjectDirectory_Mdk10* RTRShmProxyManagedObjectServer::directoryMdk() const
{
	return _directoryMdk;
}

inline const RTRClientSharedMemoryRoot& 
RTRShmProxyManagedObjectServer::sharedMemoryRoot() const
{
	return _sharedMemoryRoot;
}

#endif /* _rtr_shmpmos_h */
