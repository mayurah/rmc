//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Aug. 15 1995"
// Version: 1.0

#ifndef _shmhdr0_h
#define _shmhdr0_h

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif
#include "rtr/rtstring.h"
#include "rtr/shmdll.h"
#include "rtr/portipc.h"
#include "rtr/memparti0.h"

// Synopsis:
// #include"rtr/shmhdr0.h"
//
// Description:
// An instance of RTRSharedMemClientConnection_Eli maintains the state of the
// connection between a shared memory server and one of its clients.
// Connection objects are allocated in shared memory and modified by
// both server and client in accordance with the hand-shaking protocol.
//
// See Also:
//	RTRSharedMemoryHdr_EliF14, RTRSharedMemoryHdr_EliF21, 
//	RTRSharedMemoryPartitionIterator_Eli, RTRServerSharedMemoryHdr
//
// Inherits:
//	RTRShmDLink0
//

class RTRSharedMemClientConnection_Eli :
	public RTRShmDLink0
{
public:
// Attributes
	inline pid_t pid() const;
		// Process id of the client associated with this connection.
		// _TAG01 Attributes

	inline int handshakeLevel() const;
		// The value
		// ENSURE: minHandshakeLevel - 1 <= result <= maxHandshakeLevel + 1
		// _TAG01 Attributes

// State
	inline RTRBOOL serverAlive() const;
		// ENSURE: result implies handshakeLevel() > minHandshakeLevel 
		// _TAG02 State

	inline RTRBOOL serverExited() const;
		// ENSURE: result implies handshakeLevel() == minHandshakeLevel - 1
		// _TAG02 State

	inline RTRBOOL clientAlive() const;
		// ENSURE: result implies handshakeLevel() < maxHandshakeLevel
		// _TAG02 State

	inline RTRBOOL clientExited() const;
		// ENSURE: result implies handshakeLevel() == maxHandshakeLevel + 1
		// _TAG02 State

// Operations
	inline void init(pid_t);
		// _TAG03 Operations

	void markServerAlive();
		// ENSURE: handshakeLevel() >= midHandshakeLevel &&
		// ENSURE: handshakeLevel() <= maxHandshakeLevel
		// _TAG03 Operations

	void markClientAlive();
		// ENSURE: handshakeLevel() <= midHandshakeLevel
		// ENSURE: handshakeLevel() >= minHandshakeLevel
		// _TAG03 Operations

	void markServerExit();
		// ENSURE: handshakeLevel() == minHandshakeLevel - 1
		// _TAG03 Operations

	void markClientExit();
		// ENSURE: handshakeLevel() == maxHandshakeLevel + 1
		// _TAG03 Operations

// Static Data
	static int maxHandshakeLevel;
	static int midHandshakeLevel;
	static int minHandshakeLevel;
		// Static Data

protected:
// Data
	pid_t _pid;
	int _handshakeLevel;
	long _padding;			// Ensures quad alignment. Leave as last member.
};

inline 
pid_t RTRSharedMemClientConnection_Eli::pid() const
{
	return _pid;
}

inline 
int RTRSharedMemClientConnection_Eli::handshakeLevel() const
{
	return _handshakeLevel;
}

inline 
RTRBOOL RTRSharedMemClientConnection_Eli::serverAlive() const 
{ 
	return _handshakeLevel > minHandshakeLevel;
}

inline 
RTRBOOL RTRSharedMemClientConnection_Eli::serverExited() const 
{ 
	return _handshakeLevel == (minHandshakeLevel - 1);
}

inline 
RTRBOOL RTRSharedMemClientConnection_Eli::clientAlive() const 
{ 
	return _handshakeLevel < maxHandshakeLevel;
}

inline 
RTRBOOL RTRSharedMemClientConnection_Eli::clientExited() const 
{ 
	return _handshakeLevel == (maxHandshakeLevel + 1);
}

inline 
void RTRSharedMemClientConnection_Eli::init(pid_t p) 
{ 
	_handshakeLevel = midHandshakeLevel; 
	_pid = p; 
}

class RTRSharedMemoryPartitionIterator_Eli;


