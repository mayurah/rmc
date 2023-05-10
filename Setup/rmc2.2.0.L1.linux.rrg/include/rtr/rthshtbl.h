//|-------------------------------------------------------
//|              Copyright (C) 1994 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: Tom Hansen, A. MacGaffey
// Created: 12/6/94
// Version: 2.0
//

#ifndef _rthshtbl_h 
#define _rthshtbl_h

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"
#include "rtr/linkl.h"
#include "rtr/dlinkht.h"

// Forward Declaration
template <class K, class T> class RTRHashTableIterator;

// Synopsis:
//
// Description:
//
// 	Definition of a "hash table" class
//
// See Also:
//

template <class K, class T> class RTRGenHash : public RTRDLink0
{
public:
// Constructor
	RTRGenHash(K *, T *);
		// _TAG Constructor

	inline T *value() const
	{
		return _value;
	}

	inline K *key() const
	{
		return _key;
	}

protected:
	K *_key;
	T *_value;

};

// Synopsis:
//
// Description:
//
//  Definition of a "hash table" class
//
// See Also:
//

template <class K, class T> class RTRHashTable
{
public:
// Constructor
	RTRHashTable(
			unsigned long (*)(const K *), 
			int n
			);
		// Must supply hash function and initial size of allocation.
		// _TAG Constructor

	RTRHashTable(const RTRHashTable<K,T>& t);
		// Copy constructor
		// _TAG Constructor

// Destructor
	~RTRHashTable();
		// _TAG Destructor

// Access
	RTRBOOL	hasKey(K *key) const;
		// Does table contain the item identified by the given key?
		// _TAG01 Access

	RTRBOOL hasItem(T *v) const;	
		// Does table contain the given item?
        // _TAG01 Access

	T* item(K *key) const;
		// The item associated with the given key.
        // _TAG01 Access

// Attributes
	int count() const;		
		// The  number of items in the table.
		// _TAG02 Attributes

// Modification
	void put(T *value, K *key);	
		// Insert `value' with `key' into table
		// _TAG03 Modification

	void remove(K *key);	
		// Remove item associated with `key', if present
		// _TAG03 Modification

	void resize(int);
		// change number of hash buckets and rehash the table
		// _TAG03 Modification

// Clean up
	RTRHashTable<K, T>& deleteContents();
		// _TAG05 Clean up

	RTRHashTable<K, T>& deleteContentsAndKeys();
		// _TAG05 Clean up

// Compatibility - Obsolete
	RTRHashTable<K,T>* duplicate();
		// _TAG06 Compatibility - Obsolete

// Quality
	int maxSearchLength() const;
		// _TAG08 Quality

	float averageSearchLength() const;
        // _TAG08 Quality



private:
		// Force instantiation
	typedef RTRGenHash<K, T> GenHashTableLink;

protected:
	static RTRBOOL compareKeyToObject(const K *key, const RTRGenHash<K, T> *g);

	RTRDLinkHashTableIterator<K, RTRGenHash<K, T>, RTRDLink0 > 
				*newIterator() const;

	RTRDLinkHashTable<K, RTRGenHash<K, T>, RTRDLink0> *_table;
	unsigned long (*_hashFunc)(const K *);
	
private:

	friend class RTRHashTableIterator<K,T>;

};

// Synopsis:
//
// Description:
//
// See Also:
//

template <class K, class T> class RTRHashTableIterator
{
public:

// Constructor
	RTRHashTableIterator(const RTRHashTable<K,T>& t);
		// _TAG Constructor

//Destructor
	~RTRHashTableIterator();
		// _TAG Destructor

// Container
	const RTRHashTable<K,T>& 	container() const;
		// The hash table on which this iterator is operating.
		// _TAG01 Container

// Positioning
	void start();
		// Position iterator at start of table
		// _TAG02 Positioning

	void forth();
		// Increment to next valid position in table
        // _TAG02 Positioning

	RTRBOOL off() const;
		// Have all items been traversed?
        // _TAG02 Positioning

// Access
	K* currentKey() const;
		// Ptr to key located at current position
		// _TAG03 Access

	T* currentItem() const;
		// Ptr to item located at current position
        // _TAG03 Access

// Modification
	void remove(K * key);	
		// Remove object, adjusting iterator if necessary
		// _TAG04 Modification

	void reset(const RTRHashTable<K,T>& table);
		// Reset to use different hash table
		// _TAG04 Modification

protected:
// Data
	const RTRHashTable<K,T> *_table;
	RTRDLinkHashTableIterator<K, RTRGenHash<K, T>, RTRDLink0>  *_iterator;
	RTRBOOL	is_off;
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("rthshtbl.C")
#else
#include "rtr/rthshtbl.C"
#endif
#endif

#endif  // _rthshtbl_h
