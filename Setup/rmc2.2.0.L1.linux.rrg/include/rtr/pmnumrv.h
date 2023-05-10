//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/25/97"
// Version: 1.0

#ifndef _pmnumrv_h
#define _pmnumrv_h

#include "rtr/mnumrvar.h"

class RTRPublicObject;

// Synopsis:
// #include"rtr/pmnumrv.h"
//
// Description:
// 	An implementation of the RTRManagedNumericRange base class which
// 	uses the class RTRMNumRangeImpl for storage allocation.
//
//	The value will always be within the min/max range.
//	(ie. minValue() <= value() <= maxValue())
//
// See Also:
//	RTRPublicObject, 
//	RTRPublicString, RTRPublicNumeric,
//	RTRPublicCounter, RTRPublicGauge, RTRPublicBoolean,
//	RTRPublicNumericConfig, RTRPublicStringConfig,
//	RTRPublicBooleanConfig, RTRPublicGaugeConfig
//
// Inherits:
//	RTRManagedNumericRange
//

class RTRPublicNumericRange : 
	public RTRManagedNumericRange
{ 
public:
// Constructor:
	RTRPublicNumericRange(
			RTRPublicObject& context, 
			const char* name,
			const char* description,
			long initValue,
			long min = 0,
			long max = RTRManagedNumeric::MaxNumeric
			);
		// Constructs an RTRPublicNumericRange variable
		// REQUIRE: initValue >= min
		// REQUIRE: initValue <= max
		// REQUIRE: min <= max
		// ENSURE: value() == initValue
		// ENSURE: minValue() == min
		// ENSURE: maxValue() == max
		// _TAG Constructor

// Destructor
	virtual ~RTRPublicNumericRange();
		// _TAG Destructor

// Assignment
	inline RTRPublicNumericRange& operator=(long rhs);
		// Sets the current value to rhs.
		// REQUIRE: rhs >= minValue()
		// REQUIRE: rhs <= maxValue()
		// _TAG01 Assignment

// Operations
	inline void set(long newValue);
		// Sets the current value of this parameter to newValue.
		// REQUIRE: modifyEnabled()
		// REQUIRE: newValue >= minValue()
		// REQUIRE: newValue <= maxValue()
		// _TAG02 Operations

	inline void internalSet(long newValue);
		// Sets the current value of this parameter to newValue.
		// REQUIRE: newValue >= minValue()
		// REQUIRE: newValue <= maxValue()
		// _TAG02 Operations

	void set(long newMin, long newMax, long newValue);
		// Sets the minimum assignment value for this parameter to newMin,
		// the maximum assignment value for this parameter to newMax, and
		// the current value of this parameter to newValue
		// REQUIRE: newValue >= newMin
		// REQUIRE: newValue <= newMax
		// REQUIRE: newMin <= newMax
		// _TAG02 Operations

private:
		// Don't define these.
	RTRPublicNumericRange(const RTRPublicNumericRange&);
};

inline
RTRPublicNumericRange& RTRPublicNumericRange::operator=(long rhs)
{
	if ( *_store != rhs )
		internalSet(rhs);
	return *this;
}

inline
void RTRPublicNumericRange::set(long newValue)
{
	RTRManagedNumericRange::set(newValue);
}

inline
void RTRPublicNumericRange::internalSet(long newValue)
{
	RTRManagedNumericRange::internalSet(newValue);
}


#endif
