//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/03
//
// Description:
//

template <class T, class L>
RTRLiteSList<T, L>::RTRLiteSList()
{
}

template <class T, class L>
RTRLiteSList<T, L>::~RTRLiteSList()
{
}

template <class T, class L>
void RTRLiteSList<T, L>::removeAndDestroy(T *object)
{
	remove(object);
	delete object;
}

template <class T, class L>
void RTRLiteSList<T, L>::removeAllAndDestroy()
{
	T *object;
	while (object = removeFirst())
	{
		delete object;
	}
}

template <class T, class L>
T *RTRLiteSList<T, L>::find(
		bool (*compareKeyToObject)(void*, T*), void *key) const
{
	for (T *object = first(); object != 0; object = next(object))
	{
		if (compareKeyToObject(key, object))
			return(object);
	}
	return(0);
}
