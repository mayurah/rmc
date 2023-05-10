//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _mo_h
#define _mo_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
	#include <string.h>
#endif

#include "rtr/mbvar.h"
#include "rtr/mbcvar.h"
#include "rtr/mcntrvar.h"
#include "rtr/mgvar.h"
#include "rtr/mgcvar.h"
#include "rtr/mnumrvar.h"
#include "rtr/mnumcvar.h"
#include "rtr/mnumvar.h"
#include "rtr/mlnumvar.h"
#include "rtr/mstrcvar.h"
#include "rtr/mstrvar.h"
#include "rtr/objid.h"
#include "rtr/rtllist.h"
#include "rtr/mcdes.h"
#include "rtr/lock.h"
#include "rtr/dlinkl.h"

class RTRMOImpl;
class RTRMOImplPub;
class RTRManagedMemAllocator;
class RTRManagedObjectClient;
class RTRManagedObjectIterator;
class RTRManagedVariableIterator;
class RTRMOChildren;
class TraversalMOTree;

// Synopsis:
//  Implementation
//
// Description:
//  A RTRDLinkMO is a link element that exists in a RTRManagedObject
//  used for storage.
//
// See Also: RTRDLink
//

class RTRDLinkMO
	: public RTRDLink
{
public:
	inline RTRDLinkMO() {};
	inline ~RTRDLinkMO() {};
};


// Synopsis:
// #include"rtr/mo.h"
//
// Description:
// RTRManagedObject is an abstract base class representing application
// components which can be accessed and managed by external management
// entities. Management is effected by monitoring and possibly modifying
// variables made available by the application component to be managed.
//
// Managed applications are perceived by management entities as a collection of
// managed objects. These objects provide some number of variables of
// interest. The exact variables provided by an instance of managed object
// depends on the type of that object. All variables conform to one of a
// limited number of types; all variable types are specializations of
// RTRManagedVariable.
//
// The managed objects within an application have relationships with other
// managed objects, i.e. objects may refer to other objects. These
// relationships form one or more trees (whose nodes are objects) and can be
// of interest to management entities. Manged objects contained by other
// objects are children. Managed objects not contained by other objects are
// the roots of object trees. Given the set of roots in an application, or
// system, all other objects can be reached by traversing the trees defined
// by those roots.
//
// The instance tree represents the composition of an application as
// represented to external management entities, and provides
// the means for those entities to access and possibly
// modify variables within the application. The application components
// which comprise the instance tree are not concerned with the nature or
// implementation of the external components.
//
// Managed objects have an instance identifier which uniquely
// identifies that object. Managed objects also have a
// class identifier which identifies the type (semantics)
// of that object. In principle, all managed objects with a
// given class identifier (type) will provide the same set of
// variables.
//
// Application components which wish to notified of changes in the composition
// of a particular managed object may register with that object in order
// to receive object level events. To do so, they must be descendants of
// RTRManagedObjectClient.
//
// RTRManagedObject is a base class which has implementation specific
// descendants. Application components should not inherit from this class
// directly.
// Managed objects are constructed with a name (which
// must be unique in the creating context), a class,
// and, optionally, a parent. The instance identifier of child objects
// is constructed by combining the instance identifier of the
// parent (if any) and the name. The object and
// variable relationships are maintained automatically
// in the appropriate constructors and destructors.
//
// The current object tree can be accessed via the global
// managed object directory, an instance of
// RTRManagedObjectDirectory available via RTRGlobalManagedObjectDirectory.
//
// See Also:
//	RTRManagedObjectDirectory, RTRGlobalManagedObjectDirectory,
//	RTRManagedVariable, RTRManagedString, RTRManagedBoolean,
//	RTRManagedCounter, RTRManagedNumeric, RTRManagedNumericRange,
//	RTRManagedGauge, RTRManagedGaugeConfig, RTRManagedBooleanConfig,
//	RTRPublicObject, RTRManagedObjectClient
//
// Inherits:
//	RTRLockableObj, RTRDLinkMO

