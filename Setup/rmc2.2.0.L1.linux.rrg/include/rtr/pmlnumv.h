//|---------------------------------------------------------------------------
//|					      Copyright (C) 2008 Reuters,		                --
//|			   U Chu Liang Building, 968 Rama IV Road, Bangkok 10500	    --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: N. Sotanakun
// Created: "Apr. 10 2008"
// Version: 1.0

#ifndef _pmlnumv_h
#define _pmlnumv_h

#include "rtr/mlnumvar.h"
#include "rtr/vcmgr.h"
#include "rtr/rtratomic.h"

class RTRPublicObject;

// Synopsis:
//	#include"rtr/pmlnumv.h"
//
// Description:
// 	An implementation of the RTRManagedLargeNumeric base class which
// 	provides modification operations and uses the class RTRMNumericImpl
// 	for storage allocation.
//
// See Also: 
//	RTRPublicObject,
//	RTRPublicString, RTRPublicBoolean,
//	RTRPublicCounter, RTRPublicGauge,
//	RTRPublicNumeric,
//	RTRPublicNumericRange,
//	RTRPublicStringConfig, RTRPublicNumericConfig,
//	RTRPublicGaugeConfig, RTRPublicBooleanConfig
//
// Inherits:
//	RTRManagedLargeNumeric
//

class RTRPublicLargeNumeric : 
	public RTRManagedLargeNumeric
{ 
public:
// Constructor:
	RTRPublicLargeNumeric(
			RTRPublicObject& context, 
			const char* name,
			const char* description,
			RTR_I64 initValue
			);
		// Constructs an RTRPublicLargeNumeric
		// ENSURE: value() == initValue
		// _TAG Constructor

// Destructor:
	virtual ~RTRPublicLargeNumeric();
		// _TAG Destructor

// Assignment
	inline RTRPublicLargeNumeric& operator=(RTR_I64);
		// _TAG01 Assignment
			
// Operations
	inline void operator+=(RTR_I64);
		// _TAG02 Operations

	inline void operator-=(RTR_I64);
        	// _TAG02 Operations

	inline RTRPublicLargeNumeric& operator++();
        	// _TAG02 Operations

	inline RTRPublicLargeNumeric& operator++(int);
        	// _TAG02 Operations

	inline RTRPublicLargeNumeric& operator--();
        	// _TAG02 Operations

	inline RTRPublicLargeNumeric& operator--(int);
        	// _TAG02 Operations
	
	inline void atomicAdd(RTR_I64);
        	// _TAG02 Operations

	inline void atomicIncrement();
        	// _TAG02 Operations

	inline void atomicSubtract(RTR_I64);
        	// _TAG02 Operations

	inline void atomicDecrement();
        	// _TAG02 Operations

	void set(RTR_I64);
		// _TAG02 Operations

private:
	RTRPublicLargeNumeric(const RTRPublicLargeNumeric&);
		// Don't define this
}; 


inline 
RTRPublicLargeNumeric& RTRPublicLargeNumeric::operator=(RTR_I64 rhs)
{
	set(rhs);
	return *this;
}

inline 
void RTRPublicLargeNumeric::operator+=(RTR_I64 rhs)
{
	*_store += rhs;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

inline 
void RTRPublicLargeNumeric::operator-=(RTR_I64 rhs)
{
	*_store -= rhs;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

inline
RTRPublicLargeNumeric& RTRPublicLargeNumeric::operator++(int)
{
	(*_store)++;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
	return *this;
}

inline
RTRPublicLargeNumeric& RTRPublicLargeNumeric::operator++()
{
	(*_store)++;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
	return *this;
}

inline 
RTRPublicLargeNumeric& RTRPublicLargeNumeric::operator--(int)
{
	(*_store)--;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
	return *this;
}

inline 
RTRPublicLargeNumeric& RTRPublicLargeNumeric::operator--()
{
	(*_store)--;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
	return *this;
}

inline 
void RTRPublicLargeNumeric::atomicAdd(RTR_I64 rhs)
{
	RTR_ATOMIC_ADD(*(rtr_atomic_val*)_store,rhs);
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

inline 
void RTRPublicLargeNumeric::atomicIncrement()
{
	RTR_ATOMIC_INCREMENT(*(rtr_atomic_val*)_store);
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

inline 
void RTRPublicLargeNumeric::atomicSubtract(RTR_I64 rhs)
{
	RTR_ATOMIC_ADD(*(rtr_atomic_val*)_store,-rhs);
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}
inline 
void RTRPublicLargeNumeric::atomicDecrement()
{
	RTR_ATOMIC_DECREMENT(*(rtr_atomic_val*)_store);
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

#endif
