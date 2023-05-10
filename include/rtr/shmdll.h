//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel (A. MacGaffey)
// Created: 8/11/94
//

#ifndef _shmdll_h
#define _shmdll_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/shmlinkl.h"

template <class T, class L> class RTRShmDLinkListIterator;
	// RTRShmDLinkListIterator

// Synopsis:
// #include"rtr/shmdll.h"
//
// Description:
// 	The following defines a link list class without an iterator.
//
// See Also:
//	RTRShmDLink, RTRShmDLink0, RTRShmDLink1, RTRShmDLink2
//
// Inherits:
//	RTRShmDList
//

template <class T, class L>
class RTRShmDLinkList: protected RTRShmDList
{
public:
// Constructor
	RTRShmDLinkList();
		// _TAG Constructor

	RTRShmDLinkList(const char *base);
        // _TAG Constructor

// Destructor
	~RTRShmDLinkList();
		// _TAG Destructor

// Implicit cast
	inline L *toL(L *object) const;
		// _TAG01 Implicit cast

// Put
	void putFirst(T *object, const char *base);
		// _TAG02 Put

	void putLast(T *object, const char *base);
        // _TAG02 Put

	void putPrevious(T *object, T *newObject, const char *base);
        // _TAG02 Put

	void putNext(T *object, T *newObject, const char *base);
        // _TAG02 Put

// Remove
	void remove(T *object, const char *base);
		// _TAG03 Remove

	void removeAndDestroy(T *object, const char *base);
        // _TAG03 Remove

	void removeAll(const char *base);
        // _TAG03 Remove

	void removeAllAndDestroy(const char *base);
        // _TAG03 Remove

// Get
	T *first(const char *base);
		// _TAG04 Get

	T *last(const char *base);
        // _TAG04 Get

	T *next(T *object, const char *base) const;
        // _TAG04 Get

	T *previous(T *object, const char *base) const;
        // _TAG04 Get

// Concatenate
	void append(RTRShmDLinkList<T,L> *list, const char *base);
		// _TAG05 Concatenate

	void prepend(RTRShmDLinkList<T,L> *list, const char *base);
        // _TAG05 Concatenate

// Split
	void split(T *object, RTRShmDLinkList<T,L> *list, const char *base);
		// _TAG06 Split

// Membership
	RTRBOOL has(T *object, const char *base) const;
		// _TAG07 Membership

	T *
	find(RTRBOOL (*compareKeyToObject)(void*, T*), void *key, const char *base) const;
        // _TAG07 Membership

	RTRBOOL has(RTRBOOL (*compareKeyToObject)(void*, T*), void *, const char *) const;
        // _TAG07 Membership

// State
	inline RTRBOOL isEmpty() const;
		// _TAG08 State

// Size
	int count(const char *base) const;
		// _TAG09 Size

// Initialization
	void reset(const char *base);
		// _TAG10 Initialization

protected:
	int _count;

private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRShmDLinkList(const RTRShmDLinkList<T, L>&);
	RTRShmDLinkList<T, L>& operator=(const RTRShmDLinkList<T, L>&);

// Friends
friend class RTRShmDLinkListIterator<T,L>;
};

template<class T, class L> inline
L *RTRShmDLinkList<T, L>::toL(L *object) const
{
	return(object);
}

template<class T, class L> inline 
RTRBOOL RTRShmDLinkList<T, L>::isEmpty() const
{
	return(RTRShmDList::isEmpty());
}

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef ibmrs
#pragma implementation("shmdll.C")
#else
#include "rtr/shmdll.C"
#endif
#endif


#endif
