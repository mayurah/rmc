//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: Randy N. Lagman
// Created: "February 05, 1998"
// Version: 1.0
//

#ifndef _rwlock_h
#define _rwlock_h

#include "rtr/synch.h"
#include "rtr/dlinkl.h"
#include "rtr/thread.h"
#include "rtr/condvar.h"
#include <limits.h>

// Synopsis:
// #include "rtr/rwlock.h"
//
// Description:
// An RTRRWNode represents a reader/writer that is waiting for access to
// an RTRReaderWriterLock.
//
// See Also:
// RTRReaderWriterLock
//
// Inherits:
// RTRDLink0
//

class RTRRWNode :
	public RTRDLink0
{
public:
#ifndef _RDEV_NO_STL_
	friend ostream& operator << (ostream&, const RTRRWNode&);
#endif
	enum RTRRWNodeType { Reader = 0, Writer };
		// The type of node this is.

// Constructor
	RTRRWNode(RTRThreadId thread, RTRRWNodeType type);	
		// _TAG Constructor

// Destructor
	~RTRRWNode();
		// _TAG Destructor

// Attributes
	inline const int acquiredLocks() const;
		// Returns the number of acquired locks for this RWNode.
		// _TAG01 Attributes

	inline const RTRRWNodeType type() const;
		// Returns the type of the node.
		// _TAG01 Attributes

	inline const RTRThreadId thread() const;
		// Returns a reference to the thread associated with this node.
		// _TAG01 Attributes

// Operations
	inline void incrementAcquiredLocks();
		// Increments the number of acquired locks for this RWNode.
		// _TAG02 Operations

	inline void decrementAcquiredLocks();
		// Decrements the number of acquired locks for this RWNode.
		// _TAG02 Operations

protected:
// Data
	RTRThreadId _thread;
	RTRRWNodeType _type;
	int _acquiredLocks;
};

// Synopsis:
// #include "rtr/rwlock.h"
//
// Description:
// An instance of RTRReaderWriterLock allows simultaneous read access by
// multiple threads or exclusive write access to a single thread.
//
// In general it is more expensive to use compared to RTRMutex.  This 
// construct will perform better than an RTRMutex only when reading occurs
// much more frequently than writing in a multi-threaded program.
//
// Prevention of starvation and fairness for writers is implemented through the
// use of a FIFO queueing scheme.
//
// This class is NOT a wrapper of system coalls on rwlock_t in Solaris because
// the rw_unlock() there unlocks as a reader or writer implicitly based on
// the type of lock the calling thread holds, while this class implies that
// user code should operate on the lock appropriately.  For example, if a
// thread calls waitToRead() to acquire a read lock, it should call 
// doneReading() to release it.
//
// See Also:
// RTRRWNode
//

class RTRReaderWriterLock
{
public:
// Constructor
	RTRReaderWriterLock();
		// _TAG Constructor
			
// Destructor
	~RTRReaderWriterLock();
		// _TAG Destructor

// Attributes
	inline int numReaders();
		// _TAG01 Attributes

// Operations
	void waitToRead();
		// A blocking call that attempts to obtain a read lock.
		// _TAG02 Operations

	void waitToWrite();
		// A blocking call that attempts to obtain the write lock.
		// _TAG02 Operations

	void doneReading();
		// Releases the read lock counter by one.
		// _TAG02 Operations

	void doneWriting();
		// Releases the write lock.
		// _TAG02 Operations

	int tryToRead();
		// A non-blocking call that attempts to obtain a read lock.
		// Returns RTRLockSuccess if a lock is acquired.
		// _TAG02 Operations

	int tryToWrite();
		// A non-blocking call that attempts to get the write lock.
		// Returns RTRLockSuccess if the lock is acquired.
		// _TAG02 Operations

protected:
// Utility
	int firstWriter();
		// Returns index of the first writer thread in the queue.

	int getIndex(RTRThreadId thread);
		// Returns the index of the given thread in the queue.

#ifdef RTDEBUG
	void printWaiters();
		// Prints the list of nodes waiting to acquire the lock.
#endif

// Data
	RTRDLinkedList<RTRRWNode, RTRDLink0> _waiters;
	RTRConditionVariable* _allowAccess;
	int _numReaders;
		// The current number of readers that have obtained a lock.
};

#ifndef _RDEV_NO_STL_
ostream& operator << (ostream& os, const RTRRWNode& node)
{
	os << "Acquired Locks: " << node.acquiredLocks() << " ";
	os << "Node type: ";
	if (node.type() == RTRRWNode::Reader)
	{
		os << "Reader ";
	}
	else
	{
		os << "Writer ";
	}
	os << "Thread id: " << node.thread() << endl;
	return os;
}
#endif

RTRRWNode::RTRRWNode(RTRThreadId thread, RTRRWNodeType type) :
	_thread(thread), _type(type), _acquiredLocks(0)
{
}

RTRRWNode::~RTRRWNode()
{
}

inline const int RTRRWNode::acquiredLocks() const
{
	return _acquiredLocks;
}

inline const RTRRWNode::RTRRWNodeType RTRRWNode::type() const
{
	return _type;
}

inline const RTRThreadId RTRRWNode::thread() const
{
	return _thread;
}

inline void RTRRWNode::incrementAcquiredLocks()
{
	_acquiredLocks++;
}

inline void RTRRWNode::decrementAcquiredLocks()
{
	_acquiredLocks--;
}

RTRReaderWriterLock::RTRReaderWriterLock() :
	_numReaders(0)	
{
	_allowAccess = new RTRConditionVariable(RTRTRUE);
}

RTRReaderWriterLock::~RTRReaderWriterLock()
{
	delete _allowAccess;
}

inline int RTRReaderWriterLock::numReaders()
{
	return _numReaders;
}

