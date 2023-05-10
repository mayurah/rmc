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
RTRDLinkList<T,L>::RTRDLinkList()
{
	_count = 0;
}

template <class T, class L>
RTRDLinkList<T,L>::~RTRDLinkList()
{
}

template <class T, class L>
void RTRDLinkList<T, L>::removeAllAndDestroy()
{
	T *nextObject;
	for (T *object = first(); object != 0; )
	{
		nextObject = next(object);
		remove(object);
		delete object;
		object = nextObject;
	}
	RTPOSTCONDITION(_count == 0);
}

template <class T, class L>
T *RTRDLinkList<T, L>::find(
	RTRBOOL (*compareKeyToObject)(void*, T*), void *key) const
{
	for (T *object = first(); object != 0; object = next(object))
	{
		if (compareKeyToObject(key, object))
			return(object);
	}
	return(0);
}

template <class T, class L>
void RTRDLinkList<T, L>::removeAndDestroy(T *object)
{
	remove(object);
	delete object;
}

template <class T, class L>
RTRDLinkListIterator<T, L>::RTRDLinkListIterator(RTRDLinkList<T,L> &list)
		: _list(&list)
{
	_object = 0;
	_currentObjectRemoved = RTRFALSE;
	RTPOSTCONDITION(off());
}

template <class T, class L>
RTRDLinkListIterator<T, L>::RTRDLinkListIterator()
		: _list(0)
{
	_object = 0;
	_currentObjectRemoved = RTRFALSE;
	// RTPOSTCONDITION(off());
}

template <class T, class L>
RTRDLinkListIterator<T, L>::~RTRDLinkListIterator()
{
}

template <class T, class L>
void RTRDLinkListIterator<T, L>::forth() 
{
	RTPRECONDITION(_list != 0);
	RTPRECONDITION(!off());
	if (!_currentObjectRemoved)
	{
		_object = _list->next(_object);
	}
	else
	{
		_object = _nextObject;
		_currentObjectRemoved = RTRFALSE;
	}
}

template <class T, class L>
void RTRDLinkListIterator<T, L>::back()
{
	RTPRECONDITION(_list != 0);
	RTPRECONDITION(!off());
	if (!_currentObjectRemoved)
	{
		_object = _list->previous(_object);
	}
	else
	{
		_object = _prevObject;
		_currentObjectRemoved = RTRFALSE;
	}
}

template <class T, class L>
void RTRDLinkListIterator<T, L>::remove()
{
	RTPRECONDITION(_list != 0);
	RTPRECONDITION(!off());
	RTPRECONDITION(!_currentObjectRemoved);

	_nextObject = _list->next(_object);
	_prevObject = _list->previous(_object);
	_list->remove(_object);
	_currentObjectRemoved = RTRTRUE;
}

