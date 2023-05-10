//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "May. 14 1997"
// Version: 1.0

#ifndef _rtr_mcdes_h
#define _rtr_mcdes_h

#include "rtr/objid.h"
#include "rtr/rtllist.h"

#ifndef _RDEV_NO_STL_

#else
	#include <stdio.h>
#endif


class RTRClassDescImpl;
class RTRClassDescImplPub;
class RTRManagedMemAllocator;

class RTRMVariableDescription;
class RTRVarDescrIterator;
class RTRMODescrDictionary;

//
// Synopsis:
// #include "rtr/mcdes.h"
//
// Description:
// 
// See Also:
//
// Inherits:
//


class RTRMOClassDescription
{ 
public:
// Destructor
	~RTRMOClassDescription();
		// _TAG Destructor

// Attributes
	inline const RTRObjectId& classId() const  ;
		// _TAG01 Attributes

	inline const RTRString& definition() const ;
		// _TAG01 Attributes

	inline RTRMOClassDescription* parentDescr() const ;
		// _TAG01 Attributes
	
	inline RTRMODescrDictionary& dictionary() const ;
		// _TAG01 Attributes
// Access
	RTRVarDescrIterator varDescrIterator() const;
		// _TAG02 Access

	RTRMVariableDescription* varDescrByName(const char* name) const;
		// _TAG02 Access

// Private Implementation
	RTRClassDescImplPub* storeImplPub(RTRManagedMemAllocator&) const;
		// Don't ask.
		// _TAG08 Private Implementation

protected:
// Constructor
	RTRMOClassDescription(
			RTRMODescrDictionary& dict, 
			RTRClassDescImpl* cdAddr
			);
		 		// For client side
		 		// _TAG Constructor

	RTRMOClassDescription( 
			RTRMODescrDictionary& dict, 
			const RTRObjectId& cId, 
			const char* def, 
			RTRMOClassDescription* pDescr = 0);
				 // For server side
				 // _TAG Constructor


	void putVarDescr(RTRMVariableDescription&);

// Operations
	void update();
		// Update based on memory on client side by clone dictionary

	void cleanUpImplPub(RTRManagedMemAllocator&);
		// Clean up _storeImplPub (include its its varDescs) by allocator

	RTRBOOL initImplPub(RTRManagedMemAllocator& alc);
		// Publish the _storeImplPub with the alc

// Data
	RTRObjectId _classId;
	RTRString _definition;
	RTRLinkedList<RTRMVariableDescription> _varDescrps;
	RTRMODescrDictionary& _dictionary;
	RTRMOClassDescription* _parentDescr;
	RTRClassDescImplPub* _storeImplPub;
		// This is for publishing 
	RTRClassDescImpl* _storeImpl;
		// This is for reading

private:
// Friends
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream& os, const RTRMOClassDescription& );
#else
public:
	void print(FILE* os);
#endif
private:
	friend class RTRMVariableDescription;
	friend class RTRVarDescrIterator;
	friend class RTRMODescrDictionary;
	friend class RTRManagedMemAllocator;
	friend class RTRCloneDescriptionDict;
	friend class RTRManagedObject;

// Don't implement
	RTRMOClassDescription(const RTRMOClassDescription&);
	RTRMOClassDescription& operator=(const RTRMOClassDescription&);
}; 


inline 
const RTRObjectId& RTRMOClassDescription::classId() const  
{
	return _classId;
}

inline 
const RTRString& RTRMOClassDescription::definition() const 
{
	return _definition;
}

inline 
RTRMOClassDescription* RTRMOClassDescription::parentDescr() const 
{
	return _parentDescr;
}

inline RTRMODescrDictionary& RTRMOClassDescription::dictionary() const 
{
	return _dictionary;
}


//
// Synopsis:
// #include "rtr/mcdes.h"
//
// Description:
// 
// See Also:
//	RTRMOClassDescription
//
// Inherits:
//

class RTRVarDescrIterator
{
public:
// Constructor
	RTRVarDescrIterator(RTRMOClassDescription& c):_context(c){};
		// _TAG Constructor

// Destructor
	~RTRVarDescrIterator(){};
		// _TAG Destructor

// Attributes
	int count() const;
		// The number of variable descriptions available via this iterator.
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
	RTRMVariableDescription& item() const;
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

	void finish();
		// Start an iteration from the last available description.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void back();
		// Continue the current iteration from finish() to start().
		// REQUIRE: !off()
		// _TAG04 Operations

protected:
// Data
	RTRMOClassDescription& _context;
};

#endif
