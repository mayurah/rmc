//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jul. 01 1995"
// Version: 1.0
//
// Modified: "Nov. 07 1997"
// 	Changes for new variable types
// Author: T. Zhang
// Version: 2.0

#ifndef _parmdsp_h
#define _parmdsp_h

#include "rtr/prmdsp.h"
#include "rtr/timercmd.h"

class RTRVariableSelection;

class RTRManagedBoolean;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRBooleanDisplayFrame, 
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRBooleanDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRBooleanDisplay(
		RTRDisplayFrame&, 
		RTRManagedBoolean&, 
		RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRBooleanDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
        // _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedBoolean& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRParameterDisplay, RTRNumericParameterDisplay, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
//  RTRDisplayFrame
//

class RTRBooleanDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRBooleanDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedBoolean&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRBooleanDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRBooleanDisplay _display;
};

class RTRManagedBooleanConfig;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRBooleanDisplayFrame, 
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRBooleanConfigDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRBooleanConfigDisplay(
		RTRDisplayFrame&, 
		RTRManagedBooleanConfig&, 
		RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRBooleanConfigDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
        // _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedBooleanConfig& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRParameterDisplay, RTRNumericParameterDisplay, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
//  RTRDisplayFrame
//

class RTRBooleanConfigDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRBooleanConfigDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedBooleanConfig&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRBooleanConfigDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRBooleanConfigDisplay _display;
};

class RTRManagedCounter;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRBooleanDisplayFrame, 
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRCounterDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRCounterDisplay(
		RTRDisplayFrame&, 
		RTRManagedCounter&, 
		RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRCounterDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
        // _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedCounter& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRParameterDisplay, RTRNumericParameterDisplay, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
//  RTRDisplayFrame
//

class RTRCounterDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRCounterDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedCounter&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRCounterDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRCounterDisplay _display;
};

class RTRManagedNumeric;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRBooleanDisplayFrame, 
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRNumericDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRNumericDisplay(
		RTRDisplayFrame&, 
		RTRManagedNumeric&, 
		RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRNumericDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedNumeric& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRParameterDisplay, RTRNumericParameterDisplay, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
//  RTRDisplayFrame
//

class RTRNumericDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRNumericDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedNumeric&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRNumericDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRNumericDisplay _display;
};

class RTRManagedLargeNumeric;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRBooleanDisplayFrame, 
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRLargeNumericDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRLargeNumericDisplay(
		RTRDisplayFrame&, 
		RTRManagedLargeNumeric&, 
		RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRLargeNumericDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedLargeNumeric& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRParameterDisplay, RTRNumericParameterDisplay, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
//  RTRDisplayFrame
//

class RTRLargeNumericDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRLargeNumericDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedLargeNumeric&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRLargeNumericDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRLargeNumericDisplay _display;
};


class RTRManagedNumericRange;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRNumericParameterDisplayFrame, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRNumericRangeDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRNumericRangeDisplay(
		RTRDisplayFrame&, 
		RTRManagedNumericRange&, 
		RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRNumericRangeDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
        // _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedNumericRange& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRParameterDisplay, RTRNumericParameterDisplay, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
//  RTRDisplayFrame
//

class RTRNumericRangeDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRNumericRangeDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedNumericRange&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRNumericRangeDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRNumericRangeDisplay _display;
};

class RTRManagedNumericConfig;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRNumericParameterDisplayFrame, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRNumericConfigDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRNumericConfigDisplay(
		RTRDisplayFrame&, 
		RTRManagedNumericConfig&, 
		RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRNumericConfigDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
        // _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedNumericConfig& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRParameterDisplay, RTRNumericParameterDisplay, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
//  RTRDisplayFrame
//

class RTRNumericConfigDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRNumericConfigDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedNumericConfig&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRNumericConfigDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRNumericConfigDisplay _display;
};

class RTRManagedString;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRStringParameterDisplayFrame, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRStringDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRStringDisplay(
		RTRDisplayFrame&, 
		RTRManagedString&, 
		RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRStringDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
        // _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedString& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRParameterDisplay, RTRStringParameterDisplay, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
//  RTRDisplayFrame
//

class RTRStringDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRStringDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedString&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRStringDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRStringDisplay _display;
};

class RTRManagedStringConfig;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRStringParameterDisplayFrame, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRStringConfigDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRStringConfigDisplay(
		RTRDisplayFrame&, 
		RTRManagedStringConfig&,
		RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRStringConfigDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
        // _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedStringConfig& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//  RTRParameterDisplay, RTRStringParameterDisplay, 
//  RTRStringParameterDisplay, RTRStringParameterDisplayFrame
//
// Inherits:
//  RTRDisplayFrame
//

class RTRStringConfigDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRStringConfigDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedStringConfig&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRStringConfigDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRStringConfigDisplay _display;
};


class RTRManagedGauge;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRGaugeDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRGaugeDisplay(RTRDisplayFrame&, RTRManagedGauge&, RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRGaugeDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
        // _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedGauge& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//
// Inherits:
//  RTRDisplayFrame
//

class RTRGaugeDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRGaugeDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedGauge&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRGaugeDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRGaugeDisplay _display;
};
class RTRManagedGaugeConfig;

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//
// Inherits:
// 	RTRParameterDisplay, RTRTimerCmd 
//

class RTRGaugeConfigDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRGaugeConfigDisplay(
		RTRDisplayFrame&, 
		RTRManagedGaugeConfig&,
		RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRGaugeConfigDisplay();
		// _TAG Destructor

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
		// _TAG01 Event processing - from RTRInputDisplayClient

	virtual void processInputComplete(RTRInputDisplay&);
        // _TAG01 Event processing - from RTRInputDisplayClient

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();
		// _TAG02 Event processing - from RTRTimerCmd

protected:
// Data
	RTRManagedGaugeConfig& _parm;
	RTRVariableSelection& _varSel;
};

// Synopsis:
// #include"rtr/parmdsp.h
//
// Description:
// See Also:
//
// Inherits:
//  RTRDisplayFrame
//

class RTRGaugeConfigDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRGaugeConfigDisplayFrame(
			RTRMBrowserApplication&, 
			RTRManagedGaugeConfig&,
			RTRVariableSelection&);
		// _TAG Constructor

// Destructor
	virtual ~RTRGaugeConfigDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRGaugeConfigDisplay _display;
};


#endif