void RTRReaderWriterLock::waitToRead()
{
	_allowAccess->lock();
	RTRRWNode* node;
	RTRThreadId currThread = RTRThread::currentThreadId();
	int index = getIndex(currThread);
	if (index == -1)
	{
		node = new RTRRWNode(currThread, RTRRWNode::Reader);
		_waiters.putLast(node);
	}
	else
	{
		int i = 0;
		for (_waiters.start(); i < index; _waiters.forth(), i++) { }
		node = _waiters.item();
	}
	while (getIndex(currThread) > firstWriter())
	{
		_allowAccess->wait();
	}
	_numReaders++;
	node->incrementAcquiredLocks();
	_allowAccess->unlock();
}

void RTRReaderWriterLock::waitToWrite()
{
	_allowAccess->lock();
	RTRRWNode* node;
	RTRThreadId currThread = RTRThread::currentThreadId();
	int index = getIndex(currThread);
	if (index == -1)
	{
		node = new RTRRWNode(currThread, RTRRWNode::Writer);
		_waiters.putLast(node);
	}
	else
	{
		int i = 0;
		for (_waiters.start(); i < index; _waiters.forth(), i++) { }
		node = _waiters.item();
	}
	RTPOSTCONDITION(node->type() == RTRRWNode::Writer);
	while (getIndex(currThread) != 0)
	{
		_allowAccess->wait();
	}
	node->incrementAcquiredLocks();
	_allowAccess->unlock();
}

void RTRReaderWriterLock::doneReading()
{
	_allowAccess->lock();
	RTRRWNode* node;
	RTRThreadId currThread = RTRThread::currentThreadId();
	int index = getIndex(currThread);
	RTPOSTCONDITION(firstWriter() > index);
	int i = 0;
	for (_waiters.start(); i < index; _waiters.forth(), i++) { }
	node = _waiters.item();
	node->decrementAcquiredLocks();
	if (node->acquiredLocks() == 0)
	{
		_waiters.remove(node);
	}
	_numReaders--;
	if (_numReaders == 0)
	{
		_allowAccess->broadcast();
	}
	_allowAccess->unlock();
}

void RTRReaderWriterLock::doneWriting()
{
	_allowAccess->lock();
	RTRRWNode* node;
	RTRThreadId currThread = RTRThread::currentThreadId();
	int index = getIndex(currThread);
	RTPOSTCONDITION(firstWriter() >= index);
	int i = 0;
	for (_waiters.start(); i < index; _waiters.forth(), i++) { }
	node = _waiters.item();
	node->decrementAcquiredLocks();
	if (node->acquiredLocks() == 0)
	{
		_waiters.remove(node);
	}
	_allowAccess->broadcast();
	_allowAccess->unlock();
}

int RTRReaderWriterLock::tryToRead()
{
	// Only return RTRLockSuccess if there lock is obtained and the index of
	// the node is less than the index of the first writer.
	if (_allowAccess->tryLock() == RTRLockSuccess)
	{
		RTRRWNode* node;
		RTRThreadId currThread = RTRThread::currentThreadId();
		int index = getIndex(currThread);
		if (index == -1)
		{
			if (firstWriter() < INT_MAX)
			{
				_allowAccess->unlock();
				return RTRLockFailure;
			}
			else
			{
				node = new RTRRWNode(currThread, RTRRWNode::Reader);
				_waiters.putLast(node);
			}
		}
		index = getIndex(currThread);
		if (getIndex(currThread) < firstWriter())
		{
			int i = 0;
			for (_waiters.start(); i < index; _waiters.forth(), i++) { }
			node = _waiters.item();
			_numReaders++;
			node->incrementAcquiredLocks();
			_allowAccess->unlock();
			return RTRLockSuccess;
		}
		else
		{
			_allowAccess->unlock();
			return RTRLockFailure;
		}
	}
	else
	{
		return RTRLockFailure;
	}
}

int RTRReaderWriterLock::tryToWrite()
{
	if (_allowAccess->tryLock() == RTRLockSuccess)
	{
		RTRRWNode* node;
		RTRThreadId currThread = RTRThread::currentThreadId();
		int index = getIndex(currThread);
		if ((index == -1 && _waiters.count() == 0) || index == 0)
		{
			if (index == -1)
			{
				node = new RTRRWNode(currThread, RTRRWNode::Writer);
				_waiters.putLast(node);
			}
			int i = 0;
			_waiters.start();
			node = _waiters.item();
			RTPOSTCONDITION(node->type() == RTRRWNode::Writer);
			node->incrementAcquiredLocks();
			_allowAccess->unlock();
			return RTRLockSuccess;
		}
		else
		{
			_allowAccess->unlock();
			return RTRLockFailure;
		}
	}
	else	
	{
		return RTRLockFailure;
	}
}

int RTRReaderWriterLock::firstWriter()
{
	int i = 0;
	for (_waiters.start(); !_waiters.off(); _waiters.forth(), i++)
	{
		RTRRWNode* node = _waiters.item();
		if (node->type() == RTRRWNode::Writer)
		{
			return i;
		}
	}
	return INT_MAX;
}

int RTRReaderWriterLock::getIndex(RTRThreadId thread)
{
	int i = 0;
	for (_waiters.start(); !_waiters.off(); _waiters.forth(), i++)
	{
		RTRRWNode* node = _waiters.item();
		if (node->thread() == thread)
		{
			return i;
		}
	}
	return -1;
}

#ifdef RTDEBUG
void RTRReaderWriterLock::printWaiters()
{
	cout << endl;
	for (_waiters.start(); !_waiters.off(); _waiters.forth())
	{
		RTRRWNode* node = _waiters.item();
		cout << *node;
	}
	cout << endl;
}
#endif

#endif // _rwlock_h
