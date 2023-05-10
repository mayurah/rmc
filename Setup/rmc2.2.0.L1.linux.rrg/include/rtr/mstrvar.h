//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _mstrvar_h
#define _mstrvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
#endif
#include <string.h>

#include "rtr/mvar.h"
#include "rtr/vcmgr.h"

// Synopsis:
// #include"rtr/mstrvar.h"
//
// Description:
// 	The base class for string variables and provides services
//      for accessing and modifying the value of the ManagedString.
//
//	Consumers can modify the variable if
//	permitted by the publisher (modifyEnabled == RTRTRUE).
//	Permission is granted/denied when the variable is created
//	and cannot be changed during its life-cycle.
// 	The context (ManagedObject) will be notified of changes.
// 
// 	This class cannot not be instantiated directly.
//
// See Also:
//	RTRManagedObject, RTRManagedVariable,
//	RTRManagedNumeric, RTRManagedBoolean,
//	RTRManagedCounter, RTRManagedGauge,
//	RTRManagedNumericRange,
//	RTRManagedStringConfig, RTRManagedNumericConfig,
//	RTRManagedBooleanConfig, RTRManagedGaugeConfig
//
// Inherits:
//	RTRManagedVariable
//

class RTRManagedString : 
	public RTRManagedVariable
{ 
public:
// Destructor
	virtual ~RTRManagedString();
		// _TAG Destructor

// Access
	inline RTRString value() const;
		// A copy of the current value of this variable.
		// _TAG01 Access

// Transformation
	inline operator const char *() const;
		// This variable as a C string (null terminated).
		// _TAG02 Transformation

	virtual RTRString toString() const;
		// A copy of this variables value, represented as a string.
		// _TAG02 Transformation

// Comparison
	inline RTRBOOL operator==(const char *) const;
		// _TAG03 Comparison

// Attributes
	inline RTRBOOL modifyEnabled() const;
		// Is the managing application permitted to modify this variable ?
		// _TAG04 Attributes

// Assignment
	inline RTRManagedString& operator=(const char *rhs);
		// Assigns the value of this variable to rhs
		// REQUIRE: modifyEnabled()
		// <Synchronized>
		// _TAG05 Assignment

// Operations
	virtual void set(const char *newValue);
		// A synonym for operator=()
		// REQUIRE: modifyEnabled()
		// <Synchronized>
		// _TAG06 Operations

protected:
// Constructor
	RTRManagedString(
			RTRManagedObject& context,
			MVType type,
			const char *name,
			const char *description = "",
			RTRBOOL modifyEnabled = RTRFALSE
			);
		// Constructor

// Operations
	virtual void internalSet(const char *newValue) ;
		// <Synchronized>

	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;
		// Operations

// Data
	char *_store;
	RTRBOOL _modifyEnabled;
	unsigned short _valueLen;

private:
		// Don't define these.
	RTRManagedString(const RTRManagedString&);
	RTRManagedString& operator=(const RTRManagedString&);

// Friend functions
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRManagedString&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
RTRString RTRManagedString::value() const
{
	return RTRString(_store);
}

inline
RTRBOOL RTRManagedString::operator==(const char *rhs) const
{
	return (strcmp(_store, rhs) == 0) ? RTRTRUE : RTRFALSE;
}

inline
RTRBOOL RTRManagedString::modifyEnabled() const
{
	return _modifyEnabled;
}

inline 
RTRManagedString::operator const char *() const
{
	return _store;
}

inline
RTRManagedString& RTRManagedString::operator=(const char *rhs)
{
	set(rhs);
	return *this;
}

#endif
