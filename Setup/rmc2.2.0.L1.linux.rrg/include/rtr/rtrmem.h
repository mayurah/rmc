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


#ifndef __rtr_rtrmem_h
#define __rtr_rtrmem_h

#include "rtr/memry.h"

// Synopsis:
// #inlcude"rtr/rtrmem.h"
// 
// Description:
//	By including this header, system components have access to the
//  global memory manager, which provides facilities to allocate
//  and deallocate memory.
//
//  The exact implementation of the manager is decided at link time.
//  Specifically, the following external "C" functions must be
//  provided:
// 	
//	\bullet
//		o RTRMemory *rtr_init_mem_manager() --
//              Create memory manager if does not exist and
//              return a pointer to it.
//		o RTRMemoryAllocator &rtr_getFixedExp() --
//              Return reference to the fixed explicit allocator.
//		o RTRMemoryAllocator &rtr_getVarExp() --
//              Return reference to the variable explicit allocator.
//		o RTRMemoryAllocator &rtr_getVarImpl() --
//              Return reference to the variable implicit allocator.
//	\endbullet
//
//  Typically, the above functions are defined in the source files
//  which implement a particular memory manager. The object file
//  for that source code then provides everything needed for linking
//  a memory manager into an executable program.
//
// See Also:
//	RTRManageClass, RTRMallocMemory, RTRMemory, RTRMemoryAllocator
//

class RTRMemManager
{
public:

// Constructor
	RTRMemManager();
		// _TAG Constructor

// Destructor
	~RTRMemManager();
		// _TAG Destructor

// Manager.
	static RTRMemory *memManager;
		// Manager

// Allocators
	static RTRMemoryAllocator *fixedImplAlloc;
	static RTRMemoryAllocator *fixedExplAlloc;
	static RTRMemoryAllocator *varImplAlloc;
	static RTRMemoryAllocator *varExplAlloc;


protected:

	static int count;
	static int allocated;
};

static RTRMemManager RTRMemoryManager;
	// RTRMemoryManager

// Synopsis:
// #include"rtr/rtrmem.h"
//
// Description:
// 	A RTRManageClass overwrites the new and delete of
// 	a class to use the memory manager. A class that
// 	wants this functionality would inherit from this
// 	class.
//
// See Also:
//	RTRMemManager, RTRMallocMemory, RTRMemory, RTRMemoryAllocator
//

class RTRManageClass
{
public:

// Constructor
	inline RTRManageClass() {};
		// _TAG Constructor

// Destructor
	virtual ~RTRManageClass();
		// _TAG Destructor

#if defined(x86_Linux_2X) || defined(x86_Linux_3X) || defined(x86_Linux_4X)
	void *operator new(size_t) throw();
#else
	void *operator new(size_t);
#endif
		// _TAG01 Other

	void operator	delete(void*,size_t);
		// _TAG01 Other

};

#endif
