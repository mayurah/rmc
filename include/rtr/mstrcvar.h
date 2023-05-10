//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "Jun. 12 1996"
// Version: 1.0

#ifndef _mstrcvar_h
#define _mstrcvar_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mstrvar.h"
class RTRMStrConfigImpl;

// Synopsis:
// #include"rtr/mstrcvar.h"
//
// Description:
//	String config inherit from String and provide services
//	for specifying configuration and default values.
//
//	Consumers can modify the variable if
//	permitted by the publisher (modifyEnabled == RTRTRUE).
//	Permission is granted/denied when the variable is created
//	and cannot be changed during its life-cycle.
// 	The context (ManagedObject) will be notified of changes.
//
// 	This class cannot be instantiated directly.
// 
// See Also:
//	RTRManagedObject, RTRManagedVariable, 
//	RTRManagedCounter, RTRManagedNumeric,
//	RTRManagedGauge, RTRManagedBoolean,
//	RTRManagedString,
//	RTRManagedNumericRange,
//	RTRManagedBooleanConfig, RTRManagedGaugeConfig,
//	RTRManagedNumericConfig
//
// Inherits:
//	RTRManagedString
//

class RTRManagedStringConfig : 
	public RTRManagedString
{ 
public:
// Destructor
	virtual ~RTRManagedStringConfig();
		// _TAG Destructor

// Assignment
	inline RTRManagedStringConfig& operator=(const char *rhs);
		// Set the active value to rhs
		// REQUIRE: modifyEnabled()
		// <Synchronized>
		// _TAG01 Assignment

// Attributes
	inline RTRString activeValue() const;
		// A synonym for value()
		// _TAG03 Attributes
			
	inline RTRString storeValue() const;
		// The store value
		// _TAG03 Attributes

	inline RTRString factoryDefault() const;
		// The factory default value
		// _TAG03 Attributes

	RTRBOOL hasStore() const;
		// Is the variable a client of a RTRVariableConfig ?
		// _TAG03 Attributes

	RTRBOOL isStoreActive() const;
		// Is the RTRVariableConfig in an active state ?
		// REQUIRE: hasStore()
		// _TAG03 Attributes

	RTRBOOL isStoreClassConfig() const;
		// Is the RTRVariableConfig's context a RTRClassConfig ?
		// class config ?
		// REQUIRE: hasStore()
		// _TAG03 Attributes

	RTRBOOL isStoreInstanceConfig() const;
		// Is the RTRVariableConfig's context a RTRInstanceConfig ?
		// instance config ?
		// REQUIRE: hasStore()
		// _TAG03 Attributes

protected:
// Constructor:
	RTRManagedStringConfig(
		RTRManagedObject& context,
		const char *name,
		const char *description = "",
		RTRBOOL modifyEnabled = RTRFALSE
		);

// Utilities
	void markStoreActive();
	void markStoreInactive();
	void markStoreCC();
	void markStoreIC();
	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) ;
	virtual void cleanUpImplPub() ;

// Data
	char *_storeValue;
	char *_factoryDefault;
	short _storeState;
	unsigned short _storeValueLen;

private:
		// Don't define these.
	RTRManagedStringConfig(const RTRManagedStringConfig&);
	RTRManagedStringConfig& operator=(const RTRManagedStringConfig&);

// Friend functions
	friend class RTRStrConfigImplPub;
	friend class RTRManagedMemAllocator;
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&, const RTRManagedStringConfig&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline
RTRString RTRManagedStringConfig::activeValue() const
{
	return RTRString(_store);
}

inline
RTRString RTRManagedStringConfig::storeValue() const
{
	return RTRString(_storeValue);
}

inline
RTRString RTRManagedStringConfig::factoryDefault() const
{
	return RTRString(_factoryDefault);
}

inline
RTRManagedStringConfig&
RTRManagedStringConfig::operator=(const char *rhs)
{
	set(rhs);
	return *this;
}


#endif
