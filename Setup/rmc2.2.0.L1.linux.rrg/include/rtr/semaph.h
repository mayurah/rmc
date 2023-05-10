//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 07 1995"
// Version: 1.0

#ifndef _semaph_h
#define _semaph_h

#include "rtr/semaset.h"
#include "rtr/portipc.h"

// Synopsis:
// #include"rtr/semaph.h"
//
// Description:
// 	A base class which encapsulate semphore primatives. This class provides
// 	the means to get at various semaphore attributes and values but does not
// 	provide public methods by which the value of the semaphore can be changed.
//
// 	If constructed with a semaphore set then a new semaphore number is
// 	allocated from that set and a system semaphore is allocated with the
// 	key of the set and the newly allocated number.
//
// 	A semaphore may be constructed to access a system semaphore which already
// 	exists by providing the key and number of that system semaphore.
//
// See Also:
//	RTRBinarySemaphore, RTRSemaphoreFlag, RTRSemaphoreSet, 
//	RTRServerSemaphoreSet, RTRReadWriteLock 
//

class RTRSemaphore
{ 
public:
// Constructor
	RTRSemaphore(RTRServerSemaphoreSet& s, int initialValue, int numClients);
		// Allocate a new semaphore from the given set.
		// REQUIRE : !s.error()
		// REQUIRE : s.numberUnusedSemaphores() > 0
		// ENSURE : id() == s.id();
		// ENSURE : lastValue() == initialValue;
		// ENSURE : number() >= 0;
		// ENSURE : number() < s.numberOfSemaphores();
		// _TAG Constructor

	RTRSemaphore(const char *, int semNumber);
		// Attach to an existing semaphore from the set with the given key.
		// REQUIRE  : semNumber >= 0
		// REQUIRE  : semNumber < s.numberOfSemaphores()
		// ENSURE : id() == s.id();
		// ENSURE : number() == semNumber
        // _TAG Constructor

// Destructor
	~RTRSemaphore();
		// _TAG Destructor

// Identity
	inline HANDLE id() const;
		// The id of the semaphore set to which this semaphore belongs.
		// _TAG01 Identity

	inline int number() const;
		// The number of this semaphore within the set identified by id().
        // _TAG01 Identity

// State
	inline RTRBOOL error() const;
		// Is this semaphore in an error state?
		// _TAG02 State

// Attributes
	RTRString text() const;
		// An explanation of the error encountered by this semaphore. 
		// REQUIRE : error()
		// _TAG03 Attributes

#ifndef	_WIN32
	inline int lastValue() const;
		// Result of last call to getLastValue(). Not valid after other
		// "get" operation.
		// REQUIRE : !error()
        // _TAG03 Attributes

	inline int lastPID() const;
		// Result of last call to getLastPID(). Not valid after other
		// "get" operation.
		// REQUIRE : !error()
        // _TAG03 Attributes

	inline int lastNCount() const;
		// Result of last call to getLastNCount(). Not valid after other
		// "get" operation.
		// REQUIRE : !error()
        // _TAG03 Attributes

	inline int lastZCount() const;
		// Result of last call to getLastZCount(). Not valid after other
		// "get" operation.
		// REQUIRE : !error()
        // _TAG03 Attributes

// Access
	void getLastValue();
		// Make the semaphore value available as lastValue()
		// _TAG04 Access

	void getLastPID();
		// Make the pid of the last process to invoke a semaphore operation
		// available as lastPID()
        // _TAG04 Access

	void getLastNCount();
		// Make the semaphore ncount available as lastNCount()
        // _TAG04 Access

	void getLastZCount();
		// Make the semaphore zcount available as lastZCount()
        // _TAG04 Access

#endif

protected:
// Set operations
	void set(int);

	void decrement(int, RTRBOOL undo = RTRTRUE);
		// Blocking

	RTRBOOL tryDecrement(int, RTRBOOL undo = RTRTRUE);
		// Non-blocking

	void increment(int, RTRBOOL undo = RTRTRUE);

// Data
	HANDLE _id;
	int _number;
	int _lastErrorNumber;
	union store {
		int lastValue;
		int lastPID;
		int lastNCount;
		int lastZCount;
	} _store;
		// Data
}; 

inline 
HANDLE RTRSemaphore::id() const 
{ 
	return _id; 
}

inline 
int RTRSemaphore::number() const
{
	return _number;
}

inline 
RTRBOOL RTRSemaphore::error() const 
{ 
	return _lastErrorNumber != 0; 
}

#ifndef	_WIN32
inline 
int RTRSemaphore::lastValue() const
{
	return _store.lastValue;
}

inline 
int RTRSemaphore::lastPID() const
{
	return _store.lastPID;
}

inline 
int RTRSemaphore::lastNCount() const
{
	return _store.lastNCount;
}

inline 
int RTRSemaphore::lastZCount() const
{
	return _store.lastZCount;
}
#endif

#endif
