//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Aug. 08 1995"
// Version: 1.0

#ifndef _rtr_gc_h
#define _rtr_gc_h

#include "rtr/rtrdefs.h"
#include "rtr/gcref.h"

// Synopsis:
// #include "rtr/gc.h"
//
// RTRObjRef<RTRMyClass> ptr = new RTRMyClass();
// RTRObjRef<RTRMyClass> optr = ptr;
// RTRObjRef<RTRMyClass>* foo = new RTRObjRef<RTRMyClass>(ptr)
// delete foo;
//
// Description:
// The base class for reference counted objects. Used in conjunction with
// a smart pointer template class.
//
// See Also:
// RTRObjRef<T>
//

class RTRGCObj
{
public:
// Constructor
	RTRGCObj();
		// _TAG Constructor

// Destructor
	virtual ~RTRGCObj();
		// _TAG Destructor

// Operations
	inline void incrementCount();
		// _TAG01 Operations

	inline void decrementCount();
        // _TAG01 Operations

protected:
// Operations
	virtual void dispose();
		// calls delete

// Data
	int _referenceCount;
};

inline 
void RTRGCObj::incrementCount()
{
	_referenceCount++;
}

inline 
void RTRGCObj::decrementCount()
{
	_referenceCount--;
	if ( _referenceCount == 0 )
		dispose();
}

#endif
