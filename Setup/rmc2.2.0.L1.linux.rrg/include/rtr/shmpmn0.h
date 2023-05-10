//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.27"
// Version: 1.0

#ifndef _rtr_shmpmn0_h
#define _rtr_shmpmn0_h

#include "rtr/prxymn.h"
#include "rtr/shmmvar.h"
#include "rtr/shmpmvh0.h"

class RTRShmProxyManagedObject_EliF21;
class RTRShmProxyManagedObject_Mdk10;

// Synopsis:
// #include "rtr/shmpmn0.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedNumeric.
//
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedCounter_EliF21, 
// RTRShmProxyManagedGauge_EliF21, RTRShmProxyManagedNumericConfig_EliF21, 
// RTRShmProxyManagedNumericRange_EliF21, RTRShmProxyManagedString_EliF21, 
// RTRShmProxyManagedStringConfig_EliF21
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedNumeric -> RTRProxyManagedVariable
//

class RTRShmProxyManagedNumeric_EliF21 :
	public RTRProxyManagedNumeric
{ 
public:
// Constructor
	RTRShmProxyManagedNumeric_EliF21(
			RTRShmProxyManagedObject_EliF21&,
			RTRShmProxyManagedVariableHandle_EliF21&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedNumeric_EliF21();
		// _TAG Destructor

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
	RTRShmProxyManagedNumeric_EliF21(const RTRShmProxyManagedNumeric_EliF21&);
	RTRShmProxyManagedNumeric_EliF21& operator=(const RTRShmProxyManagedNumeric_EliF21&);
}; 

class RTRShmProxyManagedNumeric_Mdk10 :
	public RTRProxyManagedNumeric
{ 
public:
// Constructor
	RTRShmProxyManagedNumeric_Mdk10(
			RTRShmProxyManagedObject_Mdk10&,
			RTRShmProxyManagedVariableHandle_Mdk10&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedNumeric_Mdk10();
		// _TAG Destructor

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
	RTRShmProxyManagedNumeric_Mdk10(const RTRShmProxyManagedNumeric_Mdk10&);
	RTRShmProxyManagedNumeric_Mdk10& operator=(const RTRShmProxyManagedNumeric_Mdk10&);
}; 

#endif /* _rtr_shmpmn0_h */