class RTRManagedObject :
	public RTRLockableObj,
	public RTRDLinkMO
{ 
public:
	enum MOState {
		Init, Normal, ManualRecovery, AutoRecovery, Dead
		};
		// The type of managed variable

// Destructor
	virtual ~RTRManagedObject();
		// _TAG Destructor

// Identity
	inline const RTRObjectId& classId() const;
		// The class (type) identifier of this object.
		// _TAG01 Identity

	inline const RTRObjectId& instanceId() const;
		// The instance identifier of this object.
		// _TAG01 Identity

	inline const RTRString& name() const;
		// The name of this object.
		// _TAG01 Identity

// Attributes
	inline RTRManagedObject *parent() const;
		// The parent (if any) of this object.
		// _TAG02 Attributes

	inline MOState state() const;
		// The state value of this object.
		// _TAG02 Attributes

	inline MOState previousState() const;
		// The state value of this object.
		// _TAG02 Attributes

	inline const char* text() const;
		// Textual information regarding the state of this object.
		// _TAG02 Attributes

	inline const RTRString& description() const;
		// The definition of this class
		// _TAG02 Attributes

	inline RTRMODescrDictionary& MODescrDictionary() const;
	
// State
	inline RTRBOOL isInitializing() const;
		// Is this object in an initialization state?
		// _TAG03 State

	inline RTRBOOL isNormal() const;
		// Is this object in a normal state?
		// _TAG03 State

	inline RTRBOOL isRecovering() const;
		// Is this object recovering service automatically?
		// _TAG03 State

	inline RTRBOOL isWaiting() const;
		// Is this object waiting for manual recovery?
		// _TAG03 State

	inline RTRBOOL isInterrupted() const;
		// Is this object in a service interrupted state?
		// ENSURE: result == isRecovering() || isWaiting()
		// _TAG03 State

	inline RTRBOOL isDead() const;
		// Is this object in an unrecoverable error condition representing
		// non-graceful exit?
		// _TAG03 State

// Query
	RTRBOOL hasChild(const RTRString&) const;
		// Does this object have a child with the given name ?
		// _TAG04 Query

	RTRBOOL hasVariable(const RTRString&) const;
		// Does this object have a variable with the given name ?
		// _TAG04 Query

// Access - sequential
	RTRManagedObjectIterator childIterator() const;
		// The managable children of this instance.
		// _TAG05 Access - sequential

	RTRManagedVariableIterator variableIterator() const;
		// The managable variables of this instance.
		// _TAG05 Access - sequential

// Access - random
	RTRManagedObject* childByName(const char *) const;
		// The child, if any, with the given name.
		// _TAG06 Access - random

	RTRManagedVariable *variableByName(const char *) const;
		// The variable, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name)
		// _TAG06 Access - random

	RTRManagedBoolean *booleanByName(const char *) const;
		// The boolean, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) || (
		//		variableByName(name)->type != Boolean &&
		//		variableByName(name)->type != BooleanConfig )
		// _TAG06 Access - random

	RTRManagedBooleanConfig *booleanConfigByName(const char *) const;
		// The boolean config, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variableByName(name)->type != BooleanConfig
		// _TAG06 Access - random

	RTRManagedCounter *counterByName(const char *) const;
		// The counter, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variableByName(name)->type != Counter
		// _TAG06 Access - random

	RTRManagedGauge *gaugeByName(const char *) const;
		// The gauge, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) || (
		//		variableByName(name)->type != Gauge &&
		//		variableByName(name)->type != GaugeConfig )
		// _TAG06 Access - random

	RTRManagedGaugeConfig *gaugeConfigByName(const char *) const;
		// The gauge config, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variableByName(name)->type != GaugeConfig
		// _TAG06 Access - random

	RTRManagedNumeric *numericByName(const char *) const;
		// The numeric, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) || (
		//		variableByName(name)->type != Numeric &&
		//		variableByName(name)->type != NumericConfig &&
		//		variableByName(name)->type != NumericRange &&
		//		variableByName(name)->type != Gauge &&
		//		variableByName(name)->type != GaugeConfig )
		// _TAG06 Access - random
	
	RTRManagedLargeNumeric *largeNumericByName(const char *) const;
		// The large numeric, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) || (
		//		variableByName(name)->type != LargeNumeric &&
		//		variableByName(name)->type != LargeNumericConfig &&
		//		variableByName(name)->type != LargeNumericRange )
		// _TAG06 Access - random

	RTRManagedNumericConfig *numericConfigByName(const char *) const;
		// The numeric config, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variableByName(name)->type != NumericConfig
		// _TAG06 Access - random

	RTRManagedNumericRange *numericRangeByName(const char *) const;
		// The numeric range, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variableByName(name)->type != NumericRange
		// _TAG06 Access - random

	RTRManagedString *stringByName(const char *) const;
		// The string, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) || (
		//		variableByName(name)->type != String &&
		//		variableByName(name)->type != StringConfig )
		// _TAG06 Access - random

	RTRManagedStringConfig *stringConfigByName(const char *) const;
		// The string config, if any, with the given name.
		// ENSURE: result == null implies !hasVariable(name) ||
		//		variableByName(name)->type != StringConfig
		// _TAG06 Access - random

// Client management 
	void addClient(RTRManagedObjectClient& client);
		// REQUIRE : !hasClient(client);
		// ENSURE : hasClient(client);
		// _TAG07 Client management 

	void dropClient(RTRManagedObjectClient& client);
		// REQUIRE : hasClient(client);
		// ENSURE : !hasClient(client);
		// _TAG07 Client management 

	RTRBOOL hasClient(RTRManagedObjectClient& client) const;
		// Is the given client registered to receive events
		// from this managed object ?
		// _TAG07 Client management 

// Operations - From RTRLockableObj
	virtual void lock() ;
		// _TAG08 Operations - From RTRLockableObj

	virtual void unlock() ;
		// _TAG08 Operations - From RTRLockableObj

	virtual RTRBOOL locked() const;
		// _TAG08 Operations - From RTRLockableObj

// Static data
	static RTRBOOL MOLevelLockEnabled;
		// Default is false. Enabled when same object could be accessed 
		// in multiple threads
		// Static data
	static RTRLockableObj MOLevelInitLock;
		// To synchronize the initilization when MOLevelLockEnabled is true. 
		// Static data

// Private Implementation
	inline RTRMOImpl *storeImpl() const;
		// Don't ask.
		// _TAG09 Private Implementation

	inline RTRMOImplPub *storeImplPub() const;
		// Don't ask.
		// _TAG09 Private Implementation

	void cleanUpImplPub();
		// Don't ask.
		// _TAG09 Private Implementation

	RTRBOOL initImplPub(RTRManagedMemAllocator&, RTRBOOL = RTRTRUE );
		// Don't ask.
		// _TAG09 Private Implementation

// Private Event processing
	virtual void processParameterChange(RTRManagedVariable&);
		// One of the parameter variables contained by this object
		// has been changed.
		// _TAG10 Private Event processing 

	virtual void processConfigChange(RTRManagedVariable&);
		// One of the configuration variables contained by this object
		// has been changed.
		// _TAG10 Private Event processing 

protected:
// Constructor
	RTRManagedObject(
		const RTRObjectId& context,
		const char* name,
		const RTRObjectId& classId,
		const char* description = ""
	);
		// A new root object in a "Normal" state

	RTRManagedObject(
		RTRManagedObject& parentObject, 
		const char* name,
		const RTRObjectId& classId,
		const char* description = ""
	);
		// A new sub-object in a "Normal" state

	RTRManagedObject(
		const RTRObjectId& context,
		const char* name,
		const RTRObjectId& classId,
		MOState startState,
		const char* description = ""
	);
		// A new root object in the given state
//
	RTRManagedObject(
		const RTRObjectId& context,
		const char* name,
		const RTRObjectId& classId,
		MOState startState,
		bool b,
		const char* description = ""
	);
//

	RTRManagedObject(
		RTRManagedObject& parentObject, 
		const char* name,
		const RTRObjectId& classId,
		MOState startState,
		const char* description = ""
	);
		// A new sub-object in the given state

// Operations
	void markNormal( const char * txt );
		// Mark this object normal and notify clients;

	void markRecovering( const char * txt );
		// Mark this object recovering and notify clients;

	void markWaiting( const char * txt );
		// Mark this object waiting and notify clients;

	void markDead( const char * txt );
		// Mark this object dead and notify clients;

	void indicateInfo( const char * txt );
		// Notify the new info change.

	void putChild(RTRManagedObject& child);
		// REQUIRE: !hasChild(child.name())
		// ENSURE: hasChild(child.name())
		// Insert a new child of this object.

	void removeChild(RTRManagedObject& child);
		// ENSURE: !hasChild(child.name())
		// Remove a child of this object.

	void putVariable(RTRManagedVariable& var);
		// REQUIRE: !hasVariable(var.name())
		// ENSURE: hasVariable(var.name())
		// Insert a new variable of this object.

	void removeVariable(RTRManagedVariable& var);
		// ENSURE: !hasVariable(var.name())
		// Remove a variable of this object.

// Private Event propagation
	void notifyObjectInService(RTRManagedObjectClient*, RTRManagedObject*);
	void notifyObjectRecovering(RTRManagedObjectClient*, RTRManagedObject*);
	void notifyObjectWaiting(RTRManagedObjectClient*, RTRManagedObject*);
	void notifyObjectDead(RTRManagedObjectClient*, RTRManagedObject*);
	void notifyObjectInfo(RTRManagedObjectClient*, RTRManagedObject*);
	void notifyObjectDeleted(RTRManagedObjectClient*, RTRManagedObject*);
	void notifyChildAdded(RTRManagedObjectClient*, RTRManagedObject*);
	void notifyChildRemoved(RTRManagedObjectClient*, RTRManagedObject*);
	void notifyVariableAdded(RTRManagedObjectClient*, RTRManagedObject*);
	void notifyVariableRemoved(RTRManagedObjectClient*, RTRManagedObject*);

// Data
	RTRObjectId _instanceId;
	MOState _state;
	MOState _previousState;
	RTRString _name;
	RTRString _text;
	RTRMOClassDescription& _classDesc;
	RTRManagedObject *_parent;
	RTRMOChildren *_children;
	RTRDLinkList<RTRManagedVariable, RTRDLinkMV> _variables;
	void *_storeImpl;	// Initialized by implementation
				// Hides import mechanism 
				// (e.g. from shared memory).
				// Use void* for backward compatibility
	RTRMOImplPub *_storeImplPub;	// Initialized by implementation
				// Hides export mechanism  
				// (e.g. to shared memory).

	void *_notifier;

	RTRManagedObject *tmpObject;
	RTRManagedVariable *tmpVariable;
	
	bool _visited;

private:
		// Don't define these.
	RTRManagedObject(const RTRManagedObject&);
	RTRManagedObject& operator=(const RTRManagedObject&);

// Friends
	friend class RTRMOImplPub;
	friend class RTRManagedMemAllocator;
	friend class RTRManagedVariable;
	friend class RTRManagedVariableIterator;
	friend class RTRManagedObjectIterator;
	friend class TraversalMOTree;
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&, const RTRManagedObject&);
#else
public:
	void print(FILE* os);
