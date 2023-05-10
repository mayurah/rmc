//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 23 1997"
// Version: 1.0

#ifndef _rtr_pmosp_h
#define _rtr_pmosp_h

#include "rtr/rtllist.h"
#include "rtr/llcursor.h"
#include "rtr/prxymos.h"
#include "rtr/lock.h"

class RTRProxyManagedObjectServerPool;
class RTRProxyManagedObjectServerPoolClient;

typedef RTRProxyManagedObjectServerPool PMOSP;
typedef RTRProxyManagedObjectServerPoolClient PMOSPC;


//
// Synopsis:
// #include "rtr/proxymos.h"
//
// Description:
// RTRProxyManagedObjectServerPool acts as a factory 
// for instances of the class RTRProxyManagedObjectServer.
// 
// See Also:
// RTRProxyManagedObjectServer
//
// Inherits:
// RTRLockableObj	
//

class RTRProxyManagedObjectServerPool
	: public RTRLockableObj
{ 
public:
// Constructor
	RTRProxyManagedObjectServerPool(
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedObjectServerPool();
		// _TAG Destructor

// Access -- sequential
	RTRLinkedListCursor<RTRProxyManagedObjectServer> servers() const;
		// A cursor providing sequential access to the servers in this pool.
		// _TAG01 Access -- sequential

// Event client management
	RTRBOOL hasClient(const RTRProxyManagedObjectServerPoolClient&) const;
		// Is the given client registered to receive update events
		// from this pool.
		// _TAG02 Event client management

	void addClient(const RTRProxyManagedObjectServerPoolClient& client);
		// Register the given client to receive update events from
		// this pool.
		// REQUIRE: !hasClient(client)
		// REQUIRE: hasClient(client)
		// _TAG02 Event client management

	void dropClient(const RTRProxyManagedObjectServerPoolClient& client);
		// Un-register the given client to receive update events from
		// this pool.
		// ENSURE: !hasClient(client)
		// _TAG02 Event client management

protected:
// Utilities
	void indicateServerAdded(RTRProxyManagedObjectServer&);
	void indicateServerRemoved(RTRProxyManagedObjectServer&);

	void notifyServerAdded(PMOSPC*, PMOSP*);
	void notifyServerRemoved(PMOSPC*, PMOSP*);

// Data
	RTRLinkedList<RTRProxyManagedObjectServer> _servers;
	void *_notifier;

	RTRProxyManagedObjectServer* _tmpServer;

// Friends
private:
// Don't implement
	RTRProxyManagedObjectServerPool(const RTRProxyManagedObjectServerPool&);
	RTRProxyManagedObjectServerPool& operator=
			(const RTRProxyManagedObjectServerPool&);
}; 

#endif
