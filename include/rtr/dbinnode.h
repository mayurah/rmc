//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters                               --
//|               1400 Kensington Road, Oak Brook, Il. 60523                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: J. Barcalow
// Created: "Feb. 20, 1998"
// Version: 1.0

#ifndef _rtr_dbinnode_h_
#define _rtr_dbinnode_h_

#include "rtr/rtrdefs.h"

// Synopsis:
// #include "rtr/dbinnode.h"
//
// Description:
// Any class which wishes to be added to a RTRDBinaryTree must
// be a subclass of this class.  This classes encapsulates the
// parent, left child, right child structure common to every
// node in a binary tree.
//
// See Also:
// RTRDBinaryTree, RTRDLink
//
// Inherits:
//

class RTRDBinaryNode
{
public:
// Constructor
	RTRDBinaryNode();
		// _TAG Constructor

// Destructor
	virtual ~RTRDBinaryNode();
		// _TAG Destructor

// Accessing
	inline RTRDBinaryNode *rightChild() const;
		// _TAG01 Accessing

	inline RTRDBinaryNode *leftChild() const;
		// _TAG01 Accessing

	inline RTRDBinaryNode *parent() const;
		// _TAG01 Accessing

	virtual RTRDBinaryNode *next() const;
		// ENSURE: value of result >= value of this
		// _TAG01 Accessing

	virtual RTRDBinaryNode *prev() const;
		// ENSURE: value of result >= value of this
		// _TAG01 Accessing

// Assignment
	void putRightChild(RTRDBinaryNode *node);
		// ENSURE: rightChild() == node
		// ENSURE: !node || node->parent() == this
		// _TAG02 Assignment

	void putLeftChild(RTRDBinaryNode *node);
		// ENSURE: leftChild() == node
		// ENSURE: !node || node->parent() == this
		// _TAG02 Assignment

	void putParent(RTRDBinaryNode *node);
		// REQUIRE: !node || \\
		//          (node->leftChild() == this) || \\
		//          (node->rightChild() == this)
		// ENSURE: !parent() || \\
		//         (parent()->leftChild() == this) || \\
		//         (parent()->rightChild() == this) 
		// _TAG02 Assignment

// Query
	inline RTRBOOL isRoot() const;
		// ENSURE: result == RTRTRUE implies parent() == NULL
		// _TAG03 Query

	inline RTRBOOL isLeaf() const;
		// ENSURE: result == RTRTRUE implies \\
		//         (leftChild() == NULL) && (rightChild() == NULL)
		// _TAG03 Query

	inline RTRBOOL isInTree() const;
		// _TAG03 Query

	inline RTRBOOL hasTwoChildren() const;
		// _TAG03 Query

	inline RTRBOOL isLeftChild() const;
		// _TAG03 Query

	int depth() const;
		// _TAG03 Query

	const RTRDBinaryNode *oldestAncestor() const;
		// ENSURE: result.parent() == NULL
		// _TAG03 Query

// Safe Operations
	void removeFromTree();
		// ENSURE : (!isInTree());
		// _TAG04 Safe Operations

// Unsafe operations
	inline void empty();
		// ENSURE: (!isInTree());
		// _TAG05 Unsafe Operations

	void pruneTree();
		// ENSURE: (!isInTree());
		// _TAG05 Unsafe Operations

	void pruneTreeAndDestroy();
		// _TAG05 Unsafe Operations

// Private - Accessing for RTRDBinaryTree 
	RTRDBinaryNode *removeReplacement() const;
		// _TAG06 Private - Accessing for RTRDBinaryTree

protected:
	RTRDBinaryNode *minRight() const;
	RTRDBinaryNode *maxLeft() const;

// Data
	RTRDBinaryNode *_leftChild;
	RTRDBinaryNode *_rightChild;
	RTRDBinaryNode *_parent;

private:
// Copy constructor -- Don't define!
	RTRDBinaryNode(const RTRDBinaryNode&);

// Assignment -- Don't define!
	RTRDBinaryNode& operator=(const RTRDBinaryNode&);

// Leave this commment for george formatting
};


inline RTRDBinaryNode *RTRDBinaryNode::leftChild() const
{
	return _leftChild;
}
	 
inline RTRDBinaryNode *RTRDBinaryNode::rightChild() const
{
	return _rightChild;
}
		  
inline RTRDBinaryNode *RTRDBinaryNode::parent() const
{
  return _parent;
}
		



inline RTRBOOL RTRDBinaryNode::isRoot() const 
{
	return _parent ? RTRFALSE : RTRTRUE;
}

inline RTRBOOL RTRDBinaryNode::isLeaf() const
{
	return (!_leftChild && !_rightChild) ? RTRTRUE : RTRFALSE;
}

inline RTRBOOL RTRDBinaryNode::isInTree() const
{
	return (isRoot() && isLeaf()) ? RTRFALSE : RTRTRUE;
}

inline RTRBOOL RTRDBinaryNode::hasTwoChildren() const
{
	return (_leftChild && _rightChild) ? RTRTRUE : RTRFALSE;
}

inline RTRBOOL RTRDBinaryNode::isLeftChild() const 
{
    return (!isRoot() && (_parent->_leftChild == this)) ? RTRTRUE : RTRFALSE;
}

inline void RTRDBinaryNode::empty()
{
	_leftChild = _rightChild = _parent = 0;
}

#endif // _rtr_dbinnode_h_

