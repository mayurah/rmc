//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel (A. MacGaffey)
// Created: 8/11/94
//
// Description:
//

#include "rtr/shmdll.h"

template< class T, class L>
RTRShmDLinkList<T, L>::RTRShmDLinkList()
{
}

template< class T, class L>
RTRShmDLinkList<T, L>::RTRShmDLinkList(const char *base)
	: RTRShmDList(base)
{
	_count = 0;
}

template< class T, class L>
RTRShmDLinkList<T, L>::~RTRShmDLinkList()
{
}

template<class T, class L>
int RTRShmDLinkList<T, L>::count(const char *) const
{
	return(_count);
}

template<class T, class L>
void RTRShmDLinkList<T, L>::removeAll(const char *base)
{
	RTRShmDList::removeAll(base);
	_count = 0;
}

template< class T, class L>
void RTRShmDLinkList<T, L>::removeAllAndDestroy(const char *base)
{
	T *nextObject;
	for (T *object = first(base); object != 0; )
	{
		nextObject = next(object, base);
		remove(object, base);
		delete object;
		object = nextObject;
	}
	RTPOSTCONDITION(_count == 0);
}

template< class T, class L>
void RTRShmDLinkList<T, L>::split(T *object, RTRShmDLinkList<T,L> *list, const char *base)
{
#ifdef RTDEBUG
	int cnt = count(base);
#endif
	RTRShmDList::split((toL(object)), list, base);
	_count = RTRShmDList::count(base);
	list->_count = list->RTRShmDList::count(base);
	RTPOSTCONDITION(cnt == (count(base) + list->count(base)));
};

template< class T, class L>
T *RTRShmDLinkList<T, L>::find(
		RTRBOOL (*compareKeyToObject)(void*, T*), 
		void *key, 
		const char *base
		) const
{
	RTRShmDLinkList<T,L> *tmp = (RTRShmDLinkList<T, L> *)this;
	for (T *object = tmp->first(base); 
			object != 0; 
				object = tmp->next(object, base))
	{
		if (compareKeyToObject(key, object))
			return(object);
	}
	return(0);
}

template<class T, class L>
void RTRShmDLinkList<T, L>::remove(T *object, const char *base)
{
	RTRShmDList::remove(toL(object), base);
	--_count;
	RTPOSTCONDITION(count(base) >= 0);
}

template<class T, class L>
void RTRShmDLinkList<T, L>::putFirst(T *object, const char *base)
{
	RTRShmDList::putFirst(toL(object), base);
	++_count;
}

template<class T, class L>
void RTRShmDLinkList<T, L>::putLast(T *object, const char *base)
{
	RTRShmDList::putLast(toL(object), base);
	++_count;
}

template<class T, class L>
void RTRShmDLinkList<T, L>::putPrevious(T *object, T *newObject, const char *base)
{
	RTRShmDList::putPrevious(toL(object), toL(newObject), base);
	++_count;
}

template<class T, class L>
void RTRShmDLinkList<T, L>::putNext(T *object, T *newObject, const char *base)
{
	RTRShmDList::putNext(toL(object), toL(newObject), base);
	++_count;
}

template<class T, class L>
void RTRShmDLinkList<T, L>::removeAndDestroy(T *object, const char *base)
{
	remove(object, base);
	delete object;
}

template<class T, class L>
T *RTRShmDLinkList<T, L>::first(const char *base)
{
	return((T*)((L*)RTRShmDList::first(base)));
}

template<class T, class L>
T *RTRShmDLinkList<T, L>::last(const char *base)
{
	return((T*)((L*)RTRShmDList::last(base)));
}

template<class T, class L>
T *RTRShmDLinkList<T, L>::next(T *object, const char *base) const
{
	return((T*)((L*)RTRShmDList::next((toL(object)), base)));
}

template<class T, class L>
T *RTRShmDLinkList<T, L>::previous(T *object, const char *base) const
{
	return((T*)((L*)RTRShmDList::previous((toL(object)), base)));
}

template<class T, class L>
void RTRShmDLinkList<T, L>::append(RTRShmDLinkList<T,L> *list, const char *base)
{
	_count += list->count(base);
	RTRShmDList::append(list, base);
	list->_count = 0;
}

template<class T, class L>
void RTRShmDLinkList<T, L>::prepend(RTRShmDLinkList<T,L> *list, const char *base)
{
	_count += list->count(base);
	RTRShmDList::prepend(list, base);
	list->_count = 0;
}

template<class T, class L>
RTRBOOL RTRShmDLinkList<T, L>::has(T *object, const char *base) const
{
	return(RTRShmDList::has(toL(object), base));
}

template<class T, class L>
RTRBOOL RTRShmDLinkList<T, L>::has(
		RTRBOOL (*compareKeyToObject)(void*, T*), void *key, const char *base) const
{
	return(find(compareKeyToObject, key, base) ? RTRTRUE : RTRFALSE);
}

template<class T, class L>
void RTRShmDLinkList<T, L>::reset(const char *base)
{
	RTRShmDList::reset(base);
	_count = 0;
}
