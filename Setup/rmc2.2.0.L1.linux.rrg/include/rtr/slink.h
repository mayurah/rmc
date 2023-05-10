//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/03
//

#ifndef _slink_h
#define _slink_h

// Synopsis:
//
// Description:
//
// Defines implementation of two single link lists based on RTRSLink link:
//		class RTRSList and class RTRHSList
// These two classes are the based classes for RTRLiteSList and RTRLiteSLinkList
//
// RTRSList maintains head and tail, RTRHSList maintains head only
// TRHSList requires less memory but operations on the tail are more
// expensive than for RTRSList.
//
// See Also:
//

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"

class RTRSLink
{
public:
// Constructor
	inline RTRSLink() {_next = this;};
		// _TAG Contructor

// Destructor
	inline ~RTRSLink() {};
		// _TAG Destructor

// Support
	inline void setNotActive()
		// _TAG01 Support
	{
		_next = this;
	}

	inline bool isActive() const
        // _TAG01 Support
	{
		return(_next != this);
	}

protected:
// Put
	inline void putNext(RTRSLink *link)
	{
		link->_next = _next;
		_next = link;
	}
		// put new link after this link

// Get
	inline RTRSLink *next() const
	{
		return(_next);
	}

// Set
	inline void setNext(RTRSLink *link)
	{
		_next = link;
	}

protected:
	RTRSLink *_next;

private:

// Friends
friend class RTRSList;
friend class RTRHSList;
};





// Synopsis:
//
// Description:
//
// See Also: RTRSLink
//	

