//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters                               --
//|               1400 Kensington Road, Oak Brook, Il. 60523                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: J. Barcalow
// Created: "Feb. 20, 1998"
// Version: 1.0

#include "rtr/dbintree.h"

#ifndef _rtr_dbintree_C_
#define _rtr_dbintree_C_

// public:
template<class T, class K, class N>
RTRDBinaryTree<T,K,N>::RTRDBinaryTree(const K &(* f)(const T &))
	: _root(0), _key(f), _last(0), _first(0), _count(0)
{
}

template<class T, class K, class N>
RTRDBinaryTree<T,K,N>::RTRDBinaryTree(T &root, const K &(* f)(const T &))
	: _root(&root), _key(f), _last(&root), _first(&root), _count(0)
{
	RTPRECONDITION(!root.parent());
}

template<class T, class K, class N>
RTRDBinaryTree<T,K,N>::~RTRDBinaryTree()
{
}


template<class T, class K, class N>
RTRBOOL RTRDBinaryTree<T,K,N>::has(const T &node) const
{
	return (node.oldestAncestor() == _root) ? RTRTRUE : RTRFALSE;
}

template<class T, class K, class N>
RTRBOOL RTRDBinaryTree<T,K,N>::isEmpty() const
{
	return (_root) ? RTRFALSE : RTRTRUE;
}

template<class T, class K, class N>
unsigned int RTRDBinaryTree<T,K,N>::count() const
{
	return _count;
}

template<class T, class K, class N>
N *RTRDBinaryTree<T,K,N>::root() const
{
	return _root;
}

template<class T, class K, class N>
T *RTRDBinaryTree<T,K,N>::first() const
{
/*
	if (isEmpty())
		return 0;
	N *currentNode = _root;
	while (currentNode->leftChild())
		currentNode = (N *) currentNode->leftChild();
	return (T *)currentNode;
*/
	return (T *)_first;
}

template<class T, class K, class N>
T *RTRDBinaryTree<T,K,N>::last() const
{
/*	if (isEmpty())
		return 0;
	N *currentNode = _root;
	while (currentNode->rightChild())
		currentNode = (N *) currentNode->rightChild();
	return (T *)currentNode;
*/
	return (T *)_last;
}


template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::insertNode(T &node)
{
	RTPRECONDITION(!node.isInTree());
	if (!_root)
	{
		_root = &node;
		_first = &node;
		_last = &node;
		_count++;
	}
	else
	{
		N *currentNode = findInsertionNode(key(node));

		insertNodeAt(node, currentNode);
	}

	// RTPOSTCONDITION(has(node));
	// RTPOSTCONDITION(!((N&)node).next() || (key(node) <= key(*(T *)((N&)node).next())));
	// RTPOSTCONDITION(!((N&)node).prev() || (key(node) >= key(*(T *)((N&)node).prev())));
}

template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::insertNodeAtEqualNode(T &node, T &equalNode)
{
	RTPRECONDITION(!node.isInTree());
	RTPRECONDITION(has(equalNode));
	RTPRECONDITION(key(equalNode) == key(node));
	
	N *currentNode;
	N *comparisonNode = &equalNode;
	while (comparisonNode)
	{
		currentNode = comparisonNode;
		if (key(equalNode) < key(*(T *)comparisonNode))
			comparisonNode = (N *) comparisonNode->leftChild();
		else
			comparisonNode = (N *) comparisonNode->rightChild();
	}
	insertNodeAt(node, currentNode);
	
	// RTPOSTCONDITION(has(node));
	// RTPOSTCONDITION(!((N&)node).next() || (key(node) <= key(*(T *)((N&)node).next())));
	// RTPOSTCONDITION(!((N&)node).prev() || (key(node) >= key(*(T *)((N&)node).prev())));
}

template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::insertNodeAt(T &node, N *currentNode)
{
	if (key(node) < key(*(T *)currentNode))
	{
		currentNode->putLeftChild(&node);
		if (currentNode == _first)
			_first = &node;
	}
	else
	{
		currentNode->putRightChild(&node);
		if (currentNode == _last)
			_last = &node;
	}
	_count++;
}

template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::removeNode(T &node)
{
	if (node.isRoot())
	{
		N *replacement = (N *) node.removeReplacement();
		_root = replacement;
	}
	if (&node == _first)
		_first = (N *) ((N&)node).next();
	else if (&node == _last)
		_last = (N *) ((N&)node).prev();
	node.removeFromTree();
	_count--;
	// RTPOSTCONDITION(!has(node));
}

template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::removeFromFirstToNode(T &node)
{
	RTPRECONDITION(has(node));
	N *currentNode = &node;
	N *possibleNewRoot = (N *) ((N&)node).next();
	while (currentNode)
	{
		N *prevNode = (N *) currentNode->prev();
		removeNode(*(T *)currentNode);
		if (currentNode == _root)
			_root = possibleNewRoot;
		currentNode = prevNode;
	}
	// RTPOSTCONDITION(!has(node));
	// RTPOSTCONDITION( isEmpty() || (key(node) <= key(*(T *)last())) );
}


