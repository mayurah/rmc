//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.27"
// Version: 1.0

#ifndef _rtr_shmpms_h
#define _rtr_shmpms_h

#include "rtr/prxyms.h"
#include "rtr/mvimpl.h"
#include "rtr/shmpmvh.h"

class RTRShmProxyManagedObject;

// Synopsis:
// #include "rtr/shmpms.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedString.
// 
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedBoolean, 
// RTRShmProxyManagedBooleanConfig, RTRShmProxyManagedCounter, 
// RTRShmProxyManagedGauge, RTRShmProxyManagedGaugeConfig, 
// RTRShmProxyManagedNumeric, RTRShmProxyManagedNumericConfig,  
// RTRShmProxyManagedNumericRange, RTRShmProxyManagedStringConfig
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedString -> RTRProxyManagedVariable
//

class RTRShmProxyManagedString :
	public RTRProxyManagedString
{ 
public:
// Constructor
	RTRShmProxyManagedString(
			RTRShmProxyManagedObject&,
			RTRShmProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedString();
		// _TAG Destructor

// Operators
	inline RTRShmProxyManagedString& operator=(const RTRString& rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operators

	inline RTRShmProxyManagedString& operator=(const char *rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operators

// Operations -- from RTRProxyManagedString
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
	RTRStringImpl *_varImpl;
	unsigned short _transactionLevel;

// Friends
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedString(const RTRShmProxyManagedString&);
	RTRShmProxyManagedString& operator=(const RTRShmProxyManagedString&);
}; 

inline
RTRShmProxyManagedString&
RTRShmProxyManagedString::operator=(const RTRString& rhs)
{
	set(rhs);
	return *this;
}

inline
RTRShmProxyManagedString&
RTRShmProxyManagedString::operator=(const char *rhs)
{
	set(rhs);
	return *this;
}

#endif /* _rtr_shmpms_h */
