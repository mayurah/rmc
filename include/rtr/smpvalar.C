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
//	description:
//


#include "rtr/smpvalar.h"


template<class T> RTRSimpleValueArray<T>::RTRSimpleValueArray(
			const int max_size)
{
	RTPRECONDITION(max_size > 0);

	_size = max_size;
	_array = new T[ _size ];
};

template<class T> RTRSimpleValueArray<T>::RTRSimpleValueArray(
			const RTRSimpleValueArray<T>& aRTRSimpleValueArray)
{
	int i;

	_size = aRTRSimpleValueArray.capacity();

	_array = new T[ _size ];

	for (i=lower(); i <= upper(); i++)
		_array[i] = aRTRSimpleValueArray[i];
};

template<class T> RTRSimpleValueArray<T>::~RTRSimpleValueArray()
{
	delete [] _array;
};



template<class T> RTRSimpleValueArray<T>& RTRSimpleValueArray<T>::operator=(
			const RTRSimpleValueArray<T>& aRTRSimpleValueArray)
{
	int i;

	delete [] _array;

	_size = aRTRSimpleValueArray.capacity();

	_array = new T[ _size ];

	for (i=lower(); i <= upper(); i++)
		_array[i] = aRTRSimpleValueArray[i];

	return *this;
};


template<class T> void RTRSimpleValueArray<T>::resize(const int max_size)
{
	RTPRECONDITION(max_size > 0);
	T*	_new_array;
	int	i;

	if (max_size > _size)
	{
		_new_array = new T[max_size];

		for (i=lower();i<capacity();i++)
			_new_array[i] = _array[i];

		delete [] _array;

		_size = max_size;
		_array = _new_array;
	}
};

template<class T> void RTRSimpleValueArray<T>::grow(const int max_size)
{
	RTPRECONDITION(max_size > 0);

	if (max_size > _size)
	{
		delete [] _array;
		_size = max_size;
		_array = new T[max_size];
	}
};


template<class T> int RTRSimpleValueArray<T>::occurrences(T v) const
{
	int i;
	int occ;

	for ( i=lower(),occ=0; i <= upper(); i++ )
		if ( _array[ i ] == v )
			occ++;

	return(occ);
};

template<class T> RTRBOOL RTRSimpleValueArray<T>::operator==(RTRSimpleValueArray<T>& anArray)
{
	int i;

	if (capacity() == anArray.capacity() )
	{
		for (i=lower(); i<=upper(); i++)
			if ( _array[ i ] != anArray[i] )
				return(RTRFALSE);

		return(RTRTRUE);
	}
	else
		return(RTRFALSE);
};

template<class T> RTRBOOL RTRSimpleValueArray<T>::has(T v)
{
	int i;

	for (i=lower(); i<=upper(); i++)
	{
		if ( _array[ i ] == v)
			return(RTRTRUE);
	}
	return(RTRFALSE);
};

template<class T> RTRBOOL RTRSimpleValueArray<T>::has(T v, int number_to_check)
{
	int i;

	for (i=lower(); i<number_to_check; i++)
	{
		if ( _array[ i ] == v)
			return(RTRTRUE);
	}
	return(RTRFALSE);
};

