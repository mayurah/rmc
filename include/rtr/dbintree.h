//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters                               --
//|               1400 Kensington Road, Oak Brook, Il. 60523                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: J. Barcalow
// Created: "Feb. 20, 1998"
// Version: 1.0

#ifndef _rtr_dbintree_h_
#define _rtr_dbintree_h_

#include "rtr/rtllist.h"

// Synopsis:
// #include "dbintree.h"
//
// Description:
// This class is a data structure template for a binary tree.
// Classes which wish to be placed in a balanced tree must be 
// subclasses of RTRDBinaryNode.
//
// The template class has three template parameters.  T (tree
// element) is the class of the objects which are inserted into
// the tree.  K (key) is the class used for comparisons.  
// N (node) is the class of the type of RTRDBinaryNode of which T 
// is a subclass. (RTRDBinaryNode, RTRDBinaryNode1, etc.)
//
// The constructor takes one argument, a function.  This function
// must take a tree element as an argument and return a key.  It
// is called the key function, and it is used to compare tree
// elements.
//
// See Also:
// RTRDBinaryNode, RTRDLink, RTRDLinkList
//
// Inherits:
//

template<class T, class K, class N> class RTRDBinaryTree
{
public:
// Constructor
	RTRDBinaryTree(const K &(* f)(const T &));
		// _TAG Constructor
	
	RTRDBinaryTree(T &root, const K &(* f)(const T &));
		// _TAG Constructor

// Destructor
	virtual ~RTRDBinaryTree();
		// _TAG Destructor

// Accessing	
	T *first() const;
		// ENSURE: has(node) implies key(result) <= key(node)
		// _TAG01 Accessing
	
	T *last() const;
		// ENSURE: has(node) implies key(result) >= key(node)
		// _TAG01 Accessing

	N *root() const;
		// _TAG01 Accessing
	
	unsigned int count() const;
		// _TAG01 Accessing

// Query
	RTRBOOL has(const T &node) const;
		// _TAG02 Query
	
	RTRBOOL isEmpty() const;
		// ENSURE: has(node) implies result == RTRFALSE
		// _TAG02 Query

// Node Operations
	virtual void insertNode(T &node);
		// REQUIRE: node.isEmpty()
		// ENSURE: has(node)
		// ENSURE: key(node) <= key(node.next())
		// ENSURE: key(node) >= key(node.prev())
		// _TAG03 Node Operations
	
	virtual void insertNodeAtEqualNode(T &node, T &equalNode);
		// REQUIRE: node.isEmpty()
		// REQUIRE: has(equalNode)
		// REQUIRE: key(node) == key(equalNode);
		// ENSURE: has(node)
		// ENSURE: key(node) <= key(node.next())
		// ENSURE: key(node) >= key(node.prev())
		// _TAG03 Node Operations

	virtual void removeNode(T &node);
		// REQUIRE: has(node)
		// ENSURE: !has(node)
		// _TAG03 Node Operations
	
	void removeFromFirstToNode(T &node);
		// REQUIRE: has(node)
		// ENSURE: !has(node)
		// ENSURE: isEmpty() || (key(node) <= key(first()))
		// _TAG03 Node Operations
	
	void removeFromNodeToLast(T &node);
		// REQUIRE: has(node)
		// ENSURE: !has(node)
		// ENSURE: isEmpty() || (key(node) >= key(last()))
		// _TAG03 Node Operations

// Key Operations
	void removeAllEqualTo(const K &k);
		// ENSURE: listAllEqualTo(k)->empty()
		// _TAG04 Key Operations
	
	void removeAllBefore(const K &k);
		// ENSURE: k < key(first())
		// _TAG04 Key Operations
	
	void removeAllAfter(const K &k);
		// ENSURE: k > key(last())
		// _TAG04 Key Operations
	
// Access Operations
	RTRLinkedList<T> *asList() const;
		// ENSURE: result.has(node) <=> has(node)
		// _TAG05 Access Operations
	
	RTRLinkedList<T> *listAllEqualTo(const K &k) const;
		// ENSURE: result.has(node) implies key(node) == k
		// _TAG05 Access Operations
	
	RTRLinkedList<T> *listAllLessThan(const K &k) const;
		// ENSURE: result.has(node) implies key(node) < k
		// _TAG05 Access Operations
	
	RTRLinkedList<T> *listAllGreaterThan(const K &k) const;
		// ENSURE: result.has(node) implies key(node) > k
		// _TAG05 Access Operations
	
	RTRLinkedList<T> *listAllBetween(const K &firstKey, const K &lastKey) const;
		// ENSURE: result.has(node) implies \\
		//         (key(node) > firstKey) && (key(node) < lastKey)
		// _TAG05 Access Operations
	
	T *findFirst(const K &k) const;
		// "minimum" node == k
		// ENSURE: result == NULL implies listAllEqualTo(k)->empty()
		// ENSURE: result != NULL implies key(result) == k	
		// ENSURE: (result != NULL) && (result.prev() != NULL) implies \\
		//         key(result.prev()) < k
		// _TAG05 Access Operations

	T *findLast(const K &k) const;
		// "maximum" node == k
		// ENSURE: result == NULL implies listAllEqualTo(k)->empty()
		// ENSURE: result != NULL implies key(result) == k
		// ENSURE: (result != NULL) && (result.next() != NULL) implies \\
		//         key(result.next()) > k
		// _TAG05 Access Operations

	T *findBefore(const K &k) const;
		// "maximum" node < k
		// ENSURE: result == NULL implies listAllEqualTo(k)->empty()
		// ENSURE: result != NULL implies key(result) < k
		// ENSURE: (result != NULL) && (result.next() != NULL) implies \\
		//         key(result.next()) >= k
		// _TAG05 Access Operations

	T *findAfter(const K &k) const;
		// "minimum" node > k
		// ENSURE: result == NULL implies listAllEqualTo(k)->empty()
		// ENSURE: result != NULL implies key(result) > k
		// ENSURE: (result != NULL) && (result.prev() != NULL) implies \\
		//         key(result.prev()) <= k
		// _TAG05 Access Operations

	T *findFirstNotBefore(const K &k) const;
		// "minimum" node >= k
		// ENSURE: result == NULL implies listAllEqualTo(k)->empty()
		// ENSURE: result == NULL implies listAllGreaterThan(k)->empty()
		// ENSURE: result != NULL implies key(result) >= k
		// ENSURE: (result != NULL) && (result.prev() != NULL) implies \\
		//         key(result.prev()) < k
		// _TAG05 Access Operations

	T *findLastNotAfter(const K &k) const;
		// "minimum" node <= k
		// ENSURE: result == NULL implies listAllEqualTo(k)->empty()
		// ENSURE: result == NULL implies listAllLessThan(k)->empty()
		// ENSURE: result != NULL implies key(result) <= k
		// ENSURE: (result != NULL) && (result.next() != NULL) implies \\
		//         key(result.next()) > k
		// _TAG05 Access Operations

// Operations
	virtual void removeAll();
		// ENSURE: isEmpty()
		// _TAG06 Operations

	virtual void removeAllAndDestroy();
		// ENSURE: isEmpty()
		// _TAG06 Operations

// Support
	const K &key(const T &) const;
		// _TAG06 Support

	void printTree(const char *) const;
		// _TAG07 Support

protected:
// Utilities
	N *findOne(const K &) const;
	N *findInsertionNode(const K &) const;	
	void insertNodeAt(T &, N *);

// Data
	N *_root;
	N *_last;
	N *_first;
	unsigned int _count;
	const K &(* _key)(const T &);

private:
// Copy constructor -- Don't define!
	RTRDBinaryTree(const RTRDBinaryTree<T,K,N>&);

// Assignment -- Don't define!
	RTRDBinaryTree<T,K,N>& operator=(const RTRDBinaryTree<T,K,N>&);

// Leave this commment for george formatting
};


#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("dbintree.C")
#else
#include "rtr/dbintree.C"
#endif
#endif


#endif // _rtr_bintree_h_

