//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/03
//

#ifndef __RTRSLinkHashTable
#define __RTRSLinkHashTable

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/lsllist.h"

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T> class RTRSLinkHashTableIterator;

// Synopsis:
//
// Description: HASH_K, COMP and HASH_T need to be defined
// as function objects using the following examples/templates:
//
//    struct hashKey
//    {
//       unsigned long operator()(K *key)
//       {
//           unsigned hashsum = ...
//           return hashsum;
//       }
//	 // Or Pass key by value for numeric key
//       unsigned long operator()(K key)
//       {
//           unsigned hashsum = ...
//           return hashsum;
//       }
//    }
//
//    struct compareKeyObject
//    {
//       bool operator()(K *key, T *object)
//       {
//           if (key and object match)
//               return true;
//           else
//               return false;
//       }
//	 // Or Pass key by value for numeric key
//       bool operator()(K key, T *object)
//       {
//           if (key and object match)
//               return true;
//           else
//               return false;
//       }
//    }
//
//    struct hashObject
//    {
//       unsigned long operator()(T *object)
//       {
//           unsigned hashsum = ...
//           return hashsum;
//       }
//    }
//
// See Also:
//

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
class RTRSLinkHashTable
{
	friend class RTRSLinkHashTableIterator<K,T,L,HASH_K,COMP,HASH_T>;
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRSLinkHashTable(const RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>&);
	RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>& operator=(const RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T>&);
		// Force instantiation
	typedef RTRLiteSList<T,L> HashTableBucketList;
		//
protected:
	int _hashTableSize;
		//
	int _count;
		//
	RTRLiteSList<T,L> *_hashTable;
		//
public:

// Constructor
	RTRSLinkHashTable(
		int hashTableSize, bool adjustSize = true);
		// _TAG Constructor

// Destructor
	virtual ~RTRSLinkHashTable();
		// _TAG Destructor

// State

	// _TAG01 State	
	inline bool error() const
	{
		return(_hashTable == 0);
	};

// Size

	// _TAG02 Size
	inline int count() const
	{
		RTPRECONDITION(!error());
		return(_count);
	};

	// _TAG02 Size
	inline void setCount(int count)
	{
		RTPRECONDITION(!error());
		RTPRECONDITION(count >= 0);
		_count = count;
	};

	// _TAG02 Size
	inline int capacity() const
	{
		RTPRECONDITION(!error());
		return(_hashTableSize);
	};

// Implicit cast

	// _TAG03 Implicit cast
	inline L *toL(L *object) const
	{
		return(object);
	};

// Put

	// _TAG04 Put
	inline void put(K *key, T *object)
	{
		RTPRECONDITION(!error());
		_hashTable[HASH_K()(key)%(unsigned int)_hashTableSize].putFirst(object);
		++_count;
	};

	// _TAG04 Put
	inline void put(unsigned long hashsum, T *object)
	{
		RTPRECONDITION(!error());
		_hashTable[hashsum%(unsigned int)_hashTableSize].putFirst(object);
		++_count;
	};

// Remove

	// _TAG05 Remove
	inline void remove(T *object, unsigned long hashsum)
	{
		RTPRECONDITION(!error());
		_hashTable[hashsum%(unsigned int)_hashTableSize].remove(object);
		--_count;
		RTPOSTCONDITION(_count >= 0);
	};

	// _TAG05 Remove
	inline void remove(T *object)
	{
		RTPRECONDITION(!error());
		remove(object, HASH_T()(object));
	};
		// _TAG05 Remove
	inline void remove(RTRLiteSList<T,L> *collList, T *object)
	{
		RTPRECONDITION(!error());
		collList->remove(object);
		--_count;
		RTPOSTCONDITION(_count >= 0);
	};

	// _TAG05 Remove
	inline void remove(RTRLiteSList<T,L> *collList, T *prevObject, T *object)
	{
		RTPRECONDITION(!error());
		if (prevObject != 0)
			collList->removeNext(prevObject, object);
		else
			collList->removeFirst();
		--_count;
		RTPOSTCONDITION(_count >= 0);
	};

	T *removeByKey(K *key, unsigned long hashsum);
		// _TAG05 Get

	// _TAG05 Get
	inline T *removeByKey(K *key)
	{
		return(removeByKey(key, HASH_K()(key)));
	};

	void removeAll();
		// _TAG05 Remove

	void removeAllAndDestroy();
		// _TAG05 Remove

// Get
	T *get(K *key, unsigned long hashsum) const
		// _TAG06 Get
	{
		RTPRECONDITION(!error());
		RTRLiteSList<T,L> *collisionList = 
				(RTRLiteSList<T,L> *)&_hashTable[hashsum%(unsigned int)_hashTableSize];
		T *object;
		for (object = collisionList->first(); object && !COMP()(key, object);
						object = collisionList->next(object))
		{
		}
		return(object);
	}

