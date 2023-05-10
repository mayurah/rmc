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

#ifndef __rtr_varall_h
#define __rtr_varall_h

#include "rtr/memry.h"

class RTRAllocMem;
class RTRManMemStats;

// Synopsis:
// #include"rtr/varall.h"
//
// Description:
// See Also:
//	RTRAllocMem, RTRAllocRealMem, RTRFixedAllocator, RTRFixedImpAlloc,
//	RTRFixedMemAlloc, RTRManMemStats, RTRManagedMemory, RTRMemoryDefs,
//	RTRVarImpAlloc, RTRVarMemAlloc
//
// Inherits:
//	RTRMallocMemory
//

class RTRVarAllocator :
	public RTRMallocMemory
{
public:

// Constructor
	RTRVarAllocator(
			RTRAllocMem&,
			RTRManMemStats&,
			size_t minManaged,
			size_t maxManaged,
			size_t granularity );
		// _TAG Constructor

// Destructor
	~RTRVarAllocator();
		// _TAG Destructor

// Attributes
	inline size_t minimum();
		// _TAG01 Attributes

	inline size_t maximum();
        // _TAG01 Attributes    

	inline size_t gran();
        // _TAG01 Attributes    

// Operations
	void * allocate(size_t size,size_t *allocatedSize);
		// _TAG02 Operations

	void deallocate(void *mem,size_t size);
        // _TAG02 Operations

	void preallocate(size_t size,size_t count);
		// _TAG02 Operations

protected:

	RTRAllocMem	&_mem;
	RTRManMemStats &_stats;
	void		**_freeArray;
	size_t		_maxManagedSize;
	size_t		_minManagedSize;
	size_t		_granularity;
	size_t		_minSub;
	size_t		_shift;
	int			_maxIndex;

	void		*_lockInfo;         // If thread safe, any lock information.
									// It has to be done this way so we can
									// link in the version after compilation.

};

inline size_t RTRVarAllocator::minimum() { return(_minManagedSize);};
inline size_t RTRVarAllocator::maximum() {return(_maxManagedSize);};
inline size_t RTRVarAllocator::gran() {return(_granularity);};

#endif
