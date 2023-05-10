//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: Andrew MacGaffey
// Created: Jan. 4, 1994
// Version: 2.0

#ifndef _rtllist_h 
#define _rtllist_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/linkl.h"
#include "rtr/dlinkl.h"

template <class T> class RTRLinkedList;
template <class T> class RTRLinkedListCursor;

// Synopsis:
//
// Description:
//
// See Also:
//

template<class T> class RTRGenLink : public RTRDLink0
{
public:
// Constructor
	RTRGenLink(T *t) : _item(t) {};
		// _TAG Constructor

	// _TAG01 Other
	T *item() { return _item; };

// Friend 
friend class RTRLinkedList<T>;
friend class RTRLinkedListCursor<T>;

protected:
	T *_item;
};

// Synopsis:
//
// Description:
//
// See Also:
//

template<class T> class RTRLinkedList
{
public:
// Constructors
	RTRLinkedList();
		// _TAG Constructor

	RTRLinkedList(const RTRLinkedList<T>&);
		// _TAG Constructor

// Destructor
	~RTRLinkedList();
		// _TAG Destructor

// Attributes
	T* first() const;
		// The first item in the list.
		// REQUIRE : !empty()
		// _TAG01 Attributes

	T* last() const;
		// The last item in the list.
		// REQUIRE : !empty()
        // _TAG01 Attributes

	int count() const;
		// The number of items in the list.
        // _TAG01 Attributes

    int position() const;
		// The position of the cursor.
        // _TAG01 Attributes

// State
	RTRBOOL empty() const;
		// Is this list empty
		// ENSURE: result implies count() == 0
		// _TAG02 State

	RTRBOOL off() const;
		// Is the cursor out-of-bounds?
		// ENSURE: result implies ( offleft() || offright() )
        // _TAG02 State

	RTRBOOL offRight() const;
		// Is the cursor off the end of the list?
		// ENSURE: result implies position() > count()
        // _TAG02 State

	RTRBOOL offLeft() const;
		// Is the cursor off the beginning of the list?
		// ENSURE: result implies position() < 1
        // _TAG02 State

// Query
	RTRBOOL has(T *t) const;
		// Does this list contain t (by operator==)?
		// REQUIRE : t != 0
		// ENSURE: result == RTRTRUE implies !empty()
		// _TAG03 Query

// Access
	T*  item() const;
		// The item at position
		// REQUIRE: !off()
		// _TAG04 Access

	T*  iTh(int i) const;
		// The item in the list at position i.
		// REQUIRE: i > 0
		// REQUIRE: i <= count()
        // _TAG04 Access

// Cursor operations
	RTRLinkedList<T>& forth();
		// Move the cursor toward the end of the list
		// REQUIRE: !offRight()
		// ENSURE: position() = old position() + 1
		// _TAG05 Cursor operations

	RTRLinkedList<T>& back();
		// Move the cursor toward the beginning of the list
		// REQUIRE: !offLeft()
		// ENSURE: position() = old position() - 1
        // _TAG05 Cursor operations

	RTRLinkedList<T>& finish();
		// Move the cursor to the end of the list.
		// ENSURE: position() = count()
        // _TAG05 Cursor operations

	RTRLinkedList<T>& start();
		// Move the cursor to the beginning of the list.
		// ENSURE: position() == 1
        // _TAG05 Cursor operations

	RTRLinkedList<T>& goITh(int i);
		// Move the cursor to the ith position in the list (or offLeft() or
		// offRight() ).
		// REQUIRE: i >= 0
		// REQUIRE: i <= count() + 1
		// ENSURE: position() == i
        // _TAG05 Cursor operations

// Insertion
	RTRLinkedList<T>& addFront(const T* newT);
		// Add the item newT at the front of the list.
		// REQUIRE : newT != 0
		// ENSURE: first() == newT
		// _TAG06 Insertion

	RTRLinkedList<T>& addLeft(const T* newT);
		// Add the item newT at position - 1 in the list.
		// REQUIRE : newT != 0
		// REQUIRE !offLeft() unless empty()
        // _TAG06 Insertion

	RTRLinkedList<T>& addRight(const T* newT);
		// Add the item newT at position + 1 in the list.
		// REQUIRE : newT != 0
		// REQUIRE !offRight() unless empty()
        // _TAG06 Insertion

	RTRLinkedList<T>& extend(const T* newT);
		// Add the item newT at the end of the list.
		// REQUIRE : newT != 0
		// ENSURE: last() == newT
        // _TAG06 Insertion

// Deletion
	RTRLinkedList<T>& remove();
		// Remove the item found at the current cursor position from the list.
		// REQUIRE: !off()
		// _TAG07 Deletion

	RTRLinkedList<T>& deleteContents();
		// Empty the list after deleting the contents.
		// ENSURE: count() == 0;
        // _TAG07 Deletion

	RTRLinkedList<T>& wipeOut();
		// Empty the list (no delete).
		// ENSURE: count() == 0
        // _TAG07 Deletion

// Query
	RTRLinkedList<T>& search(const T *t);
		// Leave the cursor pointing at item t found in the list or offRight()
		// ENSURE: !off() implies item() == t
		// _TAG08 Query

// Compatibility -- obsolete

	// _TAG09 Compatibility -- obsolete
	inline int index() const
	{
		return position();
	}

protected:
	RTRDLinkList<RTRGenLink<T>, RTRDLink0 > _list;
	int _position;
	RTRGenLink<T> *_link;

// Friends
friend class RTRLinkedListCursor<T>;

private:
	RTRLinkedList<T>& operator=(const RTRLinkedList<T>&);
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("rtllist.C")
#else
#include "rtr/rtllist.C"
#endif
#endif

#endif  // _rtllist_h
