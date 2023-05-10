//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "Jun. 12 1996"
// Version: 1.0

#ifndef _mnumcvar_h
#define _mnumcvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mnumvar.h"
#include "rtr/vcmgr.h"

// Synopsis:
// #include"rtr/mnumcvar.h"
//
// Description:
//	Numeric configs inherit from Numeric and provides
//	services for specifying min/max values, configuration
//	value and a default value.
//
//	Consumers can modify the variable if
//	permitted by the publisher (modifyEnabled == RTRTRUE).
//	Permission is granted/denied when the variable is created
//	and cannot be changed during its life-cycle.
// 	The context (ManagedObject) will be notified of the change.
// 
//	The value must always be within the min/max range.
//	(ie. minValue() <= value() <= maxValue())
//
// 	This class cannot no be instantiated directly.
//
// See Also:
//	RTRManagedObject, RTRManagedVariable,
//	RTRManagedString, RTRManagedNumeric,
//	RTRManagedCounter, RTRManagedGauge,
//	RTRManagedBoolean,
//	RTRManagedNumericRange, RTRManagedStringConfig,
//	RTRManagedBooleanConfig, RTRManagedGaugeConfig
//
// Inherits:
//	RTRManagedNumeric
//

class RTRManagedNumericConfig : 
	public RTRManagedNumeric
{ 
public:
// Destructor:
	virtual ~RTRManagedNumericConfig();
		// _TAG Destructor

// Attributes
	inline long minValue() const;
		// The minimum value which may be assigned to the active
		// variable.
		// ENSURE: ( minValue() <= maxValue() )
		// ENSURE: ( minValue() <= value() )
		// _TAG01 Attributes

	inline long maxValue() const;
		// The maximum value which may be assigned to the active
		// variable.
		// ENSURE: ( maxValue() >= minValue() )
		// ENSURE: ( maxValue() >= value() )
		// _TAG01 Attributes

	inline long activeValue() const;
		// A synonym for value()
		// ENSURE: ( activeValue() >= minValue() )
		// ENSURE: ( activeValue() <= maxValue() )
		// _TAG01 Attributes

	inline long storeValue() const;
		// The store value
		// _TAG01 Attributes

	inline int storeState() const;
		// The store state
		// _TAG01 Attributes

	inline long factoryDefault() const;
		// The factory default value
		// _TAG01 Attributes

	inline RTRBOOL modifyEnabled() const;
		// Is the consumer permitted to modify this variable ?
		// _TAG01 Attributes

	RTRBOOL hasStore() const;
		// Is the variable a client of a RTRVariableConfig ?
		// _TAG01 Attributes

	RTRBOOL isStoreActive() const;
		// Is the RTRVariableConfig in an active state ?
		// REQUIRE: hasStore()
		// _TAG01 Attributes

	RTRBOOL isStoreClassConfig() const;
		// Is the RTRVariableConfig's context a RTRClassConfig ?
		// class config ?
		// REQUIRE: hasStore()
		// _TAG01 Attributes

	RTRBOOL isStoreInstanceConfig() const;
		// Is the RTRVariableConfig's context a RTRInstanceConfig ?
		// instance config ?
		// REQUIRE: hasStore()
		// _TAG01 Attributes

// Assignment
	inline RTRManagedNumericConfig& operator=(long rhs);
		// REQUIRE: modifyEnabled()
		// REQUIRE: rhs >= minValue()
		// REQUIRE: rhs <= maxValue()
		// Set the active value.
		// <Synchronized>
		// _TAG02 Assignment

// Operations
	virtual void set(long newValue);
		// REQUIRE: modifyEnabled()
		// REQUIRE: newValue >= minValue()
		// REQUIRE: newValue <= maxValue()
		// A synonym for operator=()
		// <Synchronized>
		// _TAG03 Operations

protected:
// Constructor:
	RTRManagedNumericConfig(
			RTRManagedObject& context, 
			const char *name,
			long storeDflt,
			long factoryDflt,
			long min,
			long max,
			const char *description = "",
			RTRBOOL modifyEnabled = RTRFALSE
			);

// Utilities
	void markStoreActive();
	void markStoreInactive();
	void markStoreCC();
	void markStoreIC();
	inline void internalSet(long val);
	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;

// Data
	long _storeValue;
	long _factoryDefault;
	long _minValue;
	long _maxValue;
	int  _storeState;
	RTRBOOL _modifyEnabled;

private:
		// Don't define these.
	RTRManagedNumericConfig(const RTRManagedNumericConfig&);
	RTRManagedNumericConfig& operator=(const RTRManagedNumericConfig&);

// Friend functions
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRManagedNumericConfig&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
long RTRManagedNumericConfig::minValue() const
{
	return _minValue;
}

inline 
long RTRManagedNumericConfig::maxValue() const
{
	return _maxValue;
}

inline 
long RTRManagedNumericConfig::activeValue() const
{
	return value();
}

inline 
long RTRManagedNumericConfig::storeValue() const
{
	return _storeValue;
}

inline 
int RTRManagedNumericConfig::storeState() const
{
	return _storeState;
}

inline 
long RTRManagedNumericConfig::factoryDefault() const
{
	return _factoryDefault;
}

inline
RTRBOOL RTRManagedNumericConfig::modifyEnabled() const
{
	return _modifyEnabled;
}

inline
RTRManagedNumericConfig& RTRManagedNumericConfig::operator=(long rhs)
{
	set(rhs);
	return *this;
}

inline
void RTRManagedNumericConfig::internalSet(long newValue)
{
	lock();
	RTPRECONDITION ( newValue >= minValue() );
	RTPRECONDITION ( newValue <= maxValue() );

	*_store = newValue;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
	unlock();
}

#endif
