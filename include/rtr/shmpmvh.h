//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/32/00"
// Version: 1.0

#ifndef _rtr_shmpmvh_h
#define _rtr_shmpmvh_h

#include "rtr/prxyh.h"
#include "rtr/mvimpl.h"


// Synopsis:
// #include "rtr/shmpmvh.h"
//
// Description:
// 
// See Also:
//
// Inherits:
// RTRProxyManagedVariableHandle
//

class RTRShmProxyManagedVariableHandle :
	public RTRProxyManagedVariableHandle
{ 
public:
// Constructor
	RTRShmProxyManagedVariableHandle(
			const RTRString& name,
			int type,
			MVAddr *impl,
			rtrUIntPtr base
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedVariableHandle();
		// _TAG Destructor

// Access
	inline RTRMVImpl *impl() const;

protected:
// Data
	RTRMVImpl *_impl;

private:
// Don't implement
	RTRShmProxyManagedVariableHandle(const RTRShmProxyManagedVariableHandle&);
	RTRShmProxyManagedVariableHandle& operator=(const RTRShmProxyManagedVariableHandle&);
}; 

inline RTRMVImpl *RTRShmProxyManagedVariableHandle::impl() const
{
	return _impl;
}

#endif /* _rtr_shmpmvh_h */
