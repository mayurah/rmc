//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/23/97"
// Version: 1.0

#ifndef _pmbcv_h
#define _pmbcv_h

#include "rtr/mbcvar.h"
#include "rtr/vcmgr.h"

class RTRPublicObject;

// Synopsis:
//	#include"rtr/pmbcv.h"
//
// Description:
// 	An implementation of the RTRManagedBooleanConfig base class which
// 	provides modification operations and uses the global instance of
// 	RTRMOServerMemPool for storage allocation.
//
//	If modifyEnabled is true (default value is false), then consumers
//	will be permitted to modify the active value. 
//
// See Also: 
//	RTRPublicObject,
//	RTRPublicString, RTRPublicNumeric,
//	RTRPublicCounter, RTRPublicGauge,
//	RTRPublicBoolean,
//	RTRPublicNumericRange,
//	RTRPublicStringConfig, RTRPublicNumericConfig,
//	RTRPublicGaugeConfig
//
// Inherits:
//	RTRManagedBooleanConfig 
//

class RTRPublicBooleanConfig : 
	public RTRManagedBooleanConfig
{ 
public:
// Constructor:
	RTRPublicBooleanConfig(
			RTRPublicObject& context, 
			const char* name,
			const char* description,
			RTRBOOL dfltValue,
			RTRBOOL modifyEnabled = RTRFALSE
			);
		// Constructs an RTRPublicBooleanConfig
		// ENSURE: activeValue() == dfltValue
		// ENSURE: storeValue() == dfltValue
		// ENSURE: factoryDefault() == dfltValue
		// _TAG Constructor

// Destructor:
	virtual ~RTRPublicBooleanConfig();
		// _TAG Destructor

// Assignment
	inline RTRPublicBooleanConfig& operator=(RTRBOOL rhs);
		// Set the value to rhs.
		// The modifyEnabled() REQUIRE from the base class
		// has been removed.
		// _TAG01 Assignment

// Operations
	inline void internalSet();
		// Set the value to newValue
		// _TAG02 Operations
			
	inline void internalClear();
		// Set the value to newValue
		// _TAG02 Operations
			
// Operations
	void setStore();
		// Set the store value to RTRTRUE.
		// The new value is not persistent.
		//_TAG03 Operations

	void clearStore();
		// Set the store value to RTRFALSE.
		// The new value is not persistent.
		//_TAG03 Operations

private:
	RTRPublicBooleanConfig(const RTRPublicBooleanConfig&);
		// Don't define this
}; 

inline
RTRPublicBooleanConfig& RTRPublicBooleanConfig::operator=(RTRBOOL rhs)
{
	if ( *_store != rhs )
	{
		if ( rhs )
			internalSet();
		else
			internalClear();
	}
	return *this;
}

inline
void RTRPublicBooleanConfig::internalSet()
{
	RTRManagedBooleanConfig::internalSet();
}

inline
void RTRPublicBooleanConfig::internalClear()
{
	RTRManagedBooleanConfig::internalClear();
}

#endif
