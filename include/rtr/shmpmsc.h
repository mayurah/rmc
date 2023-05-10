//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmsc_h
#define _rtr_shmpmsc_h

#include "rtr/prxymsc.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// Synopsis:
// #include "rtr/shmpmsc.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedStringConfig.
// 
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBoolean, 
// RTRShmProxyManagedBooleanConfig, RTRShmProxyManagedCounter, 
// RTRShmProxyManagedGauge, RTRShmProxyManagedGaugeConfig, 
// RTRShmProxyManagedNumeric, RTRShmProxyManagedNumericConfig, 
// RTRShmProxyManagedNumericRange, RTRShmProxyManagedString
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedStringConfig ->
// RTRProxyManagedString -> RTRProxyManagedVariable
//

class RTRShmProxyManagedStringConfig :
	public RTRProxyManagedStringConfig
{ 
public:
// Constructor
	RTRShmProxyManagedStringConfig(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedStringConfig();
		// _TAG Destructor

// Operators
	inline RTRShmProxyManagedStringConfig& operator=(const RTRString& rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operators

	inline RTRShmProxyManagedStringConfig& operator=(const char *rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operators

// Operations -- from RTRProxyManagedStringConfig
	void set(const RTRString& newValue);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG07 Operations

	void set(const char* newValue);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG07 Operations

protected:
// Operations
	void init();
	void update();

// Data
	RTRStrConfigImpl *_varImpl;
	unsigned short _transactionLevel;

// Friends
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedStringConfig(const RTRShmProxyManagedStringConfig&);
	RTRShmProxyManagedStringConfig& operator=(const RTRShmProxyManagedStringConfig&);
}; 

inline
RTRShmProxyManagedStringConfig&
RTRShmProxyManagedStringConfig::operator=(const RTRString& rhs)
{
	set(rhs);
	return *this;
}

inline
RTRShmProxyManagedStringConfig&
RTRShmProxyManagedStringConfig::operator=(const char *rhs)
{
	set(rhs);
	return *this;
}

#endif /* _rtr_shmpmsc_h */
