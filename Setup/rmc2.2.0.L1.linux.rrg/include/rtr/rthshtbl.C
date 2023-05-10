//|-------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Implementation of a "hash table" class
//
// Author: Tom Hansen, A. MacGaffey
// Created: 12/6/94
// Tersion: 2.0
//

template <class K, class T>
RTRGenHash<K, T>::RTRGenHash(K *k, T *v)
	: _key(k), _value(v) 
{
}


template <class K, class T> 
RTRHashTable<K,T>::RTRHashTable(
			unsigned long (*hashFunc)(const K *), 
			int n
			)
	: _table(0), _hashFunc(hashFunc)
{
	_table = new RTRDLinkHashTable<K, RTRGenHash<K, T>, RTRDLink0 >(
									n,
									hashFunc,
									compareKeyToObject
									);
}

template<class K, class T>
RTRHashTable<K,T>::RTRHashTable(const RTRHashTable<K,T>& other)
	: _hashFunc(other._hashFunc)
{
	_table = new RTRDLinkHashTable<K, RTRGenHash<K, T>, RTRDLink0 >(
									other.count(),
									_hashFunc,
									compareKeyToObject
									);
	RTRHashTableIterator<K,T> iterator(other);
	for (iterator.start(); !iterator.off(); iterator.forth())
		put(iterator.currentItem(), iterator.currentKey());
}

template<class K, class T>
RTRHashTable<K,T>::~RTRHashTable()
{
	delete _table;
}

template<class K, class T>
RTRBOOL	RTRHashTable<K,T>::hasKey(K* key) const
{
	return (_table->get(key)) ? RTRTRUE : RTRFALSE;
}

template<class K, class T>
RTRBOOL RTRHashTable<K,T>::hasItem(T *v) const
{
	RTRHashTableIterator<K,T> iterator(*this);
	for (iterator.start(); !iterator.off(); iterator.forth())
		if (v == iterator.currentItem())
			break;
	return iterator.off() ? RTRFALSE : RTRTRUE;
}

template<class K, class T>
T* RTRHashTable<K,T>::item(K* key) const
{
	RTRGenHash<K, T> *g = _table->get(key);
	if (g)
		return g->value();
	else
		return 0;
}

template<class K, class T>
int	RTRHashTable<K,T>::count() const
{
	return _table->count();
}

template <class K, class T>
int RTRHashTable<K,T>::maxSearchLength() const
{
	return _table->maxSearchLength();
}

template <class K, class T>
float RTRHashTable<K,T>::averageSearchLength() const
{
	return _table->averageSearchLength();
}

template<class K, class T>
void RTRHashTable<K,T>::put(T* value, K* key)
{
	RTRGenHash<K, T> *g = new RTRGenHash<K, T>(key, value);
	_table->put(key, g);
}

template<class K, class T>
void RTRHashTable<K,T>::remove(K* key)
{
	RTRGenHash<K, T> *g = _table->get(key);
	if (g)
	{
		_table->remove(g);
		delete g;
	}
}

template<class K, class T>
RTRHashTable<K, T>& RTRHashTable<K,T>::deleteContents()
{
	RTRHashTableIterator<K,T> iterator(*this);
	for (iterator.start(); !iterator.off(); )
	{
		T *t = iterator.currentItem();
		K *k = iterator.currentKey();
		iterator.forth();
		remove(k);
		delete t;
	}
	return *this;
}

template<class K, class T>
RTRHashTable<K, T>& RTRHashTable<K,T>::deleteContentsAndKeys()
{
	RTRHashTableIterator<K,T> iterator(*this);
	for (iterator.start(); !iterator.off(); )
	{
		T *t = iterator.currentItem();
		K *k = iterator.currentKey();
		iterator.forth();
		remove(k);
		delete t;
		delete k;
	}
	return *this;
}


template <class K, class T>
RTRBOOL 
RTRHashTable<K,T>::compareKeyToObject(const K *key, const RTRGenHash<K, T> *g)
{
	return *(g->key()) == *key;
}

template <class K, class T>
RTRDLinkHashTableIterator<K, RTRGenHash<K, T>, RTRDLink0 > *
RTRHashTable<K,T>::newIterator() const
{
	return new RTRDLinkHashTableIterator<K, RTRGenHash<K, T>, RTRDLink0 >(*_table);
}

template<class K, class T>
void RTRHashTable<K,T>::resize(int size)
{
	RTRDLinkHashTable<K, RTRGenHash<K, T>, RTRDLink0> * newtable = 
		new RTRDLinkHashTable<K, RTRGenHash<K, T>, RTRDLink0 >(
							size, _hashFunc, compareKeyToObject);
	
	RTRDLinkHashTableIterator<K, RTRGenHash<K, T>, RTRDLink0 > iter(*_table);
	for (iter.start(); !iter.off(); iter.forth())
	{
		RTRGenHash<K, T> * i = iter.item();
		iter.remove();
		newtable->put(i->key(), i);
	}

	delete _table;
	_table = newtable;
}




template<class K, class T>
RTRHashTableIterator<K,T>::RTRHashTableIterator(const RTRHashTable<K,T>& t)
	: _table(&t), _iterator(0)
{
	_iterator = t.newIterator();
}

template<class K, class T>
RTRHashTableIterator<K,T>::~RTRHashTableIterator()
{
	delete _iterator;
}

template<class K, class T>
const RTRHashTable<K,T>&  RTRHashTableIterator<K,T>::container() const
{
	return *_table;
}

template<class K, class T>
void	RTRHashTableIterator<K,T>::start()
{
	_iterator->start();
}

template<class K, class T>
void	RTRHashTableIterator<K,T>::forth()
{
	_iterator->forth();
}

template<class K, class T>
RTRBOOL	RTRHashTableIterator<K,T>::off() const
{
	return _iterator->off();
}

template<class K, class T>
K*	RTRHashTableIterator<K,T>::currentKey() const
{
	return _iterator->item()->key();
}

template<class K, class T>
T*	RTRHashTableIterator<K,T>::currentItem() const
{
	return _iterator->item()->value();
}

template<class K, class T>
void	RTRHashTableIterator<K,T>::reset(const RTRHashTable<K,T>& t)
{
	_table = &t;
	if ( _iterator )
	{
		delete _iterator;
		_iterator = t.newIterator();
	}
}

template<class K, class T>
void	RTRHashTableIterator<K,T>::remove(K * key)
{
	_iterator->remove(key);
}


