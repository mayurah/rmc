//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 07 1995"
// Version: 1.0

#ifndef _semlock_h
#define _semlock_h

#include "rtr/semaph.h"
#include "rtr/rtstring.h"

// Synopsis:
// #include"rtr/semlock.h"
//
// Description:
// 	A descendant of RTRSemaphore provides for locking between multiple "readers"
// 	and a single "writer"
//
// 	The controlling process ("server") creates an instance of RTRReadWriteLock
// 	using a semaphore set and  indicating the maximum number of readers which
// 	will be allowed.
//
// 	A client process creates an instance of RTRReadWriteLock by providing
// 	the key and number of an existing semaphore (created by the server).
//
// 	Once the appropriate access capability (read or write ) has been acquired,
// 	calling process may safely access the shared resource. Once access has
// 	been completed, the lock should be release using the appropriate operation
// 	(read or write).
//
// 	Acquisition of the lock (read or write capability) may be blocking or
// 	non-blocking.
//
// 	In the event of un-graceful process termination, any acquired capability
// 	will be released by the operating system.
//
// See Also:
//	RTRBinarySemaphore, RTRSemaphoreFlag
//
// Inherits:
//	RTRSemaphore
//

#ifndef _WIN32

class RTRReadWriteLock : 
	public RTRSemaphore
{ 
public:
// Constructor
	RTRReadWriteLock(RTRServerSemaphoreSet&, int maxReaders);
		// New read/write lock which allocates a new system semaphore
		// using the key of the given set and number allocated from the set.
		// _TAG Constructor

	RTRReadWriteLock(const char*, int semNumber, int maxReaders);
		// A new read/write lock attached to an existing system semaphore.
		// _TAG Constructor

// Operations
	void obtainReadAccess();
		// Obtain permission for read-only access to the shared resource.
		// Blocking
		// _TAG01 Operations

	RTRBOOL tryObtainReadAccess();
		// Obtain permission for read-only access to the shared resource.
		// Non-blocking, returns RTRTRUE if access acquired 
        // _TAG01 Operations

	void releaseReadAccess();
		// Release the read-permission acquired via a successful call to 
		// obtainReadAccess() or tryObtainReadAccess()
        // _TAG01 Operations

	void obtainWriteAccess();
		// Obtain permission for write-only access to the shared resource.
		// Blocking
        // _TAG01 Operations

	RTRBOOL tryObtainWriteAccess();
		// Obtain permission for write-only access to the shared resource.
		// Non-blocking, returns RTRTRUE if access acquired 
        // _TAG01 Operations

	void releaseWriteAccess();
		// Release the write-permission acquired via a successful call to 
		// obtainWriteAccess() or tryObtainWriteAccess()
        // _TAG01 Operations

protected:
// Data
	int _maxReaders;
}; 

// Synopsis:
// #include"rtr/semlock.h"
//
// Description:
// 	A descendant of RTRSemaphore whose value may only be 1 or 0. This lock
// 	may be obtained (blocking an non-blocking) and released. In the event
// 	of un-gracefull termination, an acquired lock will be released by the
// 	operating system.
//
// See Also:
// 	RTRServerSemaphoreSet, RTRReadWriteLock, RTRSemaphoreFlag
// 
// Inherits:
//	RTRSemaphore
//

class RTRBinarySemaphore : 
	public RTRSemaphore
{ 
public:
// Constructor
	RTRBinarySemaphore(RTRServerSemaphoreSet&, RTRBOOL initToOne = RTRFALSE);
		// New binary lock which allocates a new system semaphore
		// using the key of the given set and number allocated from the set.
		// If initToOne is RTRTRUE value will be initialized to one.
		// _TAG Constructor

	RTRBinarySemaphore(const char*, int semNum);
		// A new binary lock attached to an existing system semaphore.
		// _TAG Constructor

// Operations
	void obtain();
		// Acquire the lock, blocking until it is available.
        // _TAG01 Operations

	RTRBOOL tryObtain();
		// Acquire the lock if available. Non-blocking. Return RTRTRUE
		// if acquired.
        // _TAG01 Operations

	void release();
		// Release the lock acquired via obtain() or tryObtain()
        // _TAG01 Operations

}; 

#else

class RTRReadWriteLock
{
public:
// Constructor
	RTRReadWriteLock(RTRServerSemaphoreSet&, int maxReaders);
		// New read/write lock which allocates a new system semaphore
		// using the key of the given set and number allocated from the set.
		// _TAG Constructor
 
	RTRReadWriteLock(const char*, int semNumber, int maxReaders);
		// A new read/write lock attached to an existing system semaphore.
		// _TAG Constructor
 
// Destructor
	~RTRReadWriteLock();
		// _TAG Destructor
 
// Identity
	inline int number() const;
		// The number of this semaphore within the set identified by _id.
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
 
// Operations
	void obtainReadAccess();
		// Obtain permission for read-only access to the shared resource.
		// Blocking
		// _TAG04 Operations
 
	RTRBOOL tryObtainReadAccess();
		// Obtain permission for read-only access to the shared resource.
		// Non-blocking, returns RTRTRUE if access acquired
		// _TAG04 Operations
 
	void releaseReadAccess();
		// Release the read-permission acquired via a successful call to
		// obtainReadAccess() or tryObtainReadAccess()
		// _TAG04 Operations
 
	void obtainWriteAccess();
		// Obtain permission for write-only access to the shared resource.
		// Blocking
		// _TAG04 Operations
 
	RTRBOOL tryObtainWriteAccess();
		// Obtain permission for write-only access to the shared resource.
		// Non-blocking, returns RTRTRUE if access acquired
		// _TAG04 Operations
 
