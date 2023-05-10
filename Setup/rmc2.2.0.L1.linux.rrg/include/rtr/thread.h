//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T.L. Zhang
// Created: "Jul. 11 1996"
// Version: 1.0

#ifndef _thread_h
#define _thread_h

#include "rtr/synch.h"

#ifdef MULTI_THREAD_SUPPORTED

#include "rtr/mtgc.h"
#include "rtr/rtllist.h"
#include "rtr/rtstring.h"

#ifdef OS2
#undef sleep
#endif

class RTRThreadMgr;

//
// Synopsis:
// #include "rtr/thread.h"
//
// Description:
// RTRThread is an abstract base class representing a thread object in a 
// process. The pure virtual function run() must be overidden in 
// descendent classes to serve as the main execution unit in a thread.
// Its public interface can be divided into three categories:
//
// \bullet
//	o Methods that return the state/attribute of the thread object, such as
//    isSuspended()...
//	o Methods that control the thread execution, such as start(), suspend()...
//    These methods should be called from another thread.
//	o Static methods, that are executed in calling thread, such as sleep()...
// \endbullet
//
// See Also:
//	RTRThreadMgr, RTRGCThread
//

class RTRThread
{ 
public:
	enum ExitStatus {
			abnormal = -1,
			normal ,
			exit_inside_run ,
			interrupt_by_stop};

// Destructor
	virtual ~RTRThread();
		// _TAG Destructor

// Identity
	inline RTRThreadId id() { return _id; };
		// _TAG01 Identity

	inline RTRString name() { return _name; };
		// _TAG01 Identity
		 
// Attributes
	inline RTRThreadMgr & threadMgr() const { return _threadMgr; }; 
		// _TAG02 Attributes
	 
// State
	RTRBOOL isAlive() ;
		// _TAG03 State
						   
	inline RTRBOOL isSuspended() { return _suspended; };
		// _TAG03 State

	inline int error() { return _error; };
		// _TAG03 State

// Operations -- Thread Attributes
	inline void setStackSize(int bytes) { _stackSize = bytes; };
		// A default of 0 is used if not called.
		// _TAG04 Operations -- Thread Attributes

	inline void setSuspended(RTRBOOL suspended ) { _suspended = suspended; };
		// A default of RTRFALSE is used if not called.
		// _TAG04 Operations -- Thread Attributes

#if defined(DEV_POS_THR)
	void setAttributes(int priority = 0,
				   	   RTRBOOL bound = RTRFALSE,
					   RTRBOOL detached = RTRFALSE);
		// Sets flags that only apply to POSIX
		// _TAG04 Operations -- Thread Attributes
#elif defined(SOLARIS2)
	void setFlags(RTRBOOL detached=RTRFALSE,
				  RTRBOOL bound = RTRFALSE,
				  RTRBOOL newLwp = RTRFALSE,
				  RTRBOOL daemon = RTRFALSE);
		// Sets flags that only apply to SOLARIS
		// _TAG04 Operations -- Thread Attributes
#endif

// Operations -- Thread Execution
	int start();
		// Called to start this thread.
		// REQUIRE : !isAlive()
		// ENSURE : isAlive() || error()
		// _TAG05 Operations -- Thread Execution

	virtual RTRBOOL notify(int) { return RTRFALSE; };
		// Called to send an event to this thread's main loop. 
		// Decendent classes overide this and run() member functions to
		// establish signal/wait relationships.  Possibly use a condition 
		// variable.
		// REQUIRE : isAlive()
		// _TAG05 Operations -- Thread Execution

	RTRBOOL stop();
		// Called to stop this thread.
		// REQUIRE currentThreadId() != _id;
		// ENSURE : !isAlive() || error()
		// _TAG05 Operations -- Thread Execution

	RTRBOOL suspend();
		// Called to suspend this thread.
		// REQUIRE : isAlive() && !isSuspended()
		// ENSURE : isSuspended() || error()
		// _TAG05 Operations -- Thread Execution

	RTRBOOL resume();
		// Called to resume this thread.
		// REQUIRE : isAlive() && isSuspended()
		// ENSURE : !isSuspended() || error()
		// _TAG05 Operations -- Thread Execution
	
	int join();
		// Waiting for this thread to die.
		// REQUIRE: currentThreadId() != _id
		// ENSURE : !isAlive() || error()
		// _TAG05 Operations -- Thread Execution

	int getPriority();
		// Returns priority level if operation is successful.
		// Return -1 if failed on SOLARIS2, 
		// return THREAD_PRIORITY_ERROR_RETURN if failed for WindowsNT.
		// _TAG05 Operations -- Thread Execution

