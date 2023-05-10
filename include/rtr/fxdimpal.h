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

#ifndef __rtr_fxdimpal_h
#define __rtr_fxdimpal_h

#include "rtr/memry.h"
#include "rtr/fxdall.h"
class RTRAllocMem;
class RTRManMemStats;

// Synopsis:
// #include"rtr/fxdimpal.h"
//
// Description:
// See Also:
//	RTRAllocMem, RTRAllocRealMem, RTRFixedAllocator, RTRFixedMemAlloc,
//	RTRManMemStats, RTRManagedMemory, RTRMemoryDefs, RTRVarAllocator, 
//	RTRVarImpAlloc, RTRVarMemAlloc 
//
// Inherits:
//	RTRMemoryAllocator
//

class RTRFixedImpAlloc :
	public RTRMemoryAllocator
{
public:

// Constructor
	RTRFixedImpAlloc(
			RTRFixedAllocator&,
			size_t maxSize,
			RTRMemoryAllocator&,
			RTRManMemStats&);
		// _TAG Constructor

// Destructor
	virtual ~RTRFixedImpAlloc();
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
	RTRManMemStats		&_stats;
	RTRFixedAllocator	&_store;
	RTRMemoryAllocator	&_overSizeAlloc;
	size_t				_hdrSize;

#ifdef RTR_MEM_DEBUG
	size_t				_dbgHdrSize;

	void				setDebugHdr(void*);
	void				checkDebugHdr(void *mem);
#endif

};


#endif
