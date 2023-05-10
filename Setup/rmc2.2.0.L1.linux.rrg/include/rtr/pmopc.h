//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 23 1997"
// Version: 1.0

#ifndef _rtr_pmopc_h
#define _rtr_pmopc_h

class RTRProxyManagedObjectPool;
class RTRProxyManagedObject;

//
// Synopsis:
// #include "rtr/pmopc.h"
//
// Description:
// RTRProxyManagedObjectPoolClient is the abstract base class for application
// components which wish to register with one or more instances of 
// RTRProxyManagedObjectPool in order to be notified when objects are added to 
// or removed from a pool.
// 
// See Also:
// RTRProxyManagedObjectPool, RTRProxyManagedObject
//
// Inherits:
//

class RTRProxyManagedObjectPoolClient
{ 
public:
// Constructor
	RTRProxyManagedObjectPoolClient();
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedObjectPoolClient();
		// _TAG Destructor

// Event processing
	virtual void processProxyManagedObjectAdded(
			RTRProxyManagedObjectPool&,
			RTRProxyManagedObject&
			) = 0;
		// A new object has been added to the given pool.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectRemoved(
			RTRProxyManagedObjectPool&,
			RTRProxyManagedObject&
			) = 0;
		// An object has been removed from the given pool.
		// _TAG01 Event processing

protected:
// Friends
private:
// Don't implement
	RTRProxyManagedObjectPoolClient(const RTRProxyManagedObjectPoolClient&);
	RTRProxyManagedObjectPoolClient& operator=
			(const RTRProxyManagedObjectPoolClient&);
}; 

#endif
