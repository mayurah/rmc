//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmc0_h
#define _rtr_shmpmc0_h

#include "rtr/prxymc.h"
#include "rtr/shmmvar.h"
#include "rtr/shmpmvh0.h"

class RTRShmProxyManagedObject_EliF21;
class RTRShmProxyManagedObject_Mdk10;

// Synopsis:
// #include "rtr/shmpmc0.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedCounter.
//
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedGauge_EliF21, 
// RTRShmProxyManagedNumeric_EliF21, RTRShmProxyManagedNumericConfig_EliF21, 
// RTRShmProxyManagedNumericRange_EliF21, RTRShmProxyManagedString_EliF21, 
// RTRShmProxyManagedStringConfig_EliF21
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedCounter -> RTRProxyManagedVariable
//

class RTRShmProxyManagedCounter_EliF21 :
	public RTRProxyManagedCounter
{ 
public:
// Constructor
	RTRShmProxyManagedCounter_EliF21(
			RTRShmProxyManagedObject_EliF21&,
			RTRShmProxyManagedVariableHandle_EliF21&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedCounter_EliF21();
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
	RTRShmMNumeric_EliF21 *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_EliF21;

private:
// Don't implement
	RTRShmProxyManagedCounter_EliF21(const RTRShmProxyManagedCounter_EliF21&);
	RTRShmProxyManagedCounter_EliF21& operator=(const RTRShmProxyManagedCounter_EliF21&);
}; 

class RTRShmProxyManagedCounter_Mdk10 :
	public RTRProxyManagedCounter
{ 
public:
// Constructor
	RTRShmProxyManagedCounter_Mdk10(
			RTRShmProxyManagedObject_Mdk10&,
			RTRShmProxyManagedVariableHandle_Mdk10&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedCounter_Mdk10();
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
	RTRShmMNumeric *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_Mdk10;

private:
// Don't implement
	RTRShmProxyManagedCounter_Mdk10(const RTRShmProxyManagedCounter_Mdk10&);
	RTRShmProxyManagedCounter_Mdk10& operator=(const RTRShmProxyManagedCounter_Mdk10&);
}; 

#endif /* _rtr_shmpmc0_h */

