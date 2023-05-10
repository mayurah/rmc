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

#ifndef __rtr_memry_h
#define __rtr_memry_h

// Turn on memory debugging for reuter debugging
//#ifdef RTDEBUG
//#ifndef RTR_MEM_DEBUG
//#define RTR_MEM_DEBUG
//#endif
//#endif

#include "rtr/rtrdefs.h"
#include "rtr/memalc.h"
#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif


// Synopsis:
// #include"rtr/memry.h"
//
// Description:
//  RTRMemory is the abstract base class for memory allocation which
//  provides facilities whereby users can allocate and deallocate memory
//  from different allocators based on the attributes of the memory
//  needed.
//
//  The purpose of this class is to provide access to the different
//  allocators that can be used in the system.
//
//  There is a need for only one RTRMemory for system memory. To do
//  this a user includes "rtr/rtrmem.h" giving access to a static
//  class of type RTRMemManager. This class implements a reference
//  couting scheme which will automatically construct/destruct a
//  memory manager as necessary. This is similar to the mechanism used
//  for making cin and cout when accessing iostreams. Typically, the
//  source file containing main() includes "rtr/rtrmem.h", meaning
//  that the memory manager is always in existence (until program
//  termination).
//
//  In the case the user wants to override the global new() and delete(),
//  causing all classes to use the memory manager, he would link in
//  the libgblnew library. This will automatically instantiate the
//  memory allocator when its needed.
//
//  If multiple memory allocators are needed, the user must pass
//  around the reference to the memory allocators needed. An example
//  of another memory allocator is one that uses shared memory.
//
//	Memory allocators are retrieved based upon attibutes. The current
//	attributes an allocator may have are:
//
//  \bullet
//  o RTRMemory::rtrMemFixed --
//      Fixed sized memory chunks (class,structures,etc), they
//      normally do not change sizes.
//  o RTRMemory::rtrMemVariable --
//      Variable sized memory chunks (strings,buffers,(char*),etc),
//      they normally change sizes.
//  o RTRMemory::rtrMemImplicit --
//      The memory chunk keeps track of its own size.
//  o RTRMemory::rtrMemExplicit() --
//      The user of the allocator keep track of the memory size and
//      returns that size on the deallocate call.
//  \endbullet
//
//  RTRMemory::rtrMemFixed implies !RTRMemory::rtrMemVariable
//  RTRMemory::rtrMemVariable implies !RTRMemory::rtrMemFixed
//	RTRMemory::rtrMemImplicit implies !RTRMemory::rtrMemExplicit
//	RTRMemory::rtrMemExplicit implies !RTRMemory::rtrMemImplicit
//
// See Also:
//  RTRManageClass, RTRMemManager, RTRMemoryAllocator
// 
// Inherits:
//  RTRMallocMemory
//

class RTRMemory :
	public RTRMallocMemory
{
public:

// Destructor
	virtual ~RTRMemory();
		// _TAG Destructor

// Attributes
	enum {	rtrMemFixed = 0x01,
			rtrMemVariable = 0x02,
			rtrMemImplicit = 0x04,
			rtrMemExplicit = 0x08 };

// Operations
	virtual RTRMemoryAllocator & allocator(rtrMemAttributes attributes) = 0;
		// _TAG01 Operations
		// `attributes' contains a bitmask of the enumation attributes above.

// Dump out any statistics to ostream
#ifndef _RDEV_NO_STL_
	virtual void dump( std::ostream& ) = 0;
		// _TAG02 Dump out any statistics to ostream
#else
	virtual void dump( FILE* ) = 0;
		// _TAG02 Dump out any statistics to ostream
#endif
};


#endif
