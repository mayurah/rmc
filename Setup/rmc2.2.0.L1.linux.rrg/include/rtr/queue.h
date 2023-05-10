//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T.L. Zhang
// Created: "Jan. 22 1995"
// Version: 1.0

#ifndef _queue_h
#define _queue_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/rtllist.h"

// Synopsis:
//
// Description:
//
//  A simple implementation of queue. Will add more functionality and optimize
//  performance later on.
// 
// See Also:
//

template<class T> class RTRQueue
{ 
public:
// Constructor
	RTRQueue();
		// _TAG Constructor

// Destructor
	~RTRQueue();
		// _TAG Destructor

// Attributes
	T* head() const;
		// _TAG01 Attributes

	T* dequeue();
        // _TAG01 Attributes

	RTRQueue<T>&  enqueue(T*);
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
#pragma implementation("queue.C")
#else
#include "rtr/queue.C"
#endif
#endif

#endif
