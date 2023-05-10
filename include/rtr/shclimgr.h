//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "Jul. 29 1997"
// Version: 1.0

#ifndef _rtr_shclimgr_h
#define _rtr_shclimgr_h

#include "rtr/cshrdmem.h"

class RTRShmProxyMgr;
class RTRShmCloneMgr;

//
// Synopsis:
// #include "rtr/shclimgr.h"
//
// Description:
// 
// See Also:
//	RTRShmCloneMgr, RTRShmProxyMgr
//
// Inherits:
//	RTRSharedMemoryClient
//

class RTRShmClientMgr :
	public RTRSharedMemoryClient
{ 
public:
// Constructor
	RTRShmClientMgr(
			const RTRObjectId& context,
			const char *name, 
			RTRClientSharedMemoryRoot&, 
			RTRBOOL readOnly = RTRFALSE,
			RTRBOOL deadEnabled = RTRFALSE,
			const char *prefix = ""
			);
		// _TAG Constructor

// Destructor
	~RTRShmClientMgr();
		// _TAG Destructor

// Attributes
	inline RTRShmProxyMgr *proxyMgr();
		// _TAG01 Attributes

	inline RTRShmCloneMgr *cloneMgr();
		// _TAG01 Attributes

	inline int runtimeVersion() const;
		// _TAG01 Attributes

// State
	RTRBOOL error() const;
		// _TAG02 State

	const char* text() const ;
		// _TAG02 State

// Event processing - RTRSharedMemoryClient
	virtual void processClientError(RTRClientSharedMemoryRoot&);
		// Log an event and cleanup.
		// _TAG03 Event processing - RTRSharedMemoryClient

	virtual void processServerUp(RTRClientSharedMemoryRoot&);
		// Log an event, initialize and update
		// _TAG03 Event processing - RTRSharedMemoryClient

	virtual void processServerExit(RTRClientSharedMemoryRoot&);
		// Log an event and cleanup.
		// _TAG03 Event processing - RTRSharedMemoryClient

	virtual void processServerInactive(RTRClientSharedMemoryRoot&);
		// Log an event and cleanup.
		// _TAG03 Event processing - RTRSharedMemoryClient 
	
	virtual void processServerRestart(RTRClientSharedMemoryRoot&);
		// Log an event and cleanup.
		// _TAG03 Event processing - RTRSharedMemoryClient

protected:
// Utilities
	void init();
	void cleanUp();

// Data
	RTRShmProxyMgr* _proxyMgr;
	RTRShmCloneMgr* _cloneMgr;
	int _rtVersion;
	RTRString _text;
	RTRBOOL _error;

	RTRClientSharedMemoryRoot& _sharedMemoryRoot;
	RTRString _prefix;
	RTRBOOL _deadEnabled;
	RTRBOOL _readOnly;
	RTRObjectId _instanceId;

// Friends
private:
// Don't implement
	RTRShmClientMgr(const RTRShmClientMgr&);
	RTRShmClientMgr& operator=(const RTRShmClientMgr&);
}; 

inline
RTRShmProxyMgr *RTRShmClientMgr::proxyMgr()
{
	return _proxyMgr;
}

inline
RTRShmCloneMgr *RTRShmClientMgr::cloneMgr()
{
	return _cloneMgr;
}

inline
int RTRShmClientMgr::runtimeVersion() const
{
	return _rtVersion;
}

#endif
