//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 16 1995"
// Version: 1.0

#ifndef _pvardsp_h
#define _pvardsp_h

#include "rtr/tabuldsp.h"
#include "rtr/prxymos.h"

#include "rtr/prxymvc.h"
#include "rtr/prxyms.h"
#include "rtr/prxymsc.h"
#include "rtr/prxymn.h"
#include "rtr/prxymln.h"
#include "rtr/prxymnc.h"
#include "rtr/prxymnr.h"
#include "rtr/prxymc.h"
#include "rtr/prxymg.h"
#include "rtr/prxymgc.h"
#include "rtr/prxymb.h"
#include "rtr/prxymbc.h"

class RTRProxyVariablesDisplay :
	public RTRTabularDisplay,
	public RTRProxyManagedObjectClient
{ 
public:
// Constructor
	RTRProxyVariablesDisplay(
		RTRDisplayFrame&, 
		RTRProxyManagedObjectPtr,
		int nc, 		// number of columns
		int nr,			// number of rows
		int cw,			// column width
		Fill f = TopToBottom,	// fill style for insertion
		int lw = -1		// optional label width
		);

// Destructor
	~RTRProxyVariablesDisplay();

// Event processing -- from RTRProxyManagedObjectClient
	virtual void processProxyManagedObjectError(
			const RTRProxyManagedObject&
			);
		// _TAG01 Event processing

	virtual void processProxyManagedObjectInfo(
			const RTRProxyManagedObject&
			);
		// The given ProxyManagedObject has new text
		// _TAG01 Event processing

	virtual void processProxyManagedObjectInService(
			const RTRProxyManagedObject&
			);
		// The given ProxyManagedObject is InService
		// _TAG01 Event processing

	virtual void processProxyManagedObjectRecovering(
			const RTRProxyManagedObject&
			);
		// The given ProxyManagedObject is in Auto Recovery
		// _TAG01 Event processing

	virtual void processProxyManagedObjectWaiting(
			const RTRProxyManagedObject&
			);
		// The given ProxyManagedObject is in Maunal Recovery
		// _TAG01 Event processing

	virtual void processProxyManagedObjectDead(
			const RTRProxyManagedObject&
			);
		// The given ProxyManagedObject is in Dead state.
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
// Data
	RTRProxyManagedObjectPtr _proxyObject;
	int _lw;
	int _cw;
}; 

class RTRProxyVariableSelection :
	public RTRMBDisplayRegion,
	public RTRProxyManagedVariableClient
{
public:
// Constructor
	RTRProxyVariableSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedVariable&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyVariableSelection();

// Attributes
	virtual const char *text();

	virtual RTRBOOL selectable() const ;

// Event processing
	virtual void processProxyManagedVariableDeleted(
			RTRProxyManagedVariable&
			);

	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);
	virtual void processProxyManagedVariableSync(
			RTRProxyManagedVariable&
			);
	virtual void processProxyManagedVariableError(
			RTRProxyManagedVariable&
			);

protected:
// Data
	const RTRDisplayFrame& _frame;
	RTRString _text;
	RTRProxyManagedVariablePtr _variable;
};

class RTRProxyBooleanSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyBooleanSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedBoolean&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyBooleanSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection();

};

class RTRProxyBooleanConfigSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyBooleanConfigSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedBooleanConfig&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyBooleanConfigSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection();

};

class RTRProxyCounterSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyCounterSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedCounter&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyCounterSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection();

};

class RTRProxyGaugeSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyGaugeSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedGauge&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyGaugeSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection() ;

};

class RTRProxyGaugeConfigSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyGaugeConfigSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedGaugeConfig&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyGaugeConfigSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection() ;

};

class RTRProxyNumericSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyNumericSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedNumeric&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyNumericSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection() ;

};

class RTRProxyLargeNumericSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyLargeNumericSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedLargeNumeric&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyLargeNumericSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection() ;

};

class RTRProxyStringSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyStringSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedString&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyStringSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection() ;

};

class RTRProxyNumericRangeSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyNumericRangeSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedNumericRange&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyNumericRangeSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection();

};

class RTRProxyNumericConfigSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyNumericConfigSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedNumericConfig&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyNumericConfigSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection();

};

class RTRProxyStringConfigSelection :
	public RTRProxyVariableSelection
{
public:
// Constructor
	RTRProxyStringConfigSelection(
			const RTRDisplayFrame&, 
			RTRProxyManagedStringConfig&, 
			int labelWidth,
			int w
			);

// Destructor
	virtual ~RTRProxyStringConfigSelection();

// Event processing
	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			);

// Operations 
	virtual void processSelection();

};

#endif
