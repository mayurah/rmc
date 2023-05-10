//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/94
//

#ifndef _dlinkl_h
#define _dlinkl_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/linkl.h"

template <class T, class L> class RTRDLinkListIterator;
template <class T, class L> class RTRDLinkListFastIterator;

// Synopsis:
//
// Description:
//
// 	The following defines a link list class without an iterator
//
// See Also:
//

template <class T, class L>
class RTRDLinkList: protected RTRDList
{
public:
// Constructor
	RTRDLinkList();
		// _TAG Constructor

// Destructor
	~RTRDLinkList();
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
		RTRDList::putFirst(toL(object));
		++_count;
	};

	// _TAG02 Put
	inline void putLast(T *object)
	{
		RTRDList::putLast(toL(object));
		++_count;
	};

	// _TAG02 Put
	inline void putPrevious(T *object, T *newObject)
	{
		RTRDList::putPrevious(toL(object), toL(newObject));
		++_count;
	};

	// _TAG02 Put
	inline void putNext(T *object, T *newObject)
	{
		RTRDList::putNext(toL(object), toL(newObject));
		++_count;
	};

// State

	// _TAG03 State
	inline RTRBOOL isEmpty() const
	{
		return(RTRDList::isEmpty());
	};

// Size

	// _TAG04 Size
	inline int count() const
	{
		return(_count);
	};

// Remove

	// _TAG05 Remove
	inline void remove(T *object)
	{
		RTRDList::remove(toL(object));
		--_count;
		RTPOSTCONDITION(count() >= 0);
	};

	// _TAG05 Remove
	inline T *removeFirst()
	{
		RTPOSTCONDITION(count() > 0);
		return((T*)((L*)RTRDList::removeFirst(_count)));
	};

	// _TAG05 Remove
	inline T *removeLast()
	{
		RTPOSTCONDITION(count() > 0);
		return((T*)((L*)RTRDList::removeLast(_count)));
	};

	void removeAndDestroy(T *object);
		// _TAG05 Remove

	// _TAG05 Remove
	inline void removeAll()
	{
		RTRDList::removeAll();
		_count = 0;
	};

	void removeAllAndDestroy();
        // _TAG05 Remove

// Get

	// _TAG06 Get
	inline T *first() const
	{
		return((T*)((L*)RTRDList::first()));
	};

    // _TAG06 Get
	inline T *last() const
	{
		return((T*)((L*)RTRDList::last()));
	};

	// _TAG06 Get
	inline T *next(T *object) const
	{
		return((T*)((L*)RTRDList::next((toL(object)))));
	};

	// _TAG06 Get
	inline T *previous(T *object) const
	{
		return((T*)((L*)RTRDList::previous((toL(object)))));
	};

// Concatenate

	// _TAG07 Concatenate
	inline void append(RTRDLinkList<T,L> *list)
	{
		_count += list->count();
		RTRDList::append(list);
		list->_count = 0;
	};

	// _TAG07 Concatenate
	inline void prepend(RTRDLinkList<T,L> *list)
	{
		_count += list->count();
		RTRDList::prepend(list);
		list->_count = 0;
	};

// Split

	// _TAG08 Split
	inline void split(T *object, RTRDLinkList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
#endif
		RTRDList::split((toL(object)), list);
		_count = RTRDList::count();
		list->_count = list->RTRDList::count();
		RTPOSTCONDITION(cnt == (count() + list->count()));
	};

// Membership

	// _TAG09 Membership
	inline RTRBOOL has(T *object) const
	{
		return(RTRDList::has(toL(object)));
	};

	T *find(RTRBOOL (*compareKeyToObject)(void*, T*), void *key) const;
		// _TAG09 Membership

	// _TAG09 Membership
	inline 
	RTRBOOL has(RTRBOOL (*compareKeyToObject)(void*, T*), void *key) const
	{
		return(find(compareKeyToObject, key) ? RTRTRUE : RTRFALSE);
	};

protected:
	int _count;

private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRDLinkList(const RTRDLinkList<T, L>&);
	RTRDLinkList<T, L>& operator=(const RTRDLinkList<T, L>&);
		//
//Friends
	friend class RTRDLinkListIterator<T,L>;
	friend class RTRDLinkListFastIterator<T,L>;
};

// Synopsis:
//
// Description:
//
//	The RTRDLinkListIterator is a bit slower version of an iterator
//	than RTRDLinkListFastIterator but allows application to remove
//	current item from the list during traversal
//
// See Also:
//

template <class T, class L>
class RTRDLinkListIterator
{
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRDLinkListIterator(const RTRDLinkListIterator<T, L>&);
	RTRDLinkListIterator<T, L>& operator=(const RTRDLinkListIterator<T, L>&);
		//
public:
// Constructor
	RTRDLinkListIterator(RTRDLinkList<T, L>& list);
		// _TAG Constructor

	RTRDLinkListIterator();
        // _TAG Constructor

// Destructor
	~RTRDLinkListIterator();
		// _TAG Destructor

// State

	// _TAG01 State
	inline RTRBOOL off() const
	{
		RTPRECONDITION(_list != 0);
		return(_object ? RTRFALSE : RTRTRUE);
	};

	// _TAG01 State
	inline RTRBOOL offLeft() const
	{
		RTPRECONDITION(_list != 0);
		return(off());
	};

