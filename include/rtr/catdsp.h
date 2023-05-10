//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 31 1995"
// Version: 1.0

#ifndef _catdsp_h
#define _catdsp_h

#include "rtr/tabuldsp.h"
#include "rtr/mod.h"

// Synopsis:
// #include"rtr/catdsp.h"
//
// Description:
// See Also:
// 	RTRCategorySelection, RTRCategoryDisplayFrame
//
// Inherits:
//	RTRTabularDisplay, RTRManagedObjDirClient
//

class RTRCategoryDisplay :
	public RTRTabularDisplay,
	public RTRManagedObjDirClient
{ 
public:
// Constructor
	RTRCategoryDisplay(
		RTRDisplayFrame&, 
		const RTRClassCategory<RTRManagedObject>&
		);
		// _TAG Constructor

// Destructor
	virtual ~RTRCategoryDisplay();
		// _TAG Destructor

// Operations
	virtual void draw();
		// REQUIRE : onTop()
		// ENSURE : visible()
		// _TAG01 Operations

// Event processing
	virtual void processManagedObjectAdded(
				RTRManagedObjectDirectory&, RTRManagedObject& mo);
		// _TAG02 Event processing

	virtual void processManagedObjectRemoved(
					RTRManagedObjectDirectory&, 
					RTRManagedObject&);
		// _TAG02 Event processing

protected:
// Methods
	void allocateDisplayRegions();

// Data
	const RTRClassCategory<RTRManagedObject>& _category;

}; 

// Synopsis:
// #include"rtr/catdsp.h"
//
// Description:
// See Also:
//  RTRCategoryDisplay, RTRCategoryDisplayFrame
//
// Inherits:
//	RTRMBDisplayRegion
//

class RTRCategorySelection :
	public RTRMBDisplayRegion
{
public:
// Constructor
	RTRCategorySelection(
			RTRMBrowserApplication&, 
			const RTRClassCategory<RTRManagedObject>&,
			int,										// Width
			const char * = 0
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCategorySelection();
		// _TAG Destructor

// Attributes
	virtual const char *text();
		// _TAG01 Attributes

	virtual RTRBOOL selectable() const ;
		// _TAG01 Attributes

// Operations
	virtual void processSelection();
		// _TAG02 Operations

protected:
// Data
	RTRMBrowserApplication& _application;
	const RTRClassCategory<RTRManagedObject>& _category;
};

// Synopsis:
// #include"rtr/catdsp.h"
//
// Description:
// See Also:
//  RTRCategoryDisplay, RTRCategorySelection
//
// Inherits:
//  RTRDisplayFrame
//

class RTRCategoryDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRCategoryDisplayFrame(
			RTRMBrowserApplication&,
			const RTRClassCategory<RTRManagedObject>&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCategoryDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRCategoryDisplay _display;

};

#endif
