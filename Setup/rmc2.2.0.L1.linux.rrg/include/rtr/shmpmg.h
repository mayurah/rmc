//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmg_h
#define _rtr_shmpmg_h

#include "rtr/prxymg.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// Synopsis:
// #include "rtr/shmpmg.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedGauge.
//
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBoolean, 
// RTRShmProxyManagedBooleanConfig, RTRShmProxyManagedCounter, 
// RTRShmProxyManagedGaugeConfig, RTRShmProxyManagedNumeric, 
// RTRShmProxyManagedNumericConfig, RTRShmProxyManagedNumericRange, 
// RTRShmProxyManagedString, RTRShmProxyManagedStringConfig
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedGauge -> RTRProxyManagedNumeric ->
// RTRProxyManagedVariable
//

class RTRShmProxyManagedGauge :
	public RTRProxyManagedGauge
{ 
public:
// Constructor
	RTRShmProxyManagedGauge(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedGauge();
		// _TAG Destructor

// Operations -- from RTRProxyManagedGauge
	void setRange(long newMin, long newMax);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// REQUIRE: newMin <= newMax
		// _TAG07 Operations -- from RTRProxyManagedGauge

protected:
// Operations
	void init();
	void update();

// Data
	RTRGaugeImpl *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedGauge(const RTRShmProxyManagedGauge&);
	RTRShmProxyManagedGauge& operator=(const RTRShmProxyManagedGauge&);
}; 

#endif /* _rtr_shmpmg_h */
