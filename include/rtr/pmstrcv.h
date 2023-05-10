//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "Jun. 13 1996"
// Version: 1.0

#ifndef _pmstrcv_h
#define _pmstrcv_h

#include "rtr/mstrcvar.h"

// Synopsis:
// #include"rtr/pmstrcv.h"
//
// Description:
// 	An implementation of the RTRManagedStringConfig base class which uses
// 	the class RTRMStrConfigImpl for storage allocation.
//
//	If modifyEnabled is true (default value is false), then consumers
//	will be permitted to modify the active value. 
//
// See Also:
//	RTRPublicObject,
//	RTRPublicNumeric, RTRPublicString,
//	RTRPublicGauge, RTRPublicCounter
//	RTRPublicBoolean, RTRPublicNumericRange,
//	RTRPublicNumericConfig, RTRPublicGaugeConfig,
//	RTRPublicBooleanConfig
//
// Inherits:
//	RTRManagedStringConfig
//

class RTRPublicStringConfig : 
	public RTRManagedStringConfig
{ 
public:
// Constructor:
	RTRPublicStringConfig(
			RTRPublicObject& context, 
			const char* name,
			const char* description,
			const char* dfltValue,
			RTRBOOL modifyEnabled=RTRFALSE
			);
		// Constructs an RTRPublicStringConfig variable
		// ENSURE: activeValue() == storeValue() ==
		//		factoryDefault() == dfltValue
		// _TAG Constructor

// Destructor:
	virtual ~RTRPublicStringConfig();
		// _TAG Destructor

// Assignment
	inline RTRPublicStringConfig& operator=(const char *rhs);
		// Set the active value.
		// Note: The modifyEnabled() REQUIRE from the base class
		// has been removed.
		// <Synchronized>
		// _TAG01 Assignment

// Operations
	virtual void set(const char *newValue);
		// Sets the current value to newValue.
		// Notify the context managed object
		// <Synchronized>
		// _TAG02 Operations

	virtual void internalSet(const char *newValue);
		// Set the active value.
		// Does not notify the context managed object.
		// <Synchronized>
		// _TAG02 Operations

	void setStore(const char *newStore);
		// Set the store value.
		// <Synchronized>
		// _TAG02 Operations

protected:
// Helper
	void init(RTRPublicObject&, const char*, const char*, RTRBOOL);
	void internalSetStore(const char *newStore);
	void cleanUpStore();

private:
		// Don't define these.
	RTRPublicStringConfig(const RTRPublicStringConfig&);
};


inline
RTRPublicStringConfig& RTRPublicStringConfig::operator=(const char* rhs)
{
	internalSet(rhs);
	return *this;
}
#endif
