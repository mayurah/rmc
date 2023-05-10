//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _pmo_h
#define _pmo_h

#include "rtr/mo.h"
#include "rtr/pmbv.h"
#include "rtr/pmbcv.h"
#include "rtr/pmcntrv.h"
#include "rtr/pmgv.h"
#include "rtr/pmgcv.h"
#include "rtr/pmnumrv.h"
#include "rtr/pmnumcv.h"
#include "rtr/pmnumv.h"
#include "rtr/pmlnumv.h"
#include "rtr/pmstrcv.h"
#include "rtr/pmstrv.h"
#include "rtr/glbmod.h"

// Synopsis:
// #include"rtr/pmo.h"
//
// Description:
// 	Typically, application components which wish to be
// 	managed or become "public" are descendants of RTRPublicObject.
// 	They in turn may instantiate other public objects which
// 	will be their children in the managed object tree.
//
// 	Public objects may create member variables as appropriate,
// 	using the appropriate Public variable class. For example, to
// 	instantiate a numeric counter, the RTRPublicCounter
// 	class would be used.
//
// See Also:
//	RTRPublicCounter, RTRPublicGauge, RTRPublicNumeric,
// 	RTRPublicLargeNumeric,
//	RTRPublicString, RTRPublicNumericRange, RTRPublicStringConfig,
//	RTRPublicNumericConfig, RTRPublicBooleanConfig,
//	RTRPublicGaugeConfig, RTRPublicBoolean
//
// Inherits:
//	RTRManagedObject
//

class RTRPublicObject :
	public RTRManagedObject
{
public:
// Constructor 
	RTRPublicObject(
		const RTRObjectId& context,
		const char* name,
		const char* description,
		const RTRObjectId& classId
		);
		// A new root object in the Normal state
		// _TAG Constructor

	RTRPublicObject(
		RTRPublicObject& parentObject, 
		const char* name,
		const char * description,
		const RTRObjectId& classId
		);
		// A new sub-object in the Normal state
		// _TAG Constructor

	RTRPublicObject(
		const RTRObjectId& context,
		const char* name,
		const char* description,
		const RTRObjectId& classId,
		MOState startState
		);
		// A new root object in the given state.
		// _TAG Constructor

	RTRPublicObject(
		RTRPublicObject& parentObject, 
		const char* name,
		const char* description,
		const RTRObjectId& classId,
		MOState startState
		);
		// A new sub-object in the given state.
		// _TAG Constructor

// Destructor
	~RTRPublicObject();
		// _TAG Destructor

	// Expose these operations from RTRManagedObject as inlines so that 
	// they show up in the documentation

// Operations
	void markNormal( const char * );
		// Mark this object normal and notify clients;
		// _TAG06 Operations

	void markRecovering( const char * );
		// Mark this object recovering and notify clients;
		// _TAG06 Operations

	void markWaiting( const char * );
		// Mark this object waiting and notify clients;
		// _TAG06 Operations

	void markDead( const char * );
		// Mark this object dead and notify clients;
		// _TAG06 Operations

	void indicateInfo( const char * );
		// Notify clients of change in text.
		// _TAG06 Operations

private:
// Don't define these:
	RTRPublicObject(const RTRPublicObject&);
	RTRPublicObject & operator=(const RTRPublicObject&);
};


// Synopsis:
// #include"rtr/pmo.h"
//
// Description:
// A construct that is convinient in a multi-thread application where 
// synchronization is needed for accessing managed object directory (MOD) and
// parent managed object. For example, when constructing/descructing 
// intances of RTRPublicObject in multiple threads, instance of this can be
// constructed on stack to lock the global object tree, and when
// this instance is out of scope, its desctructor is called to unlock the
// global object tree.
// Example code:
//  	// A block of code in one thread
//  {
//  	RTRPublicObjectLock lock1;
//			//Now the global object directory is locked
//  	root = new RTRPublicObject(...);
//  }
//  	// lock1 now is out of scope 
//
// See Also:
//  RTRPublicObject, RTRGlobalManagedObjectDirectory, RTRLockableObj
//
// Inherits:
//

class RTRPublicObjectLock 
{
public:
// Constructor 
	inline RTRPublicObjectLock(RTRManagedObject* parent = 0);
		// Used to synchronize the access of global managed object directory.
		// Parent object is present when constructing a non-root object where 
		// its parent also needs to be locked in a multi-thread context
		// _TAG Constructor

// Destructor
	~RTRPublicObjectLock();
		// _TAG Destructor

protected:
	RTRManagedObject* _parentObj;

private:
// Don't define these:
	RTRPublicObjectLock(const RTRPublicObjectLock&);
	RTRPublicObjectLock & operator=(const RTRPublicObjectLock&);
};

inline RTRPublicObjectLock::RTRPublicObjectLock(RTRManagedObject* parent)
	:_parentObj(parent)
{
	RTRManagedObjectDirectory& dir =
		RTRGlobalManagedObjectDirectory::directory();
	dir.lock();
	if(_parentObj)
		_parentObj->lock();
}

inline RTRPublicObjectLock::~RTRPublicObjectLock()
{
	if(_parentObj)
		_parentObj->unlock();
	RTRManagedObjectDirectory& dir =
		RTRGlobalManagedObjectDirectory::directory();
	dir.unlock();
}

#endif
