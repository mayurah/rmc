//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 31 1995"
// Version: 1.0

#ifndef _instdsp_h
#define _instdsp_h

#include "rtr/dspfrm.h"
#include "rtr/ffrmdsp.h"
#include "rtr/tabuldsp.h"
#include "rtr/vardsp.h"
#include "rtr/mo.h"

// Synopsis:
// #include"rtr/instdsp.h"
//
// Description:
// See Also:
//	RTRChildrenDisplay, RTRInstanceSelection, RTRInstanceDisplayFrame
//
// Inherits:
//	RTRFreeFormDisplay, RTRManagedObjectClient
//

class RTRInstanceDisplay :
	public RTRFreeFormDisplay,
	public RTRManagedObjectClient
{ 
public:
// Constructor
	RTRInstanceDisplay(RTRDisplayFrame&, RTRManagedObject&);
		// _TAG Constructor

// Destructor
	virtual ~RTRInstanceDisplay();
		// _TAG Destructor

// Operations
	virtual void draw();
		// REQUIRE : onTop()
		// ENSURE : visible()
		// _TAG01 Operations

// Event processing -- from RTRManagedObjectClient
	virtual void processObjectDeleted(RTRManagedObject&);
		// _TAG02 Event processing -- from RTRManagedObjectClient

protected:
// Data
	RTRManagedObject *_managedObject;

}; 

// Synopsis:
// #include"rtr/instdsp.h"
//
// Description:
// See Also:
//  RTRInstanceDisplay, RTRInstanceSelection, RTRInstanceDisplayFrame
//
// Inherits:
//  RTRTabularDisplay, RTRManagedObjectClient
//

class RTRChildrenDisplay :
	public RTRTabularDisplay,
	public RTRManagedObjectClient
{ 
public:
// Constructor
	RTRChildrenDisplay(
		RTRDisplayFrame&, 
		RTRManagedObject&,
		int nc, 						// number of columns
		int nr,							// number of rows
		int cw,							// column width
		Fill f = TopToBottom			// fill style for insertion
		);
		// _TAG Constructor

// Destructor
	virtual ~RTRChildrenDisplay();
		// _TAG Destructor

// Operations
	virtual void draw();
		// REQUIRE : onTop()
		// ENSURE : visible()
		// _TAG01 Operations

// Event processing -- from RTRManagedObjectClient
	virtual void processObjectDeleted(RTRManagedObject&);
		// _TAG02 Event processing -- from RTRManagedObjectClient

	virtual void processChildAdded(RTRManagedObject&, RTRManagedObject&);
        // _TAG02 Event processing -- from RTRManagedObjectClient

	virtual void processChildRemoved(RTRManagedObject&, RTRManagedObject&);
        // _TAG02 Event processing -- from RTRManagedObjectClient

protected:
// Methods
	void allocateDisplayRegions();

// Data
	RTRManagedObject *_managedObject;

}; 

// Synopsis:
// #include"rtr/instdsp.h"
//
// Description:
// See Also:
//  RTRInstanceDisplay, RTRChildrenDisplay, RTRInstanceDisplayFrame
//
// Inherits:
//	RTRMBDisplayRegion
//

class RTRInstanceSelection :
	public RTRMBDisplayRegion
{
public:
// Constructor
	RTRInstanceSelection(
			RTRMBrowserApplication&, 
			RTRManagedObject&, 
			int,							// Width
			const char * = 0);
		// _TAG Constructor

// Destructor
	virtual ~RTRInstanceSelection();
		// _TAG Destructor

// Attributes
	virtual const char *text();
		// _TAG01 Attributes

	virtual RTRBOOL selectable() const ;
		// _TAG01 Attributes

	inline RTRManagedObject& managedObject() const;
		// _TAG01 Attributes

// Operations
	virtual void processSelection();
		// _TAG02 Operations

protected:
// Data
	RTRMBrowserApplication& _application;
	RTRManagedObject& _managedObject;
		// Data
};

inline 
RTRManagedObject& RTRInstanceSelection::managedObject() const
{
	return _managedObject;
}

// Synopsis:
// #include"rtr/instdsp.h"
//
// Description:
// See Also:
//  RTRInstanceDisplay, RTRChildrenDisplay, RTRInstanceDisplayFrame
//
// Inherits:
//      RTRMBDisplayRegion
//
class RTRStateSelection :
	public RTRMBDisplayRegion,
	public RTRManagedObjectClient
{
public:
// Constructor
	RTRStateSelection(
			const RTRDisplayFrame&,
			RTRManagedObject&,
			int,                    // Width
			const char * = 0);
		// _TAG Constructor

// Destructor
	virtual ~RTRStateSelection();
		// _TAG Destructor

// Attributes
	virtual const char *text();
		// _TAG01 Attributes

	virtual RTRBOOL selectable() const ;
		// _TAG01 Attributes

	inline RTRManagedObject& managedObject() const;
		// _TAG01 Attributes

// Operations
	virtual void processSelection();
		// _TAG02 Operations

// Event processing
	virtual void processObjectInService(RTRManagedObject&);
		// _TAG03 Event processing

	virtual void processObjectRecovering(RTRManagedObject&);
		// _TAG03 Event processing

	virtual void processObjectWaiting(RTRManagedObject&);
		// _TAG03 Event processing

	virtual void processObjectDead(RTRManagedObject&);
		// _TAG03 Event processing

	virtual void processObjectInfo(RTRManagedObject&);
		// _TAG03 Event processing

	virtual void processObjectDeleted(RTRManagedObject&);
		// _TAG03 Event processing

protected:
// Utilities
	const char *stateText(RTRManagedObject::MOState st);

// Data
	const RTRDisplayFrame&  _frame;
	RTRManagedObject&       _managedObject;
	RTRString               _text;
		// Data
};

inline
RTRManagedObject& RTRStateSelection::managedObject() const
{
	return _managedObject;
}


// Synopsis:
// #include"rtr/instdsp.h"
//
// Description:
// See Also:
//  RTRInstanceDisplay, RTRChildrenDisplay, RTRInstanceSelection
//
// Inherits:
//  RTRDisplayFrame
//

class RTRInstanceDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRInstanceDisplayFrame(RTRMBrowserApplication&, RTRManagedObject&);
		// _TAG Constructor

// Destructor
	virtual ~RTRInstanceDisplayFrame();
		// _TAG Destructor

// Operations -- from RTRDisplayFrame (override)
	virtual void selectNext();
		// REQUIRE : onTop()
		// _TAG01 Operations -- from RTRDisplayFrame (override)

protected:
// Data
	RTRInstanceDisplay _instanceDisplay;
	RTRVariablesDisplay _variablesDisplay;
	RTRChildrenDisplay _childrenDisplay;

};

#endif
