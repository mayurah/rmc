//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/03
//

#ifndef _slinkl_h
#define _slinkl_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/slink.h"

// Synopsis:
//
// Description:
//
// 	The following defines a link list class without an iterator
//
// See Also:
//

template <class T, class L>
class RTRSLinkList: protected RTRSList
{
public:
// Constructor
	RTRSLinkList();
		// _TAG Constructor

// Destructor
	~RTRSLinkList();
		// _TAG Destructor

// Implicit cast

	// _TAG01 Implicit cast
	inline L *toL(L *object) const
	{
		return(object);
	};

// Put

	// _TAG02 Put
	inline void putFirst(T *object)
	{
		RTRSList::putFirst(toL(object));
		++_count;
	};

	// _TAG02 Put
	inline void putLast(T *object)
	{
		RTRSList::putLast(toL(object));
		++_count;
	};

	// _TAG02 Put
	inline void putPrevious(T *object, T *newObject)
	{
		RTRSList::putPrevious(toL(object), toL(newObject));
		++_count;
	};

	// _TAG02 Put
	inline void putNext(T *object, T *newObject)
	{
		RTRSList::putNext(toL(object), toL(newObject));
		++_count;
	};

// State

	// _TAG03 State
	inline bool isEmpty() const
	{
		return(RTRSList::isEmpty());
	};

// Size

	// _TAG04 Size
	inline int count() const
	{
		return(_count);
	};

// Remove

	// _TAG05 Remove
	inline void removeNext(T *object, T *nextObject)
	{
		RTRSList::removeNext(toL(object), toL(nextObject));
		--_count;
		RTPOSTCONDITION(count() >= 0);
	};

	// _TAG05 Remove
	inline void remove(T *object)
	{
		RTRSList::remove(toL(object));
		--_count;
		RTPOSTCONDITION(count() >= 0);
	};

	// _TAG05 Remove
	inline T *removeFirst()
	{
		RTPOSTCONDITION(count() > 0);
		return((T*)((L*)RTRSList::removeFirst(_count)));
	};

	// _TAG05 Remove
	inline T *removeLast()
	{
		RTPOSTCONDITION(count() > 0);
		return((T*)((L*)RTRSList::removeLast(_count)));
	};

	void removeAndDestroy(T *object);
		// _TAG05 Remove

	// _TAG05 Remove
	inline void removeAll()
	{
		RTRSList::removeAll();
		_count = 0;
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

// Concatenate

	// _TAG07 Concatenate
	inline void append(RTRSLinkList<T,L> *list)
	{
		_count += list->count();
		RTRSList::append(list);
		list->_count = 0;
	};

	// _TAG07 Concatenate
	inline void prepend(RTRSLinkList<T,L> *list)
	{
		_count += list->count();
		RTRSList::prepend(list);
		list->_count = 0;
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
		return(find(compareKeyToObject, key) != 0);
	};

protected:
	int _count;

private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRSLinkList(const RTRSLinkList<T, L>&);
	RTRSLinkList<T, L>& operator=(const RTRSLinkList<T, L>&);
		//
//Friends
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("slinkl.C")
#else
#include "rtr/slinkl.C"
#endif
#endif

#endif
