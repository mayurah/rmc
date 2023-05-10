//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _mcntrvar_h
#define _mcntrvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mvar.h"

// Synopsis:
// #include"rtr/mcntrvar.h"
//
// Description:
//      RTRManagedCounter is a descendant of RTRManagedVariable.
//      the RTRManagedCounter can be incremented or reset (to 0),
//      it cannot be decremented.
// 
//      Consumers are permitted to reset (to 0) the variable.
//	The context (ManagedObject) is not notified of resets.
// 
//      This class cannot be directly instantiated.
//
// See Also:
//	RTRManagedObject, RTRManagedVariable,
//	RTRManagedString, RTRManagedNumeric,
//	RTRManagedGauge, RTRManagedBoolean,
//	RTRManagedNumericRange,
//	RTRManagedStringConfig, RTRManagedNumericConfig,
//	RTRManagedGaugeConfig, RTRManagedBooleanConfig,
//
// Inherits:
//	RTRManagedVariable
//

class RTRManagedCounter : 
	public RTRManagedVariable
{ 
public:
// Destructor:
	virtual ~RTRManagedCounter();
		// _TAG Destructor

// Comparison
	inline RTRBOOL operator==(unsigned long) const;
		// _TAG01 Comparison

// Access
	inline unsigned long value() const;
		// The current value of this variable.
		// _TAG02 Access

// Transformation
	inline operator unsigned long() const;
		// This variable as an unsigned long.
		// _TAG03 Transformation

	virtual RTRString toString() const;
		// A copy of this variable's value, represented as a string.
		// _TAG03 Transformation

// Operations
	virtual void reset() = 0;
		// Reset this counter to 0.
		// _TAG04 Operations 

// Static Data
	static const unsigned long MinCounter;
	static const unsigned long MaxCounter;
		// Static Data
	
protected:
// Constructor:
	RTRManagedCounter(
			RTRManagedObject& context,
			MVType type,
			const char *name,
			const char* description = ""
			);

	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;

// Data
	unsigned long *_store;

private:
		// Don't define these.
	RTRManagedCounter(const RTRManagedCounter&);
	RTRManagedCounter& operator=(const RTRManagedCounter&);

// Friend functions
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&, const RTRManagedCounter&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline
RTRBOOL RTRManagedCounter::operator==(unsigned long rhs) const
{
	return *_store == rhs;
}

inline
unsigned long RTRManagedCounter::value() const
{
	return *_store;
}

inline
RTRManagedCounter::operator unsigned long() const
{
	return *_store;
}

#endif
