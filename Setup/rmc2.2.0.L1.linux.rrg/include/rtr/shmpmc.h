//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmc_h
#define _rtr_shmpmc_h

#include "rtr/prxymc.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// Synopsis:
// #include "rtr/shmpmc.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedCounter.
//
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBoolean, 
// RTRShmProxyManagedBooleanConfig, RTRShmProxyManagedGauge, 
// RTRShmProxyManagedGaugeConfig, RTRShmProxyManagedNumeric, 
// RTRShmProxyManagedNumericConfig, RTRShmProxyManagedNumericRange, 
// RTRShmProxyManagedString, RTRShmProxyManagedStringConfig
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedCounter -> RTRProxyManagedVariable
//

class RTRShmProxyManagedCounter :
	public RTRProxyManagedCounter
{ 
public:
// Constructor
	RTRShmProxyManagedCounter(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedCounter();
		// _TAG Destructor

// Operations -- from RTRProxyManagedCounter
	void reset();
		// REQUIRE: inSync() && !error()
		// _TAG07 Operations

protected:
// Operations	
	void init();
	void update();

// Data
	RTRNumericImpl *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedCounter(const RTRShmProxyManagedCounter&);
	RTRShmProxyManagedCounter& operator=(const RTRShmProxyManagedCounter&);
}; 

#endif /* _rtr_shmpmc_h */
