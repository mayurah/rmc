//|---------------------------------------------------------------------------
//|					      Copyright (C) 2008 Reuters,		                --
//|			   U Chu Liang Building, 968 Rama IV Road, Bangkok 10500	    --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: N. Sotanakun
// Created: "Apr. 10 2008"
// Version: 1.0

#ifndef _mlnumvar_h
#define _mlnumvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mvar.h"
#include "rtr/os.h"

// Synopsis:
// #include"rtr/mlnumvar.h"
//
// Description:
//	The base class for large numeric managed variables. This class provides
//	a read-only interface to the large numeric value.
// 
//	This class cannot be directly instantiated.
//
// See Also:
//	RTRManagedObject,
//	RTRManagedString, RTRManagedBoolean,
//	RTRManagedCounter, RTRManagedGauge,
//	RTRManagedNumeric,
//	RTRManagedNumericRange,
//	RTRManagedStringConfig, RTRManagedNumericConfig,
//	RTRManagedBooleanConfig, RTRManagedGaugeConfig
//
// Inherits:
//	RTRManagedVariable
//

class RTRManagedLargeNumeric : 
	public RTRManagedVariable
{ 
public:
// Destructor:
	virtual ~RTRManagedLargeNumeric();
		// _TAG Destructor

// Comparison

	inline RTRBOOL operator==(RTR_I64) const;
		// _TAG01 Comparison

// Access
	inline RTR_I64 value() const;
		// The current value of this variable.
		// _TAG02 Access

// Transformation
	inline operator RTR_I64() const;
		// This variable as an long long. 
		// _TAG03 Transformation

	virtual RTRString toString() const;
		// A copy of this variable value, represented as a string
		// _TAG03 Transformation

// Static Data
	static const RTR_I64 LongMinNumeric;
	static const RTR_I64 LongMaxNumeric;
		// Static Data
	
protected:
// Constructor:
	RTRManagedLargeNumeric(
		RTRManagedObject& context,
		MVType type,
		const char *name,
		const char *description = ""
		);

	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;

// Data
	RTR_I64 *_store;

private:
		// Don't define these.
	RTRManagedLargeNumeric(const RTRManagedLargeNumeric&);
	RTRManagedLargeNumeric& operator=(const RTRManagedLargeNumeric&);

// Friend functions
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRManagedLargeNumeric&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
RTRBOOL RTRManagedLargeNumeric::operator==(RTR_I64 rhs) const
{
	return *_store == rhs;
}

inline 
RTR_I64 RTRManagedLargeNumeric::value() const
{
	return *_store;
}

inline 
RTRManagedLargeNumeric::operator RTR_I64() const
{
	return *_store;
}

#endif
