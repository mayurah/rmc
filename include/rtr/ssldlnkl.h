//
//|---------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       October 13, 1994
//  version:       1.0
//

#ifndef __RTRSigSafeDLinkList
#define __RTRSigSafeDLinkList

#include "rtr/rtrdefs.h"
#include "rtr/linkl.h"
#include "rtr/signotif.h"


/*
 * The following defines a link list class without an iterator
 */

// Synopsis:
//
// Description:
//
//  This represents a doubly linked list that has member
//  functions that can be used in order to be signal safe.
//  That is, the default action is block all signals before
//  performing the list operation.
//  A set of members functions that do not block signals
//  before an operation will also be specified (unsafe).
//
// See Also:
//

template <class T, class L>
class RTRSigSafeDLinkList: protected RTRDList
{
private:
		// Define the following but do not implement.
		// Will cause a link time error if called.
	RTRSigSafeDLinkList(const RTRSigSafeDLinkList<T, L>&);
	RTRSigSafeDLinkList<T, L>& operator=(const RTRSigSafeDLinkList<T, L>&);
		//
protected:

public:

// Constructor

	// _TAG Constructor
	inline RTRSigSafeDLinkList()
	{
	};

// Destructor

	// _TAG Destructor
	inline ~RTRSigSafeDLinkList()
	{
	};



// Unsafe Put

	// _TAG01 Unsafe Put
	inline void unsafePutFirst(T *object)
	{
		RTRDList::putFirst((L*)object);
	};

	// _TAG01 Unsafe Put
	inline void unsafePutLast(T *object)
	{
		RTRDList::putLast((L*)object);
	};

	// _TAG01 Unsafe Put
	inline void unsafePutPrevious(T *object, T *newObject)
	{
		RTRDList::putPrevious((L*)object, (L*)newObject);
	};

	// _TAG01 Unsafe Put
	inline void unsafePutNext(T *object, T *newObject)
	{
		RTRDList::putNext((L*)object, (L*)newObject);
	};


// Safe Put

	// _TAG02 Safe Put
	inline void putFirst(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::putFirst((L*)object);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};

	// _TAG02 Safe Put
	inline void putLast(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::putLast((L*)object);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};

	// _TAG02 Safe Put
	inline void putPrevious(T *object, T *newObject)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::putPrevious((L*)object, (L*)newObject);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};

	// _TAG02 Safe Put
	inline void putNext(T *object, T *newObject)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::putNext((L*)object, (L*)newObject);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};


// Unsafe Remove

	// _TAG03 Unsafe Remove
	inline void unsafeRemove(T *object)
	{
		RTRDList::remove((L*)object);
	};

	// _TAG03 Unsafe Remove
	inline void unsafeRemoveAndDestroy(T *object)
	{
		remove(object);
		delete object;
	};

	// _TAG03 Unsafe Remove
	inline void unsafeRemoveAll()
	{
		RTRDList::removeAll();
	};

	// _TAG03 Unsafe Remove
	inline void unsafeRemoveAllAndDestroy()
	{
		T *nextObject;

		for (T *object = first(); object != 0; )
		{
			nextObject = next(object);
			remove(object);
			delete object;
			object = nextObject;
		};
	};


// Safe Remove

	// _TAG04 Safe Remove
	inline void remove(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::remove((L*)object);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};

	// _TAG04 Safe Remove
	inline void removeAndDestroy(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		unsafeRemoveAndDestroy(object);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};

	// _TAG04 Safe Remove
	inline void removeAll()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		unsafeRemoveAll();
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};

	// _TAG04 Safe Remove
	inline void removeAllAndDestroy()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		unsafeRemoveAllAndDestroy();
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};




// Safe Get

	// _TAG05 Safe Get
	inline T *first()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		T *ret=(T*)((L*)RTRDList::first_no_assertions());
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return( ret );
	};

	// _TAG05 Safe Get
	inline T *last()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		T *ret=(T*)((L*)RTRDList::last());
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return( ret );
	};

	// _TAG05 Safe Get
	inline T *next(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		T *ret=(T*)((L*)RTRDList::next_no_assertions(((L*)object)));
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return( ret );
	};

	// _TAG05 Safe Get
	inline T *previous(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		T *ret=(T*)((L*)RTRDList::previous(((L*)object)));
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return( ret );
	};


// Unsafe Get

	// _TAG06 Unsafe Get
	inline T *unsafeFirst()
	{
		return((T*)((L*)RTRDList::first_no_assertions()));
	};

	// _TAG06 Unsafe Get
	inline T *unsafeLast()
	{
		return((T*)((L*)RTRDList::last()));
	};

	// _TAG06 Unsafe Get
	inline T *unsafeNext(T *object)
	{
		return((T*)((L*)RTRDList::next_no_assertions(((L*)object))));
	};

	// _TAG06 Unsafe Get
	inline T *unsafePrevious(T *object)
	{
		return((T*)((L*)RTRDList::previous(((L*)object))));
	};



// Retrieval and removal.

	// _TAG07 Retrieval and removal
	inline T *removeFirst()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		T *ret=(T*)((L*)RTRDList::first_no_assertions());
		if (ret) RTRDList::remove((L*)ret);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return( ret );
	};

	// _TAG07 Retrieval and removal
	inline T *removeLast()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		T *ret=(T*)((L*)RTRDList::last());
		if (ret) RTRDList::remove((L*)ret);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return( ret );
	};


// Unsafe Retrieval and removal.

	// _TAG08 Unsafe Retrieval and removal
	inline T *unsafeRemoveFirst()
	{
		T *ret=(T*)((L*)RTRDList::first_no_assertions());
		if (ret) RTRDList::remove((L*)ret);
		return( ret );
	};

	// _TAG08 Unsafe Retrieval and removal
	inline T *unsafeRemoveLast()
	{
		T *ret=(T*)((L*)RTRDList::last());
		if (ret) RTRDList::remove((L*)ret);
		return( ret );
	};


// Concatenate

	// _TAG09 Concatenate
	inline void append(RTRSigSafeDLinkList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
		int cntList = list->count();
#endif
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::append(list);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		RTPOSTCONDITION((cnt + cntList) == count());
	};

	// _TAG09 Concatenate
	inline void prepend(RTRSigSafeDLinkList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
		int cntList = list->count();
#endif
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::prepend(list);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		RTPOSTCONDITION((cnt + cntList) == count());
	};

// Split

	// _TAG10 Split
	inline void split(T *object, RTRSigSafeDLinkList<T,L> *list)
	{
#ifdef RTDEBUG
		int cnt = count();
#endif
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::split(((L*)object), list);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		RTPOSTCONDITION(cnt == (count() + list->count()));
	};

// Membership

	// _TAG11 Membership
	inline RTRBOOL has(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRBOOL ret = RTRDList::has((L*)object);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return(ret);
	};

	// _TAG11 Membership
	inline RTRBOOL unsafeHas(T *object)
	{
		RTRBOOL ret = RTRDList::has((L*)object);
		return(ret);
	};

// State

	// _TAG12 State
	inline RTRBOOL isEmpty()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRBOOL ret = RTRDList::isEmpty();
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return(ret);
	};

	// _TAG12 State
	inline RTRBOOL unsafeIsEmpty()
	{
		return( RTRDList::isEmpty() );
	};


// Size

	// _TAG13 Size
	inline int count()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		int ret = RTRDList::count();
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return(ret);
	};

	// _TAG13 Size
	inline int unsafeCount()
	{
		int ret = RTRDList::count();
		return(ret);
	};
};


#endif
