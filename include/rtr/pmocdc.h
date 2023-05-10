//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 23 1997"
// Version: 1.0

#ifndef _rtr_pmocdc_h
#define _rtr_pmocdc_h

class RTRProxyManagedObjectClassDirectory;
class RTRProxyManagedObjectServer;
class RTRProxyManagedObjectHandle;

//
// Synopsis:
// #include "rtr/pmocdc.h"
//
// Description:
// RTRProxyManagedObjectClassDirectoryClient is the abstract base class for
// application components which can register to receive events from one
// or more instances of RTRProxyManagedObjectClassDirectory.
// 
// See Also:
// RTRProxyManagedObjectClassDirectory
//
// Inherits:
//

class RTRProxyManagedObjectClassDirectoryClient
{ 
public:
// Constructor
	RTRProxyManagedObjectClassDirectoryClient();
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedObjectClassDirectoryClient();
		// _TAG Destructor

// Event processing
	virtual void processDirectoryHandleAdded(
			RTRProxyManagedObjectClassDirectory&,
			RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			) = 0;
		// The handle has been added to the given directory.
		// _TAG01 Event processing

	virtual void processDirectoryHandleRemoved(
			RTRProxyManagedObjectClassDirectory&,
			RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			) = 0;
		// The handle has been removed from the given directory.
		// _TAG01 Event processing

private:
// Don't implement
	RTRProxyManagedObjectClassDirectoryClient(
			const RTRProxyManagedObjectClassDirectoryClient&);
	RTRProxyManagedObjectClassDirectoryClient& operator=
			(const RTRProxyManagedObjectClassDirectoryClient&);
}; 

#endif
