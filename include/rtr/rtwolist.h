//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: Tom Hansen
// Created: Wed Nov 17 09:42:52 1993
// Version: 1.0

#ifndef _rtwolist_h 
#define _rtwolist_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/rtllist.h"

// Synopsis:
//
// Description:
//
// See Also:
//

template<class G> 
class RTRSortedTwoWayList
{
public:
// Constructors
	RTRSortedTwoWayList();
		// _TAG Constructor

// Destructor
	~RTRSortedTwoWayList();
		// _TAG Destructor

// Attributes
	int count() const;
		// _TAG01 Attributes

	int index() const;
        // _TAG01 Attributes

// State
	RTRBOOL empty() const;
		// _TAG02 State

	RTRBOOL off() const;
        // _TAG02 State

// Query
	RTRBOOL has(G* item) const;
		// _TAG03 Query

	RTRSortedTwoWayList<G>& search(G* item);
        // _TAG03 Query

// Access
	G* item() const;
		// _TAG04 Access

	G* first() const;
        // _TAG04 Access

	G* last() const;
        // _TAG04 Access

// Random access
	G*  operator[](int i) const;
		// _TAG05 Random access

	G*  iTh(int i) const;
        // _TAG05 Random access

// Insertion
	RTRSortedTwoWayList<G>& merge(RTRSortedTwoWayList<G>& aList);
		// _TAG06 Insertion

	RTRSortedTwoWayList<G>& extend(G* item);
		// Start from first, put item in front of those "less/equal (<=) items".
        // _TAG06 Insertion

	RTRSortedTwoWayList<G>& extendFromBehind(G* item);
		// Start from end, put item to the back of those "no less (>=) items".
        // _TAG06 Insertion

// Cursor operations
	RTRSortedTwoWayList<G>& start();
		// _TAG07 Cursor operations

	RTRSortedTwoWayList<G>& finish();
        // _TAG07 Cursor operations

	RTRSortedTwoWayList<G>& forth();
        // _TAG07 Cursor operations

	RTRSortedTwoWayList<G>& back();
        // _TAG07 Cursor operations

	RTRSortedTwoWayList<G>& remove();
        // _TAG07 Cursor operations

	RTRSortedTwoWayList<G>& goITh(int i);
        // _TAG07 Cursor operations

protected:
// Data
	RTRLinkedList<G> *listRep;
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("rtwolist.C")
#else
#include "rtr/rtwolist.C"
#endif
#endif

#endif /* RTR_SORTED_TWO_WAY_LIST */
