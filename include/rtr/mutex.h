//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T.L. Zhang
// Created: "Apr. 16 1996"
// Version: 1.0
//

#ifndef _mutex_h
#define _mutex_h


#include "rtr/synch.h"

#if defined(MULTI_THREAD_SUPPORTED) 
	// a platform dependent flag decided in "rtr/synch.h"

// Synopsis:
// #include "rtr/mutex.h" 
//
// Description:
// RTRMutex represents a mutual exclusion lock used to ensure that only one 
// thread can access a resource or execute a critical section of code at a time
//
// Note:
// Since the lock()/unlock() functions are inlined for performance reasons, 
// the function calls can no longer be switched between dummy implementations 
// and actual system calls by linking to different thread libraries.
// The user should use RTRLockableObj instead if they want this type of 
// flexibility in their library.
//

class RTRMutex
{ 
public:
// Constructor
	RTRMutex();
		// _TAG Constructor

// Destructor
	~RTRMutex();
		// _TAG Destructor

// Operations
	inline RTRBOOL lock() ;
		// acquire lock on this. 
		// calling thread blocks until the mutex becomes available
		// return RTRFALSE if the underline system call fails
		// _TAG01 Operations

	RTRLockState trylock(int msec = 0) ;
		// a non-blocking call by default. 
		// If the argument given is greater than zero, calling thread will 
		// try acquiring lock for that many millseconds.
		// return RTRLockTimeout if lock is not granted when time expires. 
		// _TAG01 Operations

	inline RTRBOOL unlock() ;
		// Release lock on this.
		// return RTRFALSE if the caller is not the owner of this mutex
		// _TAG01 Operations

// State
	inline RTRBOOL locked() { return _lockedLevel==0 ? RTRFALSE:RTRTRUE; };
		// Is this in a locked state?
		// Note: only valid when calling thread is the owner of the lock
		// _TAG02 Operations
		
	inline int lockedLevel() { return _lockedLevel; };
		// How many times the lock() has been called by this owner thread
		// Note: valid only when calling thread owns the lock
		// _TAG02 Operations

protected:
	int _lockedLevel;	
	RTRMutexType _mutex;
}; 

#if defined(DEV_POS_THR)
inline RTRBOOL RTRMutex::lock()
{
	int ret = pthread_mutex_lock(&_mutex);
	_lockedLevel++;
	return ret == 0 ? RTRTRUE : RTRFALSE;
}

inline RTRBOOL RTRMutex::unlock()
{
	_lockedLevel--;
	return pthread_mutex_unlock(&_mutex) == 0 ? RTRTRUE : RTRFALSE;
}

// Synopsis:
// #include"rtr/mutex.h"
//
// Description:
// RTRReentMutex is-a RTRMutex. For platforms that don't support recursive 
// locking (i.e., a thread can acquire same lock more than once), such as 
// Solaris, RTRReentMutex could be used to avoid potential deadlock.  
//
// The WIN32 mutexes are already capable of recursive locking, so, normally 
// using RTRMutex is sufficient.  RTRReentMutex is just a typedef and useful 
// when platform independent syntax is needed.
//
// See Also:
//	RTRMutex
//
// Inherits:
//  RTRMutex

class RTRReentMutex : public RTRMutex
{
public:
// Constructor
	RTRReentMutex();
		// _TAG Constructor

// Destructor
	~RTRReentMutex();
		// _TAG Destructor

// Operations
	RTRBOOL lock();
		// Acquire lock on this if it is not locked yet; Increase the 
		// _lockedLevel if the calling thread has already got the lock;
		// Otherwise, block until other thread realeases the lock 
		// _TAG01 Operations

	RTRLockState trylock(int msec = 0);
		// Attempt to lock the mutex for period of msec millseconds 
		// Return RTRLockTimeout if lock is not granted within that time  
		// _TAG01 Operations

	RTRBOOL unlock();
		// Release the lock or decrement the _lockedLevel by one if the
		// lock has been locked by same thread for more than once.
		// The calling thread must be the owner of this lock, otherwise
		// it returns RTRFALSE. 
		// _TAG01 Operations

protected:
	RTRThreadId _ownerId;
	RTRMutexType _stateLock;
		// used to synchronize the operations on _lockedLevel and _ownerId 
};

#elif defined(SOLARIS2)

inline RTRBOOL RTRMutex::lock()  
{
	int ret = mutex_lock(&_mutex);
	_lockedLevel++;
	return ret == 0 ? RTRTRUE:RTRFALSE;
}

inline RTRBOOL RTRMutex::unlock() 
{
	_lockedLevel--;
	return mutex_unlock(&_mutex) == 0 ? RTRTRUE: RTRFALSE;
}

