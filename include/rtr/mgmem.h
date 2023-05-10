//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       May 1, 1996
//  version:       1.0
//
//	defines:
//

#ifndef __rtr_mgmem_h
#define __rtr_mgmem_h

#include "rtr/memry.h"
#include "rtr/rtratomic.h"
#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

class RTRFixedMemAlloc;
class RTRAllocRealMem;
class RTRFixedImpAlloc;
class RTRFixedAllocator;
class RTRVarAllocator;
class RTRVarMemAlloc;
class RTRVarImpAlloc;

// Synopsis:
// #include"rtr/mgmem.h"
//
// Description:
// See Also:
//	RTRManagedMemory, RTRAllocMem, RTRAllocRealMem, RTRFixedAllocator,
//	RTRFixedImpAlloc, RTRFixedMemAlloc, RTRMemoryDefs, RTRVarAllocator,
//	RTRVarImpAlloc, RTRVarMemAlloc
//
// Inherits:
//	RTRMallocMemory
//

class RTRManMemStats :
	public RTRMallocMemory
{
public:
	RTRManMemStats();
		// _TAG Constructor

	rtr_atomic_val allocatorType;
		enum { allocNoThread, allocSingleLock, allocMultLock };

	rtr_atomic_val numMutexes;
	rtr_atomic_val pageSize;
	rtr_atomic_val byteAlignment;
	rtr_atomic_val pagePerAlloc;

	rtr_atomic_val numAllocations;
	rtr_atomic_val numDeallocations;

	rtr_atomic_val bytesAskedFor;
	rtr_atomic_val bytesFreed;

	rtr_atomic_val bytesAllocated;
		// Total number of bytes allocated by memory manager.

	rtr_atomic_val nonMgdBytes;
		// Total number of non memory managed bytes.

	rtr_atomic_val elementsInFreeLists;
		// Total number of elements in free lists.

	rtr_atomic_val elementsInUse;
		// Total number of elements in use.

	rtr_atomic_val overheadBytes;

	rtr_atomic_val wastedBytes;

	rtr_atomic_val chunksInUse;
	rtr_atomic_val freedChunks;

};

// Synopsis:
// #include"rtr/mgmem.h"
//
// Description:
// See Also:
//  RTRManMemStats, RTRAllocMem, RTRAllocRealMem, RTRFixedAllocator,
//  RTRFixedImpAlloc, RTRFixedMemAlloc, RTRMemoryDefs, RTRVarAllocator,
//  RTRVarImpAlloc, RTRVarMemAlloc
//
// Inherits:
//  RTRMemory
//

class RTRManagedMemory :
	public RTRMemory
{
public:

// Constructor
	RTRManagedMemory();
		// _TAG Constructor

// Destructor
	virtual ~RTRManagedMemory();
		// _TAG Destructor

// From RTRMemory
	virtual RTRMemoryAllocator & allocator(rtrMemAttributes);
		// _TAG01 From RTRMemory

#ifndef _RDEV_NO_STL_
	virtual void dump( std::ostream& );
		// _TAG01 From RTRMemory
#else
	virtual void dump( FILE* );
		// _TAG01 From RTRMemory
#endif
protected:

	RTRManMemStats		_stats;

	RTRFixedMemAlloc	*fixedMem;
	RTRFixedImpAlloc	*fixedImpl;
	RTRFixedAllocator	*fxdAlloc;

	RTRAllocRealMem		*realMem;

	size_t				_maxFxdMgdSize;

	RTRVarMemAlloc		*varMem;
	RTRVarImpAlloc		*varImpl;
	int					_varLevels;
	RTRVarAllocator		**varAlloc;

};


#endif
