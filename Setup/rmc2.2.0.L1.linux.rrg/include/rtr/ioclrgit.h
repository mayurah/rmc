//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: M. Schwenk
// Created: "Feb. 3 1995"
// Version: 1.0

#ifndef _rgioclit_h
#define _rgioclit_h

#include "rtr/rtrdefs.h"
#include "rtr/spinit.h"

class RTRIOClient;
class RTRIOClientRegistration;
class RTRIOEventMgr;

// Synopsis:
//
// Description:
//
// 	Implementation class used to iterate over registered clients.
//
// See Also:
//

class RTRIOClientRegistrationIterator
	: public RTRSparseIndexableIterator
{
public:
// Constructor
	RTRIOClientRegistrationIterator(const RTRIOEventMgr& manager);
		// _TAG Constructor

// Destructor
	virtual ~RTRIOClientRegistrationIterator();
		// _TAG Destructor

// Access
	RTRIOClientRegistration& registration() const;
		// _TAG01 Access

};

#endif 
