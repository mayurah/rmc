//|-----------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 8/11/94
//

#ifndef __RTRDLinkHashTable
#define __RTRDLinkHashTable

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/ldlinkl.h"

template <class K, class T, class L> class RTRDLinkHashTableIterator;

// Synopsis:
//
// Description:
//
// See Also:
//

template <class K, class T, class L>
class RTRDLinkHashTable
{
	friend class RTRDLinkHashTableIterator<K,T,L>;
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRDLinkHashTable(const RTRDLinkHashTable<K, T, L>&);
	RTRDLinkHashTable<K, T, L>& operator=(const RTRDLinkHashTable<K, T, L>&);
		// Force instantiation
	typedef RTRLiteDLinkList<T,L> HashTableBucketList;
		//
protected:
	int _hashTableSize;
		//
	int _count;
		//
	RTRLiteDLinkList<T,L> *_hashTable;
		//
	unsigned long (*_hashKey)(const K*);
		//
	RTRBOOL (*_compareKeyToObject)(const K*, const T*);
		//
	unsigned long (*_hashObject)(const T*);
		//
public:

// Constructor
	RTRDLinkHashTable(
		int hashTableSize,
		unsigned long (*hashKey)(K*),
		RTRBOOL (*compareKeyToObject)(K*, T*),
		unsigned long (*hashObject)(T*) = 0,
		RTRBOOL adjustSize = RTRTRUE
		);
		// _TAG Constructor

	RTRDLinkHashTable(
		int hashTableSize,
		unsigned long (*hashKey)(const K*),
		RTRBOOL (*compareKeyToObject)(const K*, const T*),
		unsigned long (*hashObject)(const T*) = 0,
		RTRBOOL adjustSize = RTRTRUE
		);
		// _TAG Constructor

// Destructor
	virtual ~RTRDLinkHashTable();
		// _TAG Destructor

// State

	// _TAG01 State	
	inline RTRBOOL error() const
	{
		return(_hashTable == 0 ? RTRTRUE : RTRFALSE);
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
		_hashTable[_hashKey(key)%(unsigned int)_hashTableSize].putFirst(object);
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
	inline void remove(T *object)
	{
		RTPRECONDITION(!error());
//		RTPRECONDITION(expensiveHas(object));
		(toL(object))->remove();
		--_count;
		RTPOSTCONDITION(_count >= 0);
	};

	void removeAll();
		// _TAG05 Remove

	void removeAllAndDestroy();
		// _TAG05 Remove

// Get
	T *get(K *key, unsigned long hashsum) const;
		// _TAG06 Get

	// _TAG06 Get
	inline T *get(K *key) const
	{
		return(get(key, _hashKey(key)));
	};

	// _TAG06 Get
	inline RTRLiteDLinkList<T,L> *getCollisionList(int bucket)
	{
		RTPRECONDITION(!error());
		RTPRECONDITION(bucket >= 0 && bucket < _hashTableSize);
		return(&_hashTable[bucket]);
	};

	// _TAG06 Get
	inline RTRLiteDLinkList<T,L> *getCollisionList(unsigned long hashsum)
	{
		RTPRECONDITION(!error());
		return(&_hashTable[hashsum%(unsigned int)_hashTableSize]);
	};

	// _TAG06 Get
	inline RTRLiteDLinkList<T,L> *getCollisionList(K *key)
	{
		RTPRECONDITION(!error());
		return(&_hashTable[_hashKey(key)%(unsigned int)_hashTableSize]);
	};

// Resize
	void resize(int newHashTableSize, RTRBOOL adjustSize = RTRTRUE);
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
	RTRBOOL expensiveHas(T *object) const;
};

// Synopsis:
//
// Description:
//
// See Also:
//

template <class K, class T, class L>
class RTRDLinkHashTableIterator
{
private:
		// Define the following but do not implement.
		// Will cause a compile time error if called.
	RTRDLinkHashTableIterator(const RTRDLinkHashTableIterator<K, T, L>&);
	RTRDLinkHashTableIterator<K, T, L>& operator=(const RTRDLinkHashTableIterator<K, T, L>&);
		//
protected:
	RTRDLinkHashTable<K,T,L> *_hashTable;
		//
	RTRLiteDLinkList<T,L> *_collisionList;
		//
	RTRLiteDLinkList<T,L> *_lastCollisionList;
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
	inline RTRBOOL off() const
	{
		RTPRECONDITION(_hashTable != 0);
		return((_object == 0) ? RTRTRUE : RTRFALSE);
	};

	// _TAG01 Positioning
	inline void forth()
	{
		RTPRECONDITION(_hashTable != 0);
		RTPRECONDITION(!off());
		positionToNextObject();
	};

	// _TAG01 Positioning
	inline RTRBOOL offRight() const
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
	RTRDLinkHashTableIterator(RTRDLinkHashTable<K,T,L> &hashTable);
		// _TAG Constructor

	RTRDLinkHashTableIterator();
        // _TAG Constructor

// Destructor

	// _TAG Destructor
	inline ~RTRDLinkHashTableIterator()
	{
	};

// Initialize

	// _TAG04 Initialize
	inline void initialize(RTRDLinkHashTable<K,T,L> &hashTable)
	{
		_hashTable = &hashTable;
		RTPRECONDITION(!_hashTable->error());
		_object = 0;
		_currentObjectRemoved = RTRFALSE;
		RTPOSTCONDITION(off());
	};

};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("dlinkht.C")
#else
#include "rtr/dlinkht.C"
#endif
#endif

#endif
