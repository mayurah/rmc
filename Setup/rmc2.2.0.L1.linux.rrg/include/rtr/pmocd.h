//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 23 1997"
// Version: 1.0

#ifndef _rtr_pmocd_h
#define _rtr_pmocd_h

#include "rtr/pmosp.h"
#include "rtr/pmospc.h"
#include "rtr/mtgc.h"
#include "rtr/lock.h"

class RTRProxyManagedObjectClassDirectoryClient;

//
// Synopsis:
// #include "rtr/proxymos.h"
//
// Description:
// RTRProxyManagedObjectClassDirectory is a directory of all object 
// handles for all managed objects of a particular type as published 
// by a pool of RTRProxyManagedObjectServer. The handles can be used 
// to retrieve instances of RTRProxyManagedObject from a 
// RTRProxyManagedObjectServer. The pool of servers which contribute to 
// a directory is specified when the directory is constructed.
// The directory will dynamically adjust its contents according to changes
// in the server pool and changes in the set of objects published by the
// servers.
//
// Application components which want to monitor events associated with one
// or more instances of RTRProxyManagedObjectClassDirectory must be 
// descendants of RTRProxyManagedObjectClassDirectoryClient.
// 
// See Also:
// RTRProxyManagedObjectClassDirectoryClient
//
// Inherits:
// RTRProxyManagedObjectServerPoolClient, RTRMTGCObj, RTRLockableObj
//

class RTRProxyManagedObjectClassDirectory :
	public RTRProxyManagedObjectServerPoolClient,
	public RTRLockableObj,
	public RTRMTGCObj
{ 
public:
// Constructor
	RTRProxyManagedObjectClassDirectory(
			RTRProxyManagedObjectServerPool& pool,
			const RTRObjectId& filter
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedObjectClassDirectory();
		// _TAG Destructor

// Attributes
	inline const RTRObjectId& classFilter() const;
		// _TAG01 Attributes

	inline const RTRProxyManagedObjectServerPool& serverPool() const;
		// _TAG01 Attributes

// Query
	RTRBOOL hasHandle(const RTRObjectId&) const;
		// Does this directory contain a handle which has the
		// given instance identifiers?
		// _TAG02 Query

	RTRBOOL hasHandle(const RTRProxyManagedObjectHandle&) const;
		// Does this directory contain the given handle ?
		// _TAG02 Query

// Access -- random
	const RTRProxyManagedObjectHandle* handle(const RTRObjectId& iid) const;
		// The handle, if any, which has the given instance identifier.
		// ENSURE: (result == null) == hasHandle(iid)
		// _TAG03 Access -- random

// Access -- sequential
	RTRProxyManagedObjectHandleIterator handles() const;
		// An iterator providing sequential access to the handles in
		// this directory.
		// _TAG04 Access -- sequential

// Event processing -- from RTRProxyManagedObjectServerPoolClient
	virtual void processProxyManagedObjectServerAdded(
			RTRProxyManagedObjectServerPool&,
			RTRProxyManagedObjectServer&
			);
		// The given server has been added to the pool.
		// _TAG05 Event processing -- from RTRProxyManagedObjectServerPoolClient

// Event client management
	RTRBOOL hasClient(const RTRProxyManagedObjectClassDirectoryClient&) const;
		// Is the given client registered to receive update events
		// from this directory.
		// _TAG06 Event client management

	void addClient(const RTRProxyManagedObjectClassDirectoryClient& client);
		// Register the given client to receive update events from
		// this directory.
		// REQUIRE: !hasClient(client)
		// REQUIRE: hasClient(client)
		// _TAG06 Event client management

	void dropClient(const RTRProxyManagedObjectClassDirectoryClient& client);
		// Un-register the given client to receive update events from
		// this directory.
		// ENSURE: !hasClient(client)
		// _TAG06 Event client management

protected:
// Utilities
	void putHandle(
			RTRProxyManagedObjectServer&, 
			RTRProxyManagedObjectHandle& nod
			);
		// REQUIRE: nod.classId().isDescendant(classFilter())
		// REQUIRE: !hasHandle(nod.instanceId())
		// ENSURE: hasHandle(nod.instanceId())

	void removeHandle(
			RTRProxyManagedObjectServer&,
			RTRProxyManagedObjectHandle& nod
			);
		// ENSURE: !hasHandle(nod.instanceId())

// Operations
	virtual void serverAdded(
			RTRProxyManagedObjectServer&
			) = 0;

// Utilties -- event propagation
	void indicateHandleAdded(
			RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			);
	void indicateHandleRemoved(
			RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			);

	void notifyHandleAdded(
			RTRProxyManagedObjectClassDirectoryClient*,
			RTRProxyManagedObjectClassDirectory*
			);
	void notifyHandleRemoved(
			RTRProxyManagedObjectClassDirectoryClient*,
			RTRProxyManagedObjectClassDirectory*
			);

// Data
	RTRProxyManagedObjectServerPool& _pool;
	RTRObjectId _classFilter;
	RTRDLinkList<RTRProxyManagedObjectHandle, RTRDLink0> _handles;
	void *_notifier;
	RTRProxyManagedObjectServer* _tmpServer;
	const RTRProxyManagedObjectHandle* _tmpHandle;

private:
// Don't implement
	RTRProxyManagedObjectClassDirectory(
			const RTRProxyManagedObjectClassDirectory&);
	RTRProxyManagedObjectClassDirectory& operator=
			(const RTRProxyManagedObjectClassDirectory&);
}; 

inline
const RTRObjectId& RTRProxyManagedObjectClassDirectory::classFilter() const
{
	return _classFilter;
}

inline const RTRProxyManagedObjectServerPool&
RTRProxyManagedObjectClassDirectory::serverPool() const
{
	return _pool;
}

typedef RTRObjRef<RTRProxyManagedObjectClassDirectory> RTRProxyManagedObjectClassDirectoryPtr;

#endif
