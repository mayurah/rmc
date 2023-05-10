//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "Jun. 18 1996"
// Version: 1.0

#ifndef _rtr_prxymnc_h
#define _rtr_prxymnc_h

#include "rtr/prxymn.h"

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// A cloned (proxy) representation of a NumericConfig variable.
// The base class for proxy numeric managed configuration variables.
// Inherits from RTRProxyManagedNumeric and provides additional services
// for accessing the stored and default values and for modifying
// (conditionally) the active value.
//
// If modifyEnabled() is True, then managing applications are permitted
// to modify the active value.
// Note: The active values of configuration variables are not persistent.
//
// See Also:
// RTRProxyManagedVariableClient,
// RTRProxyManagedCounter, RTRProxyManagedGauge,
// RTRProxyManagedNumeric, RTRProxyManagedString,
// RTRProxyManagedBoolean,
// RTRProxyManagedNumericRange, RTRProxyManagedStringConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRProxyManagedNumeric
//

class RTRProxyManagedNumericConfig :
	public RTRProxyManagedNumeric
{ 
public:
// Constructor
	RTRProxyManagedNumericConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedNumericConfig();
		// _TAG Destructor

// Access
	inline long activeValue() const;
		// A synonym for value().
		// REQUIRE: inSync() && !error()
		// _TAG01 Access

// Attributes
	inline long minValue() const;
		// The minimum value which may be assigned to this variable.
		// REQUIRE: inSync() && !error()
		// ENSURE: minValue() <= maxValue()
		// ENSURE: minValue() <= value()
		// _TAG02 Attributes

	inline long maxValue() const;
		// The maximum value which may be assigned to this variable.
		// REQUIRE: inSync() && !error()
		// ENSURE: maxValue() >= minValue()
		// ENSURE: maxValue() >= value()
		// _TAG02 Attributes

	inline long storeValue() const;
		// The store value
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes

	inline long factoryDefault() const;
		// The factory default value for this variable.
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes

	inline RTRBOOL modifyEnabled() const;
		// Is the consumer permitted to modify this variable ?
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
	inline RTRProxyManagedNumericConfig& operator=(long rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: rhs >= minValue()
		// REQUIRE: rhs <= maxValue()
		// _TAG03 Assignment

// Operations
	virtual void set(long newValue) = 0;
		// A synonym for operator=()
		// REQUIRE: inSync() && !error()
		// REQUIRE: newValue >= minValue()
		// REQUIRE: newValue <= maxValue()
		// _TAG04 Operations

protected:
// Data
	long _storeValue;
	long _factoryDefault;
	long _minValue;
	long _maxValue;
	int  _storeState;
	RTRBOOL _modifyEnabled;
		// Data
}; 

inline 
long RTRProxyManagedNumericConfig::activeValue() const
{
	RTPRECONDITION( inSync() && !error() );
	return value();
}

inline 
long RTRProxyManagedNumericConfig::minValue() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _minValue <= _maxValue );
	RTPOSTCONDITION( _minValue <= _value );
	return _minValue;
}

inline 
long RTRProxyManagedNumericConfig::maxValue() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _maxValue >= _minValue );
	RTPOSTCONDITION( _maxValue >= _value );
	return _maxValue;
}

inline 
long RTRProxyManagedNumericConfig::storeValue() const
{
	RTPRECONDITION( inSync() && !error() );
	return _storeValue;
}

inline 
long RTRProxyManagedNumericConfig::factoryDefault() const
{
	RTPRECONDITION( inSync() && !error() );
	return _factoryDefault;
}

inline
RTRBOOL RTRProxyManagedNumericConfig::modifyEnabled() const
{
	RTPRECONDITION( inSync() && !error() );
	return _modifyEnabled;
}

inline
RTRProxyManagedNumericConfig&
RTRProxyManagedNumericConfig::operator=(long rhs)
{
	RTPRECONDITION( inSync() && !error() );
	RTPRECONDITION( rhs >= _minValue );
	RTPRECONDITION( rhs <= _maxValue );
	set(rhs);
	return *this;
}

typedef RTRObjRef<RTRProxyManagedNumericConfig> RTRProxyManagedNumericConfigPtr;

#endif
