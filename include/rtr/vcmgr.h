//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 02 1995"
// Version: 1.0

#ifndef _vcmgr_h
#define _vcmgr_h

#include "rtr/rtrdefs.h"

class RTRManagedVariable;
class RTRManagedVariableClient;

// Synopsis:
// #include"rtr/vcmgr.h"
//
// Description:
// See Also:
//	RTRManagedObject, RTRManagedVariableClient,
//	RTRManagedString, RTRManagedStringParameter,
//	RTRManagedCounter, RTRManagedNumeric, RTRManagedNumericParameter,
//	RTRManagedGauge, RTRPublicObject, RTRString
//

class RTRManagedVarClientMgr
{ 
public:
// Constructor
	RTRManagedVarClientMgr(RTRManagedVariable&);
		// _TAG Constructor

// Destructor
	~RTRManagedVarClientMgr();
		// _TAG Destructor

// Attributes
	inline RTRManagedVariable& variable() const;
		// The variable whose clients are being managed.
		// _TAG01 Attributes

	int count() const;
		// The number of clients currently registered for events.
		// _TAG01 Attributes

// Client management
	void addClient(RTRManagedVariableClient& newClient);
		// Register the given client to receive events from 
		// this directory.
		// ENSURE : hasClient(newClient)
		// _TAG02 Client management

	void dropClient(RTRManagedVariableClient& oldClient);
		// Un-register the given client to receive events from 
		// this directory.
		// ENSURE : !hasClient(oldClient)
		// _TAG02 Client management

	RTRBOOL hasClient(RTRManagedVariableClient& client) const;
		// Is the given client registered to receive events from 
		// this directory.
		// _TAG02 Client management

// Operations
	void notifyUpdate();
		// _TAG03 Operations

	void notifyDelete();
		// _TAG03 Operations 

protected:
// Data
	RTRManagedVariable& _variable;
	void *_notifier;
		// Data
}; 

inline 
RTRManagedVariable& RTRManagedVarClientMgr::variable() const
{
	return _variable;
}

#endif
