//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 16 1995"
// Version: 1.0

#ifndef _vardsp_h
#define _vardsp_h

#include "rtr/tabuldsp.h"
#include "rtr/mod.h"

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//	RTRVariableSelection, RTRCounterSelection, RTRNumericSelection, 
//	RTRGaugeSelection, RTRStringSelection, RTRNumericParameterSelection,
//	RTRStringParameterSelection, RTRNumericConfigSelection, 
//	RTRStringConfigSelection
//
// Inherits:
//	RTRTabularDisplay, RTRManagedObjDirClient
//

class RTRVariablesDisplay :
	public RTRTabularDisplay,
	public RTRManagedObjDirClient
{ 
public:
// Constructor
	RTRVariablesDisplay(
		RTRDisplayFrame&, 
		RTRManagedObject&,
		int nc, 		// number of columns
		int nr,			// number of rows
		int cw,			// column width
		Fill f = TopToBottom,	// fill style for insertion
		int lw = -1		// optional label width
		);
		// _TAG Constructor

// Destructor
	~RTRVariablesDisplay();
		// _TAG Destructor

// Event processing
	virtual void processManagedObjectRemoved(
					RTRManagedObjectDirectory&, 
					RTRManagedObject&);
		// _TAG01 Event processing

protected:
// Data
	RTRManagedObject *_managedObject;

}; 

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRCounterSelection, RTRNumericSelection, 
//  RTRGaugeSelection, RTRStringSelection, RTRNumericParameterSelection,
//  RTRStringParameterSelection, RTRNumericConfigSelection, 
//  RTRStringConfigSelection
//
// Inherits:
// 	RTRMBDisplayRegion, RTRMVariableClient
//

