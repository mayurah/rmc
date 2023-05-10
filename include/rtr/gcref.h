//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Aug. 08 1995"
// Version: 1.0

#ifndef _rtr_gcref_h
#define _rtr_gcref_h

#include "rtr/rtrdefs.h"


// Synopsis:
// #include "rtr/gc.h"
//
// RTRObjRef<RTRMyClass> ptr = new RTRMyClass();
// RTRObjRef<RTRMyClass> optr = ptr;
// RTRObjRef<RTRMyClass>* foo = new RTRObjRef<RTRMyClass>(ptr)
// delete foo;
//
// Description:
// The template for a smart pointer. The parameter class T must be a 
// descendant of RTRGCObj.
//
// See Also:
// RTRGCObj
//

template <class T> class RTRObjRef
{ 
public:
	
	// _TAG Constructor
	// A new "null" pointer.
	inline RTRObjRef() : _impl(0) { }

	// _TAG Constructor
	// A copy of other.
	inline RTRObjRef(const RTRObjRef<T>& other)
		: _impl(other._impl)
	{
		if ( _impl )
			_impl->incrementCount();
	}

	// _TAG Constructor
	// A pointer to the object pointed to by t.
	inline RTRObjRef(T * t)
		: _impl(t)
	{
		if ( _impl )
			_impl->incrementCount();
	}

	// _TAG Constructor
	// A pointer to the object referenced by t.
	inline RTRObjRef(T& t)
		: _impl(&t)
	{
		if ( _impl )
			_impl->incrementCount();
	}

// Destructor

	// _TAG Destructor
	inline ~RTRObjRef()
	{
		if ( _impl )
			_impl->decrementCount();
	}

// Operators

	// _TAG01 Operators
	inline T *operator->() const { return (T*)_impl; }

	// _TAG01 Operators
	inline T& operator*() const { return *_impl; }

// Transformation

	// _TAG02 Transformation	
	operator T*() const 
	{
		return _impl;
	}

// Comparison

	// _TAG03 Comparison
	// Pointer equality.
	inline RTRBOOL operator==(const RTRObjRef<T>& rhs) const
	{
		return _impl == rhs._impl;
	}

	// _TAG03 Comparison
	// Pointer inequality.
	inline RTRBOOL operator!=(const RTRObjRef<T>& rhs) const
	{
		return _impl != rhs._impl;
	}

	// _TAG03 Comparison
	// Pointer equality.
	inline RTRBOOL operator==(const T * t) const { return _impl == t; }

	// _TAG03 Comparison
	// Pointer inequality.
	inline RTRBOOL operator!=(const T * t) const { return _impl != t; }

// Assignment

	// _TAG04 Assignment
	inline RTRObjRef<T>& operator=(const RTRObjRef<T>& rhs)
	{
		if ( _impl )
			_impl->decrementCount();
		_impl = rhs._impl;
		if ( _impl )
			_impl->incrementCount();
		return *this;
	}

	// _TAG04 Assignment
	inline RTRObjRef<T>& operator=(T *t)
	{
		if ( _impl )
			_impl->decrementCount();
		_impl = t;
		if ( _impl )
			_impl->incrementCount();
		return *this;
	}

protected:
	T *_impl;

}; 

#endif
