//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 23 1997"
// Version: 1.0

#ifndef _rtr_pmop_h
#define _rtr_pmop_h

#include "rtr/pmocd.h"
#include "rtr/pmocdc.h"

class RTRProxyManagedObjectPoolClient;

//
// Synopsis:
// #include "rtr/pmop.h"
//
// Description:
// RTRProxyManagedObjectPool is a pool of objects matching the contents of 
// a directory provided on the constructor. The directory in turn matches
// the contents of a pool of object servers.
// 
// See Also:
// RTRProxyManagedObjectClassDirectory 
//
// Inherits:
// RTRProxyManagedObjectClassDirectoryClient
//

class RTRProxyManagedObjectPool :
	public RTRProxyManagedObjectClassDirectoryClient
{ 
public:
// Constructor
	RTRProxyManagedObjectPool(RTRProxyManagedObjectClassDirectory&);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedObjectPool();
		// _TAG Destructor

// Query
	RTRBOOL hasObject(const RTRObjectId&) const;
		// Does this pool contain an object with the given identifier?
		// _TAG01 Query

// Attributes
	inline RTRProxyManagedObjectClassDirectory& directory() const;
		// _TAG02 Attributes
	
// Access -- random
	RTRProxyManagedObjectPtr object(const RTRObjectId&) const;
		// The object, if any, with the given identifier;
		// _TAG03 Access -- random

// Access -- sequential
	RTRLinkedListCursor<RTRProxyManagedObjectPtr> objects() const;
		// An iterator providing sequential access to the objects in this pool.
		// _TAG04 Access -- sequential

// Event processing
	virtual void processDirectoryHandleAdded(
			RTRProxyManagedObjectClassDirectory&,
			RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			);
		// _TAG05 Event processing

	virtual void processDirectoryHandleRemoved(
			RTRProxyManagedObjectClassDirectory&,
			RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			);
		// _TAG05 Event processing

// Event client management
	RTRBOOL hasClient(const RTRProxyManagedObjectPoolClient&) const;
		// Is the given client registered to receive update events
		// from this pool.
		// _TAG06 Event client management

	void addClient(const RTRProxyManagedObjectPoolClient& client);
		// Register the given client to receive update events from
		// this pool.
		// REQUIRE: !hasClient(client)
		// REQUIRE: hasClient(client)
		// _TAG06 Event client management

	void dropClient(const RTRProxyManagedObjectPoolClient& client);
		// Un-register the given client to receive update events from
		// this pool.
		// ENSURE: !hasClient(client)
		// _TAG06 Event client management

protected:
// Utilities
	void indicateObjectAdded(RTRProxyManagedObject&);
	void indicateObjectRemoved(RTRProxyManagedObject&);

	void notifyObjectAdded(RTRProxyManagedObjectPoolClient*, RTRProxyManagedObjectPool*);
	void notifyObjectRemoved(RTRProxyManagedObjectPoolClient*, RTRProxyManagedObjectPool*);

// Data
	RTRProxyManagedObjectClassDirectory& _directory;
	RTRLinkedList<RTRProxyManagedObjectPtr> _objects;
	void* _notifier;
	RTRProxyManagedObject* _tmpObject;

// Friends
private:
// Don't implement
	RTRProxyManagedObjectPool(const RTRProxyManagedObjectPool&);
	RTRProxyManagedObjectPool& operator=(const RTRProxyManagedObjectPool&);
}; 

inline
RTRProxyManagedObjectClassDirectory&
RTRProxyManagedObjectPool::directory() const
{
	return _directory;
}

#endif
