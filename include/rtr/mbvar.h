//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/23/97"
// Version: 1.0

#ifndef _mbvar_h
#define _mbvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mvar.h"
#include "rtr/vcmgr.h"

// Synopsis:
// #include"rtr/mbvar.h"
//
// Description:
//	The base class for boolean managed variables.
//	Inherits from RTRManagedVariable and provides
//	services for accessing and modifying a variable
//	of type boolean.
// 
//	Consumers can modify the variable if
//	permitted by the publisher (modifyEnabled == RTRTRUE).
//	Permission is granted/denied when the variable is created
//	and cannot be changed during its life-cycle.
// 	The context (ManagedObject) will be notified of changes.
// 
//	This class cannot be directly instantiated.
//
// See Also:
//	RTRManagedObject,
//	RTRManagedNumeric, RTRManagedString,
//	RTRManagedCounter, RTRManagedGauge
//	RTRManagedNumericRange,
//	RTRManagedStringConfig, RTRManagedNumericConfig,
//	RTRManagedBooleanConfig, RTRManagedGaugeConfig
//
// Inherits:
//	RTRManagedVariable
//

class RTRManagedBoolean : 
	public RTRManagedVariable
{ 
public:
// Destructor:
	virtual ~RTRManagedBoolean();
		// _TAG Destructor

// Comparison
	inline RTRBOOL operator==(RTRBOOL) const;
		// _TAG01 Comparison

// Access
	inline RTRBOOL value() const;
		// The current value of this variable.
		// _TAG02 Access

// Transformation
	virtual RTRString toString() const;
		// A copy of this variable value, represented as a string
		// _TAG03 Transformation

// State
	inline RTRBOOL modifyEnabled();
		// Is the managing application permitted to modify
		// this variable ?
		// _TAG04 State

// Assignment
	inline RTRManagedBoolean& operator=(RTRBOOL rhs);
		// REQUIRE: modifyEnabled()
		// Set the current value to rhs, notify clients and
		// notify context (containing managed object).
		// _TAG05 Assignment

// Operations
	virtual void set();
		// REQUIRE: modifyEnabled()
		// Set the current value to RTRTRUE, notify clients and
		// notify context (containing managed object).
		// _TAG06 Operations

	virtual void clear();
		// REQUIRE: modifyEnabled()
		// Set the current value to RTRFALSE, notify clients and
		// notify context (containing managed object).
		// _TAG06 Operations

protected:
// Constructor:
	RTRManagedBoolean(
			RTRManagedObject& context,
			MVType type,
			const char *name,
			const char *description,
			RTRBOOL modifyEnabled
			);
		// Constructor

// Operations
	inline void internalSet();
	inline void internalClear();

	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;
		// Operations

// Data
	RTRBOOL *_store;
	RTRBOOL _modifyEnabled;
		// Data

private:
	// Don't define these.
	RTRManagedBoolean(const RTRManagedBoolean&);
	RTRManagedBoolean& operator=(const RTRManagedBoolean&);

// Friend functions
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRManagedBoolean&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
RTRBOOL RTRManagedBoolean::operator==(RTRBOOL rhs) const
{
	return *_store == rhs;
}

inline 
RTRBOOL RTRManagedBoolean::value() const
{
	return *_store;
}

inline
RTRBOOL RTRManagedBoolean::modifyEnabled()
{
	return _modifyEnabled;
}

inline
RTRManagedBoolean& RTRManagedBoolean::operator=(RTRBOOL rhs)
{
	if ( rhs )
		set();
	else
		clear();
	return *this;
}

inline
void RTRManagedBoolean::internalSet()
{
	*_store = RTRTRUE;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

inline
void RTRManagedBoolean::internalClear()
{
	*_store = RTRFALSE;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

#endif
