//|---------------------------------------------------------------------------
//|                Copyright (C) 2001 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60523                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "6/26/01"
// Version: 1.0

#ifndef _rtr_shmpmodi0_h
#define _rtr_shmpmodi0_h

#include "rtr/rtrdefs.h"

class RTRShmProxyManagedObjectDirectory_EliF21;
class RTRShmProxyManagedObjectHandle_EliF21;
class RTRShmProxyManagedObjectDirectory_Mdk10;
class RTRShmProxyManagedObjectHandle_Mdk10;

class RTRShmProxyManagedObjDirRootIterator_EliF21
{
public:
// Constructor
	RTRShmProxyManagedObjDirRootIterator_EliF21(RTRShmProxyManagedObjectDirectory_EliF21*);
		// _TAG Constructor

// Destructor
	~RTRShmProxyManagedObjDirRootIterator_EliF21();
		// _TAG Destructor

// Attributes
	int count() const;
		// The number of roots available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no root available via this iterator?
		// ENSURE: result implies count() == 0
		// _TAG02 State

// Access
	RTRShmProxyManagedObjectHandle_EliF21& item() const;
		// The current item in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void finish();
		// Start an iteration from the last available root.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void forth();
		// Continue the current iteration from start() to finish().
		// REQUIRE: !off()
		// _TAG04 Operations

	void back();
		// Continue the current iteration from finish() to start().
		// REQUIRE: !off()
		// _TAG04 Operations

protected:
// Data
	RTRShmProxyManagedObjectDirectory_EliF21& _context;
	RTRShmProxyManagedObjectHandle_EliF21* _current;
};


class RTRShmProxyManagedObjDirRootIterator_Mdk10
{
public:
// Constructor
	RTRShmProxyManagedObjDirRootIterator_Mdk10(RTRShmProxyManagedObjectDirectory_Mdk10*);
		// _TAG Constructor

// Destructor
	~RTRShmProxyManagedObjDirRootIterator_Mdk10();
		// _TAG Destructor

// Attributes
	int count() const;
		// The number of roots available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no root available via this iterator?
		// ENSURE: result implies count() == 0
		// _TAG02 State

// Access
	RTRShmProxyManagedObjectHandle_Mdk10& item() const;
		// The current item in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void finish();
		// Start an iteration from the last available root.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void forth();
		// Continue the current iteration from start() to finish().
		// REQUIRE: !off()
		// _TAG04 Operations

	void back();
		// Continue the current iteration from finish() to start().
		// REQUIRE: !off()
		// _TAG04 Operations

protected:
// Data
	RTRShmProxyManagedObjectDirectory_Mdk10& _context;
	RTRShmProxyManagedObjectHandle_Mdk10* _current;
};

#endif

