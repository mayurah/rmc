//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 28 1996"
// Version: 1.0

#ifndef _rtr_prxyh_h
#define _rtr_prxyh_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
    #include <string.h>
#endif

#include "rtr/objid.h"
#include "rtr/linkl.h"

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// A RTRProxyManagedObjectHandle uniquely identifies a Proxy
// Managed Object.  The handle is used to request a clone
// (proxy) of a particular managed object.
//
// See Also:
// RTRProxyManagedVariableHandle,
// RTRProxyManagedObjectHandleIterator, RTRProxyManagedVarHandleIterator
//
// Inherits:
// RTRDLink0
//

class RTRProxyManagedObjectHandle :
	public RTRDLink0
{ 
public:
// Constructor
	RTRProxyManagedObjectHandle(
			const RTRObjectId& classId,
			const RTRObjectId& instanceId,
			const RTRString& name
			);
		// _TAG Constructor

// Copy constructor
	RTRProxyManagedObjectHandle(
			const RTRProxyManagedObjectHandle&
			);
		// Copy constructor	
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedObjectHandle() {};
		// _TAG Destructor

// Attributes
	inline const RTRObjectId& classId() const;
		// The class identifier of a proxy managed object.
		// _TAG01 Attributes

	inline const RTRObjectId& instanceId() const;
		// The instance identifier of a proxy managed object.
		// _TAG01 Attributes

	inline const RTRString& name() const;
		// The name of a proxy managed object.
		// _TAG01 Attributes

protected:
// Data
	RTRObjectId _instanceId;
	RTRObjectId _classId;
	RTRString _name;

// Friends
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&, const RTRProxyManagedObjectHandle&);
#else
public:
	void print(FILE* os);
#endif
}; 


// Synopsis:
// #include"rtr/prxyh.h"
//
// Description:
// A RTRProxyManagedVariableHandle uniquely identifies a Proxy
// Managed Variable.  The handle is used to request a clone
// (proxy) of a particular managed variable.
//
// See Also:
// RTRProxyManagedObjectHandle,
// RTRProxyManagedObjectHandleIterator, RTRProxyManagedVarHandleIterator
//
// Inherits:
// RTRDLink0
//

class RTRProxyManagedVariableHandle :
	public RTRDLink0
{ 
public:
// Enumerations
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
		LargeNumeric,
		Invalid,
		LastValueDummy
	};
		// The proxy managed variable type

// Constructor
	RTRProxyManagedVariableHandle(
			const RTRString& name,
			int type
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedVariableHandle() {};
		// _TAG Destructor

// Attributes
	inline const RTRString& name() const;
		// The name of the variable.
		// _TAG01 Attributes

	inline MVType type() const;
		// The variable type.
		// _TAG01 Attributes

	inline RTRString typeString() const;
		// The variable type represented as a string.
		// _TAG01 Attributes

// Static methods
	static const char* typeToString(RTRProxyManagedVariableHandle::MVType);
		// _TAG02 Static methods

protected:
// Data
	RTRString _name;
	MVType _type;
}; 


// Synopsis:
// #include"rtr/prxyh.h"
//
// Description:
// A RTRProxyManagedObjectHandleIterator is used to sequentially traverse
// a set of Proxy Managed Object Handles.
//
// See Also:
// RTRProxyManagedObjectHandle, RTRProxyManagedVariableHandle, 
// RTRProxyManagedVarHandleIterator
//


class RTRProxyManagedObjectHandleIterator
{ 
public:
// Constructor
	RTRProxyManagedObjectHandleIterator(
			const RTRDLinkList<RTRProxyManagedObjectHandle, RTRDLink0>&
			);
		// _TAG Constructor

// Attributes
	int count() const;
		// The number of children available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete ?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no children available via this iterator ?
		// ENSURE: result implies count() == 0
		// _TAG02 State

// Access
	RTRProxyManagedObjectHandle& item() const;
		// The current item in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void finish();
		// Start an iteration from the last available child.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void forth();
		// Continue the current iteration from start() to finish().
		// REQUIRE: !off()
		// _TAG04 Operations

	void back();
		// Continue the current iteration from finish() to start().
		// REQUIRE: !off()
		// _TAG04 Operations

protected:
// Data
	const RTRDLinkList<RTRProxyManagedObjectHandle, RTRDLink0>& _list;
	RTRProxyManagedObjectHandle* _current;
}; 



// Synopsis:
// #include"rtr/prxyh.h"
//
// Description:
// A RTRProxyManagedVarHandleIterator is used to sequentially traverse
// a set of Proxy Managed Variable Handles.
//
// See Also:
// RTRProxyManagedObjectHandle, RTRProxyManagedVariableHandle, 
// RTRProxyManagedObjectHandleIterator
//
class RTRProxyManagedVarHandleIterator
{ 
public:
// Constructor
	RTRProxyManagedVarHandleIterator(
			const RTRDLinkList<RTRProxyManagedVariableHandle, RTRDLink0>&
			);
		// _TAG Constructor

// Attributes
	int count() const;
		// The number of variable available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete ?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no variable available via this iterator ?
		// ENSURE: result implies count() == 0
		// _TAG02 State

// Access
	RTRProxyManagedVariableHandle& item() const;
		// The current item in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void finish();
		// Start an iteration from the last available variable.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void forth();
		// Continue the current iteration from start() to end.
		// REQUIRE: !off()
		// _TAG04 Operations

	void back();
		// Continue the current iteration from end to start().
		// REQUIRE: !off()
		// _TAG04 Operations

protected:
// Data
	const RTRDLinkList<RTRProxyManagedVariableHandle, RTRDLink0>& _list;
	RTRProxyManagedVariableHandle* _current;
		// Data

}; 

inline 
const RTRObjectId& RTRProxyManagedObjectHandle::instanceId() const
{
	return _instanceId;
}

inline 
const RTRString& RTRProxyManagedObjectHandle::name() const
{
	return _name;
}

inline 
const RTRObjectId& RTRProxyManagedObjectHandle::classId() const
{
	return _classId;
}

inline 
const RTRString& RTRProxyManagedVariableHandle::name() const
{
	return _name;
}

inline 
RTRProxyManagedVariableHandle::MVType 
RTRProxyManagedVariableHandle::type() const
{
	return _type;
}

inline 
RTRString RTRProxyManagedVariableHandle::typeString() const
{
	return typeToString(type());
}

#endif
