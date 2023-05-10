//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  Author:        Robert Bonaguro
//  Created:       April 7, 1997
//  Version:       1.0
//

#ifndef __rtr_thread_h
#define __rtr_thread_h

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif
#include "rtr/rtrthrd.h"
#include "rtr/rtratomic.h"

#ifdef RTR_THREAD_CREATE

//
// Synopsis:
// #include "rtr/rtrthread.h"
//
// Description:
// RTRPlatThread is an abstract base class representing a thread object in a
// process. The pure virtual function runThread() must be declared in its
// descendent class to serve as the main execution unit in the thread.
//
// Once class that is-a RTRPlatThread has been instantiated, the start()
// method must be used to actually start the new thread running. This can
// be verified through the hasStartedRunning() state.
//
// In order to set thread attributes, they must be set before before the
// start() method is invoked.
//
// If another thread wants to wait for this thread to exit, it can invoke
// the join() method.
//
// See Also:
// RTRPlatFlagThread, RTRPlatHierThread
//

class RTRPlatThread
{
public:

// Output
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&,RTRPlatThread&);
#else
	void print(FILE*);
#endif
// Constructor
	RTRPlatThread(const char *nm);
		// _TAG Constructor

// Destructor
	virtual ~RTRPlatThread();
		// _TAG Destructor

// Identity
	inline rtr_thread_id threadId()
		// _TAG01 Identity
		// REQUIRE : isAlive()
	{
		RTPRECONDITION(isAlive());
		return(_thread_info.thread_id);
	};

	inline const char *name()		{ return(_name); };
		// _TAG01 Identity

	inline RTRBOOL isThisThread()
		// _TAG01 Identity
		// REQUIRE : isAlive()
		// Is the thread calling this method the same
		// thread this class is running?
	{
		RTPRECONDITION(isAlive());
		return(currentThreadId() == _thread_info.thread_id);
	};

// State
	inline RTRBOOL isAlive()		{ return(_is_alive); };
		// _TAG02 State

	inline RTRBOOL isSuspended()	{ return(_is_suspended); };
		// _TAG02 State

	inline RTRBOOL hasStartedRunning()	{ return(_has_started_running); };
		// As soon as the thread starts running
		// for the first time this will be set.
		// If the thread has been created but has
		// not started running, then set to false.
		// _TAG02 State


// Start Attributes
	inline void setBound()			{ RTR_SET_THR_BOUND(&_thread_info); };
		// REQUIRE : !isAlive()
		// _TAG03 Start Attributes

	inline void setStack(void *base, rtr_stack_sz sz)
									{ RTR_SET_STACK(&_thread_info,base,sz); };
		// REQUIRE : !isAlive()
		// _TAG03 Start Attributes

#ifdef RTR_SET_THR_DETACHED
	inline void setDetached()		{ RTR_SET_THR_DETACHED(&_thread_info); };
		// REQUIRE : !isAlive()
		// _TAG03 Start Attributes
#endif

#ifdef RTR_SET_THR_SUSPENDED
	inline void setSuspended()		{ RTR_SET_THR_SUSPENDED(&_thread_info);
										_is_suspended = 1; };
		// REQUIRE : !isAlive()
		// _TAG03 Start Attributes
#endif

#ifdef RTR_SET_THR_NEW_LWP
	inline void setNewLwp()			{ RTR_SET_THR_NEW_LWP(&_thread_info); };
		// REQUIRE : !isAlive()
		// _TAG03 Start Attributes
#endif

#ifdef RTR_SET_THR_DAEMON
	inline void setDaemon()			{ RTR_SET_THR_DAEMON(&_thread_info); };
		// REQUIRE : !isAlive()
		// _TAG03 Start Attributes
#endif


// Thread Control
	RTRBOOL start(rtr_thr_err *sys_error_code=0);
		// Called to start the thread.
		// REQUIRE : !isAlive()
		// ENSURE : (isAlive() && !isSuspended) || error()
		// _TAG04 Thread Control

	RTRBOOL join(rtr_thr_err *sys_error_code=0);
		// Wait for this thread to die
		// REQUIRE : !isThisThread()
		// _TAG04 Thread Control

	inline void yield() {RTR_THREAD_YIELD(); };
	inline void yield(int millisec) { RTR_THREAD_TIMEYIELD(millisec); };

	RTRBOOL setThreadName(const char* name, rtr_thr_err *sys_error_code=0);
		// Called to set the thread name which appears in top
		// max length can be 16 including the '\0'
		// REQUIRE : currentThreadId() == threadId()
		// ENSURE : currentThreadId() == threadId())
		
#ifdef RTR_THREAD_SUSPEND
	RTRBOOL suspend(rtr_thr_err *sys_error_code=0);
		// Called to suspend this thread
		// REQUIRE : isAlive() && !isSuspended()
		// ENSURE : (isAlive() && isSuspended) || error()
		// _TAG04 Thread Control
#endif

#ifdef RTR_THREAD_CONTINUE
	RTRBOOL resume(rtr_thr_err *sys_error_code=0);
		// Called to resume a suspended thread
		// REQUIRE : isAlive() && !isSuspended()
		// ENSURE : (isAlive() && !isSuspended) || error()
		// _TAG04 Thread Control
#endif

#ifdef RTR_GET_THREAD_PRI
	RTRBOOL getPriority(rtr_thr_pri *pri,rtr_thr_err *sys_error_code=0);
		// Get the thread priority
		// _TAG04 Thread Control
#endif

#ifdef RTR_SET_THREAD_PRI
	RTRBOOL setPriority(rtr_thr_pri pri,rtr_thr_err *sys_error_code=0);
		// Set the thread priority
		// _TAG04 Thread Control
#endif


// Static Methods
	static rtr_thread_id currentThreadId();
		// return the calling thread id
		// _TAGXX Static Methods

protected:

	void Exit();
		// REQUIRE : currentThreadId() == threadId()
		// Exit this thread while running


// Scheduler Class Control
#ifdef RTR_SCHED_REAL_TIME
	RTRBOOL setSchedRealTime(rtr_thr_pri pri,rtr_thr_err *sys_error_code=0);
		// REQUIRE : isAlive()
		// REQUIRE : isThisThread()
#endif

#ifdef RTR_SCHED_SYSTEM
	RTRBOOL setSchedSystem(rtr_thr_pri pri,rtr_thr_err *sys_error_code=0);
		// REQUIRE : isAlive()
		// REQUIRE : isThisThread()
#endif

#ifdef RTR_SCHED_TIMESHARE
	RTRBOOL setSchedTimeShare(rtr_thr_pri pri,rtr_thr_err *sys_error_code=0);
		// REQUIRE : isAlive()
		// REQUIRE : isThisThread()
#endif

	static RTR_THREAD_START_FUNC(startWrapper,arg);


// Override functions
	virtual void runThread() = 0;
		// REQUIRE : isThisThread()
		// descendent class define to provide main function of thread


// Data Members
	rtr_atomic_val			_is_alive;
	rtr_atomic_val			_flag_recieved;
	char				_name[64];
	rtr_thread_info		_thread_info;
	int					_is_suspended;
	int					_has_started_running;


	virtual void privateThreadInit();
		// This is thread implementation specific. Do not overwrite
		// for normal thread usage.

};

#endif

#endif