	RTRBOOL setPriority(int);
		// Returns RTRTRUE if operation is successful.
		// _TAG05 Operations -- Thread Execution

// Static Methods
	static void sleep(long sec, long millsec);
		// Sleep while in run().
		// _TAG06 Static Methods

	static void yield();
		// Yield to other threads while in run().
		// _TAG06 Static Methods

	static RTRThreadId currentThreadId();
		// Returns the calling thread id.
		// _TAG06 Static Methods

	static int getCurrentPriority();
		// Returns the calling thread priority.
		// _TAG06 Static Methods

	static RTRBOOL setCurrentPriority(int);
		// Set the calling thread's priority.
		// _TAG06 Static Methods

// Default RTRThreadMgr 
	static RTRThreadMgr dfltThreadMgr;
		// The default manater for an RTRThread object which is not given a
		// specified instance of RTRThreadMgr in its constructor.

protected:
// Overide functions 
	virtual void run() = 0;
		// Decendent class defines it to provide main function in thread.

	virtual void exitInstance();
		// Called at the end of thread execution or when creating thread
		// fails, to unregister with mgr and set states.

	virtual void initInstance();
		// called before create thread in start()
		// to register with mgr and set states

// Constructor
	RTRThread(RTRThreadMgr&, const char* nm ="");
		// Create a thread belonged to this manager, name is optional
		// Can't instantiate directly, derive a descendent class from this
		// _TAG Constructor

	RTRThread(const char* nm = "");
		// thread belongs to default global group managed by dfltThreadMgr
		// _TAG Constructor

	void exit();
		// ENSURE currentThreadId() == _id;
		// exit this thread while run() 

	static RTRThrdFuncRetType threadFuncWrapper(void*) ;
		// The real starting point for thread execution


// Data 
	RTRThreadMgr & _threadMgr;
	RTRString _name;
	RTRThreadId _id;
	int _error;
	int _stackSize;
	RTRBOOL _suspended;
	int _exitStatus;
#if defined(DEV_POS_THR)
	RTRThreadAttributeObject _attributes;
	int _priority;
	RTRBOOL _bound;
	RTRBOOL _detached;
#elif defined(_WIN32)
	HANDLE _handle;
#elif defined(SOLARIS2)
	RTRBOOL _detached;
	RTRBOOL _daemon;
	RTRBOOL _bound;
	RTRBOOL _newLwp;
#endif

//Friends
friend class RTRThreadMgr;

private:
// Don't implement
	RTRThread(const RTRThread& );
	RTRThread& operator=(const RTRThread& );
}; 

//
// RTRGCThread
//
// Synopsis:
// #include "rtr/thread.h"
//
// Description:
// A descendent of the base class RTRThread and RTRMTGCObj. An instance of 
// RTRGCThread won't be deleted being while thread is still executing.
// It does so by keeping a smart pointer to itself while executing run()
//
// See Also:
//  RTRThread, RTRThreadMgr, RTRMTGCObj
// 
// Inherits:
//	RTRThread, RTRMTGCObj, RTRMutex


class RTRGCThread :
	public RTRThread,
	public RTRMTGCObj
{
public:
	~RTRGCThread();

protected:
	RTRGCThread(const char* nm="")
		:RTRThread(nm),_keepRunningPtr(0){};

	RTRGCThread(RTRThreadMgr& m,const char* nm="")
		:RTRThread(m,nm),_keepRunningPtr(0){};

	void initInstance();

	void exitInstance();

	void* _keepRunningPtr;
		// Can't declare RTRGCThreadPtr here, oc compiler doesn't like that
};

typedef RTRObjRef<RTRGCThread> RTRGCThreadPtr;


class RTRThreadMgrIterator;
//
// RTRThreadMgr
//
// Synopsis:
// #include "rtr/thread.h"
//
// Description:
// An instance of RTRThreadMgr manages a pool of thread objects that register 
// with it. The control of multiple threads is made easier via the 
// RTRThreadMgr's public methods. For example, joinMultiple() can block until 
// all threads that the calling thread is waiting for are finished.
// 
// By default, all RTRThread objects will register with a static RTRThreadMgr
// instance.  Applications can create their own RTRThreadMgr instance and pass 
// it in the constructors of RTRThread. In this way, control of specific 
// groups of RTRThread objects is made possible.
//
// See Also:
//	RTRThread, RTRGCThread

