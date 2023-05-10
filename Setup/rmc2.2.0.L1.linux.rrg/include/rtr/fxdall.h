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

#ifndef __rtr_fxdall_h
#define __rtr_fxdall_h

#include "rtr/memry.h"

class RTRAllocMem;
class RTRManMemStats;

// Synopsis:
// #include"rtr/fxdall.h"
//
// Description:
// See Also:
//	RTRAllocMem, RTRAllocRealMem, RTRFixedImpAlloc,
//	RTRFixedMemAlloc, RTRManMemStats, RTRManagedMemory, RTRMemoryDefs,
//	RTRVarAllocator, RTRVarImpAlloc, RTRVarMemAlloc
//
// Inherits:
//	RTRMallocMemory
//

class RTRFixedAllocator :
	public RTRMallocMemory
{
public:

// Constructor
	RTRFixedAllocator(RTRAllocMem&,size_t maxMgd,RTRManMemStats&);
		// _TAG Constructor

// Destructor
	~RTRFixedAllocator();
		// _TAG Destructor

// Operations
	void * allocate(size_t size,size_t *allocatedSize);
		// _TAG01 Operations

	void deallocate(void *mem,size_t size);
        // _TAG01 Operations

	void preallocate(size_t size,size_t count);
        // _TAG01 Operations


protected:

	RTRAllocMem	&_mem;
	RTRManMemStats	&_stats;
	void		**_freeArray;
	size_t		_maxManagedSize;	// Maximum size that will be memory managed.
	int			_shift;
	int			_maxIndex;

	void		*_lockInfo;			// If thread safe, any lock information.
									// It has to be done this way so we can
									// link in the version after compilation.
};

#endif
