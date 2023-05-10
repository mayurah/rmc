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

#ifndef __rtr_varimpal_h
#define __rtr_varimpal_h

#include "rtr/memry.h"
#include "rtr/varall.h"
class RTRAllocMem;
class RTRManMemStats;

// Synopsis:
// #include"rtr/varimpal.h"
//
// Description:
// See Also:
//	RTRAllocMem, RTRAllocRealMem, RTRFixedAllocator, RTRFixedImpAlloc, 
//	RTRFixedMemAlloc, RTRManMemStats, RTRManagedMemory, RTRMemoryDefs,
//	RTRVarAllocator, RTRVarMemAlloc
//
// Inherits:
//	RTRMemoryAllocator
//

class RTRVarImpAlloc :
	public RTRMemoryAllocator
{
public:

// Constructor
	RTRVarImpAlloc(int levels,RTRVarAllocator **varAlloc,RTRManMemStats&,RTRBOOL secUseRealMem = RTRTRUE);
		// _TAG Constructor

// Destructor
	virtual ~RTRVarImpAlloc();
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
	size_t			_hdrSize;


#ifdef RTR_MEM_DEBUG
	size_t				_dbgHdrSize;
	size_t				_dbgFtrSize;

	void				setDebugHdr(void* mem);
	void				checkDebugHdr(void *mem);
	void				setDebugFtr(void* mem,size_t size);
	void				checkDebugFtr(void* mem,size_t size);
#endif

};


#endif
