//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters                               --
//|               1400 Kensington Road, Oak Brook, Il. 60523                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: J. Barcalow
// Created: "Feb. 20, 1998"
// Version: 1.0

#include "rtr/dbaltree.h"

#ifndef _rtr_dbaltree_C_
#define _rtr_dbaltree_C_

// public:
template<class T, class K, class N>
RTRDBalancedTree<T,K,N>::RTRDBalancedTree(const K &(* f)(const T &))
	: RTRDBinaryTree<T,K,N>(f)
{
}

template<class T, class K, class N>
RTRDBalancedTree<T,K,N>::RTRDBalancedTree(T &root, const K &(* f)(const T &))
	: RTRDBinaryTree<T,K,N>(root, f)
{
}

template<class T, class K, class N>
RTRDBalancedTree<T,K,N>::~RTRDBalancedTree()
{
}

template<class T, class K, class N>
void RTRDBalancedTree<T,K,N>::insertNode(T &node)
{
	RTPRECONDITION(!node.isInTree());

	RTRDBinaryTree<T,K,N>::insertNode(node);
	node.setRed();
	N *currentNode = &node;
	N *otherNode;
	while ((!currentNode->isRoot()) && ((N *)currentNode->parent())->isRed())
	{
		if (currentNode->parent()->isLeftChild())
		{
			otherNode = (N *) currentNode->parent()->parent();
			if (!otherNode)
				;
			else if ( otherNode->rightChild() &&
					  ((N *)otherNode->rightChild())->isRed() )
			{
				((N *)currentNode->parent())->setBlack();
				((N *)otherNode->rightChild())->setBlack();
				otherNode->setRed();
				currentNode = otherNode;
			}
			else
			{
				if (!currentNode->isLeftChild())
				{
					currentNode = (N *) currentNode->parent();
					leftRotate(currentNode);
				}
				((N *)currentNode->parent())->setBlack();
				((N *)currentNode->parent()->parent())->setRed();
				rightRotate((N *)currentNode->parent()->parent());
			}
		}
		else
		{
			otherNode = (N *)currentNode->parent()->parent();
			if (!otherNode)
				;
			else if (otherNode->leftChild() &&
				((N *)otherNode->leftChild())->isRed())
			{
				((N *)currentNode->parent())->setBlack();
				((N *)otherNode->leftChild())->setBlack();
				otherNode->setRed();
				currentNode = otherNode;
			}
			else
			{
				if (currentNode->isLeftChild())
				{
					currentNode = (N *) currentNode->parent();
					rightRotate(currentNode);
				}
				((N *)currentNode->parent())->setBlack();
				((N *)currentNode->parent()->parent())->setRed();
				leftRotate((N *)currentNode->parent()->parent());
			}
		}
	}
	this->_root->setBlack();

	// RTPOSTCONDITION(isBalanced());
	// RTPOSTCONDITION(has(node));
}

template<class T, class K, class N>
void RTRDBalancedTree<T,K,N>::removeNode(T &node)
{
	RTPRECONDITION(has(node));

	N *current, *parent, *replacement;
	RTRBOOL fixUp;
	
	// find node to replace removed node
	replacement = (N *) node.removeReplacement();
		
	if (replacement)
	{
		fixUp = replacement->isBlack();
		replacement->setColor(node.color());
		current = (N *) replacement->rightChild();
		if ( replacement->parent() != &node )
			parent = (N *) replacement->parent();
		else
			parent = replacement;
	}	
	else
	{
		fixUp = node.isBlack();
		current = 0;
		parent = (N *) node.parent();
	}
	
	// perform the remove
	RTRDBinaryTree<T,K,N>::removeNode(node);

	// rebalance tree
	if (fixUp)
		removeNodeFixUp(current, parent);

	// RTPOSTCONDITION(!has(node));
	// RTPOSTCONDITION(isBalanced());
}

