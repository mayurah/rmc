//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: Andrew MacGaffey
// Created: Jan. 4, 1994
// Version: 2.0

template<class T>
RTRLinkedList<T>::RTRLinkedList()
	: _position(0), _link(0)
{
}

template<class T>
RTRLinkedList<T>::RTRLinkedList(const RTRLinkedList<T>& o)
{
	for ( RTRGenLink<T> *l = o._list.first(); l; l = o._list.next(l) )
	{
		finish();
		addRight(l->_item);
	}

}

template<class T>
RTRLinkedList<T>::~RTRLinkedList()
{
	wipeOut();
}

template<class T>
T* RTRLinkedList<T>::first() const
{
	RTPRECONDITION ( !empty() );

	return _list.first()->item();
}

template<class T>
T* RTRLinkedList<T>::last() const
{
	RTPRECONDITION ( !empty() );

	return _list.last()->item();
}

template<class T>
int RTRLinkedList<T>::count() const
{
	return _list.count();
}

template<class T>
int RTRLinkedList<T>::position() const
{
	return _position;
}

template<class T>
RTRBOOL RTRLinkedList<T>::empty() const
{
	// RTPOSTCONDITION ( result implies count() == 0 )

	return count() == 0;
}

template<class T>
RTRBOOL RTRLinkedList<T>::off() const
{
	// RTPOSTCONDITION ( result implies ( offleft() || offright() )

	return offLeft() || offRight();
}

template<class T>
RTRBOOL RTRLinkedList<T>::offRight() const
{
	// RTPOSTCONDITION ( result implies position > count() )

	return _position > count();
}

template<class T>
RTRBOOL RTRLinkedList<T>::offLeft() const
{
	// RTPOSTCONDITION ( result implies position < 1 )

	return _position < 1;
}

template<class T>
RTRBOOL RTRLinkedList<T>::has(T *t) const
{
	RTPRECONDITION ( t );

	RTRBOOL result = RTRFALSE;
	RTRGenLink<T> *l = 0;
	for (l = _list.first(); l != 0 && !result; l = _list.next(l))
		result = (l->item() == t);

	RTPOSTCONDITION ( !result || !empty() );

	return result;
}

template<class T>
T*  RTRLinkedList<T>::item() const
{
	RTPRECONDITION ( !off() );

	return (_link->item());
}

template<class T>
T*  RTRLinkedList<T>::iTh(int i) const
{
	RTPRECONDITION ( i > 0 );
	RTPRECONDITION ( i <= count() );

	int _i = 1;
	RTRGenLink<T> *l = 0;
	for (l = _list.first(); l != 0 && _i != i; l = _list.next(l), _i++)
		;
	return l->item();
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::forth()
{
	RTPRECONDITION ( !offRight() );

	_position++;
	if (_position > 1)
		_link = _list.next(_link);
	else
		_link = _list.first();

	// RTPOSTCONDITION ( position = old position + 1 )

	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::back()
{
	RTPRECONDITION ( !offLeft() );

	_position--;
	_link = _list.previous(_link);

	// RTPOSTCONDITION ( position = old position - 1 )

	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::finish()
{
	_position = count();
	_link = _list.last();

	// RTPOSTCONDITION ( position = count() )

	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::start()
{
	_position = 1;
	_link = _list.first();

	RTPOSTCONDITION ( position() == 1 );

	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::goITh(int i)
{
	_position = 1;
	for (_link = _list.first(); _link != 0 && _position != i; 
				_link = _list.next(_link), _position++)
		;

	RTPOSTCONDITION ( position() == i );

	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::addFront(const T* newT)
{
	RTRGenLink<T> *newLink = new RTRGenLink<T>((T*)newT);
	_list.putFirst(newLink);

	RTPOSTCONDITION ( first() == newT);

	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::addLeft(const T* newT)
{
	RTPRECONDITION (  !offLeft() || empty() );

	RTRGenLink<T> *newLink = new RTRGenLink<T>((T*)newT);
	if (empty())
		_list.putFirst(newLink);
	else
	{
		_list.putPrevious(_link, newLink);
	}
	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::addRight(const T* newT)
{
	RTPRECONDITION (  !offLeft() || empty() );

	RTRGenLink<T> *newLink = new RTRGenLink<T>((T*)newT);
	if (empty())
		_list.putFirst(newLink);
	else
	{
		_list.putNext(_link, newLink);
	}
	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::extend(const T* newT)
{
	RTRGenLink<T> *newLink = new RTRGenLink<T>((T*)newT);
	_list.putLast(newLink);

	RTPOSTCONDITION ( last() == newT);

	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::remove()
{
	RTPRECONDITION ( !off() );

	RTRGenLink<T> *oldLink = _link;
	_link = _list.next(oldLink);
	_list.remove(oldLink);
	delete oldLink;
	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::deleteContents()
{
	while ((_link = _list.first()) != 0 )
	{
		_list.remove(_link);
		delete _link->item();
		delete _link;
	}
	_position = 0;

	RTPOSTCONDITION ( count() == 0 );

	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::wipeOut()
{
	while ((_link = _list.first()) != 0 )
	{
		_list.remove(_link);
		delete _link;
	}
	_position = 0;

	RTPOSTCONDITION ( count() == 0 );

	return *this;
}

template<class T>
RTRLinkedList<T>& RTRLinkedList<T>::search(const T* t)
{
	_position = 1;
	for (_link = _list.first(); _link != 0 && _link->item() != t; 
				_link = _list.next(_link), _position++)
		;

	RTPOSTCONDITION ( off() || item() == t );

	return *this;
}