class RTRThreadMgr
{
public:
// Constructor
	RTRThreadMgr(const char* nm = ""):_name(nm){};
		// The name can be provided for identity
		// _TAG Constructor

// Destructor
	virtual ~RTRThreadMgr();
		// _TAG Destructor

// Identity
	inline RTRString name() { return _name;};
		// _TAG01 Identity

// State
	int activeThreadCount();
		// An estimate of threads that are running
		// _TAG03 State

// Query 
	RTRThread* threadById(RTRThreadId);
		// the thread obj managed by this mgr
		// return null if it couldn't be found from this manager (could be
		// an invalid id or the thread has already unregistered).
		// _TAG04 Query

	RTRThread* threadByName(const char*);
		// the thread obj managed by this mgr
		// _TAG04 Query

#if defined(SOLARIS2)
// Concurrency
	static void setConcurrency(int);
		// Set the desired amount of thread concurrency.
		// _TAG05 Concurrency
	
	static int getConcurrency();
		// Get the current amount of desired thread concurrency.
		// _TAG05 Concurrency
#endif

// Operations 
	RTRBOOL notifyAll(int signal);
		// send (user-defined) signal to all threads that are managed by this.
		// the implementation thread class takes responsibility to define 
		// action w.r.t. the signal in virtual function notify() 
		// return RTRTRUE if success for all 
		// _TAG07 Operations

	RTRBOOL stopAll();
		// Cause all managed threads to terminate.
		// return RTRTRUE if success for all 
		// The manager will unregister its threads gracefully, unless the 
		// calling thread is also registered here (not right in the first
		// place)
		// Warning: since the targeted threads have no chance to execute 
		// user-mode code, so, it might leave a lock unreleased, etc. 
		// _TAG07 Operations

	RTRBOOL resumeAll();
		// resume running for all threads that are registered here
		// (with suspended state)
		// _TAG07 Operations

	RTRBOOL suspendAll();
		// suspend all threads that are managed by this and are running 
		// _TAG07 Operations

	RTRBOOL joinAll();
		// wait for all threads that are registered here to finish execution
		// Warning: deadlock if calling thread is also managed here
		// _TAG07 Operations

	RTRThreadId joinMultiple(int num,RTRThreadId* arr,RTRBOOL waitAll=RTRTRUE);
		// Wait for a given array of thread id to finish execution
		// the return thread id is indetermined
		// NOTE: the posix implementation will always wait for all threads
		// in arr to join regardless of the value of waitAll.
		// _TAG07 Operations

// Access - sequential
	RTRThreadMgrIterator threadIterator();
		// _TAG03 Access - sequential

	void lockThreadPool();
		// Synchronize the access of its thread pool

	void unlockThreadPool();

protected:
	void registerThread(RTRThread&);
		// Register the thread with this mgr when it is started

	void unRegisterThread(RTRThread&);
		// unregister the thread with this mgr when it is to be finished

// Data
	RTRLinkedList<RTRThread> _tList;
	RTRMutex _tListLock; //Lock to protect _tList
	RTRString _name;

// Friends
	friend class RTRThread;
	friend class RTRThreadMgrIterator;

private:
// Don't implement
	RTRThreadMgr(const RTRThreadMgr& );
	RTRThreadMgr& operator=(const RTRThreadMgr& );
};

// Synopsis:
// #include "rtr/thread.h"
//
// Description:
//
// See Also:
//	RTRThreadMgr
//
class RTRThreadMgrIterator
{
public:
// Constructor
	RTRThreadMgrIterator(RTRThreadMgr*);
		// _TAG Constructor

// Destructor
	~RTRThreadMgrIterator();
		// _TAG Destructor

// Attributes
	int count() const;
		// The number of threads available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete?
		// _TAG02 State

	RTRBOOL empty() const;
		// ENSURE: result implies count() == 0
		// _TAG02 State

// Access
	RTRThread& item() const;
		// The current item in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration.
		// ENSURE: off() implies empty()
		// _TAG03 Operations

	void finish();
		// Start an iteration from the last available thread.
		// ENSURE: off() implies empty()
		// _TAG03 Operations

	void forth();
		// Continue the current iteration from start() to finish().
		// REQUIRE: !off()
		// _TAG03 Operations

	void back();
		// Continue the current iteration from finish() to start().
		// REQUIRE: !off()
		// _TAG03 Operations

protected:
// Data
	RTRThreadMgr* _context;
};

#endif // For platforms that not support thread programming, shouldn't 
		// use thread classes at all

#endif