template<class T, class K, class N>
void RTRDBalancedTree<T,K,N>::removeNodeFixUp(N *node, N *parent)
{
	N *currentNode = node;
	N *currentParent = parent;
	N *otherNode;
	
	while ( currentParent && (!currentNode || currentNode->isBlack()) )
	{
		if (currentNode == (N *) currentParent->leftChild())
		{
			otherNode = (N *) currentParent->rightChild();
			if (!otherNode)
			{
// case: left, empty sibling
				currentNode = currentParent;
				currentParent = (N *) currentNode->parent();
			}
			else if (otherNode->isBlack())
			{
				if ( otherNode->rightChild() &&
					 ((N *)otherNode->rightChild())->isRed() )
				{
// case: left, fix 2
					leftRotate(currentParent);
					otherNode->setColor(currentParent->color());
					currentParent->setBlack();
					((N *)otherNode->rightChild())->setBlack();
					currentParent = 0; // exit loop
				}
				else if ( otherNode->leftChild() &&
						  ((N *)otherNode->leftChild())->isRed())
				{
// case: left, fix 3
					rightRotate(otherNode);
					leftRotate(currentParent);
					((N *)otherNode->parent())->setColor(currentParent->color());
					currentParent->setBlack();
					currentParent = 0; // exit loop
				}
				else // both children are black
				{
// case: left, fix 1
					otherNode->setRed();
					currentNode = currentParent;
					currentParent = (N *) currentNode->parent();
						// forces recursion
				}
			}
			else // otherNode->isRed()
			{
// case: left, fix 4
				leftRotate(currentParent);
				otherNode->setBlack();
				currentParent->setRed();
					// currentNode not reassigned or color changed forces recursion
			}
		}
		else // currentNode is rightChild
		{
			otherNode = (N *)currentParent->leftChild();
			if (!otherNode)
			{
				currentNode = currentParent;
				currentParent = (N *) currentNode->parent();
// case: right, empty sibling
			}
			else if (otherNode->isBlack())
			{
				if ( otherNode->leftChild() &&
					 ((N *)otherNode->leftChild())->isRed() )
				{
// case: right, fix 2
					rightRotate(currentParent);
					otherNode->setColor(currentParent->color());
					currentParent->setBlack();
					((N *)otherNode->leftChild())->setBlack();
					currentParent = 0; // exit loop
				}
				else if ( otherNode->rightChild() &&
						  ((N *)otherNode->rightChild())->isRed() )
				{
// case: right, fix 3
					leftRotate(otherNode);
					rightRotate(currentParent);
					((N *)otherNode->parent())->setColor(currentParent->color());
					currentParent->setBlack();
					currentParent = 0; // exit loop
				}
				else // both children are black
				{
// case: right, fix 1
					otherNode->setRed();
					currentNode = currentParent;
					currentParent = (N *)currentNode->parent();
						// forces recursion
				}
			}
			else // otherNode->isRed()
			{
// case: right, fix 4
				rightRotate(currentParent);
				otherNode->setBlack();
				currentParent->setRed();
					// currentNode not reassigned or color changed forces recursion
			}
		}

	}
	if (currentNode)
		currentNode->setBlack();
}


template<class T, class K, class N>
RTRBOOL RTRDBalancedTree<T,K,N>::isBalanced() const
{
	return !this->_root || this->_root->isBalanced();
}


template<class T, class K, class N>
void RTRDBalancedTree<T,K,N>::leftRotate(N *node)
{
	N *y = (N *) node->rightChild();
	node->putRightChild(y->leftChild());
	if (node->isRoot())
	{
		this->_root = y;
		y->putParent(0);
	}
	else if (node->isLeftChild())
		node->parent()->putLeftChild(y);
	else
		node->parent()->putRightChild(y);
	y->putLeftChild(node);
}

template<class T, class K, class N>
void RTRDBalancedTree<T,K,N>::rightRotate(N *node)
{
	N *y = (N *) node->leftChild();
	node->putLeftChild(y->rightChild());
	if (node->isRoot())
	{
		this->_root = y;
		y->putParent(0);
	}
	else if (node->isLeftChild())
		node->parent()->putLeftChild(y);
	else
		node->parent()->putRightChild(y);
	y->putRightChild(node);

}

#endif // _rtr_dbaltree_C_

