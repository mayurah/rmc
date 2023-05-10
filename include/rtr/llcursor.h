//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: Andrew MacGaffey
// Created: Jan. 4, 1994
// Version: 2.0

#ifndef _llcursor_h 
#define _llcursor_h

#include "rtr/rtllist.h"

// Synopsis:
//
// Description:
//
// See Also:
//

template<class T> class RTRLinkedListCursor
{
public:
// Constructors
	RTRLinkedListCursor();
		// _TAG Constructor

	RTRLinkedListCursor(const RTRLinkedListCursor<T>&);
		// _TAG Constructor

// Destructor
	~RTRLinkedListCursor();
		// _TAG Destructor

// State
	RTRBOOL off() const;
		// _TAG02 State

// Access
	T* current() const;
		// _TAG03 Access

// Comparison
	RTRBOOL operator==(const RTRLinkedListCursor<T>& rhs) const;
		// _TAG04 Comparison
	RTRBOOL operator!=(const RTRLinkedListCursor<T>& rhs) const;
		// _TAG04 Comparison

// Transformation
	T& operator*() const;
		// _TAG05 Transformation
	T *operator->() const;
		// _TAG05 Transformation
	operator T*() const;
		// _TAG05 Transformation

// Assignment
	const RTRLinkedListCursor<T>& operator=(const RTRLinkedList<T>&);
		// _TAG07 Assignment

	const RTRLinkedListCursor<T>& operator=(const RTRLinkedListCursor<T>&);
		// _TAG07 Assignment

	const RTRLinkedListCursor<T>& operator++();
		// _TAG07 Assignment

	const RTRLinkedListCursor<T>& operator++(int);
		// _TAG07 Assignment

	const RTRLinkedListCursor<T>& operator--(int);
		// _TAG07 Assignment

// Operations
	void start();
		// _TAG07 Assignment

	void forth();
		// _TAG07 Assignment

	void back();
		// _TAG07 Assignment

	void finish();
		// _TAG07 Assignment

protected:
	const RTRDLinkList<RTRGenLink<T>, RTRDLink0 >* _list;
	RTRGenLink<T> *_current;
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("llcursor.C")
#else
#include "rtr/llcursor.C"
#endif
#endif

#endif 
