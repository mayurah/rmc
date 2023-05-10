//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T.L. Zhang
// Created: "Sept. 10 1996"
// Version: 1.0
//

#ifndef _lock_h
#define _lock_h

#include "rtr/rtrdefs.h"

// Synopsis:
// #include "rtr/lock.h" 
//
// Description:
// RTRLockableObj is a base class representing application component which 
// provides lock/unlock operations on itself perceiving that its states/values 
// could be accessed from multiple threads in applications thus need to be 
// synchronized. Any component that want to be made MT-safe can be a decendent 
// class of this. 
//
// The public methods lock()/unlock()/locked() are virtual, so, descendent
// classes can choose their locking implementation if they decide not to use
// RTRReentMutex which comes as default. For example, they can use RTRMutex, 
// or share lock with other contained/referenced class.
//
// The state query member function locked() is used for RTPRECONDITION in 
// application libraries to ensure internal integrity and correct external
// usage. It can be turn on by set static member alwaysLocked to be false
//
// Dummy implementaions are provided for this class so that for platforms 
// that thread programming is not supported, such as sunOS, or for 
// applications that don't require the library classes to be MT-safe,
// the MT-safed libraries will have minimal performance penality.
//
// See Also:
//    RTRReentMutex, RTRLock
//

class RTRLockableObj
{ 
public:
// Constructor
	RTRLockableObj(RTRBOOL useMutex = RTRTRUE);
		// _TAG Constructor

// Destructor
	virtual ~RTRLockableObj() ;
		// _TAG Destructor

// Operations
	virtual void lock() ;
		// _TAG01 Operations

	virtual void unlock();
		// _TAG01 Operations

// State
	virtual RTRBOOL locked() const ; 
		// Is this locked by calling thread ?
		// It is used in PRECONDITION of application class to ensure that an 
		// instance of RTRLockableObj must be locked before access. 
		// Note: this only serves as necessary-but-not-sufficient condition;
		// i.e., (locked()== RTRTRUE) == (possiblely right);
		//       (locked()== RTRFALSE) ==  (definitely wrong);
		// By default this call will always return RTRTRUE unless static member
		// alwaysLocked is set RTRFALSE
		// _TAG02 State

// Static data
	static RTRBOOL alwaysLocked;
		// Used to turn on all internal PRECONDITIONs on "object being locked".
		// This could be too strict for thread application where only necessary 
		// objects need to be locked in a specific context, thus the default 
		// is set to be RTRTRUE here
		// _TAG03 Static data

protected:
	void* _lock; // Default impl use RTRReentMutex,
				 // Descendent class can use something else
private:
// Don't implement
	RTRLockableObj(const RTRLockableObj& );
	RTRLockableObj& operator=(const RTRLockableObj& );
}; 

// Synopsis:
// #include"rtr/lock.h"
//
// Description:
// An instance of RTRLock locks a RTRLockableObj object passed as an argument 
// in constructor, and unlocks it when the RTRLock instance is deleted.
//
// Dummy implementaions are provided for this class so that for platforms 
// that thread programming is not supported, such as sunOS, or for 
// applications that don't require the library classes to be MT-safe,
// the calls (contructor and destructor) embeded in the methods of MT-safed 
// library classes will be no-op, thus minimal performance penality is paid for
// application.
//
// See Also:
// RTRLockableObj

class RTRLock
{
public:
// Constructor
	RTRLock(RTRLockableObj& );
		// On construction,lock the obj
		// _TAG Constructor
					 
// Destructor
	 ~RTRLock() ; 
		 // On destruction, unlock the obj 
		 // _TAG Destructor
protected:
	RTRLockableObj& _lockableObj;

private:
// Don't implement
	RTRLock(const RTRLock& );
	RTRLock& operator=(const RTRLock& );
};


#endif
