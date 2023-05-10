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
RTRLinkedListCursor<T>::RTRLinkedListCursor()
	: _list(0), _current(0)
{
}

template<class T>
RTRLinkedListCursor<T>::RTRLinkedListCursor(const RTRLinkedListCursor<T>& other)
	: _list(other._list), _current(other._current)
{
}

template<class T>
RTRLinkedListCursor<T>::~RTRLinkedListCursor()
{
}

template<class T>
RTRBOOL RTRLinkedListCursor<T>::off() const
{
	return (_current == 0) ? RTRTRUE : RTRFALSE;
}

template<class T>
T* RTRLinkedListCursor<T>::current() const
{
	return _current->_item;
}

template<class T>
RTRBOOL RTRLinkedListCursor<T>::operator==(
		const RTRLinkedListCursor<T>& rhs
		) const
{
	return _current ? _current == rhs._current : RTRFALSE;
}

template<class T>
RTRBOOL RTRLinkedListCursor<T>::operator!=(
		const RTRLinkedListCursor<T>& rhs
		) const
{
	return _current ? _current != rhs._current : RTRFALSE;
}

template<class T>
T& RTRLinkedListCursor<T>::operator*() const
{
	return _current ? *(_current->_item) : *(T*)0;
}

template<class T>
T* RTRLinkedListCursor<T>::operator->() const
{
	return _current ? _current->_item : 0;
}

template<class T>
RTRLinkedListCursor<T>::operator T*() const
{
	return _current ? _current->_item : 0;
}

template<class T>
const RTRLinkedListCursor<T>& RTRLinkedListCursor<T>::operator=(
		const RTRLinkedList<T>& rhs
		)
{
	_list = &rhs._list;
	_current = _list->first();
	return *this;
}

template<class T>
const RTRLinkedListCursor<T>& RTRLinkedListCursor<T>::operator=(
		const RTRLinkedListCursor<T>& rhs
		)
{
	_list = rhs._list;
	_current = rhs._current;
	return *this;
}

template<class T>
const RTRLinkedListCursor<T>& RTRLinkedListCursor<T>::operator++()
{
	_current = _list->next(_current);
	return *this;
}

template<class T>
const RTRLinkedListCursor<T>& RTRLinkedListCursor<T>::operator++(int)
{
	_current = _list->next(_current);
	return *this;
}

template<class T>
const RTRLinkedListCursor<T>& RTRLinkedListCursor<T>::operator--(int)
{
	_current = _list->previous(_current);
	return *this;
}

template<class T>
void RTRLinkedListCursor<T>::start()
{
	_current = _list->first();
}

template<class T>
void RTRLinkedListCursor<T>::forth()
{
	_current = _list->next(_current);
}

template<class T>
void RTRLinkedListCursor<T>::back()
{
	_current = _list->previous(_current);
}

template<class T>
void RTRLinkedListCursor<T>::finish()
{
	_current = _list->last();
}
