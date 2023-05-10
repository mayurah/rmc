//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/28/98"
// Version: 1.0

#ifndef _rtr_shmosrvr_h
#define _rtr_shmosrvr_h

#include "rtr/objid.h"
#include "rtr/rtrdefs.h"
#include "rtr/shmsrvr.h"

class RTRShmMOServerMemPool;
class RTRSharedMemoryStats;

// Synopsis:
// #include "rtr/shmosrvr.h"
//
// Description:
// RTRShmMOServer is a helper class which instatiates an
// instance of RTRServerSharedMemoryRoot (and conditionally
// RTRSharedMemoryStats) as indicated by either the config db
// or information passed in on the constructor.
//
// RTRShmMOServer utilizes a portion of the shared memory
// segment created by RTRShmServer for storing managed objects.
//
// See Also:
// RTRServerSharedMemoryRoot, RTRSharedMemoryStats,
// RTRShmServer
//
// Inherits:
//

class RTRShmMOServer
{
public:
// Constructor
	RTRShmMOServer(
			const RTRObjectId& classId,
			const RTRObjectId& context,
			const char *name,
			RTRShmServer& shm,
			RTRBOOL enable=RTRTRUE
			);
		// Use the RTRConfigDb::configDb for configuration.
		// REQUIRE: !shm.error()
		// _TAG Constructor

	RTRShmMOServer(
			const RTRObjectId& context,
			const char *name,
			RTRShmServer& shm,
			unsigned long sharedMemorySize,
			RTRBOOL enable=RTRTRUE,
			RTRBOOL enableStats=RTRFALSE
			);
		// Use the constructor arguments for configuring
		// the managed object server.
		// REQUIRE: !shm.error()
		// _TAG Constructor

// Destructor
	~RTRShmMOServer();
		// _TAG Destructor

// State
	inline RTRBOOL enabled() const;
		// Has the RTRShmMOServerMemPool been instatiated ?
		// _TAG01 State

	RTRBOOL error() const;
		// Is this class or the RTRShmMOServerMemPool in
		// an error state ?
		// _TAG01 State

// Identity
	inline const RTRObjectId& instanceId() const;
		// _TAG02 Identity

// Attributes
	inline unsigned long sharedMemorySize() const;
		// Amount of shared memory allocated for storing managed objects
		// (bytes).
		// _TAG02 Attributes

	inline int maxClients() const;
		// The maximum number of clients permitted to access the
		// shared memory segment.
		// _TAG02 Attributes

	inline const RTRString& text() const;
		// _TAG02 Attributes

	inline RTRShmMOServerMemPool *managedObjectServer() const;
		// ENSURE: 0 implies !enabled()
		// _TAG02 Attributes

	inline RTRSharedMemoryStats *memoryStats() const;
		// _TAG02 Attributes

// Operations
	void enable();
		// Create an instance of RTRShmMOServerMemPool.
		// REQUIRE: !enabled()
		// ENSURE: enabled()
		// _TAG03 Operations

	void disable();
		// Destroys an instance of RTRShmMOServerMemPool
		// REQUIRE: enabled()
		// ENSURE: !enabled()
		// _TAG03 Operations

// Static data
	static unsigned long defaultSharedMemoryMOSize;
	static RTRString sharedMemoryMOSizeVarName;
	static RTRString enableMemoryStatsVarName;
	static int updateMemoryStatsInterval;
	static RTRBOOL defaultEnableMemoryStats;
		// Static data

protected:
// Utilities
	void extractConfiguration(const RTRObjectId& classId);

// Data
	RTRBOOL _error;
	RTRString _text;
	RTRShmServer& _shmServer;
	RTRShmMOServerMemPool *_moServer;
	RTRSharedMemoryStats *_stats;
	RTRBOOL _enableStats;
	RTRObjectId _instanceId;
	unsigned long _moSize;
		// Data

private:
// Do not implement
	RTRShmMOServer(const RTRShmMOServer&);
	RTRShmMOServer& operator=(const RTRShmMOServer&);
};

inline
RTRBOOL RTRShmMOServer::enabled() const
{
        return _moServer ? RTRTRUE : RTRFALSE;
}
 
inline
const RTRString& RTRShmMOServer::text() const
{
        return _text;
}
 
inline
RTRShmMOServerMemPool *RTRShmMOServer::managedObjectServer() const
{
        return _moServer;
}

inline
RTRSharedMemoryStats *RTRShmMOServer::memoryStats() const
{
	return _stats;
}

inline
const RTRObjectId& RTRShmMOServer::instanceId() const
{
	return _instanceId;
}

inline
unsigned long RTRShmMOServer::sharedMemorySize() const
{
	return _moSize;
}

inline
int RTRShmMOServer::maxClients() const
{
	return _shmServer.maxClients();
}

#endif
