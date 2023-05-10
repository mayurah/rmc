//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "Sept. 13 1996"
// Version: 1.0

#ifndef _mtgc_h
#define _mtgc_h

#include "rtr/gc.h"
#include "rtr/lock.h"
#include "rtr/mutex.h"

// Synopsis:
// #include "rtr/mtgc.h"
//
// Description:
// RTRMTGCObj is a MT-safe version of RTRGCObj, operations on its reference 
// counter are synchronized by an instance of RTRLockableObj.
//
// See Also:
// RTRGCObj
//

class RTRMTGCObj
{
public:
// Constructor
	inline RTRMTGCObj() ;
		// _TAG Constructor

// Destructor
	virtual ~RTRMTGCObj();
		// _TAG Destructor

// Operations
	inline void incrementCount();
		// _TAG01 Operations

	inline void decrementCount();
        // _TAG01 Operations

protected:
// Operations
	virtual void dispose();
		// calls delete

// Data
	int _referenceCount;
	RTRLockableObj _refCountLock;
};

inline
RTRMTGCObj::RTRMTGCObj() 
	: _referenceCount(0)
{
}

inline 
void RTRMTGCObj::incrementCount()
{
	_refCountLock.lock();
	_referenceCount++;
	_refCountLock.unlock();
}

inline 
void RTRMTGCObj::decrementCount()
{
	_refCountLock.lock();
	_referenceCount--;
	if ( _referenceCount == 0 )
	{
		_refCountLock.unlock();
		dispose() ;
	}
	else
		_refCountLock.unlock();
}

// Synopsis:
// #include "rtr/mtgc.h"
//
// Description:
// RTRGCMutex is-a RTRMutex and also a RTRMTGCObj.
//
// See Also:
// RTRMutex, RTRMTGCObj
//
// Inherits:
//	RTRMutex, RTRMTGCObj
// 
class RTRGCMutex :
	 public RTRMutex,
	 public RTRMTGCObj
{
};

typedef RTRObjRef<RTRGCMutex> RTRGCMutexPtr;


// Synopsis:
// #include "rtr/mtgc.h"
//
// Description:
// RTRGCGuard to RTRGCMutex is the same as RTRGuard to RTRMutex. 
//
// See Also:
// RTRGCMutex, RTRGuard, RTRMutex
//

class RTRGCGuard {
public:
// Constructor
	inline RTRGCGuard(RTRGCMutex& m);
		// On construction, acquire the lock 
		// _TAG Constructor

	inline RTRGCGuard(RTRGCMutex* m);
		// On construction, acquire the lock 
		// _TAG Constructor

// Destructor
	inline ~RTRGCGuard();
		// On destruction, release the lock 
		// _TAG Destructor

protected:
RTRGCMutexPtr _mtxptr;
};

inline 
RTRGCGuard::RTRGCGuard(RTRGCMutex& m)
{
	_mtxptr = &m;
	_mtxptr->lock();
}

inline 
RTRGCGuard::RTRGCGuard(RTRGCMutex* m)
{
	_mtxptr = m;
	_mtxptr->lock();
}

inline 
RTRGCGuard::~RTRGCGuard() 
{
	_mtxptr->unlock();
}

#endif