	// _TAG01 State
	inline RTRBOOL offRight() const
	{
		RTPRECONDITION(_list != 0);
		return(off());
	};

// Initialize

	// _TAG02 Initialize
	inline void initialize(RTRDLinkList<T,L> &list)
	{
		_list = &list;
		_object = 0;
		_currentObjectRemoved = RTRFALSE;
		RTPOSTCONDITION(off());
	};

// Positioning

	// _TAG03 Positioining
	inline void start() 
	{
		RTPRECONDITION(_list != 0);
		_object = _list->first();
		_currentObjectRemoved = RTRFALSE;
	};

	// _TAG03 Positioining
	inline void finish() 
	{
		RTPRECONDITION(_list != 0);
		_object = _list->last();
		_currentObjectRemoved = RTRFALSE;
	};

	void forth();
		// _TAG03 Positioning

	void back();
		// _TAG03 Positioning

// Get

	// _TAG04 Get
	inline T *item() const
	{
		RTPRECONDITION(_list != 0);
		RTPRECONDITION(!off());
		RTPRECONDITION(!_currentObjectRemoved);
		return(_object);
	};

// Remove
	void remove();
		// _TAG05 Remove

protected:
	RTRDLinkList<T,L> *_list;
		//
	T *_object;
		// _object points to the current object
	T *_nextObject;
		// _nextObject is the next object to the current object 
		// _nextObject allows an application to traverse the list
		// and remove the current object
	T *_prevObject;
		// see comment for _nextObject
	short _currentObjectRemoved;
		// flag to indicate whether the current _object was
		// removed via remove() function
};

// Synopsis:
//
// Description:
//
//	The RTRDLinkListFastIterator is the faster version of an iterator
//	but it doesn't allow application to remove current item from the list
//	during traversal
//
// See Also:
//

template <class T, class L>
class RTRDLinkListFastIterator
{
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRDLinkListFastIterator(const RTRDLinkListFastIterator<T, L>&);
	RTRDLinkListFastIterator<T, L>& operator=(const RTRDLinkListFastIterator<T, L>&);
		//
protected:
	RTRDLinkList<T,L> *_list;
		//
	T *_object;
		// _object points the current object
public:

// Constructor

	// _TAG Constructor
	inline RTRDLinkListFastIterator(RTRDLinkList<T,L> &list)
			: _list(&list)
	{
		_object = 0;
		RTPOSTCONDITION(off());
	};

	// _TAG Constructor
	inline RTRDLinkListFastIterator()
			: _list(0)
	{
		_object = 0;
		// RTPOSTCONDITION(off());
	};

// Destructor

	// _TAG Destructor
	inline ~RTRDLinkListFastIterator()
	{
	};

// Initialize

	// _TAG01 Initialize
	inline void initialize(RTRDLinkList<T,L> &list)
	{
		_list = &list;
		_object = 0;
		RTPOSTCONDITION(off());
	};

// Positioning

	// _TAG02 Positioning
	inline void start()
	{
		RTPRECONDITION(_list != 0);
		_object = _list->first();
	};

	// _TAG02 Positioning
	inline void finish()
	{
		RTPRECONDITION(_list != 0);
		_object = _list->last();
	};

	// _TAG02 Positioning
	inline void forth()
	{
		RTPRECONDITION(_list != 0);
		RTPRECONDITION(!off());
		_object = _list->next(_object);
	};

	// _TAG02 Positioning
	inline void back()
	{
		RTPRECONDITION(_list != 0);
		RTPRECONDITION(!off());
		_object = _list->previous(_object);
	};

// State

	// _TAG03 State
	inline RTRBOOL off() const
	{
		RTPRECONDITION(_list != 0);
		return(_object ? RTRFALSE : RTRTRUE);
	};

	// _TAG03 State
	inline RTRBOOL offLeft() const
	{
		RTPRECONDITION(_list != 0);
		return(off());
	};

	// _TAG03 State
	inline RTRBOOL offRight() const
	{
		RTPRECONDITION(_list != 0);
		return(off());
	};

// Get

	// _TAG04 Get
	inline T *item() const
	{
		RTPRECONDITION(_list != 0);
		RTPRECONDITION(!off());
		return(_object);
	};
};

// Synopsis:
//
// Description:
//
//	For user convenience, the following aggregate class is defined:
//		RTRDLinkedList = RTRDLinkList + RTRDLinkListIterator
//
// See Also:
//

template <class T, class L>
class RTRDLinkedList : 
	public RTRDLinkListIterator<T,L>,
	public RTRDLinkList<T,L>
{
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRDLinkedList(const RTRDLinkedList<T, L>&);
	RTRDLinkedList<T, L>& operator=(const RTRDLinkedList<T, L>&);
		//
public:

	// _TAG Constructor
	inline RTRDLinkedList()
	{
		RTRDLinkListIterator<T,L>::initialize(*this);
	};

	// _TAG Destructor
	inline ~RTRDLinkedList()
	{
	};

	// _TAG01 Other
	inline void remove(T *object)
	{
		 RTRDLinkList<T,L>::remove(object);
	};

	// _TAG01 Other
	inline void remove()
	{
		 RTRDLinkListIterator<T,L>::remove();
	};
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("dlinkl.C")
#else
#include "rtr/dlinkl.C"
#endif
#endif

#endif
