//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.28"
// Version: 1.0

#ifndef _rtr_shmpmsc0_h
#define _rtr_shmpmsc0_h

#include "rtr/prxymsc.h"
#include "rtr/shmmvar.h"
#include "rtr/shmpmvh0.h"

class RTRShmProxyManagedObject_EliF21;
class RTRShmProxyManagedObject_Mdk10;

// Synopsis:
// #include "rtr/shmpmsc0.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedStringConfig.
// 
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedCounter_EliF21, 
// RTRShmProxyManagedGauge_EliF21, RTRShmProxyManagedNumeric_EliF21, 
// RTRShmProxyManagedNumericConfig_EliF21, 
// RTRShmProxyManagedNumericRange_EliF21, RTRShmProxyManagedString_EliF21
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedStringConfig ->
// RTRProxyManagedString -> RTRProxyManagedVariable
//

class RTRShmProxyManagedStringConfig_EliF21 :
	public RTRProxyManagedStringConfig
{ 
public:
// Constructor
	RTRShmProxyManagedStringConfig_EliF21(
			RTRShmProxyManagedObject_EliF21&,
			RTRShmProxyManagedVariableHandle_EliF21&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedStringConfig_EliF21();
		// _TAG Destructor

// Operators
	inline RTRShmProxyManagedStringConfig_EliF21& operator=(const RTRString& rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operators

	inline RTRShmProxyManagedStringConfig_EliF21& operator=(const char *rhs);
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
	RTRShmMStringConfig_EliF21 *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_EliF21;

private:
// Don't implement
	RTRShmProxyManagedStringConfig_EliF21(const RTRShmProxyManagedStringConfig_EliF21&);
	RTRShmProxyManagedStringConfig_EliF21& operator=(const RTRShmProxyManagedStringConfig_EliF21&);
}; 

inline
RTRShmProxyManagedStringConfig_EliF21&
RTRShmProxyManagedStringConfig_EliF21::operator=(const RTRString& rhs)
{
	set(rhs);
	return *this;
}

inline
RTRShmProxyManagedStringConfig_EliF21&
RTRShmProxyManagedStringConfig_EliF21::operator=(const char *rhs)
{
	set(rhs);
	return *this;
}


class RTRShmProxyManagedStringConfig_Mdk10 :
	public RTRProxyManagedStringConfig
{ 
public:
// Constructor
	RTRShmProxyManagedStringConfig_Mdk10(
			RTRShmProxyManagedObject_Mdk10&,
			RTRShmProxyManagedVariableHandle_Mdk10&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedStringConfig_Mdk10();
		// _TAG Destructor

// Operators
	inline RTRShmProxyManagedStringConfig_Mdk10& operator=(const RTRString& rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operators

	inline RTRShmProxyManagedStringConfig_Mdk10& operator=(const char *rhs);
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
	RTRShmMStringConfig *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_Mdk10;

private:
// Don't implement
	RTRShmProxyManagedStringConfig_Mdk10(const RTRShmProxyManagedStringConfig_Mdk10&);
	RTRShmProxyManagedStringConfig_Mdk10& operator=(const RTRShmProxyManagedStringConfig_Mdk10&);
}; 

inline
RTRShmProxyManagedStringConfig_Mdk10&
RTRShmProxyManagedStringConfig_Mdk10::operator=(const RTRString& rhs)
{
	set(rhs);
	return *this;
}

inline
RTRShmProxyManagedStringConfig_Mdk10&
RTRShmProxyManagedStringConfig_Mdk10::operator=(const char *rhs)
{
	set(rhs);
	return *this;
}

#endif /* _rtr_shmpmsc0_h */
