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

#ifndef __rtr_dfltmem_h
#define __rtr_dfltmem_h

#include "rtr/memry.h"
#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif
class RTRDfltMemAlloc;


// Synopsis:
// #include"rtr/dfltmem.h"
//
// Description:
// See Also:
//	RTRDfltMemAlloc
//
// Inherits:
//	RTRMemory
//

class RTRDfltMemoryMgr :
	public RTRMemory
{
public:

// Constructor
	RTRDfltMemoryMgr();
		// _TAG Constructor

// Destructor
	virtual ~RTRDfltMemoryMgr();
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

	RTRDfltMemAlloc		*defVarMem;

};


#endif
