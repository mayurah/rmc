//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/94
//

#ifndef _lsllist_h
#define _lsllist_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/slink.h"


// Synopsis:
//
// Description:
//
//	The following defines a link list class without an iterator
//
// See Also:
//

template <class T, class L>
class RTRLiteSList: protected RTRHSList
{
public:
// Constructor
	RTRLiteSList();
		// _TAG Constructor

// Destructor
	~RTRLiteSList();
		// _TAG Destructor

// Implicit cast

	// _TAG01 Implicit cast
	inline L *toL(L *object) const
	{
		return(object);
	};

// State

	// _TAG02 State
	inline bool isEmpty() const
	{
		return(RTRHSList::isEmpty());
	};

// Size

	// _TAG03 Size
	inline int count() const
	{
		return(RTRHSList::count());
	};

// Put

	// _TAG04 Put
	inline void putFirst(T *object)
	{
		RTRHSList::putFirst(toL(object));
	};

	// _TAG04 Put
	inline void putLast(T *object)
	{
		RTRHSList::putLast(toL(object));
	};

	// _TAG04 Put
	inline void putPrevious(T *object, T *newObject)
	{
		RTRHSList::putPrevious(toL(object), toL(newObject));
	};

	// _TAG04 Put
	inline void putNext(T *object, T *newObject)
	{
		RTRHSList::putNext(toL(object), toL(newObject));
	};

// Remove

	// _TAG05 Remove
	inline void removeNext(T *object, T *nextObject)
	{
		RTRHSList::removeNext(toL(object), toL(nextObject));
	};

	// _TAG05 Remove
	inline void remove(T *object)
	{
		RTRHSList::remove(toL(object));
	};

	// _TAG05 Remove
	inline T *removeFirst()
	{
		return((T*)((L*)RTRHSList::removeFirst()));
	};

	// _TAG05 Remove
	inline T *removeLast()
	{
		return((T*)((L*)RTRHSList::removeLast()));
	};

	void removeAndDestroy(T *object);
		// _TAG05 Remove

	// _TAG05 Remove
	inline void removeAll()
	{
		RTRHSList::removeAll();
	};

	void removeAllAndDestroy();
        // _TAG05 Remove

// Get

	// _TAG06 Get
	inline T *first() const
	{
		return((T*)((L*)RTRHSList::first()));
	};

	// _TAG06 Get
	inline T *last() const
	{
		return((T*)((L*)RTRHSList::last()));
	};

	// _TAG06 Get
	inline T *next(T *object) const
	{
		return((T*)((L*)RTRHSList::next((toL(object)))));
	};

	// _TAG06 Get
	inline T *previous(T *object) const
	{
		return((T*)((L*)RTRHSList::previous((toL(object)))));
	};

	// _TAG06 Get
	inline T *head() const
	{
		return((T*)((L*)RTRHSList::head()));
	};

// Concatenate

	// _TAG07 Concatenate
	inline void append(RTRLiteSList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
		int cntList = list->count();
#endif
		RTRHSList::append(list);
		RTPOSTCONDITION((cnt + cntList) == count());
	};

	// _TAG07 Concatenate
	inline void prepend(RTRLiteSList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
		int cntList = list->count();
#endif
		RTRHSList::prepend(list);
		RTPOSTCONDITION((cnt + cntList) == count());
	};

// Membership

	// _TAG09 Membership
	inline bool has(T *object) const
	{
		return(RTRHSList::has(toL(object)));
	};

	T *find(bool (*compareKeyToObject)(void*, T*), void *key) const;
		// _TAG09 Membership

	// _TAG09 Membership
	inline 
	bool has(bool (*compareKeyToObject)(void*, T*), void *key) const
	{
		return(find(compareKeyToObject, key) ? true : false);
	};

private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRLiteSList(const RTRLiteSList<T, L>&);
	RTRLiteSList<T, L>& operator=(const RTRLiteSList<T, L>&);
		//
// Friends
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("lsllist.C")
#else
#include "rtr/lsllist.C"
#endif
#endif

#endif
