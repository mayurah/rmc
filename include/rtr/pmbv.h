//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/23/97"
// Version: 1.0

#ifndef _pmbv_h
#define _pmbv_h

#include "rtr/mbvar.h"
#include "rtr/vcmgr.h"

class RTRPublicObject;

// Synopsis:
//	#include"rtr/pmbv.h"
//
// Description:
// 	An implementation of the RTRManagedBoolean base class which
// 	provides modification operations and uses the global instance of
// 	RTRMOServerMemPool for storage allocation.
//
//	If modifyEnabled is true (default value is false), then consumers
//	will be permitted to modify the active value. 
//
// See Also: 
//	RTRPublicObject,
//	RTRPublicString, RTRPublicNumeric,
//	RTRPublicCounter, RTRPublicGauge
//	RTRPublicNumericRange,
//	RTRPublicStringConfig, RTRPublicNumericConfig,
//	RTRPublicBooleanConfig, RTRPublicGaugeConfig
//
// Inherits:
//	RTRManagedBoolean
//

class RTRPublicBoolean : 
	public RTRManagedBoolean
{ 
public:
// Constructor:
	RTRPublicBoolean(
			RTRPublicObject& context, 
			const char* name,
			const char* description,
			RTRBOOL initValue,
			RTRBOOL modifyEnabled=RTRFALSE
			);
		// Constructs an RTRPublicBoolean
		// ENSURE: value() == initValue
		// _TAG Constructor

// Destructor:
	virtual ~RTRPublicBoolean();
		// _TAG Destructor

// Assignment
	inline RTRPublicBoolean& operator=(RTRBOOL rhs);
		// Set the current value to rhs, notify clients 
		// The modifyEnabled() precondition in the 
		// base classis removed.
		// _TAG01 Assignment

// Operations
	inline void internalSet();
		// Set the value to RTRTRUE
		// _TAG02 Operations

	inline void internalClear();
		// Set the value to RTRFALSE
		// _TAG02 Operations

private:
	// Don't define this
	RTRPublicBoolean(const RTRPublicBoolean&);
}; 

inline
RTRPublicBoolean& RTRPublicBoolean::operator=(RTRBOOL rhs)
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
void RTRPublicBoolean::internalSet()
{
	RTRManagedBoolean::internalSet();
}

inline
void RTRPublicBoolean::internalClear()
{
	RTRManagedBoolean::internalClear();
}

#endif
