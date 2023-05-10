//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 03 1995"
// Version: 1.0

#ifndef _mempmhdr_h
#define _mempmhdr_h

#include <sys/types.h>

#include "rtr/shmmo.h"
#include "rtr/shmdll.h"
#include "rtr/shmmsgs.h"
#include "rtr/portipc.h"
#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

class RTRClientPartition_Eli;

//
// Note: Choose between the version that supports "maxClient" (used in 
// Columbia) or the version that prior to that but after EliF21.
//

class RTRMOMemPoolHeader
{
public:
// Attributes
	inline int versionNumber() const;
		// The version number of this object layout (insurance).
		// _TAG02 Attributes

	inline RTRShmDLinkList<RTRShmMObject, RTRShmDLink0>& roots();
		// This list of root objects in this memory pool.
		// REQUIRE : !error()
		// _TAG02 Attributes

	inline int numberOfAdds() const;
		// The transaction level for additions of roots to the list
		// in this header. Changes when roots are added.
		// REQUIRE : !error()        
		// _TAG02 Attributes

	inline int numberOfRemoves() const;
		// The transaction level for deletions of roots from the list
		// in this header. Changes when roots are removed.
		// REQUIRE : !error()        
		// _TAG02 Attributes

	RTRString text() const;
		// Textual explanation of error.
		// Note : can't store this text as class data because actual
		// data is shared between server and client. 
		// REQUIRE : error()        
		// _TAG02 Attributes

	const char *semaphoreKey() const;
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

	inline int maxClients() const;
		// The maximum number of clients the server will allow.
		// _TAG02 Attributes

	inline const char *msgData() const;
		// Msg data sent by clients
		// _TAG04 Access

	inline const char *replyData() const;
		// Msg data sent by the server
		// _TAG04 Access

// Query
	RTRBOOL hasRoot(const char * nm, const char* base) const;
		// Does this segment have a root object with the given name?
		// REQUIRE : !error()        
		// _TAG05 Query

	RTRBOOL hasRoot(const char * nm, const char* base, RTRShmMObject*) const;
		// Does this segment have a root object with the given name?
		// REQUIRE : !error()        
		// _TAG05 Query

// Static functions
#ifndef _RDEV_NO_STL_
	static void print(std::ostream&, const RTRClientPartition_Eli&);
		// _TAG07 Static functions
#else
	static void print(FILE* os, const RTRClientPartition_Eli&);
		// _TAG07 Static functions
#endif
protected:
// Data
	int _versionNumber;
	int _tlvlAdds;
	int _tlvlRemoves;
	char _semaphoreKey[MAX_SEMAPHORE];
	int _transFlagSemaphoreNumber;
	int _moLockSemaphoreNumber;
	int _rwLockSemaphoreNumber;
	int _replySemaphoreNumber;
	int _maxClients;
		// FIX ME: Some versions between EliF21 and current
		// eshmo2.0 don't have this field
	char _msgData[sizeof(RTRParameterSetRequest)];
	char _replyData[sizeof(RTRParameterSetResult)];
	RTRShmDLinkList<RTRShmMObject, RTRShmDLink0> _roots;
		// Data
};

inline int RTRMOMemPoolHeader::versionNumber() const
{
	return _versionNumber;
}

inline int RTRMOMemPoolHeader::numberOfAdds() const
{
	return _tlvlAdds;
}

inline int RTRMOMemPoolHeader::numberOfRemoves() const
{
	return _tlvlRemoves;
}

inline int RTRMOMemPoolHeader::transFlagSemaphoreNumber() const
{
	return _transFlagSemaphoreNumber;
}

inline int RTRMOMemPoolHeader::moLockSemaphoreNumber() const
{
	return _moLockSemaphoreNumber;
}

inline int RTRMOMemPoolHeader::rwLockSemaphoreNumber() const
{
	return _rwLockSemaphoreNumber;
}

inline int RTRMOMemPoolHeader::replySemaphoreNumber() const
{
	return _replySemaphoreNumber;
}

inline const char *RTRMOMemPoolHeader::semaphoreKey() const
{
	return &_semaphoreKey[0];
}

inline RTRShmDLinkList<RTRShmMObject, RTRShmDLink0>& RTRMOMemPoolHeader::roots()
{
	return _roots;
}

inline const char *RTRMOMemPoolHeader::msgData() const
{
	return _msgData;
}

inline const char *RTRMOMemPoolHeader::replyData() const
{
	return _replyData;
}

inline int RTRMOMemPoolHeader::maxClients() const
{
	return _maxClients;
}

//
// class RTRMOMemPoolHeader_EliF21
//

class RTRMOMemPoolHeader_EliF21
{
public:
// Attributes
	inline int versionNumber() const;

	inline RTRShmDLinkList<RTRShmMObject_EliF21, RTRShmDLink0>& roots();

	inline int numberOfAdds() const;

	inline int numberOfRemoves() const;

	RTRString text() const;

	const char *semaphoreKey() const;

	inline int moLockSemaphoreNumber() const;

	inline int transFlagSemaphoreNumber() const;

	inline int rwLockSemaphoreNumber() const;

	inline int replySemaphoreNumber() const;

	inline const char *msgData() const;

	inline const char *replyData() const;

