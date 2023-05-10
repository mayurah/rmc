//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _mvar_h
#define _mvar_h

#include "rtr/rtstring.h"
#include "rtr/lock.h"
#include "rtr/mvdes.h"
#include "rtr/linkl.h"

class RTRManagedObject;
class RTRManagedVariableClient;
class RTRManagedVarClientMgr;
class RTRManagedBoolean;
class RTRManagedBooleanConfig;
class RTRManagedCounter;
class RTRManagedGauge;
class RTRManagedGaugeConfig;
class RTRManagedNumeric;
class RTRManagedLargeNumeric;
class RTRManagedNumericConfig;
class RTRManagedNumericRange;
class RTRManagedString;
class RTRManagedStringConfig;
class RTRMVImpl;
class RTRMVImplPub;
class RTRManagedMemAllocator;

// Synopsis:
//  Implementation
//
// Description:
//  A RTRDLinkMV is a link element that exists in a RTRManagedVariable
//  used for storage.
//
// See Also: RTRDLink
//

class RTRDLinkMV
	: public RTRDLink
{
public:
	inline RTRDLinkMV() {};
	inline ~RTRDLinkMV() {};
};

// Synopsis:
// #include"rtr/mvar.h"
//
// Description:
// 	This is the base class for more specific types of managed
// 	variables. A managed variable has a name, type, and
// 	is contained by an instance of RTRManagedObject. The
// 	name of the variable must be unique within the context
// 	of the containing object.
//
// 	The set of supported variable types is fixed and defined
// 	by an enumeration.
//
// 	Variables may change over time and will propagate changes
// 	to registered clients.
//
// 	This class cannot be instantiated directly.
// 
// See Also:
//	RTRManagedObject, RTRManagedVariableClient,
//	RTRManagedString, RTRManagedNumeric,
//	RTRManagedLargeNumeric,
//	RTRManagedCounter, RTRManagedBoolean,
//	RTRManagedNumericRange, RTRManagedGauge,
//	RTRManagedNumericConfig, RTRManagedStringConfig,
//	RTRManagedBooleanConfig, RTRManagedGaugeConfig,
//	RTRPublicObject, RTRString
//
// Inherits:
//	RTRLockableObj, RTRDLinkMV

