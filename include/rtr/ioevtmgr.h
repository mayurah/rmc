//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Dec. 28 1993"
// Version: 1.0

#ifndef _ioevtmgr_h 
#define _ioevtmgr_h

#include "rtr/indxable.h"

class RTRGenericPointerVector;
class RTRIOClient;
class RTRIOClientRegistration;
class RTRIOClientRegistrationIterator;

// Synopsis:
// #include"rtr/ioevtmgr.h"
//
// Description:
// 	Implementation class used to associate/disassociate instances of
// 	RTRIOClient (IO Client) with file descriptors.  It maintains a store
// 	(which is NOT indexed by file descriptor) of pointers to
// 	IOClientRegistration objects.
// 
// See Also:
//	RTREventNotifier     		
// Inherits:
//	RTRIndexableStore
//

class RTRIOEventMgr : public RTRIndexableStore
{
public:
// Constructor
	RTRIOEventMgr(int size);
		// _TAG Constructor

// Destructor
	~RTRIOEventMgr();
		// _TAG Destructor

// Attributes
	virtual int lower() const;
		// _TAG01 Attributes

	virtual int upper() const;
		// _TAG01 Attributes

// Query
	RTRBOOL has(int fd) const;
		// _TAG02 Query

	virtual int count() const;
		// _TAG02 Query

// Access
	RTRIOClient *client(int fd) const;
		// _TAG03 Access

	void *operator[](int index) const;
		// note that index is not a file descriptor
        // REQUIRE : i >= lower() && i <= upper()
		// _TAG03 Access

	RTRIOClientRegistration *clientRegistration(int index) const;
		// note that index is not a file descriptor
        // REQUIRE : i >= lower() && i <= upper() 	
		// _TAG03 Access

// Insert
	void put(RTRIOClient& newClient, int fd);
		// REQUIRE: !has(fd);
		// ENSURE : has(fd) && (client(fd) == &newClient)
		// _TAG04 Insert

// Remove
	void remove(int fd);
		// ENSURE : !has(fd)
		// _TAG05 Remove

// Sequential access
	RTRIOClientRegistrationIterator iterator() const;
		// _TAG06 Sequential access

protected:
	RTRIOClientRegistration *find(int fd) const;

	RTRGenericPointerVector *_store;
};

#endif 
