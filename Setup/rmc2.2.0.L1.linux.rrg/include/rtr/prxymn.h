//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 30 1996"
// Version: 1.0

#ifndef _rtr_prxymn_h
#define _rtr_prxymn_h

#include "rtr/prxymv.h"

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// A cloned (proxy) representation of a Numeric variable.
// The base class for proxy numeric managed variables.
// Inherits from RTRProxyManagedVariable and provides services
// for accessing the current value of the variable.
//
// See Also:
// RTRProxyManagedVariableClient, RTRProxyManagedCounter, 
// RTRProxyManagedGauge, RTRProxyManagedString,
// RTRProxyManagedBoolean,
// RTRProxyManagedNumericRange, 
// RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRProxyManagedVariable 
//

class RTRProxyManagedNumeric :
	public RTRProxyManagedVariable
{ 
public:
// Constructor
	RTRProxyManagedNumeric(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedNumeric();
		// _TAG Destructor

// Comparison
	inline RTRBOOL operator==(long rhs) const;
		// REQUIRE: inSync() && !error()
		// _TAG01 Comparison

// Access
	inline long value() const;
		// The current value of this variable.
		// REQUIRE: inSync() && !error()
		// _TAG02 Access

// Transformation
	virtual RTRString toString() const;
		// The value of this variable represented as a string.
		// REQUIRE: inSync() && !error()
		// _TAG03 Transformation

	inline operator long() const;
		// This variable as a long.
		// REQUIRE: inSync() && !error()
		// _TAG03 Transformation

	operator RTRProxyManagedGauge&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::Gauge ||
		//	type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG03 Transformation

	operator const RTRProxyManagedGauge&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::Gauge ||
		//	type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG03 Transformation

	operator RTRProxyManagedGaugeConfig&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG03 Transformation

	operator const RTRProxyManagedGaugeConfig&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG03 Transformation

	operator RTRProxyManagedNumericConfig&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::NumericConfig
		// _TAG03 Transformation

	operator const RTRProxyManagedNumericConfig&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::NumericConfig
		// _TAG03 Transformation

	operator RTRProxyManagedNumericRange&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::NumericRange
		// _TAG03 Transformation

	operator const RTRProxyManagedNumericRange&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::NumericRange
		// _TAG03 Transformation

// Static Data
	static const long MinNumeric;
	static const long MaxNumeric;
		// Static Data

protected:
// Data
	long _value;
		// Data
}; 

inline
RTRBOOL RTRProxyManagedNumeric::operator==(long rhs) const
{
	RTPRECONDITION( inSync() && !error() );
	return _value == rhs;
}

inline 
long RTRProxyManagedNumeric::value() const
{
	RTPRECONDITION( inSync() && !error() );
	return _value;
}

inline
RTRProxyManagedNumeric::operator long() const
{
	RTPRECONDITION( inSync() && !error() );
	return _value;
}

typedef RTRObjRef<RTRProxyManagedNumeric> RTRProxyManagedNumericPtr;

#endif
