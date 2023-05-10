//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 06 1996"
// Version: 1.0

#ifndef _rtr_prxymos_h
#define _rtr_prxymos_h

#include "rtr/lock.h"
#include "rtr/prxyh.h"
#include "rtr/pmosc.h"
#include "rtr/prxymo.h"


// Synopsis:
// #include"rtr/prxymos.h"
//
// Description:
// Provides access to the managed objects of a
// particular RTRManagedObjectServer.
// The set of available root proxy managed objects is 
// also maintained.
//
// See Also:
// RTRProxyManagedObjectServerClient
//
// Inherits:
// RTRLockableObj
//

class RTRProxyManagedObjectServer :
	public RTRLockableObj
{ 
public:
// Constructor
	RTRProxyManagedObjectServer();
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedObjectServer();
		// _TAG Destructor

// Attributes
	inline const RTRString& text() const;
		// An explanation for the state of this proxy.
		// _TAG01 Attributes

// State
	inline RTRBOOL error() const;
		// Is this proxy in an unrecoverable error state?
		// _TAG02 State

	inline RTRBOOL inSync() const;
		// Is this proxy synchronized with its remote server?
		// _TAG02 State

// Access -- sequential
	RTRProxyManagedObjectHandleIterator roots() const;
		// An iterator which provides sequential access to handles
		// of all root objects available from this proxy.
		// REQUIRE: inSync()
		// _TAG03 Access -- sequential

// Access -- random
	virtual RTRProxyManagedObjectPtr object(
			const RTRProxyManagedObjectHandle& id
			); // const; mgobj0255
		// The object with the given id (handle).
		// _TAG04 Access -- random

// Event client management
	RTRBOOL hasClient(const RTRProxyManagedObjectServerClient&) const;
		// Is the given client registered to receive update and state events
		// from this ProxyManaged Object Server.
		// _TAG05 Event client management

	void addClient(const RTRProxyManagedObjectServerClient& client);
		// Register the given client to receive update and state events from
		// this ProxyManaged Object Server.
		// REQUIRE: !hasClient(client)
		// REQUIRE: hasClient(client)
		// _TAG05 Event client management

	void dropClient(const RTRProxyManagedObjectServerClient& client);
		// Un-register the given client to receive update events from
		// this ProxyManaged Object Server.
		// ENSURE: !hasClient(client)
		// _TAG05 Event client management

protected:
// Access
	virtual RTRProxyManagedObject* objectById(const RTRObjectId&) const;

// Utilities -- event propagation
	void indicateError();
	void indicateSync();
	void indicateRootAdded(const RTRProxyManagedObjectHandle&);
	void indicateRootRemoved(const RTRProxyManagedObjectHandle&);

	void notifyError(
			RTRProxyManagedObjectServerClient*,
			RTRProxyManagedObjectServer*);
	void notifySync(
			RTRProxyManagedObjectServerClient*,
			RTRProxyManagedObjectServer*);
	void notifyRootAdded(
			RTRProxyManagedObjectServerClient*,
			RTRProxyManagedObjectServer*);
	void notifyRootRemoved(
			RTRProxyManagedObjectServerClient*,
			RTRProxyManagedObjectServer*);

// Operations
	void removeObject(RTRProxyManagedObject&);
	virtual void cleanUp();
	virtual RTRProxyManagedObject* newObject(
			const RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			) const = 0;

// Data
	RTRBOOL _error;
	RTRBOOL _inSync;
	RTRString _text;
	RTRDLinkList<RTRProxyManagedObjectHandle, RTRDLink0> _roots;
	RTRDLinkList<RTRProxyManagedObject, RTRDLink0> _objects;
	void *_notifier;

// Temp data
	const RTRProxyManagedObjectHandle* _tmpHandle;

// Friends
friend class RTRProxyManagedObject;
}; 

inline 
const RTRString& RTRProxyManagedObjectServer::text() const
{
	return _text;
}

inline 
RTRBOOL RTRProxyManagedObjectServer::error() const
{
	return _error;
}

inline 
RTRBOOL RTRProxyManagedObjectServer::inSync() const
{
	return _inSync;
}

#endif
