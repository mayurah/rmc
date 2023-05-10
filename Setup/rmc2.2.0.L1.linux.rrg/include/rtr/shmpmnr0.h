//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmnr0_h
#define _rtr_shmpmnr0_h

#include "rtr/prxymnr.h"
#include "rtr/shmmvar.h"
#include "rtr/shmpmvh0.h"

class RTRShmProxyManagedObject_EliF21;
class RTRShmProxyManagedObject_Mdk10;

// Synopsis:
// #include "rtr/shmpmnr0.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedNumericRange.
//
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedCounter_EliF21, 
// RTRShmProxyManagedGauge_EliF21, RTRShmProxyManagedNumeric_EliF21, 
// RTRShmProxyManagedNumericConfig_EliF21, RTRShmProxyManagedString_EliF21, 
// RTRShmProxyManagedStringConfig_EliF21
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedNumericRange ->
// RTRProxyManagedNumeric -> RTRProxyManagedVariable
//

class RTRShmProxyManagedNumericRange_EliF21 :
	public RTRProxyManagedNumericRange
{ 
public:
// Constructor
	RTRShmProxyManagedNumericRange_EliF21(
			RTRShmProxyManagedObject_EliF21&,
			RTRShmProxyManagedVariableHandle_EliF21&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedNumericRange_EliF21();
		// _TAG Destructor

// Operations -- from RTRProxyManagedNumericRange
	void set(long newValue);
		// REQUIRE: inSync() && !error()
		// REQUIRE: newValue >= minValue()
		// REQUIRE: newValue <= maxValue()
		// _TAG07 Operations -- from RTRProxyManagedNumericRange

protected:
// Utilities
	void init();
	void update();

// Data
	RTRShmMNumericRange_EliF21 *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_EliF21;

private:
// Don't implement
	RTRShmProxyManagedNumericRange_EliF21(const RTRShmProxyManagedNumericRange_EliF21&);
	RTRShmProxyManagedNumericRange_EliF21& operator=(const RTRShmProxyManagedNumericRange_EliF21&);
}; 

class RTRShmProxyManagedNumericRange_Mdk10 :
	public RTRProxyManagedNumericRange
{ 
public:
// Constructor
	RTRShmProxyManagedNumericRange_Mdk10(
			RTRShmProxyManagedObject_Mdk10&,
			RTRShmProxyManagedVariableHandle_Mdk10&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedNumericRange_Mdk10();
		// _TAG Destructor

// Operations -- from RTRProxyManagedNumericRange
	void set(long newValue);
		// REQUIRE: inSync() && !error()
		// REQUIRE: newValue >= minValue()
		// REQUIRE: newValue <= maxValue()
		// _TAG07 Operations -- from RTRProxyManagedNumericRange

protected:
// Utilities
	void init();
	void update();

// Data
	RTRShmMNumericRange *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_Mdk10;

private:
// Don't implement
	RTRShmProxyManagedNumericRange_Mdk10(const RTRShmProxyManagedNumericRange_Mdk10&);
	RTRShmProxyManagedNumericRange_Mdk10& operator=(const RTRShmProxyManagedNumericRange_Mdk10&);
}; 

#endif /* _rtr_shmpmnr0_h */
