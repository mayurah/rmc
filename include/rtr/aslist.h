//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       September 23, 1996
//  version:       1.0

#ifndef _aslist_h
#define _aslist_h

#include "rtr/platform.h"
#include "rtr/linkl.h"

// Synopsis:
//
// Description:
//	Sorted doubly linked list in ascending order.
//	This version of the list is intrusive. The link elements
//	must be part of the object stored in the list.
//
// See Also:
//

template<class T,class L>
class RTRAscSortList : protected RTRDList
{
public:
// Constructors
	inline RTRAscSortList() {};
		// _TAG Constructor

// Destructor
	inline ~RTRAscSortList() {};
		// _TAG Destructor

// Implicit cast
	inline L *toL(L *object) const
		// _TAG01 Implicit cast
	{
		return(object);
	};

// State
	inline RTRBOOL empty() const
		// Is this list empty
		// ENSURE: result implies count() == 0
		// _TAG02 State
	{
		return(RTRDList::isEmpty());
	};

// Attributes
	inline T* first() const
		// The first item in the list.
		// _TAG03 Attributes
	{
		return((T*)((L*)RTRDList::first()));
	};

	inline T* last() const
		// The last item in the list.
		// _TAG03 Attributes
	{
		return((T*)((L*)RTRDList::last()));
	};

	inline T *next(T *object) const
		// The next element in last after object.
		// REQUIRE : object != 0
		// REQUIRE : !empty()
		// _TAG03 Attributes
	{
		return((T*)((L*)RTRDList::next((toL(object)))));
	};

	inline T *previous(T *object) const
	{
		// The previous element in last before object.
		// REQUIRE : object != 0
		// REQUIRE : !empty()
		// _TAG03 Attributes
		return((T*)((L*)RTRDList::previous((toL(object)))));
	};

	inline int count() const
		// The number of items in the list.
		// _TAG03 Attributes
	{
		return(RTRDList::count());
	};

// Query
	inline RTRBOOL has(T *object) const
		// Does this list contain t (by operator==)?
		// REQUIRE : t != 0
		// ENSURE: result == RTRTRUE implies !empty()
		// _TAG04 Query
	{
		return(RTRDList::has(toL(object)));
	};

// Insertion
	void extend(T *object);
		// Add element to the list in correct position.
		// Start from beginning of list.
		// _TAG05 Insertion

	void extendFromBehind(T *object);
		// Add element to the list in correct position.
		// Start from end of list and go backwards.
		// _TAG05 Insertion


// Deletion
	inline void remove(T *object)
		// Remove element from list.
		// _TAG06 Deletion
	{
		RTRDList::remove(toL(object));
	};

	inline void removeFirst()
		// Remove the first element in the list.
		// REQUIRE: !empty()
		// _TAG06 Deletion
	{
		RTPRECONDITION ( !empty() );
		T *object = first();
		RTRDList::remove(toL(object));
	};

	inline void removeLast()
		// Remove the last element in the list.
		// REQUIRE: !empty()
		// _TAG06 Deletion
	{
		RTPRECONDITION ( !empty() );
		T *object = last();
		RTRDList::remove(toL(object));
	};

	void deleteContents();
		// Empty the list after deleting the contents.
		// _TAG06 Deletion

	void wipeOut();
		// Empty the list (no delete).
		// _TAG06 Deletion


protected:

private:
	RTRAscSortList(const RTRAscSortList<T,L>&);
	RTRAscSortList<T,L>& operator=(const RTRAscSortList<T,L>&);

};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("aslist.C")
#else
#include "rtr/aslist.C"
#endif
#endif

#endif  // _aslist_h
