//
//|---------------------------------------------------------------
//|                Copyright (C) 2000 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60523          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//

#ifndef _rtr_pointerlist_h
#define _rtr_pointerlist_h

#include "rtr/rtrdefs.h"

// Synopsis:
//
// Description:
//
//  This class implements a generic list of void pointers.
//  Users of this class must typecast outside the class in
//  order to get specific types. The implementation uses an
//	array that automatically resizes itself it needed.
//  The array starts at index 0 and ends at index capacity()-1.
//
//  Destruction: This class cannot destruct objects within it.
//  The user of this class is in charge of destruction of the
//  objects in the array.
//
// See Also:
//

class rtrPtrList
{

public:
  
// Constructors
	rtrPtrList();
		// Default constructor.

	rtrPtrList(const int max_size);
		// Create an array that can hold `max_size' elements
		// and beginning at index 0.
		// REQUIRE: max_size > 0
		// _TAG Constructor

	rtrPtrList( const rtrPtrList& artrPtrList);
		// Copy Constructor
		// _TAG Constructor

// Destructors
	~rtrPtrList();
		// _TAG Destructor

// Attributes
	inline RTRBOOL isEmpty() const
	{
		return(_index <= 0);
	};

	inline int capacity() const
		// return the current available capacity of the array
        // _TAG01 Attributes	
	{
		return( _size );
	};

	inline int last() const
		// Index of the current last element in the list.
		// Returns -1 if list is emtpy.
	{
		return( _index-1 );
	};

	inline int end() const
		// Index of the element after last element in the list.
		// Returns -1 if list is emtpy.
	{
		return( _index );
	};

// Assignment
	rtrPtrList& operator=( const rtrPtrList& aList);
		// _TAG03 Assignment 

// Insertion
	inline void add( void *element, int increase=16 )
		// Add the element to the end of the list.
		// If need to be resized, increase by 'increase'
		// amount.
	{
		if ( _index >= _size )
			resize( _size+increase );
		_array[_index++] = element;
	};

// Removal
	void remove( int i );
		// Remove the element at index 'i'.

	void remove( void *ptr, RTRBOOL all=RTRFALSE );
		// Remove the first element set to ptr.
		// If 'all' is set the TRUE then remove all
		// the elements set to ptr.

// Access contents of array slot i
	inline void* operator[](const int i) const
		// Access the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG06 Access contents
	{
		RTPRECONDITION( (i >= 0) && (i <_size) );
		return(_array[ i ]);
	};

	inline void* value(int i) const
		// _TAG09 Get value	
	{
		RTPRECONDITION( (i >= 0) && (i <_size) );
		return(_array[ i ]);
	};

	inline void* index(int i) const
		// Access the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
        // _TAG06 Access contents
	{
		RTPRECONDITION( (i >= 0) && (i <_size) );
		return(_array[ i ]);
	};

// Copy
	void copy( const rtrPtrList& aList );
		// _TAG05 Copy

// Resize
	void resize( const int max_size );
		// Resize the current array so it can hold `max_size' elements
		// and beginning at index 0.
		// Copy the contents of the old array.
		// REQUIRE: max_size > 0
		// _TAG04 Resize

// Information
	RTRBOOL has(void* v, int index=0) const;
		// is v in the list starting at index in the array?
		// _TAG08 Other

	int indexOf(void* v, int index=0) const;
		// Return index of v in the list starting at index in the array?
		// Return -1 if not in list.
		// _TAG08 Other

	int occurrences(void* v) const;
		// Count the number of times v is in the array
		// _TAG11 Information

	RTRBOOL operator==(rtrPtrList& anArray) const;
		// Are the two arrays equal?
		// _TAG11 Information

	inline RTRBOOL validIndex(int i) const
		// is i a valid index in the array?
		// _TAG11 Information
	{
		return( ((i >= 0) && (i < _size)) ? RTRTRUE : RTRFALSE);
	};

protected:

	void	**_array;	// Array of void pointers.
	int		_size;		// Maximum size of the array.
	int		_index;		// Current last index of the array.

};

#endif


