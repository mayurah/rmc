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

#ifndef __rtrcondvar_h
#define __rtrcondvar_h

#include "rtr/rtrcv.h"
class RTRPlatFlagThread;


// Synopsis:
// #include "rtr/rtrmutex.h"
//
// Description
// RTRPlatCondVar represents a condition variable which is used to synchronize threads
// whose executions are pending on particular conditions. When a thread is waiting
// for another thread to communicate its state, it uses a condition variable along with
// mutex. A condition variable may be used by threads to signal each other when
// a task is complete, which then allows the next waiting thread to take ownership
// of the mutex.
//
// A condition variable enables threads to atomically block and test the condition
// under the protection of a mutex until the condition is satisfied. If the condition
// is false, a thread blocks on a condition variable and atomically releases the
// mutex that is waiting for the condition to change. If another thread changes the
// condition, it may wake up waiting threads by signaling the associated condition
// variable. When the waiting threads awaken, they reacquire the mutex and re-evaluate
// the condition.
//
// Typical Usage:
// 
//     "//" RTRPlatCondVar cv;
//     ...
//          "first thread"
//         cv.lock();
//         while (condition_false)
//             cv.wait();
//         cv.unlock();
//     ...
//          "second thread"
//         cv.lock();
//         change_condition
//         cv.signal();
//         cv.unlock();
//
// Notice that when the signaling thread calls the signal() method it does it while
// holding the lock. This MUST always be the case.
//
// In order to force a blocking thread out of a condition variable wait the user
// must use platform specific handling. This is usually needed for thread shutdown.
// WindowsNT -
//             Set an event in the condition variable that the thread will block
//             on along with the condition variable. You can then signal that
//             event for force the wait() to return RTRFALSE.
// Posix/Solairs
//             Send a signal to the blocking thread to force the wait() to return
//             RTRFALSE.
//
// The class RTRPlatFlagThread incorporates this functionality in a generic way
// to properly flag threads. Note - you must call the setFlagThread() method
// with the appropriate RTRPlatFlagThread to setup the flag handling.
// The class RTRPlatHierThread incorporates this functionality in a generic way
// to properly flag/shutdown threads. Note - you must call the setFlagThread() method
// with the appropriate RTRPlatFlagThread to setup the flag handling.
//
//
// See Also:
// RTRPlatMutex, RTRPlatThread, RTRPlatFlagThread, RTRPlatHierThread
//
// Inherits:
//

#ifdef RTR_CV_INIT

class RTRPlatCondVar
{
public:

// Constructor
	RTRPlatCondVar();
		// _TAG Constructor

// Destructor
	virtual ~RTRPlatCondVar();
		// _TAG Destructor

// State
	inline RTRBOOL error()
		// Is the condition variable in a error state. If so the
		// condition variable is unusable.
		// _TAG01 State
	{
		return(_error);
	};

// Operations
	inline RTRBOOL wait()
		// The calling thread waits for a signal() event on this
		// condition variable and atomically releases the associated
		// mutex.
		// _TAG02 Operations
	{
		RTPRECONDITION(!error());
		rtr_cv_error err = 0;
		return(RTR_CV_WAIT(_condVar,err));
	};

	inline RTRBOOL wait(int seconds, int milliseconds)
		// The calling thread waits for a signal() event on this
		// condition variable and atomically releases the associated
		// mutex. This wait waits for `seconds' and `milliseconds'.
		// _TAG02 Operations
	{
		RTPRECONDITION(!error());
		rtr_cv_error err = 0;
		return(RTR_CV_TIMED_WAIT(_condVar,seconds,milliseconds,err));
	};

	inline RTRBOOL waitAbs(int seconds, int milliseconds)
		// The calling thread waits for a signal() event on this
		// condition variable and atomically releases the associated
		// mutex. This wait waits for the absolute system time of
		// `seconds' and `milliseconds'. Wait for the system time
		// to be seconds,milliseconds.
		// _TAG02 Operations
	{
		RTPRECONDITION(!error());
		rtr_cv_error err = 0;
		return(RTR_CV_TIMED_WAITABS(_condVar,seconds,milliseconds,err));
	};

	inline RTRBOOL signal()
		// Signal the condition variable to release one currently
		// waiting thread.
		// _TAG02 Operations
	{
		RTPRECONDITION(!error());
		rtr_cv_error err = 0;
		return(RTR_CV_SIGNAL(_condVar,err));
	};
	
	inline RTRBOOL signalall()
		// Signal the condition variable to release all currently
		// waiting threads
		// _TAG02 Operations
	{
		RTPRECONDITION(!error());
		rtr_cv_error err = 0;
		return(RTR_CV_SIGNALALL(_condVar,err));
	};

// Mutex Operations
	inline RTRBOOL lock()
		// Acquire the lock on the mutex.
		// Calling thread blocks until the
		// mutex becomes available.
		// Returns false when lock() operations fails.
		// _TAG03 Mutex Operations
	{
		RTPRECONDITION(!error());
		rtr_cv_error err = 0;
		return(RTR_CV_LOCK(_condVar,err));
	};

	inline RTRBOOL unlock()
		// Release the lock on the mutex.
		// Returns false when unlock() operation fails.
		// _TAG03 Mutex Operations
	{
		RTPRECONDITION(!error());
		rtr_cv_error err = 0;
		return(RTR_CV_UNLOCK(_condVar,err));
	};

	inline RTRBOOL trylock()
		// Attempt to acquire the lock on the mutex. If
		// the mutex is already locked return RTRFALSE.
		// _TAG03 Mutex Operations
	{
		RTPRECONDITION(!error());
		rtr_cv_error err = 0;
		return(RTR_CV_TRYLOCK(_condVar,err));
	};


// Helpers
	void setFlagThread(RTRPlatFlagThread&);
		// Setup the flagable thread for
		// this condition variable. Whenever
		// the thread is flagged(), this cv
		// must return from a wait() with RTRFALSE.
		// _TAG04 Helpers

#ifdef _WIN32
	inline RTRBOOL setFlagHandle(HANDLE flagEvent)
		// Setup a flag events handle. When
		// a thread wait()'s on a condition variable,
		// it can also wait of a flagEvent event
		// in order to force the wait to return
		// RTRFALSE.
		// _TAG04 Helpers
	{
		return(RTR_CV_SET_FLAG(_condVar,flagEvent));
	};
#endif


protected:

	RTRBOOL			_error;
	rtr_cond_var	_condVar;

};

#endif

#endif
