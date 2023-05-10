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
//              Kevin Nicodemus
//  created:    March 19, 1996
//  version:    1.0
//

#ifndef __rtr_memalc_h
#define __rtr_memalc_h

#include "rtr/systypes.h"
#include "rtr/rtrdefs.h"

typedef unsigned long rtrMemAttributes;


//
// Description:
//  This class redefines the class member functions new() and delete().
//  These are implemented to use "malloc" and "free" from the c run-time
//  in order to make it possible to overwrite the global new and delete.
//  All relevant classes the memory allocator instantiates must inherit
//  from this class so it uses malloc and free for construction and
//  destruction.
//
//  In the case global new and delete are implemented to use the
//  memory allocator. When the allocator initializes, any object
//  created will call the global new in order to get the memory for
//  the object if this class is not used.
//
// See Also:
//	RTRMemoryAllocator, RTRManageClass, RTRMemManager, RTRMemory
//

class RTRMallocMemory
{
public:

	void *operator	new(size_t);
		// _TAG01 Other

	void operator	delete(void*,size_t);
		// _TAG01 Other

};



// Synopsis:
// #include"rtr/memalc.h"
//
// Description:
//  This abstract class defines the public interface of a memory
//  allocator.
//
//  The memory allocator is an abstract interface used to allocate
//  and deallocate memory. An allocator has attributes associated
//  with it on how its memory management is performed and the types
//  of memory it provides.
//
// See Also:
//  RTRManageClass, RTRMemManager, RTRMemory
//
// Inherits:
//	RTRMallocMemory
//

class RTRMemoryAllocator :
	public RTRMallocMemory
{
public:

// Destructor
	virtual ~RTRMemoryAllocator();
		// _TAG Destructor

// Attributes
	virtual rtrMemAttributes attributes() const = 0;
		// _TAG01 Attributes

// Operations
	virtual void * allocate(size_t size,size_t *allocatedSize = 0) = 0;
		// Allocate memory of `size' bytes. Put the
		// actual allocated size in `allocatedSize' if
		// it exists.
		// REQUIRE : attributes().isImplicit() || (allocatedSize != 0)
		// _TAG02 Operations

	virtual void deallocate(void *mem,size_t size = 0) = 0;
		// Return memory block `mem' to the allocator.
		// REQUIRE : attributes().isImplicit() || size
		// _TAG02 Operations

	virtual void preallocate(size_t size,size_t count) = 0;
		// Pre-allocate `count' memory chunks of `size' bytes.
		// _TAG02 Operations

};

#endif
