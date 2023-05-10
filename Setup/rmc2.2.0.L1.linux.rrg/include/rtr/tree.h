//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T.L. Zhang
// Created: "Jan. 11 1996"
// Version: 1.0

#ifndef _tree_h
#define _tree_h

#include "rtr/dlinkl.h"
#include "rtr/objid.h"
#include "rtr/rtstack.h"
#include "rtr/queue.h"


template <class T> class RTRTreeNode;
class RTRTreeKey;

// Synopsis:
//
// Description:
//
// See also:
//

template <class T>
class RTRTree
{
public:
// Constructor
	RTRTree(const T* val, RTRTreeKey* key);
		// _TAG Constructor

// Destructor
	~RTRTree();
		// Delete tree but not entries which are not created by tree
		// _TAG Destructor

// Insert
	RTRTree<T>& put(const T* val, RTRTreeKey* key);
		// Using key to find position , and put entry there
		// _TAG01 Insert

// Remove
	RTRTree<T>& remove(const RTRTreeKey& key);
		// Remove the node found by key, and delete the node (not entry)
		// _TAG02 Remove

	void deleteContents();
		// Delete entry of each node in tree, left a tree skeleton
		// Used only when the T objs need to deleted through tree
        // _TAG02 Remove

// Set
	RTRBOOL setValue(const T* value, const RTRTreeKey& key);
		// _TAG03 Set

// Query
	const T* getValue(const RTRTreeKey& key);
		// _TAG04 Query

	RTRTreeNode<T>*  find(const RTRTreeKey& key);
        // _TAG04 Query

	RTRTreeNode<T>*  findAncestor(const RTRTreeKey& theKey);
		// Find a node whose key is closest to theKey if not theKey
        // _TAG04 Query

// Attributes

	// _TAG05 Attributes	
	RTRTreeNode<T>* root() { return _root; };

	// _TAG05 Attributes
	RTRBOOL isEmpty() const { return _root==0 ;};

protected:
// Data
	RTRTreeNode<T>* _root;

};

//
// RTRTreeNode
//
// -----------
// Synopsis:
//
// Description:
//
// See Also:
//

template <class T>
class RTRTreeNode : public RTRDLink0
{ 
public:
// Constructor
	RTRTreeNode(const T* entry, RTRTreeKey* key);
		// entry could be null to represent an empty node
		// _TAG Constructor

// Destructor
	~RTRTreeNode();
		// _TAG Destructor

// Insert
	RTRTreeNode<T>& addChild(RTRTreeNode<T>* childNode);
		// _TAG01 Insert

	void addDescendant(RTRTreeNode<T>* aNode);
        // _TAG01 Insert

// Remove
	RTRTreeNode<T>& dropChild(RTRTreeNode<T>* childNode);
		// _TAG02 Remove

	void removeDescendants();
        // _TAG02 Remove

// Query
	RTRBOOL hasChild(RTRTreeNode<T>* childNode);
		// _TAG03 Query

// Set
	RTRTreeNode<T>& setParent(RTRTreeNode<T>* parNode);
		// _TAG04 Set

	// _TAG04 Set
	void setEntry(const T* entry) { _nodeEntry = entry;} ;

// Get
	RTRTreeNode<T>* childByKey(const RTRTreeKey& key);
		// _TAG05 Get

	RTRTreeNode<T>* childByExtendedKey(const RTRTreeKey& key);
        // _TAG05 Get

	RTRTreeNode<T>* descandentByKey(const RTRTreeKey& key);
        // _TAG05 Get

	// _TAG05 Get	
	RTRTreeNode<T>* parent() {return _parentNode;};

	// _TAG05 Get
	const RTRDLinkList<RTRTreeNode<T>,RTRDLink0>& children()
								{ return _childrenNodes;};
// Attributes

	// _TAG06 Attributes	
	RTRTreeKey& key() { return *_nodeKey;}

	// _TAG06 Attributes
	const T* entry() { return _nodeEntry;}

	// _TAG06 Attributes
	RTRBOOL isLeaf() const { return _childrenNodes.isEmpty();};

	// _TAG06 Attributes
	RTRBOOL isRoot() const { return (_parentNode==0) ? RTRTRUE: RTRFALSE;};

	// _TAG06 Attributes
	RTRBOOL isEmpty() const { return (_nodeEntry==0) ? RTRTRUE: RTRFALSE;};

// Deletion
	void deleteEntries();
		// _TAG07 Deletion

protected:

// Data storage
	RTRTreeKey * _nodeKey;
	const T* _nodeEntry;
	RTRTreeNode<T>* _parentNode;
	RTRDLinkList<RTRTreeNode<T>,RTRDLink0>  _childrenNodes;
	
}; 



//
// RTRTreeKey used by RTRTree
//
// --------------------------
// Synopsis:
//
// Description:
//
// 	use object id as a prototype impl
//
// 	Base class for TreeKey
//
// See Also:
//