// Synopsis:
// #include"rtr/shmhdr.h"
//
// Description:
// See Also:
//	RTRSharedMemClientConnection_Eli, RTRSharedMemoryPartitionIterator_Eli,

class RTRSharedMemoryHdr_EliF21
{
public:
// Constructor
	RTRSharedMemoryHdr_EliF21();
		// _TAG Constructor

// Destructor
	~RTRSharedMemoryHdr_EliF21();
		// _TAG Destructor

// Attributes
	inline unsigned int version() const;
		// The version number of this header layout.
		// _TAG02 Attributes

	inline pid_t pid() const;
		// The pid of the server 
		// _TAG02 Attributes

	inline unsigned int heartbeatInterval() const;
		// The heartbeat to be used in handshaking.
		// _TAG02 Attributes

	long secondsSinceTimeStamp() const;
		// The number of seconds since this segment was timestamped by
		// the server.
		// _TAG02 Attributes

	inline long secondsForTimeOut() const;
		// The number of seconds which, when exceeded, constitutes a timeout.
		// _TAG02 Attributes

	inline const char *semaphoreKey() const;
		// The key of the semaphore to be used for obtaining
		// safe access to this segment.
		// _TAG02 Attributes

	inline int semaphoreNumber() const;
		// The number of the semaphore.
		// _TAG02 Attributes

	inline long timeStamp() const;
		// The last time the server polled this segment.
		// _TAG02 Attributes

	inline unsigned int clientCount() const;
		// The number of active clients.
		// _TAG02 Attributes

	inline unsigned int maxClients() const;
		// The maximum number of clients.
		// _TAG02 Attributes

	inline unsigned long bytesOfUserData() const;
		// The size of the available data area 
		// _TAG02 Attributes

	inline unsigned long userDataOffset() const;
		// Offset of user data from start of segment.
		// _TAG02 Attributes

	inline char *userData() const;
		// The start of the data region available for allocation.
		// ENSURE : result % sizeof(char *)) == 0
		// _TAG02 Attributes

	inline unsigned long userBytesAllocated() const;
		// _TAG02 Attributes

// State
	inline RTRBOOL canAcceptMoreClients() const;
		// ENSURE: result implies clientCount < maxClients
		// _TAG03 State

	inline RTRBOOL hasTimedOut() const;
		// ENSURE: result implies secondsSinceTimeStamp() >= secondsForTimeOut()
		// _TAG03 State

	RTRBOOL connectionIsAllocated(RTRSharedMemClientConnection_Eli&);
		// _TAG03 State

// Client management
	RTRSharedMemClientConnection_Eli *allocatedClient(pid_t);
		// REQUIRE : canAcceptMoreClients()
		// ENSURE : connectionIsAllocated(*result)
		// _TAG04 Client management

	void deallocateClient(RTRSharedMemClientConnection_Eli&);
		// REQUIRE : connectionIsAllocated(RTRSharedMemClientConnection_Eli&);
		// ENSURE : canAcceptMoreClients()
		// _TAG04 Client management
	
// Static functions
	inline static unsigned long headerBytes(unsigned int maxClients);
		// Bytes used for record keeping
		// _TAG05 Static functions

	inline static unsigned long systemBytes(
			unsigned int maxClients, 
			unsigned long userBytesRequired
			);
		// The size allocated from the system.
		// ENSURE : Result == headerBytes(maxClients) + userBytesRequired
		// _TAG05 Static functions

protected:
// Data
	unsigned int _version;
	pid_t _pid;
	unsigned int _heartbeatInterval;
	char _semaphoreKey[MAX_SEMAPHORE];
	int _semaphoreNumber;
	long _timestamp;
	unsigned long _bytesOfUserData;
	unsigned long _userDataOffset;
	unsigned long _userBytesAllocated;
	int _maxClients;			
			// This can be derived from lists below
			// but we need to save it for checking
			// validity of re-attach operation. (The
			// lists are always re-initialized, 
			// overwriting the stuff we're attaching to.)
	RTRShmDLinkList<RTRSharedMemClientConnection_Eli, RTRShmDLink0> _activeClients;
	RTRShmDLinkList<RTRSharedMemClientConnection_Eli, RTRShmDLink0> _freeClients;

