//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.22"
// Version: 1.0

#ifndef _rtr_shmpmo_h
#define _rtr_shmpmo_h

#include "rtr/prxymo.h"
#include "rtr/moimpl.h"
#include "rtr/shmpmoh.h"	// RTRShmProxyManagedObjectHandle
#include "rtr/shmpmb.h"		// RTRShmProxyManagedBoolean
#include "rtr/shmpmbc.h"	// RTRShmProxyManagedBooleanConfig
#include "rtr/shmpmc.h"		// RTRShmProxyManagedCounter
#include "rtr/shmpmg.h"		// RTRShmProxyManagedGauge
#include "rtr/shmpmgc.h"	// RTRShmProxyManagedGaugeConfig
#include "rtr/shmpmn.h"		// RTRShmProxyManagedNumeric
#include "rtr/shmpmln.h"	// RTRShmProxyManagedLargeNumeric
#include "rtr/shmpmnc.h"	// RTRShmProxyManagedNumericConfig
#include "rtr/shmpmnr.h"	// RTRShmProxyManagedNumericRange
#include "rtr/shmpms.h"		// RTRShmProxyManagedString
#include "rtr/shmpmsc.h"	// RTRShmProxyManagedStringConfig

class RTRProxyManagedObjectServer;
class RTRMODirImpl;
class RTRMOShmemHeader;
class RTRClassDescImpl;

// Synopsis:
// #include "rtr/shmpmo.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedObject.
// 
// See Also:
// RTRProxyManagedObjectClient
//
// Inherits:
// RTRProxyManagedObject
//

class RTRShmProxyManagedObject :
	public RTRProxyManagedObject
{ 
public:
// Constructor
	RTRShmProxyManagedObject(
			const RTRProxyManagedObjectServer&,
			RTRShmProxyManagedObjectHandle&
			);
		// A root object.
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObject();
		// _TAG Destructor

protected:
// Operations
	inline RTRClassDescImpl *descImpl() const;
	void addChildHandle(RTRProxyManagedObjectHandle&);
	void removeChildHandle(RTRProxyManagedObjectHandle&);
	void update();
	void init();
	void checkForRemovedVariables();
	void checkForAddedVariables();
	void updateVariables();

// Operations -- from RTRProxyManagedObject
	virtual void cleanUp(RTRBOOL error, RTRBOOL useTmp);
	RTRProxyManagedBoolean *newBoolean(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;
	RTRProxyManagedBooleanConfig *newBooleanConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;
	RTRProxyManagedCounter *newCounter(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;
	RTRProxyManagedGauge *newGauge(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;
	RTRProxyManagedGaugeConfig *newGaugeConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;
	RTRProxyManagedNumeric *newNumeric(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;
	RTRProxyManagedLargeNumeric *newLargeNumeric(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;
	RTRProxyManagedNumericConfig *newNumericConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;
	RTRProxyManagedNumericRange *newNumericRange(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;
	RTRProxyManagedString *newString(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;
	RTRProxyManagedStringConfig *newStringConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const;

// Data
	RTRShmProxyManagedObjectHandle *_shmHandle;
	RTRClassDescImpl *_descImpl;
	unsigned short _totalVarsAdded;
	unsigned short _totalVarsRemoved;

// Friends
	friend class RTRShmProxyManagedObjectHandle;
	friend class RTRShmProxyManagedBoolean;
	friend class RTRShmProxyManagedBooleanConfig;
	friend class RTRShmProxyManagedCounter;
	friend class RTRShmProxyManagedGauge;
	friend class RTRShmProxyManagedGaugeConfig;
	friend class RTRShmProxyManagedNumeric;
	friend class RTRShmProxyManagedLargeNumeric;
	friend class RTRShmProxyManagedNumericConfig;
	friend class RTRShmProxyManagedNumericRange;
	friend class RTRShmProxyManagedString;
	friend class RTRShmProxyManagedStringConfig;

private:
// Don't implement
	RTRShmProxyManagedObject(const RTRShmProxyManagedObject&);
	RTRShmProxyManagedObject& operator=(const RTRShmProxyManagedObject&);
}; 

inline
RTRClassDescImpl *RTRShmProxyManagedObject::descImpl() const
{
	return _descImpl;
}

#endif /* _rtr_shmpmo_h */
