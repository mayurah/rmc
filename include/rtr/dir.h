//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 05 1995"
// Version: 1.0

#ifndef _dir_h
#define _dir_h

#ifndef _RDEV_NO_STL_
    #include <iostream>
#else
	#include <stdio.h>
    #include <string.h>
#endif

#include "rtr/platform.h"
#include "rtr/lock.h"
#include "rtr/rtllist.h"
#include "rtr/objid.h"

template<class T> class RTRClassCategoryIterator;
	// RTRClassCategoryIterator

// Synopsis:
// #include"rtr/dir.h"
//
// Description:
//	An instance of RTRClassCategory<RTRManagedObject> is a set of 
//	RTRManagedObject instances whose class identifiers all conform to the 
//	class identifier of the category.
// 
//	Categories provide random and sequential access to the instances contained
//	therein. Categories are obtained from a directory. Application components
//	do not instantiate categories directly.
//
// See Also:
//	RTRGlobalManagedObjectDirectory, RTRManagedObjectDirectory, RTRManagedObject//

template<class T> class RTRClassCategory
{
public:
// Constructor
	RTRClassCategory(const RTRObjectId& cc);
		// ENSURE : cc == categoryClass()
		// _TAG Constructor

// Destructor
	~RTRClassCategory();
		// _TAG Destructor

// Attributes
	const RTRObjectId& categoryClass() const;
		// The class of the objects in this category.
		// _TAG01 Attributes

	int count() const;
		// The number of entries in this category
		// _TAG01 Attributes

// Query
	RTRBOOL has(const RTRObjectId&) const;
		// Does the category contain an instance with the given id.
		// _TAG02 Query

// Access
	T *instance(const RTRObjectId& id) const;
		// The instance, if any, with the given id.
		// ENSURE : (result) == has(id)
		// ENSURE : !result || (result->instanceId() == id
		// _TAG03 Access

	RTRClassCategoryIterator<T> instanceIterator();
		// The list of instances in this category.
		// ENSURE : Result.count() == count()
		// _TAG03 Access

// Insertion
	void put(T& t);
		// REQUIRE : t.classId() == categoryClass()
		// REQUIRE : !has(t.instanceId())
		// ENSURE : has(t.instanceId())
		// ENSURE : instance(t.id()) == &t;
		// _TAG04 Insertion

// Removal
	void remove(T& t);
		// ENSURE : !has(t.instanceId())
		// _TAG05 Removal

protected:
// Data
	RTRObjectId _classId;
	RTRLinkedList<T> _contents;

// Friend functions
	friend class RTRClassCategoryIterator<T>;
#ifndef _RDEV_NO_STL_
	#ifndef _WIN32
		template <class S> friend std::ostream& operator<<(std::ostream&, const RTRClassCategory<T>&);
	#endif
#else
	#ifndef _WIN32
		public:
		void print(FILE* os);
	#endif
#endif
};

// Synopsis:
// #include"rtr/dir.h"
//
// Description:
// See Also:
// 	RTRClassCategory, RTRDirectory, RTRDirectoryIterator
//

template<class T> class RTRClassCategoryIterator
{
public:
// Constructor
	RTRClassCategoryIterator(RTRClassCategory<T>*);
		// _TAG Constructor

// Destructor
	~RTRClassCategoryIterator();
		// _TAG Destructor

// Attributes
	int count() const;
		// The number of instances available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no instance available via this iterator?
		// ENSURE: result implies count() == 0
		// _TAG02 State

// Access
	T& item() const;
		// The current instance in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void finish();
		// Start an iteration from the last available instance.
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
	RTRClassCategory<T>* _context;
};

template <class T> class RTRDirectoryIterator;
	// RTRDirectoryIterator

// Synopsis:
// #include"rtr/dir.h"
//
// Description:
// See Also:
//	RTRClassCategory, RTRClassCategoryIterator, RTRDirectoryIterator
//

template<class T> class RTRDirectory
	: public RTRLockableObj
{
public:
// Constructor
	RTRDirectory();
		// _TAG Constructor

// Destructor
	virtual ~RTRDirectory();
		// _TAG Destructor

// Attributes
	int categoryCount();
		// The number of categories in this directory.
		// _TAG01 Attributes

	int instanceCount();
		// The number of instances in this directory.
		// _TAG01 Attributes

// Query
	RTRBOOL hasInstance(const RTRObjectId&);
		// Does the directory contain an instance with the given instance id.
		// _TAG02 Query

	RTRBOOL hasCategory(const RTRObjectId&);
		// Does the directory contain a category with the given class id.
		// _TAG02 Query

// Access
	T *instance(const RTRObjectId& id);
		// The instance, if any, with the given id.
		// ENSURE : (result) == hasInstance(id)
		// ENSURE : !result || (result->instanceId() == id)
		// _TAG03 Access
	
	const RTRClassCategory<T> *category(const RTRObjectId& cid);
		// The category with the given class. 
		// ENSURE : (result) == hasCategory(cid)
		// ENSURE : !result || (result->categoryClass().equivalent(cid) )
		// _TAG03 Access

	RTRDirectoryIterator<T> categoryIterator();
		// Sequential access to categories in this directory.
		// _TAG03 Access

// Insertion
	virtual void put(T& t);
		// Add the given interface instance to the directory.
		// REQUIRE : !hasInstance(t.instanceId())
		// ENSURE : hasInstance(t.instanceId()) \\ 
		// for all base classes of t.classId() \\
		// { 
		//    ENSURE : hasCategory(base class) \\
		// }
		// ENSURE : instance(t.instanceId()) == &t;
		// _TAG04 Insertion

// Deletion
	virtual void remove(T& t);
		// Remove the given interface instance from the directory.
		// ENSURE : !hasInstance(t.instanceId())
		// _TAG05 Deletion

// OBSOLETE
	const RTRLinkedList< RTRClassCategory<T> >& contents() const;
		// The list of categories in this directory.
		// _TAG06 OBSOLETE

protected:
// Methods
	virtual void putCategory(RTRClassCategory<T>&);

// Data
	RTRLinkedList< RTRClassCategory<T> > _categories;

// Friend functions
	friend class RTRDirectoryIterator<T>;
#ifndef _RDEV_NO_STL_
	#ifndef _WIN32
		template <class S> friend std::ostream& operator<<(std::ostream&, const RTRDirectory<T>&);
	#endif
#else
	#ifndef _WIN32
		public:
		void print(FILE* os);
	#endif
#endif
};

// Synopsis:
// #include"rtr/dir.h"
//
// Description:
// See Also:
//	RTRClassCategory, RTRClassCategoryIterator, RTRDirectory
//

template<class T> class RTRDirectoryIterator
{
public:
// Constructor
	RTRDirectoryIterator(RTRDirectory<T>*);
		// _TAG Constructor

// Destructor
	~RTRDirectoryIterator();
		// _TAG Destructor

// Attributes
	int count() const;
		// The number of categories available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no category available via this iterator?
		// ENSURE: result implies count() == 0
		// _TAG02 State

// Access
	RTRClassCategory<T>& item() const;
		// The current category in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void finish();
		// Start an iteration from the last available category.
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
	RTRDirectory<T>* _context;
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("dir.C")
#else
#include "rtr/dir.C"
#endif
#endif

#endif