	RTRShmDLinkList<RTRSharedMemoryPartitionHdr_Eli, RTRShmDLink0> _partitions;

	long _padding;	// Ensures quad alignment. Leave as last member.

// Static data
	static const char *_sharedMemorySegmentData; 
		// Used by operator new (as the return value).

// Friends
	friend class RTRClientSharedMemoryRoot;
	friend class RTRSharedMemoryPartitionHdr_Eli;
	friend class RTRSharedMemoryPartitionIterator_Eli;
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&,
									const RTRSharedMemoryHdr_EliF21&);
#else
public:
	void print(FILE*);
#endif
		// Friends
};

inline 
unsigned int RTRSharedMemoryHdr_EliF21::version() const
{
	return _version;
}

inline 
pid_t RTRSharedMemoryHdr_EliF21::pid() const
{
	return _pid;
}

inline 
unsigned int RTRSharedMemoryHdr_EliF21::heartbeatInterval() const
{
	return _heartbeatInterval;
}

inline 
long RTRSharedMemoryHdr_EliF21::secondsForTimeOut() const
{
	return 
		(RTRSharedMemClientConnection_Eli::maxHandshakeLevel/2)*heartbeatInterval();
}

inline 
int RTRSharedMemoryHdr_EliF21::semaphoreNumber() const
{
	return _semaphoreNumber;
}
inline
const char *RTRSharedMemoryHdr_EliF21::semaphoreKey() const
{
	return &_semaphoreKey[0];
}

inline 
long RTRSharedMemoryHdr_EliF21::timeStamp() const
{
	return _timestamp;
}

inline 
unsigned int RTRSharedMemoryHdr_EliF21::clientCount() const
{
	return 
		((RTRSharedMemoryHdr_EliF21 *)this)->_activeClients.count((char *)this);
}

inline 
unsigned int RTRSharedMemoryHdr_EliF21::maxClients() const
{
	return _maxClients;
}

inline 
unsigned long RTRSharedMemoryHdr_EliF21::bytesOfUserData() const
{
	return _bytesOfUserData;
}

inline 
unsigned long RTRSharedMemoryHdr_EliF21::userDataOffset() const
{
	return _userDataOffset;
}

inline 
unsigned long RTRSharedMemoryHdr_EliF21::userBytesAllocated() const
{
	return _userBytesAllocated;
}

inline 
char *RTRSharedMemoryHdr_EliF21::userData() const
{
	RTPOSTCONDITION ( ((long)(this + _userDataOffset) % sizeof(char *)) == 0);
	return (char *)this + _userDataOffset;
}

inline 
RTRBOOL RTRSharedMemoryHdr_EliF21::canAcceptMoreClients() const
{
	return clientCount() < maxClients();
}

inline 
RTRBOOL RTRSharedMemoryHdr_EliF21::hasTimedOut() const
{
	return secondsSinceTimeStamp() >= secondsForTimeOut();
}

inline 
unsigned long RTRSharedMemoryHdr_EliF21::headerBytes(unsigned int maxClients)
{
	return sizeof(RTRSharedMemoryHdr_EliF21) + 
					(maxClients * sizeof(RTRSharedMemClientConnection_Eli));
}

inline 
unsigned long RTRSharedMemoryHdr_EliF21::systemBytes(
			unsigned int maxClients,
			unsigned long userBytesRequired
		)
{
	return userBytesRequired + headerBytes(maxClients);
}

#ifndef _WIN32
	// Not needed for Windows_NT

// Synopsis:
//	#include "rtr/shmhdr.h"
//
// Description:
//
// See Also:
//
// Inherits:
//

class RTRSharedMemoryHdr_EliF14
{
public:
// Attributes
	inline unsigned int version() const;
		// The version number of this header layout.
		// _TAG01 Attributes

	inline pid_t pid() const;
		// The pid of the server .
		// _TAG01 Attributes

	inline unsigned int heartbeatInterval() const;
		// The heartbeat to be used in handshaking.
		// _TAG01 Attributes

	long secondsSinceTimeStamp() const;
		// The number of seconds since this segment was timestamped by
		// the server.
		// _TAG01 Attributes

