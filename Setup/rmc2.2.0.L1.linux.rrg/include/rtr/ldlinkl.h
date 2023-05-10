//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/94
//

#ifndef _ldlinkl_h
#define _ldlinkl_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/linkl.h"

template <class T, class L> class RTRLiteDLinkListIterator;
template <class T, class L> class RTRLiteDLinkListFastIterator;

// Synopsis:
//
// Description:
//
//	The following defines a link list class without an iterator
//
// See Also:
//

template <class T, class L>
class RTRLiteDLinkList: protected RTRDList
{
public:
// Constructor
	RTRLiteDLinkList();
		// _TAG Constructor

// Destructor
	~RTRLiteDLinkList();
		// _TAG Destructor

// Implicit cast

	// _TAG01 Implicit cast
	inline L *toL(L *object) const
	{
		return(object);
	};

// State

	// _TAG02 State
	inline RTRBOOL isEmpty() const
	{
		return(RTRDList::isEmpty());
	};

// Size

	// _TAG03 Size
	inline int count() const
	{
		return(RTRDList::count());
	};

// Put

	// _TAG04 Put
	inline void putFirst(T *object)
	{
		RTRDList::putFirst(toL(object));
	};

	// _TAG04 Put
	inline void putLast(T *object)
	{
		RTRDList::putLast(toL(object));
	};

	// _TAG04 Put
	inline void putPrevious(T *object, T *newObject)
	{
		RTRDList::putPrevious(toL(object), toL(newObject));
	};

	// _TAG04 Put
	inline void putNext(T *object, T *newObject)
	{
		RTRDList::putNext(toL(object), toL(newObject));
	};

// Remove

	// _TAG05 Remove
	inline void remove(T *object)
	{
		RTRDList::remove(toL(object));
	};

	// _TAG05 Remove
	inline T *removeFirst()
	{
		return((T*)((L*)RTRDList::removeFirst()));
	};

	// _TAG05 Remove
	inline T *removeLast()
	{
		return((T*)((L*)RTRDList::removeLast()));
	};

	void removeAndDestroy(T *object);
		// _TAG05 Remove

	// _TAG05 Remove
	inline void removeAll()
	{
		RTRDList::removeAll();
	};

	void removeAllAndDestroy();
        // _TAG05 Remove

	void reset();
        // _TAG05 Reset

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
	inline void append(RTRLiteDLinkList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
		int cntList = list->count();
#endif
		RTRDList::append(list);
		RTPOSTCONDITION((cnt + cntList) == count());
	};

	// _TAG07 Concatenate
	inline void prepend(RTRLiteDLinkList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
		int cntList = list->count();
#endif
		RTRDList::prepend(list);
		RTPOSTCONDITION((cnt + cntList) == count());
	};

// Split

	// _TAG08 Split
	inline void split(T *object, RTRLiteDLinkList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
#endif
		RTRDList::split((toL(object)), list);
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

private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRLiteDLinkList(const RTRLiteDLinkList<T, L>&);
	RTRLiteDLinkList<T, L>& operator=(const RTRLiteDLinkList<T, L>&);
		//
// Friends
	friend class RTRLiteDLinkListIterator<T,L>;
	friend class RTRLiteDLinkListFastIterator<T,L>;
};

// Synopsis:
//
// Description:
//
//	The RTRLiteDLinkListIterator is a bit slower version of an iterator
//	than RTRLiteDLinkListFastIterator but allows application to remove
//	current item from the list during traversal
//
// See Also:
//

template <class T, class L>
class RTRLiteDLinkListIterator
{
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRLiteDLinkListIterator(const RTRLiteDLinkListIterator<T, L>&);
	RTRLiteDLinkListIterator<T, L>& operator=(const RTRLiteDLinkListIterator<T, L>&);
		//
protected:
	RTRLiteDLinkList<T,L> *_list;
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
public:

// Constructor

	// _TAG Constructor
	inline RTRLiteDLinkListIterator(RTRLiteDLinkList<T,L> &list)
			: _list(&list)
	{
		_object = 0;
		_currentObjectRemoved = RTRFALSE;
		RTPOSTCONDITION(off());
	};

	// _TAG Constructor
	inline RTRLiteDLinkListIterator()
			: _list(0)
	{
		_object = 0;
		_currentObjectRemoved = RTRFALSE;
		// RTPOSTCONDITION(off());
	};

// Destructor

