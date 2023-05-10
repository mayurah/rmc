//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 02 1995"
// Version: 1.0

#ifndef _mod_h
#define _mod_h

#include "rtr/mo.h"
#include "rtr/dir.h"
#include "rtr/lock.h"

class RTRManagedObjDirClient;
class RTRManagedObjDirRootIterator;
class RTRManagedObjectDirectory;

typedef RTRManagedObjDirClient MODirClient;

class MOClosure
{
public:
	MOClosure() : moDir(0), mo(0), cat(0) {}

// event propagation
	void notifyCategoryAdded(MODirClient *c, MOClosure *closure);
	void notifyInstanceAdded(MODirClient *c, MOClosure *closure);
	void notifyInstanceRemoved(MODirClient *c, MOClosure *closure);

	RTRManagedObjectDirectory* moDir;
	RTRManagedObject* mo;
	RTRClassCategory<RTRManagedObject>* cat;
};

template<typename MODirClient, typename MOClosure>
class RTRArrayFunctionNotifier;


// Synopsis:
// #include"rtr/mod.h"
//
// Description:
//	A descendant of the template class RTRDirectory which is specific to
//	managed objects, instances of this class provide access to a list
//	of so-called root objects, i.e. managed objects with no parent.
// 
//	Typically, an application (process) has only a single static instance of
//	RTRManagedObjectDirectory. This instance is made available to application
//	components via the RTRGlobalManagedObjectDirectory class.
//	  
//	A directory consists of a set of categories. Each category within the
//	directory is a container for all objects (RTRManagedObject) in the directory
//	whose class (type) conforms to the class represented by that category.
//	   
//	Categories are allocated by the directory as needed in response to the
//	insertion of objects into the directory. As objects are added to the
//	directory, the directory allocates the necessary categories. The number
//	of categories affected depends on the class identifier of the inserted object.
//
//	An object may conform to more than one class (polymorphism) and hence may be
//	contained by more than one category within the directory. For example:
//	If the type BaseClass.SubClass is a descendant of BaseClass and object of
//	type BaseClass.SubClass is inserted into the directory, then that object
//	will be found in categories for both BaseClass and BaseClass.SubClass.
// 
//	A directory provides both random and sequential access to its constituent
//	categories. It also provides random access to objects (keyed by instance
//	identifier). Lastly,  it provides sequential access to those objects which
//	do not have parents, otherwise known as "root" objects.
//
// See Also:
//	 RTRManagedObject, RTRClassCategory<RTRManagedObject>, RTRLockableObj
//
// Inherits:
//	RTRDirectory<RTRManagedObject>
//

class RTRManagedObjectDirectory : 
	public RTRDirectory<RTRManagedObject>
{ 
public:
// Constructor
	RTRManagedObjectDirectory();
		// _TAG Constructor

// Destructor
	~RTRManagedObjectDirectory();
		// _TAG Destructor

// Attributes
	RTRManagedObjDirRootIterator rootIterator();
		// sequential access to the list of managed object instances 
		// which have no parent object.
		// _TAG01 Attributes
	
// Access
	const RTRClassCategory<RTRManagedObject>& automaticCategory(
				const RTRObjectId& cid
				) const;
		// The category with the given class (category is allocated if it
		// doesn't currently exist in the directory). 
		// ENSURE : result.classCategory() == cid
		// _TAG02 Access

// Insertion
	virtual void put(RTRManagedObject& mo);
		// Add the given interface instance to the directory.
		// REQUIRE : !has(mo.instanceId());
		// ENSURE : has(mo.instanceId());
		// ENSURE : category(mo.classId()) != NULL
		// _TAG03 Insertion

// Deletion
	virtual void remove(RTRManagedObject& mo);
		// Remove the given interface instance from the directory.
		// REQUIRE : has(mo.instanceId());
		// ENSURE : !has(mo.instanceId());
		// _TAG04 Deletion

// Client management
	void addClient(RTRManagedObjDirClient& newClient);
		// Register the given client to receive events from 
		// this directory.
		// REQUIRE : !hasClient(newClient)
		// ENSURE : hasClient(newClient)
		// _TAG05 Client management

	void dropClient(RTRManagedObjDirClient& oldClient);
		// Un-register the given client to receive events from 
		// this directory.
		// REQUIRE : hasClient(newClient)
		// ENSURE : !hasClient(oldClient)
		// _TAG05 Client management

	RTRBOOL hasClient(RTRManagedObjDirClient& client) const;
		// Is the given client registered to receive events from 
		// this directory.
		// _TAG05 Client management

protected:
// Methods
	virtual void putCategory(RTRClassCategory<RTRManagedObject>&);

// Data
	RTRDLinkList<RTRManagedObject, RTRDLinkMO> _roots;
	RTRArrayFunctionNotifier<MODirClient, MOClosure> *_notifier;

private:
		// Don't define these.
	RTRManagedObjectDirectory(const RTRManagedObjectDirectory&);
	RTRManagedObjectDirectory& operator=(const RTRManagedObjectDirectory&);

// Friends
	friend class RTRManagedObjDirRootIterator;
}; 

// Synopsis:
// #include"rtr/mod.h"
//
// Description:
//	RTRManagedObjDirClient is the base class for application components which
//	wish to register to receive events from an instance of
//	RTRManagedObjectDirectory
//
// See Also:
//	RTRManagedObjectDirectory, RTRClassCategory<RTRManagedObject>,
//	RTRManagedObject
//

class RTRManagedObjDirClient
{
public:
// Event processing
	virtual void processCategoryAdded(
			RTRManagedObjectDirectory&, RTRClassCategory<RTRManagedObject>&);
		// The given object has been added to the global directory.
		// _TAG01 Event processing

	virtual void processManagedObjectAdded(
			RTRManagedObjectDirectory&, RTRManagedObject&);
		// The given object has been added to the global directory.
		// _TAG01 Event processing

	virtual void processManagedObjectRemoved(
			RTRManagedObjectDirectory&, RTRManagedObject&) ;
		// The given object has been removed from the global directory.
		// _TAG01 Event processing
};

// Synopsis:
// #include"rtr/mod.h"
//
// Description:
// See Also:
//	RTRManagedObjectDirectory, RTRManagedObjDirClient
//

class RTRManagedObjDirRootIterator
{
public:
// Constructor
	RTRManagedObjDirRootIterator(RTRManagedObjectDirectory*);
		// _TAG Constructor

// Destructor
	~RTRManagedObjDirRootIterator();
		// _TAG Destructor

// Attributes
	int count() const;
		// The number of roots available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no root available via this iterator?
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
		// Start an iteration from the last available root.
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
	RTRManagedObjectDirectory& _context;
	RTRManagedObject* _current;
};

#endif
