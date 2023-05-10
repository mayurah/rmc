//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "Jun. 19 1996"
// Version: 1.0

#ifndef _rtr_prxymsc_h
#define _rtr_prxymsc_h

#include "rtr/prxyms.h"

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// A cloned (proxy) representation of a StringConfig variable.
// The base class for proxy string managed configuration variables.
// Inherits from RTRProxyManagedString and provides additional services
// for accessing the stored and default values.
//
// See Also:
// RTRProxyManagedVariableClient, RTRProxyManagedCounter,
// RTRProxyManagedGauge, RTRProxyManagedNumeric, 
// RTRProxyManagedBoolean, RTRProxyManagedString,
// RTRProxyManagedNumericRange, 
// RTRProxyManagedNumericConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRProxyManagedString
//

class RTRProxyManagedStringConfig :
	public RTRProxyManagedString
{ 
public:
// Constructor
	RTRProxyManagedStringConfig(
			RTRProxyManagedObject&, 
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedStringConfig();
		// _TAG Destructor

// Access
	inline const RTRString& activeValue() const;
		// A synonym for value().
		// REQUIRE: inSync() && !error()
		// _TAG01 Access

// Attributes
	inline const RTRString& storeValue() const;
		// The store value.
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes

	inline const RTRString& factoryDefault() const;
		// The factory default value.
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes

	RTRBOOL hasStore() const;
		// Is the variable a client of a RTRVariableConfig ?
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes

	RTRBOOL isStoreActive() const;
		// Is the RTRVariableConfig in an active state ?
		// REQUIRE: inSync() && !error()
		// REQUIRE: hasStore()
		// _TAG02 Attributes

	RTRBOOL isStoreClassConfig() const;
		// Is the RTRVariableConfig's context a class config ?
		// REQUIRE: inSync() && !error()
		// REQUIRE: hasStore()
		// _TAG02 Attributes

	RTRBOOL isStoreInstanceConfig() const;
		// Is the RTRVariableConfig's context a instance config ?
		// REQUIRE: inSync() && !error()
		// REQUIRE: hasStore()
		// _TAG02 Attributes

// Assignment
	inline RTRProxyManagedStringConfig& operator=(const RTRString& rhs);
		// Assigns the value of this variable to rhs.
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG03 Assignment

	inline RTRProxyManagedStringConfig& operator=(const char *rhs);
		// Assigns the value of this variable to rhs.
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG03 Assignment

protected:
// Data
	RTRString _storeValue;
	RTRString _factoryDefault;
	int       _storeState;
		// Data
}; 

inline 
const RTRString& RTRProxyManagedStringConfig::activeValue() const
{
	RTPRECONDITION( inSync() && !error() );
	return value();
}

inline 
const RTRString& RTRProxyManagedStringConfig::storeValue() const
{
	RTPRECONDITION( inSync() && !error() );
	return _storeValue;
}

inline 
const RTRString& RTRProxyManagedStringConfig::factoryDefault() const
{
	RTPRECONDITION( inSync() && !error() );
	return _factoryDefault;
}

inline
RTRProxyManagedStringConfig&
RTRProxyManagedStringConfig::operator=(const RTRString& rhs)
{
	RTPRECONDITION( inSync() && !error() );
	RTPRECONDITION( _modifyEnabled );
	set(rhs);
	return *this;
}

inline
RTRProxyManagedStringConfig&
RTRProxyManagedStringConfig::operator=(const char *rhs)
{
	RTPRECONDITION( inSync() && !error() );
	RTPRECONDITION( _modifyEnabled );
	set(rhs);
	return *this;
}

typedef RTRObjRef<RTRProxyManagedStringConfig> RTRProxyManagedStringConfigPtr;

#endif