	// _TAG Destructor
	inline ~RTRLiteDLinkListIterator()
	{
	};

// Initialize

	// _TAG01 Initialize
	inline void initialize(RTRLiteDLinkList<T,L> &list)
	{
		_list = &list;
		_object = 0;
		_currentObjectRemoved = RTRFALSE;
		RTPOSTCONDITION(off());
	};

// Positioning

	// _TAG02 Positioning
	inline void start()
	{
		RTPRECONDITION(_list != 0);
		_object = _list->first();
		_currentObjectRemoved = RTRFALSE;
	};

	// _TAG02 Positioning
	inline void finish()
	{
		RTPRECONDITION(_list != 0);
		_object = _list->last();
		_currentObjectRemoved = RTRFALSE;
	};

	// _TAG02 Positioning
	inline void forth()
	{
		RTPRECONDITION(_list != 0);
		RTPRECONDITION(!off());
		if (!_currentObjectRemoved)
		{
			_object = _list->next(_object);
		}
		else
		{
			_object = _nextObject;
			_currentObjectRemoved = RTRFALSE;
		}
	};

	// _TAG02 Positioning
	inline void back()
	{
		RTPRECONDITION(_list != 0);
		RTPRECONDITION(!off());
		if (!_currentObjectRemoved)
		{
			_object = _list->previous(_object);
		}
		else
		{
			_object = _prevObject;
			_currentObjectRemoved = RTRFALSE;
		}
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
		RTPRECONDITION(!_currentObjectRemoved);
		return(_object);
	};

// Remove

	// _TAG05 Remove
	inline void remove()
	{
		RTPRECONDITION(_list != 0);
		RTPRECONDITION(!off());
		RTPRECONDITION(!_currentObjectRemoved);

		_nextObject = _list->next(_object);
		_prevObject = _list->previous(_object);
		_list->remove(_object);
		_currentObjectRemoved = RTRTRUE;
	};
};

// Synopsis:
//
// Description:
//
//	The RTRLiteDLinkListFastIterator is the faster version of an iterator
//	but it doesn't allow application to remove current item from
//	the list during traversal
//
// See Also:
//

template <class T, class L>
class RTRLiteDLinkListFastIterator
{
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRLiteDLinkListFastIterator(const RTRLiteDLinkListFastIterator<T, L>&);
	RTRLiteDLinkListFastIterator<T, L>& operator=(const RTRLiteDLinkListFastIterator<T, L>&);
		//
protected:
	RTRLiteDLinkList<T,L> *_list;
		//
	T *_object;
		// _object points the current object
public:

// Constructor

	// _TAG Constructor
	inline RTRLiteDLinkListFastIterator(RTRLiteDLinkList<T,L> &list)
			: _list(&list)
	{
		_object = 0;
		RTPOSTCONDITION(off());
	};

	// _TAG Constructor
	inline RTRLiteDLinkListFastIterator()
			: _list(0)
	{
		_object = 0;
		// RTPOSTCONDITION(off());
	};

// Destructor

	// _TAG Destructor
	inline ~RTRLiteDLinkListFastIterator()
	{
	};

// Initialize

	// _TAG01 Initialize
	inline void initialize(RTRLiteDLinkList<T,L> &list)
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
//		RTRLiteDLinkedList = RTRLiteDLinkList + RTRLiteDLinkListIterator
//
// See Also:
//

template <class T, class L>
class RTRLiteDLinkedList: 
	public RTRLiteDLinkList<T,L>, public RTRLiteDLinkListIterator<T,L>
{
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRLiteDLinkedList(const RTRLiteDLinkedList<T, L>&);
	RTRLiteDLinkedList<T, L>& operator=(const RTRLiteDLinkedList<T, L>&);
		//
public:

	// _TAG Contructor
	inline RTRLiteDLinkedList()
	{
		RTRLiteDLinkListIterator<T,L>::initialize(*this);
	};

	// _TAG01 Other
	inline void remove(T *object)
	{
		 RTRLiteDLinkList<T,L>::remove(object);
	};

	// _TAG01 Other
	inline void remove()
	{
		 RTRLiteDLinkListIterator<T,L>::remove();
	};
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("ldlinkl.C")
#else
#include "rtr/ldlinkl.C"
#endif
#endif

#endif
