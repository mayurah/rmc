//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jul. 01 1995"
// Version: 1.0

#ifndef _pparmdsp_h
#define _pparmdsp_h

#include "rtr/ffrmdsp.h"
#include "rtr/timercmd.h"
#include "rtr/chinptd.h"
#include "rtr/prmdsp.h"

class RTRProxyManagedBoolean;
class RTRProxyManagedBooleanConfig;
class RTRProxyManagedCounter;
class RTRProxyManagedGauge;
class RTRProxyManagedGaugeConfig;
class RTRProxyManagedNumeric;
class RTRProxyManagedLargeNumeric;
class RTRProxyManagedNumericConfig;
class RTRProxyManagedNumericRange;
class RTRProxyManagedString;
class RTRProxyManagedStringConfig;

class RTRProxyBooleanDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyBooleanDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedBoolean&
			);

// Destructor
	virtual ~RTRProxyBooleanDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedBoolean& _var;
};

class RTRProxyBooleanConfigDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyBooleanConfigDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedBooleanConfig&
			);

// Destructor
	virtual ~RTRProxyBooleanConfigDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedBooleanConfig& _var;
};

class RTRProxyCounterDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyCounterDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedCounter&
			);

// Destructor
	virtual ~RTRProxyCounterDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedCounter& _var;
};

class RTRProxyGaugeDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyGaugeDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedGauge&
			);

// Destructor
	virtual ~RTRProxyGaugeDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedGauge& _var;
};

class RTRProxyGaugeConfigDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyGaugeConfigDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedGaugeConfig&
			);

// Destructor
	virtual ~RTRProxyGaugeConfigDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedGaugeConfig& _var;
};

class RTRProxyNumericDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyNumericDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedNumeric&
			);

// Destructor
	virtual ~RTRProxyNumericDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedNumeric& _var;
};


class RTRProxyLargeNumericDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyLargeNumericDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedLargeNumeric&
			);

// Destructor
	virtual ~RTRProxyLargeNumericDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedLargeNumeric& _var;
};

class RTRProxyNumericConfigDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyNumericConfigDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedNumericConfig&
			);

// Destructor
	virtual ~RTRProxyNumericConfigDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedNumericConfig& _var;
};

class RTRProxyNumericRangeDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyNumericRangeDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedNumericRange&
			);

// Destructor
	virtual ~RTRProxyNumericRangeDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedNumericRange& _var;
};

class RTRProxyStringDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyStringDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedString&
			);

// Destructor
	virtual ~RTRProxyStringDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedString& _var;
};

class RTRProxyStringConfigDisplay :
	public RTRParameterDisplay,
	public RTRTimerCmd
{
public:
// Constructor
	RTRProxyStringConfigDisplay(
			RTRDisplayFrame&,
			RTRProxyManagedStringConfig&
			);

// Destructor
	virtual ~RTRProxyStringConfigDisplay();

// Event processing - from RTRInputDisplayClient
	virtual void processInputAborted(RTRInputDisplay&);
	virtual void processInputComplete(RTRInputDisplay&);

// Event processing - from RTRTimerCmd
	virtual void processTimerEvent();

protected:
// Data
	RTRProxyManagedStringConfig& _var;
};

class RTRProxyBooleanDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyBooleanDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedBoolean&
			);

// Destructor
	virtual ~RTRProxyBooleanDisplayFrame();

protected:
// Data
	RTRProxyBooleanDisplay _display;
};

class RTRProxyBooleanConfigDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyBooleanConfigDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedBooleanConfig&
			);

// Destructor
	virtual ~RTRProxyBooleanConfigDisplayFrame();

protected:
// Data
	RTRProxyBooleanConfigDisplay _display;
};

class RTRProxyCounterDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyCounterDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedCounter&
			);

// Destructor
	virtual ~RTRProxyCounterDisplayFrame();

protected:
// Data
	RTRProxyCounterDisplay _display;
};

class RTRProxyGaugeDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyGaugeDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedGauge&
			);

// Destructor
	virtual ~RTRProxyGaugeDisplayFrame();

protected:
// Data
	RTRProxyGaugeDisplay _display;
};

class RTRProxyGaugeConfigDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyGaugeConfigDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedGaugeConfig&
			);

// Destructor
	virtual ~RTRProxyGaugeConfigDisplayFrame();

protected:
// Data
	RTRProxyGaugeConfigDisplay _display;
};

class RTRProxyNumericDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyNumericDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedNumeric&
			);

// Destructor
	virtual ~RTRProxyNumericDisplayFrame();

protected:
// Data
	RTRProxyNumericDisplay _display;
};

class RTRProxyLargeNumericDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyLargeNumericDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedLargeNumeric&
			);

// Destructor
	virtual ~RTRProxyLargeNumericDisplayFrame();

protected:
// Data
	RTRProxyLargeNumericDisplay _display;
};

class RTRProxyNumericConfigDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyNumericConfigDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedNumericConfig&
			);

// Destructor
	virtual ~RTRProxyNumericConfigDisplayFrame();

protected:
// Data
	RTRProxyNumericConfigDisplay _display;
};

class RTRProxyNumericRangeDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyNumericRangeDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedNumericRange&
			);

// Destructor
	virtual ~RTRProxyNumericRangeDisplayFrame();

protected:
// Data
	RTRProxyNumericRangeDisplay _display;
};

class RTRProxyStringDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyStringDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedString&
			);

// Destructor
	virtual ~RTRProxyStringDisplayFrame();

protected:
// Data
	RTRProxyStringDisplay _display;
};

class RTRProxyStringConfigDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRProxyStringConfigDisplayFrame(
			RTRMBrowserApplication&, 
			RTRProxyManagedStringConfig&
			);

// Destructor
	virtual ~RTRProxyStringConfigDisplayFrame();

protected:
// Data
	RTRProxyStringConfigDisplay _display;
};

#endif