	inline long secondsForTimeOut() const;
		// The number of seconds which, when exceeded, constitutes a timeout.
		// _TAG01 Attributes

	inline key_t semaphoreKey() const;
		// The key of the semaphore to be used for obtaining
		// safe access to this segment.
		// _TAG01 Attributes

	inline int semaphoreNumber() const;
		// The number of the semaphore.
		// _TAG01 Attributes

	inline long timeStamp() const;
		// The last time the server polled this segment.
		// _TAG01 Attributes

	inline unsigned int clientCount() const;
		// The number of active clients.
		// _TAG01 Attributes

	inline unsigned int maxClients() const;
		// The maximum number of clients.
		// _TAG01 Attributes

	inline unsigned long bytesOfUserData() const;
		// The size of the available data area 
		// _TAG01 Attributes

	inline unsigned long userDataOffset() const;
		// Offset of user data from start of segment.
		// _TAG01 Attributes

	inline char *userData() const;
		// The start of the data region available for allocation.
		// ENSURE : result % sizeof(char *)) == 0
		// _TAG01 Attributes

	inline unsigned long userBytesAllocated() const;
		// _TAG01 Attributes

// State
	inline RTRBOOL canAcceptMoreClients() const;
		// ENSURE: result implies clientCount < maxClients
		// _TAG02 State
	
	inline RTRBOOL hasTimedOut() const;
		// ENSURE: result implies secondsSinceTimeStamp() >= secondsForTimeOut()
		// _TAG02 State

	RTRBOOL connectionIsAllocated(RTRSharedMemClientConnection_Eli&);
		// _TAG02 State

// Client management
	RTRSharedMemClientConnection_Eli *allocatedClient(pid_t);
		// REQUIRE : canAcceptMoreClients()
		// ENSURE : connectionIsAllocated(*result)
		// _TAG03 Client management

	void deallocateClient(RTRSharedMemClientConnection_Eli&);
		// REQUIRE : connectionIsAllocated(RTRSharedMemClientConnection_Eli&);
		// ENSURE : canAcceptMoreClients()
		// _TAG03 Client management

	
// Static functions
	inline static unsigned long headerBytes(unsigned int maxClients);
		// Bytes used for record keeping
		// _TAG04 Static functions

	inline static unsigned long systemBytes(
			unsigned int maxClients, 
			unsigned long userBytesRequired
			);
		// The size allocated from the system.
		// ENSURE : Result == headerBytes(maxClients) + userBytesRequired
		// _TAG04 Static functions

protected:
// Data
	unsigned int _version;
	pid_t _pid;
	unsigned int _heartbeatInterval;
	key_t _semaphoreKey;
	int _semaphoreNumber;
	long _timestamp;
	unsigned long _bytesOfUserData;
	unsigned long _userDataOffset;
	unsigned long _userBytesAllocated;
	int _maxClients;			
			// This can be derived from lists below
			// but we need to save it for checking
			// validity of re-attach operation. (The
			// lists are always re-initialized, 
			// overwriting the stuff we're attaching to.)
	RTRShmDLinkList<RTRSharedMemClientConnection_Eli, RTRShmDLink0> _activeClients;
	RTRShmDLinkList<RTRSharedMemClientConnection_Eli, RTRShmDLink0> _freeClients;

	RTRShmDLinkList<RTRSharedMemoryPartitionHdr_Eli, RTRShmDLink0> _partitions;

	long _padding;	// Ensures quad alignment. Leave as last member.

// Static data
	static const char *_sharedMemorySegmentData; 
		// Used by operator new (as the return value).

// Friends
	friend class RTRClientSharedMemoryRoot;
	friend class RTRSharedMemoryPartitionHdr_Eli;
	friend class RTRSharedMemoryPartitionIterator_Eli;
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&,
									const RTRSharedMemoryHdr_EliF14&);
#else
public:
	void print(FILE*);
#endif
};

//
// inlines for RTRSharedMemoryHdr_EliF14
//

inline 
unsigned int RTRSharedMemoryHdr_EliF14::version() const
{
	return _version;
}