	RTRBOOL hasRoot(const char * nm, const char* base) const;
	RTRBOOL hasRoot(const char * nm, const char* base, RTRShmMObject_EliF21*) const;

#ifndef _RDEV_NO_STL_
	static void print(std::ostream&, const RTRClientPartition_Eli&);
#else
	static void print(FILE* os, const RTRClientPartition_Eli&);
#endif
protected:
	int _versionNumber;
	int _tlvlAdds;
	int _tlvlRemoves;
	char _semaphoreKey[MAX_SEMAPHORE];
	int _transFlagSemaphoreNumber;
	int _moLockSemaphoreNumber;
	int _rwLockSemaphoreNumber;
	int _replySemaphoreNumber;
	char _msgData[sizeof(RTRParameterSetRequest_EliF21)];
	char _replyData[sizeof(RTRParameterSetResult_EliF21)];
	RTRShmDLinkList<RTRShmMObject_EliF21, RTRShmDLink0> _roots;
};

inline int RTRMOMemPoolHeader_EliF21::versionNumber() const
{
	return _versionNumber;
}

inline int RTRMOMemPoolHeader_EliF21::numberOfAdds() const
{
	return _tlvlAdds;
}

inline int RTRMOMemPoolHeader_EliF21::numberOfRemoves() const
{
	return _tlvlRemoves;
}

inline int RTRMOMemPoolHeader_EliF21::transFlagSemaphoreNumber() const
{
	return _transFlagSemaphoreNumber;
}

inline int RTRMOMemPoolHeader_EliF21::moLockSemaphoreNumber() const
{
	return _moLockSemaphoreNumber;
}

inline int RTRMOMemPoolHeader_EliF21::rwLockSemaphoreNumber() const
{
	return _rwLockSemaphoreNumber;
}

inline int RTRMOMemPoolHeader_EliF21::replySemaphoreNumber() const
{
	return _replySemaphoreNumber;
}

inline const char *RTRMOMemPoolHeader_EliF21::semaphoreKey() const
{
	return &_semaphoreKey[0];
}

inline RTRShmDLinkList<RTRShmMObject_EliF21, RTRShmDLink0>& RTRMOMemPoolHeader_EliF21::roots()
{
	return _roots;
}

inline const char *RTRMOMemPoolHeader_EliF21::msgData() const
{
	return _msgData;
}

inline const char *RTRMOMemPoolHeader_EliF21::replyData() const
{
	return _replyData;
}


#ifndef _WIN32

//
// class RTRMOMemPoolHeader_EliF14
//

class RTRMOMemPoolHeader_EliF14
{
public:
// Attributes
	inline int versionNumber() const;

	inline RTRShmDLinkList<RTRShmMObject_EliF14, RTRShmDLink0>& roots();

	inline int numberOfAdds() const;

	inline int numberOfRemoves() const;

	inline key_t semaphoreKey() const;

	inline int moLockSemaphoreNumber() const;

	inline int transFlagSemaphoreNumber() const;

	inline int rwLockSemaphoreNumber() const;

	inline int replySemaphoreNumber() const;

	inline const char *msgData() const;

	inline const char *replyData() const;

// Query
	RTRBOOL hasRoot(const char *, const char*) const;
	RTRBOOL hasRoot(const char * nm, const char* base, RTRShmMObject_EliF14*) const;

// Static functions
#ifndef _RDEV_NO_STL_
	static void print(std::ostream&, const RTRClientPartition_Eli&);
#else
	static void print(FILE* os, const RTRClientPartition_Eli&);
#endif
protected:
// Data
	int _versionNumber;
	int _tlvlAdds;
	int _tlvlRemoves;
	key_t _semaphoreKey;
	int _transFlagSemaphoreNumber;
	int _moLockSemaphoreNumber;
	int _rwLockSemaphoreNumber;
	int _replySemaphoreNumber;
	char _msgData[sizeof(RTRParameterSetRequest_EliF14)];
	char _replyData[sizeof(RTRParameterSetResult_EliF14)];
	RTRShmDLinkList<RTRShmMObject_EliF14, RTRShmDLink0> _roots;
};

inline int RTRMOMemPoolHeader_EliF14::versionNumber() const
{
	return _versionNumber;
}

inline int RTRMOMemPoolHeader_EliF14::numberOfAdds() const
{
	return _tlvlAdds;
}

inline int RTRMOMemPoolHeader_EliF14::numberOfRemoves() const
{
	return _tlvlRemoves;
}

inline key_t RTRMOMemPoolHeader_EliF14::semaphoreKey() const
{
	return _semaphoreKey;
}

inline int RTRMOMemPoolHeader_EliF14::transFlagSemaphoreNumber() const
{
	return _transFlagSemaphoreNumber;
}

inline int RTRMOMemPoolHeader_EliF14::moLockSemaphoreNumber() const
{
	return _moLockSemaphoreNumber;
}

inline int RTRMOMemPoolHeader_EliF14::rwLockSemaphoreNumber() const
{
	return _rwLockSemaphoreNumber;
}

inline int RTRMOMemPoolHeader_EliF14::replySemaphoreNumber() const
{
	return _replySemaphoreNumber;
}

inline RTRShmDLinkList<RTRShmMObject_EliF14, RTRShmDLink0>& RTRMOMemPoolHeader_EliF14::roots()
{
	return _roots;
}

inline const char *RTRMOMemPoolHeader_EliF14::msgData() const
{
	return _msgData;
}

inline const char *RTRMOMemPoolHeader_EliF14::replyData() const
{
	return _replyData;
}

#else

class RTRMOMemPoolHeader_EliF14
	: public RTRMOMemPoolHeader_EliF21
{
public:
	inline int semaphoreKey() const { return 0;};
		// A fake for compiling other units on NT
};

#endif  // EliF14 was not ported to NT

#endif
