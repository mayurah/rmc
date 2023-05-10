//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       September 13, 1996
//  version:       1.0
//
//  description:
//


template<class T>
void RTRAscSortedList<T>::extend(T *newT)
{
	RTPRECONDITION ( newT );
	RTRLinkElement *newLink = new RTRLinkElement(newT);
	RTRLinkElement *l;
	for (l = _list.first();(l != 0)&&(*newT >= *(T*)(l->item())); l=_list.next(l))
		;
	if (l == 0)
		_list.putLast(newLink);
	else
		_list.putPrevious(l,newLink);
};

template<class T>
void RTRAscSortedList<T>::extendFromBehind(T *newT)
{
	RTPRECONDITION ( newT );
	RTRLinkElement *newLink = new RTRLinkElement(newT);
	RTRLinkElement *l;
	for (l=_list.last();(l != 0)&&(*newT < *(T*)(l->item())); l=_list.previous(l))
		;
	if (l == 0)
		_list.putFirst(newLink);
	else
		_list.putNext(l,newLink);
};

template<class T>
RTRBOOL RTRAscSortedList<T>::has(T *t) const
{
	RTPRECONDITION ( t );

	RTRBOOL result = RTRFALSE;
	RTRLinkElement *l = 0;
	for (l = _list.first(); l != 0 && !result; l = _list.next(l))
		result = (l->item() == t);

//	RTPOSTCONDITION ( !result || !empty() );
	return(result);
};

template<class T>
void RTRAscSortedList<T>::deleteContents()
{
	while (_link = _list.first())
	{
		_list.remove(_link);
		delete (T*)_link->item();
		delete _link;
	}
//	RTPOSTCONDITION(empty());
};

template<class T>
void RTRAscSortedList<T>::wipeOut()
{
	while (_link = _list.first())
	{
		_list.remove(_link);
		delete _link;
	}
//	RTPOSTCONDITION(empty());
};

template<class T>
void RTRAscSortedList<T>::remove(T *t)
{
	RTRLinkElement *l;
	for (l = _list.first(); (l != 0);l = _list.next(l) )
	{
		if (l->item() == t)
		{
			if (l == _link)
		        _link = _list.next(l);
			_list.remove(l);
			delete l;
			break;
		}
	}
};

template<class T>
void RTRAscSortedList<T>::search(T *t)
{
	for (	_link = _list.first();
			(_link != 0) && (_link->item() != t); 
			_link = _list.next(_link) )
		;

//	RTPOSTCONDITION ( off() || (item() == t) );
};
