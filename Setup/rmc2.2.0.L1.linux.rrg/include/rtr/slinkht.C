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

#include <stdlib.h>

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
int RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>::getPrimeNumber(int number)
{
	static 
	int primes[] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
					43, 47, 53, 59, 61, 67, 73, 79, 83, 89, 91, 97};
	int	prime_number;
	int	remainder;
	int found;
	int ii;
	int primesLength;

	prime_number = number;

	if ( prime_number > 2 )
	{
		remainder = prime_number % 2;

		if ( remainder == 0 )
			prime_number++;

		primesLength = (int) ( sizeof(primes)/sizeof(primes[0]));

		do
		{
			found = 0;
			for (ii = 0; ii < primesLength; ii++)
			{
				if ((remainder=prime_number%primes[ii]) == 0 &&
		                           prime_number != primes[ii] )
				{
					found = 1;
					prime_number += 2;
					break;
				}
			}
		}
		while ( found );
	} 
	else
	    prime_number = 2;

	RTPOSTCONDITION(prime_number > 0);
	return(prime_number);
}

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>::RTRSLinkHashTable(
		int hashTableSize, bool adjustSize)
{
	if (adjustSize)
		_hashTableSize = getPrimeNumber(hashTableSize);
	else
		_hashTableSize = hashTableSize;
	_hashTable = new RTRLiteSList<T,L>[(unsigned int) _hashTableSize];
	_count = 0;
}

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>::~RTRSLinkHashTable()
{
	delete[] _hashTable;
}


template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
float RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>::averageSearchLength() const
{
	RTPRECONDITION(!error());
	unsigned long totalSearchLength = 0;

	RTRLiteSList<T,L> *colissionList = &_hashTable[0];
	T *object;
	int length;
	for (int cnt = _hashTableSize; cnt-- > 0; colissionList++)
	{
		length = 0;
		for (object = colissionList->first(); object != 0;
							object = colissionList->next(object))
		{
			length++;
			totalSearchLength += (unsigned int) length;
		}
	}
	if (count() > 0)
	{
		return((float)totalSearchLength /count());
	}
	else
		return(0);
}

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
T *RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>::removeByKey(K *key, unsigned long hashsum)
{
	RTPRECONDITION(!error());
	RTRLiteSList<T,L> *collisionList = 
				(RTRLiteSList<T,L> *)&_hashTable[hashsum%(unsigned int) _hashTableSize];

	T *prevObject = collisionList->head();
	T *object;
	for (object = collisionList->first(); object != 0;
						object = collisionList->next(object))
	{
		if (COMP()(key, object))
		{
			collisionList->removeNext(prevObject, object);
			--_count;
			break;
		}
		prevObject = object;
	}
	return(object);
}

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
int RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>::maxSearchLength() const
{
	RTPRECONDITION(!error());
	int maxSearchLength = 0;

	RTRLiteSList<T,L> *colissionList = &_hashTable[0];
	int length;
	for (int count = _hashTableSize; count-- > 0; colissionList++)
	{
		length = colissionList->count();

		if (length > maxSearchLength)
			maxSearchLength = length;
	}
	return(maxSearchLength);
}


template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
bool RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>::expensiveHas(T *object) const
{
	RTPRECONDITION(!error());

	RTRLiteSList<T,L> *colissionList = &_hashTable[0];
	for (int count = _hashTableSize; count-- > 0; colissionList++)
	{
		if (colissionList->has(object))
			return(true);
	}
	return(false);
}


template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
void RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>::resize(
		int newHashTableSize, bool adjustSize)
{
	RTPRECONDITION(!error());

	RTRLiteSList<T,L> *currentHashTable = _hashTable;
	int currentSize = _count;
	int currentHashTableSize = _hashTableSize;

	if (adjustSize)
		_hashTableSize = getPrimeNumber(newHashTableSize);
	else
		_hashTableSize = newHashTableSize;
	_hashTable = new RTRLiteSList<T,L>[(unsigned int) _hashTableSize];
	_count = 0;

	if (_hashTable == 0)
	{
		_hashTable = currentHashTable;
		_count = currentSize;
		_hashTableSize = currentHashTableSize;
		return;
	}

	T *object;
	T *nextObject;

	RTRLiteSList<T,L> *colissionList = &currentHashTable[0];
	for (int count = currentHashTableSize; count-- > 0; colissionList++)
	{
		for (object = colissionList->first(); object != 0; )
		{
			nextObject = colissionList->next(object);
			colissionList->remove(object);
			put(HASH_T()(object), object);
			object = nextObject;
		}
	}

	delete[] currentHashTable;
}


