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

#ifndef __rtr_varmemal_h
#define __rtr_varmemal_h

#include "rtr/memry.h"
#include "rtr/varall.h"
class RTRAllocMem;
class RTRManMemStats;

// Synopsis:
// #include"rtr/varmemal.h"
//
// Description:
// See Also:
//	RTRAllocMem, RTRAllocRealMem, RTRFixedAllocator, RTRFixedImpAlloc,
//	RTRFixedMemAlloc, RTRManMemStats, RTRManagedMemory, RTRMemoryDefs,
//	RTRVarAllocator, RTRVarImpAlloc
//
// Inherits:
//	RTRMemoryAllocator
//

class RTRVarMemAlloc :
	public RTRMemoryAllocator
{
public:

// Constructor
	RTRVarMemAlloc(int levels,RTRVarAllocator **varAlloc,RTRManMemStats&,RTRBOOL secUseRealMem = RTRTRUE);
		// _TAG Constructor

// Destructor
	virtual ~RTRVarMemAlloc();
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

	RTRBOOL			_secUseRealMem;
	int				_levels;
	RTRVarAllocator	**_allocators;
	RTRManMemStats	&_stats;


#ifdef RTR_MEM_DEBUG
	size_t			_dbgHdrSize;
	size_t			_dbgFtrSize;

	void			setDebugHdr(void* mem,size_t);
	void			checkDebugHdr(void* mem,size_t size);
	void			setDebugFtr(void* mem, size_t size);
	void			checkDebugFtr(void* mem, size_t size);
#endif

};


#endif