class RTRTreeKey
{
public:
// Constructor

// Destructor
	virtual ~RTRTreeKey() ;
		// _TAG Destructor

//	Attributes
	virtual RTRTreeKey* parentKey()=0;
		// _TAG01 Attributes

	virtual RTRBOOL isEmpty() const =0;
        // _TAG01 Attributes

	virtual const char* to_c() const = 0;
		// Internal storage 
        // _TAG01 Attributes

// Comparisons
	virtual RTRBOOL isDescendant(const RTRTreeKey&) const = 0; 
		// _TAG02 Comparisons

	virtual RTRBOOL operator==(const RTRTreeKey&) const = 0 ; 
        // _TAG02 Comparisons

protected:
};

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRObjectIdTreeKey :
	public RTRTreeKey
{
public:
// Constructor
	RTRObjectIdTreeKey(const RTRObjectId & id);
		// _TAG Constructor

// Destructor
	~RTRObjectIdTreeKey();
		// _TAG Destructor

// Attributes
	const char* to_c() const ;
		// _TAG01 Attributes

	// _TAG01 Attributes
	const RTRObjectId& objId() const { return _oId;};

	RTRTreeKey* parentKey();
		// _TAG01 Attributes

    // _TAG01 Attributes
	RTRBOOL isEmpty() const { return _oId.isEmpty();}

	int levels();
        // _TAG01 Attributes

// Comparisons
	virtual RTRBOOL isDescendant(const RTRTreeKey&) const; 
		// _TAG02 Comparisons

	virtual RTRBOOL operator==(const RTRTreeKey&) const; 
        // _TAG02 Comparisons

protected:
	RTRObjectId _oId;
	RTRObjectIdTreeKey* _parentKey;
	RTRLinkedList<RTRString>* _keyList;

};

//
// RTRTreeDFSIterator : Depth First Search Tree Iterator
//
// ------------------
// Synopsis:
//
// Description:
//
//	Depth First Search Tree Iterator
//
// See Also:
// 

template <class T>
class RTRTreeDFSIterator
{
#ifndef _RDEV_NO_STL_
	friend ostream& operator<<(ostream& os,RTRTreeDFSIterator<T>&);
#endif
public:
// Constructor
	RTRTreeDFSIterator(RTRTree<T>& tree);
		// _TAG Constructor

	RTRTreeDFSIterator();
		// _TAG Constructor

// Destructor
	~RTRTreeDFSIterator();
		// _TAG Destructor

//	Initialization
	void init();
		// _TAG01 Initialization

	void init(RTRTreeNode<T>* root);
        // _TAG01 Initialization

// Read Cursor

	// _TAG02 Read Cursor
	RTRBOOL hasTree() { return _treeRoot!=0; };

	void start();
		// _TAG02 Read Cursor

	void forth();
        // _TAG02 Read Cursor

    // _TAG02 Read Cursor
	RTRBOOL off() { return _currentNode==0;};

	// _TAG02 Read Cursor
	RTRTreeNode<T>* item() { return _currentNode;};

protected:
	RTRTreeNode<T>* _treeRoot;
	RTRTreeNode<T>* _currentNode;
	RTRStack<RTRTreeNode<T> > _stack;
};


//
// RTRTreeBFSIterator : Breadth First Search Tree Iterator
//
// ------------------
// Synopsis:
//
// Description:
//
//	Breadth First Search Tree Iterator
//
// See Also:
//

template <class T>
class RTRTreeBFSIterator
{
#ifndef _RDEV_NO_STL_
	friend ostream& operator<<(ostream& os,RTRTreeBFSIterator<T>&);
#endif
public:
// Constructor
	RTRTreeBFSIterator(RTRTree<T>& tree);
		// _TAG Constructor

	RTRTreeBFSIterator();
        // _TAG Constructor

// Destructor
	~RTRTreeBFSIterator();
		// _TAG Destructor

//	Initialization
	void init();
		// _TAG01 Initialization
	
	void init(RTRTreeNode<T>* root);
        // _TAG01 Initialization

// Read Cursor

	// _TAG02 Read Cursor	
	RTRBOOL hasTree() { return _treeRoot!=0; };

	void start();
		// _TAG02 Read Cursor

	void forth();
        // _TAG02 Read Cursor

    // _TAG02 Read Cursor
	RTRBOOL off() { return _currentNode==0;};

	// _TAG02 Read Cursor
	RTRTreeNode<T>* item() { return _currentNode;};

protected:
	RTRTreeNode<T>* _treeRoot;
	RTRTreeNode<T>* _currentNode;
	RTRQueue<RTRTreeNode<T> > _queue;
};





#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("tree.C")
#else
#include "rtr/tree.C"
#endif
#endif

#endif
