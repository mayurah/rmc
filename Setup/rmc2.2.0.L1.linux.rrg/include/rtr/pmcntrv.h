//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _pmcntrv_h
#define _pmcntrv_h

#include "rtr/mcntrvar.h"
#include "rtr/vcmgr.h"
#include "rtr/rtratomic.h"

class RTRPublicObject;

// Synopsis:
// #include"rtr/pmcntrv.h"
//
// Description:
// 	An implementation of the ManagedCounter base class which
// 	provides increment capability and uses the class RTRMNumericImpl 
// 	for storage allocation. Note: counters can be
// 	reset to 0 and incremented, but not decremented.
//
// See Also:
//	RTRPublicObject,
//	RTRPublicString, RTRPublicNumeric,
//	RTRPublicGauge, RTRPublicBoolean,
//	RTRPublicNumericRange,
//	RTRPublicStringConfig, RTRPublicNumericConfig,
//	RTRPublicBooleanConfig, RTRPublicGaugeConfig,
//
// Inherits:
//	RTRManagedCounter
//

class RTRPublicCounter : 
	public RTRManagedCounter
{ 
public:
// Constructor:
	RTRPublicCounter(
			RTRPublicObject& context, 
			const char* name,
			const char* description,
			unsigned long initValue = 0
			);
		// Constructs an RTRPublicCounter variable
		// ENSURE: value() == initValue
		// _TAG Constructor

// Destructor:
	virtual ~RTRPublicCounter();
		// _TAG Destructor

// Operations
	virtual void reset();
		// Reset this counter to 0.
		// _TAG01 Operations

	inline void operator+=(unsigned long);
		// _TAG01 Operations
	
	inline RTRPublicCounter& operator++();
		// _TAG01 Operations

	inline RTRPublicCounter& operator++(int);
		// _TAG01 Operations

	inline void atomicAdd(unsigned long);
		// _TAG01 Operations

	inline void atomicIncrement();
		// _TAG01 Operations

private:
		// Don't define these.
	RTRPublicCounter(const RTRPublicCounter&);
	RTRPublicCounter& operator=(const RTRPublicCounter&);
		// Don't define
}; 

inline 
void RTRPublicCounter::operator+=(unsigned long rhs)
{
	*_store += rhs;
	//if (_clientMgr)
	//	_clientMgr->notifyUpdate();
}

inline
RTRPublicCounter& RTRPublicCounter::operator++(int)
{
	(*_store)++;
	//if (_clientMgr)
	//	_clientMgr->notifyUpdate();
	return *this;
}

inline
RTRPublicCounter& RTRPublicCounter::operator++()
{
	(*_store)++;
	//if (_clientMgr)
	//	_clientMgr->notifyUpdate();
	return *this;
}

inline 
void RTRPublicCounter::atomicAdd(unsigned long rhs)
{
	RTR_ATOMIC_ADD(*(rtr_atomic_val*)_store,rhs);
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

inline 
void RTRPublicCounter::atomicIncrement()
{
	RTR_ATOMIC_INCREMENT(*(rtr_atomic_val*)_store);
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

#endif
