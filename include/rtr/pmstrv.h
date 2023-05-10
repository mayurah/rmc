//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _pmstrv_h
#define _pmstrv_h

#include "rtr/mstrvar.h"

class RTRPublicObject;

// Synopsis:
// #include"rtr/pmstrv.h"
//
// Description:
// 	An implementation of the RTRManagedString base class which
// 	provides set operations and uses the class RTRMStringImpl 
// 	for storage allocation.
//
//	If modifyEnabled is true (default value is false), then consumers
//	will be permitted to modify the active value. 
//
// See Also:
//	RTRPublicObject,
//	RTRPublicNumeric, RTRPublicBoolean,
//	RTRPublicCounter, RTRPublicGauge
//	RTRPublicNumericRange,
//	RTRPublicStringConfig, RTRPublicNumericConfig,
//	RTRPublicGaugeConfig, RTRPublicBooleanConfig,
//
// Inherits:
//	RTRManagedString
//

class RTRPublicString : 
	public RTRManagedString
{ 
public:
// Constructor:
	RTRPublicString(
			RTRPublicObject& context, 
			const char* name,
			const char* description,
			const char* initValue,
			RTRBOOL modifyEnabled = RTRFALSE
			);
		// Constructs an RTRPublicString variable
		// ENSURE: value() == initValue
		// _TAG Constructor

// Destructor:
	virtual ~RTRPublicString();
		// _TAG Destructor

// Assignment
	inline RTRPublicString& operator=(const char *rhs);
		// Sets the current value to rhs.
		// Note: The modifyEnabled() REQUIRE from the base
		// class has been removed.
		// <Synchronized>
		// _TAG01 Assignment

// Operations
	void set(const char *newValue);
		// Sets the current value to newValue.
		// Notify the context (managed object)
		// <Synchronized>
		// _TAG02 Operations

	void internalSet(const char *newValue);
		// Sets the current value to newValue.
		// <Synchronized>
		// _TAG02 Operations

private:
		// Don't define these.
	RTRPublicString(const RTRPublicString&);

}; 

inline
RTRPublicString& RTRPublicString::operator=(const char *rhs)
{
	internalSet(rhs);
	return *this;
}

#endif
