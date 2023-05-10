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

#include "rtr/smpptrar.h"


template<class T> RTRSimplePointerArray<T>::RTRSimplePointerArray(int max_size) :
	_aVector( max_size )
{
	RTPRECONDITION(max_size > 0);
};

template<class T> RTRSimplePointerArray<T>::RTRSimplePointerArray(
			const RTRSimplePointerArray<T>& anArray) :
	_aVector( anArray._aVector )
{
};


template<class T> RTRSimplePointerArray<T>::~RTRSimplePointerArray()
{
};



template<class T> RTRSimplePointerArray<T>& RTRSimplePointerArray<T>::operator=(
			const RTRSimplePointerArray<T>& aRTRSimplePointerArray)
{
	_aVector = aRTRSimplePointerArray._aVector;
	return *this;
};




template<class T> RTRSimplePointerArray<T>& RTRSimplePointerArray<T>::deleteContents()
{
	for (int i = lower(); i <= upper(); i++)
	{
		T *curItem = operator[](i);
		put(i, (T *)0);
		if (curItem)
			delete curItem;
	}
	return *this;
};


