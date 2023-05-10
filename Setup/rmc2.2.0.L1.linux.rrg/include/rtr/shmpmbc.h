//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmbc_h
#define _rtr_shmpmbc_h

#include "rtr/prxymbc.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// Synopsis:
// #include "rtr/shmpmbc.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedBooleanConfig.
//
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBoolean, 
// RTRShmProxyManagedCounter, RTRShmProxyManagedGauge, 
// RTRShmProxyManagedGaugeConfig, RTRShmProxyManagedNumeric, 
// RTRShmProxyManagedNumericConfig, RTRShmProxyManagedNumericRange, 
// RTRShmProxyManagedString, RTRShmProxyManagedStringConfig
// 
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedBooleanConfig -> 
// RTRProxyManagedBoolean -> RTRProxyManagedVariable
//

class RTRShmProxyManagedBooleanConfig :
	public RTRProxyManagedBooleanConfig
{ 
public:
// Constructor
	RTRShmProxyManagedBooleanConfig(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedBooleanConfig();
		// _TAG Destructor

// Operators
	inline RTRShmProxyManagedBooleanConfig& operator=(RTRBOOL rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG07 Operators

// Operations -- from RTRProxyManagedBooleanConfig
	void set();
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG08 Operations -- from RTRProxyManagedBooleanConfig

	void clear();
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG08 Operations -- from RTRProxyManagedBooleanConfig

protected:
// Operations
	void init();
	void update();

// Data
	RTRBoolConfigImpl *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedBooleanConfig(const RTRShmProxyManagedBooleanConfig&);
	RTRShmProxyManagedBooleanConfig& operator=(const RTRShmProxyManagedBooleanConfig&);
}; 

inline
RTRShmProxyManagedBooleanConfig&
RTRShmProxyManagedBooleanConfig::operator=(RTRBOOL rhs)
{
	if (rhs)
		set();
	else
		clear();
	return *this;
}

#endif /* _rtr_shmpmbc_h */
