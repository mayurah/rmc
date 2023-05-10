//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/27/97"
// Version: 1.0

#ifndef _rtr_prxymgc_h
#define _rtr_prxymgc_h

#include "rtr/prxymg.h"

// Synopsis:
// #include"rtr/proxymo.h"
// 
// Description:
// A cloned (proxy) representation of a GaugeConfig variable.
// The base class for proxy gauge managed configuration variables.
// Inherits from RTRProxyManagedGauge and provides additional services
// for accessing the stored and default values for the minimum
// and maximum values.
//
// See Also:
// RTRProxyManagedVariableClient, RTRProxyManagedCounter, 
// RTRProxyManagedNumeric, RTRProxyManagedString,
// RTRProxyManagedBoolean, RTRProxyManagedGauge,
// RTRProxyManagedNumericRange, 
// RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRProxyManagedGauge
//

class RTRProxyManagedGaugeConfig :
	public RTRProxyManagedGauge
{ 
public:
// Constructor
	RTRProxyManagedGaugeConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedGaugeConfig();
		// _TAG Destructor

// Attributes
	inline long minStoreValue() const;
		// The minimum store value.
		// REQUIRE: inSync() && !error()
		// ENSURE: minStoreValue() <= maxStoreValue()
		// _TAG01 Attributes

	inline long minFactoryDefault() const;
		// The minimum factory default value.
		// REQUIRE: inSync() && !error()
		// ENSURE: minFactoryDefault() <= maxFactoryDefault()
		// _TAG01 Attributes

	inline long maxStoreValue() const;
		// The maximum store value.
		// REQUIRE: inSync() && !error()
		// ENSURE: maxStoreValue() >= minStoreValue()
		// _TAG01 Attributes

	inline long maxFactoryDefault() const;
		// The maximum factory default value.
		// REQUIRE: inSync() && !error()
		// ENSURE: maxFactoryDefault() >= minFactoryDefault()
		// _TAG01 Attributes

protected:
// Data
	long _minStoreValue;
	long _minFactoryDefault;
	long _maxStoreValue;
	long _maxFactoryDefault;
		// Data
}; 

inline 
long RTRProxyManagedGaugeConfig::minStoreValue() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _minStoreValue <= _maxStoreValue );
	return _minStoreValue;
}

inline 
long RTRProxyManagedGaugeConfig::minFactoryDefault() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _minFactoryDefault <= _maxFactoryDefault );
	return _minFactoryDefault;
}

inline 
long RTRProxyManagedGaugeConfig::maxStoreValue() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _maxStoreValue >= _minStoreValue );
	return _maxStoreValue;
}

inline 
long RTRProxyManagedGaugeConfig::maxFactoryDefault() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _maxFactoryDefault >= _minFactoryDefault );
	return _maxFactoryDefault;
}

typedef RTRObjRef<RTRProxyManagedGaugeConfig> RTRProxyManagedGaugeConfigPtr;

#endif