class RTRSLink0: public RTRSLink 
{ 
public: 
	// _TAG Constructor 
	inline RTRSLink0() {}; 
	// _TAG Destructor
	inline ~RTRSLink0() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRSLink
//  

class RTRSLink1: public RTRSLink 
{ 
public: 
	// _TAG Constructor
	inline RTRSLink1() {}; 
	// _TAG Destructor
	inline ~RTRSLink1() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRSLink
//  

class RTRSLink2: public RTRSLink 
{ 
public: 
	// _TAG Constructor
	inline RTRSLink2() {}; 
	// _TAG Destructor
	inline ~RTRSLink2() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRSLink
//  

class RTRSLink3: public RTRSLink 
{ 
public: 
	// _TAG Constructor
	inline RTRSLink3() {}; 
	// _TAG Destructor
	inline ~RTRSLink3() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRSLink
//  
	
class RTRSLink4: public RTRSLink 
{ 
public: 
	// _TAG Constructor
	inline RTRSLink4() {}; 
	// _TAG Destructor
	inline ~RTRSLink4() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRSLink
//  

class RTRSLink5: public RTRSLink 
{ 
public: 
	// _TAG Constructor
	inline RTRSLink5() {}; 
	// _TAG Destructor
	inline ~RTRSLink5() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRSLink
//  

class RTRSLink6: public RTRSLink 
{ 
public: 
	// _TAG Constructor
	inline RTRSLink6() {}; 
	// _TAG Destructor
	inline ~RTRSLink6() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRSLink
//  

class RTRSLink7: public RTRSLink 
{ 
public: 
	// _TAG Constructor
	inline RTRSLink7() {}; 
	// _TAG Destructor
	inline ~RTRSLink7() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRSLink
//  

class RTRSLink8: public RTRSLink 
{ 
public: 
	// _TAG Constructor
	inline RTRSLink8() {}; 
	// _TAG Destructor
	inline ~RTRSLink8() {}; 
};

// Synopsis:
//
// Description:
//
// See Also: RTRSLink
//  

class RTRSLink9: public RTRSLink 
{ 
public: 
	// _TAG Constructor
	inline RTRSLink9() {}; 
	// _TAG Destructor
	inline ~RTRSLink9() {}; 
};

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRSList
{
public:
// Constructor
	inline RTRSList()
		// _TAG Contructor
	{
		_head.setNext(0);
		_tail.setNext(0);
	}

// Destructor
	inline ~RTRSList()
		// _TAG Destructor
	{
		removeAll();
	}

// Put
	inline void putFirst(RTRSLink *link)
		// _TAG01 Put
	{
		RTPRECONDITION(link != 0);
		_head.putNext(link);
		if (!link->next()) _tail.setNext(link);
	}

	inline void putLast(RTRSLink *link)
        // _TAG01 Put
	{
		RTPRECONDITION(link != 0);
		_tail.next() ? _tail.next()->putNext(link) : _head.putNext(link);
		_tail.setNext(link);
	}

	inline void putPrevious(RTRSLink *link, RTRSLink *newLink)
        // _TAG01 Put
	{
		RTPRECONDITION(link != &_head);
		RTPRECONDITION(link != 0);
		RTPRECONDITION(newLink != 0);
		//RTPRECONDITION(has(link));
		RTPRECONDITION(link->isActive());
		RTPRECONDITION(!newLink->isActive());

		RTRSLink *l = &_head;
		while (link != l->next()) l = l->next();
		l->putNext(newLink);
	}

	inline void putNext(RTRSLink *link, RTRSLink *newLink)
        // _TAG01 Put
	{
		RTPRECONDITION(link != 0);
		RTPRECONDITION(newLink != 0);
		//RTPRECONDITION(has(link));
		RTPRECONDITION(link->isActive());
		RTPRECONDITION(!newLink->isActive());

		link->putNext(newLink);
		if (!newLink->next()) _tail.setNext(newLink);
	}

// Get
	inline RTRSLink *next(const RTRSLink *link) const
		// _TAG02 Get
	{
		RTPRECONDITION(link != 0);
		//RTPRECONDITION(has(link) || (link == &_head) || (link == &_tail));
		RTPRECONDITION(link->isActive());

		return(link->next());
	}

	inline RTRSLink *previous(const RTRSLink *link) const
        // _TAG02 Get
	{
		RTPRECONDITION(link != 0);
		//RTPRECONDITION(has(link));
		RTPRECONDITION(link->isActive());

		RTRSLink *l = (RTRSLink*)&_head;
		while (link != l->next()) l = l->next();
		return((l == &_head) ? 0 : l);
	}

	inline RTRSLink *first() const
        // _TAG02 Get
	{
		return(_head.next());
	}

	inline RTRSLink *last() const
        // _TAG02 Get
	{
		return(_tail.next());
	}

	inline RTRSLink *head() const
		// _TAG02 Get
	{
		return((RTRSLink*)&_head);
	}

// Remove
	inline void removeNext(RTRSLink *link, RTRSLink *nextLink)
		// _TAG03 Remove
	{
		RTPRECONDITION(link != 0);
		//RTPRECONDITION(has(link));
		RTPRECONDITION(link->isActive());
		RTPRECONDITION(nextLink->isActive());
		RTPRECONDITION(nextLink != 0);
		RTPRECONDITION(link->next() == nextLink);

		if (0 == (link->_next = nextLink->next()))
		{
			(link == &_head) ? _tail.setNext(0) : _tail.setNext(link);
		}
		nextLink->setNotActive();
	}

	inline void remove(RTRSLink *link)
		// _TAG03 Remove
	{
		RTPRECONDITION(link != 0);
		//RTPRECONDITION(has(link));
		RTPRECONDITION(link->isActive());

		RTRSLink *l = &_head;
		while (link != l->next()) l = l->next();
		if ((l->_next = link->next()) == 0)
		{
			(l == &_head) ? _tail.setNext(0) : _tail.setNext(l);
		}
		link->setNotActive();
	}

	inline RTRSLink *removeFirst()
		// _TAG03 Remove
	{
		RTRSLink *link = _head.next();
		if (link) removeNext(&_head, link);
		return link;
	}

	inline RTRSLink *removeFirst(int &cnt)
		// _TAG03 Remove
	{
		RTRSLink *link = _head.next();
		if (link) { removeNext(&_head, link); cnt--; }
		return link;
	}

	inline RTRSLink *removeLast()
		// _TAG03 Remove
	{
		RTRSLink *link = _tail.next();
		if (link) remove(link);
		return link;
	}

	inline RTRSLink *removeLast(int &cnt)
		// _TAG03 Remove
	{
		RTRSLink *link = _tail.next();
		if (link) { remove(link); cnt--; }
		return link;
	}

	void removeAll();
        // _TAG03 Remove

// Concatenate
	void append(RTRSList *list);
		// _TAG04 Concatenate

	void prepend(RTRSList *list);
        // _TAG04 Concatenate

// Membership
	bool has(const RTRSLink *link) const;
		// _TAG06 Membership

// State
	inline bool isEmpty() const
		// _TAG07 State
	{
		return(_head.next() == 0);
	}

// Size
	int count() const;
		// _TAG08 Size

protected:
// Operations
	inline void reset()
	{
		_head.setNext(0);
		_tail.setNext(0);
	}

// Data
	RTRSLink _head;
	RTRSLink _tail;
		// _head.next() points to the first element on a list or 0
		// _tail.next() points to the last element on a list or 0

private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRSList(const RTRSList&);
	RTRSList& operator=(const RTRSList&);
		//
// Friends
};

class RTRHSList
{
public:
// Constructor
	inline RTRHSList()
		// _TAG Contructor
	{
		_head.setNext(0);
	}

// Destructor
	inline ~RTRHSList()
		// _TAG Destructor
	{
		removeAll();
	}

// Put
	inline void putFirst(RTRSLink *link)
		// _TAG01 Put
	{
		RTPRECONDITION(link != 0);
		_head.putNext(link);
	}

	inline void putLast(RTRSLink *link)
        // _TAG01 Put
	{
		RTPRECONDITION(link != 0);
		RTRSLink *l = &_head;
		while (l->next()) l = l->next();
		l->putNext(link);
	}

