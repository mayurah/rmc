//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 03 1994"
// Version: 1.0

#include <memory.h>

template<class T> RTRNotifierArray<T>::RTRNotifierArray(int size)
{
	RTPRECONDITION( size > 0 );

	max = size;
	stuff = new void *[max];
	for (int i = 0; i<max; i++)
		stuff[i] = (void *)0;
};

template<class T> RTRNotifierArray<T>::~RTRNotifierArray()
{
	delete [] stuff;
};

template<class T> int RTRNotifierArray<T>::count()
{
	int j = 0;
	for(int i = 0; i < max; i++)
	{
		if (!(stuff[i] == (void *)0))
			j++;
	}
	return j;
};

template<class T> void RTRNotifierArray<T>::insert(T *t)
{
	void **newStuff;
	int i;

	for(i = 0; i < max; i++)
	{
		if (stuff[i] == (void *)0)
		{
			stuff[i] = (void *)t;
			break;
		}
	}
	if (i == max)
	{
		int newMax = max*2;
		newStuff = new void *[newMax];
		for (int j = 0; j<newMax; j++)
			newStuff[j] = (void *)0;
		(void)memcpy(newStuff, stuff, max*sizeof(void *));
		delete [] stuff;
		max = newMax;
		stuff = newStuff;
		stuff[i] = (void *)t;
	};

	RTPOSTCONDITION( has(t) );

};

template<class T> RTRBOOL RTRNotifierArray<T>::has(T *t)
{
	return indexOf(t) >= 0 ? RTRTRUE : RTRFALSE;
};

template<class T> void RTRNotifierArray<T>::remove(T *t)
{
	for(int i = 0; i < max; i++)
	{
		if (stuff[i] == (void *)t)
		{
			stuff[i] = (void *)0;
			break;
		}
	}

	RTPOSTCONDITION( !has(t) );
};

template<class T> void RTRNotifierArray<T>::removeItemAt(int i)
{
	RTPRECONDITION( i >= 0 );
	RTPRECONDITION( i < capacity() );

	stuff[i] = (void *)0;
};

template<class T> int RTRNotifierArray<T>::indexOf(T *t)
{
	int i;
	for(i = 0; i < max && !(stuff[i] == (void *)t); i++)
		;

	int result = i < max ? i : -1;
	return result;
};

template<class T> T *RTRNotifierArray<T>::item(int i)
{
	RTPRECONDITION( i >= 0 );
	RTPRECONDITION( i < capacity() );
	return((T *)stuff[i]);
};

template<class T> int RTRNotifierArray<T>::capacity()
{
	return max;
};

template<class T> void RTRNotifierArray<T>::absorb(RTRNotifierArray<T> *t)
{
	T *c;
	int m = t->capacity();

	for(int i = 0; i < m; i++)
	{
		c = t->item(i);
		if (c)
		{
			insert(c);
			t->removeItemAt(i);
		};
	};
};
