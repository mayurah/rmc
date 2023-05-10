//
//|---------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  Author:        Robert Bonaguro
//  Created:       April 29, 1997
//  Version:       1.0
//

#ifndef __rtrmutex_h
#define __rtrmutex_h

#include "rtr/rtrmutx.h"

// Synopsis:
// #include "rtr/rtrmutex.h"
//
// Description
// RTRPlatMutex represents a mutual exclusion lock used to ensure that only one
// thread can access a resource or execute a critical section of code at one
// time. The implementation has been inlined for performance reasons.
//
// See Also:
//
// Inherits:
//

class RTRPlatMutex
{
public:

// Constructor
	RTRPlatMutex();
		// _TAG Constructor

	RTRPlatMutex(int attribute);

// Destructor
	virtual ~RTRPlatMutex();
		// _TAG Destructor

// State
	inline RTRBOOL error()
		// Is the mutex in a error state. If so the
		// mutex is unusable.
		// _TAG01 State
	{
		return(_error);
	};

// Operations
	inline RTRBOOL lock()
		// Acquire the lock on the mutex.
		// Calling thread blocks until the
		// mutex becomes available.
		// Returns false when lock() operations fails.
		// _TAG02 Operations
	{
		RTPRECONDITION(!error());
		rtr_mutex_error err = 0;
		return(RTR_MUTEX_LOCK(_mutex,err));
	};

	inline RTRBOOL unlock()
		// Release the lock on the mutex.
		// Returns false when unlock() operation fails.
		// _TAG02 Operations
	{
		RTPRECONDITION(!error());
		rtr_mutex_error err = 0;
		return(RTR_MUTEX_UNLOCK(_mutex,err));
	};

	inline RTRBOOL trylock()
		// Attempt to acquire the lock on the mutex. If
		// the mutex is already locked return RTRFALSE.
		// _TAG02 Operations
	{
		RTPRECONDITION(!error());
		rtr_mutex_error err = 0;
		return(RTR_MUTEX_TRYLOCK(_mutex,err));
	};


protected:

	RTRBOOL		_error;
	rtr_mutex	_mutex;

};

// The guard class takes the mutex as an argument and locks it when the class
// object is instantiated and unlocks it when the object is destroyed. This
// reduces the chance for deadlock as the lock is always released at the end of // the function.  
class RTRMutexGuard
{
    RTRPlatMutex *_mutex;
public:
    RTRMutexGuard(RTRPlatMutex *mutex) : _mutex(mutex) { if (_mutex) _mutex->lock(); }
    ~RTRMutexGuard() { if (_mutex) _mutex->unlock(); }
};


#endif
