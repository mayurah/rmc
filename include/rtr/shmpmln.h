//|---------------------------------------------------------------------------
//|					      Copyright (C) 2008 Reuters,		                --
//|			   U Chu Liang Building, 968 Rama IV Road, Bangkok 10500	    --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: N. Sotanakun
// Created: "Apr. 10 2008"
// Version: 1.0

#ifndef _rtr_shmpmln_h
#define _rtr_shmpmln_h

#include "rtr/prxymln.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// Synopsis:
// #include "rtr/shmpmln.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedLargeNumeric.
// 
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBoolean, 
// RTRShmProxyManagedBooleanConfig, RTRShmProxyManagedCounter, 
// RTRShmProxyManagedGauge, RTRShmProxyManagedGaugeConfig, 
// RTRShmProxyManagedNumericConfig, RTRShmProxyManagedNumericRange, 
// RTRShmProxyManagedString, RTRShmProxyManagedStringConfig
// 
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedLargeNumeric -> RTRProxyManagedVariable//

class RTRShmProxyManagedLargeNumeric :
	public RTRProxyManagedLargeNumeric
{ 
public:
// Constructor
	RTRShmProxyManagedLargeNumeric(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedLargeNumeric();
		// _TAG Destructor

protected:
// Operations
	void init();
	void update();

// Data
	RTRLargeNumericImpl *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedLargeNumeric(const RTRShmProxyManagedLargeNumeric&);
	RTRShmProxyManagedLargeNumeric& operator=(const RTRShmProxyManagedLargeNumeric&);
}; 

#endif /* _rtr_shmpmln_h */
