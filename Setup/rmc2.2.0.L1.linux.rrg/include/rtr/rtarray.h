//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Dec. 02 1994"
// Version: 1.0

#ifndef _rtarray_h
#define _rtarray_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/gnptrvec.h"

// Synopsis:
//
// Description:
//
// 	Array template
//
// 	Min/Max indices specified on constructor.
//
// See Also:
//

template<class T>
class RTRArray
{
public:
// Constructor
	RTRArray(int minindex, int maxindex);
		// _TAG Constructor

	RTRArray(const RTRArray<T>&);
		// _TAG Constructor

// Destructor
	~RTRArray();
		// _TAG Destructor

// Attributes
	int lower() const;
		// _TAG01 Attributes

	int upper() const;
        // _TAG01 Attributes

	int capacity() const;
        // _TAG01 Attributes

// Access
	T* operator[](int i) const;
		// _TAG02 Access

	T* iTh(int i) const;
        // _TAG02 Access

// Assignment
	RTRArray<T>& operator=(const RTRArray<T>&);
		// _TAG03 Assignment

// Modify
	T*& operator[](int i);
		// _TAG04 Modify

	void force(T* v, int i);
        // _TAG04 Modify

	void put(T* v, int i);
        // _TAG04 Modify

	RTRArray<T>& deleteContents();
        // _TAG04 Modify

// Query
	RTRBOOL has(T* v);
		// _TAG05 Query

	int occurrences(T* v) const;
        // _TAG05 Query

	RTRBOOL validIndex(int i) const;
        // _TAG05 Query

// Equality
	RTRBOOL operator==(RTRArray<T>& anArray);
		// _TAG06 Equality

// Compatibility - Obsolete
	T* index(int i) const;
		// _TAG07 Compatibility - Obsolete

	T*& index(int i);
        // _TAG07 Compatibility - Obsolete

	RTRArray<T>& set(int i, T* v);
        // _TAG07 Compatibility - Obsolete

	int count() const;
        // _TAG07 Compatibility - Obsolete

protected:
	RTRGenericPointerVector *_store;
	int _minIndex;
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("rtarray.C")
#else
#include "rtr/rtarray.C"
#endif
#endif

#endif // _rtarray_h
