//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmgc_h
#define _rtr_shmpmgc_h

#include "rtr/prxymgc.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// @synopsis
// #include "rtr/shmpmgc.h"
//
// @description
// A shared memory based implementation of a RTRProxyManagedGaugeConfig.
// 
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBoolean, 
// RTRShmProxyManagedBooleanConfig, RTRShmProxyManagedCounter, 
// RTRShmProxyManagedGauge, RTRShmProxyManagedNumeric, 
// RTRShmProxyManagedNumericConfig, RTRShmProxyManagedNumericRange, 
// RTRShmProxyManagedString, RTRShmProxyManagedStringConfig
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedGaugeConfig ->
// RTRProxyManagedGauge -> RTRProxyManagedVariable
//

class RTRShmProxyManagedGaugeConfig :
	public RTRProxyManagedGaugeConfig
{ 
public:
// Constructor
	RTRShmProxyManagedGaugeConfig(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedGaugeConfig();
		// _TAG Destructor

// Operations -- from RTRProxyManagedGaugeConfig
	void setRange(long newMin, long newMax);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// REQUIRE: newMin <= newMax
		// _TAG07 Operations -- from RTRProxyManagedGaugeConfig

protected:
// Operations
	void init();
	void update();

// Data
	RTRGaugeConfigImpl *_varImpl;	

// Friends
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedGaugeConfig(const RTRShmProxyManagedGaugeConfig&);
	RTRShmProxyManagedGaugeConfig& operator=(const RTRShmProxyManagedGaugeConfig&);
}; 

#endif /* _rtr_shmpmgc_h */
