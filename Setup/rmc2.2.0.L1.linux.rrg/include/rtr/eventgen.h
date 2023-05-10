//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60523                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 15 1998"
// Version: 1.0

#ifndef _rtr_eventgen_h
#define _rtr_eventgen_h

#include "rtr/dlinkl.h"
#include "rtr/eglink.h"

//
// Synopsis:
// #include "rtr/eventgen.h"
//
// Description:
// 
// See Also:
//
// Inherits:
//

template <class G, class C>
class RTREventGenerator
{ 
public:
// Constructor
	RTREventGenerator();
		// _TAG Constructor

// Destructor
	virtual ~RTREventGenerator();
		// _TAG Destructor

// Attributes
	int count() const;
		// _TAG02 Attributes

// Query
	RTRBOOL hasClient(const C& client) const;
		// Is the given client registered with this generator.
		// _TAG04 Query

// Access
	RTRDLinkList<RTREventGenLink<C>, RTRDLink0> & clients() const;
		// _TAG05 Access

// Operations
	virtual void addClient(const C& client);
		// REQUIRE: !hasClient(client);
		// ENSURE: hasClient(client);
		// _TAG07 Operations

	virtual void dropClient(const C& client);
		// ENSURE: !hasClient(client);
		// _TAG07 Operations

#ifdef WIN32 /* work around VC++5.0 compiler bug */

	void notify(void (G::*callback)(C&), G& g)
	{
		_notifying = RTRTRUE;
		for ( RTREventGenLink<C>* l = _clients.first(); l; )
		{
			RTREventGenLink<C>* n = _clients.next(l);
			((&g)->*callback)(l->client());
			l = n;
		}
		_clients.append(&_tmp);
		_notifying = RTRFALSE;
	}

		// THIS VERSION OF notify IS OBSOLETE
	void notify(void (G::*callback)(C&))
	{
		_notifying = RTRTRUE;
		for ( RTREventGenLink<C>* l = _clients.first(); l; )
		{
			RTREventGenLink<C>* n = _clients.next(l);
			(((G*)this)->*callback)(l->client());
			l = n;
		}
		_clients.append(&_tmp);
		_notifying = RTRFALSE;
	}

#else
	void notify(void (G::*)(C&), G&);
		// Invoke the given generator event method for all clients;
		// _TAG07 Operations

	void notify(void (G::*)(C&));
		// OBSOLETE
		// Invoke the given generator event method for all clients;
		// _TAG07 Operations

#endif /* work around VC++ 5.0 compiler bug */

protected:
// Utilities

// Data
	RTRDLinkList< RTREventGenLink<C>, RTRDLink0> _clients;
	RTRDLinkList< RTREventGenLink<C>, RTRDLink0> _tmp;
	RTRBOOL _notifying;

// Friends
private:
// Don't implement
	RTREventGenerator(const RTREventGenerator<G, C>&);
	RTREventGenerator<G, C> & operator=(const RTREventGenerator<G, C>&);
}; 

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("eventgen.C")
#else
#include "rtr/eventgen.C"
#endif
#endif

#endif
