//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 27 1996"
// Version: 1.0

#ifndef _rtr_prxymv_h
#define _rtr_prxymv_h

#include "rtr/mtgc.h"
#include "rtr/lock.h"
#include "rtr/prxyh.h"
#include "rtr/prxymvc.h"
#include "rtr/linkl.h"

class RTRProxyManagedObject;
class RTRProxyManagedBoolean;
class RTRProxyManagedBooleanConfig;
class RTRProxyManagedCounter;
class RTRProxyManagedGauge;
class RTRProxyManagedGaugeConfig;
class RTRProxyManagedNumeric;
class RTRProxyManagedLargeNumeric;
class RTRProxyManagedNumericConfig;
class RTRProxyManagedNumericRange;
class RTRProxyManagedString;
class RTRProxyManagedStringConfig;

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// A cloned (proxy) representation of an RTRManagedVariable.
// The base class for all of the proxy managed variable types.
// The cloning process could be an asynchronous process
// and so the state of the proxy variable must be checked before
// using many of the available operations (methods).
//
// Clients may register with instances of this class to
// receive notifications of variable state changes, 
// attribute changes and deletion of the variable.
//
// See Also:
// RTRProxyManagedVariableClient,
// RTRProxyManagedCounter, RTRProxyManagedGauge,
// RTRProxyManagedNumeric, RTRProxyManagedString,
// RTRProxyManagedLargeNumeric,
// RTRProxyManagedBoolean,
// RTRProxyManagedNumericRange,
// RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//
// Inherits:
// RTRMTGCObj, RTRDLink0, RTRLockableObj
//

