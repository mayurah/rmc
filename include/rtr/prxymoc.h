//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 24 1996"
// Version: 1.0

#ifndef _rtr_prxymoc_h
#define _rtr_prxymoc_h

class RTRProxyManagedObject;
class RTRProxyManagedObjectHandle;
class RTRProxyManagedVariableHandle;

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// The base class for components which can register with a proxy managed object
// to receive change events from that proxy managed object.  The notifications
// are grouped into five categories:
// (1) proxy managed object state changes,
// (2) the managed object has been deleted by the producer,
// (3) the state attribute has changed,
// (4) a child managed object has been added/removed, and
// (5) a contained managed variable has been added/removed.
//
// See Also:
//	RTRProxyManagedObject
//

class RTRProxyManagedObjectClient
{ 
public:
// Destructor
	virtual ~RTRProxyManagedObjectClient();
		// _TAG Destructor

// Event processing
	virtual void processProxyManagedObjectError(
			const RTRProxyManagedObject&
			) = 0;
		// The given proxy managed object has transitioned into
		// an unrecoverable error state.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectSync(
			const RTRProxyManagedObject&
			) = 0;
		// The given ProxyManagedObject is in Sync.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectDeleted(
			const RTRProxyManagedObject&
			) = 0;
		// The given ProxyManagedObject has been removed.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectInfo(
			const RTRProxyManagedObject&
			) = 0;
		// The given proxy managed object has additional information
		// concerning its state attribute.  The proxy managed object
		// has not changed state.  Refer to the text() attribute of the
		// given proxy managed object.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectInService(
			const RTRProxyManagedObject&
			) = 0;
		// The given proxy managed object is now in a normal service state.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectRecovering(
			const RTRProxyManagedObject&
			) = 0;
		// The given proxy managed object is in a service interrupted state but
		// is attempting to recover normal service automatically. 
		// _TAG01 Event processing

	virtual void processProxyManagedObjectWaiting(
			const RTRProxyManagedObject&
			) = 0;
		// The given proxy managed object is in a service interrupted state and
		// is waiting for manual intervention to restore normal service. 
		// _TAG01 Event processing

	virtual void processProxyManagedObjectDead(
			const RTRProxyManagedObject&
			) = 0;
		// The given proxy managed object has entered an unrecoverable error state.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectChildAdded(
			const RTRProxyManagedObject&,
			const RTRProxyManagedObjectHandle&
			) = 0;
		// The given proxy managed object has a new child.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectChildRemoved(
			const RTRProxyManagedObject&, 
			const RTRProxyManagedObjectHandle&
			) = 0;
		// The given proxy managed object has had a child removed.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectVariableAdded(
			const RTRProxyManagedObject&,
			const RTRProxyManagedVariableHandle&
			) = 0;
		// The given proxy managed object has a new variable.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectVariableRemoved(
			const RTRProxyManagedObject&,
			const RTRProxyManagedVariableHandle&
			) = 0;
		// The given proxy managed object has had a variable removed.
		// _TAG01 Event processing

}; 

#endif
