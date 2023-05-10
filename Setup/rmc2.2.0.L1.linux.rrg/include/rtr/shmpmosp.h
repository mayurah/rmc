//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.27"
// Version:  1.0

#ifndef _rtr_shmpmosp_h
#define _rtr_shmpmosp_h

#include "rtr/pmosp.h"

class RTRClientSharedMemoryRoot;
class RTRShmProxyManagedObjectServer;

// Synopsis:
// #include "rtr/shmpmosp.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedObjectServerPool.
// 
// See Also:
// RTRShmProxyManagedObjectServer
//
// Inherits:
// RTRProxyManagedObjectServerPool
//

class RTRShmProxyManagedObjectServerPool :
	public RTRProxyManagedObjectServerPool
{ 
public:
// Constructor
	RTRShmProxyManagedObjectServerPool(
			const RTRObjectId& context,
			const char *name
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObjectServerPool();
		// _TAG Destructor

// Operations
	RTRShmProxyManagedObjectServer *addServer(
			const char *key,
			int pollInterval=1,
			int handshakeInterval=2
			);
		// Add a server with the shared memory given key to this pool.
		// _TAG07 Operations

	void dropServer(const char *key);
		// Drop the server with the given shared memory key from this pool.
		// _TAG07 Operations

protected:
// Data
	RTRLinkedList<RTRClientSharedMemoryRoot> _sharedMemoryRoots;
	RTRObjectId _instanceId;

private:
// Don't implement
	RTRShmProxyManagedObjectServerPool(const RTRShmProxyManagedObjectServerPool&);
	RTRShmProxyManagedObjectServerPool& operator=(const RTRShmProxyManagedObjectServerPool&);
}; 

#endif /* _rtr_shmpmosp_h */
