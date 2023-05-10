//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 23 1997"
// Version: 1.0

#ifndef _rtr_pmospc_h
#define _rtr_pmospc_h

class RTRProxyManagedObjectServerPool;
class RTRProxyManagedObjectServer;

//
// Synopsis:
// #include "rtr/proxymos.h"
//
// Description:
// The base class for components which can register with a proxy managed
// object server pool to receive change events from that server pool.
// The notifications are grouped into a single category.
// (1) A proxy managed object server has been added/removed from the pool.
// 
// See Also:
// RTRProxyManagedObjectServerPool
//
// Inherits:
//

class RTRProxyManagedObjectServerPoolClient
{ 
public:
// Constructor
	RTRProxyManagedObjectServerPoolClient();
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedObjectServerPoolClient();
		// _TAG Destructor

// Event processing
	virtual void processProxyManagedObjectServerAdded(
			RTRProxyManagedObjectServerPool&,
			RTRProxyManagedObjectServer&
			);
		// The given server has been added to the pool.
		// _TAG08 Event processing

	virtual void processProxyManagedObjectServerRemoved(
			RTRProxyManagedObjectServerPool&,
			RTRProxyManagedObjectServer&
			);
		// The given server is being removed from the pool.
		// _TAG08 Event processing

protected:
// Friends
private:
// Don't implement
	RTRProxyManagedObjectServerPoolClient(const RTRProxyManagedObjectServerPoolClient&);
	RTRProxyManagedObjectServerPoolClient& operator=(const RTRProxyManagedObjectServerPoolClient&);
}; 

#endif
