//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _pmnumv_h
#define _pmnumv_h

#include "rtr/mnumvar.h"
#include "rtr/vcmgr.h"
#include "rtr/rtratomic.h"

class RTRPublicObject;

// Synopsis:
//	#include"rtr/pmnumv.h"
//
// Description:
// 	An implementation of the RTRManagedNumeric base class which
// 	provides modification operations and uses the class RTRMNumericImpl
// 	for storage allocation.
//
// See Also: 
//	RTRPublicObject,
//	RTRPublicString, RTRPublicBoolean,
//	RTRPublicCounter, RTRPublicGauge
//	RTRPublicNumericRange,
//	RTRPublicStringConfig, RTRPublicNumericConfig,
//	RTRPublicGaugeConfig, RTRPublicBooleanConfig
//
// Inherits:
//	RTRManagedNumeric
//

class RTRPublicNumeric : 
	public RTRManagedNumeric
{ 
public:
// Constructor:
	RTRPublicNumeric(
			RTRPublicObject& context, 
			const char* name,
			const char* description,
			long initValue
			);
		// Constructs an RTRPublicNumeric
		// ENSURE: value() == initValue
		// _TAG Constructor

// Destructor:
	virtual ~RTRPublicNumeric();
		// _TAG Destructor

// Assignment
	inline RTRPublicNumeric& operator=(long);
		// _TAG01 Assignment
			
// Operations
	inline void operator+=(long);
		// _TAG02 Operations

	inline void operator-=(long);
        	// _TAG02 Operations

	inline RTRPublicNumeric& operator++();
        	// _TAG02 Operations

	inline RTRPublicNumeric& operator++(int);
        	// _TAG02 Operations

	inline RTRPublicNumeric& operator--();
        	// _TAG02 Operations

	inline RTRPublicNumeric& operator--(int);
        	// _TAG02 Operations

	inline void atomicAdd(long);
            // _TAG02 Operations

    inline void atomicIncrement();
            // _TAG02 Operations

    inline void atomicSubtract(long);
            // _TAG02 Operations

    inline void atomicDecrement();
            // _TAG02 Operations

	void set(long);
		// _TAG02 Operations

private:
	RTRPublicNumeric(const RTRPublicNumeric&);
		// Don't define this
}; 


inline 
RTRPublicNumeric& RTRPublicNumeric::operator=(long rhs)
{
	set(rhs);
	return *this;
}

inline 
void RTRPublicNumeric::operator+=(long rhs)
{
	*_store += rhs;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

inline 
void RTRPublicNumeric::operator-=(long rhs)
{
	*_store -= rhs;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
}

inline
RTRPublicNumeric& RTRPublicNumeric::operator++(int)
{
	(*_store)++;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
	return *this;
}

inline
RTRPublicNumeric& RTRPublicNumeric::operator++()
{
	(*_store)++;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
	return *this;
}

inline 
RTRPublicNumeric& RTRPublicNumeric::operator--(int)
{
	(*_store)--;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
	return *this;
}

inline 
RTRPublicNumeric& RTRPublicNumeric::operator--()
{
	(*_store)--;
	if (_clientMgr)
		_clientMgr->notifyUpdate();
	return *this;
}

void RTRPublicNumeric::atomicAdd(long rhs)
{
    RTR_ATOMIC_ADD(*(rtr_atomic_val*)_store,rhs);
    if (_clientMgr)
        _clientMgr->notifyUpdate();
}

inline
void RTRPublicNumeric::atomicIncrement()
{
    RTR_ATOMIC_INCREMENT(*(rtr_atomic_val*)_store);
    if (_clientMgr)
        _clientMgr->notifyUpdate();
}
    
inline 
void RTRPublicNumeric::atomicSubtract(long rhs)
{   
    RTR_ATOMIC_ADD(*(rtr_atomic_val*)_store,-rhs);
    if (_clientMgr)
        _clientMgr->notifyUpdate();
}

inline
void RTRPublicNumeric::atomicDecrement()
{
    RTR_ATOMIC_DECREMENT(*(rtr_atomic_val*)_store);
    if (_clientMgr)
        _clientMgr->notifyUpdate();
}

#endif
