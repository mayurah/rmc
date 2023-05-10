//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmb_h
#define _rtr_shmpmb_h

#include "rtr/prxymb.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// Synopsis:
// #include "rtr/shmpmb.h"
//
// @description
// A shared memory based implementation of a RTRProxyManagedBoolean.
//
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBooleanConfig,
// RTRShmProxyManagedCounter, RTRShmProxyManagedGauge,
// RTRShmProxyManagedGaugeConfig, RTRShmProxyManagedNumeric,
// RTRShmProxyManagedNumericConfig, RTRShmProxyManagedNumericRange,
// RTRShmProxyManagedString, RTRShmProxyManagedStringConfig
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedBoolean -> RTRProxyManagedVariable
//

class RTRShmProxyManagedBoolean :
	public RTRProxyManagedBoolean
{ 
public:
// Constructor
	RTRShmProxyManagedBoolean(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedBoolean();
		// _TAG Destructor

// Operators
	inline RTRShmProxyManagedBoolean& operator=(RTRBOOL rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG07 Operators

// Operations -- from RTRProxyManagedBoolean
	void set();
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG08 Operations -- from RTRProxyManagedBoolean
	
	void clear();
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG08 Operations -- from RTRProxyManagedBoolean

protected:
// Operations
	void init();
	void update();

// Data
	RTRBoolImpl *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedBoolean(const RTRShmProxyManagedBoolean&);
	RTRShmProxyManagedBoolean& operator=(const RTRShmProxyManagedBoolean&);
}; 

inline
RTRShmProxyManagedBoolean& RTRShmProxyManagedBoolean::operator=(RTRBOOL rhs)
{
	if (rhs)
		set();
	else
		clear();
	return *this;
}

#endif /* _rtr_shmpmb_h */
