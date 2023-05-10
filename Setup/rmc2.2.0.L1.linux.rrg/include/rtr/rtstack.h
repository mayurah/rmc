//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T.L. Zhang
// Created: "Dec. 27 1995"
// Version: 1.0

#ifndef _rtstack_h
#define _rtstack_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/rtllist.h"

// Synopsis:
//
// Description:
//
//  A simple implementation of stack. Will add more functionality and optimize
//  performance later on.
//
// See Also:
//

template<class T> class RTRStack
{ 
public:
// Constructor
	RTRStack();
		// _TAG Constructor

// Destructor
	~RTRStack();
		// _TAG Destructor

// Attributes
	T* top() const;
		// _TAG01 Attributes

	T* pop();
        // _TAG01 Attributes

	RTRStack<T>&  push(T*);
        // _TAG01 Attributes

	RTRBOOL empty();
        // _TAG01 Attributes

	void init();
        // _TAG01 Attributes

protected:
	RTRLinkedList<T> _store;

}; 

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("rtstack.C")
#else
#include "rtr/rtstack.C"
#endif
#endif

#endif
