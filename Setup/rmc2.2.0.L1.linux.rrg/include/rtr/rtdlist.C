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
RTRBOOL RTRDblLinkList<T>::has(T *t) const
{
	RTPRECONDITION ( t );

	RTRBOOL result = RTRFALSE;
	RTRLinkElement *l;
	for (l = _list.first(); l != 0 && !result; l = _list.next(l))
		result = (l->item() == t);

	RTPOSTCONDITION ( !result || !empty() );
	return(result);
};

template<class T>
void RTRDblLinkList<T>::deleteContents()
{
	while (_link = _list.first())
	{
		_list.remove(_link);
		delete _link->item();
		delete _link;
	}
	RTPOSTCONDITION(empty());
};

template<class T>
void RTRDblLinkList<T>::wipeOut()
{
	while (_link = _list.first())
	{
		_list.remove(_link);
		delete _link;
	}
	RTPOSTCONDITION(empty());
};

template<class T>
void RTRDblLinkList<T>::remove(T *t)
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
void RTRDblLinkList<T>::search(T *t)
{
	for (	_link = _list.first();
			(_link != 0) && (_link->item() != t); 
			_link = _list.next(_link) )
		;

	RTPOSTCONDITION ( off() || (item() == t) );
};

