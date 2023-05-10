//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Aug. 15 1995"
// Version: 1.0
//
// Modified: "Jul. 24 1997"
// Author: 	T. Zhang
// Version: 2.0

#ifndef _memparti_h
#define _memparti_h

#include "rtr/memparti0.h"
#include "rtr/shmhdr.h"


// Synopsis:
// #include"rtr/memparti.h"
//
// Description:
// 	The description of a shared memory partition.
//
// See Also:
// 	RTRServerPartition, RTRClientPartition
//


struct ShmPartiHdr
{
	unsigned long classId;
	unsigned long instanceId;
	unsigned long size;
	unsigned long offset;
	unsigned long next;
		// next partition  hdr
};

class RTRSharedMemoryPartitionHdr 
{ 
public:
// Constructor
	RTRSharedMemoryPartitionHdr(
		RTRSharedMemoryHdr& hdr,
		ShmPartiHdr* s)
		:_header(hdr),_storeImpl(s){};
		// From client side

	RTRSharedMemoryPartitionHdr(
			RTRSharedMemoryHdr& header,
			const RTRObjectId& cid, 	// Class of this partition
			const RTRObjectId& iid, 	// Unique instance id of this partition
			unsigned long size
			);
		// _TAG Constructor

// Identity
	const char *classId() const;
		// _TAG02 Identity

	const char *instanceId() const;
        // _TAG02 Identity

// Attributes
	inline unsigned long size() const;
		// The size of this partition.
		// _TAG03 Attributes

	inline unsigned long offset() const;
		// Offset of this partition from start of header user data.
        // _TAG03 Attributes

	inline const char *data(const char *basePtr);
		// Pointer to data region of this partition.
        // _TAG03 Attributes

	inline rtrUIntPtr base() const;

// Static methods
	static const char* classIdOf(ShmPartiHdr&, rtrUIntPtr base);

	static const char* instanceIdOf(ShmPartiHdr&, rtrUIntPtr base);

protected:
// Data
	ShmPartiHdr* _storeImpl;
	RTRSharedMemoryHdr& _header;
}; 

inline
rtrUIntPtr RTRSharedMemoryPartitionHdr::base() const
{
	return _header._base;
}

inline
const char *RTRSharedMemoryPartitionHdr::classId() const
{
	return (char*)(_storeImpl->classId + base());
}

inline
const char *RTRSharedMemoryPartitionHdr::instanceId() const
{
	return (char*)(_storeImpl->instanceId + base());
}

inline 
unsigned long RTRSharedMemoryPartitionHdr::size() const
{
	return _storeImpl->size;
}

inline 
unsigned long RTRSharedMemoryPartitionHdr::offset() const
{
	return _storeImpl->offset;
}

// Synopsis:
// #include "rtr/memparti.h"
//
// Description:
//	A descendant of RTRSharedMemoryPartition which provides primitive
//	facillities for allocating memory from within the partition. No
//	de-allocation methods are provided (clients must maintain their own
//	free lists).
//
// See Also:
//	RTRSharedMemoryParitionHdr, RTRSharedMemoryPartition, 
//	RTRClientPartition
//

class RTRServerPartition
{ 
public:
// Constructor
	RTRServerPartition(
			const RTRObjectId&, 	// Class of this partition
			const RTRObjectId&, 	// Unique instance id of this partition
			RTRSharedMemoryHdr&,	// Memory from which to allocate
			unsigned long 			// Size
			);
		// Id's are copied.
		// _TAG Constructor

	~RTRServerPartition();

// Identity
	inline const RTRObjectId& classId() const;
		// _TAG01 Identity

	inline const RTRObjectId& instanceId() const;
        // _TAG01 Identity

// Attributes
	inline unsigned long size() const;
		// The size of this partition.
		// _TAG02 Attributes

	inline unsigned long bytesAvailable() const;
		// The number of bytes still available from this partition.
        // _TAG02 Attributes

	inline unsigned long bytesUsed() const;
		// The number of bytes already allocated from this partition.
        // _TAG02 Attributes

	inline const RTRString& text() const;
		// An explanation for error().
        // _TAG02 Attributes

