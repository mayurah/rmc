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
//  created:       September 13, 1996
//  version:       1.0

#ifndef _rdslist_h
#define _rdslist_h

#include "rtr/platform.h"
#include "rtr/rtdlist.h"

// Synopsis:
//
// Description:
//	Sorted doubly linked list in descending order.
//
// See Also:
//

template<class T>
class RTRDescSortedList
{
public:
// Constructors
	inline RTRDescSortedList() : _link(0) {};
		// _TAG Constructor

// Destructor
	inline ~RTRDescSortedList() {};
		// _TAG Destructor

// State
	inline RTRBOOL empty() const
		// Is this list empty
		// ENSURE: result implies count() == 0
		// _TAG01 State
	{
		return(_list.isEmpty());
	};

	inline RTRBOOL off() const
		// Is the cursor out-of-bounds?
		// _TAG01 State
	{
		return(_link == 0);
	};

// Attributes
	inline T* first() const
		// The first item in the list.
		// REQUIRE : !empty()
		// _TAG02 Attributes
	{
		RTPRECONDITION ( !empty() );
		return((T*)_list.first()->item());
	};

	inline T* last() const
		// The last item in the list.
		// REQUIRE : !empty()
		// _TAG02 Attributes
	{
		RTPRECONDITION ( !empty() );
		return((T*)_list.last()->item());
	};

	inline int count() const
		// The number of items in the list.
		// _TAG02 Attributes
	{
		return(_list.count());
	};

// Query
	RTRBOOL has(T *t) const;
		// Does this list contain t (by operator==)?
		// REQUIRE : t != 0
		// ENSURE: result == RTRTRUE implies !empty()
		// _TAG03 Query

// Access
	inline T* item() const
		// The item at position
		// REQUIRE: !off()
		// _TAG04 Access
	{
		RTPRECONDITION(!off());
		return ((T*)_link->item());
	};

// Cursor operations
	inline void forth()
		// Move the cursor toward the end of the list
		// REQUIRE: !off()
		// _TAG05 Cursor operations
	{
		RTPRECONDITION(!off());
		_link = _list.next(_link);
	};

	inline void back()
		// Move the cursor toward the beginning of the list
		// REQUIRE: !off()
		// _TAG05 Cursor operations
	{
		RTPRECONDITION(!off());
		_link = _list.previous(_link);
	};

	inline void finish()
		// Move the cursor to the end of the list.
		// _TAG05 Cursor operations
	{
		_link = _list.last();
	};

	inline void start()
		// Move the cursor to the beginning of the list.
		// _TAG05 Cursor operations
	{
		_link = _list.first();
	};


// Insertion
	void extend(T *t);
		// Add element to the list in correct position.
		// Start from beginning of list.
		// _TAG06 Insertion

	void extendFromBehind(T *t);
		// Add element to the list in correct position.
		// Start from end of list and go backwards.
		// _TAG06 Insertion


// Deletion
	inline void remove()
		// Remove the item found at the current cursor position from the list.
		// REQUIRE: !off()
		// _TAG07 Deletion
	{
		RTPRECONDITION ( !off() );
		RTRLinkElement *oldLink = _link;
		_link = _list.next(oldLink);
		_list.remove(oldLink);
		delete oldLink;
	};

	inline void removeFirst()
		// Remove the first element in the list.
		// REQUIRE: !empty()
		// _TAG07 Deletion
	{
		RTPRECONDITION ( !empty() );
		RTRLinkElement *oldLink = _list.first();
		if (oldLink == _link)
			_link = _list.next(oldLink);
		_list.remove(oldLink);
		delete oldLink;
	};

	inline void removeLast()
		// Remove the last element in the list.
		// REQUIRE: !empty()
		// _TAG07 Deletion
	{
		RTPRECONDITION ( !empty() );
		RTRLinkElement *oldLink = _list.last();
		if (oldLink == _link)
			_link = _list.next(oldLink);
		_list.remove(oldLink);
		delete oldLink;
	};

	void remove(T *t);
		// Remove element from list.
		// _TAG07 Deletion

	void deleteContents();
		// Empty the list after deleting the contents.
		// _TAG07 Deletion

	void wipeOut();
		// Empty the list (no delete).
		// _TAG07 Deletion

// Query
	void search(T *t);
		// Leave the cursor pointing at item t found in the list or off()
		// _TAG08 Query


protected:
	RTRDLinkList<RTRLinkElement,RTRDLink0> _list;
	RTRLinkElement *_link;

private:
	RTRDescSortedList(const RTRDescSortedList<T>&);
	RTRDescSortedList<T>& operator=(const RTRDescSortedList<T>&);

};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("rdslist.C")
#else
#include "rtr/rdslist.C"
#endif
#endif

#endif  // _rdslist_h
