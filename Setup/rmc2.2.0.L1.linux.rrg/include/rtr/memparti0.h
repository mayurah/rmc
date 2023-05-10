//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Aug. 15 1995"
// Version: 1.0

#ifndef _memparti0_h
#define _memparti0_h

#include "rtr/rtstring.h"
#include "rtr/objid.h"
#include "rtr/shmdll.h"

class RTRSharedMemoryHdr_EliF14;
class RTRSharedMemoryHdr_EliF21;

// Synopsis:
// #include"rtr/memparti.h"
//
// Description:
// The description of a shared memory partition. 
//
// See Also:
// 	RTRClientPartition_Eli
//

#define MAX_CLASS_ID_LENGTH 40
#define MAX_INSTANCE_ID_LENGTH 100

class RTRSharedMemoryPartitionHdr_Eli :
	public RTRShmDLink0
{ 
public:
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

protected:
// Data
	char _classId[MAX_CLASS_ID_LENGTH + 1];
	char _instanceId[MAX_INSTANCE_ID_LENGTH + 1];
	unsigned long _size;
	unsigned long _offset;
		// Data
}; 

inline 
unsigned long RTRSharedMemoryPartitionHdr_Eli::size() const
{
	return _size;
}

inline 
unsigned long RTRSharedMemoryPartitionHdr_Eli::offset() const
{
	return _offset;
}


class RTRClientSharedMemoryRoot;

// Synopsis:
// #include"rtr/memparti.h"
//
// Description:
// See Also:
//	RTRSharedMemoryPartitionHdr_Eli, RTRClientSharedMemoryRoot, 
//	RTRSharedMemoryHdr_EliF21, RTRSharedMemoryHdr_EliF14
//

class RTRClientPartition_Eli
{ 
public:
// Constructor
	RTRClientPartition_Eli(
			const RTRClientSharedMemoryRoot& root,
			const RTRObjectId& classId
			);
		// _TAG Constructor

	RTRClientPartition_Eli(
			const RTRClientSharedMemoryRoot& root,
			const RTRObjectId& cid,
			const RTRObjectId& iid
			);
		// _TAG Constructor
	
	RTRClientPartition_Eli(
			RTRSharedMemoryHdr_EliF14& header,
			RTRSharedMemoryPartitionHdr_Eli& partition
			);
		// _TAG Constructor

	RTRClientPartition_Eli(
			RTRSharedMemoryHdr_EliF21& header,
			RTRSharedMemoryPartitionHdr_Eli& partition
			);
		// _TAG Constructor

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

	inline const char *baseAddress() const;
		// REQUIRE: !error() 
		// _TAG02 Attributes

	inline const char *data() const;
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
	char* _baseAddr;
	RTRSharedMemoryPartitionHdr_Eli *_partition;
		// Data
}; 

inline 
const RTRObjectId& RTRClientPartition_Eli::classId() const
{
	return _classId;
}

inline 
const RTRObjectId& RTRClientPartition_Eli::instanceId() const
{
	RTPRECONDITION ( !error() );
	return _instanceId;
}

inline 
unsigned long RTRClientPartition_Eli::size() const
{
	RTPRECONDITION ( !error() );

	return _partition->size();
}

inline 
const RTRString& RTRClientPartition_Eli::text() const
{
	return _text;
}

inline 
RTRBOOL RTRClientPartition_Eli::error() const
{
	return _error;
}

inline
const char *RTRClientPartition_Eli::baseAddress() const
{
	RTPRECONDITION ( !error() );
	return _baseAddr;
}

inline
const char *RTRClientPartition_Eli::data() const
{
	RTPRECONDITION ( !error() );
	RTPRECONDITION ( size() > 0 );
	return (char*)(_baseAddr + _partition->offset());
}

#endif
