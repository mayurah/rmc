//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/25/97"
// Version: 1.0

#ifndef _mnumrvar_h
#define _mnumrvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mnumvar.h"
#include "rtr/mo.h"
#include "rtr/vcmgr.h"

// Synopsis:
// #include"rtr/mnumrvar.h"
//
// Description:
//      Numeric Ranges inherit from Numeric and provides
//	services for specifying a min/max value.
//
//	Consumers are always permitted to modify the value.
//	The value must always be within the min/max range.
//	(ie. minValue() <= value() <= maxValue())
// 	The context (ManagedObject) will be notified of the change.
// 
//	The range may be changed by the publisher but the value wiil
//	always be within the min/max range.
//	(ie. minValue() <= value() <= maxValue())
//
// 	This class cannot no be instantiated directly.
//
// See Also:
//	RTRManagedObject, RTRManagedVariable,
//	RTRManagedString, RTRManagedNumeric,
//	RTRManagedCounter, RTRManagedGauge
//	RTRManagedBoolean,
//	RTRManagedStringConfig, RTRManagedNumericConfig,
//	RTRManagedGaugeConfig, RTRManagedBooleanConfig,
// 
// Inherits:
//	RTRManagedNumeric
//

class RTRManagedNumericRange : 
	public RTRManagedNumeric
{ 
public:
// Destructor:
	virtual ~RTRManagedNumericRange();
		// _TAG Destructor

// Attributes
	inline long minValue() const;
		// The minimum value which may be assigned to this parameter.
		// ENSURE: ( minValue() <= maxValue() )
		// ENSURE: ( minValue() <= value() )
		// _TAG01 Attributes
	
	inline long maxValue() const;
		// The maximum value which may be assigned to this parameter.
		// ENSURE: ( maxValue() >= minValue() )
		// ENSURE: ( maxValue() >= value() )
		// _TAG01 Attributes

// Assignment
	inline RTRManagedNumericRange& operator=(long rhs);
		// REQUIRE: ( rhs >= minValue() )
		// REQUIRE: ( rhs <= maxValue() )
		// _TAG02 Assignment

// Operations
	virtual void set(long newValue);
		// A synonym for operator=()
		// REQUIRE: ( newValue >= minValue() )
		// REQUIRE: ( newValue <= maxValue() )
		// _TAG03 Operations

protected:
// Constructor:
	RTRManagedNumericRange(
			RTRManagedObject& context,
			const char *name,
			long min,
			long max,
			const char *description = ""
			);
		// REQUIRE: ( min <= max )
		// ENSURE: minValue() == min
		// ENSURE: maxValue() == max

// Operations
	virtual void internalSet(long newValue);
		// REQUIRE: ( newValue >= minValue() )
		// REQUIRE: ( newValue <= maxValue() )

	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;
		// Operations

// Data
	long _minValue;
	long _maxValue;

private:
		// Don't define these.
	RTRManagedNumericRange(const RTRManagedNumericRange&);
	RTRManagedNumericRange& operator=(const RTRManagedNumericRange&);

// Friend functions
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRManagedNumericRange&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
long RTRManagedNumericRange::minValue() const
{
	return _minValue;
}

inline 
long RTRManagedNumericRange::maxValue() const
{
	return _maxValue;
}

inline
RTRManagedNumericRange& RTRManagedNumericRange::operator=(long rhs)
{
	set(rhs);
	return *this;
}

#endif
