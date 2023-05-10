//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/94
//
// Description:
//

template <class T, class L>
RTRLiteDLinkList<T, L>::RTRLiteDLinkList()
{
}

template <class T, class L>
RTRLiteDLinkList<T, L>::~RTRLiteDLinkList()
{
}

template <class T, class L>
void RTRLiteDLinkList<T, L>::removeAndDestroy(T *object)
{
	remove(object);
	delete object;
}

template <class T, class L>
void RTRLiteDLinkList<T, L>::removeAllAndDestroy()
{
	T *nextObject;
	for (T *object = first(); object != 0; )
	{
		nextObject = next(object);
		remove(object);
		delete object;
		object = nextObject;
	}
}

template <class T, class L>
void RTRLiteDLinkList<T, L>::reset()
{
  RTRDList::reset();
}

template <class T, class L>
T *RTRLiteDLinkList<T, L>::find(
		RTRBOOL (*compareKeyToObject)(void*, T*), void *key) const
{
	for (T *object = first(); object != 0; object = next(object))
	{
		if (compareKeyToObject(key, object))
			return(object);
	}
	return(0);
}
