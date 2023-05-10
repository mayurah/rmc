//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/94
//

#ifndef _lslinkl_h
#define _lslinkl_h

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
class RTRLiteSLinkList: protected RTRSList
{
public:
// Constructor
	RTRLiteSLinkList();
		// _TAG Constructor

// Destructor
	~RTRLiteSLinkList();
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
		return(RTRSList::isEmpty());
	};

// Size

	// _TAG03 Size
	inline int count() const
	{
		return(RTRSList::count());
	};

// Put

	// _TAG04 Put
	inline void putFirst(T *object)
	{
		RTRSList::putFirst(toL(object));
	};

	// _TAG04 Put
	inline void putLast(T *object)
	{
		RTRSList::putLast(toL(object));
	};

	// _TAG04 Put
	inline void putPrevious(T *object, T *newObject)
	{
		RTRSList::putPrevious(toL(object), toL(newObject));
	};

	// _TAG04 Put
	inline void putNext(T *object, T *newObject)
	{
		RTRSList::putNext(toL(object), toL(newObject));
	};

// Remove

	// _TAG05 Remove
	inline void removeNext(T *object, T *nextObject)
	{
		RTRSList::removeNext(toL(object), toL(nextObject));
	};

	// _TAG05 Remove
	inline void remove(T *object)
	{
		RTRSList::remove(toL(object));
	};

	// _TAG05 Remove
	inline T *removeFirst()
	{
		return((T*)((L*)RTRSList::removeFirst()));
	};

	// _TAG05 Remove
	inline T *removeLast()
	{
		return((T*)((L*)RTRSList::removeLast()));
	};

	void removeAndDestroy(T *object);
		// _TAG05 Remove

	// _TAG05 Remove
	inline void removeAll()
	{
		RTRSList::removeAll();
	};

	void removeAllAndDestroy();
        // _TAG05 Remove

// Get

	// _TAG06 Get
	inline T *first() const
	{
		return((T*)((L*)RTRSList::first()));
	};

	// _TAG06 Get
	inline T *last() const
	{
		return((T*)((L*)RTRSList::last()));
	};

	// _TAG06 Get
	inline T *next(T *object) const
	{
		return((T*)((L*)RTRSList::next((toL(object)))));
	};

	// _TAG06 Get
	inline T *previous(T *object) const
	{
		return((T*)((L*)RTRSList::previous((toL(object)))));
	};

	// _TAG06 Get
	inline T *head() const
	{
		return((T*)((L*)RTRSList::head()));
	};

// Concatenate

	// _TAG07 Concatenate
	inline void append(RTRLiteSLinkList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
		int cntList = list->count();
#endif
		RTRSList::append(list);
		RTPOSTCONDITION((cnt + cntList) == count());
	};

	// _TAG07 Concatenate
	inline void prepend(RTRLiteSLinkList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
		int cntList = list->count();
#endif
		RTRSList::prepend(list);
		RTPOSTCONDITION((cnt + cntList) == count());
	};

// Membership

	// _TAG09 Membership
	inline bool has(T *object) const
	{
		return(RTRSList::has(toL(object)));
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
	RTRLiteSLinkList(const RTRLiteSLinkList<T, L>&);
	RTRLiteSLinkList<T, L>& operator=(const RTRLiteSLinkList<T, L>&);
		//
// Friends
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("lslinkl.C")
#else
#include "rtr/lslinkl.C"
#endif
#endif

#endif
