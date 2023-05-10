//
//|---------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//	author:		Robert Bonaguro
//	created:	May 16, 1994
//	version:	1.0
//

#ifndef RTR_GENERIC_POINTER_VECTOR 
#define RTR_GENERIC_POINTER_VECTOR




#include "rtr/rtrdefs.h"

// Synopsis:
//
// Description:
//
//  This class implements a generic vector of void pointers.
//  Users of this class must typecast outside the class in
//  order to get specific types.
//  The vector start at index 0 and ends at index capacity()-1.
//
//  Destruction: This class cannot destruct objects within it.
//  The user of this class is in charge of destruction of the
//  objects in the array.
//
// See Also:
//

class RTRGenericPointerVector
{
 
private:

 
protected:

	void	**_array;	// Array of void pointers.
	int		_size;		// Maximum size of the array.


public:
  
// Constructors
	RTRGenericPointerVector(const int max_size);
		// Create an array that can hold `max_size' elements
		// and beginning at index 0.
		// REQUIRE: max_size > 0
		// _TAG Constructor

	RTRGenericPointerVector(
		const RTRGenericPointerVector& aRTRGenericPointerVector);
		// Copy Constructor
		// _TAG Constructor

// Destructors
	~RTRGenericPointerVector();
		// _TAG Destructor

// Attributes

	inline int lower() const
		// return the lower bound of the array
		// _TAG01 Attributes
	{
		return(0);
	};

	inline int upper() const
		// return the upper bound of the array
        // _TAG01 Attributes	
	{
		return(_size-1);
	};

	inline int capacity() const
		// return the current available capacity of the array
        // _TAG01 Attributes	
	{
		return( _size );
	};


// Initialization
	void Initialize( void *value=0 );
		// _TAG02 Initialization
  
// Assignment
	RTRGenericPointerVector& operator=(
		const RTRGenericPointerVector& aGenericPointerVector);
		// _TAG03 Assignment 

// Resize
	void resize( const int max_size );
		// Resize the current array so it can hold `max_size' elements
		// and beginning at index 0.
		// Copy the contents of the old array.
		// REQUIRE: max_size > 0
		// _TAG04 Resize

	void grow( const int max_size );
		// Grow the array so it can hold `max_size' elements beginning
		// at index 0.
		// REQUIRE: max_size > 0
        // _TAG04 Resize
  
// Copy
	void copy( const RTRGenericPointerVector& aVector );
		// _TAG05 Copy

// Access contents of array slot i

	inline void* operator[](const int i) const
		// Access the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG06 Access contents
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return(_array[ i ]);
	};

	inline void* index(int i) const
		// Access the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
        // _TAG06 Access contents
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return(_array[ i ]);
	};


// Modify contents of array slot i
	inline void*& operator[](int i)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG07 Modify contents	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return(_array[ i ]);
	};

	inline void*& index(int i)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
        // _TAG07 Modify contents	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return(_array[ i ]);
	};

// Other
	RTRBOOL has(void* v);
		// is v in the array?
		// _TAG08 Other

// Get a value from the array.
	inline void* value(int i)
		// _TAG09 Get value	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return(_array[ i ]);
	};


// Place v in the array at index i
	inline RTRGenericPointerVector& set(int i, void* v)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG10 Place	 v in array
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		_array[ i ] = v;
		return(*this);
	};

	inline void put(int i, void* v)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG10 Place v in array	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		_array[ i ] = v;
	};

	inline void force(int i, void* v)
		// Force the value at index i.
		// REQUIRE: i >= 0
        // _TAG10 Place v in array	
	{
		RTPRECONDITION( i >= 0 );

		if ( i > upper() )
			resize( i+10 );

		_array[ i ] = v;
	};


// Information
	int occurrences(void* v) const;
		// Count the number of times v is in the array
		// _TAG11 Information

	RTRBOOL operator==(RTRGenericPointerVector& anArray);
		// Are the two arrays equal?
		// _TAG11 Information

	inline RTRBOOL validIndex(int i) const
		// is i a valid index in the array?
		// _TAG11 Information
	{
		if ((i >= lower()) && (i <= upper()))
			return(RTRTRUE);
		else
			return(RTRFALSE);
	};

};



#endif /* RTR_GENERIC_POINTER_VECTOR */


