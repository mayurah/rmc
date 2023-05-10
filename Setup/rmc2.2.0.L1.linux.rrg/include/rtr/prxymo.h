//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 24 1996"
// Version: 1.0

#ifndef _rtr_prxymo_h
#define _rtr_prxymo_h

#include "rtr/prxymoc.h"
#include "rtr/prxymb.h"
#include "rtr/prxymbc.h"
#include "rtr/prxymc.h"
#include "rtr/prxymg.h"
#include "rtr/prxymgc.h"
#include "rtr/prxymn.h"
#include "rtr/prxymln.h"
#include "rtr/prxymnc.h"
#include "rtr/prxymnr.h"
#include "rtr/prxyms.h"
#include "rtr/prxymsc.h"
#include "rtr/prxyh.h"
#include "rtr/mtgc.h"
#include "rtr/lock.h"

class RTRProxyManagedObjectServer;

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// A cloned (proxy) representation of a managed object.
// RTRProxyManagedObject is an abstract base class representing application
// components which can be accessed and managed by external management
// entities. Management is accomplished by monitoring and possibly modifying
// variables made available by the application component to be managed.
//
// Managed applications are perceived by management entities as a collection of
// proxy managed objects. These objects provide some number of variables of
// interest. The exact variables provided by an instance of managed object
// depends on the type of that object. All variables conform to one of a
// limited number of types; all variable types are specializations of
// RTRProxyManagedVariable.
//
// The managed objects within an application have relationships with other
// managed objects, i.e. objects may refer to other objects. These
// relationships form one or more trees (whose nodes are objects) and can be
// of interest to management entities. Managed objects contained by other
// objects are children. Managed objects not contained by other objects are
// the roots of object trees. Given the set of roots in an application, or
// system, all other objects can be reached by traversing the trees defined
// by those roots.
//
// The instance tree represents the composition of an application as
// represented to external management entities, and provides
// the means for those entities to access and possibly
// modify variables within the application.
//
// Managed objects have an instance identifier which uniquely
// identifies that object. Managed objects also have a
// class identifier which identifies the type (semantics)
// of that object. In principle, all managed objects with a
// given class identifier (type) will provide the same set of
// variables.
//
// Application components which wish to be notified of changes in the 
// composition of a particular managed object may register with that object in 
// order to receive object level events.  To do so, they must be descendants of
// RTRProxyManagedObjectClient.
// See Also:
// RTRProxyManagedObjectClient
//
// Inherits:
// RTRMTGCObj, RTRLockableObj, RTRDLink0
//

