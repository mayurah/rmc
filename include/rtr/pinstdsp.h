//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 31 1995"
// Version: 1.0

#ifndef _pinstdsp_h
#define _pinstdsp_h

#include "rtr/dspfrm.h"
#include "rtr/ffrmdsp.h"
#include "rtr/tabuldsp.h"
#include "rtr/pvardsp.h"
#include "rtr/prxymo.h"

class RTRProxyInstanceDisplay :
	public RTRFreeFormDisplay,
	public RTRProxyManagedObjectClient
{ 
public:
// Constructor
	RTRProxyInstanceDisplay(
			RTRProxyManagedObjectServer&,
			RTRDisplayFrame&,
			RTRProxyManagedObjectPtr
			);

// Destructor
	virtual ~RTRProxyInstanceDisplay();

// Operations
	virtual void draw();
		// REQUIRE : onTop()
		// ENSURE : visible()

// Event processing -- from RTRProxymanagedObjectClient
	virtual void processProxyManagedObjectError(
			const RTRProxyManagedObject&
			);
		// _TAG01 Event processing

	virtual void processProxyManagedObjectSync(
			const RTRProxyManagedObject&
			);
		// The given Network Object is in Sync.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectDeleted(
			const RTRProxyManagedObject&
			);
		// The given Network Object has been removed.
		// _TAG01 Event processing

	virtual void processProxyManagedObjectInfo(
			const RTRProxyManagedObject&
			);
		// _TAG01 Event processing

	virtual void processProxyManagedObjectInService(
			const RTRProxyManagedObject&
			);
		// _TAG01 Event processing

	virtual void processProxyManagedObjectRecovering(
			const RTRProxyManagedObject&
			);
		// _TAG01 Event processing

	virtual void processProxyManagedObjectWaiting(
			const RTRProxyManagedObject&
			);
		// _TAG01 Event processing

	virtual void processProxyManagedObjectDead(
			const RTRProxyManagedObject&
			);
		// _TAG01 Event processing

	virtual void processProxyManagedObjectChildAdded(
			const RTRProxyManagedObject&,
			const RTRProxyManagedObjectHandle&
			);
		// _TAG01 Event processing

	virtual void processProxyManagedObjectChildRemoved(
			const RTRProxyManagedObject&, 
			const RTRProxyManagedObjectHandle&
			);
		// _TAG01 Event processing

	virtual void processProxyManagedObjectVariableAdded(
			const RTRProxyManagedObject&,
			const RTRProxyManagedVariableHandle&
			);
		// _TAG01 Event processing

	virtual void processProxyManagedObjectVariableRemoved(
			const RTRProxyManagedObject&,
			const RTRProxyManagedVariableHandle&
			);
		// _TAG01 Event processing

protected:
// Utilities
	const char *stateText(
			RTRProxyManagedObject::PMOState st
			);

// Data
	RTRProxyManagedObjectPtr _proxyObject;
	RTRProxyManagedObjectServer& _server;

}; 

class RTRProxyChildrenDisplay :
	public RTRTabularDisplay,
	public RTRProxyManagedObjectClient
{ 
public:
// Constructor
	RTRProxyChildrenDisplay(
		RTRProxyManagedObjectServer&,
		RTRDisplayFrame&, 
		RTRProxyManagedObjectPtr,
		int nc, 			// number of columns
		int nr,				// number of rows
		int cw,				// column width
		Fill f = TopToBottom		// fill style for insertion
		);

// Destructor
	virtual ~RTRProxyChildrenDisplay();

// Operations
	virtual void draw();
		// REQUIRE : onTop()
		// ENSURE : visible()

// Event processing -- from RTRProxyManagedObjectClient
	virtual void processProxyManagedObjectError(
			const RTRProxyManagedObject&
			);

	virtual void processProxyManagedObjectSync(
			const RTRProxyManagedObject&
			);

	virtual void processProxyManagedObjectDeleted(
			const RTRProxyManagedObject&
			);

	virtual void processProxyManagedObjectInfo(
			const RTRProxyManagedObject&
			);

	virtual void processProxyManagedObjectInService(
			const RTRProxyManagedObject&
			);

	virtual void processProxyManagedObjectRecovering(
			const RTRProxyManagedObject&
			);

	virtual void processProxyManagedObjectWaiting(
			const RTRProxyManagedObject&
			);

	virtual void processProxyManagedObjectDead(
			const RTRProxyManagedObject&
			);

	virtual void processProxyManagedObjectChildAdded(
			const RTRProxyManagedObject&,
			const RTRProxyManagedObjectHandle&
			);

	virtual void processProxyManagedObjectChildRemoved(
			const RTRProxyManagedObject&,
			const RTRProxyManagedObjectHandle&
			);

	virtual void processProxyManagedObjectVariableAdded(
			const RTRProxyManagedObject&,
			const RTRProxyManagedVariableHandle&
			);

	virtual void processProxyManagedObjectVariableRemoved(
			const RTRProxyManagedObject&,
			const RTRProxyManagedVariableHandle&
			);

protected:
// Methods
	void allocateDisplayRegions();

// Data
	RTRProxyManagedObjectPtr _proxyObject;
	RTRProxyManagedObjectServer& _server;

}; 

class RTRProxyInstanceSelection :
	public RTRMBDisplayRegion
{
public:
// Constructor
	RTRProxyInstanceSelection(
			RTRProxyManagedObjectServer&,
			RTRMBrowserApplication&, 
			RTRProxyManagedObjectHandle&, 
			int,			// Width
			const char * = 0);

// Destructor
	virtual ~RTRProxyInstanceSelection();

// Attributes
	virtual const char *text();

	virtual RTRBOOL selectable() const ;

	inline RTRProxyManagedObjectHandle& proxyObject() const;

// Operations
	virtual void processSelection();

protected:
// Data
	RTRProxyManagedObjectServer& _server;
	RTRMBrowserApplication& _application;
	RTRProxyManagedObjectHandle& _proxyObjHandle;
};

inline 
RTRProxyManagedObjectHandle& RTRProxyInstanceSelection::proxyObject() const
{
	return _proxyObjHandle;
}

class RTRProxyInstanceDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyInstanceDisplayFrame(
			RTRProxyManagedObjectServer&,
			RTRMBrowserApplication&,
			RTRProxyManagedObjectPtr
			);

// Destructor
	virtual ~RTRProxyInstanceDisplayFrame();

// Operations -- from RTRDisplayFrame (override)
	virtual void selectNext();
		// REQUIRE : onTop()

protected:
// Data
	RTRProxyInstanceDisplay _instanceDisplay;
	RTRProxyVariablesDisplay _variablesDisplay;
	RTRProxyChildrenDisplay _childrenDisplay;
	RTRProxyManagedObjectServer& _server;
};

#endif
