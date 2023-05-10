//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "Jun. 25 1996"
// Version: 1.0

#ifndef _rtr_prxymnr_h
#define _rtr_prxymnr_h

#include "rtr/prxymn.h"

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// A cloned (proxy) representation of a NumericRange variable.
// The base class for proxy numeric range managed variables.
// Inherits from RTRProxyManagedNumeric and provides additional services
// for accessing and modifying (conditionally) the current value.
// It also provides a fixed range of values that the variable can assume.
//
// If modifyEnabled() is True, the managing applications are permitted
// to modify the current value.  The new value must be within the
// specified range (minValue()/maxValue()).
//
// See Also:
// RTRProxyManagedVariableClient, RTRProxyManagedCounter,
// RTRProxyManagedGauge, RTRProxyManagedNumeric, 
// RTRProxyManagedBoolean, RTRProxyManagedString,
// RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRProxyManagedNumeric
//

class RTRProxyManagedNumericRange :
	public RTRProxyManagedNumeric
{ 
public:
// Constructor
	RTRProxyManagedNumericRange(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedNumericRange();
		// _TAG Destructor

// Attributes
	inline long minValue() const;
		// The minimum value which may be assigned to this variable.
		// REQUIRE: inSync() && !error()
		// ENSURE: minValue() <= maxValue()
		// ENSURE: minValue() <= value()
		// _TAG01 Attributes

	inline long maxValue() const;
		// The maximum value which may be assigned to this variable.
		// REQUIRE: inSync() && !error()
		// ENSURE: maxValue() >= minValue()
		// ENSURE: maxValue() >= value()
		// _TAG01 Attributes

// Assignment
	inline RTRProxyManagedNumericRange& operator=(long rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: rhs >= minValue()
		// REQUIRE: rhs <= maxValue()
		// _TAG02 Assignment

// Operations
	virtual void set(long newValue) = 0;
		// A synonym for operator=()
		// REQUIRE: inSync() && !error()
		// REQUIRE: newValue >= minValue()
		// REQUIRE: newValue <= maxValue()
		// _TAG02 Operations

protected:
// Data
	long _minValue;
	long _maxValue;
		// Data
}; 

inline 
long RTRProxyManagedNumericRange::minValue() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _minValue <= _maxValue );
	RTPOSTCONDITION( _minValue <= _value );
	return _minValue;
}

inline 
long RTRProxyManagedNumericRange::maxValue() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _maxValue >= _minValue );
	RTPOSTCONDITION( _maxValue >= _value );
	return _maxValue;
}

inline 
RTRProxyManagedNumericRange& 
RTRProxyManagedNumericRange::operator=(long rhs)
{
	RTPRECONDITION( inSync() && !error() );
	RTPRECONDITION ( rhs >= minValue() );
	RTPRECONDITION ( rhs <= maxValue() );
	set(rhs);
	return *this;
}

typedef RTRObjRef<RTRProxyManagedNumericRange> RTRProxyManagedNumericRangePtr;

#endif