class RTRVariableSelection :
	public RTRMBDisplayRegion,
	public RTRMVariableClient
{
public:
// Constructor
	RTRVariableSelection(
			const RTRDisplayFrame&, 
			RTRManagedVariable&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRVariableSelection();
		// _TAG Destructor

// Attributes
	inline RTRBOOL hasVariable() const;
		// _TAG01 Attributes

	virtual const char *text();
		// _TAG01 Attributes

	virtual RTRBOOL selectable() const ;
		// _TAG01 Attributes

// Event processing
	virtual void processVariableDelete(RTRManagedVariable&);
		// _TAG02 Event processing

	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG02 Event processing

protected:
// Data
	const RTRDisplayFrame& _frame;
	RTRString _text;
	RTRManagedVariable *_variable;
};

inline 
RTRBOOL RTRVariableSelection::hasVariable() const
{
	return (_variable!=0);
}


// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRNumericSelection, 
//  RTRGaugeSelection, RTRStringSelection, RTRNumericParameterSelection,
//  RTRStringParameterSelection, RTRNumericConfigSelection, 
//  RTRStringConfigSelection
//
// Inherits:
//	RTRVariableSelection 
//

class RTRBooleanSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRBooleanSelection(
			const RTRDisplayFrame&, 
			RTRManagedBoolean&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRBooleanSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection() ;
		// _TAG02 Operations
};

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRNumericSelection, 
//  RTRGaugeSelection, RTRStringSelection, RTRNumericParameterSelection,
//  RTRStringParameterSelection, RTRNumericConfigSelection, 
//  RTRStringConfigSelection
//
// Inherits:
//	RTRVariableSelection 
//

class RTRBooleanConfigSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRBooleanConfigSelection(
			const RTRDisplayFrame&, 
			RTRManagedBooleanConfig&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRBooleanConfigSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection() ;
		// _TAG02 Operations
};

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRNumericSelection, 
//  RTRGaugeSelection, RTRStringSelection, RTRNumericParameterSelection,
//  RTRStringParameterSelection, RTRNumericConfigSelection, 
//  RTRStringConfigSelection
//
// Inherits:
//	RTRVariableSelection 
//

class RTRCounterSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRCounterSelection(
			const RTRDisplayFrame&, 
			RTRManagedCounter&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCounterSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection() ;
		// _TAG02 Operations
};

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRCounterSelection, 
//  RTRGaugeSelection, RTRStringSelection, RTRNumericParameterSelection,
//  RTRStringParameterSelection, RTRNumericConfigSelection, 
//  RTRStringConfigSelection
//
// Inherits:
//  RTRVariableSelection 
//

class RTRNumericSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRNumericSelection(
			const RTRDisplayFrame&, 
			RTRManagedNumeric&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRNumericSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection() ;
		// _TAG02 Operations

};


// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRCounterSelection, 
//  RTRGaugeSelection, RTRStringSelection, RTRNumericParameterSelection,
//  RTRStringParameterSelection, RTRNumericConfigSelection, 
//  RTRStringConfigSelection
//
// Inherits:
//  RTRVariableSelection 
//

class RTRLargeNumericSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRLargeNumericSelection(
			const RTRDisplayFrame&, 
			RTRManagedLargeNumeric&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRLargeNumericSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection() ;
		// _TAG02 Operations

};

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRCounterSelection, 
//  RTRNumericSelection, RTRStringSelection, RTRNumericParameterSelection,
//  RTRStringParameterSelection, RTRNumericConfigSelection, 
//  RTRStringConfigSelection
//
// Inherits:
//  RTRVariableSelection 
//

class RTRGaugeSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRGaugeSelection(
			const RTRDisplayFrame&, 
			RTRManagedGauge&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRGaugeSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection() ;
		// _TAG02 Operations

};

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRCounterSelection, 
//  RTRNumericSelection, RTRStringSelection, RTRNumericParameterSelection,
//  RTRStringParameterSelection, RTRNumericConfigSelection, 
//  RTRStringConfigSelection
//
// Inherits:
//  RTRVariableSelection 
//

class RTRGaugeConfigSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRGaugeConfigSelection(
			const RTRDisplayFrame&, 
			RTRManagedGaugeConfig&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRGaugeConfigSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection() ;
		// _TAG02 Operations

};

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRCounterSelection, 
//  RTRNumericSelection, RTRGaugeSelection, RTRNumericParameterSelection,
//  RTRStringParameterSelection, RTRNumericConfigSelection, 
//  RTRStringConfigSelection
//
// Inherits:
//  RTRVariableSelection 
//

class RTRStringSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRStringSelection(
			const RTRDisplayFrame&, 
			RTRManagedString&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRStringSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection() ;
		// _TAG02 Operations

};

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRCounterSelection, 
//  RTRNumericSelection, RTRGaugeSelection, RTRStringSelection,
//  RTRStringParameterSelection, RTRNumericConfigSelection, 
//  RTRStringConfigSelection
//
// Inherits:
//  RTRVariableSelection 
//

class RTRNumericRangeSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRNumericRangeSelection(
			const RTRDisplayFrame&, 
			RTRManagedNumericRange&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRNumericRangeSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection();
		// _TAG02 Operations

};

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRCounterSelection, 
//  RTRNumericSelection, RTRGaugeSelection, RTRStringSelection,
//  RTRNumericParameterSelection, RTRStringParameterSelection, 
//  RTRStringConfigSelection
//
// Inherits:
//  RTRVariableSelection 
//

class RTRNumericConfigSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRNumericConfigSelection(
			const RTRDisplayFrame&, 
			RTRManagedNumericConfig&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRNumericConfigSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection();
		// _TAG02 Operations

};

// Synopsis:
// #include"rtr/vardsp.h"
//
// Description:
// See Also:
//  RTRVariablesDisplay, RTRCounterSelection, 
//  RTRNumericSelection, RTRGaugeSelection, RTRStringSelection,
//  RTRNumericParameterSelection, RTRStringParameterSelection, 
//  RTRNumericConfigSelection
//
// Inherits:
//  RTRVariableSelection 
//

class RTRStringConfigSelection :
	public RTRVariableSelection
{
public:
// Constructor
	RTRStringConfigSelection(
			const RTRDisplayFrame&, 
			RTRManagedStringConfig&, 
			int labelWidth,
			int w
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRStringConfigSelection();
		// _TAG Destructor

// Event processing
	virtual void processVariableChange(RTRManagedVariable&);
		// _TAG01 Event processing

// Operations 
	virtual void processSelection();
		// _TAG02 Operations

};

#endif
