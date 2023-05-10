//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 17 1995"
// Version: 1.0

#ifndef _pdirdsp_h
#define _pdirdsp_h

// Proxy Managed Object Browser header files
#include "rtr/tabuldsp.h"

// Proxy Managed Object header files
#include "rtr/prxymos.h"
#include "rtr/pmosp.h"
#include "rtr/pmospc.h"

class RTRProxyRootsDisplay :
	public RTRTabularDisplay,
	public RTRProxyManagedObjectServerClient,
	public RTRProxyManagedObjectServerPoolClient
{ 
public:
// Constructor
	RTRProxyRootsDisplay(
		RTRProxyManagedObjectServerPool&,
		RTRDisplayFrame&,
		Fill f = TopToBottom		// fill style for insertion
		);
			// Number of columns == 1
			// Column width == 25
			// Origin column == 4

// Destructor
	virtual ~RTRProxyRootsDisplay();

// Operations
	virtual void draw();
		// REQUIRE : onTop()
		// ENSURE : visible()


// Event processing -- from RTRProxyManagedObjectServerPoolClient
	virtual void processProxyManagedObjectServerAdded(
		   	RTRProxyManagedObjectServerPool&,
			RTRProxyManagedObjectServer&
			);

	virtual void processProxyManagedObjectServerRemoved(
			RTRProxyManagedObjectServerPool&,
			RTRProxyManagedObjectServer&
			);

// Event processing -- from RTRProxyManagedObjectServerClient
	virtual void processObjectServerError(
			RTRProxyManagedObjectServer&
			);

	virtual void processObjectServerSync(
			RTRProxyManagedObjectServer&
			);

	virtual void processObjectServerRootAdded(
			RTRProxyManagedObjectServer&, 
			const RTRProxyManagedObjectHandle&
			);

	virtual void processObjectServerRootRemoved(
			RTRProxyManagedObjectServer&, 
			const RTRProxyManagedObjectHandle&
			);

protected:
// Methods
	void allocateDisplayRegions();

// Data
	RTRProxyManagedObjectServerPool& _pool;

};

class RTRProxyDirectoryDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyDirectoryDisplayFrame(
		RTRMBrowserApplication&,
		RTRProxyManagedObjectServerPool&);

// Destructor
	virtual ~RTRProxyDirectoryDisplayFrame();

protected:

	RTRProxyRootsDisplay _rootsDisplay;

};

#endif
