//|-------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: A. MacGaffey, T. Hansen
// Created:
// Version: 2.0
//

#ifndef _objid_h 
#define _objid_h

#ifndef _RDEV_NO_STL_
// Not include
#else
#include <stdio.h>
#endif

#include "rtr/rtrdefs.h"
#include "rtr/rtstring.h"
#include "rtr/rtllist.h"

template <class T> class RTRLinkedList;
	// RTRLinkedList

// Synopsis:
// #include"rtr/objid.h"
//
// Description:
// An object identifier. Both instance identifiers and class identifiers
// can be represented by instances of RTRObjectId
//
// See Also:
// RTRString
//

class RTRObjectId
{
public:
// Constructor
	RTRObjectId();
		// Construct a blank object id.
		// _TAG Constructor

	RTRObjectId(const RTRObjectId& cntxt, const RTRString& nm);
		// Construct an object id composed of a context and 
		// a name.  The final object id string will be
		// "<cntxt><delimiter><nm>".  cntxt and nm may be empty
		// values.
		// _TAG Constructor

	RTRObjectId(const char* value);
		// Construct an object id using the given character string.  The
		// string representation of the object id is <value>.
		// _TAG Constructor

	RTRObjectId(const char* value, unsigned int l);
		// Construct an object id using the given character string.  The
		// string representation of the object id is the first l characters
		// of <value>.
		// _TAG Constructor

	RTRObjectId(const RTRObjectId& id);
		// Copy constructor.
		// _TAG Constructor

// Destructor
	virtual ~RTRObjectId();
		// _TAG Destructor

// Attributes
	RTRString name() const;
		// The name portion of this object id.
		// ENSURE: RTRObjectId(result) == lastN(1)
		// _TAG01 Attributes

	RTRString base() const;
		// The base portion of this object id.
		// ENSURE: RTRObjectId(result) == firstN(1)
		// _TAG01 Attributes

	int numberOfElements() const;
		// The number of names which comprise this object id.
		// _TAG01 Attributes

	inline int count() const;
		// The number of characters in this object id.
		// _TAG01 Attributes

	unsigned long hash() const;
		// Hash code of this id. 
		// _TAG01 Attributes

// State
	RTRBOOL isEmpty() const;
		// Is there no value for this id?
		// _TAG02 State

// Access
	RTRLinkedList<RTRString>* lineage() const;
		// Return a list of names representing the lineage of the object id.
		// _TAG03 Access

	RTRString iTh(int i) const;
		// A new object id comprised of the iTh element of this id.
		// REQUIRE: i <= numberOfElements()
		// _TAG03 Access

// Query
	RTRBOOL isDescendant(const RTRObjectId& other) const;
		// Is this instance id a "contained" by other? 
		// ENSURE: !commonRoot(other).isEmpty()
		// _TAG04 Query

	RTRBOOL conformsTo (const RTRObjectId& other) const;
		// Is this class id a "descendant" of other? 
		// Synonym for isDescendant()
		// _TAG04 Query

// Comparison
	RTRBOOL operator==(const RTRObjectId& other) const;
		// Is this id exactly like other?
		// _TAG05 Comparison

	RTRBOOL operator!=(const RTRObjectId& other) const;
		// Is this id not equal to other?
		// _TAG05 Comparison

	RTRBOOL operator==(const RTRString& other) const;
		// Is this id exactly equal to other?
		// _TAG05 Comparison

	RTRBOOL operator==(const char *other) const;
		// Is this id exactly equal to other?
		// _TAG05 Comparison

// Transformation
	operator const char *() const;
		// _TAG06 Transformation

	RTRString string() const;
		// Return the string representation of this id.
		// _TAG06 Transformation

	RTRString delimitedString(char delimiter) const;
		// Return the string representation of this id using given delimiter 
		// in place of the default delimiter. 
		// _TAG06 Transformation

	RTRObjectId firstN(int n) const;
		// A new object id comprised of the first n elements of this id.
		// REQUIRE: n <= numberOfElements()
		// _TAG06 Transformation

	RTRObjectId lastN(int n) const;
		// A new object id comprised of the last n elements of this id.
		// REQUIRE: n <= numberOfElements()
		// _TAG06 Transformation

	RTRObjectId parent() const;
		// Return the object id for the parent object (empty if no parent)
		// ENSURE: result == firstN(numberOfElements() - 1)
		// _TAG06 Transformation

	RTRObjectId commonRoot(const RTRObjectId& other) const;
		// A new object id comprised of the portion of this object id that
		// is in common with the other object id.
		// _TAG06 Transformation

// Assignment
	RTRObjectId& operator=(const RTRObjectId& rhs);
		// ENSURE: firstN(numberOfElements()) == 
		//         rhs.firstN(rhs.numberOfElements())
		// _TAG07 Assignment

// Modication
	void set(RTRString& s, int n1, int n2);
		// Set this id to the value of "s" from index n1 to index n2 of "s". 
		// _TAG08 Modification

// OBSOLETE
	const char *to_c() const;
		// Char * representation of this string. Returns up to first
		// null value in id.
		// _TAG09 OBSOLETE

	RTRBOOL equivalent (const RTRObjectId& other) const;
		// For equality use
		//		operator==(const RTRObjectId&) for equality
		// To compare instance id with instance context
		//		conformsTo(const RTRObjectId&)
		// To compare class id with base class id
		// _TAG09 OBSOLETE

// Static data
	static char defaultDelimiter;

protected:
	int _count;			// Number of elements set in 'area'
	int _capacity;		// Actual allocated size of 'area'
	char *_area;		// Internal storage
	
// Methods
	void resize(int newsize);
	void grow(int newsize);
	void init(const RTRObjectId* cntxt, const RTRString* nm);
	
// Friends
#ifndef _RDEV_NO_STL_
friend std::ostream& operator<<(std::ostream&, const RTRObjectId&); 
#else
public:
void print(FILE*);
#endif
};

inline int RTRObjectId::count() const
{
	return _count;
}

#endif /* _objid_h */
