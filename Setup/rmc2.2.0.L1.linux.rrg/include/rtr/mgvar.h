//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _mgvar_h
#define _mgvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mnumvar.h"
#include "rtr/vcmgr.h"

// Synopsis:
// #include "rtr/mgvar.h"
//
// Description:
//	A RTRManagedGauge is a descendant of RTRManagedNumeric and
//	provides services for min/max values and low/high water marks.
//	The low/high water marks indicate the lowest/highest values
//	assumed by a gauge since its creation.
// 
//	Consumers can modify the min and max attributes of the variable if
//	permitted by the publisher (modifyEnabled == RTRTRUE).
//	Permission is granted/denied when the variable is created
//	and cannot be changed during its life-cycle.
//	The context (ManagedObject) is notified of changes.
// 
//	if modifyEnabled is false, then the active value will be between
//	minValue() and maxValue() (ie. minValue <= activeValue <= maxValue).
//	This restriction does not exist if the consumer is permitted to
//	modify the min/max values.  The active value could be outside the
//	min/max range.
//
//	This class cannot be directly instantiated.
//
// See Also:
//	RTRManagedObject, RTRManagedVariable,
//	RTRManagedString, RTRManagedNumeric,
//	RTRManagedCounter, RTRManagedBoolean,
//	RTRManagedNumericRange,
//	RTRManagedStringConfig, RTRManagedNumericConfig,
//	RTRManagedGaugeConfig, RTRManagedBooleanConfig,
//
// Inherits:
//	RTRManagedNumeric
//

class RTRManagedGauge : 
	public RTRManagedNumeric
{ 
public:
// Destructor
	virtual ~RTRManagedGauge();
		// _TAG Destructor

// Attributes
	inline long minValue() const;
		// The minimum value which may be assigned to this parameter.
		// ENSURE: minValue() <= maxValue()
		// ENSURE: (minValue() <= value()) || modifyEnabled()
		// ENSURE: (minValue() <= highWaterMark()) || modifyEnabled()
		// _TAG01 Attributes

	inline long maxValue() const;
		// The maximum value which may be assigned to this parameter.
		// ENSURE: maxValue() >= minValue()
		// ENSURE: (maxValue() >= value()) || modifyEnabled()
		// ENSURE: (maxValue() >= lowWaterMark()) || modifyEnabled()
		// _TAG01 Attributes 

	inline long lowWaterMark() const;
		// The lowest value assumed by this gauge since its creation.
		// ENSURE: lowWaterMark() <= highWaterMark()
		// ENSURE: lowWaterMark() <= value()
		// ENSURE: (lowWaterMark() <= maxValue()) || modifyEnabled()
		// _TAG01 Attributes

	inline long highWaterMark() const;
		// The highest value assumed by this gauge since its creation.
		// ENSURE: highWaterMark() >= lowWaterMark()
		// ENSURE: highWaterMark() >= value()
		// ENSURE: (highWaterMark() >= minValue()) || modifyEnabled()
		// _TAG01 Attributes

	inline RTRBOOL modifyEnabled() const;
		// Is the consumer permitted to modify this variable ?
		// _TAG01 Attributes

// Operations
	virtual void setRange(long newMin, long newMax);
		// Sets the min and max values.
		// REQUIRE: modifyEnabled()
		// REQUIRE: (newMin <= newValue) || modifyEnabled()
		// REQUIRE: (newMax >= newValue) || modifyEnabled()
		// REQUIRE: newMin <= newMax
		// _TAG02 Operations

protected:
// Constructor:
	RTRManagedGauge(
			RTRManagedObject& context, 
			MVType type,
			const char *name,
			long min,
			long max,
			const char *description = "",
			RTRBOOL modifyEnabled = RTRFALSE
			);
		// Constructor
		// REQUIRE: min <= max
		// ENSURE: lowWaterMark() == highWaterMark() == value()
		// ENSURE: minValue() == min
		// ENSURE: maxValue() == max

// Operations
	virtual void internalSetRange(long newMin, long newMax);
	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;
		// Operations

// Data
	long _minValue;
	long _maxValue;
	long _lowWaterMark;
	long _highWaterMark;
	RTRBOOL _modifyEnabled;
		// Data

private:
		// Don't define these.
	RTRManagedGauge(const RTRManagedGauge&);
	RTRManagedGauge& operator=(const RTRManagedGauge&);

// Friend functions
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRManagedGauge&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
long RTRManagedGauge::minValue() const
{
	return _minValue;
}

inline 
long RTRManagedGauge::maxValue() const
{
	return _maxValue;
}

inline
long RTRManagedGauge::lowWaterMark() const
{
	return _lowWaterMark;
}

inline
long RTRManagedGauge::highWaterMark() const
{
	return _highWaterMark;
}

inline
RTRBOOL RTRManagedGauge::modifyEnabled() const
{
	return _modifyEnabled;
}


#endif
