//
//|---------------------------------------------------------------
//|                Copyright (C) 2000 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60523          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  description:
//	This class provides generic refernce counting for objects.
//	When the reference count finally goes to zero the object will
//	be deleted.
//


#ifndef _rtr_rtrefnct_h
#define _rtr_rtrefnct_h

#include "rtr/rtrdefs.h"
#include "rtr/rtrmutex.h"


class rtrRefCountObj
{
public:
// Constructor
	inline rtrRefCountObj( RTRPlatMutex *mtx = 0 ) :
			_referenceCount(1),
			_referenceMutex(mtx)
		// ENSURE : referenceCount() == 1
	{
	};

// Destructor
	virtual ~rtrRefCountObj();

// Operations
	void addReference();
		// Add a reference to the object.
		// <Synchronized>
		//  _TAG01 Operations

	void dropReference();
		// Drop a reference from the object.
		// <Synchronized>
		// _TAG01 Operations

// Attributes
	int referenceCount() const;
		// The current reference count for the object.
		// <Synchronized>
		// _TAG02 Attributes

protected:

// Operations
	virtual void dispose();
		// Calls delete on this. Overwrite for different
		// disposal of object.
		// _TAG01 Operations

	inline void addRefNoSafe()
		// Add a reference to the object.
		//  _TAG01 Operations
	{
		_referenceCount++;
	};

	inline void dropRefNoSafe()
		// Drop a reference from the object.
		// _TAG01 Operations
	{
		if (--_referenceCount <= 0)
			dispose();
	};

	inline RTRBOOL dropRefNoSafeNoDispose()
	{
		return ((--_referenceCount <= 0) ? RTRTRUE : RTRFALSE);
	};

	inline void refDoLock() const
	{
		if (_referenceMutex) _referenceMutex->lock();
	};

	inline void refDoUnlock() const
	{
		if (_referenceMutex) _referenceMutex->unlock();
	};

// Attributes
	int referenceCountNoSafe() const
		// The current reference count for the object.
		// <Synchronized>
		// _TAG02 Attributes
	{
		return(_referenceCount);
	};

// Attributes
	int				_referenceCount;
	RTRPlatMutex	*_referenceMutex;

};

#endif
