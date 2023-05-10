//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Aug. 22 1995"
// Version: 1.0

#ifndef _semaset_h
#define _semaset_h

#include "rtr/portipc.h"
#include "rtr/rtstring.h"

// Synopsis:
// #include"rtr/semaset.h"
//
// Description:
// 	A base class representing a set of semaphores allocated using a single
// 	semaphore key.
//
// See Also:
//	RTRServerSemaphoreSet, RTRSemaphore, RTRSemaphoreFlag, RTRBinarySemaphore,
//	RTRReadWriteLock
//

class RTRSemaphoreSet
{ 
public:
// Identity
	inline int id () const;
		// The unique id of this semaphore set.
		// _TAG01 Identity

	RTRString &key();
		// The key used to create/reference this set.
        // _TAG01 Identity

// State
	inline RTRBOOL error() const;
		// Is this set in an error state?
		// _TAG02 State

// Attributes
	RTRString text() const;
		// An explanation of the error encountered by this set.
		// REQUIRE : error()
		// _TAG03 Attributes

	inline int numberOfSemaphores() const;
		// The number of semaphores in this set.
		// REQUIRE : !error()
		// _TAG03 Attributes

protected:
// Constructor
	RTRSemaphoreSet(const RTRString& k);
		// ENSURE : key() == k
		// ENSURE : numberOfSemaphores() == 0
		// ENSURE : error() 

	RTRSemaphoreSet(const RTRString& k, int num);
		// ENSURE : key() == k
		// ENSURE : numberOfSemaphores() == num
		// ENSURE : error() 

// Data
	int _id;
	RTRString _key;
	int _lastErrorNumber;
	int _numberOfSemaphores;
		// Data
}; 

inline 
int RTRSemaphoreSet::id () const
{
	return _id;
}

inline 
RTRBOOL RTRSemaphoreSet::error() const
{
	return _id == -1;
}

inline 
int RTRSemaphoreSet::numberOfSemaphores() const
{
	return _numberOfSemaphores;
}

// Synopsis:
// #include"rtr/semaset.h"
//
// Description:
// 	A descendant of RTRSemaphoreSet which implements a primitive scheme
// 	for allocating semaphores. Does not currently support de-allocation and
// 	re-use of semaphore numbers.
//
// Semaphore number allocation is used primarily by the various semaphore
//	implementation classes: RTRReadWriteLock, RTRBinarySemaphore, and
//	RTRSemaphoreFlag.
//
// See Also:
//  RTRSemaphoreSet, RTRSemaphore, RTRSemaphoreFlag, RTRBinarySemaphore,
//	RTRReadWriteLock
//

class RTRServerSemaphoreSet :
	public RTRSemaphoreSet
{ 
public:
// Constructor
	RTRServerSemaphoreSet(const RTRString& k, int number);
		// Creates new set with number of semaphores. 
		// ENSURE : key() == k
		// ENSURE : error() or else numberOfSemaphores() == number()
		// ENSURE : error() or else numberUnusedSemaphores() == number()
		// _TAG Constructor

// Destructor
	~RTRServerSemaphoreSet();
		// _TAG Destructor

// Query
	inline int numberUnusedSemaphores() const;
		// The number of semaphores from this set which have not been
		// allocated.
		// REQUIRE : !error()
		// _TAG01 Query

// Attributes
	inline int lastAllocatedSemaphoreNumber() const;
		// The result of the last call to allocateSemaphoreNumber()
		// REQUIRE : !error()
		// ENSURE : result >= 0
		// ENSURE : result < numberOfSemaphores()
		// _TAG02 Attributes

// Operations
	void allocateSemaphoreNumber();
		// Allocate the next unused semaphore number and make it available
		// via lastAllocatedSemaphoreNumber()
		// REQUIRE : !error()
		// REQUIRE : numberUnusedSemaphores() > 0;
		// _TAG03 Operations

protected:
// Data
	int _lastAllocatedSemaphoreNumber;
		// Data
}; 

inline 
int RTRServerSemaphoreSet::lastAllocatedSemaphoreNumber() const
{
	return _lastAllocatedSemaphoreNumber;
}

inline 
int RTRServerSemaphoreSet::numberUnusedSemaphores() const
{
	return numberOfSemaphores() - (lastAllocatedSemaphoreNumber() + 1);
}

#endif
