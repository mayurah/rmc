//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "May. 14 1997"
// Version: 1.0

#ifndef _rtr_moddict_h
#define _rtr_moddict_h

#include "rtr/objid.h"
#include "rtr/rthshtbl.h"
#include "rtr/lock.h"

#ifndef _RDEV_NO_STL_

#else
	#include <stdio.h>
#endif

class RTRMOClassDescription;
class RTRMVariableDescription;
class RTRMOClassDescrIterator;
class RTRManagedMemAllocator;
class RTRDescDictImplPub;

//
// Synopsis:
// #include "rtr/moddict.h"
//
// Description:
// 	A RTRMODescrDictionary is both a place holder and factory in that...
// 
// See Also:
//
// Inherits:
//	RTRLockableObj
//

class RTRMODescrDictionary
	: public RTRLockableObj
{ 
public:
	RTRMODescrDictionary(const RTRObjectId& id, RTRBOOL dfltPub = RTRTRUE );
		// _TAG Constructor

// Destructor
	virtual ~RTRMODescrDictionary();
		// _TAG Destructor

// Identity
	inline const RTRObjectId& instanceId() const;
		// _TAG01 Identity

// Operations
	RTRMOClassDescription& classDescription(const RTRObjectId&, const char* =0);
		// <Synchronized>
		// _TAG02 Operations

	RTRMVariableDescription& variableDescription(const RTRObjectId& cId, const char* name, char t, const char* def = 0);
		// <Synchronized>
		// _TAG02 Operations

// Access - sequential
	RTRMOClassDescrIterator classDescrIterator() const;
		// _TAG04 Access - Sequential

// Access - random
	RTRMOClassDescription* classDescrById(const char* cId)  const;
		// Not use RTRObjectId to avoid call its constructor - performance 
		// _TAG03 Access - Random

	RTRMOClassDescription* classDescrById(const RTRObjectId& cId)  const;
		// _TAG03 Access - Random

	RTRMVariableDescription* variableDescrByName(const RTRObjectId& cId, const char* name);
		// _TAG03 Access - Random

// Private implementation
	void cleanUpImplPub(RTRManagedMemAllocator&);
		// Don't ask
		// _TAG04 Private implementation

	RTRBOOL initImplPub(RTRManagedMemAllocator&);
		// Don't ask
		// _TAG04 Private implementation

	RTRDescDictImplPub* storeImplPub(RTRManagedMemAllocator&) const;
		// Don't ask
		// _TAG04 Private implementation

// Static data
	static int estTotalClassDescrps;
		// Estimated total class descriptions in the dictionary
		// _TAG04 Static data

protected:
	void putClassDescr(const RTRMOClassDescription& cd) ;
	void removeClassDescr(const RTRMOClassDescription& cd) ;

// Data
	RTRObjectId _instanceId;
		// Using hashtable for performance
	RTRHashTable<RTRObjectId, RTRMOClassDescription>* _classDescrps;
	RTRHashTableIterator<RTRObjectId, RTRMOClassDescription>* _iterator;
	RTRDescDictImplPub* _storeImplPub;
		// This is for publishing 

// Friends
	friend class RTRMOClassDescription;
	friend class RTRMOClassDescrIterator;
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream& os, const RTRMODescrDictionary& );
#else
public:
	void print(FILE* os);
#endif
private:
// Don't implement
	RTRMODescrDictionary(const RTRMODescrDictionary&);
	RTRMODescrDictionary& operator=(const RTRMODescrDictionary&);
}; 


inline const RTRObjectId& RTRMODescrDictionary::instanceId() const
{
	return _instanceId;
}

// Synopsis:
// #include "rtr/moddict.h"
//
// Description:
//
// See Also:
//	RTRMODescrDictionary
//
// Inherits:
//

class RTRMOClassDescrIterator
{
public:
// Constructor
	RTRMOClassDescrIterator(RTRMODescrDictionary& c);
		// _TAG Constructor

// Destructor
	~RTRMOClassDescrIterator(){};
		// _TAG Destructor

// State
	RTRBOOL off() const;
		// Is this iteration complete?
		// _TAG01 State

	RTRBOOL empty() const;
		// Are there no class descr available via this iterator?
		// ENSURE: result implies count() == 0
		// _TAG01 State

// Attributes
	int count() const;
		// _TAG02 Attributes

// Access
	RTRMOClassDescription& item() const;
		// The current item in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void forth();
		// Continue the current iteration from start() to finish().
		// REQUIRE: !off()
		// _TAG04 Operations

protected:
// Data
	RTRHashTableIterator<RTRObjectId, RTRMOClassDescription> _iterator;
};

class RTRMasterDictIterator;

//
// Synopsis:
// #include "rtr/glbmodd.h"
//
// Description:
// RTRMasterDictionary is a utility class which keeps a list of 
// RTRMODescrDictionary instances distinguished by their identifier.
// Dictionaries from different naming space can be added to or removed from 
// this by an application, and they are independent to each other with their 
// contents. 
// 
// 
// See Also:
//	RTRMODescrDictionary
//
// Inherits:
//	RTRLockableObj
//

class RTRMasterDictionary
	: public RTRLockableObj
{
public:
// Constructor
	RTRMasterDictionary();

// Desctructor
	~RTRMasterDictionary();

// Query
	RTRMODescrDictionary* dictionaryById(const RTRObjectId& id) const;

// State
	RTRBOOL hasDictionary(const RTRObjectId& id) const;

// Operation
	RTRMODescrDictionary& dictionary(const RTRObjectId& id);
		// <Synchronized>

	RTRMasterDictIterator dictionaryIterator();

protected:
// Utility
	void add(RTRMODescrDictionary&);
		// <Synchronized>

	void remove(RTRMODescrDictionary&);
		// <Synchronized>

// Data
	RTRLinkedList<RTRMODescrDictionary> _dictionaries;
	friend class RTRMasterDictIterator;
	friend class RTRMODescrDictionary;
};

class RTRMasterDictIterator
{
public:
// Constructor
	RTRMasterDictIterator(RTRMasterDictionary& md):_context(md){};
		// _TAG Constructor

// Attributes
	int count() const;
		// The number of dictionaries available via this iterator.
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
	RTRMODescrDictionary& item() const;
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
	RTRMasterDictionary& _context; 
};

#endif
