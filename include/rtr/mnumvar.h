//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _mnumvar_h
#define _mnumvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mvar.h"

// Synopsis:
// #include"rtr/mnumvar.h"
//
// Description:
//	The base class for numeric managed variables. This class provides
//	a read-only interface to the numeric value.
// 
//	This class cannot be directly instantiated.
//
// See Also:
//	RTRManagedObject,
//	RTRManagedString, RTRManagedBoolean,
//	RTRManagedCounter, RTRManagedGauge,
//	RTRManagedNumericRange,
//	RTRManagedStringConfig, RTRManagedNumericConfig,
//	RTRManagedBooleanConfig, RTRManagedGaugeConfig
//
// Inherits:
//	RTRManagedVariable
//

class RTRManagedNumeric : 
	public RTRManagedVariable
{ 
public:
// Destructor:
	virtual ~RTRManagedNumeric();
		// _TAG Destructor

// Comparison
	inline RTRBOOL operator==(long) const;
		// _TAG01 Comparison

// Access
	inline long value() const;
		// The current value of this variable.
		// _TAG02 Access

// Transformation
	inline operator long() const;
		// This variable as an long.
		// _TAG03 Transformation

	virtual RTRString toString() const;
		// A copy of this variable value, represented as a string
		// _TAG03 Transformation

// Static Data
	static const long MinNumeric;
	static const long MaxNumeric;
		// Static Data
	
protected:
// Constructor:
	RTRManagedNumeric(
		RTRManagedObject& context,
		MVType type,
		const char *name,
		const char *description = ""
		);

	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;

// Data
	long *_store;

private:
		// Don't define these.
	RTRManagedNumeric(const RTRManagedNumeric&);
	RTRManagedNumeric& operator=(const RTRManagedNumeric&);

// Friend functions
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&, const RTRManagedNumeric&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
RTRBOOL RTRManagedNumeric::operator==(long rhs) const
{
	return *_store == rhs;
}

inline 
long RTRManagedNumeric::value() const
{
	return *_store;
}

inline 
RTRManagedNumeric::operator long() const
{
	return *_store;
}

#endif
