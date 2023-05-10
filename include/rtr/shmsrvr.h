//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/28/98"
// Version: 1.0

#ifndef _rtr_shmsrvr_h
#define _rtr_shmsrvr_h

#include "rtr/objid.h"

class RTRServerSharedMemoryRoot;

// Synopsis:
// #include "rtr/shmsrvr.h"
//
// Description:
// RTRShmServer is a helper class which instantiates an 
// RTRServerSharedMemoryRoot.  The configuration of the
// RTRServerSharedMemoryRoot is obtained from either a config
// file or passed in from the constructor (with a minimal
// number of required arguments)..
//
// See Also:
// RTRServerSharedMemoryRoot
//
// Inherits:
//

class RTRShmServer
{
public:
// Constructor
	RTRShmServer(
			const RTRObjectId& classId,
			const RTRObjectId& context,
			const char *name,
			RTRBOOL enable=RTRTRUE
			);
		// Use RTRConfig::configDb()..
		// _TAG Constructor

	RTRShmServer(
			const RTRObjectId& context,
			const char *name,
			unsigned long sharedMemorySize,
		   	const char *sharedMemoryKey,
			const char *semaphoreKey,
			RTRBOOL enable=RTRTRUE,
			int maxClients=10,
			int numSemaphores=8
			);
		// Use arguments provided.(RTRConfigDb::configDb() is not used).
		// _TAG Constructor

// Destructor
	~RTRShmServer();
		// _TAG Destructor


// State
	inline RTRBOOL enabled() const;
		// Has the segment of shared memory been created ?
		// _TAG01 State

	RTRBOOL error() const;
		// Is this class or the RTRServerSharedMemoryRoot in
		// an error state ?
		// _TAG01 State

// Identity
	inline const RTRObjectId& instanceId() const;
		// _TAG02 Identity

// Attributes
	inline const RTRString& sharedMemoryKey() const;
		// The shared memory key.
		// _TAG03 Attributes

	inline const RTRString& semaphoreKey() const;
		// The semaphore key.
		// _TAG03 Attributes

	inline unsigned long sharedMemorySize() const;
		// The desired size of the shared memory segment (in bytes).
		// _TAG03 Attributes

	inline int maxClients() const;
		// The desired max number of allowed clients.
		// _TAG03 Attributes

	inline int numberOfSemaphores() const;
		// The number of semaphores.
		// _TAG03 Attributes

	inline const RTRString& text() const;
		// _TAG03 Attributes

	inline RTRServerSharedMemoryRoot *sharedMemory() const;
		// A reference to the RTRServerSharedMemoryRoot.
		// ENSURE: 0 implies !enabled()
		// _TAG03 Attributes

// Operations
	void enable();
		// REQUIRE: !enabled()
		// Creates an RTRServerSharedMemoryRoot.
		// ENSURE: enabled()
		// _TAG04 Operations

	void disable();
		// REQUIRE: enabled()
		// Destroys the RTRServerSharedMemoryRoot.
		// ENSURE: !enabled()
		// _TAG04 Operations

// Static data
	static unsigned long defaultSharedMemorySize;
	static int defaultMaxClients;
	static int defaultNumSemaphores;
	static RTRString sharedMemoryKeyVarName;
	static RTRString sharedMemorySizeVarName;
	static RTRString semaphoreKeyVarName;
	static RTRString maxClientsVarName;
	static RTRString numSemaphoresVarName;
		// Static data

protected:
// Utilities
	void extractConfiguration(const RTRObjectId& classId);

// Data
	RTRBOOL _error;
	RTRString _text;
	RTRServerSharedMemoryRoot *_sharedMemory;
	RTRObjectId _instanceId;
	RTRString _shmKey;
	RTRString _semKey;
	unsigned long _shmSize;
	int _numSem;
	int _maxClients;
		// Data

private:
// Do not implement
	RTRShmServer(const RTRShmServer&);
	RTRShmServer& operator=(const RTRShmServer&);
};

inline
RTRBOOL RTRShmServer::enabled() const
{
        return _sharedMemory ? RTRTRUE : RTRFALSE;
}
 
inline
const RTRString& RTRShmServer::text() const
{
        return _text;
}
 
inline
RTRServerSharedMemoryRoot *RTRShmServer::sharedMemory() const
{
        return _sharedMemory;
}

inline
const RTRObjectId& RTRShmServer::instanceId() const
{
	return _instanceId;
}

inline
const RTRString& RTRShmServer::sharedMemoryKey() const
{
	return _shmKey;
}
inline
const RTRString& RTRShmServer::semaphoreKey() const
{
	return _semKey;
}
inline
unsigned long RTRShmServer::sharedMemorySize() const
{
	return _shmSize;
}
inline
int RTRShmServer::maxClients() const
{
	return _maxClients;
}
inline
int RTRShmServer::numberOfSemaphores() const
{
	return _numSem;
}

#endif