	inline void putPrevious(RTRSLink *link, RTRSLink *newLink)
        // _TAG01 Put
	{
		RTPRECONDITION(link != &_head);
		RTPRECONDITION(link != 0);
		RTPRECONDITION(newLink != 0);
		//RTPRECONDITION(has(link));
		RTPRECONDITION(link->isActive());
		RTPRECONDITION(!newLink->isActive());

		RTRSLink *l = &_head;
		while (link != l->next()) l = l->next();
		l->putNext(newLink);
	}

	inline void putNext(RTRSLink *link, RTRSLink *newLink)
        // _TAG01 Put
	{
		RTPRECONDITION(link != 0);
		RTPRECONDITION(newLink != 0);
		//RTPRECONDITION(has(link));
		RTPRECONDITION(link->isActive());
		RTPRECONDITION(!newLink->isActive());

		link->putNext(newLink);
	}

// Get
	inline RTRSLink *next(const RTRSLink *link) const
		// _TAG02 Get
	{
		RTPRECONDITION(link != 0);
		//RTPRECONDITION(has(link) || (link == &_head));
		RTPRECONDITION(link->isActive());

		return(link->next());
	}

	inline RTRSLink *previous(const RTRSLink *link) const
        // _TAG02 Get
	{
		RTPRECONDITION(link != 0);
		//RTPRECONDITION(has(link));
		RTPRECONDITION(link->isActive());

		RTRSLink *l = (RTRSLink*)&_head;
		while (link != l->next()) l = l->next();
		return((l == &_head) ? 0 : l);
	}

	inline RTRSLink *first() const
        // _TAG02 Get
	{
		return(_head.next());
	}

	inline RTRSLink *last() const
        // _TAG02 Get
	{
		RTRSLink *l = (RTRSLink*)&_head;
		while (l->next()) l = l->next();
		return((l == &_head) ? 0 : l);
	}

	inline RTRSLink *head() const
		// _TAG02 Get
	{
		return((RTRSLink*)&_head);
	}

// Remove
	inline void removeNext(RTRSLink *link, RTRSLink *nextLink)
		// _TAG03 Remove
	{
		RTPRECONDITION(link != &_head);
		RTPRECONDITION(link != 0);
		//RTPRECONDITION(has(link));
		RTPRECONDITION(link->isActive());
		RTPRECONDITION(nextLink->isActive());
		RTPRECONDITION(nextLink != 0);
		RTPRECONDITION(link->next() == nextLink);

		link->setNext(nextLink->next());
		nextLink->setNotActive();
	}

	inline void remove(RTRSLink *link)
		// _TAG03 Remove
	{
		RTPRECONDITION(link != 0);
		//RTPRECONDITION(has(link));
		RTPRECONDITION(link->isActive());

		RTRSLink *l = &_head;
		while (link != l->next()) l = l->next();
		l->setNext(link->next());
		link->setNotActive();
	}

	inline RTRSLink *removeFirst()
		// _TAG03 Remove
	{
		RTRSLink *link = _head.next();
		if (link) removeNext(&_head, link);
		return link;
	}

	inline RTRSLink *removeFirst(int &cnt)
		// _TAG03 Remove
	{
		RTRSLink *link = _head.next();
		if (link) { removeNext(&_head, link); cnt--; }
		return link;
	}

	inline RTRSLink *removeLast()
		// _TAG03 Remove
	{
		RTRSLink *l = _head.next();
		if (l)
		{
			RTRSLink *prevl = &_head;
			while (l->next()) { prevl = l; l = l->next(); }
			removeNext(prevl, l);
			return l;
		}
		else
			return 0;
	}

	inline RTRSLink *removeLast(int &cnt)
		// _TAG03 Remove
	{
		RTRSLink *l = _head.next();
		if (l)
		{
			RTRSLink *prevl = &_head;
			while (l->next()) { prevl = l; l = l->next(); }
			removeNext(prevl, l); cnt--;
			return l;
		}
		else
			return 0;	
	}

	void removeAll();
        // _TAG03 Remove

// Concatenate
	void append(RTRHSList *list);
		// _TAG04 Concatenate

	void prepend(RTRHSList *list);
        // _TAG04 Concatenate

// Membership
	bool has(const RTRSLink *link) const;
		// _TAG06 Membership

// State
	inline bool isEmpty() const
		// _TAG07 State
	{
		return(_head.next() == 0);
	}

// Size
	int count() const;
		// _TAG08 Size

protected:
// Operations
	inline void reset()
	{
		_head.setNext(0);
	}

// Data
	RTRSLink _head;
		// _head.next() points to the first element on a list or 0
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRHSList(const RTRHSList&);
	RTRHSList& operator=(const RTRHSList&);
		//
// Friends
};

#endif
