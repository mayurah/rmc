//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel (A. MacGaffey)
// Created: 8/11/94
//

#ifndef _shmlinkl_h
#define _shmlinkl_h

#include "rtr/os.h"
#include "rtr/rtrdefs.h"
#include "rtr/intcustmem.h" /* needed for IntPtr definitions */

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

// Synopsis:
// #include"rtr/shmlinkl.h"
//
// Description:
// See Also:
//	RTRShmDLink0, RTRShmDLink1, RTRShmDLink2, RTRShmDList
//

class RTRShmDLink
{
public:
// Constructor
	RTRShmDLink();
		// _TAG Constructor

// Destructor
	~RTRShmDLink();
		// _TAG Destructor

// State
	inline RTRBOOL isActive() const;
		// _TAG01 State

// Attributes
	inline int offset(const char *base) const;
		// _TAG02 Attributes

	inline int offsetOfNext() const;
        // _TAG02 Attributes

	inline int offsetOfPrev() const;
        // _TAG02 Attributes

// Support
	inline void setNotActive();
		// _TAG03 Support

	void remove(const char *base);
		// remove this link from list
        // _TAG03 Support

protected:
// Put
	void putPrevious(RTRShmDLink *link, const char *base);
		// put new link before this link

	void putNext(RTRShmDLink *link, const char *base);
		// put new link after this link

// Attributes
	inline RTRShmDLink *next(const char *base) const;

	inline RTRShmDLink *previous(const char *base) const;

// Set
	inline void setNext(RTRShmDLink *link, const char *base);

	inline void setPrev(RTRShmDLink *link, const char *base);

protected:
	int _offsetOfNext;
	int _offsetOfPrev;

private:
//Debug
	void deActivate();
		// When a link is not on a list, it must be deactivated
		// in order to detect the application attempt to put a given object 
		// on two different lists at the same time.

// Friends
	friend class RTRShmDList;
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&, const RTRShmDLink&);
#else
public:
	void print(FILE*);
#endif
		// Friends
};

inline 
void RTRShmDLink::deActivate()
{
	_offsetOfPrev = _offsetOfNext = -1;
}

inline 
void RTRShmDLink::setNotActive()
{
	_offsetOfPrev = _offsetOfNext = -1;
}

inline 
RTRBOOL RTRShmDLink::isActive() const
{
	return((_offsetOfPrev != -1) || (_offsetOfNext != -1 ));
}

inline 
int RTRShmDLink::offset(const char *base) const
{
	return (int)((rtrUIntPtr)this - (rtrUIntPtr)base);
}

inline 
int RTRShmDLink::offsetOfNext() const
{
	return _offsetOfNext;
}

inline 
int RTRShmDLink::offsetOfPrev() const
{
	return _offsetOfPrev;
}

inline 
RTRShmDLink *RTRShmDLink::next(const char *base) const
{
	return (RTRShmDLink *)(base + _offsetOfNext);
}

inline 
RTRShmDLink *RTRShmDLink::previous(const char *base) const
{
	return (RTRShmDLink *)(base + _offsetOfPrev);
}

inline 
void RTRShmDLink::setNext(RTRShmDLink *link, const char *base)
{
	_offsetOfNext = link->offset(base);
}

inline 
void RTRShmDLink::setPrev(RTRShmDLink *link, const char *base)
{
	_offsetOfPrev = link->offset(base);
}

// Synopsis:
// #include"rtr/shmlinkl.h"
//
// Description:
// See Also:
//	RTRShmDLink1, RTRShmDLink2, RTRShmDList
//
// Inherits:
//	RTRShmDLink
//

class RTRShmDLink0: public RTRShmDLink
{ 
public: 
	RTRShmDLink0(); 
		// _TAG Constructor

	~RTRShmDLink0(); 
		// _TAG Destructor

};

// Synopsis:
// #include"rtr/shmlinkl.h"
//
// Description:
// See Also:
//  RTRShmDLink0, RTRShmDLink2, RTRShmDList
//
// Inherits:
//  RTRShmDLink
//

class RTRShmDLink1: public RTRShmDLink
{ 
public: 
	RTRShmDLink1(); 
		// _TAG Constructor

	~RTRShmDLink1(); 
		// _TAG Destructor

};

// Synopsis:
// #include"rtr/shmlinkl.h"
//
// Description:
// See Also:
//  RTRShmDLink0, RTRShmDLink1, RTRShmDList
//
// Inherits:
//  RTRShmDLink
//

class RTRShmDLink2: public RTRShmDLink
{ 
public: 
	RTRShmDLink2(); 
		// _TAG Constructor

	~RTRShmDLink2(); 
		// _TAG Destructor

};

// Synopsis:
// #include"rtr/shmlinkl.h"
//
// Description:
// See Also:
//	RTRShmDLink, RTRShmDLink0, RTRShmDLink1, RTRShmDLink2
//

class RTRShmDList
{
public:
// Constructor
	RTRShmDList();
		// _TAG Constructor

	RTRShmDList(const char *);
		// _TAG Constructor

// Destructor
	~RTRShmDList();
		// _TAG Destructor

// Put
	void putFirst(RTRShmDLink *link, const char *base);
		// _TAG01 Put

	void putLast(RTRShmDLink *link, const char *base);
        // _TAG01 Put

	void putPrevious(RTRShmDLink *link, RTRShmDLink *newLink, const char *base);
        // _TAG01 Put

	void putNext(RTRShmDLink *link, RTRShmDLink *newLink, const char *base);
        // _TAG01 Put

// Get
	RTRShmDLink *next(RTRShmDLink *link, const char *base) const;
		// _TAG02 Get

	RTRShmDLink *previous(RTRShmDLink *link, const char *base) const;
        // _TAG02 Get

	RTRShmDLink *first(const char *base);
        // _TAG02 Get

	RTRShmDLink *last(const char *base);
        // _TAG02 Get

// Remove
	void remove(RTRShmDLink *link, const char *base);
		// _TAG03 Remove

	void removeAll(const char *base);
        // _TAG03 Remove

// Concatenate
	void append(RTRShmDList *list, const char *base);
		// _TAG04 Concatenate

	void prepend(RTRShmDList *list, const char *base);
        // _TAG04 Concatenate

// Split
	void split(RTRShmDLink *link, RTRShmDList *list, const char *base);
		// _TAG05 Split

// Membership
	RTRBOOL has(RTRShmDLink *link, const char *base) const;
		// _TAG06 Membership

// State
	inline RTRBOOL isEmpty() const;
		// _TAG07 State

// Size
	int count(const char *base) const;
		// _TAG08 Size

// Initialization
	inline void reset(const char *base);
		// _TAG09 Initialization

protected:
	RTRShmDLink _sentinel;
		// A sentinell is an artificial (and well known) element.
		// An empty list contains the sentinel element only.
		// sentinel.next() points to the first element on a list
		// sentinel.previous() points to the last element on a list

protected:
	inline RTRShmDLink *getSentinel();

	RTRShmDLink *next_no_assertions(RTRShmDLink *link, const char *base);

private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRShmDList(const RTRShmDList&);
	RTRShmDList& operator=(const RTRShmDList&);
};

inline 
RTRBOOL RTRShmDList::isEmpty() const
{
	return !_sentinel.isActive();
}

inline 
void RTRShmDList::reset(const char *base)
{
	_sentinel._offsetOfNext = _sentinel.offset(base);
	_sentinel._offsetOfPrev = _sentinel.offset(base);
}

inline 
RTRShmDLink *RTRShmDList::getSentinel()
{
	return &_sentinel;
}

#endif
