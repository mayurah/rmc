//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmnr_h
#define _rtr_shmpmnr_h

#include "rtr/prxymnr.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// Synopsis:
// #include "rtr/shmpmnr.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedNumericRange.
//
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBoolean, 
// RTRShmProxyManagedBooleanConfig, RTRShmProxyManagedCounter, 
// RTRShmProxyManagedGauge, RTRShmProxyManagedGaugeConfig, 
// RTRShmProxyManagedNumeric, RTRShmProxyManagedNumericConfig, 
// RTRShmProxyManagedString, RTRShmProxyManagedStringConfig
// 
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedNumericRange ->
// RTRProxyManagedNumeric -> RTRProxyManagedVariable
//

class RTRShmProxyManagedNumericRange :
	public RTRProxyManagedNumericRange
{ 
public:
// Constructor
	RTRShmProxyManagedNumericRange(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedNumericRange();
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
	RTRNumRangeImpl *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedNumericRange(const RTRShmProxyManagedNumericRange&);
	RTRShmProxyManagedNumericRange& operator=(const RTRShmProxyManagedNumericRange&);
}; 

#endif /* _rtr_shmpmnr_h */
