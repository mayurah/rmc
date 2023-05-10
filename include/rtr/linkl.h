//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/94
//

#ifndef _linkl_h
#define _linkl_h

#include "rtr/rtrdefs.h"

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRDLink
{
public:
// Constructor
	inline RTRDLink() {_prev = _next = 0;};
		// _TAG Contructor

// Destructor
	inline ~RTRDLink() {};
		// _TAG Destructor

// Remove
	inline void remove()
		// remove this link from list
		// _TAG01 Remove
	{
		_prev->_next = _next;
		_next->_prev = _prev;
		_prev = _next = 0;
	}

// Support
	inline void setNotActive()
		// _TAG02 Support
	{
		_prev = _next = 0;
	}

	inline RTRBOOL isActive() const
        // _TAG02 Support
	{
		return(_prev || _next);
	}

protected:
// Put
	inline void putPrevious(RTRDLink *link)
		// put new link before this link
	{
		link->_prev = _prev;
		link->_next = this;
		_prev = _prev->_next = link;
	}

	inline void putNext(RTRDLink *link)
	{
		link->_next = _next;
		link->_prev = this;
		_next = _next->_prev = link;
	}
		// put new link after this link

// Get
	inline RTRDLink *next() const
	{
		return(_next);
	}

	inline RTRDLink *previous() const
	{
		return(_prev);
	}

// Set
	inline void setNext(RTRDLink *link)
	{
		_next = link;
	}

	inline void setPrev(RTRDLink *link)
	{
		_prev = link;
	}

protected:
	RTRDLink *_next;
	RTRDLink *_prev;

private:
//Debug
	// When a link is not on a list, it must be deactivated
	// in order to detect the application attempt to put a given object 
	// on two different lists at the same time.
	inline void deActivate()
	{
		_prev = _next = 0;
	}

// Friends
friend class RTRDList;
};





// Synopsis:
//
// Description:
//
// See Also: RTRDLink
//	

