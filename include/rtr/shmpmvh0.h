//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/31/00"
// Version: 1.0

#ifndef _rtr_shmpmvh0_h
#define _rtr_shmpmvh0_h

#include "rtr/prxyh.h"
#include "rtr/shmmvar.h"


// Synopsis:
// #include "rtr/shmpmvh0.h"
//
// Description:
//
// See Also:
//
// Inherits:
// RTRProxyManagedVariableHandle
//

class RTRShmProxyManagedVariableHandle_EliF21 :
	public RTRProxyManagedVariableHandle
{ 
public:
// Constructor
	RTRShmProxyManagedVariableHandle_EliF21(
			const RTRString& nm,
			int type,
			RTRShmMVariable_EliF21 *impl
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedVariableHandle_EliF21();
		// _TAG Destructor

// Access
	inline RTRShmMVariable_EliF21 *impl() const;

protected:
// Data
	RTRShmMVariable_EliF21 *_impl;

private:
// Don't implement
	RTRShmProxyManagedVariableHandle_EliF21(const RTRShmProxyManagedVariableHandle_EliF21&);
	RTRShmProxyManagedVariableHandle_EliF21& operator=(const RTRShmProxyManagedVariableHandle_EliF21&);
}; 

inline
RTRShmMVariable_EliF21 *RTRShmProxyManagedVariableHandle_EliF21::impl() const
{
	return _impl;
}

class RTRShmProxyManagedVariableHandle_Mdk10 :
	public RTRProxyManagedVariableHandle
{ 
public:
// Constructor
	RTRShmProxyManagedVariableHandle_Mdk10(
			const RTRString& nm,
			int type,
			RTRShmMVariable *impl
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedVariableHandle_Mdk10();
		// _TAG Destructor

// Access
	inline RTRShmMVariable *impl() const;

protected:
// Data
	RTRShmMVariable *_impl;

private:
// Don't implement
	RTRShmProxyManagedVariableHandle_Mdk10(const RTRShmProxyManagedVariableHandle_Mdk10&);
	RTRShmProxyManagedVariableHandle_Mdk10& operator=(const RTRShmProxyManagedVariableHandle_Mdk10&);
}; 

inline
RTRShmMVariable *RTRShmProxyManagedVariableHandle_Mdk10::impl() const
{
	return _impl;
}

#endif /* _rtr_shmpmvh0_h */

