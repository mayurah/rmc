//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 30 1996"
// Version: 1.0

#ifndef _rtr_prxymc_h
#define _rtr_prxymc_h

#include "rtr/prxymv.h"

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// A cloned (proxy) representation of a Counter variable.
// The base class for proxy counter managed variables.
// Inherits from RTRProxyManagedVariable and provides services
// for accessing and resetting (to 0) the value of a managed variable
// of type counter.  The managed application will always accept reset
// modification requests.
//
// See Also:
// RTRProxyManagedVariableClient,
// RTRProxyManagedGauge, RTRProxyManagedNumeric,
// RTRProxyManagedBoolean, RTRProxyManagedString,
// RTRProxyManagedNumericRange,
// RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRProxyManagedVariable
//

class RTRProxyManagedCounter :
	public RTRProxyManagedVariable
{ 
public:
// Constructor
	RTRProxyManagedCounter(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedCounter();
		// _TAG Destructor

// Comparison
	inline RTRBOOL operator==(unsigned long rhs) const;
		// REQUIRE: inSync() && !error()
		// _TAG01 Comparison

// Access
	inline unsigned long value() const;
		// The current value of this variable.
		// REQUIRE: inSync() && !error()
		// _TAG02 Access

// Transformation
	virtual RTRString toString() const;
		// The value of this variable represented as a string.
		// REQUIRE: inSync() && !error()
		// _TAG03 Transformation

	inline operator unsigned long() const;
		// This variable as an unsigned long.
		// REQUIRE: inSync() && !error()
		// _TAG03 Transformation

// Operations
	virtual void reset() = 0;
		// REQUIRE: inSync() && !error()
		// _TAG04 Operations

// Static Data
	static const unsigned long MinCounter;
	static const unsigned long MaxCounter;
		// Static Data
	
protected:
// Data
	unsigned long _value;
		// Data
}; 

inline
RTRBOOL RTRProxyManagedCounter::operator==(unsigned long rhs) const
{
	RTPRECONDITION( inSync() && !error() );

	return _value == rhs;
}

inline 
unsigned long RTRProxyManagedCounter::value() const
{
	RTPRECONDITION( inSync() && !error() );

	return _value;
}

inline
RTRProxyManagedCounter::operator unsigned long() const
{
	RTPRECONDITION( inSync() && !error() );

	return _value;
}

typedef RTRObjRef<RTRProxyManagedCounter> RTRProxyManagedCounterPtr;

#endif