	// _TAG06 Get
	inline T *get(K *key) const
	{
		return(get(key, HASH_K()(key)));
	};

	T *get(K key, unsigned long hashsum) const
		// _TAG06 Get
	{
		RTPRECONDITION(!error());
		RTRLiteSList<T,L> *collisionList = 
				(RTRLiteSList<T,L> *)&_hashTable[hashsum%(unsigned int)_hashTableSize];
		T *object;
		for (object = collisionList->first(); object && !COMP()(key, object);
						object = collisionList->next(object))
		{
		}
		return(object);
	}

	// _TAG06 Get
	inline T *get(K key) const
	{
		return(get(key, HASH_K()(key)));
	};

	// _TAG06 Get
	inline RTRLiteSList<T,L> *getCollisionList(int bucket)
	{
		RTPRECONDITION(!error());
		RTPRECONDITION(bucket >= 0 && bucket < (unsigned int)_hashTableSize);
		return(&_hashTable[bucket]);
	};

	// _TAG06 Get
	inline RTRLiteSList<T,L> *getCollisionList(unsigned long hashsum)
	{
		RTPRECONDITION(!error());
		return(&_hashTable[hashsum%(unsigned int)_hashTableSize]);
	};

	// _TAG06 Get
	inline RTRLiteSList<T,L> *getCollisionList(K *key)
	{
		RTPRECONDITION(!error());
		return(&_hashTable[HASH_K()(key)%(unsigned int)_hashTableSize]);
	};

// Resize
	void resize(int newHashTableSize, bool adjustSize = true);
		// _TAG07 Resize

// Quality
	int maxSearchLength() const;
		// _TAG08 Quality

	float averageSearchLength() const;
        // _TAG08 Quality

// Get Prime Number
	static int getPrimeNumber(int number);
		// _TAG09 Get Prime Number

// Debug
private:
	bool expensiveHas(T *object) const;
};

// Synopsis:
//
// Description:
//
// See Also:
//

template <class K, class T, class L, class HASH_K, class COMP, class HASH_T>
class RTRSLinkHashTableIterator
{
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRSLinkHashTableIterator(const RTRSLinkHashTableIterator<K,T,L,HASH_K,COMP,HASH_T>&);
	RTRSLinkHashTableIterator<K,T,L,HASH_K,COMP,HASH_T>& operator=(const RTRSLinkHashTableIterator<K,T,L,HASH_K,COMP,HASH_T>&);
		//
protected:
	RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T> *_hashTable;
		//
	RTRLiteSList<T,L> *_collisionList;
		//
	RTRLiteSList<T,L> *_lastCollisionList;
		//
	T *_object;
		//
	T *_nextObject;
		// by maintaining _nextObject to the current _object
		// we allow application to remove current _object from the hash table
		// during traversal
		//
	short _currentObjectRemoved;
		// flag to indicate whether the current _object was
		// removed via remove() function
		//
	void positionToNextObject();
		//
public:

// Positioning

	void start();
		// _TAG01 Positioning

	// _TAG01 Positioning
	inline bool off() const
	{
		RTPRECONDITION(_hashTable != 0);
		return(_object == 0);
	};

	// _TAG01 Positioning
	inline void forth()
	{
		RTPRECONDITION(_hashTable != 0);
		RTPRECONDITION(!off());
		positionToNextObject();
	};

	// _TAG01 Positioning
	inline bool offRight() const
	{
		RTPRECONDITION(_hashTable != 0);
		return(off());
	};

// Get

	// _TAG02 Get
	inline T *item() const
	{
		RTPRECONDITION(_hashTable != 0);
		RTPRECONDITION(!off());
		RTPRECONDITION(!_currentObjectRemoved);
		return(_object);
	};

// Modification
	void remove();
		// _TAG04 Modification

	void remove(K * key);	
		// Remove object, adjusting iterator if necessary
		// _TAG04 Modification


// Constructor
	RTRSLinkHashTableIterator(RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T> &hashTable);
		// _TAG Constructor

	RTRSLinkHashTableIterator();
        // _TAG Constructor

// Destructor

	// _TAG Destructor
	inline ~RTRSLinkHashTableIterator()
	{
	};

// Initialize

	// _TAG04 Initialize
	inline void initialize(RTRSLinkHashTable<K,T,L,HASH_K,COMP,HASH_T> &hashTable)
	{
		_hashTable = &hashTable;
		RTPRECONDITION(!_hashTable->error());
		_object = 0;
		_currentObjectRemoved = false;
		RTPOSTCONDITION(off());
	};

};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("slinkht.C")
#else
#include "rtr/slinkht.C"
#endif
#endif

#endif
