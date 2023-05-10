//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 17 1995"
// Version: 1.0

#ifndef _dirdsp_h
#define _dirdsp_h

#include "rtr/tabuldsp.h"
#include "rtr/mod.h"

class RTRCategoryDisplay;

// Synopsis:
// #include"rtr/dirdsp.h"
//
// Description:
// See Also:
//	RTRRootsDisplay, RTRDirectoryDisplayFrame
//
// Inherits:
//	RTRTabularDisplay, RTRManagedObjDirClient
//

class RTRContentsDisplay :
	public RTRTabularDisplay,
	public RTRManagedObjDirClient
{ 
public:
// Constructor
	RTRContentsDisplay(
		RTRDisplayFrame&,
		Fill f = TopToBottom			// fill style for insertion
		);
		// Number of columns == 1,
		// Column width == 25,
		// Origin column == 4
		// _TAG Constructor

// Destructor
	virtual ~RTRContentsDisplay();
		// _TAG Destructor

// Operations
	virtual void draw();
		// REQUIRE : onTop()
		// ENSURE : visible()
		// _TAG01 Operations

// Event processing
	virtual void processCategoryAdded(
					RTRManagedObjectDirectory&, 
					RTRClassCategory<RTRManagedObject>&
					);
		// _TAG02 Event processing

protected:
// Methods
	void allocateDisplayRegions();

}; 

// Synopsis:
// #include"rtr/dirdsp.h"
//
// Description:
// See Also:
//  RTRContentsDisplay, RTRDirectoryDisplayFrame
//
// Inherits:
//  RTRTabularDisplay, RTRManagedObjDirClient
//

class RTRRootsDisplay :
	public RTRTabularDisplay,
	public RTRManagedObjDirClient
{ 
public:
// Constructor
	RTRRootsDisplay(
		RTRDisplayFrame&,
		Fill f = TopToBottom			// fill style for insertion
		);
		// Number of columns == 1,
		// Column width == 25,
		// Origin column == 4
		// _TAG Constructor

// Destructor
	virtual ~RTRRootsDisplay();
		// _TAG Destructor

// Operations
	virtual void draw();
		// REQUIRE : onTop()
		// ENSURE : visible()
		// _TAG01 Operations

// Event processing
	virtual void processManagedObjectAdded(
					RTRManagedObjectDirectory&, 
					RTRManagedObject&
					);
		// _TAG02 Event processing

	virtual void processManagedObjectRemoved(
					RTRManagedObjectDirectory&, 
					RTRManagedObject&
					);
		// _TAG02 Event processing

protected:
// Methods
	void allocateDisplayRegions();

};

// Synopsis:
// #include"rtr/dirdsp.h"
//
// Description:
// See Also:
//  RTRContentsDisplay, RTRRootsDisplay
//
// Inherits:
//  RTRDisplayFrame
//

class RTRDirectoryDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRDirectoryDisplayFrame(RTRMBrowserApplication&);
		// _TAG Constructor

// Destructor
	virtual ~RTRDirectoryDisplayFrame();
		// _TAG Destructor

protected:

	RTRContentsDisplay _contentsDisplay;
	RTRRootsDisplay _rootsDisplay;

};

#endif
