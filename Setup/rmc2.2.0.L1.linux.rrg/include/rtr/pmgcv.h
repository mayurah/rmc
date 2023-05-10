//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _pmgcv_h
#define _pmgcv_h

#include "rtr/mgcvar.h"
#include "rtr/vcmgr.h"

class RTRPublicObject;

// Synopsis:
// #include"rtr/pmgv.h"
//
// Description:
// 	An implementation of the RTRManagedGaugeConfig base class which
// 	provides modification operations and uses the global instance of
// 	RTRMOServerMemPool for storage allocation.
//
//	If modifyEnabled is true (default value is false), then consumers
//	will be permitted to modify the active min/max values. 
//	
//	if modifyEnabled is false, then the active value will be between
//	minValue() and maxValue() (ie. minValue <= activeValue <= maxValue).
//	This restriction does not exist if the consumer is permitted to
//	modify the min/max values.  The active value could be outside the
//	min/max range.
//
// See Also:
//	RTRPublicObject,
//	RTRPublicString, RTRPublicNumeric,
//	RTRPublicCounter, RTRPublicBoolean,
//	RTRPublicNumericRange, RTRPublicGauge,
//	RTRPublicStringConfig, RTRPublicNumericConfig,
//	RTRPublicBooleanConfig,
//
// Inherits:
//	RTRManagedGaugeConfig
//

class RTRPublicGaugeConfig : 
	public RTRManagedGaugeConfig
{ 
public:
// Constructor:
	RTRPublicGaugeConfig(
			RTRPublicObject& context, 
			const char* name,
			const char* description,
			long initValue,
			long minDflt = 0,
			long maxDflt = RTRManagedNumeric::MaxNumeric,
			RTRBOOL modifyEnabled=RTRFALSE
			);
		// Constructs an RTRPublicGaugeConfig
		// REQUIRE: initValue >= minDflt
		// REQUIRE: initValue <= maxDflt
		// REQUIRE: minDflt <= maxDflt
		// ENSURE: lowWaterMark() == highWaterMark() == value()
		// ENSURE: value() == initValue
		// ENSURE: minValue() == minStoreValue() == minFactoryDefault() == minDflt
		// ENSURE: maxValue() == maxStoreValue() == maxFactoryDefault() == maxDflt
		// _TAG Constructor

// Destructor
	virtual ~RTRPublicGaugeConfig();
		// _TAG Destructor

// Assignment
	inline RTRPublicGaugeConfig& operator=(long rhs);
		// REQUIRE: (rhs >= minValue()) || modifyEnabled()
		// REQUIRE: (rhs <= maxValue()) || modifyEnabled()
		// ENSURE: lowWaterMark() <= value()
		// ENSURE: highWaterMark() >= value()
		// _TAG01 Assignment

// Operations
	void operator+=(long);
		// REQUIRE: (newValue >= minValue()) || modifyEnabled()
		// REQUIRE: (newValue <= maxValue()) || modifyEnabled()
		// ENSURE: lowWaterMark() <= value()
		// ENSURE: highWaterMark() >= value()
		// _TAG02 Operations
	
	void operator-=(long);
		// REQUIRE: (newValue >= minValue()) || modifyEnabled()
		// REQUIRE: (newValue <= maxValue()) || modifyEnabled()
		// ENSURE: lowWaterMark() <= value()
		// ENSURE: highWaterMark() >= value()
		// _TAG02 Operations
			
	RTRPublicGaugeConfig& operator++();
		// REQUIRE: (newValue <= maxValue()) || modifyEnabled()
		// ENSURE: highWaterMark() >= value()
		// _TAG02 Operations

	RTRPublicGaugeConfig& operator++(int);
		// REQUIRE: (newValue <= maxValue()) || modifyEnabled()
		// ENSURE: highWaterMark() >= value()
		// _TAG02 Operations

	RTRPublicGaugeConfig& operator--();
		// REQUIRE: (newValue >= minValue()) || modifyEnabled()
		// ENSURE: lowWaterMark() <= value()
		// _TAG02 Operations

	RTRPublicGaugeConfig& operator--(int);
		// REQUIRE: (newValue >= minValue()) || modifyEnabled()
		// ENSURE: lowWaterMark() <= value()
		// _TAG02 Operations

	void set(long newValue);
		// REQUIRE: (newValue >= minValue()) || modifyEnabled()
		// REQUIRE: (newValue <= maxValue()) || modifyEnabled()
		// ENSURE: lowWaterMark() <= value()
		// ENSURE: highWaterMark() >= value()
		// _TAG02 Operations

	void set(long newMin, long newMax, long newValue);
		// Sets the minimum assignment value for this gauge to newMin,
		// the maximum assignment value for this gauge to newMax, and the
		// current value of this gauge to newValue
		// REQUIRE: (newValue >= minValue()) || modifyEnabled()
		// REQUIRE: (newValue <= maxValue()) || modifyEnabled()
		// REQUIRE: newMin <= newMax
		// ENSURE: lowWaterMark() <= value()
		// ENSURE: highWaterMark() >= value()
		// _TAG02 Operations
	
	void internalSetRange(long newMin, long newMax);
		// Sets the values for min and max. Clients are notified
		// but the context is not notified.
		// REQUIRE: (newValue >= minValue()) || modifyEnabled()
		// REQUIRE: (newValue <= maxValue()) || modifyEnabled()
		// REQUIRE: newMin <= newMax
		// _TAG02 Operations

	void setStore(long newMin, long newMax);
		// REQUIRE: newMin <= newMax
		// _TAG02 Operations

private:
		// Don't define these.
	RTRPublicGaugeConfig(const RTRPublicGaugeConfig&);
	RTRPublicGaugeConfig & operator=(const RTRPublicGaugeConfig&);
		// Don't Define
}; 

inline 
RTRPublicGaugeConfig& RTRPublicGaugeConfig::operator=(long rhs)
{
	set(rhs);
	return *this;
}


#endif
