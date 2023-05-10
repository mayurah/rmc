//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/23/97"
// Version: 1.0

#ifndef _mgcvar_h
#define _mgcvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mgvar.h"

// Synopsis:
// #include "rtr/mgcvar.h"
//
// Description:
//	Inherits from RTRManagedGauge and provides
//	services for providing a configuration and
//	default min/max values for the gauge.
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
//	RTRManagedCounter, RTRManagedGauge,
//	RTRManagedBoolean,
//	RTRManagedNumericRange,
//	RTRManagedStringConfig, RTRManagedNumericConfig,
//	RTRManagedBooleanConfig
//
// Inherits:
//	RTRManagedGauge
//

class RTRManagedGaugeConfig : 
	public RTRManagedGauge
{ 
public:
// Destructor
	virtual ~RTRManagedGaugeConfig();
		// _TAG Destructor

// Attributes
	inline long minStoreValue() const;
		// The store minimum value.
		// _TAG01 Attributes 

	inline long minFactoryDefault() const;
		// The factory default minimum value
		// _TAG01 Attributes 

	inline long maxStoreValue() const;
		// The store maximum value
		// _TAG01 Attributes 

	inline long maxFactoryDefault() const;
		// The factory default maximum value
		// _TAG01 Attributes 

protected:
// Constructor:
	RTRManagedGaugeConfig(
			RTRManagedObject& context,
			const char *name,
			long minStoreDflt,
			long minFactoryDflt,
			long maxStoreDflt,
			long maxFactoryDflt,
			const char *description = "",
			RTRBOOL modifyEnabled = RTRFALSE
			);
		// REQUIRE: minStoreDflt <= maxStoreDflt
		// REQUIRE: minFactoryDflt <= maxFactoryDflt

	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;

// Data
	long _minStoreValue;
	long _minFactoryDefault;
	long _maxStoreValue;
	long _maxFactoryDefault;

private:
		// Don't define these.
	RTRManagedGaugeConfig(const RTRManagedGaugeConfig&);
	RTRManagedGaugeConfig& operator=(const RTRManagedGaugeConfig&);

// Friend functions
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRManagedGaugeConfig&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
long RTRManagedGaugeConfig::minStoreValue() const
{
	return _minStoreValue;
}

inline
long RTRManagedGaugeConfig::minFactoryDefault() const
{
	return _minFactoryDefault;
}

inline 
long RTRManagedGaugeConfig::maxStoreValue() const
{
	return _maxStoreValue;
}

inline
long RTRManagedGaugeConfig::maxFactoryDefault() const
{
	return _maxFactoryDefault;
}

#endif