	const char *baseAddress() const;
		// REQUIRE: !error() 
        // _TAG02 Attributes

// State
	inline RTRBOOL error() const;
		// Is this partition in an error state.
		// _TAG03 State

// Query
	inline RTRBOOL hasAvailableBytes(unsigned long sz);
		// Are sz bytes available from this partition?
		// _TAG04 Query

// Operations
	const char *allocateAvailableBytes(unsigned long sz);
		// Allocate the given number of bytes, returning a pointer to
		// the starting address.
		// ENSURE : (result % sizeof(char *)) == 0
		// _TAG05 Operations

protected:
// Data
	RTRObjectId _classId;
	RTRObjectId _instanceId;
	RTRBOOL _error;
	RTRString _text;
	unsigned long _bytesUsed;
	RTRSharedMemoryHdr& _header;
	RTRSharedMemoryPartitionHdr *_memoryPartition;
		// Data
}; 

inline 
const RTRObjectId& RTRServerPartition::classId() const
{
	return _classId;
}

inline 
const RTRObjectId& RTRServerPartition::instanceId() const
{
	return _instanceId;
}

inline 
unsigned long RTRServerPartition::size() const
{
	return _memoryPartition ? _memoryPartition->size() : 0;
}

inline 
const RTRString& RTRServerPartition::text() const
{
	return _text;
}

inline 
RTRBOOL RTRServerPartition::error() const
{
	return _error;
}

inline
RTRBOOL RTRServerPartition::hasAvailableBytes(unsigned long sz)
{
	return (unsigned long)sz <= bytesAvailable();
}

inline 
unsigned long RTRServerPartition::bytesUsed() const
{
	return _bytesUsed;
}

inline 
unsigned long RTRServerPartition::bytesAvailable() const
{
	return size() - bytesUsed();
}


class RTRClientSharedMemoryRoot;

// Synopsis:
// #include"rtr/memparti.h"
//
// Description:
// See Also:
//	RTRSharedMemoryPartitionHdr, RTRServerPartition
//

class RTRClientPartition
{ 
public:
// Constructor
	RTRClientPartition(
			const RTRClientSharedMemoryRoot& root,
			const RTRObjectId& classId
			);
		// _TAG Constructor

	RTRClientPartition(
			const RTRClientSharedMemoryRoot& root,
			const RTRObjectId& cid,
			const RTRObjectId& iid
			);
		// _TAG Constructor
	
	RTRClientPartition(
			RTRSharedMemoryHdr& header,
			ShmPartiHdr& partition
			);
		// _TAG Constructor

// Desctructor
	~RTRClientPartition();
		// _TAG Desctructor

// Identity
	inline const RTRObjectId& classId() const;
		// _TAG01 Identity

	inline const RTRObjectId& instanceId() const;
		// REQUIRE: !error()
        // _TAG01 Identity

// Attributes
	inline unsigned long size() const;
		// The size of this partition.
		// REQUIRE: !error()
		// _TAG02 Attributes

	const char *baseAddress() const;
		// REQUIRE: !error() 
        // _TAG02 Attributes

	const char *data() const;
		// The data for this partition
		// REQUIRE: !error() 
		// REQUIRE: size() > 0
        // _TAG02 Attributes

	inline const RTRString& text() const;
        // _TAG02 Attributes

// State
	inline RTRBOOL error() const;
		// _TAG03 State

protected:
// Data
	RTRObjectId _classId;
	RTRObjectId _instanceId;
	RTRBOOL _error;
	RTRString _text;
	RTRSharedMemoryHdr& _header;
	RTRSharedMemoryPartitionHdr *_partition;
		// Data
}; 

inline 
const RTRObjectId& RTRClientPartition::classId() const
{
	return _classId;
}

inline 
const RTRObjectId& RTRClientPartition::instanceId() const
{
	RTPRECONDITION ( !error() );

	return _instanceId;
}

inline 
unsigned long RTRClientPartition::size() const
{
	RTPRECONDITION ( !error() );

	return _partition->size();
}

inline 
const RTRString& RTRClientPartition::text() const
{
	return _text;
}

inline 
RTRBOOL RTRClientPartition::error() const
{
	return _error;
}

#endif
