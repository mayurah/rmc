//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_NOTIFIER_ARRAY 
#define RTR_NOTIFIER_ARRAY


#include "rtr/platform.h"
#include "rtr/rtrdefs.h"

template<class T> class RTRNotifierArray;

// Synopsis:
//
// Description:
//
// 	Specialized array for notifier implementations
//
// 	Sparsely populated (no compaction occurs)
//
// 	Indexed from 1 to capacity()
//
// See Also:
//

template<class T> class RTRNotifierArray
{

private:

// Object Assignment ** DON'T DEFINE THIS!
	RTRNotifierArray<T>& 
		operator=(const RTRNotifierArray<T>& rhs);

// Copy Constructor ** DON'T DEFINE THIS!
	RTRNotifierArray(RTRNotifierArray<T>& other);

protected:

	int max;
	void **stuff;

public:

// Constructor
	RTRNotifierArray(int size);
		// _TAG Constructor

// Destructor
	~RTRNotifierArray();
		// _TAG Destructor

	int count();
		// Current number of entries.
		// _TAG01 Other

	void insert(T *t);
		// ENSURE : has(t)
		//			count() == old count() + 1
		// _TAG01 Other

	RTRBOOL has(T *t);
		// Is t an entry?
		// _TAG01 Other

	void remove(T *t);
		// ENSURE : !has(t)
		// _TAG01 Other

	void removeItemAt(int i);
		// Remove the entry at index i.
		// REQUIRE : i >= 0 && i < capacity()
		// _TAG01 Other

	T *item(int i);
		// The entry at index i.
		// REQUIRE : i >= 0 && i < capacity()
		// _TAG01 Other

	int indexOf(T *t);
		// The index of entry t.
		// ENSURE: (result == -1) == !has(t)
		// ENSURE: result < capacity()
		// _TAG01 Other

	int capacity();
		// The current capacity.
		// _TAG01 Other

	void absorb(RTRNotifierArray<T> *other);
		// Absorb the entries from other
		// _TAG01 Other

};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("notifarr.C")
#else
#include "rtr/notifarr.C"
#endif
#endif


#endif /* RTR_NOTIFIER_ARRAY */


