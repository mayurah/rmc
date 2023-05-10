//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey, T. Zhang
// Created: "Aug. 15 1995"
// Modified: "Jul. 24 1997"
// Version: 2.0

#ifndef _shmhdr_h
#define _shmhdr_h

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif
#include "rtr/shmhdr0.h"
#include "rtr/rtstring.h"
#include "rtr/rtllist.h"
#include "rtr/portipc.h"

#define VERSION_MAGIC_NUMBER 54321
#define SHM_HDR_VERSION 2001

class RTRSharedMemoryPartitionHdr;
struct ShmPartiHdr;

// Synopsis:
// #include"rtr/shmhdr.h"
//
// Description:
// 	An instance of RTRSharedMemClientConnection maintains the state of the
//	connection between a shared memory server and one of its clients.
//	Connection objects are allocated in shared memory and modified by
//	both server and client in accordance with the hand-shaking protocol.
//
// See Also:
//	RTRSharedMemoryHdr, RTRSharedMemoryPartitionIterator, 
//	RTRServerSharedMemoryHdr
//
// Inherits:
//


struct ShmemClientConn
{
	long pid;
	long handshakeLevel;
	unsigned long nextConnection;
};

class RTRSharedMemClientConnection 
{
public:
// Constructor
	RTRSharedMemClientConnection(ShmemClientConn* s)
		:_connStore(s){};
		// From client side

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

	void markClientAlive();
		// ENSURE: handshakeLevel() <= midHandshakeLevel
		// ENSURE: handshakeLevel() >= minHandshakeLevel
        // _TAG03 Operations

	void markClientExit();
		// ENSURE: handshakeLevel() == maxHandshakeLevel + 1
        // _TAG03 Operations

// Static method  - called from server side
	static RTRBOOL clientAlive(ShmemClientConn& c) ;

	static void markServerAlive(ShmemClientConn& c);
		// ENSURE: c.handshakeLevel >= midHandshakeLevel &&
		// ENSURE: c.handshakeLevel <= maxHandshakeLevel
        // _TAG03 Operations

	static void markServerExit(ShmemClientConn&);

	static void init(ShmemClientConn*, pid_t);
		// _TAG04 Static method

	static ShmemClientConn* firstClientOf(
		unsigned long listStart, rtrUIntPtr b);
		// _TAG04 Static method

	static ShmemClientConn* nextClientOf(
		ShmemClientConn& c, rtrUIntPtr b);
		// _TAG04 Static method

	static void putFirst(
		unsigned long* listStart, ShmemClientConn*, rtrUIntPtr b);
		// _TAG04 Static method

	static void remove(
		unsigned long* listStart, ShmemClientConn*, rtrUIntPtr b);
		// _TAG04 Static method

// Static Data
	static int maxHandshakeLevel;
	static int midHandshakeLevel;
	static int minHandshakeLevel;
		// Static Data

protected:
// Data
	ShmemClientConn* _connStore;	

// Friends
	friend class RTRSharedMemoryHdr;
};

inline 
pid_t RTRSharedMemClientConnection::pid() const
{
	return _connStore->pid;
}

inline 
int RTRSharedMemClientConnection::handshakeLevel() const
{
	return _connStore->handshakeLevel;
}

inline 
RTRBOOL RTRSharedMemClientConnection::serverAlive() const 
{ 
	return _connStore->handshakeLevel > minHandshakeLevel;
}

inline 
RTRBOOL RTRSharedMemClientConnection::serverExited() const 
{ 
	return _connStore->handshakeLevel == (minHandshakeLevel - 1);
}

inline 
RTRBOOL RTRSharedMemClientConnection::clientAlive() const 
{ 
	return _connStore->handshakeLevel < maxHandshakeLevel;
}

inline 
RTRBOOL RTRSharedMemClientConnection::clientExited() const 
{ 
	return _connStore->handshakeLevel == (maxHandshakeLevel + 1);
}


class RTRSharedMemoryPartitionIterator;



