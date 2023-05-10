//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "Jun. 25 1996"
// Version: 1.0

#ifndef _rtr_prxymg_h
#define _rtr_prxymg_h

#include "rtr/prxymn.h"

// Synopsis:
// #include"rtr/proxymo.h"
// 
// Description:
// A cloned (proxy) representation of a Gauge variable.
// The base class for proxy gauge managed variables.
// Inherits from RTRProxyManagedNumeric and provides additional services
// for accessing and modifying a managed variable of type gauge.
//
// In addition to the current value, this variable also contains
// a minimum, maximum, low water mark and high water mark values.
// The low and high water marks indicate the lowest and highest
// values that the variable has assumed since the variable was
// created.
//
// The minimum and maximum values specify a desired range of
// values that the variable can assume.
//
// If modifyEnabled() is False, then the values that the variable
// can assume are strictly enforced.  The value will always 
// be between minValue() and maxValue() (inclusive).  Note,
// however, that the min and max values can be changed by
// the producer, but the current value will be
// within the new range.  When modifyEnabled() is False, then
// consumers are not permitted to modify the variable.
//
// If modifyEnabled() is True, then the consumer
// is permitted to change the range (the min/max values).
// In this case, the current value does not have to be within
// the min/max range. Note: The consumer cannot modify
// the current value.
//
// See Also:
// RTRProxyManagedVariableClient, RTRProxyManagedCounter, 
// RTRProxyManagedNumeric, RTRProxyManagedString,
// RTRProxyManagedBoolean,
// RTRProxyManagedNumericRange, 
// RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRProxyManagedNumeric
//

class RTRProxyManagedGauge :
	public RTRProxyManagedNumeric
{ 
public:
// Constructor
	RTRProxyManagedGauge(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedGauge();
		// _TAG Destructor

// Transformation
	operator RTRProxyManagedGaugeConfig&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG01 Transformation

	operator const RTRProxyManagedGaugeConfig&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG01 Transformation

// Attributes
	inline long minValue() const;
		// The minimum value which may be assigned to this variable.
		// REQUIRE: inSync() && !error()
		// ENSURE: minValue() <= maxValue()
		// ENSURE: (minValue() <= value()) || modifyEnabled()
		// ENSURE: (minValue() <= highWaterMark()) || modifyEnabled()
		// _TAG02 Attributes

	inline long maxValue() const;
		// The maximum value which may be assigned to this variable.
		// REQUIRE: inSync() && !error()
		// ENSURE: maxValue() >= minValue()
		// ENSURE: (maxValue() >= value()) || modifyEnabled()
		// ENSURE: (maxValue() >= lowWaterMark()) || modifyEnabled()
		// _TAG02 Attributes

	inline long lowWaterMark() const;
		// The lowest value assumed by this gauge since its creation.
		// REQUIRE: inSync() && !error()
		// ENSURE: lowWaterMark() <= highWaterMark()
		// ENSURE: lowWaterMark() <= value()
		// ENSURE: (lowWaterMark() <= maxValue()) || modifyEnabled()
		// _TAG02 Attributes

	inline long highWaterMark() const;
		// The highest value assumed by this gauge since its creation.
		// REQUIRE: inSync() && !error()
		// ENSURE: highWaterMark() >= lowWaterMark()
		// ENSURE: highWaterMark() >= value()
		// ENSURE: (highWaterMark() >= minValue()) || modifyEnabled()
		// _TAG02 Attributes

	inline RTRBOOL modifyEnabled() const;
		// Is the consumer permitted to modify this variable ?
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes

// Operations
	virtual void setRange(long newMin, long newMax) = 0;
		// Sets the min and max values.
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// REQUIRE: newMin <= newMax
		// _TAG03 Operations

protected:
// Data
	long _minValue;
	long _maxValue;
	long _lowWaterMark;
	long _highWaterMark;
	RTRBOOL _modifyEnabled;
		// Data
}; 

inline 
long RTRProxyManagedGauge::minValue() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _minValue <= _maxValue );
	RTPOSTCONDITION( (_minValue <= _value) || _modifyEnabled );
	RTPOSTCONDITION( (_minValue <= _highWaterMark) || _modifyEnabled );
	return _minValue;
}

inline 
long RTRProxyManagedGauge::maxValue() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _maxValue >= _minValue );
	RTPOSTCONDITION( (_maxValue >= _value) || _modifyEnabled );
	RTPOSTCONDITION( (_maxValue >= _lowWaterMark) || _modifyEnabled );
	return _maxValue;
}

inline
long RTRProxyManagedGauge::lowWaterMark() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _lowWaterMark <= _highWaterMark );
	RTPOSTCONDITION( _lowWaterMark <= _value );
	RTPOSTCONDITION( (_lowWaterMark <= _maxValue) || _modifyEnabled );
	return _lowWaterMark;
}

inline
long RTRProxyManagedGauge::highWaterMark() const
{
	RTPRECONDITION( inSync() && !error() );
	RTPOSTCONDITION( _lowWaterMark <= _highWaterMark );
	RTPOSTCONDITION( _lowWaterMark <= _value );
	RTPOSTCONDITION( (_lowWaterMark <= _maxValue) || _modifyEnabled );
	return _highWaterMark;
}

inline
RTRBOOL RTRProxyManagedGauge::modifyEnabled() const
{
	RTPRECONDITION( inSync() && !error() );

	return _modifyEnabled;
}

typedef RTRObjRef<RTRProxyManagedGauge> RTRProxyManagedGaugePtr;

#endif
