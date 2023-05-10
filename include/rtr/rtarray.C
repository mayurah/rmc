//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Dec. 02 1994"
// Version: 1.0

#include "rtr/rtarray.h"

template<class T> 
RTRArray<T>::RTRArray(int minindex, int maxindex)
	: _minIndex(minindex),
	  _store(new RTRGenericPointerVector(maxindex - minindex + 1))
{
	_store->Initialize(0);
}

template<class T> 
RTRArray<T>::RTRArray(const RTRArray<T>& o)
	: _store(new RTRGenericPointerVector(*(o._store)))
{
	_minIndex = o._minIndex;
	_store->Initialize(0);
}

template<class T> 
RTRArray<T>::~RTRArray()
{
	delete _store;
}

template<class T> 
int RTRArray<T>::lower() const
{
	return _minIndex;
}

template<class T> 
int RTRArray<T>::upper() const
{
	return _minIndex + _store->capacity() - 1;
}

template<class T> 
int RTRArray<T>::capacity() const
{
	return _store->capacity();
}

template<class T> 
T* RTRArray<T>::operator[](int i) const
{
	return (T *)_store->operator[](i - _minIndex); 
}

template<class T> 
T* RTRArray<T>::iTh(int i) const
{
	return (T *)_store->operator[](i - _minIndex); 
}

template<class T> 
RTRArray<T>& RTRArray<T>::operator=(const RTRArray<T>& other)
{
	delete _store;
	_minIndex = other._minIndex;
	_store = new RTRGenericPointerVector(other.capacity());
	for (int i = lower(); i <= upper(); i++)
		_store->put(i, other[i]);
	return *this;
}

template<class T> 
T*& RTRArray<T>::operator[](int i)
{
	return (T *&)(void *&)_store->operator[](i - _minIndex);
}

template<class T> 
void RTRArray<T>::force(T* v, int i)
{
	_store->force(i - _minIndex, v);
}

template<class T> 
void RTRArray<T>::put(T* v, int i)
{
	_store->put(i - _minIndex, v);
}

template<class T> 
RTRArray<T>& RTRArray<T>::deleteContents()
{
	for (int i = _store->lower(); i <= _store->upper(); i++)
	{
		T *t = (T *)_store->operator[](i);
		if (t)
			delete t;
		_store->put(i, 0);
	}
	return *this;
}

template<class T> 
RTRBOOL RTRArray<T>::has(T* v)
{
	for (int i = _store->lower(); i <= _store->upper(); i++)
		if ( (T *)_store->operator[](i) == v )
			return RTRTRUE;
	return RTRFALSE;
}

template<class T> 
int RTRArray<T>::occurrences(T* v) const
{
	int result = 0;
	for (int i = _store->lower(); i <= _store->upper(); i++)
		if ( (T *)_store->operator[](i) == v )
			result++;
	return result;
}

template<class T> 
RTRBOOL RTRArray<T>::validIndex(int i) const
{
	return i >= lower() && i <= upper();
}

template<class T> 
RTRBOOL RTRArray<T>::operator==(RTRArray<T>& other)
{
	if (_minIndex == other._minIndex && capacity() == other.capacity() )
	{
		for (int i = lower(); i <= upper(); i++)
			if ( operator[](i) != other[i] )
				return RTRFALSE;
		return RTRTRUE;
	}
	else
		return RTRFALSE;
}

template<class T> 
T* RTRArray<T>::index(int i) const
{
	return (T *)_store->operator[](i - _minIndex);
}

template<class T> 
T*& RTRArray<T>::index(int i)
{
	return (T *&)_store->operator[](i - _minIndex);
}

template<class T> 
RTRArray<T>& RTRArray<T>::set(int i, T* v)
{
	put(v, i);
	return *this;
}

template<class T> 
int RTRArray<T>::count() const
{
	return capacity();
}
