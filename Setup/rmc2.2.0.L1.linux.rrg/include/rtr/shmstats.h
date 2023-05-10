//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Aug. 02 1995"
// Version: 1.0

#ifndef _shmstats_h
#define _shmstats_h

#include "rtr/shrdmem.h"
#include "rtr/shmmosvr.h"
#include "rtr/pmo.h"
#include "rtr/pmnumv.h"
#include "rtr/pmstrv.h"
#include "rtr/timercmd.h"
#include "rtr/sfevnotf.h"

// Synopsis:
// #include"rtr/shmstats.h"
//
// Description:
// See Also:
//	RTRShmMOServerMemPool
//
// Inherits:
//	RTRTimerCmd, RTRPublicObject
//

class RTRSharedMemoryStats : 
	public RTRTimerCmd,
	public RTRPublicObject
{ 
public:
// Constructor
	RTRSharedMemoryStats(
			const RTRObjectId& cntxt,
			const RTRString& nm,
			RTRSharedMemoryHdr& hdr, 
			RTRBOOL publishItself, 
			int upd_intvl = 5,
			RTRSafeEventNotifier *notif = RTRSafeEventNotifier::instance
			);
        // _TAG Constructor

	RTRSharedMemoryStats(
			RTRPublicObject& parent,
			const RTRString& nm,
			RTRSharedMemoryHdr& hdr, 
			RTRBOOL publishItself, 
			int upd_intvl = 5
			);
		// _TAG Constructor

// Destructor
	~RTRSharedMemoryStats();
        // _TAG Destructor

// Operations
	void setServer(RTRShmMOServerMemPool* s);

	void update();

// Event processing
	virtual void processTimerEvent();
        // _TAG02 Event processing

	void setOutOfSharedMemory();
	void clearOutOfSharedMemory();

protected:
	RTRSharedMemoryHdr& _shmHdr;
	RTRShmMOServerMemPool* _server;
	RTRBOOL _selfPublished;

// Header vars
	RTRPublicNumeric _pid;
	RTRPublicNumeric _heartbeatInterval;
	RTRPublicString  _semKey;
	RTRPublicNumeric _semNumber;
	RTRPublicNumeric _timeStamp;
	RTRPublicNumeric _clientCount;
	RTRPublicNumeric _maxClients;
	RTRPublicBoolean _outOfSharedMemory;

// Partition vars
	RTRPublicNumeric _size;
	RTRPublicNumeric _bytesAvailable;
	RTRPublicNumeric _bytesUsed;

// Allocator stats
	RTRPublicNumeric _elementsInUse;
	RTRPublicNumeric _elementsInFreeLists;

	RTRPublicGauge _totalItemsManaged;
	RTRPublicGauge _itemsActivityRate;

// Application stats
	RTRPublicNumeric _overheadMemoryUsed;
	RTRPublicNumeric _staticMemoryUsed;
	RTRPublicGauge _dynamicMemoryUsed;

	RTRPublicGauge _objectTotalCount;
	RTRPublicGauge _variableTotalCount;

	RTRPublicNumeric _classDescrTotalCount;
	RTRPublicNumeric _variableDescrTotalCount;

}; 


#endif
