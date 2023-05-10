//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.27"
// Version: 1.0

#ifndef _rtr_shmpmn_h
#define _rtr_shmpmn_h

#include "rtr/prxymn.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// Synopsis:
// #include "rtr/shmpmn.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedNumeric.
// 
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBoolean, 
// RTRShmProxyManagedBooleanConfig, RTRShmProxyManagedCounter, 
// RTRShmProxyManagedGauge, RTRShmProxyManagedGaugeConfig, 
// RTRShmProxyManagedNumericConfig, RTRShmProxyManagedNumericRange, 
// RTRShmProxyManagedString, RTRShmProxyManagedStringConfig
// 
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedNumeric -> RTRProxyManagedVariable//

class RTRShmProxyManagedNumeric :
	public RTRProxyManagedNumeric
{ 
public:
// Constructor
	RTRShmProxyManagedNumeric(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedNumeric();
		// _TAG Destructor

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
	RTRShmProxyManagedNumeric(const RTRShmProxyManagedNumeric&);
	RTRShmProxyManagedNumeric& operator=(const RTRShmProxyManagedNumeric&);
}; 

#endif /* _rtr_shmpmn_h */
