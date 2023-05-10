//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "Jun. 27 1996"
// Version: 1.0

#ifndef _pob_h
#define _pob_h

#include "rtr/brwsapp.h"
#include "rtr/tabuldsp.h"
#include "rtr/logo.h"
#include "rtr/brwsrdsp.h"
#include "rtr/pmosp.h"
#include "rtr/helpdsp.h"

class RTRProxyObjectBrowser;

class RTRPOBMenuItem :
	public RTRMBDisplayRegion
{
public:
// Constructor
	RTRPOBMenuItem(RTRProxyObjectBrowser&);

// Destructor
	virtual ~RTRPOBMenuItem();

// Attributes
	virtual RTRBOOL selectable() const ;

protected:
// Data
	RTRProxyObjectBrowser& _pob;
};

class RTRPOBObjMenuItem :
	public RTRPOBMenuItem
{
public:
// Constructor
	RTRPOBObjMenuItem(RTRProxyObjectBrowser&);

// Destructor
	virtual ~RTRPOBObjMenuItem();

// Attributes
	virtual const char *text();

// Operations
	virtual void processSelection();

};

// Synopsis:
// #include"rtr/pob.h"
//
// Description:
// See Also:
// Inherits:
//

class RTRPOBHelpMenuItem :
	public RTRPOBMenuItem
{
public:
// Constructor
	RTRPOBHelpMenuItem(RTRProxyObjectBrowser&);
		// _TAG Constructor

// Destructor
	virtual ~RTRPOBHelpMenuItem();
		// _TAG Destructor

// Attributes
	virtual const char *text();
		// _TAG01 Attributes

// Operations
	virtual void processSelection();
		// _TAG02 Operations
};

class RTRPOBTopMenu :
	public RTRTabularDisplay
{
public:
// Constructor
	RTRPOBTopMenu(RTRProxyObjectBrowser&, RTRDisplayFrame&);

// Destructor
	virtual ~RTRPOBTopMenu();

// Operations -- from RTRTabularDisplay
	virtual void internalMoveTo(int, int);
		// REQUIRE: !visible()

	class MCmd :
		public RTRSimpleKeyClient
	{
	public:
		MCmd(RTRProxyObjectBrowser& m, int c)
			: RTRSimpleKeyClient(c), _pob(m)
		{ }
	protected:
		RTRProxyObjectBrowser& _pob;
	};

	class ToObjectsCmd: 
		public MCmd
	{
	public:
		ToObjectsCmd(RTRProxyObjectBrowser& m, int c) : MCmd(m, c) {}

		virtual void processKey();
	};

	class ToHelpCmd:
		public MCmd
	{
	public:
		ToHelpCmd(RTRProxyObjectBrowser& m, int c) : MCmd(m, c) {}

		virtual void processKey();
	};

protected:
// Data
	ToObjectsCmd _toObjectsCmd;
	ToHelpCmd _toHelpCmd;
	RTRPOBObjMenuItem _objItem;
	RTRPOBHelpMenuItem _helpItem;

};

class RTRPOBTopFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRPOBTopFrame(RTRProxyObjectBrowser&);

// Destructor
	virtual ~RTRPOBTopFrame();

// Operations -- from RTRDisplayFrame
	virtual void refresh();
		// REQUIRE : onTop()

protected:
// Data
	RTRAppLogo _logo;
	RTRPOBTopMenu _menu;
};

class RTRProxyObjectBrowser :
	public RTRMBrowserApplication
{ 
public:
// Constructor
	RTRProxyObjectBrowser(RTRProxyManagedObjectServerPool&);
		// _TAG Constructor

// Operations
	void browseObjects();
		// _TAG01 Operations

	void browseHelp();
		// _TAG01 Operations

protected:
// Data
	RTRDisplayFramePtr topFrame;
	RTRDisplayFramePtr dirFrame;
	RTRDisplayFramePtr helpFrame;
	RTRProxyManagedObjectServerPool& _pool;
}; 

#endif