struct ShmemHdr
{
	long timestamp;
	long pid;
	unsigned long heartbeatInterval;
	unsigned long semaphoreKey; // offset to a string
	long semaphoreNumber;
	unsigned long bytesOfUserData;
	unsigned long userDataOffset;
	unsigned long userBytesAllocated;
	long maxClients;			
			// This can be derived from lists below
			// but we need to save it for checking
			// validity of re-attach operation. (The
			// lists are always re-initialized, 
			// overwriting the stuff we're attaching to.)
	unsigned long activeClients;
		// List of active client connections
		// Offset to the other offset, and so on; 
	unsigned long freeClients;
		// List of free client connections
	unsigned long partitions;
		// List of partiotions
	unsigned long version;
	unsigned long versionMagic;
};

const unsigned long SHM_HDR_FIX_SIZE = sizeof(ShmemHdr) + MAX_SEMAPHORE;

// Synopsis:
// #include"rtr/shmhdr.h"
//
// Description:
// See Also:
//	RTRSharedMemClientConnection, RTRSharedMemoryPartitionIterator,

class RTRSharedMemoryHdr
{
public:
// Constructor
	RTRSharedMemoryHdr(ShmemHdr* hdr);
		// Constructor from knowing header

// Attributes
	inline ShmemHdr* store() const;

	inline unsigned int version() const;
		// The version number of this header layout.
		// _TAG02 Attributes

	inline unsigned int versionMagicNumber() const;

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

	unsigned int clientCount() const;
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

	inline rtrUIntPtr base() const;
		// The starting address of this header, used to calculate the offsets
		// inside this header, such as partition headers
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

// Query
	RTRString attachErrorText(
				unsigned int, 	// Version
				unsigned int,	// Max clients
				unsigned long	// Memory size
				);
		// The string which describes any problems prohibiting 
		// reattachment to the shared memory. If the string length
		// is zero then everything's ok.
		// Can't store state or error text in this class 
		// (it's in shared memory) so we're doing it all in one shot by
		// returning the string. If boolean "error" used, there is
		// no way to get informative text back.
		// _TAG04 Query

	RTRBOOL connectionIsAllocated(ShmemClientConn&);
        // _TAG04 Query

// Modifiy
	void stamp(long);
		// Timestamp the memory
		// _TAG05 Modify 

	void cleanConnections();
		// Server exit and clean up the connections

	void updateConnections();
		// Server check the connections

// Initialization
	void init(
			unsigned int, 	// Heartbeat interval
			unsigned long,	// Size
			const char *, 			// Semaphore key
			int, 			// Semaphore number
			unsigned int	// Max clients
			);
		// _TAG06 Initialization

// Partition management
	void putPartition(ShmPartiHdr&);
		// Put the newly allocated  partition (its header info) into list
		// _TAG07 Partition management

	unsigned long allocateBytes(unsigned long size);
		// Returns offset from this of size bytes if available otherwise 
		// returns 0.
        // _TAG07 Partition management

// Client management
	ShmemClientConn *allocatedClient(pid_t);
		// REQUIRE : canAcceptMoreClients()
		// ENSURE : connectionIsAllocated(*result)
		// _TAG08 Client management

	void deallocateClient(RTRSharedMemClientConnection&);
		// REQUIRE : connectionIsAllocated(ShmemClientConn&);
		// ENSURE : canAcceptMoreClients()
        // _TAG08 Client management
	
// Static functions
	inline static unsigned long headerBytes(unsigned int maxClients);
		// Bytes used for record keeping
		// _TAG09 Static functions

	inline static unsigned long systemBytes(
									unsigned int maxClients, 
									unsigned long userBytesRequired
									);
		// The size allocated from the system.
		// ENSURE : Result == headerBytes(maxClients) + userBytesRequired
        // _TAG09 Static functions

protected:
// Operations
	void putFree(ShmemClientConn&);
		// ENSURE : canAcceptMoreClients()

// Data
	ShmemHdr* _hdrStore;
	rtrUIntPtr _base;

// Friends
	friend class RTRServerSharedMemoryRoot;
	friend class RTRClientSharedMemoryRoot;
	friend class RTRSharedMemoryPartitionHdr;
	friend class RTRSharedMemoryPartitionIterator;
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&, const RTRSharedMemoryHdr&);
#else
public:
	void print(FILE*);
#endif
		// Friends
private:
// Don't define these:
	RTRSharedMemoryHdr(const RTRSharedMemoryHdr&);
	RTRSharedMemoryHdr & operator=(const RTRSharedMemoryHdr&);
};