#endif
}; 


// Synopsis:
// #include"rtr/mo.h"
//
// Description:
//
// See Also:
// RTRManagedObject
//
class RTRMOChildren
{
public:
	RTRDLinkList<RTRManagedObject, RTRDLinkMO> _list;
};

// Synopsis:
// #include"rtr/mo.h"
//
// Description:
// 	The abstract base class for components which wish to receive object level
// 	events.
//
// See Also:
//	RTRManagedObjectDirectory, RTRGlobalManagedObjectDirectory,
//	RTRManagedVariable, RTRManagedString, RTRManagedBoolean,
//	RTRManagedCounter, RTRManagedNumeric, RTRManagedNumericRange,
//	RTRManagedGauge, RTRManagedBooleanConfig, RTRManagedGaugeConfig,
//	RTRPublicObject
//

class RTRManagedObjectClient
{
public:
// Event processing
	virtual void processObjectDeleted(RTRManagedObject&) = 0;
		// The given managed object has been deleted.
		// _TAG01 Event processing

	virtual void processObjectInService(RTRManagedObject&);
		// The given managed object is now in a normal service state.
		// _TAG01 Event processing

	virtual void processObjectRecovering(RTRManagedObject&);
		// The given managed object is in a service interrupted state but
		// is attempting to recover normal service automatically. 
		// _TAG01 Event processing

