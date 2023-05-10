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

#ifndef _condvar_h
#define _condvar_h

#include "rtr/synch.h"

#ifdef MULTI_THREAD_SUPPORTED

#include "rtr/rtstring.h"

// Synopsis:
// #include "rtr/condvar.h" 
//
// Description:
// RTRConditionVariable is used to synchronize threads whose executions are 
// pending on a particular condition.
//
// RTRConditionVariable has two modes, namely singler and broadcast.
//
// If constructed with the flag broadcast set to be false, an instance of this 
// will operate in the singler mode: a signal() call will release zero 
// to one thread that is blocked on this condition, then reset itself to the 
// non-signaled state, i.e., the thread that calls wait() after signal() sees 
// a non-signaled condition;
// On the other hand, the setSignaled() call will change the state to be 
// signaled and remain so until a thread is released, or setNonsignaled()
// is called. 
//
// If constructed in a broadcast mode, the broadcast() call will release all 
// threads that are currently blocked on this condition, then reset itself to 
// non-signaled state; Similarly, the setSingaled() call will change the state 
// to signaled and remain so, to release all current and subsequent waiting 
// threads until setNonsignaled() is called explicitly to reset the state.
//
// The RTRConditionVariable also provides an internal mutex lock to help 
// synchronizing the resource (condition) change. The typical usuage is like 
// this:
//
//     "//"RTRConditionVariable cv;
//     ...
//          "//" one thread:
//         cv.lock();
//             change_condition;
//         cv.signal();
//         cv.unlock();
//     ...
//         "//" another thread:
//         cv.lock();
//         while (condition_is_false)
//             cv.wait();
//         cv.unlock();
//
// Notice that when lock is used, all waiting threads are competing for the 
// same mutex, and only one thread will be unblocked at a time. Thus, the 
// broadcast() is equalvalent to signal(). Using setSingaled() might be useful 
// to really wake up all blocking threads.
//
// Also notice that, if state operations such as setSignaled() are used for 
// this class, the use of associate mutex lock is mandantory, since the 
// changes/queries of _signaled are synchronized via it.
//
// See Also:
//    RTRMutex
//

class RTRConditionVariable
{ 
public:
// Constructor
	RTRConditionVariable(RTRBOOL broadcast = RTRFALSE,
						RTRBOOL initSignaled = RTRFALSE);
		// _TAG Constructor

// Destructor
	~RTRConditionVariable();
		// _TAG Destructor

// Operations
	void signal() ;
		// Send signal to release one currently waiting thread
		// it is a stateless operation, i.e. its state remains non-signaled 
		// _TAG01 Operations

	void broadcast() ;
		// send signal to all currently waiting threads, may release only one
		// of them if they are competing for the mutex lock.
		// it is a stateless operation, i.e. its state reamins non-signaled 
		// _TAG01 Operations

	void setSignaled() ;
		// change _signaled to RTRTRUE and signal/broadcast to waiting threads
		// The state remains until either one thread is released when 
		// broadcastMode() = RTRFALSE;  or setNonsignaled() is called 
		// _TAG01 Operations

	void setNonsignaled();
		// Reset state to non-signaled
		// Primarily for use when  broadcastMode() == RTRTRUE; ( When 
		// broadcastMode() == RTRFALSE, the first released thread will
		// change its state automatically)
		// _TAG01 Operations

	void wait() ;
		// Wait until this is signaled by signal(), setSignaled() or 
		// broadcast() call in other thread; Blocking 
		// _TAG01 Operations

	int timedwaitAbs(long sec,long usec) ;
		// Wait until this is signaled or time expires
		// The arguments are absolute time, i.e. CURRENT_TIME+WAIT_INTVAL 
		// Since for Solaris, the underline syscall uses absolute time,.
		// Use this to save unnecessary system calls
		// _TAG01 Operations

	int timedwaitIntvl(long sec,long usec) ;
		// Wait until this is signaled or time expires
		// The arguments are values of the waiting interval
		// For NT, it can save unnecessary system calls
		// _TAG01 Operations

// State 
	inline RTRBOOL isSignaled() const { return _signaled;};
		// Is this in a signaled state ?
		// Note: only an estimation and meaningful when you know what it 
		// means, e.g., in class RTRCallBackLockableObj 
		// _TAG02 State

// Helper 
	void lock();
		// Used to keep the integrity of condition while waiting since 
		// condition might be changed before wait() returns 
		// _TAG03 Helper

	int tryLock();
		// Returns RTRLockSuccess if a lock is acquired.
		// _TAG03 Helper

	void unlock();
		// _TAG03 Helper

// Attributes
	inline RTRBOOL broadcastMode() {return  _broadcastMode;};
		// _TAG04 Attributes

// Static date
	static RTRBOOL debugEnabled;
		// Set true to report possible deadlock 
		// _TAG05 Static date

	static RTRBOOL deadlockCore;
		// core at the place where deadlock might happen
		// _TAG05 Static date

	static int tryLockMillSec;
		// when debugEnabled is true, trylock() instead of lock() is actually 
		// called for this amount of millsec
		// _TAG05 Static date
		
protected:
	RTRCondVarType _condvar;
	RTRMutexType _condmtx;
	RTRBOOL _broadcastMode;
	RTRBOOL _signaled;
}; 

#else
class RTRConditionVariable
{
public:
	RTRConditionVariable(){};
	~RTRConditionVariable(){};
	inline void signal() {};
	inline void broadcast() {};
	inline void setSignaled() {};
	inline void setNonsignaled() {};
	inline void wait() {};
	inline int timedwaitAbs(long ,long ) { return RTRLockSuccess;};
	inline int timedwaitIntvl(long ,long ) {return RTRLockSuccess;};
	inline RTRBOOL isSignaled() const { return RTRTRUE;};
	inline void lock() {};
	inline int tryLock() {};
	inline void unlock() {};
	RTRBOOL broadcastMode() {return  RTRTRUE;};
	static RTRBOOL deadlockCore;
	static RTRBOOL debugEnabled;
	static int tryLockMillSec;
};
#endif // Empty def when MT not supported/disabled


#endif
