//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 30 1996"
// Version: 1.0

#ifndef _rtr_prxyms_h
#define _rtr_prxyms_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#endif
#include <string.h>

#include "rtr/prxymv.h"

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// A cloned (proxy) representation of a String variable.
// The base class for proxy string managed variables.
// Inherits from RTRProxyManagedVariable and provides additional services
// for accessing and modifying (conditionally) the current value.
//
// If modifyEnabled() is True, then managing applications are permitted
// to modify the current value.
//
// See Also:
// RTRProxyManagedVariableClient, RTRProxyManagedCounter,
// RTRProxyManagedGauge, RTRProxyManagedNumeric,
// RTRProxyManagedBoolean,
// RTRProxyManagedNumericRange,
// RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRProxyManagedVariable
//

class RTRProxyManagedString :
	public RTRProxyManagedVariable
{ 
public:
// Constructor
	RTRProxyManagedString(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedString();
		// _TAG Destructor

// Access
	inline const RTRString& value() const;
		// The current value of this variable.
		// REQUIRE: inSync() && !error()
		// _TAG01 Access

// Transformation
	virtual RTRString toString() const;
		// The value of this variable represented as a string.
		// REQUIRE: inSync() && !error()
		// _TAG02 Transformation

	inline operator const char *() const;
		// This variable as a C string (null terminated).
		// REQUIRE: inSync() && !error()
		// _TAG02 Transformation

	operator RTRProxyManagedStringConfig&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::StringConfig
		// _TAG02 Transformation

	operator const RTRProxyManagedStringConfig&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::StringConfig
		// _TAG02 Transformation

// Comparison
	inline RTRBOOL operator==(const char *) const;
		// REQUIRE: inSync() && !error()
		// _TAG03 Comparison

// Attributes
	inline RTRBOOL modifyEnabled() const;
		// Is the managing application permitted to modify this variable ?
		// REQUIRE: inSync() && !error()
		// _TAG04 Attributes

// Assignment
	inline RTRProxyManagedString& operator=(const RTRString& rhs);
		// Assigns the value of this variable to rhs.
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG05 Assignment

	inline RTRProxyManagedString& operator=(const char *rhs);
		// Assigns the value of this variable to rhs.
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG05 Assignment

// Operations
	virtual void set( const RTRString& newValue ) = 0;
		// A synonym for operator=()
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operations

	virtual void set( const char* newValue ) = 0;
		// A synonym for operator=()
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operations
	
protected:
// Data
	RTRString _value;
	RTRBOOL _modifyEnabled;
		// Data
}; 

inline 
const RTRString& RTRProxyManagedString::value() const
{
	RTPRECONDITION( inSync() && !error() );
	return _value;
}

inline
RTRBOOL RTRProxyManagedString::operator==(const char *rhs) const
{
	RTPRECONDITION( inSync() && !error() );
	return (strcmp(_value, rhs) == 0) ? RTRTRUE : RTRFALSE;
}

inline
RTRProxyManagedString::operator const char *() const
{
	RTPRECONDITION( inSync() && !error() );
	return (const char *)_value;
}

inline
RTRBOOL RTRProxyManagedString::modifyEnabled() const
{
	RTPRECONDITION( inSync() && !error() );
	return _modifyEnabled;
}

inline
RTRProxyManagedString& RTRProxyManagedString::operator=(const RTRString& rhs)
{
	RTPRECONDITION( inSync() && !error() );
	RTPRECONDITION( _modifyEnabled );
	set(rhs);
	return *this;
}

inline
RTRProxyManagedString& RTRProxyManagedString::operator=(const char *rhs)
{
	RTPRECONDITION( inSync() && !error() );
	RTPRECONDITION( _modifyEnabled );
	set(rhs);
	return *this;
}

typedef RTRObjRef<RTRProxyManagedString> RTRProxyManagedStringPtr;

#endif