template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
void RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>::removeAll()
{
	RTPRECONDITION(!error());
	RTRLiteSList<T,L> *collisionList = &_hashTable[0];
	for (int count = _hashTableSize; count-- > 0; )
	{
		(collisionList++)->removeAll();
	}
	_count = 0;
}


template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
void RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>::removeAllAndDestroy()
{
	RTPRECONDITION(!error());
	RTRLiteSList<T,L> *collisionList = &_hashTable[0];
	for (int count = _hashTableSize; count-- > 0; )
	{
		(collisionList++)->removeAllAndDestroy();
	}
	_count = 0;
}

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
RTRSLinkHashTableIterator<K,T,L,HASH_K,COMP,HASH_T>::RTRSLinkHashTableIterator(
		RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T> &hashTable
		)
	: _hashTable(&hashTable)
{
	RTPRECONDITION(!_hashTable->error());
	_object = 0;
	_currentObjectRemoved = false;
	RTPOSTCONDITION(off());
}

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
RTRSLinkHashTableIterator<K,T,L,HASH_K,COMP,HASH_T>::RTRSLinkHashTableIterator()
	: _hashTable(0)
{
	// don't check the following precondition
	// RTPRECONDITION(!_hashTable->error());
	_object = 0;
	_currentObjectRemoved = false;
	// don't check the following precondition
	// RTPOSTCONDITION(off());
};


template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
void RTRSLinkHashTableIterator<K,T,L,HASH_K,COMP,HASH_T>::start()
{
	RTPRECONDITION(_hashTable != 0);

	_collisionList = &_hashTable->_hashTable[0];
	_lastCollisionList = _collisionList + (_hashTable->_hashTableSize - 1);
	_object = _collisionList->first();
	if (_object != 0)
		_nextObject = _collisionList->next(_object);
	else
	{
		_nextObject = 0;
		positionToNextObject();
	}
	_currentObjectRemoved = false;
}


template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
void RTRSLinkHashTableIterator<K,T,L,HASH_K,COMP,HASH_T>::positionToNextObject()
{
	RTPRECONDITION(_hashTable != 0);
	RTPRECONDITION(_collisionList <= _lastCollisionList);

	if (_nextObject != 0)
	{
		_object = _nextObject;
		_nextObject = _collisionList->next(_object);
	}
	else for (_collisionList++, _object = 0;
		_collisionList <= _lastCollisionList;  _collisionList++)
	{
		if (_object = _collisionList->first())
		{
			_nextObject = _collisionList->next(_object);
			break;
		}
	}
	_currentObjectRemoved = false;
} 

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
void RTRSLinkHashTableIterator<K,T,L,HASH_K,COMP,HASH_T>::remove()
{
	RTPRECONDITION(_hashTable != 0);
	RTPRECONDITION(!off());
	RTPRECONDITION(!_currentObjectRemoved);

	_collisionList->remove(_object);
	--(_hashTable->_count);
	_currentObjectRemoved = true;
}


template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
void RTRSLinkHashTableIterator<K,T,L,HASH_K,COMP,HASH_T>::remove(K * key)
{
	RTPRECONDITION(_hashTable != 0);
	RTPRECONDITION(!off());
	RTPRECONDITION(!_currentObjectRemoved);

	T* object = _hashTable->get(key);

	if (object == _object)
	{
		forth();
	}
	else if (object == _nextObject)
	{
		_nextObject = _collisionList->next(_nextObject);
	}
	_hashTable->remove(object);
}