class RTRProxyManagedVariable :
	public RTRMTGCObj,
	public RTRLockableObj,
	public RTRDLink0
{ 
public:
// Constructor
	RTRProxyManagedVariable(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedVariable();
		// _TAG Destructor

// Identify
	inline const RTRString& name() const;
		// The name of this variable.
		// _TAG01 Identify

// Attributes
	inline RTRProxyManagedObject& context() const;
		// The object which contains this variable.
		// REQUIRE: !error()
		// _TAG02 Attributes

	inline const RTRString& text() const;
		// The textual explanation of any error state.
		// _TAG02 Attributes

	inline RTRProxyManagedVariableHandle::MVType type() const;
		// The type of this variable.  Either 
		// Boolean, Numeric, Guage, String, Counter, NumericRange,
		// NumericConfig, StringConfig, BooleanConfig or GaugeConfig
		// _TAG02 Attributes

	inline const RTRString& description() const;
		// A textual description of the variable.
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes

// State
	inline RTRBOOL error() const;
		// Is this proxy in an error state? If so, text() provides an
		// explanation.
		// _TAG03 State

	inline RTRBOOL inSync() const;
		// Is this proxy in sync with the server which provided it?
		// _TAG03 State

// Transformation
	virtual RTRString toString() const = 0;
		// The value of this variable represented as a string.
		// REQUIRE: inSync() && !error()
		// _TAG04 Transformation

	inline RTRString typeString() const;
		// The variable type represented as a string.
		// _TAG04 Transformation

	operator RTRProxyManagedBoolean&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::Boolean ||
		//	type()== RTRProxyManagedVariableHandle::BooleanConfig
		// _TAG04 Transformation

	operator const RTRProxyManagedBoolean&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::Boolean ||
		//	type()== RTRProxyManagedVariableHandle::BooleanConfig
		// _TAG04 Transformation

	operator RTRProxyManagedBooleanConfig&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::BooleanConfig
		// _TAG04 Transformation

	operator const RTRProxyManagedBooleanConfig&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::BooleanConfig
		// _TAG04 Transformation

	operator RTRProxyManagedCounter&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::Counter
		// _TAG04 Transformation

	operator const RTRProxyManagedCounter&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::Counter
		// _TAG04 Transformation

	operator RTRProxyManagedGauge&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::Gauge ||
		//	type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG04 Transformation

	operator const RTRProxyManagedGauge&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::Gauge ||
		//	type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG04 Transformation

	operator RTRProxyManagedGaugeConfig&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG04 Transformation

	operator const RTRProxyManagedGaugeConfig&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG04 Transformation

	operator RTRProxyManagedNumeric&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::Numeric ||
		//	type() == RTRProxyManagedVariableHandle::NumericConfig ||
		//	type() == RTRProxyManagedVariableHandle::NumericRange ||
		//	type() == RTRProxyManagedVariableHandle::Gauge ||
		//	type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG04 Transformation

	operator const RTRProxyManagedNumeric&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::Numeric ||
		//	type() == RTRProxyManagedVariableHandle::NumericConfig ||
		//	type() == RTRProxyManagedVariableHandle::NumericRange ||
		//	type() == RTRProxyManagedVariableHandle::Gauge ||
		//	type() == RTRProxyManagedVariableHandle::GaugeConfig
		// _TAG04 Transformation

	operator RTRProxyManagedLargeNumeric&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::LargeNumeric 
		// _TAG04 Transformation

	operator const RTRProxyManagedLargeNumeric&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::LargeNumeric
		// _TAG04 Transformation

	operator RTRProxyManagedNumericConfig&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::NumericConfig
		// _TAG04 Transformation

	operator const RTRProxyManagedNumericConfig&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::NumericConfig
		// _TAG04 Transformation

	operator RTRProxyManagedNumericRange&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::NumericRange
		// _TAG04 Transformation

	operator const RTRProxyManagedNumericRange&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::NumericRange
		// _TAG04 Transformation

	operator RTRProxyManagedString&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::String ||
		//	type() == RTRProxyManagedVariableHandle::StringConfig
		// _TAG04 Transformation

	operator const RTRProxyManagedString&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::String ||
		//	type() == RTRProxyManagedVariableHandle::StringConfig
		// _TAG04 Transformation

	operator RTRProxyManagedStringConfig&();
		// REQUIRE: type() == RTRProxyManagedVariableHandle::StringConfig
		// _TAG04 Transformation

	operator const RTRProxyManagedStringConfig&() const;
		// REQUIRE: type() == RTRProxyManagedVariableHandle::StringConfig
		// _TAG04 Transformation

// Event client management
	RTRBOOL hasClient(RTRProxyManagedVariableClient&) const;
		// Is the given client registered to receive update and state events
		// from this ProxyManagedwork Variable.
		// _TAG05 Event client management

	void addClient(RTRProxyManagedVariableClient& client);
		// Register the given client to receive update and state events from
		// this ProxyManagedwork Variable.
		// REQUIRE: !hasClient(client)
		// ENSURE: hasClient(client)
		// _TAG05 Event client management

	void dropClient(RTRProxyManagedVariableClient& client);
		// Un-register the given client to receive update events from
		// this ProxyManagedwork Variable.
		// REQUIRE: hasClient(client)
		// ENSURE: !hasClient(client)
		// _TAG05 Event client management

// Operations - From RTRLockableObj
	virtual void lock() ;
		// Locking is implemented via its context object. 
		// _TAG06 Operations - From RTRLockableObj
			 
	virtual void unlock() ;
		// _TAG06 Operations - From RTRLockableObj
						  
	virtual RTRBOOL locked() const;
		// _TAG06 Operations - From RTRLockableObj

protected:
// Utilities -- event propagation
	virtual void update();
	virtual void cleanUp(RTRBOOL error, RTRBOOL useTmp);
	void indicateError(RTRBOOL useTemp);
	void indicateSync();
	void indicateUpdate();
	void indicateDeleted();

	void notifyError(RTRProxyManagedVariableClient*, RTRProxyManagedVariable*);
	void notifySync(RTRProxyManagedVariableClient*, RTRProxyManagedVariable*);
	void notifyUpdate(RTRProxyManagedVariableClient*, RTRProxyManagedVariable*);
	void notifyDeleted(RTRProxyManagedVariableClient*, RTRProxyManagedVariable*);

// Data
	RTRBOOL _error;
	RTRBOOL _inSync;
	RTRString _text;
	RTRString _description;
	RTRProxyManagedObject *_context;
	RTRProxyManagedVariableHandle _handle;
	void *_notifier;
		// Data

// Friends
friend class RTRProxyManagedObject;
}; 

inline 
const RTRString& RTRProxyManagedVariable::name() const
{
	return _handle.name();
}

inline 
RTRProxyManagedObject& RTRProxyManagedVariable::context() const
{
	RTPRECONDITION( !_error && _context );
	return (RTRProxyManagedObject&)(*_context);
}

inline 
const RTRString& RTRProxyManagedVariable::text() const
{
	return _text;
}

inline 
const RTRString& RTRProxyManagedVariable::description() const
{
	RTPRECONDITION( inSync() && !error() );
	return _description;
}

inline 
RTRProxyManagedVariableHandle::MVType RTRProxyManagedVariable::type() const
{
	return _handle.type();
}

inline 
RTRBOOL RTRProxyManagedVariable::error() const
{
	return _error;
}

inline 
RTRBOOL RTRProxyManagedVariable::inSync() const
{
	return _inSync;
}

inline 
RTRString RTRProxyManagedVariable::typeString() const
{
	return _handle.typeToString(type());
}

typedef RTRObjRef<RTRProxyManagedVariable> RTRProxyManagedVariablePtr;

#endif