	virtual void processObjectWaiting(RTRManagedObject&);
		// The given managed object is in a service interrupted state and
		// is waiting for manual intervention to restore normal service. 
		// _TAG01 Event processing

	virtual void processObjectDead(RTRManagedObject&);
		// The given managed object has entered an unrecoverable error state.
		// _TAG01 Event processing

	virtual void processObjectInfo(RTRManagedObject&);
		// The given managed object has changed it's informational text.
		// _TAG01 Event processing

	virtual void processChildAdded(RTRManagedObject&, RTRManagedObject& ch);
		// The given managed object has a new child.
		// _TAG01 Event processing

	virtual void processChildRemoved(RTRManagedObject&, RTRManagedObject& ch);
		// The given managed object has had a child removed.
		// _TAG01 Event processing

	virtual void processVariableAdded(RTRManagedObject&, RTRManagedVariable&);
		// The given managed object has a new variable.
		// _TAG01 Event processing

	virtual void processVariableRemoved(RTRManagedObject&, RTRManagedVariable&);
		// The given managed object has had a variable removed.
		// _TAG01 Event processing
};

// Synopsis:
// #include"rtr/mo.h"
//
// Description:
//  Stateless iteration on an object's children. Multiple instances of this 
// can be used (in a multi-thread enviroment) for read access.
//
// See Also:
// 	RTRManagedObject, RTRManagedObjectClient
//

