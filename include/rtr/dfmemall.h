//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:     Robert Bonaguro
//  created:    March 19, 1996
//  version:    1.0
//

#ifndef __rtr_dfmemall_h
#define __rtr_dfmemall_h

#include "rtr/memry.h"

// Synopsis:
// #include"rtr/dfmemall.h"
//
// Description:
// See Also:
//	RTRDfltMemoryMgr
//
// Inherits:
//	RTRMemoryAllocator
//

class RTRDfltMemAlloc :
	public RTRMemoryAllocator
{
public:

// Constructor
	RTRDfltMemAlloc(RTRBOOL fixed);
		// _TAG Constructor

// Destructor
	virtual ~RTRDfltMemAlloc();
		// _TAG Destructor

// Attributes
	virtual rtrMemAttributes attributes() const;
		// _TAG01 Attributes

// Operations
	virtual void * allocate(size_t size,size_t *allocatedSize);
		// _TAG02 Operations

	virtual void deallocate(void *mem,size_t size);
		// _TAG02 Operations

	virtual void preallocate(size_t size,size_t count);
		// _TAG02 Operations

protected:

	RTRBOOL _fixed;

};

#endif
