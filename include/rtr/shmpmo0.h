//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.22"
// Version: 1.0

#ifndef _rtr_shmpmo0_h
#define _rtr_shmpmo0_h

#include "rtr/prxymo.h"
#include "rtr/shmmo.h"		// RTRShmMObject_EliF21
#include "rtr/shmpmoh0.h"	// RTRShmProxyManagedObjectHandle_EliF21
#include "rtr/shmpmc0.h"	// RTRShmProxyManagedCounter_EliF21
#include "rtr/shmpmg0.h"	// RTRShmProxyManagedGauge_EliF21
#include "rtr/shmpmn0.h"	// RTRShmProxyManagedNumeric_EliF21
#include "rtr/shmpmnc0.h"	// RTRShmProxyManagedNumericConfig_EliF21
#include "rtr/shmpmnr0.h"	// RTRShmProxyManagedNumericRange_EliF21
#include "rtr/shmpms0.h"	// RTRShmProxyManagedString_EliF21
#include "rtr/shmpmsc0.h"	// RTRShmProxyManagedStringConfig_EliF21

class RTRProxyManagedObjectServer;


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

class RTRShmProxyManagedObject_EliF21 :
	public RTRProxyManagedObject
{ 
public:
// Constructor
	RTRShmProxyManagedObject_EliF21(
			const RTRProxyManagedObjectServer&,
			RTRShmProxyManagedObjectHandle_EliF21&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObject_EliF21();
		// _TAG Destructor

protected:
// Operations
	void addChildHandle(RTRProxyManagedObjectHandle&);
	void removeChildHandle(RTRProxyManagedObjectHandle&);
	void update(const char *base);
	void init(const char *base);
	void checkForRemovedVariables(const char *base);
	void checkForAddedVariables(const char *base);
	void updateVariables();

// Operations -- from RTRProxyManagedObject
	virtual void cleanUp(RTRBOOL, RTRBOOL);
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
	RTRShmProxyManagedObjectHandle_EliF21 *_shmHandle;
	int _transactionLevel;
	int _usageCounter;

// Friends
	friend class RTRShmProxyManagedObjectHandle_EliF21;
	friend class RTRShmProxyManagedCounter_EliF21;
	friend class RTRShmProxyManagedGauge_EliF21;
	friend class RTRShmProxyManagedNumeric_EliF21;
	friend class RTRShmProxyManagedNumericConfig_EliF21;
	friend class RTRShmProxyManagedNumericRange_EliF21;
	friend class RTRShmProxyManagedString_EliF21;
	friend class RTRShmProxyManagedStringConfig_EliF21;

private:
// Don't implement
	RTRShmProxyManagedObject_EliF21(const RTRShmProxyManagedObject_EliF21&);
	RTRShmProxyManagedObject_EliF21& operator=(const RTRShmProxyManagedObject_EliF21&);
}; 


class RTRShmProxyManagedObject_Mdk10 :
	public RTRProxyManagedObject
{ 
public:
// Constructor
	RTRShmProxyManagedObject_Mdk10(
			const RTRProxyManagedObjectServer&,
			RTRShmProxyManagedObjectHandle_Mdk10&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObject_Mdk10();
		// _TAG Destructor

protected:
// Operations
	void addChildHandle(RTRProxyManagedObjectHandle&);
	void removeChildHandle(RTRProxyManagedObjectHandle&);
	void update(const char *base);
	void init(const char *base);
	void checkForRemovedVariables(const char *base);
	void checkForAddedVariables(const char *base);
	void updateVariables();

// Operations -- from RTRProxyManagedObject
	virtual void cleanUp(RTRBOOL, RTRBOOL);
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
	RTRShmProxyManagedObjectHandle_Mdk10 *_shmHandle;
	int _transactionLevel;
	int _usageCounter;

// Friends
	friend class RTRShmProxyManagedObjectHandle_Mdk10;
	friend class RTRShmProxyManagedCounter_Mdk10;
	friend class RTRShmProxyManagedGauge_Mdk10;
	friend class RTRShmProxyManagedNumeric_Mdk10;
	friend class RTRShmProxyManagedNumericConfig_Mdk10;
	friend class RTRShmProxyManagedNumericRange_Mdk10;
	friend class RTRShmProxyManagedString_Mdk10;
	friend class RTRShmProxyManagedStringConfig_Mdk10;

private:
// Don't implement
	RTRShmProxyManagedObject_Mdk10(const RTRShmProxyManagedObject_Mdk10&);
	RTRShmProxyManagedObject_Mdk10& operator=(const RTRShmProxyManagedObject_Mdk10&);
}; 

#endif /* _rtr_shmpmo_h */
