//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author:	T. Zhang
// Created: "Jul. 28 1997"
// Version: 2.0

#ifndef _clnobj_h
#define _clnobj_h

#include "rtr/mo.h"

class RTRCloneObjectDirectory;

// Synopsis:
// #include"rtr/shmclno.h"
//
// Description:
// RTRCloneObject is an implementation of RTRManagedObject which is a
// clone of a RTRPublicObject whose data can be found in shared memory.
// RTRCloneObject are created by an instance of RTRCloneObjectDirectory.
//
// See Also:
// RTRCloneVariable, RTRCloneObjectDirectory, 
// RTRCloneCounter, RTRCloneGauge, RTRCloneNumeric, 
// RTRCloneNumericConfig,
// RTRCloneNumericParameter, RTRCloneString, RTRCloneStringConfig, 
//	
//
// Inherits:
//	RTRManagedObject
//

class RTRCloneObject :
	public RTRManagedObject
{
public:
// Constructor 
	RTRCloneObject(
			const RTRObjectId& , 
			RTRMOImpl * ,
			RTRCloneObjectDirectory& 
			);
		// A new proxy root object
		// _TAG Constructor

	RTRCloneObject(
			RTRCloneObject& parent,
			RTRMOImpl* 
			);
		// A new proxy sub-object
        // _TAG Constructor

// Destructor
	~RTRCloneObject();
        // _TAG Destructor

// Attributes
	inline RTRCloneObjectDirectory& cloneDirectory() const;

// State
	RTRBOOL upToDate() const;
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
	RTRCloneObjectDirectory& _clnDir;
		// Add for performance 
	unsigned long _transactionLevel;
	unsigned short _totalChildAdded;
	unsigned short _totalChildRemoved;
	unsigned short _totalVarAdded;
	unsigned short _totalVarRemoved;

// Friends
friend class RTRCloneObjectDirectory;
};

inline RTRCloneObjectDirectory& RTRCloneObject::cloneDirectory() const
{
	return _clnDir;
}

#endif
