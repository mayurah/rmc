//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmnc_h
#define _rtr_shmpmnc_h

#include "rtr/prxymnc.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// Synopsis:
// #include "rtr/shmpmnc.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedNumericConfig.
// 
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBoolean, 
// RTRShmProxyManagedBooleanConfig, RTRShmProxyManagedCounter, 
// RTRShmProxyManagedGauge, RTRShmProxyManagedGaugeConfig, 
// RTRShmProxyManagedNumeric, RTRShmProxyManagedNumericRange, 
// RTRShmProxyManagedString, RTRShmProxyManagedStringConfig
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedNumericConfig ->
// RTRProxyManagedNumeric -> RTRProxyManagedVariable
//

class RTRShmProxyManagedNumericConfig :
	public RTRProxyManagedNumericConfig
{ 
public:
// Constructor
	RTRShmProxyManagedNumericConfig(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedNumericConfig();
		// _TAG Destructor

// Operations -- from RTRProxyManagedNumericConfig
	void set(long newValue);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// REQUIRE: newValue >= minValue()
		// REQUIRE: newValue <= maxValue()
		// _TAG07 Operations -- from RTRProxyManagedNumericConfig

protected:
// Operations
	void init();
	void update();

// Data
	RTRNumConfigImpl *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedNumericConfig(const RTRShmProxyManagedNumericConfig&);
	RTRShmProxyManagedNumericConfig& operator=(const RTRShmProxyManagedNumericConfig&);
}; 

#endif /* _rtr_shmpmnc_h */
