//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters                               --
//|               1400 Kensington Road, Oak Brook, Il. 60523                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: J. Barcalow
// Created: "Feb. 20, 1998"
// Version: 1.0


#ifndef _rtr_drbnode_h_
#define _rtr_drbnode_h_

#include "rtr/dbinnode.h"

typedef enum { RED, BLACK } RedBlack;
	// Color of node

// Synopsis:
// #include "rtr/drbnode.h"
//
// Description:
// Any class which wishes to be added to a RTRDBalancedTree must
// be a subclass of this class.  This classes inherits from 
// RTRDBinaryNode so it has the parent, left child, right child 
// structure common to every node in a binary tree.  This class
// also has a RedBlack color attribute used to maintain the 
// the invariants in a RTRDBalancedTree.
//
// See Also:
// RTRDBinaryTree, RTRDBalancedTree, RTRDLink
//
// Inherits:
// RTRDBinaryNode
//

class RTRDRedBlackNode : public RTRDBinaryNode
{
public:
// Constructor
	RTRDRedBlackNode();
		// _TAG Constructor

// Destructor
	virtual ~RTRDRedBlackNode();
		// _TAG Destructor
	
// State
	inline void setRed();
		// ENSURE : color() == RED
		// _TAG01 State

	inline void setBlack();
		// ENSURE : color() == BLACK
		// _TAG01 State

	inline void setColor(RedBlack color);
		// ENSURE : color() == color
		// _TAG01 State

	inline RedBlack color() const;
		// _TAG01 State

// Query
	inline RTRBOOL isRed() const;
		// _TAG02 Query
	inline RTRBOOL isBlack() const;
		// _TAG02 Query

// Testing 
	RTRBOOL isBalanced() const;
		// _TAG03 Testing

	RTRBOOL isColorBalanced() const;
		// _TAG03 Testing

	RTRBOOL isBlackHeightBalanced() const;
		// _TAG03 Testing

	int blackHeight() const;
		// _TAG03 Testing

protected:
// Data
	RedBlack _color;

private:
// Copy constructor -- Don't define!
	RTRDRedBlackNode(const RTRDRedBlackNode&);

// Assignment -- Don't define!
	RTRDRedBlackNode& operator=(const RTRDRedBlackNode&);

// Leave this commment for george formatting
};


inline void RTRDRedBlackNode::setRed()
{
	_color = RED;
}

inline void RTRDRedBlackNode::setBlack()
{
	_color = BLACK;
}

inline void RTRDRedBlackNode::setColor(RedBlack color)
{
	_color = color;
}


inline RedBlack RTRDRedBlackNode::color() const
{
	return _color;
}

inline RTRBOOL RTRDRedBlackNode::isRed() const
{
	return (_color == RED) ? RTRTRUE : RTRFALSE;
}

inline RTRBOOL RTRDRedBlackNode::isBlack() const
{
	return (_color == BLACK) ? RTRTRUE : RTRFALSE;
}

#endif // _rtr_drbnode_h_

