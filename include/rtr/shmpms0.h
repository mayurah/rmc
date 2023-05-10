//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.04.27"
// Version: 1.0

#ifndef _rtr_shmpms0_h
#define _rtr_shmpms0_h

#include "rtr/prxyms.h"
#include "rtr/shmmvar.h"
#include "rtr/shmpmvh0.h"

class RTRShmProxyManagedObject_EliF21;
class RTRShmProxyManagedObject_Mdk10;

// Synopsis:
// #include "rtr/shmpms0.h"
//
// Description:
// A shared memory based implementation of a RTRProxyManagedString.
// 
// See Also:
// RTRProxyManagedVariableClient, RTRShmProxyManagedCounter_EliF21, 
// RTRShmProxyManagedGauge_EliF21, RTRShmProxyManagedNumeric_EliF21, 
// RTRShmProxyManagedNumericConfig_EliF21,
// RTRShmProxyManagedNumericRange_EliF21, RTRShmProxyManagedStringConfig_EliF21 
//
// Inherits:
// RTRShmProxyManagedVariable, RTRProxyManagedString -> RTRProxyManagedVariable
//

class RTRShmProxyManagedString_EliF21 :
	public RTRProxyManagedString
{ 
public:
// Constructor
	RTRShmProxyManagedString_EliF21(
			RTRShmProxyManagedObject_EliF21&,
			RTRShmProxyManagedVariableHandle_EliF21&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedString_EliF21();
		// _TAG Destructor

// Operators
	inline RTRShmProxyManagedString_EliF21& operator=(const RTRString& rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operators

	inline RTRShmProxyManagedString_EliF21& operator=(const char *rhs);
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
	RTRShmMString_EliF21 *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_EliF21;

private:
// Don't implement
	RTRShmProxyManagedString_EliF21(const RTRShmProxyManagedString_EliF21&);
	RTRShmProxyManagedString_EliF21& operator=(const RTRShmProxyManagedString_EliF21&);
}; 

inline
RTRShmProxyManagedString_EliF21&
RTRShmProxyManagedString_EliF21::operator=(const RTRString& rhs)
{
	set(rhs);
	return *this;
}

inline
RTRShmProxyManagedString_EliF21&
RTRShmProxyManagedString_EliF21::operator=(const char *rhs)
{
	set(rhs);
	return *this;
}


class RTRShmProxyManagedString_Mdk10 :
	public RTRProxyManagedString
{ 
public:
// Constructor
	RTRShmProxyManagedString_Mdk10(
			RTRShmProxyManagedObject_Mdk10&,
			RTRShmProxyManagedVariableHandle_Mdk10&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedString_Mdk10();
		// _TAG Destructor

// Operators
	inline RTRShmProxyManagedString_Mdk10& operator=(const RTRString& rhs);
		// REQUIRE: inSync() && !error()
		// REQUIRE: modifyEnabled()
		// _TAG06 Operators

	inline RTRShmProxyManagedString_Mdk10& operator=(const char *rhs);
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
	RTRShmMString *_varImpl;

// Friends
	friend class RTRShmProxyManagedObject_Mdk10;

private:
// Don't implement
	RTRShmProxyManagedString_Mdk10(const RTRShmProxyManagedString_Mdk10&);
	RTRShmProxyManagedString_Mdk10& operator=(const RTRShmProxyManagedString_Mdk10&);
}; 

inline
RTRShmProxyManagedString_Mdk10&
RTRShmProxyManagedString_Mdk10::operator=(const RTRString& rhs)
{
	set(rhs);
	return *this;
}

inline
RTRShmProxyManagedString_Mdk10&
RTRShmProxyManagedString_Mdk10::operator=(const char *rhs)
{
	set(rhs);
	return *this;
}

#endif /* _rtr_shmpms0_h */
