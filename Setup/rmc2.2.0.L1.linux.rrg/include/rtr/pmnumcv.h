//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "Jun. 13 1996"
// Version: 1.0

#ifndef _pmnumcv_h
#define _pmnumcv_h

#include "rtr/mnumcvar.h"

class RTRPublicObject;

// Synopsis:
// #include"rtr/pmnumcv.h"
//
// Description:
// 	An implementation of the RTRManagedNumericConfig base class which
// 	uses the class RTRMNumConfigImpl for storage allocation.
//
//	If modifyEnabled is true (default value is false), then consumers
//	will be permitted to modify the active value. 
//
//	The value will always be within the min/max range.
//	(ie. minValue() <= value() <= maxValue())
//
// See Also:
//	RTRPublicObject, 
//	RTRPublicString, RTRPublicNumeric,
//	RTRPublicCounter, RTRPublicGauge,
//	RTRPublicBoolean,
//	RTRPublicNumericRange, RTRPublicStringConfig,
//	RTRPublicBooleanConfig, RTRPublicGaugeConfig
//
// Inherits:
//	RTRManagedNumericConfig
//

class RTRPublicNumericConfig : 
	public RTRManagedNumericConfig
{ 
public:
// Constructor:
	RTRPublicNumericConfig(
			RTRPublicObject& context,
			const char* name,
			const char* description,
			long dfltValue,
			long min = 0,
			long max = RTRManagedNumeric::MaxNumeric,
			RTRBOOL modifyEnabled=RTRFALSE
			);
		// Constructs an RTRPublicNumericConfig variable
		// REQUIRE : dfltValue >= min
		// REQUIRE : dfltValue <= max
		// REQUIRE : min <= max
		// ENSURE: activeValue() == storeValue() == factoryDefault() == dfltValue
		// ENSURE: minValue() == min
		// ENSURE: maxValue() == max
		// _TAG Constructor

// Destructor
	virtual ~RTRPublicNumericConfig();
		// _TAG Destructor

// Assignment
	inline RTRPublicNumericConfig& operator=(long rhs);
		// Set the active value to newValue.
		// Note: The modifyEnabled() REQUIRE from the base class
		// is removed here.
		// REQUIRE : newValue >= minValue()
		// REQUIRE : newValue <= maxValue()
		// <Synchronized>
		// _TAG01 Assignment

// Operations
	inline void internalSet(long newValue);
		// Set the active value to newValue.
		// Does not notify the context MO.
		// REQUIRE : newValue >= minValue()
		// REQUIRE : newValue <= maxValue()
		// <Synchronized>
		// _TAG02 Operations

	void setStore(long newStore);
		// Set the store value to newStore.
		// The value is not persistent.
		// <Synchronized>
		// _TAG02 Operations

protected:
// Helper
	void init(RTRPublicObject&, const char*, long, long, long, RTRBOOL);
	void cleanUpStore();
	
private:
		// Don't define these.
	RTRPublicNumericConfig(const RTRPublicNumericConfig&);
};

inline
RTRPublicNumericConfig& RTRPublicNumericConfig::operator=(long rhs)
{
	if ( *_store != rhs )
		internalSet(rhs);
	return *this;
}

inline
void RTRPublicNumericConfig::internalSet(long newValue)
{
	RTRManagedNumericConfig::internalSet(newValue);
}

#endif