class RTRManagedVariable 
	: public RTRLockableObj,
	  public RTRDLinkMV
{ 
public:
	enum MVType {
		Counter,
		Numeric,
		NumericRange,
		Gauge,
		String,
		GaugeConfig,
		NumericConfig,
		StringConfig,
		Boolean,
		BooleanConfig,
		LargeNumeric
		};
		// The type of managed variable

// Destructor
	virtual ~RTRManagedVariable();
		// _TAG Destructor

// Identity
	inline const RTRString& name() const;
		// _TAG01 Identity

// Attributes
	inline MVType type() const;
		// The type of this variable.
		// _TAG02 Attributes

	inline RTRManagedObject& context() const;
		// The managed object which contains this variable.
		// _TAG02 Attributes

	inline const RTRString& description() const;
		// The definition of this variable
		// _TAG02 Attributes

// Transformation
	operator RTRManagedBoolean&() const;
		// REQUIRE : type() == Boolean ||
		//	type() == BooleanConfig
		// _TAG03 Transformation

	operator RTRManagedBooleanConfig&() const;
		// REQUIRE : type() == BooleanConfig
		// _TAG03 Transformation

	operator RTRManagedCounter&() const;
		// REQUIRE : type() == Counter
		// _TAG03 Transformation

	operator RTRManagedGauge&() const;
		// REQUIRE : type() == Gauge ||
		//	type() == GaugeConfig
		// _TAG03 Transformation

	operator RTRManagedGaugeConfig&() const;
		// REQUIRE : type() == GaugeConfig
		// _TAG03 Transformation

	operator RTRManagedNumeric&() const;
		// REQUIRE : type() == Numeric ||
		//	type() == Gauge ||
		//	type() == GaugeConfig ||
		// 	type() == NumericRange ||
		//	type() == NumericConfig
		// _TAG03 Transformation
	
	operator RTRManagedLargeNumeric&() const;
		// REQUIRE : type() == LargeNumeric
		// _TAG03 Transformation

	operator RTRManagedNumericRange&() const;
		// REQUIRE : type() == NumericRange
		// _TAG03 Transformation

	operator RTRManagedNumericConfig&() const;
		// REQUIRE : type() == NumericConfig
		// _TAG03 Transformation

	operator RTRManagedStringConfig&() const;
		// REQUIRE : type() == StringConfig
		// _TAG03 Transformation

	operator RTRManagedString&() const;
		// REQUIRE : type() == String ||
		//	type() == StringConfig
		// _TAG03 Transformation

	virtual RTRString toString() const = 0;
		// A copy of this variable's value, represented as a string.
		// _TAG03 Transformation

// Client management
	virtual void addClient(RTRManagedVariableClient& newClient);
		// Register the given client to receive events from 
		// this variable.
		// ENSURE : hasClient(newClient)
		// _TAG04 Client management

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// Un-register the given client to receive events from 
		// this variable.
		// ENSURE : !hasClient(oldClient)
		// _TAG04 Client management

	RTRBOOL hasClient(RTRManagedVariableClient& client) const;
		// Is the given client registered to receive events from 
		// this variable.
		// _TAG04 Client management

	inline RTRBOOL hasClients() const;
		// Does this variable have any clients.
		// _TAG04 Client management

// Operations - From RTRLockableObj
	virtual void lock() ;
		// _TAG05 Operations - From RTRLockableObj

	virtual void unlock() ;
		// _TAG05 Operations - From RTRLockableObj

	virtual RTRBOOL locked() const;
		// _TAG05 Operations - From RTRLockableObj

// Static data
	static RTRBOOL MVLevelLockEnabled;
		// Default is false. Enabled when an instance of variable could be 
		// accessed in multiple threads
		// _TAG06 Static data

	static RTRLockableObj MVLevelInitLock;
		// To synchronize the initilization when MVLevelLockEnabled is true. 
		// _TAG16 Static data


// Private Implementation
	inline RTRMVImpl *storeImpl() const;
		// Don't ask.
		// _TAG06 Private Implementation

	inline RTRMVImplPub *storeImplPub() const;
		// Don't ask.
		// _TAG06 Private Implementation

protected:
// Constructor
	RTRManagedVariable(
			RTRManagedObject& context,
			MVType type,
			const char *name, 
			const char *description = "" 
			);

	void putVariable();

// Private Implementation
	virtual RTRBOOL initImplPub(RTRManagedMemAllocator& ) = 0;
		// Don't ask.
		// _TAG06 Private Implementation

	virtual void cleanUpImplPub() = 0;
		// Don't ask.
		// _TAG06 Private Implementation

// Data
	RTRManagedObject& _context;
	RTRMVariableDescription& _vDescr;
	RTRManagedVarClientMgr *_clientMgr;
	void *_storeImpl;		
		// Hides import mechanism (e.g. shared memory).
	void *_storeImplPub;		
		// Hides export mechanism (e.g. shared memory).
private:
	friend class RTRMVImplPub;
	friend class RTRManagedObject;
		// For access the _vDescr

		// Don't define these.
	RTRManagedVariable(const RTRManagedVariable&);
	RTRManagedVariable& operator=(const RTRManagedVariable&);
		// Don't define
}; 

inline const RTRString& RTRManagedVariable::name() const 
{ 
	return _vDescr.name();
}

inline const RTRString& RTRManagedVariable::description() const
{ 
	return _vDescr.definition();
}

inline 
RTRManagedVariable::MVType RTRManagedVariable::type() const
{
	return (MVType)_vDescr.type();
}

inline 
RTRManagedObject& RTRManagedVariable::context() const
{
	return _context;
}

inline 
RTRBOOL RTRManagedVariable::hasClients() const
{
	return (_clientMgr) ? RTRTRUE : RTRFALSE;
}

inline 
RTRMVImpl *RTRManagedVariable::storeImpl() const
{
	return (RTRMVImpl*)_storeImpl;
}

inline 
RTRMVImplPub *RTRManagedVariable::storeImplPub() const
{
	return (RTRMVImplPub*)_storeImplPub;
}

// Synopsis:
// #include"rtr/mvar.h"
//
// Description:
// 	The base class for components which can register with
// 	a variable to receive change events from that variable.
//
// See Also:
//	RTRManagedObject, RTRManagedVariable,
//	RTRManagedString, RTRManagedNumeric,
//	RTRManagedLargeNumeric,
//	RTRManagedCounter, RTRManagedBoolean,
//	RTRManagedNumericRange, RTRManagedGauge,
//	RTRManagedNumericConfig, RTRManagedStringConfig,
//	RTRManagedBooleanConfig, RTRManagedGaugeConfig,
//	RTRPublicObject, RTRString
//

class RTRManagedVariableClient
{
public:
// Event processing
	virtual void processVariableChange(RTRManagedVariable&) = 0;
		// The given variable has changed.
		// _TAG01 Event processing

	virtual void processVariableDelete(RTRManagedVariable&) = 0;
		// The given variable has been deleted.
		// _TAG01 Event processing

};

// For compatiblity with previous generations
typedef RTRManagedVariableClient RTRMVariableClient;

#endif