inline 
rtrUIntPtr RTRSharedMemoryHdr::base() const
{
	return _base;
}

inline 
ShmemHdr* RTRSharedMemoryHdr::store() const
{
	return _hdrStore;
}

inline 
unsigned int RTRSharedMemoryHdr::version() const
{
	return _hdrStore->version;
}

inline 
unsigned int RTRSharedMemoryHdr::versionMagicNumber() const
{
	return _hdrStore->versionMagic;
}

inline 
pid_t RTRSharedMemoryHdr::pid() const
{
	return _hdrStore->pid;
}

inline 
unsigned int RTRSharedMemoryHdr::heartbeatInterval() const
{
	return _hdrStore->heartbeatInterval;
}

inline 
long RTRSharedMemoryHdr::secondsForTimeOut() const
{
	return 
		(RTRSharedMemClientConnection::maxHandshakeLevel/2)*heartbeatInterval();
}

inline 
int RTRSharedMemoryHdr::semaphoreNumber() const
{
	return _hdrStore->semaphoreNumber;
}
inline
const char *RTRSharedMemoryHdr::semaphoreKey() const
{
	return (char*)(_hdrStore->semaphoreKey+_base);
}

inline 
long RTRSharedMemoryHdr::timeStamp() const
{
	return _hdrStore->timestamp;
}

inline 
unsigned int RTRSharedMemoryHdr::maxClients() const
{
	return _hdrStore->maxClients;
}

inline 
unsigned long RTRSharedMemoryHdr::bytesOfUserData() const
{
	return _hdrStore->bytesOfUserData;
}

inline 
unsigned long RTRSharedMemoryHdr::userDataOffset() const
{
	return _hdrStore->userDataOffset;
}

inline 
unsigned long RTRSharedMemoryHdr::userBytesAllocated() const
{
	return _hdrStore->userBytesAllocated;
}

inline 
char *RTRSharedMemoryHdr::userData() const
{
	return (char *)(_hdrStore->userDataOffset + _base);
}

inline 
RTRBOOL RTRSharedMemoryHdr::canAcceptMoreClients() const
{
	return clientCount() < maxClients();
}

inline 
RTRBOOL RTRSharedMemoryHdr::hasTimedOut() const
{
	return secondsSinceTimeStamp() >= secondsForTimeOut();
}

inline 
unsigned long RTRSharedMemoryHdr::headerBytes(unsigned int maxClients)
{
	RTPRECONDITION (SHM_HDR_FIX_SIZE%4 == 0);
		// If quad alignment fail here, check MAX_SEMAPHORE 

	return SHM_HDR_FIX_SIZE + (maxClients * sizeof(ShmemClientConn));
}

inline 
unsigned long RTRSharedMemoryHdr::systemBytes(
			unsigned int maxClients,
			unsigned long userBytesRequired
		)
{
	return userBytesRequired + headerBytes(maxClients);
}

// Synopsis:
// #include"rtr/shmhdr.h"
//
// Description:
// An instance of RTRSharedMemoryPartitionIterator is used to traverse the 
// partirion information on shared memory corresponding to the given header. 
// It is mainly  used on client side, where it acquires read lock on shared
// memory first and gets a snapshot of the server partitions.
//
// On server side, there is no need to use this class since the server is 
// the only writer, the server application can traverse the partition header 
// list directly without acquire lock (unless it is a multi-thread application). 

// See Also:
//	RTRSharedMemClientConnection, RTRSharedMemoryHdr
//

class RTRSharedMemoryPartitionIterator
{
public:
// Constructor
	RTRSharedMemoryPartitionIterator(RTRSharedMemoryHdr& header);
		// A new iterator initialized to start an iteration over the
		// partitions in the given header.
		// Note:
		// Acquiring read lock on the header is needed on client side
		// _TAG Constructor

// Operations
	void start();
		// _TAG01 Operations

	void forth();
        // _TAG01 Operations

// State
	RTRBOOL off() const;
		// _TAG02 State

// Get
	ShmPartiHdr *item() const;
		// _TAG03 Get

protected:
// Data
	ShmPartiHdr* _current;
	RTRSharedMemoryHdr& _header;

};

#endif
