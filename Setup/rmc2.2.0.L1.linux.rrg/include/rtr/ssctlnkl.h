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
//  created:       October 31, 1994
//  version:       1.0
//

#ifndef __RTRSigSafeCountDLinkList
#define __RTRSigSafeCountDLinkList

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
//  This version also counts the number of elements that
//  exist in the list. You can either let the list create
//  the counter or pass a reference to a counter in that
//  the list will use.
//
// See Also:
//

template <class T, class L>
class RTRSigSafeCountDLinkList: protected RTRDList
{
private:
		// Define the following but do not implement.
		// Will cause a link time error if called.
	RTRSigSafeCountDLinkList(const RTRSigSafeCountDLinkList<T, L>&);
	RTRSigSafeCountDLinkList<T, L>& operator=(const RTRSigSafeCountDLinkList<T, L>&);
		//


protected:

	int		*_count;
		// Reference to a counter of the current
		// elements in the list.
	RTRBOOL	_my_memory;


public:

// Constructor

	// _TAG Constructor
	inline RTRSigSafeCountDLinkList() : _count(0)
	{
		_count = new int;
		_my_memory = 1;
		(*_count) = 0;
		RTPOSTCONDITION( _count != 0 );
		RTPOSTCONDITION( count() == 0 );
	};

	// _TAG Constructor
	inline RTRSigSafeCountDLinkList( int * counter ) : _count(counter)
	{
		RTPRECONDITION( counter != 0 );
		(*_count) = 0;
		_my_memory = 0;
		RTPOSTCONDITION( _count != 0 );
		RTPOSTCONDITION( count() == 0 );
	};


// Destructor

	// _TAG Destructor
	inline ~RTRSigSafeCountDLinkList()
	{
		if (_my_memory)
			delete _count;
	};


// Unsafe Put

	// _TAG01 Unsfafe Put
	inline void unsafePutFirst(T *object)
	{
		RTRDList::putFirst((L*)object);
		(*_count)++;
	};

	// _TAG01 Unsfafe Put
	inline void unsafePutLast(T *object)
	{
		RTRDList::putLast((L*)object);
		(*_count)++;
	};

	// _TAG01 Unsfafe Put
	inline void unsafePutPrevious(T *object, T *newObject)
	{
		RTRDList::putPrevious((L*)object, (L*)newObject);
		(*_count)++;
	};

	// _TAG01 Unsfafe Put
	inline void unsafePutNext(T *object, T *newObject)
	{
		RTRDList::putNext((L*)object, (L*)newObject);
		(*_count)++;
	};


// Safe Put

	// _TAG02 Safe Put
	inline void putFirst(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::putFirst((L*)object);
		(*_count)++;
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};

	// _TAG02 Safe Put
	inline void putLast(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::putLast((L*)object);
		(*_count)++;
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};

	// _TAG02 Safe Put
	inline void putPrevious(T *object, T *newObject)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::putPrevious((L*)object, (L*)newObject);
		(*_count)++;
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};

	// _TAG02 Safe Put
	inline void putNext(T *object, T *newObject)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::putNext((L*)object, (L*)newObject);
		(*_count)++;
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
	};


// Unsafe Remove

	// _TAG03 Unsafe Remove
	inline void unsafeRemove(T *object)
	{
		RTRDList::remove((L*)object);
		(*_count)--;
	};

	// _TAG03 Unsafe Remove
	inline void unsafeRemoveAndDestroy(T *object)
	{
		RTRDList::remove((L*)object);
		(*_count)--;
		delete object;
	};

	// _TAG03 Unsafe Remove
	inline void unsafeRemoveAll()
	{
		RTRDList::removeAll();
		(*_count) = 0;
	};

	// _TAG03 Unsafe Remove
	inline void unsafeRemoveAllAndDestroy()
	{
		T *object;
		for (object = first(); object != 0; object = first() )
			unsafeRemoveAndDestroy( object );
	};


// Safe Remove

	// _TAG04 Safe Remove
	inline void remove(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRDList::remove((L*)object);
		(*_count)--;
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
		T *ret=(T*)((L*)RTRDList::first());
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
		T *ret=(T*)((L*)RTRDList::next(((L*)object)));
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
		return((T*)((L*)RTRDList::first()));
	};

	// _TAG06 Unsafe Get
	inline T *unsafeLast()
	{
		return((T*)((L*)RTRDList::last()));
	};

	// _TAG06 Unsafe Get
	inline T *unsafeNext(T *object)
	{
		return((T*)((L*)RTRDList::next(((L*)object))));
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
		T *ret=(T*)((L*)RTRDList::first());
		if (ret) unsafeRemove(ret);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return( ret );
	};

	// _TAG07 Retrieval and removal
	inline T *removeLast()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		T *ret=(T*)((L*)RTRDList::last());
		if (ret) unsafeRemove(ret);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return( ret );
	};


// Unsafe Retrieval and removal.

	// _TAG08 Unsafe Retrieval and removal
	inline T *unsafeRemoveFirst()
	{
		T *ret=(T*)((L*)RTRDList::first());
		if (ret) unsafeRemove(ret);
		return( ret );
	};

	// _TAG08 Unsafe Retrieval and removal
	inline T *unsafeRemoveLast()
	{
		T *ret=(T*)((L*)RTRDList::last());
		if (ret) unsafeRemove(ret);
		return( ret );
	};


// Membership

	// _TAG09 Membership
	inline RTRBOOL has(T *object)
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRBOOL ret = RTRDList::has((L*)object);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return(ret);
	};

// State

	// _TAG10 State
	inline RTRBOOL isEmpty()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		RTRBOOL ret = RTRDList::isEmpty();
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return(ret);
	};
	
	// _TAG10 State
	inline RTRBOOL unsafeIsEmpty()
	{
		return( RTRDList::isEmpty() );
	};


// Size

	// _TAG11 Size
	inline int count()
	{
		RTRSignalNotifierInit::signalNotifier->blockAllSignals();
		int ret = (*_count);
		RTRSignalNotifierInit::signalNotifier->unblockAllSignals();
		return(ret);
	};
};


#endif
