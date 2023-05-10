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

#ifndef _rtdlist_h
#define _rtdlist_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/dlinkl.h"

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRLinkElement :
	public RTRDLink0
{
public:
// Constructor
	inline RTRLinkElement(void *it) : _item(it) {};
		// _TAG Constructor

	inline void *item() {return(_item);};
		// _TAG01 Other

protected:
	void *_item;
};

// Synopsis:
//
// Description:
//
// See Also:
//

template<class T> class RTRDblLinkList
{
public:
// Constructors
	inline RTRDblLinkList() : _link(0) {};
		// _TAG Constructor

// Destructor
	inline ~RTRDblLinkList() {};
		// _TAG Destructor

// State
	inline RTRBOOL empty() const
		// Is this list empty
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
	inline void putFirst(T* newT)
		// Add the item newT at the front of the list.
		// REQUIRE: newT != 0
		// _TAG06 Insertion
	{
		RTRLinkElement *newLink = new RTRLinkElement(newT);
		_list.putFirst(newLink);
	};

	inline void putPrevious(T* newT)
		// Add item to the previous position in list.
		// REQUIRE: newT != 0
		// REQUIRE: !off()
		// _TAG06 Insertion
	{
		RTPRECONDITION(!off());
		RTRLinkElement *newLink = new RTRLinkElement(newT);
		_list.putPrevious(_link, newLink);
	};

	inline void putNext(T* newT)
		// Add item to the next position in list.
		// REQUIRE: newT != 0
		// REQUIRE: !off()
		// _TAG06 Insertion
	{
		RTPRECONDITION(!off());
		RTRLinkElement *newLink = new RTRLinkElement(newT);
		_list.putNext(_link, newLink);
	};

	inline void putLast(T* newT)
		// Add the item newT at the end of the list.
		// REQUIRE: newT != 0
		// REQUIRE: !off()
		// _TAG06 Insertion
	{
		RTRLinkElement *newLink = new RTRLinkElement(newT);
		_list.putLast(newLink);
	};

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
		// REQUIRE: t != 0
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
	RTRDblLinkList(const RTRDblLinkList<T>&);
	RTRDblLinkList<T>& operator=(const RTRDblLinkList<T>&);

};


#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("rtdlist.C")
#else
#include "rtr/rtdlist.C"
#endif
#endif

#endif  // _rtdlist_h
