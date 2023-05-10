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

#ifndef __rtr_fxdmemal_h
#define __rtr_fxdmemal_h

#include "rtr/memry.h"
#include "rtr/fxdall.h"
class RTRAllocMem;
class RTRManMemStats;

// Synopsis:
// #include"rtr/fxdmemal.h"
//
// Description:
// See Also:
// 	RTRAllocMem, RTRAllocRealMem, RTRFixedAllocator, RTRFixedImpAlloc,
//	RTRManMemStats, RTRManagedMemory, RTRMemoryDefs, RTRVarAllocator,
//	RTRVarImpAlloc, RTRVarMemAlloc
//
// Inherits:
//	RTRMemoryAllocator
//

class RTRFixedMemAlloc :
	public RTRMemoryAllocator
{
public:

// Constructor
	RTRFixedMemAlloc(
			RTRFixedAllocator&,
			size_t maxSize,
			RTRMemoryAllocator&,
			RTRManMemStats& );
		// _TAG Constructor

// Destructor
	virtual ~RTRFixedMemAlloc();
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

	size_t				_maxManagedSize;
	RTRFixedAllocator	&_store;
	RTRMemoryAllocator	&_overSizeAlloc;
	RTRManMemStats		&_stats;

#ifdef RTR_MEM_DEBUG
	size_t				_dbgHdrSize;

	void				setDebugHdr(void*,size_t);
	void				checkDebugHdr(void *mem,size_t size);
#endif

};


#endif