class RTRProxyManagedObject :
	public RTRMTGCObj,
	public RTRLockableObj,
	public RTRDLink0
{ 
public:
	enum PMOState {
		Init, Normal, ManualRecovery, AutoRecovery, Dead,
		Invalid, LastValueDummy
		};
		// The state attribute values.

// Constructor
	RTRProxyManagedObject(
			const RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedObject();
		// _TAG Destructor

// Identity
	inline const RTRObjectId& instanceId() const;
		// The instance identifier of this object.
		// _TAG01 Identity

	inline const RTRString& name() const;
		// The name of this object.
		// _TAG01 Identity

	inline const RTRObjectId& classId() const;
		// The class (type) identifier of this object.
		// _TAG01 Identity

// Attributes
	inline const RTRString& description() const;
		// The description of this variable.
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes

	inline PMOState state() const;
		// The state attribute of this proxy managed object.
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes.

	inline PMOState previousState() const;
		// The previous state attribute of this proxy managed object.
		// REQUIRE: inSync() && !error()
		// _TAG02 Attributes.

	inline const RTRString& text() const;
		// The textual explanation of any error state.
		// _TAG02 Attributes

// State
	inline RTRBOOL error() const;
		// Is this proxy in an error state? If so, text() provides an
		// explanation.
		// _TAG03 State

	inline RTRBOOL inSync() const;
		// Is this proxy in sync with the server which provided it?
		// _TAG03 State

// Query
	RTRBOOL hasChild(const RTRString&) const;
		// Does the object represented by this proxy have a child
		// with the given name?
		// REQUIRE: inSync() && !error()
		// _TAG04 Query

	RTRBOOL hasVariable(const RTRString&) const;
		// Does the object represented by this proxy contain a variable
		// with the given name?
		// REQUIRE: inSync() && !error()
		// _TAG04 Query

// Access - sequential
	RTRProxyManagedVarHandleIterator variableHandles() const;
		// An iterator which provides sequential access to all variable
		// handles contained by this ProxyManagedObject.
		// REQUIRE: inSync() && !error()
		// _TAG05 Access - sequential

	RTRProxyManagedObjectHandleIterator childHandles() const;
		// An iterator which provides sequential access to all child
		// ProxyManagedObjects contained by this ProxyManagedObject.
		// REQUIRE: inSync() && !error()
		// _TAG05 Access - sequential

// Access - random
	virtual RTRObjRef<RTRProxyManagedObject> childByName(
			const RTRString& name
			) const;
		// The child, if any, which has the given name.
		// The return type is RTRProxyManagedObjectPtr
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasChild(name)
		// _TAG06 Access - random

	RTRProxyManagedVariablePtr variableByName(
			const RTRString& name
			) const;
		// The variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name)
		// _TAG06 Access - random

	RTRProxyManagedBooleanPtr booleanByName(
			const RTRString& name
			) const;
		// The boolean variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) || (
		//		variable(name)->type != Boolean &&
		//		variable(name)->type != BooleanConfig )
		// _TAG06 Access - random

	RTRProxyManagedBooleanConfigPtr booleanConfigByName(
			const RTRString& name
			) const;
		// The boolean config variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variable(name)->type != BooleanConfig
		// _TAG06 Access - random

	RTRProxyManagedCounterPtr counterByName(
			const RTRString& name
			) const;
		// The counter variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variable(name)->type != Counter
		// _TAG06 Access - random

	RTRProxyManagedGaugePtr gaugeByName(
			const RTRString& name
			) const;
		// The gauge variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) || (
		//		variable(name)->type != Gauge &&
		//		variable(name)->type != GaugeConfig )
		// _TAG06 Access - random

	RTRProxyManagedGaugeConfigPtr gaugeConfigByName(
			const RTRString& name
			) const;
		// The gauge config variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variable(name)->type != GaugeConfig
		// _TAG06 Access - random

	RTRProxyManagedNumericPtr numericByName(
			const RTRString& name
			) const;
		// The numeric variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) || (
		//		variable(name)->type != Numeric &&
		//		variable(name)->type != NumericConfig &&
		//		variable(name)->type != NumericRange &&
		//		variable(name)->type != Gauge &&
		//		variable(name)->type != GaugeConfig )
		// _TAG06 Access - random

	RTRProxyManagedLargeNumericPtr largeNumericByName(
			const RTRString& name
			) const;
		// The large numeric variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) || (
		//		variable(name)->type != LargeNumeric )
		// _TAG06 Access - random

	RTRProxyManagedNumericConfigPtr numericConfigByName(
			const RTRString& name
			) const;
		// The numeric config variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variable(name)->type != NumericConfig
		// _TAG06 Access - random

	RTRProxyManagedNumericRangePtr numericRangeByName(
			const RTRString& name
			) const;
		// The numeric parameter variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variable(name)->type != NumericRange
		// _TAG06 Access - random

	RTRProxyManagedStringPtr stringByName(
			const RTRString& name
			) const;
		// The string variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) || (
		//		variable(name)->type != String &&
		//		variable(name)->type != StringConfig )
		// _TAG06 Access - random

	RTRProxyManagedStringConfigPtr stringConfigByName(
			const RTRString& name
			) const;
		// The string config variable, if any, which has the given name.
		// REQUIRE: inSync() && !error()
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variable(name)->type != StringConfig
		// _TAG06 Access - random

// Event client management
	RTRBOOL hasClient(RTRProxyManagedObjectClient&) const;
		// Is the given client registered to receive update and state events
		// from this ProxyManagedObject.
		// _TAG07 Event client management

	void addClient(RTRProxyManagedObjectClient&);
		// Register the given client to receive update and state events from
		// this ProxyManagedObject.
		// REQUIRE: !hasClient(client)
		// ENSURE: hasClient(client)
		// _TAG07 Event client management

	void dropClient(RTRProxyManagedObjectClient&);
		// Un-register the given client to receive update events from
		// this ProxyManagedObject.
		// REQUIRE: hasClient(client)
		// ENSURE: !hasClient(client)
		// _TAG07 Event client management

// Operations - From RTRLockableObj
	virtual void lock() ;
		// Locking is implemented via the server. 
		// _TAG08 Operations - From RTRLockableObj
			 
	virtual void unlock() ;
		// _TAG08 Operations - From RTRLockableObj
						  
	virtual RTRBOOL locked() const;
		// _TAG08 Operations - From RTRLockableObj

protected:
// Access
	RTRProxyManagedVariable* variable(const RTRString&) const;

// Operations
	void removeVariable(RTRProxyManagedVariable&);
	virtual void cleanUp(RTRBOOL error, RTRBOOL useTmp);
	void setText(const RTRString&);
		// Mark this object dead and notify clients;
	virtual RTRProxyManagedBoolean* newBoolean(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;
	virtual RTRProxyManagedBooleanConfig* newBooleanConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;
	virtual RTRProxyManagedCounter* newCounter(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;
	virtual RTRProxyManagedGauge* newGauge(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;
	virtual RTRProxyManagedGaugeConfig* newGaugeConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;
	virtual RTRProxyManagedNumeric* newNumeric(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;
	virtual RTRProxyManagedLargeNumeric* newLargeNumeric(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;
	virtual RTRProxyManagedNumericConfig* newNumericConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;
	virtual RTRProxyManagedNumericRange* newNumericRange(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;
	virtual RTRProxyManagedString* newString(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;
	virtual RTRProxyManagedStringConfig* newStringConfig(
			RTRProxyManagedObject&,
			RTRProxyManagedVariableHandle&
			) const = 0;

// Event propagation
	void indicateError(RTRBOOL useTemp);
	void indicateSync();
	void indicateInfo();
	void indicateInService();
	void indicateRecovering();
	void indicateWaiting();
	void indicateDead();
	void indicateDeleted();
	void indicateChildAdded(RTRProxyManagedObjectHandle&);
	void indicateChildRemoved(RTRProxyManagedObjectHandle&);
	void indicateVarAdded(RTRProxyManagedVariableHandle&);
	void indicateVarRemoved(RTRProxyManagedVariableHandle&);

	void notifyError(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifySync(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifyInfo(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifyInService(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifyRecovering(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifyWaiting(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifyDead(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifyDeleted(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifyChildAdded(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifyChildRemoved(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifyVarAdded(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);
	void notifyVarRemoved(RTRProxyManagedObjectClient*, RTRProxyManagedObject*);

// Data
	RTRProxyManagedObjectServer *_server;
	RTRProxyManagedObjectHandle _handle;
	PMOState _state;
	PMOState _previousState;
	RTRBOOL _error;
	RTRBOOL _inSync;
	RTRString _text;
	RTRString _description;
	RTRDLinkList<RTRProxyManagedObjectHandle,RTRDLink0> _childHandles;
	RTRDLinkList<RTRProxyManagedVariableHandle,RTRDLink0> _varHandles;
	RTRDLinkList<RTRProxyManagedVariable, RTRDLink0> _variables;
	void *_notifier;

// Static data
	RTRProxyManagedObjectHandle* tmpChildHandle;
	RTRProxyManagedVariableHandle* tmpVarHandle;

// Friends
friend class RTRProxyManagedObjectServer;
friend class RTRProxyManagedVariable;
}; 

inline 
const RTRObjectId& RTRProxyManagedObject::instanceId() const
{
	return _handle.instanceId();
}

inline 
const RTRString& RTRProxyManagedObject::name() const
{
	return _handle.name();
}

inline 
const RTRObjectId& RTRProxyManagedObject::classId() const
{
	return _handle.classId();
}

inline
const RTRString& RTRProxyManagedObject::description() const
{
	RTPRECONDITION( inSync() && !error() );
	return _description;
}

inline
RTRProxyManagedObject::PMOState RTRProxyManagedObject::state() const
{
	RTPRECONDITION( inSync() && !error() );
	return _state;
}

inline
RTRProxyManagedObject::PMOState RTRProxyManagedObject::previousState() const
{
	RTPRECONDITION( inSync() && !error() );
	return _previousState;
}

inline 
const RTRString& RTRProxyManagedObject::text() const
{
	return _text;
}

inline 
RTRBOOL RTRProxyManagedObject::error() const
{
	return _error;
}

inline 
RTRBOOL RTRProxyManagedObject::inSync() const
{
	return _inSync;
}

typedef RTRObjRef<RTRProxyManagedObject> RTRProxyManagedObjectPtr;
	// RTRProxyManagedObject smart-pointer


#endif
