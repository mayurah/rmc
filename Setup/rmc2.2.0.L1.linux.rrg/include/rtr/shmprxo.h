//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _shmprxo_h
#define _shmprxo_h

#include "rtr/mo.h"
#include "rtr/shmmo.h"

class RTRShmProxyMgr;

// Synopsis:
// #include"rtr/shmprxo.h"
//
// Description:
// RTRProxyObject is an implementation of RTRManagedObject which is a
// clone of a RTRPublicObject whose data can be found in shared memory.
// RTRProxyObject are created by an instance of RTRShmProxyMgr.
//
// See Also:
// RTRShmProxyMgr, RTRProxyCounter, RTRProxyGauge, RTRProxyNumeric, 
// RTRProxyNumericConfig,
// RTRProxyNumericParameter, RTRProxyString, RTRProxyStringConfig, 
// RTRProxyVarWatchList, RTRProxyVarWatchListClient, RTRProxyVariable
//	
//
// Inherits:
//	RTRManagedObject
//

class RTRProxyObject :
	public RTRManagedObject
{
public:
// Constructor 
	RTRProxyObject(
			const RTRObjectId&, 
			RTRShmMObject& shmObject,
			RTRShmProxyMgr& mgr,
			MOState dead
			);
		// A new proxy root object
		// _TAG Constructor

	RTRProxyObject(
			RTRProxyObject& parent,
			RTRShmMObject& shmObject,
			RTRShmProxyMgr& mgr,
			MOState dead
			);
		// A new proxy sub-object
        // _TAG Constructor

// Destructor
	~RTRProxyObject();
        // _TAG Destructor

// State
	RTRBOOL upToDate() const;
        // _TAG01 State

	RTRBOOL valid() const;
        // _TAG01 State

// Operations
	void update();
        // _TAG02 Operations

	void markDead(const char*);
        // _TAG02 Operations

// Static data
	static RTRBOOL debugEnabled;
	static RTRBOOL dupIdCheckEnabled;

protected:
// Data
	RTRShmProxyMgr& _mgr;
	int _transactionLevel;
	int _usageCounter;

// Friends
friend class RTRShmProxyMgr;
};

/////////////////////////////////////////////////////////////////////////
//
// For backward compatibility: support EliF21 version
//
/////////////////////////////////////////////////////////////////////////
// Synopsis:
// #include"rtr/shmprxo.h"
//
// Description:
// RTRProxyObject_EliF21 is an old version of class RTRProxyObject.
//
// See Also:
// RTRProxyObject, RTRShmMObject_EliF21
//
// Inherits:
//	RTRManagedObject
//

class RTRProxyObject_EliF21 :
	public RTRManagedObject
{
public:
// Constructor 
	RTRProxyObject_EliF21(
			const RTRObjectId&, 
			RTRShmMObject_EliF21& shmObject,
			RTRShmProxyMgr& mgr,
			MOState dead
			);
		// A new proxy root object
		// _TAG Constructor

	RTRProxyObject_EliF21(
			RTRProxyObject_EliF21& parent,
			RTRShmMObject_EliF21& shmObject,
			RTRShmProxyMgr& mgr,
			MOState dead
			);
		// A new proxy sub-object
        // _TAG Constructor

// Destructor
	~RTRProxyObject_EliF21();
        // _TAG Destructor

// State
	RTRBOOL upToDate() const;
        // _TAG01 State

	RTRBOOL valid() const;
        // _TAG01 State

// Operations
	void update();
        // _TAG02 Operations

	void markDead(const char*);
        // _TAG02 Operations

// Static data
	static RTRBOOL debugEnabled;
	static RTRBOOL dupIdCheckEnabled;

protected:
// Data
	RTRShmProxyMgr& _mgr;
	int _transactionLevel;
	int _usageCounter;

// Friends
friend class RTRShmProxyMgr;
};


/////////////////////////////////////////////////////////////////////////
//
// For backward compatibility: support EliF14 version
//
/////////////////////////////////////////////////////////////////////////
class RTRProxyObject_EliF14 :
	public RTRManagedObject
{
public:
// Constructor 
	RTRProxyObject_EliF14(
			const RTRObjectId&, 
			RTRShmMObject_EliF14&, 
			RTRShmProxyMgr&,
			MOState dead
			);
		// A new proxy root object

	RTRProxyObject_EliF14(
			RTRProxyObject_EliF14&, 
			RTRShmMObject_EliF14&, 
			RTRShmProxyMgr&,
			MOState dead
			);
		// A new proxy sub-object

// Destructor
	~RTRProxyObject_EliF14();

// State
	RTRBOOL upToDate() const;

	RTRBOOL valid() const;

// Operations
	void update();

	void markDead(const char*);

// Static data
	static RTRBOOL debugEnabled;
	static RTRBOOL dupIdCheckEnabled;

protected:
	RTRShmProxyMgr& _mgr;
	int _transactionLevel;
	int _usageCounter;

// Friends
friend class RTRShmProxyMgr;
};

#endif
