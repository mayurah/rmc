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

template <class K, class T, class L>
int RTRDLinkHashTable<K,T,L>::getPrimeNumber(int number)
{
	static 
	int primes[] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
					43, 47, 53, 59, 61, 67, 73, 79, 83, 89, 91, 97};
	int	prime_number;
	int	remainder;
	int found;
	int	ii;
	int primesLength;

	prime_number = number;

	if ( prime_number > 2 )
	{
		remainder = prime_number % 2;

		if ( remainder == 0 )
			prime_number++;

        primesLength = (int) (sizeof(primes)/sizeof(primes[0])); 
		
		do
		{
			found = 0;
			for (ii = 0; ii < primesLength ; ii++)
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

template <class K, class T, class L>
RTRDLinkHashTable<K,T,L>::RTRDLinkHashTable(
		int hashTableSize,
		unsigned long (*hashKey)(K*),
		RTRBOOL (*compareKeyToObject)(K*, T*),
		unsigned long (*hashObject)(T*),
		RTRBOOL adjustSize
		 )
	: _hashKey((unsigned long (*)(const K*))hashKey),
	  _compareKeyToObject((RTRBOOL (*)(const K*, const T*))compareKeyToObject),
	  _hashObject((unsigned long (*)(const T*))hashObject)
{
	if (adjustSize)
		_hashTableSize = getPrimeNumber(hashTableSize);
	else
		_hashTableSize = hashTableSize;

	_hashTable = new RTRLiteDLinkList<T,L>[(unsigned int) _hashTableSize];
	_count = 0;
}

template <class K, class T, class L>
RTRDLinkHashTable<K,T,L>::RTRDLinkHashTable(
		int hashTableSize,
		unsigned long (*hashKey)(const K*),
		RTRBOOL (*compareKeyToObject)(const K*, const T*),
		unsigned long (*hashObject)(const T*),
		RTRBOOL adjustSize
		)
	: _hashKey(hashKey),
	  _compareKeyToObject(compareKeyToObject),
	  _hashObject(hashObject)
{
	if (adjustSize)
		_hashTableSize = getPrimeNumber(hashTableSize);
	else
		_hashTableSize = hashTableSize;

	_hashTable = new RTRLiteDLinkList<T,L>[(unsigned int) _hashTableSize];
	_count = 0;
}

template <class K, class T, class L>
RTRDLinkHashTable<K,T,L>::~RTRDLinkHashTable()
{
	delete[] _hashTable;
}


template <class K, class T, class L>
float RTRDLinkHashTable<K,T,L>::averageSearchLength() const
{
	RTPRECONDITION(!error());
	//unsigned long totalSearchLength = 0;
	float totalSearchLength = 0.0;

	RTRLiteDLinkList<T,L> *colissionList = &_hashTable[0];
	T *object;
	int length;
	for (int cnt = _hashTableSize; cnt-- > 0; colissionList++)
	{
		length = 0;
		for (object = colissionList->first(); object != 0;
							object = colissionList->next(object))
		{
			length++;
			totalSearchLength += length;
		}
	}
	if (count() > 0)
	{
		return(totalSearchLength /count());
	}
	else
		return(0);
}

template <class K, class T, class L>
T *RTRDLinkHashTable<K,T,L>::get(K *key, unsigned long hashsum) const
{
	RTPRECONDITION(!error());
	RTRLiteDLinkList<T,L> *collisionList = 
				(RTRLiteDLinkList<T,L> *)&_hashTable[hashsum%(unsigned int)_hashTableSize];
	T *object;
	for (object = collisionList->first(); object != 0;
						object = collisionList->next(object))
	{
		if (_compareKeyToObject(key, object))
			break;
	}
	return(object);
}

template <class K, class T, class L>
int RTRDLinkHashTable<K,T,L>::maxSearchLength() const
{
	RTPRECONDITION(!error());
	int maxSearchLength = 0;

	RTRLiteDLinkList<T,L> *colissionList = &_hashTable[0];
	int length;
	for (int count = _hashTableSize; count-- > 0; colissionList++)
	{
		length = colissionList->count();

		if (length > maxSearchLength)
			maxSearchLength = length;
	}
	return(maxSearchLength);
}


template <class K, class T, class L>
RTRBOOL RTRDLinkHashTable<K,T,L>::expensiveHas(T *object) const
{
	RTPRECONDITION(!error());

	RTRLiteDLinkList<T,L> *colissionList = &_hashTable[0];
	for (int count = _hashTableSize; count-- > 0; colissionList++)
	{
		if (colissionList->has(object))
			return(RTRTRUE);
	}
	return(RTRFALSE);
}


template <class K, class T, class L>
void RTRDLinkHashTable<K,T,L>::resize(int newHashTableSize, RTRBOOL adjustSize)
{
	RTPRECONDITION(!error());

	if (_hashObject == 0)
		return;

	RTRLiteDLinkList<T,L> *currentHashTable = _hashTable;
	int currentSize = _count;
	int currentHashTableSize = _hashTableSize;

	if (adjustSize)
		_hashTableSize = getPrimeNumber(newHashTableSize);
	else
		_hashTableSize = newHashTableSize;

	_hashTable = new RTRLiteDLinkList<T,L>[(unsigned int) _hashTableSize];
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

	RTRLiteDLinkList<T,L> *colissionList = &currentHashTable[0];
	for (int count = currentHashTableSize; count-- > 0; colissionList++)
	{
		for (object = colissionList->first(); object != 0; )
		{
			nextObject = colissionList->next(object);
			colissionList->remove(object);
			put(_hashObject(object), object);
			object = nextObject;
		}
	}

	delete[] currentHashTable;
}


template <class K, class T, class L>
void RTRDLinkHashTable<K,T,L>::removeAll()
{
	RTPRECONDITION(!error());
	RTRLiteDLinkList<T,L> *collisionList = &_hashTable[0];
	for (int count = _hashTableSize; count-- > 0; )
	{
		(collisionList++)->removeAll();
	}
	_count = 0;
}


template <class K, class T, class L>
void RTRDLinkHashTable<K,T,L>::removeAllAndDestroy()
{
	RTPRECONDITION(!error());
	RTRLiteDLinkList<T,L> *collisionList = &_hashTable[0];
	for (int count = _hashTableSize; count-- > 0; )
	{
		(collisionList++)->removeAllAndDestroy();
	}
	_count = 0;
}

template <class K, class T, class L>
RTRDLinkHashTableIterator<K,T,L>::RTRDLinkHashTableIterator(
		RTRDLinkHashTable<K,T,L> &hashTable
		)
	: _hashTable(&hashTable)
{
	RTPRECONDITION(!_hashTable->error());
	_object = 0;
	_currentObjectRemoved = RTRFALSE;
	RTPOSTCONDITION(off());
}

template <class K, class T, class L>
RTRDLinkHashTableIterator<K,T,L>::RTRDLinkHashTableIterator()
	: _hashTable(0)
{
	// don't check the following precondition
	// RTPRECONDITION(!_hashTable->error());
	_object = 0;
	_currentObjectRemoved = RTRFALSE;
	// don't check the following precondition
	// RTPOSTCONDITION(off());
};


template <class K, class T, class L>
void RTRDLinkHashTableIterator<K,T,L>::start()
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
	_currentObjectRemoved = RTRFALSE;
}


template <class K, class T, class L>
void RTRDLinkHashTableIterator<K,T,L>::positionToNextObject()
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
	_currentObjectRemoved = RTRFALSE;
} 

template <class K, class T, class L>
void RTRDLinkHashTableIterator<K,T,L>::remove()
{
	RTPRECONDITION(_hashTable != 0);
	RTPRECONDITION(!off());
	RTPRECONDITION(!_currentObjectRemoved);

	_collisionList->remove(_object);
	--(_hashTable->_count);
	_currentObjectRemoved = RTRTRUE;
}


template <class K, class T, class L>
void RTRDLinkHashTableIterator<K,T,L>::remove(K * key)
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

