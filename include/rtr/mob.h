//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 16 1995"
// Version: 1.0

#ifndef _mob_h
#define _mob_h

#include "rtr/brwsapp.h"
#include "rtr/tabuldsp.h"
#include "rtr/logo.h"

class RTRManagedObjectBrowser;

// Synopsis:
// #include"rtr/mob.h"
//
// Description:
// See Also:
//	RTRMOBObjMenuItem, RTRMOBLogMenuItem, RTRMOBTopMenu, RTRMOBTopFrame,
//	RTRManagedObjectBrowser
//
// Inherits:
//	RTRMBDisplayRegion
//

class RTRMOBMenuItem :
	public RTRMBDisplayRegion
{
public:
// Constructor
	RTRMOBMenuItem(RTRManagedObjectBrowser&);
		// _TAG Constructor

// Destructor
	virtual ~RTRMOBMenuItem();
		// _TAG Destructor

// Attributes
	virtual RTRBOOL selectable() const ;
		// _TAG01 Attributes

protected:
// Data
	RTRManagedObjectBrowser& _mob;
};

// Synopsis:
// #include"rtr/mob.h"
//
// Description:
// See Also:
//  RTRMOBLogMenuItem, RTRMOBTopMenu, RTRMOBTopFrame,
//  RTRManagedObjectBrowser
//
// Inherits:
//  RTRMOBMenuItem
//

class RTRMOBObjMenuItem :
	public RTRMOBMenuItem
{
public:
// Constructor
	RTRMOBObjMenuItem(RTRManagedObjectBrowser&);
		// _TAG Constructor

// Destructor
	virtual ~RTRMOBObjMenuItem();
		// _TAG Destructor

// Attributes
	virtual const char *text();
		// _TAG01 Attributes

// Operations
	virtual void processSelection();
		// _TAG02 Operations

};

// Synopsis:
// #include"rtr/mob.h"
//
// Description:
// See Also:
//  RTRMOBObjMenuItem, RTRMOBTopMenu, RTRMOBTopFrame,
//  RTRManagedObjectBrowser
//
// Inherits:
//  RTRMOBMenuItem
//

class RTRMOBLogMenuItem :
	public RTRMOBMenuItem
{
public:
// Constructor
	RTRMOBLogMenuItem(RTRManagedObjectBrowser&);
		// _TAG Constructor

// Destructor
	virtual ~RTRMOBLogMenuItem();
		// _TAG Destructor

// Attributes
	virtual const char *text();
		// _TAG01 Attributes

// Operations
	virtual void processSelection();
		// _TAG02 Operations

};

// Synopsis:
// #include"rtr/mob.h"
//
// Description:
// See Also:
//  RTRMOBObjMenuItem, RTRMOBTopMenu, RTRMOBTopFrame,
//  RTRManagedObjectBrowser
//
// Inherits:
//  RTRMOBMenuItem
//

class RTRMOBHelpMenuItem :
	public RTRMOBMenuItem
{
public:
// Constructor
	RTRMOBHelpMenuItem(RTRManagedObjectBrowser&);
		// _TAG Constructor

// Destructor
	virtual ~RTRMOBHelpMenuItem();
		// _TAG Destructor

// Attributes
	virtual const char *text();
		// _TAG01 Attributes

// Operations
	virtual void processSelection();
		// _TAG02 Operations

};

// Synopsis:
// #include"rtr/mob.h"
//
// Description:
// See Also:
//  RTRMOBMenuItem, RTRMOBObjMenuItem, RTRMOBLogMenuItem, RTRMOBTopFrame,
//  RTRManagedObjectBrowser
//
// Inherits:
//	RTRTabularDisplay
//

class RTRMOBTopMenu :
	public RTRTabularDisplay
{
public:
// Constructor
	RTRMOBTopMenu(RTRManagedObjectBrowser&, RTRDisplayFrame&);
		// _TAG Constructor 

// Destructor
	virtual ~RTRMOBTopMenu();
		// _TAG Destructor

// Operations -- from RTRTabularDisplay
	virtual void internalMoveTo(int, int);
		// REQUIRE: !visible()
		// _TAG01 Operations -- from RTRTabularDisplay

	class MCmd :
		public RTRSimpleKeyClient
	{
	public:
		MCmd(RTRManagedObjectBrowser& m, int c)
			: RTRSimpleKeyClient(c), _mob(m)
		{ }
	protected:
		RTRManagedObjectBrowser& _mob;
	};

	class ToObjectsCmd: 
		public MCmd
	{
	public:
		ToObjectsCmd(RTRManagedObjectBrowser& m, int c) : MCmd(m, c) {}

		virtual void processKey();
	};

	class ToEventsCmd: 
		public MCmd
	{
	public:
		ToEventsCmd(RTRManagedObjectBrowser& m, int c) : MCmd(m, c) {}

		virtual void processKey();
	};

	class ToHelpCmd: 
		public MCmd
	{
	public:
		ToHelpCmd(RTRManagedObjectBrowser& m, int c) : MCmd(m, c) {}

		virtual void processKey();
	};

protected:
// Data
	ToObjectsCmd _toObjectsCmd;
	ToEventsCmd _toEventsCmd;
	ToHelpCmd _toHelpCmd;
	RTRMOBLogMenuItem _logItem;
	RTRMOBObjMenuItem _objItem;
	RTRMOBHelpMenuItem _helpItem;
};

// Synopsis:
// #include"rtr/mob.h"
//
// Description:
// See Also:
//  RTRMOBMenuItem, RTRMOBObjMenuItem, RTRMOBLogMenuItem, RTRMOBTopMenu,
//  RTRManagedObjectBrowser
//
// Inherits:
//	RTRDisplayFrame
//

class RTRMOBTopFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRMOBTopFrame(RTRManagedObjectBrowser&);
		// _TAG Constructor

// Destructor
	virtual ~RTRMOBTopFrame();
		// _TAG Destructor

// Operations -- from RTRDisplayFrame
	virtual void refresh();
		// REQUIRE : onTop()
		// _TAG01 Operations -- from RTRDisplayFrame

protected:
// Data
	RTRAppLogo _logo;
	RTRMOBTopMenu _menu;
};

// Synopsis:
// #include"rtr/mob.h"
//
// Description:
// See Also:
//  RTRMOBMenuItem, RTRMOBObjMenuItem, RTRMOBLogMenuItem, RTRMOBTopMenu,
//  RTRMOBTopFrame
//
// Inherits:
//	RTRMBrowserApplication
//

class RTRManagedObjectBrowser :
	public RTRMBrowserApplication
{ 
public:
// Constructor
	RTRManagedObjectBrowser();
		// _TAG Constructor

// Operations
	void browseObjects();
		// _TAG01 Operations

	void browseEvents();
		// _TAG01 Operations

	void browseHelp();
		// _TAG01 Operations

protected:
// Data
	RTRDisplayFramePtr topFrame;
	RTRDisplayFramePtr dirFrame;
	RTRDisplayFramePtr eventFrame;
	RTRDisplayFramePtr helpFrame;
}; 

#endif