template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::removeFromNodeToLast(T &node)
{
	RTPRECONDITION(has(node));
	N *currentNode = &node;
	N *possibleNewRoot = (N *) ((N&)node).prev();
	while (currentNode)
	{
		N *nextNode = (N *) currentNode->next();
		removeNode(*(T *)currentNode);
		if (currentNode == _root)
			_root = possibleNewRoot;
		currentNode = nextNode;
	}
	// RTPOSTCONDITION(!has(node));
	// RTPOSTCONDITION( isEmpty() || (key(node) >= key(*(T *)last())) );
}


template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::removeAllEqualTo(const K &k)
{
	T *currentNode = findFirst(k);
	while (currentNode && (key(*currentNode) == k))
	{
		T *nextNode = (T *) ((N*)currentNode)->next();
		removeNode(*currentNode);
		if (currentNode == _root)
			_root = nextNode;
		currentNode = nextNode;
	}
	// RTPOSTCONDITION(listAllEqualTo(k)->empty());
}


template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::removeAllBefore(const K &k)
{
	N *currentNode = (N *) findBefore(k);
	while (currentNode)
	{
		N *prevNode = (N*)currentNode->prev();
		removeNode(*(T*)currentNode);
		if (currentNode == _root)
			_root = prevNode;
		currentNode = prevNode;
	}
	// RTPOSTCONDITION(k < key(*(T*)first()));
}

template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::removeAllAfter(const K &k)
{
	N *currentNode = findAfter(k);
	while (currentNode)
	{
		N *nextNode = (N*)currentNode->next();
		removeNode(*(T*)currentNode);
		if (currentNode == _root)
			_root = nextNode;
		currentNode = nextNode;
	}
	// RTPOSTCONDITION(k > key(*(T*)first()));
}

template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::removeAll()
{
	if (isEmpty()) return;
	N *currentNode = _root;
	currentNode->pruneTree();
	_root = 0;
	_first = 0;
	_last = 0;
	_count = 0;
	// RTPOSTCONDITION(isEmpty());
}

template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::removeAllAndDestroy()
{
	if (isEmpty()) return;
	N *currentNode = _root;
	currentNode->pruneTreeAndDestroy();
	_root = 0;
	_first = 0;
	_last = 0;
	_count = 0;
	// RTPOSTCONDITION(isEmpty());
}


template<class T, class K, class N>
RTRLinkedList<T> *RTRDBinaryTree<T,K,N>::asList() const
{
	RTRLinkedList<T> *list = new RTRLinkedList<T>();
	N *currentNode = first();
	while (currentNode)
	{
		list->extend((T *)currentNode);
		currentNode = (N *) currentNode->next();
	}
	return list;
}

template<class T, class K, class N>
RTRLinkedList<T> *RTRDBinaryTree<T,K,N>::listAllEqualTo(const K &k) const
{
	RTRLinkedList<T> *list = new RTRLinkedList<T>();
	T *currentNode = findFirst(k);
	while (currentNode && (key(*currentNode) == k))
	{
		list->extend(currentNode);
		currentNode = (T *) ((N*)currentNode)->next();
	}
	return list;
}

template<class T, class K, class N>
RTRLinkedList<T> *RTRDBinaryTree<T,K,N>::listAllLessThan(const K &k) const
{
	RTRLinkedList<T> *list = new RTRLinkedList<T>();
	N *currentNode = first();
	while (currentNode && (key(*(T *)currentNode) < k))
	{
		list->extend((T *) currentNode);
		currentNode = (N *)currentNode->next();
	}
	return list;
}

template<class T, class K, class N>
RTRLinkedList<T> *RTRDBinaryTree<T,K,N>::listAllGreaterThan(const K &k) const
{
	RTRLinkedList<T> *list = new RTRLinkedList<T>();
	N *currentNode = findAfter(k);
	while (currentNode)
	{
		list->extend((T *)currentNode);
		currentNode = (N *)currentNode->next();
	}
	return list;
}

template<class T, class K, class N>
RTRLinkedList<T> *RTRDBinaryTree<T,K,N>::listAllBetween(
	const K &firstKey, const K &lastKey) const
{
	RTRLinkedList<T> *list = new RTRLinkedList<T>();
	N *currentNode = findAfter(firstKey);
	while (currentNode && (key(*(T *)currentNode) < lastKey))
	{
		list->extend((T *)currentNode);
		currentNode = (N *)currentNode->next();
	}
	return list;
}

template<class T, class K, class N>
T *RTRDBinaryTree<T,K,N>::findFirst(const K &k) const
{
	N *currentNode = findOne(k);
	if (!currentNode)
		return (T *)currentNode;
	while ( currentNode->prev() && (key(*(T *)currentNode->prev()) == k) )
		currentNode = (N *)currentNode->prev();
	return (T *)currentNode;
}

