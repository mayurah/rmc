//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/27/97"
// Version: 1.0

#ifndef _rtr_prxymbc_h
#define _rtr_prxymbc_h

#include "rtr/prxymb.h"

// Synopsis:
// #include"rtr/proxymo.h"
// 
// Description:
// A cloned (proxy) representation of a BooleanConfig variable.
// The base class for proxy boolean managed configuration variables.
// Inherits from RTRProxyManagedBoolean and provides additional services
// for accessing the stored and default values of a managed variable
// of type boolean config.  The managed application will accept modifications
// to this variable if the modifyEnabled() attribute is true.
// Accepted modifications are limited to setting the active value of the
// variable to true or false (the stored and default values cannot be
// modified).
//
// See Also:
// RTRProxyManagedVariableClient, RTRProxyManagedCounter, 
// RTRProxyManagedNumeric, RTRProxyManagedString,
// RTRManagedBoolean, RTRManagedGauge,
// RTRProxyManagedNumericRange, 
// RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
// RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRProxyManagedBoolean
//

class RTRProxyManagedBooleanConfig :
	public RTRProxyManagedBoolean
{ 
public:
// Constructor
	RTRProxyManagedBooleanConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedBooleanConfig();
		// _TAG Destructor

// Assignment
	inline RTRProxyManagedBooleanConfig& operator=(RTRBOOL rhs);
		// Set the current value to rhs.
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG01 Assignment

// Attributes
	inline RTRBOOL activeValue() const;
		// A synonym for value().
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes

	inline RTRBOOL storeValue() const;
		// The store value.
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes
	
	inline RTRBOOL factoryDefault() const;
		// The factory default value.
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes

protected:
// Data
	RTRBOOL _storeValue;
	RTRBOOL _factoryDefault;
		// Data
}; 

inline
RTRProxyManagedBooleanConfig& RTRProxyManagedBooleanConfig::operator=(RTRBOOL rhs)
{
	RTPRECONDITION( inSync() && !error() );
	RTPRECONDITION( modifyEnabled() );

	if ( rhs )
		set();
	else
		clear();
	return *this;
}

inline 
RTRBOOL RTRProxyManagedBooleanConfig::activeValue() const
{
	RTPRECONDITION( inSync() && !error() );

	return value();
}

inline 
RTRBOOL RTRProxyManagedBooleanConfig::storeValue() const
{
	RTPRECONDITION( inSync() && !error() );

	return _storeValue;
}

inline 
RTRBOOL RTRProxyManagedBooleanConfig::factoryDefault() const
{
	RTPRECONDITION( inSync() && !error() );

	return _factoryDefault;
}

typedef RTRObjRef<RTRProxyManagedBooleanConfig> RTRProxyManagedBooleanConfigPtr;

#endif