class RTRDLink0: public RTRDLink 
{ 
public: 
	// _TAG Constructor 
	inline RTRDLink0() {}; 
	// _TAG Destructor
	inline ~RTRDLink0() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRDLink
//  

class RTRDLink1: public RTRDLink 
{ 
public: 
	// _TAG Constructor
	inline RTRDLink1() {}; 
	// _TAG Destructor
	inline ~RTRDLink1() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRDLink
//  

class RTRDLink2: public RTRDLink 
{ 
public: 
	// _TAG Constructor
	inline RTRDLink2() {}; 
	// _TAG Destructor
	inline ~RTRDLink2() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRDLink
//  

class RTRDLink3: public RTRDLink 
{ 
public: 
	// _TAG Constructor
	inline RTRDLink3() {}; 
	// _TAG Destructor
	inline ~RTRDLink3() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRDLink
//  
	
class RTRDLink4: public RTRDLink 
{ 
public: 
	// _TAG Constructor
	inline RTRDLink4() {}; 
	// _TAG Destructor
	inline ~RTRDLink4() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRDLink
//  

class RTRDLink5: public RTRDLink 
{ 
public: 
	// _TAG Constructor
	inline RTRDLink5() {}; 
	// _TAG Destructor
	inline ~RTRDLink5() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRDLink
//  

class RTRDLink6: public RTRDLink 
{ 
public: 
	// _TAG Constructor
	inline RTRDLink6() {}; 
	// _TAG Destructor
	inline ~RTRDLink6() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRDLink
//  

class RTRDLink7: public RTRDLink 
{ 
public: 
	// _TAG Constructor
	inline RTRDLink7() {}; 
	// _TAG Destructor
	inline ~RTRDLink7() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRDLink
//  

class RTRDLink8: public RTRDLink 
{ 
public: 
	// _TAG Constructor
	inline RTRDLink8() {}; 
	// _TAG Destructor
	inline ~RTRDLink8() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRDLink
//  

class RTRDLink9: public RTRDLink 
{ 
public: 
	// _TAG Constructor
	inline RTRDLink9() {}; 
	// _TAG Destructor
	inline ~RTRDLink9() {}; 
};

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRDList
{
public:
// Constructor
	inline RTRDList()
		// _TAG Contructor
	{
		_sentinel.setNext(&_sentinel);
		_sentinel.setPrev(&_sentinel);
	}

// Destructor
	inline ~RTRDList()
		// _TAG Destructor
	{
		removeAll();
	}

// Put
	inline void putFirst(RTRDLink *link)
		// _TAG01 Put
	{
		RTPRECONDITION(link != 0);
		RTPRECONDITION(!link->isActive());
		_sentinel.putNext(link);
	}

	inline void putLast(RTRDLink *link)
        // _TAG01 Put
	{
		RTPRECONDITION(link != 0);
		RTPRECONDITION(!link->isActive());
		_sentinel.putPrevious(link);
	}

	inline void putPrevious(RTRDLink *link, RTRDLink *newLink)
        // _TAG01 Put
	{
		RTPRECONDITION(link != 0);
		RTPRECONDITION(newLink != 0);
		RTPRECONDITION(has(link));
		RTPRECONDITION(!newLink->isActive());
		link->putPrevious(newLink);
	}

	inline void putNext(RTRDLink *link, RTRDLink *newLink)
        // _TAG01 Put
	{
		RTPRECONDITION(link != 0);
		RTPRECONDITION(newLink != 0);
		RTPRECONDITION(has(link));
		RTPRECONDITION(!newLink->isActive());
		link->putNext(newLink);
	}

// Get
	inline RTRDLink *next(const RTRDLink *link) const
		// _TAG02 Get
	{
		RTPRECONDITION(link != 0);
		RTPRECONDITION(link->isActive());
		RTPRECONDITION(has(link) || (link == &_sentinel));
		return((link->next() == &_sentinel) ? 0 : link->next());
	}

	inline RTRDLink *previous(const RTRDLink *link) const
        // _TAG02 Get
	{
		RTPRECONDITION(link != 0);
		RTPRECONDITION(link->isActive());
		RTPRECONDITION(has(link) || (link == &_sentinel));
		return((link->previous() == &_sentinel) ? 0 : link->previous());
	}

	inline RTRDLink *first() const
        // _TAG02 Get
	{
		return(next(&_sentinel));
	}

	inline RTRDLink *last() const
        // _TAG02 Get
	{
		return(previous(&_sentinel));
	}

// Remove
	inline void remove(RTRDLink *link)
		// _TAG03 Remove
	{
		RTPRECONDITION(link != 0);
		RTPRECONDITION(link->isActive());
		RTPRECONDITION(has(link));
		link->remove();
	}

	inline RTRDLink *removeFirst()
		// _TAG03 Remove
	{
		RTRDLink *link = _sentinel.next();
		if (link != &_sentinel)
		{
			link->remove();
			return link;
		}
		else
			return 0;
	}

	inline RTRDLink *removeFirst(int &cnt)
		// _TAG03 Remove
	{
		RTRDLink *link = _sentinel.next();
		if (link != &_sentinel)
		{
			link->remove();
			cnt--;
			return link;
		}
		else
			return 0;
	}

	inline RTRDLink *removeLast()
		// _TAG03 Remove
	{
		RTRDLink *link = _sentinel.previous();
		if (link != &_sentinel)
		{
			link->remove();
			return link;
		}
		else
			return 0;
	}

	inline RTRDLink *removeLast(int &cnt)
		// _TAG03 Remove
	{
		RTRDLink *link = _sentinel.previous();
		if (link != &_sentinel)
		{
			link->remove();
			cnt--;
			return link;
		}
		else
			return 0;
	}

	void removeAll();
        // _TAG03 Remove

// Concatenate
	void append(RTRDList *list);
		// _TAG04 Concatenate

	void prepend(RTRDList *list);
        // _TAG04 Concatenate

// Split
	void split(RTRDLink *link, RTRDList *list);
		// _TAG05 Split

// Membership
	RTRBOOL has(const RTRDLink *link) const;
		// _TAG06 Membership

// State
	inline RTRBOOL isEmpty() const
		// _TAG07 State
	{
		return((_sentinel.next() == &_sentinel) ? RTRTRUE : RTRFALSE);
	}

// Size
	int count() const;
		// _TAG08 Size

protected:
// Operations
	inline void reset()
	{
		_sentinel.setNext(&_sentinel);
		_sentinel.setPrev(&_sentinel);
	}

	inline RTRDLink *getSentinel()
	{
		return(&_sentinel);
	}

	inline RTRDLink *next_no_assertions(const RTRDLink *link) const
	{
		return((link->next() == &_sentinel) ? 0 : link->next());
	}

	inline RTRDLink *first_no_assertions() const
	{
		return(next_no_assertions(&_sentinel));
	}

// Data
	RTRDLink _sentinel;
		// A sentinell is an artificial (and well known) element.
		// An empty list contains the sentinel element only.
		// sentinel.next() points to the first element on a list
		// sentinel.previous() points to the last element on a list

private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRDList(const RTRDList&);
	RTRDList& operator=(const RTRDList&);
		//
};

#endif