	void releaseWriteAccess();
		// Release the write-permission acquired via a successful call to
		// obtainWriteAccess() or tryObtainWriteAccess()
		// _TAG04 Operations
 
protected:
// Data
	int _maxReaders;
	HANDLE *_id;
	int _number;
	int _index;
	int _lastErrorNumber;
};
 
inline
int RTRReadWriteLock::number() const
{
	return _number;
}
 
inline
RTRBOOL RTRReadWriteLock::error() const
{
	return _lastErrorNumber != 0;
}
 
 
class RTRBinarySemaphore
{
public:
// Constructor
	RTRBinarySemaphore(RTRServerSemaphoreSet&, RTRBOOL initToOne = RTRFALSE);
		// New binary lock which allocates a new system semaphore
		// using the key of the given set and number allocated from the set.
		// If initToOne is RTRTRUE value will be initialized to one.
		// _TAG Constructor
 
	RTRBinarySemaphore(const char*, int semNum);
		// A new binary lock attached to an existing system semaphore.
		// _TAG Constructor
 
// Destructor
	~RTRBinarySemaphore();
 
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
 
// Operations
	void obtain();
		// Acquire the lock, blocking until it is available.
		// _TAG04 Operations
 
	RTRBOOL tryObtain();
		// Acquire the lock if available. Non-blocking. Return RTRTRUE
		// if acquired.
		// _TAG04 Operations
 
	void release();
		// Release the lock acquired via obtain() or tryObtain()
		// _TAG04 Operations
 
protected:
// Data
	HANDLE _id;
	int _number;
	int _lastErrorNumber;
		// Data
};
 
inline
HANDLE RTRBinarySemaphore::id() const
{
	return _id;
}
 
inline
int RTRBinarySemaphore::number() const
{
	return _number;
}
 
inline
RTRBOOL RTRBinarySemaphore::error() const
{
	return _lastErrorNumber != 0;
}
 
class RTRReadWriteLock_Eli : 
	public RTRSemaphore
{ 
public:
// Constructor
	RTRReadWriteLock_Eli(const char*, int semNumber, int maxReaders);
		// A new read/write lock attached to an existing system semaphore.
		// _TAG Constructor

// Operations
	void obtainReadAccess();
		// Obtain permission for read-only access to the shared resource.
		// Blocking
		// _TAG01 Operations

	RTRBOOL tryObtainReadAccess();
		// Obtain permission for read-only access to the shared resource.
		// Non-blocking, returns RTRTRUE if access acquired 
		// _TAG01 Operations

	void releaseReadAccess();
		// Release the read-permission acquired via a successful call to 
		// obtainReadAccess() or tryObtainReadAccess()
		// _TAG01 Operations

	void obtainWriteAccess();
		// Obtain permission for write-only access to the shared resource.
		// Blocking
		// _TAG01 Operations

	RTRBOOL tryObtainWriteAccess();
		// Obtain permission for write-only access to the shared resource.
		// Non-blocking, returns RTRTRUE if access acquired 
		// _TAG01 Operations

	void releaseWriteAccess();
		// Release the write-permission acquired via a successful call to 
		// obtainWriteAccess() or tryObtainWriteAccess()
		// _TAG01 Operations

protected:
// Data
	int _maxReaders;
}; 

// Synopsis:
// #include"rtr/semlock.h"
//
// Description:
// 	A descendant of RTRSemaphore whose value may only be 1 or 0. This lock
// 	may be obtained (blocking an non-blocking) and released. In the event
// 	of un-gracefull termination, an acquired lock will be released by the
// 	operating system.
//
// See Also:
// 	RTRServerSemaphoreSet, RTRReadWriteLock_Eli, RTRSemaphoreFlag
// 
// Inherits:
//	RTRSemaphore
//

class RTRBinarySemaphore_Eli : 
	public RTRSemaphore
{ 
public:
// Constructor
	RTRBinarySemaphore_Eli(
			const char*,
			int semNum
			);
		// A new binary lock attached to an existing system semaphore.
		// _TAG Constructor

// Operations
	void obtain();
		// Acquire the lock, blocking until it is available.
		// _TAG01 Operations

	RTRBOOL tryObtain();
		// Acquire the lock if available. Non-blocking. Return RTRTRUE
		// if acquired.
		// _TAG01 Operations

	void release();
		// Release the lock acquired via obtain() or tryObtain()
		// _TAG01 Operations
}; 

#endif


// Synopsis:
// #include"rtr/semlock.h"
//
// Description:
// 	A binary valued descendant of RTRSemaphore intended for hand-shaking
// 	betwen two processes, one of which raises the flag expecting it to be
// 	lowered by the other. In the event of un-gracefull termination, flag
// 	operations are NOT un-done by the operating system.
//
// See Also:
//	RTRReadWriteLock, RTRBinarySemaphore
// 
// Inherits:
//	RTRSemaphore
//

class RTRSemaphoreFlag : 
	public RTRSemaphore
{ 
public:
// Constructor
	RTRSemaphoreFlag(RTRServerSemaphoreSet&, RTRBOOL initUp = RTRFALSE);
		// New flag which allocates a new system semaphore
		// using the key of the given set and number allocated from the set.
		// If initUp is RTRTRUE then initialize the flag as up.
		// _TAG Constructor

	RTRSemaphoreFlag(const char *, int semNum);
		// A new semaphore flag attached to an existing system semaphore.
        // _TAG Constructor

// Operations
	void lower();
		// Lower the flag. If it is not up, block until it is.
        // _TAG01 Operations

	RTRBOOL tryLower();
		// Lower the flag if it is up. Non-blocking. Return RTRTRUE if
		// the flag was lowered.
        // _TAG01 Operations

	void raise();
		// Raise the flag so it can be lowered by another process.
        // _TAG01 Operations

}; 

#endif
