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

#ifndef RTR_SIMPLE_POINTER_ARRAY 
#define RTR_SIMPLE_POINTER_ARRAY



#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/gnptrvec.h"

// Synopsis:
//
// Description:
//
//  This class implements an array of pointers of objects.
//  It uses the RTRGenericPointerVector in order to implement
//  the template class.
//  It starts at index 0 and ends at index capacity()-1.
//
//  Destruction: This class does not destruct objects within it.
//  The user of this class is in charge of destruction of the
//  objects in the array.
//  The deleteContents() member function exists to delete all
//  contents of the array.
//
// See Also:
//

template<class T> class RTRSimplePointerArray
{
private:
 
protected:
	RTRGenericPointerVector	_aVector;

public:
  
// Constructors
	RTRSimplePointerArray(int max_size);
		// Create an array that can hold `max_size' elements
		// and beginning at index 0.
		// REQUIRE: max_size > 0
		// _TAG Constructor

	RTRSimplePointerArray(
		const RTRSimplePointerArray<T>& aRTRSimplePointerArray);
		// Copy constructor.
		// _TAG Constructor

// Destructors
	~RTRSimplePointerArray();
		// _TAG Destructor

// Attributes

	inline int lower() const
		// return the lower bound of the array
		// _TAG01 Attributes	
	{
		return(_aVector.lower());
	};

	inline int upper() const
		// return the upper bound of the array
        // _TAG01 Attributes	
	{
		return(_aVector.upper());
	};

	inline int capacity() const
		// return the current available capacity of the array
        // _TAG01 Attributes	
	{
		return( _aVector.capacity() );
	};

  
// Initialization

	void Initialize( T* value=0 )
		// _TAG02 Initialization
	{
		_aVector.Initialize( value );
	};


// Assignment
	RTRSimplePointerArray<T>& operator=(
				const RTRSimplePointerArray<T>& aRTRSimplePointerArray);
		// _TAG03 Assignment  

// Resize
	inline void resize( int max_size )
		// Resize the current array so it can at least hold `max_size' elements
		// and beginning at index 0.
		// Copy the contents of the old array into the new array.
		// REQUIRE: max_size > 0
		// _TAG04 Resize
	{
		RTPRECONDITION(max_size > 0);
		_aVector.resize( max_size );
	};

	inline void grow( int max_size )
		// Resize the current array so it can at least hold `max_size' elements
		// and beginning at index 0.
		// REQUIRE: max_size > 0
        // _TAG04 Resize	
	{
		RTPRECONDITION(max_size > 0);
		_aVector.grow( max_size );
	};


// Access contents of array slot i
	inline T* operator[](int i) const
		// Access the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG05 Access contents	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return((T*)_aVector[ i ]);
	};

	inline T* index(int i) const
		// Access the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
        // _TAG05 Access contents	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return((T*)_aVector[ i ]);
	};


// Modify contents of array slot i
	inline T*& operator[](int i)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG06 Modify contents	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return((T*&)_aVector[i]);
	};

	inline T*& index(int i)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
        // _TAG06 Modify contents	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return((T*&)_aVector[ i ]);
	};

// is v in the array

	inline RTRBOOL has(T* v)
		// is v in the array?
		// _TAG07 Other
	{
		return( _aVector.has( v ) );
	};


// Get a value from the array.
	inline T* value(int i)
		// _TAG08 Get value	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		return((T*)_aVector[ i ]);
	};


// Place v in the array at index i
	inline RTRSimplePointerArray<T>& set(int i, T* v)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
		// _TAG09 Place v in array	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		_aVector[ i ] = v;
		return(*this);
	};

	inline void put(int i, T* v)
		// Set the value at index i.
		// REQUIRE: (i >= 0) && (i < capacity())
        // _TAG09 Place v in array	
	{
		RTPRECONDITION( (i >= 0) && (i <capacity()) );

		_aVector[ i ] = v;
	};


// Array information
	inline int occurrences(T* v) const
		// Count the number of times v is in the array
		// _TAG10 Array information	
	{
		return( _aVector.occurrences( v ) );
	};

	inline RTRBOOL operator==(RTRSimplePointerArray<T>& anArray)
		// Are the two arrays equal?
		// _TAG10 Array information	
	{
		return ( _aVector == anArray._aVector );
	};

	inline RTRBOOL validIndex(int i) const
		// is i a valid index in the array?
        // _TAG10 Array information	
	{
		return( _aVector.validIndex( i ) );
	};

  
// Utility for cleanup.
	RTRSimplePointerArray<T>& deleteContents();
		// Delete all the contents of the array.
		// _TAG11 Utility for cleanup

};


#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("smpptrar.C")
#else
#include "rtr/smpptrar.C"
#endif
#endif


#endif /* RTR_SIMPLE_POINTER_ARRAY */