template<class T, class K, class N>
T *RTRDBinaryTree<T,K,N>::findLast(const K &k) const
{
	N *currentNode = findOne(k);
	if (!currentNode)
		return (T *)currentNode;
	while ( currentNode->next() && (key(*(T *)currentNode->next()) == k) )
		currentNode = (N *) currentNode->next();
	return (T *)currentNode;
}

template<class T, class K, class N>
T *RTRDBinaryTree<T,K,N>::findBefore(const K &k) const
{
	N *currentNode = _root;
	while (1)
	{
		if (!currentNode || 
			((key(*(T *)currentNode) < k) && 
			 (!currentNode->next() || (key(*(T *)currentNode->next()) >= k))))
				return (T *)currentNode;
		else if (key(*(T*)currentNode) < k)
			currentNode = (N *) currentNode->rightChild();
		else
			currentNode = (N *) currentNode->leftChild();
	}
}

template<class T, class K, class N>
T *RTRDBinaryTree<T,K,N>::findAfter(const K &k) const
{
	N *currentNode = _root;
	while (1)
	{
		if (!currentNode || ((key(*(T *)currentNode) > k) && 
			(!currentNode->prev() || (key(*(T *)currentNode->prev()) <= k))))
				return (T *)currentNode;
		else if (key(*(T *)currentNode) > k)
			currentNode = (N *) currentNode->rightChild();
		else
			currentNode = (N *) currentNode->leftChild();
	}
}
template<class T, class K, class N>
T *RTRDBinaryTree<T,K,N>::findLastNotAfter(const K &k) const
{
	N *currentNode = _root;
	while (1)
	{
		if ( !currentNode || 
			 ( (key(*(T *)currentNode) <= k) && 
			   (!currentNode->next() || (key(*(T *)currentNode->next()) > k))))
	 		return (T *)currentNode;
		else if (key(*(T*)currentNode) == k)
		{
			while ( currentNode->next() && 
					(key(*(T *)currentNode->next()) == k) )
				currentNode = (N *) currentNode->next();
			return (T *)currentNode;
		}
		else if (key(*(T*)currentNode) < k)
			currentNode = (N *) currentNode->rightChild();
		else
			currentNode = (N *) currentNode->leftChild();
	}
}

template<class T, class K, class N>
T *RTRDBinaryTree<T,K,N>::findFirstNotBefore(const K &k) const
{
	N *currentNode = _root;
	while (1)
	{
		if ( !currentNode || 
			 ( (key(*(T *)currentNode) >= k) && 
			   (!currentNode->prev() || (key(*(T *)currentNode->prev()) < k))))
	 		return (T *)currentNode;
		else if (key(*(T*)currentNode) == k)
		{
			while ( currentNode->prev() && 
					(key(*(T *)currentNode->prev()) == k) )
				currentNode = (N *) currentNode->prev();
			return (T *)currentNode;
		}
		else if (key(*(T*)currentNode) < k)
			currentNode = (N *) currentNode->rightChild();
		else
			currentNode = (N *) currentNode->leftChild();
	}
}



template<class T, class K, class N>
const K &RTRDBinaryTree<T,K,N>::key(const T &node) const
{
	return _key(node);
}



template<class T, class K, class N>
N *RTRDBinaryTree<T,K,N>::findInsertionNode(const K &k) const
{
	// RTPRECONDITION(!isEmpty());

	N *currentNode;
	N *comparisonNode = _root;
	if (_first && (k < key(*(T *)_first)))
		return _first;
	if (_last && (k > key(*(T *)_last)))
		return _last;
	while (comparisonNode)
	{
		currentNode = comparisonNode;
		if (k < key(*(T *)comparisonNode))
			comparisonNode = (N *) comparisonNode->leftChild();
		else
			comparisonNode = (N *) comparisonNode->rightChild();
	}
	return currentNode;
}


template<class T, class K, class N>
N *RTRDBinaryTree<T,K,N>::findOne(const K &k) const
{
	N *currentNode = _root;
	while (currentNode && !(key(*(T*)currentNode) == k))
	{
		if (k < key(*(T *)currentNode))
			currentNode = (N *) currentNode->leftChild();
		else
			currentNode = (N *) currentNode->rightChild();
	}
	return currentNode;
}

template<class T, class K, class N>
void RTRDBinaryTree<T,K,N>::printTree(const char *header) const
{
/*
	if (header)
		cout << header << endl;
	if (isEmpty())
	{
		cout << "Empty tree" << endl;
		return;
	}
	T *current = (T*)last();
	while (current)
	{
		for (int i = current->depth(); i > 0; i--)
			cout << "   ";
		cout << *current << endl;
		current = (T*)current->prev();
	}
	cout << endl;
*/
}

#endif // _rtr_dbintree_C_

