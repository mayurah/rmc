//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "Jul. 08 1997"
// Version: 1.0

#ifndef _rtr_mgshmalc_h
#define _rtr_mgshmalc_h

#include "rtr/mgmemalc.h"
#include "rtr/pbitem.h"
#include "rtr/rtstring.h"
#include "rtr/dlinkl.h"

class RTRSharedMemoryStats;
class RTRManagedSharedMem;
class RTRMemoryAllocator;
class RTRShmMOServerMemPool;
class RTRMOShmemHeader;

//
// Synopsis:
// #include "rtr/mgshmalc.h"
//
// Description:
// 
// See Also:
//
// Inherits:
//


class RTRManagedShmAllocator
	: public RTRManagedMemAllocator
{ 
public:
// Constructor
	RTRManagedShmAllocator(RTRShmMOServerMemPool&);
		// _TAG Constructor

// Destructor
	virtual ~RTRManagedShmAllocator();
		// _TAG Destructor

// Operations
	void* allocate(unsigned long bytes, int statsType=0);
		// Allocate memory of size bytes, the flag "statsType"
		// is for statistics purpose only

	void deallocate(char* mem, unsigned long bytes, int statsType);

	void update();
		// Called by server

	RTRMOMemoryHeader* newHeader(const RTRString&, int, int, int, int);

protected:
// Utilities
	void removeForAction(RTRPublishedItem&);
		// Called by item

	void addForAction(RTRPublishedItem&);
		// Called by item
		// _TAG07 Operations

	void cleanUp();
		// Separate this from destructor, for checking memory usage

// Data
	RTRManagedSharedMem* _mShmem;
	RTRMemoryAllocator* _allocator;
	RTRDLinkList<RTRPublishedItem, RTRDLinkPI> _itemList;
	RTRShmMOServerMemPool& _server;
	unsigned long _hdrBytes;
		// If not for semaphore key string, size is fixed (known)

// Friends
	friend class RTRShmMOServerMemPool;
	friend class RTRSharedMemoryStats;
private:
// Don't implement
	RTRManagedShmAllocator(const RTRManagedShmAllocator&);
	RTRManagedShmAllocator& operator=(const RTRManagedShmAllocator&);
}; 

#endif
