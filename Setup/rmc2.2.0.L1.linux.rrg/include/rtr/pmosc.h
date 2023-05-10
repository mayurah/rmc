//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 06 1996"
// Version: 1.0

#ifndef _rtr_pmosc_h
#define _rtr_pmosc_h

class RTRProxyManagedObjectServer;
class RTRProxyManagedObjectHandle;

// Synopsis:
// #include"rtr/pmosc.h"
//
// Description:
// RTRProxyManagedObjectServerClient is the abstract base class for application
// components which wish to register with one or more instances of 
// RTRProxyManagedObjectServer in order to be notified when root managed objects
// are added to or removed from a server.
//
// See Also:
// RTRProxyManagedObjectServer
//

class RTRProxyManagedObjectServerClient
{ 
public:
// Destructor
	virtual ~RTRProxyManagedObjectServerClient();
		// _TAG Destructor

// Event processing
	virtual void processObjectServerError(
			RTRProxyManagedObjectServer&
			);
		// The given server has transitioned into an unrecoverable
		// error state.
		// _TAG01 Event processing

	virtual void processObjectServerSync(
			RTRProxyManagedObjectServer&
			);
		// The given server has transitioned into the Sync state.
		// _TAG01 Event processing

	virtual void processObjectServerRootAdded(
			RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			);
		// The given root proxy managed object (handle) has
		//  been added to the server.
		// _TAG01 Event processing

	virtual void processObjectServerRootRemoved(
			RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			);
		// The given root proxy managed object (handle) has
		//  been removed from the server.
		// _TAG01 Event processing
}; 

#endif
