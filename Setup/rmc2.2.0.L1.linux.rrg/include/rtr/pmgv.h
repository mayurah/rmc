//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _pmgv_h
#define _pmgv_h

#include "rtr/mgvar.h"
#include "rtr/vcmgr.h"

class RTRPublicObject;

// Synopsis:
// #include"rtr/pmgv.h"
//
// Description:
// 	An implementation of the RTRManagedGauge base class which
// 	provides modification operations and uses the global instance of
// 	RTRMOServerMemPool for storage allocation.
//
//	If modifyEnabled is true (default value is false), then consumers
//	will be permitted to modify the active min/max values. 
// 	The context (ManagedObject) will be notified of changes.
//
//	if modifyEnabled is false, then the active value must always be between
//	minValue() and maxValue() (ie. minValue <= activeValue <= maxValue).
//	This restriction does not exist if the consumer is permitted to
//	modify the min/max values.  The active value could be outside the
//	min/max range.
//
// See Also:
//	RTRPublicObject,
//	RTRPublicString, RTRPublicNumeric,
//	RTRPublicCounter, RTRPublicBoolean,
//	RTRPublicNumericRange,
//	RTRPublicStringConfig, RTRPublicNumericConfig,
//	RTRPublicGaugeConfig, RTRPublicBooleanConfig,
//
// Inherits:
//	RTRManagedGauge
//

class RTRPublicGauge : 
	public RTRManagedGauge
{ 
public:
// Constructor:
	RTRPublicGauge(
			RTRPublicObject& context,
			const char* name,
			const char* description,
			long initValue,
			long min = 0,
			long max = RTRManagedNumeric::MaxNumeric,
			RTRBOOL modifyEnabled=RTRFALSE
			);
		// Constructs an RTRPublicGauge variable
		// REQUIRE: initValue >= min
		// REQUIRE: initValue <= max
		// REQUIRE: min <= max
		// ENSURE: lowWaterMark() == highWaterMark() == value()
		// ENSURE: value() == initValue
		// ENSURE: minValue() == min
		// ENSURE: maxValue() == max
		// _TAG Constructor

// Destructor
	virtual ~RTRPublicGauge();
		// _TAG Destructor

// Assignment
	inline RTRPublicGauge& operator=(long rhs);
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
			
	RTRPublicGauge& operator++();
		// REQUIRE: (newValue <= maxValue()) || modifyEnabled()
		// ENSURE: highWaterMark() >= value()
		// _TAG02 Operations

	RTRPublicGauge& operator++(int);
		// REQUIRE: (newValue <= maxValue()) || modifyEnabled()
		// ENSURE: highWaterMark() >= value()
		// _TAG02 Operations

	RTRPublicGauge& operator--();
		// REQUIRE: (newValue >= minValue()) || modifyEnabled()
		// ENSURE: lowWaterMark() <= value()
		// _TAG02 Operations

	RTRPublicGauge& operator--(int);
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
		// REQUIRE: (newMin <= newValue) || modifyEnabled()
		// REQUIRE: (newMax >= newValue) || modifyEnabled()
		// REQUIRE: newMin <= newMax
		// ENSURE: lowWaterMark() <= value()
		// ENSURE: highWaterMark() >= value()
		// _TAG02 Operations

	virtual void internalSetRange(long newMin, long newMax);
		// Sets the minimum assignment for this gauge to newMin,
		// the maximum assignment value for this gauge to newMax.
		// REQUIRE: (newMin <= value()) || modifyEnabled()
		// REQUIRE: (newMax >= value()) || modifyEnabled()
		// REQUIRE: newMin <= newMax
		// _TAG02 operations

private:
		// Don't define these.
	RTRPublicGauge(const RTRPublicGauge&);
	RTRPublicGauge & operator=(const RTRPublicGauge&);
		// Don't Define
}; 


inline
RTRPublicGauge& RTRPublicGauge::operator=(long newValue)
{
	set(newValue);
	return *this;
}


#endif
