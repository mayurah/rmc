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
//  created:       January 22, 1996
//  version:       1.0
//


#ifndef __rtr_rgetmem_h
#define __rtr_rgetmem_h

#if !defined(WIN32) && !defined(__OS2__)
#include <sys/param.h>
#endif
#include <sys/types.h>
#include "rtr/memry.h"

// Synopsis:
// #include"rtr/rgetmem.h"
//
// Description:
// See Also:
//	RTRMemoryDefs, RTRAllocRealMem, RTRFixedAllocator, RTRFixedImpAlloc,
//	RTRFixedMemAlloc, RTRManMemStats, RTRManagedMemory,
//	RTRVarAllocator, RTRVarImpAlloc, RTRVarMemAlloc
//
// Inherits:
//	RTRMallocMemory
//

class RTRAllocMem :
	public RTRMallocMemory
{
public:

// Operations
	virtual void * getBytes( size_t bytes ) = 0;
		// Get `bytes' of memory. Return 0
		// if out of memory.
		// _TAG01 Operations

};


// We have to use defines instead of statics since
// we are not sure if the statics will be initialized
// in time.
#ifndef PAGESIZE
#define RTR_PAGESIZE 4096
#else
#define RTR_PAGESIZE PAGESIZE
#endif

#ifdef COMPILE_64BITS
#define RTR_MEMALIGN 8
#else
#define RTR_MEMALIGN 4
#endif

// Synopsis:
// #include"rtr/rgetmem.h"
//
// Description:
// See Also:
//  RTRAllocMem, RTRAllocRealMem, RTRFixedAllocator, RTRFixedImpAlloc,
//  RTRFixedMemAlloc, RTRManMemStats, RTRManagedMemory,
//  RTRVarAllocator, RTRVarImpAlloc, RTRVarMemAlloc
//
// Inherits:
//  RTRMallocMemory
//

class RTRMemoryDefs :
	public RTRMallocMemory
{
public:
	static const size_t	pageSize;		// Page size for OS
	static const size_t	alignment;		// Alignment for OS

	static size_t alignedBytes( size_t bytes );
		// Returns number of bytes needed to properly align.
		// E.g. If quad alignement. Will always
		// be a multiple of 4.
		// _TAG01 Other

	static size_t pageAlign( size_t bytes );
		// Returns number of page aligned bytes needed
		// to satisy a request for `bytes'.
        // _TAG01 Other

	static int shiftBits( size_t bytes );
		// Returns number of bits needs to be shifted
		// to simulate division. bytes must be a
		// power of 2.
		// Returns -1 if `bytes' is not a power of 2.
        // _TAG01 Other

};


#endif
