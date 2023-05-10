//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author:	T. Zhang
// Revised: "Jul. 28 1997"
// Version: 2.0

#ifndef _moshmhdr_h
#define _moshmhdr_h

#include "rtr/momemhdr.h"

#ifndef _RDEV_NO_STL_

#else
	#include <stdio.h>
#endif

// Synopsis:
// #include"rtr/moshmhdr.h"
//
// Description:
// See Also:
//	RTRMOMemoryHeader, RTRMOMemPoolHeader, RTRMOServerReply, RTRMOCloneRequest
//
// Inherits:
//  RTRMOMemoryHeader
//


struct MOShmHeaderImpl{
	unsigned long minorVersionNumber;

	unsigned long transFlagSemaphoreNumber;
	unsigned long moLockSemaphoreNumber;
	unsigned long rwLockSemaphoreNumber;
	unsigned long replySemaphoreNumber;
	unsigned long semKeyOffset;
		// offset of the char _semaphoreKey[MAX_SEMAPHORE];
};

const unsigned long SHM_HEADER_FIX_SIZE =  sizeof(MOShmHeaderImpl);

const unsigned long SHM_MO_HEADER_SIZE =  SHM_HEADER_FIX_SIZE + 
	MO_HEADER_FIX_SIZE + PAR_SET_REQ_FIX_SIZE + PAR_SET_RES_FIX_SIZE;

class RTRMOShmemHeader
	: public RTRMOMemoryHeader
{
public:
// Constructor
	RTRMOShmemHeader(MOMemHeader& implAddr, rtrUIntPtr base)
			:RTRMOMemoryHeader(implAddr, base){};
        // _TAG Constructor

// Destructor
	~RTRMOShmemHeader();
        // _TAG Destructor

// Attributes
	inline  MOShmHeaderImpl* implHeader() const;
		// The implementation header
        // _TAG02 Attributes

	inline int minorVersionNumber() const;
		// The minor version number of this object layout (reference).
        // _TAG02 Attributes

	RTRString text() const;
		// Textual explanation of error.
        // REQUIRE : error()        
		// _TAG02 Attributes

	inline const char *semaphoreKey() const;
		// The key for the set of semaphores used by the server.
        // _TAG02 Attributes

	inline int moLockSemaphoreNumber() const;
		// The semaphore number for locking access to managed objects.
        // _TAG02 Attributes

	inline int transFlagSemaphoreNumber() const;
		// The semaphore number for locking message transactions.
        // _TAG02 Attributes

	inline int rwLockSemaphoreNumber() const;
		// The semaphore number for locking message writes.
        // _TAG02 Attributes

	inline int replySemaphoreNumber() const;
		// The semaphore number of flagging message replies. 
        // _TAG02 Attributes

// State
	RTRBOOL error() const;
		// For client to check error
        // _TAG03 State

// Server operations
	void init(const RTRString&, int, int, int, int);
		// For server to initialize the header
        // _TAG06 Server operations

protected:
// Data
		// Data
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream& os, const RTRMOShmemHeader& );
#else
public:
	void print(FILE* os);
#endif
};

inline
MOShmHeaderImpl* RTRMOShmemHeader::implHeader() const
{
	return (MOShmHeaderImpl*) (_storeAddr.implementation + base()) ;
}

inline
int RTRMOShmemHeader::minorVersionNumber() const
{
	return implHeader()->minorVersionNumber;
}

inline 
int RTRMOShmemHeader::transFlagSemaphoreNumber() const
{
	return implHeader()->transFlagSemaphoreNumber;
}

inline 
int RTRMOShmemHeader::moLockSemaphoreNumber() const
{
	return implHeader()->moLockSemaphoreNumber;
}

inline 
int RTRMOShmemHeader::rwLockSemaphoreNumber() const
{
	return implHeader()->rwLockSemaphoreNumber;
}

inline 
int RTRMOShmemHeader::replySemaphoreNumber() const
{
	return implHeader()->replySemaphoreNumber;
}

inline
const char *RTRMOShmemHeader::semaphoreKey() const
{
	return (char*)(implHeader()->semKeyOffset+base());
}

#endif