inline 
pid_t RTRSharedMemoryHdr_EliF14::pid() const
{
	return _pid;
}

inline 
unsigned int RTRSharedMemoryHdr_EliF14::heartbeatInterval() const
{
	return _heartbeatInterval;
}

inline 
long RTRSharedMemoryHdr_EliF14::secondsForTimeOut() const
{
	return 
		(RTRSharedMemClientConnection_Eli::maxHandshakeLevel/2)*heartbeatInterval();
}

inline 
key_t RTRSharedMemoryHdr_EliF14::semaphoreKey() const
{
	return _semaphoreKey;
}

inline 
int RTRSharedMemoryHdr_EliF14::semaphoreNumber() const
{
	return _semaphoreNumber;
}

inline 
long RTRSharedMemoryHdr_EliF14::timeStamp() const
{
	return _timestamp;
}

inline 
unsigned int RTRSharedMemoryHdr_EliF14::clientCount() const
{
	return 
		((RTRSharedMemoryHdr_EliF14 *)this)->_activeClients.count((char *)this);
}

inline 
unsigned int RTRSharedMemoryHdr_EliF14::maxClients() const
{
	return _maxClients;
}

inline 
unsigned long RTRSharedMemoryHdr_EliF14::bytesOfUserData() const
{
	return _bytesOfUserData;
}

inline 
unsigned long RTRSharedMemoryHdr_EliF14::userDataOffset() const
{
	return _userDataOffset;
}

inline 
unsigned long RTRSharedMemoryHdr_EliF14::userBytesAllocated() const
{
	return _userBytesAllocated;
}

inline 
char *RTRSharedMemoryHdr_EliF14::userData() const
{
	RTPOSTCONDITION ( ((long)(this + _userDataOffset) % sizeof(char *)) == 0);
	return (char *)this + _userDataOffset;
}

inline 
RTRBOOL RTRSharedMemoryHdr_EliF14::canAcceptMoreClients() const
{
	return clientCount() < maxClients();
}

inline 
RTRBOOL RTRSharedMemoryHdr_EliF14::hasTimedOut() const
{
	return secondsSinceTimeStamp() >= secondsForTimeOut();
}

inline 
unsigned long RTRSharedMemoryHdr_EliF14::headerBytes(unsigned int maxClients)
{
	return sizeof(RTRSharedMemoryHdr_EliF14) + 
			(maxClients * sizeof(RTRSharedMemClientConnection_Eli));
}

inline 
unsigned long RTRSharedMemoryHdr_EliF14::systemBytes(
		unsigned int maxClients,
		unsigned long userBytesRequired
		)
{
	return userBytesRequired + headerBytes(maxClients);
}

#else

class RTRSharedMemoryHdr_EliF14 
	: public RTRSharedMemoryHdr_EliF21
{
		// Fake this for compiling other units
};

#endif 	// Not needed for Windows_NT

// Synopsis:
// #include"rtr/shmhdr.h"
//
// Description:
// See Also:
//	RTRSharedMemClientConnection_Eli, RTRSharedMemoryHdr_EliF14,
//	RTRSharedMemoryHdr_EliF21

class RTRSharedMemoryPartitionIterator_Eli
{
public:
// Constructor
	RTRSharedMemoryPartitionIterator_Eli(RTRSharedMemoryHdr_EliF21& header);
		// A new iterator initialized to start an iteration over the
		// partitions in the given header.
		// _TAG Constructor

	RTRSharedMemoryPartitionIterator_Eli(RTRSharedMemoryHdr_EliF14& header);
		// _TAG Constructor

// Operations
	void start();
		// _TAG01 Operations

	void finish();
		// _TAG01 Operations

	void forth();
		// _TAG01 Operations

	void back();
		// _TAG01 Operations

// State
	RTRBOOL off() const;
		// _TAG02 State

// Get
	RTRSharedMemoryPartitionHdr_Eli *item() const;
		// _TAG03 Get

protected:
// Data
	RTRSharedMemoryHdr_EliF21* _header21;
	RTRSharedMemoryHdr_EliF14* _header14;
	RTRSharedMemoryPartitionHdr_Eli *_current;

};

#endif