// Synopsis:
// #include"rtr/mutex.h"
//
// Description:
// RTRReentMutex is-a RTRMutex. For platforms that don't support recursive 
// locking (i.e., a thread can acquire same lock more than once), such as 
// Solaris, RTRReentMutex could be used to avoid potential deadlock.  
//
// The WIN32 mutexes are already capable of recursive locking, so, normally 
// using RTRMutex is sufficient.  RTRReentMutex is just a typedef and useful 
// when platform independent syntax is needed.
//
// See Also:
//	RTRMutex
//
// Inherits:
//  RTRMutex

class RTRReentMutex : public RTRMutex
{
public:
// Constructor
	RTRReentMutex();
		// _TAG Constructor

// Destructor
	~RTRReentMutex();
		// _TAG Destructor

// Operations
	RTRBOOL lock();
		// Acquire lock on this if it is not locked yet; Increase the 
		// _lockedLevel if the calling thread has already got the lock;
		// Otherwise, block until other thread realeases the lock 
		// _TAG01 Operations

	RTRLockState trylock(int msec = 0);
		// Attempt to lock the mutex for period of msec millseconds 
		// Return RTRLockTimeout if lock is not granted within that time  
		// _TAG01 Operations

	RTRBOOL unlock();
		// Release the lock or decrement the _lockedLevel by one if the
		// lock has been locked by same thread for more than once.
		// The calling thread must be the owner of this lock, otherwise
		// it returns RTRFALSE. 
		// _TAG01 Operations

protected:
	RTRThreadId _ownerId;
	RTRMutexType _stateLock;
		// used to synchronize the operations on _lockedLevel and _ownerId 
};

#elif defined(_WIN32)

inline RTRBOOL RTRMutex::lock()  
{
	EnterCriticalSection(&_mutex);
	_lockedLevel++;
	return RTRTRUE;
}

inline RTRBOOL RTRMutex::unlock() 
{
	_lockedLevel--;
	RTRBOOL error = _lockedLevel>=0 ? RTRTRUE : RTRFALSE;
	LeaveCriticalSection(&_mutex);
	return error;
}

typedef RTRMutex RTRReentMutex ;

#elif defined(OS2)

inline RTRBOOL RTRMutex::lock()  
{
	APIRET rc = DosRequestMutexSem( _mutex, SEM_INDEFINITE_WAIT );
	_lockedLevel++;
	return rc==0 ? RTRTRUE: RTRFALSE;
}

inline RTRBOOL RTRMutex::unlock() 
{
	_lockedLevel--;
	return((DosReleaseMutexSem(_mutex) == 0) ? RTRFALSE: RTRTRUE);
}


typedef RTRMutex RTRReentMutex ;

#endif // for platform specific inline functions

// Synopsis:
// #include"rtr/mutex.h"
//
// Description:
// An instance of RTRGuard locks an instance of RTRMutex passed as an argument
// on construction, and release the lock when it gets deleted. Typically, it is 
// allocated on stack, therefore its destructor will be called automatically 
// when it is out of scope in the program. 
//
// See Also:
//	RTRMutex

class RTRGuard {
public:
// Constructor
	inline RTRGuard(RTRMutex& m) : _rtrmutex(m) {_rtrmutex.lock();};
		// On construction, acquire the lock 
		// _TAG Constructor

// Destructor
	inline ~RTRGuard() {_rtrmutex.unlock();};
		// On destruction, release the lock 
		// _TAG Destructor
protected:
RTRMutex& _rtrmutex;
};

// Synopsis:
// #include"rtr/mutex.h"
//
// Description:
// An instance of RTRReentGuard locks an instance of RTRReentMutex passed as 
// an argument on construction, and release the lock when it gets deleted. 
// Typically, it is allocated on stack, therefore destructor will be called 
// automatically when it is out of scope in program.
//
// See Also:
//	RTRGuard, RTRReentMutex

class RTRReentGuard {
public:
// Constructor
	inline RTRReentGuard(RTRReentMutex& m) : _rtrmutex(m) {_rtrmutex.lock();};
		// On construction, acquire the lock 
		// _TAG Constructor

// Destructor
	inline ~RTRReentGuard() {_rtrmutex.unlock();};
		// On destruction, release the lock 
		// _TAG Destructor
protected:
	RTRReentMutex& _rtrmutex;
};


#else // define classes with no-op methods and size of 0
class RTRMutex
{ 
public:
	inline RTRMutex(){};
	inline ~RTRMutex(){};
	inline RTRBOOL lock() { return RTRTRUE;};
	inline RTRLockState trylock(int = 0){ return RTRLockSuccess;};
	inline RTRBOOL unlock(){return RTRTRUE;};
	inline RTRBOOL locked() { return RTRTRUE; };
}; 

typedef RTRMutex RTRReentMutex ;

class RTRGuard {
public:
	inline RTRGuard(RTRMutex& ){};
	inline ~RTRGuard(){};
};

typedef RTRGuard RTRReentGuard ;

#endif // MULTI_THREAD_SUPPORTED 

#endif //  _mutex_h
