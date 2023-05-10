//|---------------------------------------------------------------------------
//|					      Copyright (C) 2008 Reuters,		                --
//|			   U Chu Liang Building, 968 Rama IV Road, Bangkok 10500	    --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: N. Sotanakun
// Created: "Apr. 10 2008"
// Version: 1.0

#ifndef _rtr_prxymln_h
#define _rtr_prxymln_h

#include "rtr/prxymv.h"
#include "rtr/os.h"

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
// RTRProxyManagedNumeric,
// RTRProxyManagedNumericRange, 
// RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRProxyManagedVariable 
//

class RTRProxyManagedLargeNumeric :
	public RTRProxyManagedVariable
{ 
public:
// Constructor
	RTRProxyManagedLargeNumeric(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedLargeNumeric();
		// _TAG Destructor

// Comparison
	inline RTRBOOL operator==(RTR_I64 rhs) const;
		// REQUIRE: inSync() && !error()
		// _TAG01 Comparison

// Access
	inline RTR_I64 value() const;
		// The current value of this variable.
		// REQUIRE: inSync() && !error()
		// _TAG02 Access

// Transformation
	virtual RTRString toString() const;
		// The value of this variable represented as a string.
		// REQUIRE: inSync() && !error()
		// _TAG03 Transformation

	inline operator RTR_I64() const;
		// This variable as a long.
		// REQUIRE: inSync() && !error()
		// _TAG03 Transformation

// Static Data
	static const RTR_I64 LongMinNumeric;
	static const RTR_I64 LongMaxNumeric;
		// Static Data

protected:
// Data
	RTR_I64 _value;
		// Data
}; 

inline
RTRBOOL RTRProxyManagedLargeNumeric::operator==(RTR_I64 rhs) const
{
	RTPRECONDITION( inSync() && !error() );
	return _value == rhs;
}

inline 
RTR_I64 RTRProxyManagedLargeNumeric::value() const
{
	RTPRECONDITION( inSync() && !error() );
	return _value;
}

inline
RTRProxyManagedLargeNumeric::operator RTR_I64() const
{
	RTPRECONDITION( inSync() && !error() );
	return _value;
}

typedef RTRObjRef<RTRProxyManagedLargeNumeric> RTRProxyManagedLargeNumericPtr;

#endif