class RTRManagedObjectIterator
{
public:
// Constructor
	RTRManagedObjectIterator(RTRManagedObject*);
		// _TAG Constructor

// Destructor
	~RTRManagedObjectIterator();
		// _TAG Destructor

// Attributes
	int count() const;
		// The number of children available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no child available via this iterator?
		// ENSURE: result implies count() == 0
		// _TAG02 State

// Access
	RTRManagedObject& item() const;
		// The current item in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration.
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
	RTRManagedObject& _context;
	RTRManagedObject* _current; 
};

// Synopsis:
// #include"rtr/mo.h"
//
// Description:
//  Stateless iteration on an object's variables. Multiple instances of this 
// can be used (in a multi-thread enviroment) for read access.
//
// See Also:
//	RTRManagedObject, RTRManagedObjectClient 
//

class RTRManagedVariableIterator
{
public:
// Constructor
	RTRManagedVariableIterator(RTRManagedObject*);
		// _TAG Constructor

// Destructor
	~RTRManagedVariableIterator();
		// _TAG Destructor

// Attributes
	int count() const;
		// The number of variables available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no variable available via this iterator?
		// ENSURE: result implies count() == 0
		// _TAG02 State

// Access
	RTRManagedVariable& item() const;
		// The current item in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void finish();
		// Start an iteration from the last available variable.
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
	RTRManagedObject& _context;
	RTRManagedVariable* _current;
		// Data
};

class TraversalMOTree
{
public:
	TraversalMOTree(RTRManagedObject* mo) : _root(mo), _total(0) {}

	~TraversalMOTree() {}

	RTRManagedObject* first();
	RTRManagedObject* next();
	bool isDone() ;
	void traverseMO();
	unsigned int getNumMoVisited() const { return _total; }

private:
	RTRManagedObject* _root;
	RTRManagedObject* _current;
	unsigned int _total;

	TraversalMOTree();
};


inline 
RTRManagedObject *RTRManagedObject::parent() const
{
	return _parent;
}

inline 
const RTRObjectId& RTRManagedObject::classId() const
{
	return _classDesc.classId();
}

inline 
const RTRString& RTRManagedObject::description() const
{
	return _classDesc.definition();
}

inline 
RTRMODescrDictionary& RTRManagedObject::MODescrDictionary() const
{
	return _classDesc.dictionary();
}

inline 
const RTRObjectId& RTRManagedObject::instanceId() const
{
	return _instanceId;
}

inline 
const RTRString& RTRManagedObject::name() const
{
	return _name;
}

inline
RTRManagedObject::MOState RTRManagedObject::state() const
{
	return _state;
}

inline
const char* RTRManagedObject::text() const
{
	return _text;
}

inline
RTRManagedObject::MOState RTRManagedObject::previousState() const
{
	return _previousState;
}

inline
RTRBOOL RTRManagedObject::isInitializing() const
{
	return _state == Init;
}

inline
RTRBOOL RTRManagedObject::isNormal() const
{
	return _state == Normal;
}

inline
RTRBOOL RTRManagedObject::isRecovering() const
{
	return _state == AutoRecovery;
}

inline
RTRBOOL RTRManagedObject::isWaiting() const
{
	return _state == ManualRecovery;
}

inline
RTRBOOL RTRManagedObject::isInterrupted() const
{
	return isWaiting() || isRecovering();
}

inline
RTRBOOL RTRManagedObject::isDead() const
{
	return _state == Dead;
}

inline 
RTRMOImpl *RTRManagedObject::storeImpl() const
{
	return (RTRMOImpl*)_storeImpl;
}

inline 
RTRMOImplPub *RTRManagedObject::storeImplPub() const
{
	return _storeImplPub;
}
#endif
