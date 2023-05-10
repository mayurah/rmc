//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 15 1998"
// Version: 1.0

#ifndef _rtr_eglink_h
#define _rtr_eglink_h

#include "rtr/linkl.h"

//
// Synopsis:
// #include "rtr/eglink.h"
//
// Description:
// 
// See Also:
//
// Inherits:
//

template < class C >
class RTREventGenLink :
	public RTRDLink0
{ 
protected:
// Data
	const C& _client;

public:
// Constructor
	inline RTREventGenLink(const C& c) : _client(c) { };
		// _TAG Constructor

// Destructor
	inline ~RTREventGenLink() {}
		// _TAG Destructor

// Attributes
	inline C& client() { return (C&)_client; };
		// _TAG02 Attributes

private:
// Don't implement
	RTREventGenLink(const RTREventGenLink<C>&);
	RTREventGenLink<C>& operator=(const RTREventGenLink<C>&);
}; 

#endif
