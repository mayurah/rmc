//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters                               --
//|               1400 Kensington Road, Oak Brook, Il. 60523                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: J. Barcalow
// Created: "Feb. 20, 1998"
// Version: 1.0

#ifndef _rtr_dbaltree_h_
#define _rtr_dbaltree_h_

#include "rtr/dbintree.h"

//
// Synopsis:
// #include "rtr/dbaltree.h"
//
// Description:
// This class is a data structure template for a "balanced"
// binary tree.  This balanced tree is implemented as a 
// red-black tree. 
//
// A red-back tree has two invariants :
// \bullet
// 		o All paths from root to leaf have = # of black counts
// 		o No path from root to leaf has 2 consecutive red nodes
// \endbullet
// These invariants are established at tree construction time
// and are maintained as long as the "safe" operations, 
// insertNode and removeNode are used.
//
// The height of a red-black tree is never more than 2*lg(n) 
// where n is the number of nodes in the tree.
//
// Classes which wish to be placed in a balanced tree must be 
// subclasses of RTRDRedBlackNode.
//
// See Also:
// RTRDRedBlackNode, RTRDBinaryNode
//
// Inherits:
// RTRDBinaryTree

template<class T, class K, class N>
class RTRDBalancedTree : public RTRDBinaryTree<T, K, N>
{
public:
// Constructor
	RTRDBalancedTree(const K &(* f)(const T &));
		// _TAG Constructor

	RTRDBalancedTree(T &, const K &(* f)(const T &));
		// _TAG Constructor

// Destructor
	virtual ~RTRDBalancedTree();
		// _TAG Destructor

// Safe Operations
	virtual void insertNode(T &node);
		// REQUIRE: !node.isInTree()
		// ENSURE: has(node)
		// ENSURE: isBalanced()
		// _TAG01 Safe Operations

	virtual void removeNode(T &node);
		// REQUIRE: has(node)
		// ENSURE: !has(node)
		// ENSURE: isBalanced()
		// _TAG01 Safe Operations

// Testing
	RTRBOOL isBalanced() const;
		// ENSURE: result implies all paths from root to leaf have
		//         = black counts
		// ENSURE: result implies no path from root to leaf has 2 
		//         consecutive red nodes
		// _TAG02 Testing

protected:
	void rightRotate(N *);
	void leftRotate(N *);
	void removeNodeFixUp(N *, N *);

private:
// Copy constructor -- Don't define!
	RTRDBalancedTree(const RTRDBalancedTree<T,K,N>&);

// Assignment -- Don't define!
	RTRDBalancedTree<T,K,N>& operator=(const RTRDBalancedTree<T,K,N>&);

// Leave this commment for george formatting
};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("dbaltree.C")
#else
#include "rtr/dbaltree.C"
#endif
#endif


#endif // _rtr_baltree_h_

