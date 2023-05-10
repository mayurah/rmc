//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/27/97"
// Version: 1.0

#ifndef _rtr_prxymb_h
#define _rtr_prxymb_h

#include "rtr/prxymv.h"

// Synopsis:
// #include"rtr/proxymo.h"
// 
// Description:
// A cloned (proxy) representation of a Boolean variable.
// The base class for proxy boolean managed variables.
// Inherits from RTRProxyManagedVariable and provides services
// for accessing and (conditionally) modifying a managed variable
// of type boolean.  The managed application will accept modifications
// to this variable if the modifyEnabled() attribute is true.
// Accepted modifications are limited to setting the value of the
// variable to true or false.
//
// See Also:
//    RTRProxyManagedVariableClient, RTRProxyManagedCounter, 
//    RTRProxyManagedNumeric, RTRProxyManagedString,
//    RTRProxyManagedGauge, RTRProxyManagedNumericRange, 
//    RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
//    RTRProxyManagedGaugeConfig, RTRProxyManagedBooleanConfig
//
// Inherits:
//    RTRProxyManagedVariable
//

class RTRProxyManagedBoolean :
	public RTRProxyManagedVariable
{ 
public:
// Constructor
	RTRProxyManagedBoolean(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedBoolean();
		// _TAG Destructor

// Comparison
	inline RTRBOOL operator==(RTRBOOL rhs) const;
		// REQUIRE: inSync() && !error()
		// _TAG01 Comparison

// Access
	inline RTRBOOL value() const;
		// REQUIRE: inSync() && !error()
		// _TAG02 Access

// Transformation
	virtual RTRString toString() const;
		// The value of this variable represented as a string.
		// REQUIRE: inSync() && !error()
		// _TAG03 Transformation

	operator RTRProxyManagedBooleanConfig&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::BooleanConfig
		// _TAG03 Transformation

	operator const RTRProxyManagedBooleanConfig&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::BooleanConfig
		// _TAG03 Transformation

// Attributes
	inline RTRBOOL modifyEnabled() const;
		// Is the consumer permitted to modify this variable ?
		// REQUIRE: inSync() && !error()
		// _TAG04 Attributes

// Assignment
	inline RTRProxyManagedBoolean& operator=(RTRBOOL rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG05 Assignment

// Operations
	virtual void set() = 0;
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operations

	virtual void clear() = 0;
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operations

protected:
// Data
	RTRBOOL _value;
	RTRBOOL _modifyEnabled;
		// Data
}; 

inline
RTRBOOL RTRProxyManagedBoolean::operator==(RTRBOOL rhs) const
{
	RTPRECONDITION( inSync() && !error() );

	return _value == rhs;
}

inline 
RTRBOOL RTRProxyManagedBoolean::value() const
{
	RTPRECONDITION( inSync() && !error() );

	return _value;
}

inline 
RTRBOOL RTRProxyManagedBoolean::modifyEnabled() const
{
	RTPRECONDITION( inSync() && !error() );

	return _modifyEnabled;
}

inline
RTRProxyManagedBoolean& RTRProxyManagedBoolean::operator=(RTRBOOL rhs)
{
	RTPRECONDITION( inSync() && !error() );

	if ( rhs )
		set();
	else
		clear();
	return *this;
}

typedef RTRObjRef<RTRProxyManagedBoolean> RTRProxyManagedBooleanPtr;

#endif
