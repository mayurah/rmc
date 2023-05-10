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

#ifndef RTR_SIMPLE_VALUE_ARRAY 
#define RTR_SIMPLE_VALUE_ARRAY



#include "rtr/platform.h"
#include "rtr/rtrdefs.h"

// Synopsis:
//
// Description:
//
//  This class defines an array of values. The array starts at
//  index 0 and ends at index capacity()-1.
//
// See Also:
//

template<class T> class RTRSimpleValueArray
{
 
private:

 
protected:

	T	*_array;	// Array of type T.
	int	_size;		// Maximum size of the array.


public:
  
// Constructors
	RTRSimpleValueArray(const int max_size);
		// Create an array that can hold `max_size' elements
		// and beginning at index 0.
		// REQUIRE: max_size > 0
		// _TAG Constructor

	RTRSimpleValueArray(const RTRSimpleValueArray<T>& anArray);
		// Copy Constructor
		// _TAG Constructor

// Destructors
	~RTRSimpleValueArray();
		// _TAG Destructor
  
// Assignment
	RTRSimpleValueArray<T>&	operator=(
		const RTRSimpleValueArray<T>& anArray);
 		// _TAG01 Assignment 

// Attributes

	inline int lower() const
		// return the lower bound of the array
		// _TAG02 Attributes	
	{
		return(0);
	};

	inline int upper() const
		// return the upper bound of the array
        // _TAG02 Attributes    	
	{
		return(_size-1);
	};

	inline int capacity() const
		// return the current available capacity of the array
        // _TAG02 Attributes	
	{
		return( _size );
	};



// Resize
	void resize( const int max_size );
		// Resize the current array so it can hold at least `max_size' elements
		// and beginning at index 0.
		// Copy the contents of the old array into the new array.
		// REQUIRE: max_size > 0
		// _TAG03 Resize

	void grow( const int max_size );
		// Resize the current array so it can hold at least `max_size' elements
		// and beginning at index 0.
		// REQUIRE: max_size > 0
        // _TAG03 Resize

// Access contents of array slot i

	inline T operator[](int i) const
		// Access the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG04 Access contents	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return(_array[ i ]);
	};

	inline T index(int i) const
		// Access the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
        // _TAG04 Access contents	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return(_array[ i ]);
	};


// Modify contents of array slot i
	inline T& operator[](int i)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG05 Modify contents	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return(_array[ i ]);
	};

	inline T& index(int i)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
        // _TAG05 Modify contents	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return(_array[ i ]);
	};


// is v in the array?
	RTRBOOL has(T v);
		// is v in the array?
		// _TAG06 Other

	RTRBOOL has(T v, int number_to_check);
        // is v in the array?
		// _TAG06 Other

// Get a value from the array.

	inline T value(int i)
		// _TAG07 Get value
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return(_array[ i ]);
	};


// Place v in the array at index i

	inline RTRSimpleValueArray<T>& set(int i, T v)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG08 Place v in array	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		_array[ i ] = v;
		return(*this);
	};

	inline void put(int i, T v)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
        // _TAG08 Place v in array	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		_array[ i ] = v;
	};


// Array information
	int occurrences(T v) const;
		// Count the number of times v is in the array
		// _TAG09 Array information

	RTRBOOL operator==(RTRSimpleValueArray<T>& anArray);
		// Are the two arrays equal?
        // _TAG09 Array information

	inline RTRBOOL validIndex(int i) const
		// is i a valid index in the array?
        // _TAG09 Array information
	{
		if ((i >= lower()) && (i <= upper()))
			return(RTRTRUE);
		else
			return(RTRFALSE);
	};

  
};


#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("smpvalar.C")
#else
#include "rtr/smpvalar.C"
#endif
#endif

#endif /* RTR_SIMPLE_VALUE_ARRAY */


