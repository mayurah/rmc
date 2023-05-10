//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/23/97"
// Version: 1.0

#ifndef _mbcvar_h
#define _mbcvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mbvar.h"

// Synopsis:
// #include"rtr/mbcvar.h"
//
// Description:
//	The base class for boolean config managed variables.
//	Inherits from RTRManagedBoolean and provides 
//	services for specifying configuration and default
//	values for the boolean variable.
//
//	Consumers can modify the variable if
//	permitted by the publisher (modifyEnabled == RTRTRUE).
//	Permission is granted/denied when the variable is created
//	and cannot be changed during its life-cycle.
//	The context (Managed Object) is notified of changes.
// 
//	This class cannot be directly instantiated.
//
// See Also:
//	RTRManagedObject, RTRManagedVariable,
//	RTRManagedNumeric, RTRManagedString,
//	RTRManagedCounter, RTRManagedGauge,
//	RTRManagedBoolean, RTRManagedNumericRange,
//	RTRManagedStringConfig, RTRManagedNumericConfig,
//	RTRManagedGaugeConfig
//
// Inherits:
//	RTRManagedBoolean
//

class RTRManagedBooleanConfig : 
	public RTRManagedBoolean
{ 
public:
// Destructor:
	virtual ~RTRManagedBooleanConfig();
		// _TAG Destructor

// Assignment
	inline RTRManagedBooleanConfig& operator=(RTRBOOL rhs);
		// Set the active value to rhs
		// REQUIRE: modifyEnabled()
		// _TAG01 Assignment

// Attributes
	inline RTRBOOL activeValue() const;
		// A synonym for value()
		// _TAG02 Attributes

	inline RTRBOOL storeValue() const;
		// The store value 
		// _TAG02 Attributes

	inline RTRBOOL factoryDefault() const;
		// The factory default value
		// _TAG02 Attributes

protected:
// Constructor:
	RTRManagedBooleanConfig(
			RTRManagedObject& context,
			const char *name,
			RTRBOOL storeDflt,
			RTRBOOL factoryDflt,
			const char *description = "",
			RTRBOOL modifyEnabled = RTRFALSE
			);

	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;

// Data
	RTRBOOL _storeValue;
	RTRBOOL _factoryDefault;

private:
		// Don't define these.
	RTRManagedBooleanConfig(const RTRManagedBooleanConfig&);
	RTRManagedBooleanConfig& operator=(const RTRManagedBooleanConfig&);

// Friend functions
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRManagedBooleanConfig&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline
RTRBOOL RTRManagedBooleanConfig::activeValue() const
{
	return value();
}

inline
RTRBOOL RTRManagedBooleanConfig::storeValue() const
{
	return _storeValue;
}

inline
RTRBOOL RTRManagedBooleanConfig::factoryDefault() const
{
	return _factoryDefault;
}

inline
RTRManagedBooleanConfig& RTRManagedBooleanConfig::operator=(RTRBOOL rhs)
{
	if ( rhs )
		set();
	else
		clear();
	return *this;
}

#endif
