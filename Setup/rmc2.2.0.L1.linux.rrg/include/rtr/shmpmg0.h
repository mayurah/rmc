//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmg0_h
#define _rtr_shmpmg0_h

#include "rtr/prxymg.h"
#include "rtr/shmmvar.h"
#include "rtr/shmpmvh0.h"

class RTRShmProxyManagedObject_EliF21;
class RTRShmProxyManagedObject_Mdk10;

// Synopsis:
// #include "rtr/shmpmg0.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedGauge.
//
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedCounter_EliF21, 
// RTRShmProxyManagedNumeric_EliF21, RTRShmProxyManagedNumericConfig_EliF21, 
// RTRShmProxyManagedNumericRange_EliF21, RTRShmProxyManagedString_EliF21, 
// RTRShmProxyManagedStringConfig_EliF21
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedGauge -> RTRProxyManagedNumeric ->
// RTRProxyManagedVariable
//

class RTRShmProxyManagedGauge_EliF21 :
	public RTRProxyManagedGauge
{ 
public:
// Constructor
	RTRShmProxyManagedGauge_EliF21(
			RTRShmProxyManagedObject_EliF21&,
			RTRShmProxyManagedVariableHandle_EliF21&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedGauge_EliF21();
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
	RTRShmMNumericRange_EliF21 *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_EliF21;

private:
// Don't implement
	RTRShmProxyManagedGauge_EliF21(const RTRShmProxyManagedGauge_EliF21&);
	RTRShmProxyManagedGauge_EliF21& operator=(const RTRShmProxyManagedGauge_EliF21&);
}; 


class RTRShmProxyManagedGauge_Mdk10 :
	public RTRProxyManagedGauge
{ 
public:
// Constructor
	RTRShmProxyManagedGauge_Mdk10(
			RTRShmProxyManagedObject_Mdk10&,
			RTRShmProxyManagedVariableHandle_Mdk10&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedGauge_Mdk10();
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
	RTRShmMNumericRange *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_Mdk10;

private:
// Don't implement
	RTRShmProxyManagedGauge_Mdk10(const RTRShmProxyManagedGauge_Mdk10&);
	RTRShmProxyManagedGauge_Mdk10& operator=(const RTRShmProxyManagedGauge_Mdk10&);
}; 

#endif /* _rtr_shmpmg0_h */

