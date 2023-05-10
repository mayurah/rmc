//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmnc0_h
#define _rtr_shmpmnc0_h

#include "rtr/prxymnc.h"
#include "rtr/shmmvar.h"
#include "rtr/shmpmvh0.h"

class RTRShmProxyManagedObject_EliF21;
class RTRShmProxyManagedObject_Mdk10;

// Synopsis:
// #include "rtr/shmpmnc0.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedNumericConfig.
// 
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedCounter_EliF21, 
// RTRShmProxyManagedGauge_EliF21, RTRShmProxyManagedNumeric_EliF21, 
// RTRShmProxyManagedNumericRange_EliF21, RTRShmProxyManagedString_EliF21, 
// RTRShmProxyManagedStringConfig_EliF21
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedNumericConfig ->
// RTRProxyManagedNumeric -> RTRProxyManagedVariable
//

class RTRShmProxyManagedNumericConfig_EliF21 :
	public RTRProxyManagedNumericConfig
{ 
public:
// Constructor
	RTRShmProxyManagedNumericConfig_EliF21(
			RTRShmProxyManagedObject_EliF21&,
			RTRShmProxyManagedVariableHandle_EliF21&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedNumericConfig_EliF21();
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
	RTRShmMNumericConfig_EliF21 *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_EliF21;

private:
// Don't implement
	RTRShmProxyManagedNumericConfig_EliF21(const RTRShmProxyManagedNumericConfig_EliF21&);
	RTRShmProxyManagedNumericConfig_EliF21& operator=(const RTRShmProxyManagedNumericConfig_EliF21&);
}; 

class RTRShmProxyManagedNumericConfig_Mdk10 :
	public RTRProxyManagedNumericConfig
{ 
public:
// Constructor
	RTRShmProxyManagedNumericConfig_Mdk10(
			RTRShmProxyManagedObject_Mdk10&,
			RTRShmProxyManagedVariableHandle_Mdk10&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedNumericConfig_Mdk10();
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
	RTRShmMNumericConfig *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_Mdk10;

private:
// Don't implement
	RTRShmProxyManagedNumericConfig_Mdk10(const RTRShmProxyManagedNumericConfig_Mdk10&);
	RTRShmProxyManagedNumericConfig_Mdk10& operator=(const RTRShmProxyManagedNumericConfig_Mdk10&);
}; 

#endif /* _rtr_shmpmnc0_h */
