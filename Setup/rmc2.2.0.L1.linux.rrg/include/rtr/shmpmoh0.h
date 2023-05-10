//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.06.21"
// Version: 1.0

#ifndef _rtr_shmpmoh0_h
#define _rtr_shmpmoh0_h

#include "rtr/dlinkl.h"
#include "rtr/prxyh.h"
#include "rtr/shmmo.h"

class RTRProxyManagedObjectServer;
class RTRShmProxyManagedObjectDirectory_EliF21;
class RTRShmProxyManagedObject_EliF21;
class RTRShmProxyManagedObjectDirectory_Mdk10;
class RTRShmProxyManagedObject_Mdk10;

// Synopsis:
// #include "rtr/shmpmo.h"
//
// Description:
// RTRShmProxyMOSHandle is a utility which adds a second DLink to a
// RTRProxyManagedObjectHandle so that it can be in a list maintained by
// an instance of RTRShmProxyMOSDirectory or RTRShmProxyMOSHandle as 
// well as a list maintained by an instance of
// RTRProxyManagedObjectClassDirectory.
// 
// See Also:
// RTRShmProxyMOSDirectory, RTRProxyManagedObjectClassDirectory
//
// Inherits:
// RTRShmProxyManagedObjectHandle, RTRDLink1
//

class RTRShmProxyManagedObjectHandle_EliF21 :
	public RTRProxyManagedObjectHandle,
	public RTRDLink1
{ 
public:
// Constructor
	RTRShmProxyManagedObjectHandle_EliF21(
			RTRShmProxyManagedObjectDirectory_EliF21& dir,
			const RTRObjectId& classId,
			const RTRObjectId& instanceId,
			const RTRString& name,
			RTRShmMObject_EliF21 *impl
			);
		// A root handle.
		// _TAG Constructor

	RTRShmProxyManagedObjectHandle_EliF21(
			RTRShmProxyManagedObjectHandle_EliF21& parent,
			const RTRObjectId& classId,
			const RTRObjectId& instanceId,
			const RTRString& name,
			RTRShmMObject_EliF21 *impl
			);
		// A child handle.
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObjectHandle_EliF21();
		// _TAG Destructor

	inline RTRShmMObject_EliF21 *impl() const;

	inline RTRShmProxyManagedObjectHandle_EliF21 *parent() const;

	inline RTRShmProxyManagedObjectDirectory_EliF21& directory() const;

	RTRShmProxyManagedObject_EliF21 *object(const RTRProxyManagedObjectServer&);

protected:
	void update();
	void removeObject();
	void checkForRemovedHandles(const char *base);
	void checkForAddedHandles(const char *base);
	void updateChildHandles();
	RTRBOOL hasChildHandle(const RTRString&) const;

// Data
	RTRShmProxyManagedObjectDirectory_EliF21& _directory;
	RTRShmProxyManagedObjectHandle_EliF21 *_parent;
	RTRShmMObject_EliF21 *_impl;
	RTRDLinkList<RTRShmProxyManagedObjectHandle_EliF21, RTRDLink1> _childHandles;
	RTRShmProxyManagedObject_EliF21 *_mo;
	int _transactionLevel;

// Friends
	friend class RTRShmProxyManagedObjectDirectory_EliF21;
	friend class RTRShmProxyManagedObject_EliF21;

private:
// Don't implement
	RTRShmProxyManagedObjectHandle_EliF21(const RTRShmProxyManagedObjectHandle_EliF21&);
	RTRShmProxyManagedObjectHandle_EliF21& operator=(const RTRShmProxyManagedObjectHandle_EliF21&);
}; 

inline
RTRShmProxyManagedObjectDirectory_EliF21& RTRShmProxyManagedObjectHandle_EliF21::directory() const
{
	return _directory;
}

inline
RTRShmMObject_EliF21 *RTRShmProxyManagedObjectHandle_EliF21::impl() const
{
	return _impl;
}

inline
RTRShmProxyManagedObjectHandle_EliF21 *RTRShmProxyManagedObjectHandle_EliF21::parent() const
{
	return _parent;
}

class RTRShmProxyManagedObjectHandle_Mdk10 :
	public RTRProxyManagedObjectHandle,
	public RTRDLink1
{ 
public:
// Constructor
	RTRShmProxyManagedObjectHandle_Mdk10(
			RTRShmProxyManagedObjectDirectory_Mdk10& dir,
			const RTRObjectId& classId,
			const RTRObjectId& instanceId,
			const RTRString& name,
			RTRShmMObject *impl
			);
		// A root handle.
		// _TAG Constructor

	RTRShmProxyManagedObjectHandle_Mdk10(
			RTRShmProxyManagedObjectHandle_Mdk10& parent,
			const RTRObjectId& classId,
			const RTRObjectId& instanceId,
			const RTRString& name,
			RTRShmMObject *impl
			);
		// A child handle.
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObjectHandle_Mdk10();
		// _TAG Destructor

	inline RTRShmMObject *impl() const;

	inline RTRShmProxyManagedObjectHandle_Mdk10 *parent() const;

	inline RTRShmProxyManagedObjectDirectory_Mdk10& directory() const;

	RTRShmProxyManagedObject_Mdk10 *object(const RTRProxyManagedObjectServer&);

protected:
	void update();
	void removeObject();
	void checkForRemovedHandles(const char *base);
	void checkForAddedHandles(const char *base);
	void updateChildHandles();
	RTRBOOL hasChildHandle(const RTRString&) const;

// Data
	RTRShmProxyManagedObjectDirectory_Mdk10& _directory;
	RTRShmProxyManagedObjectHandle_Mdk10 *_parent;
	RTRShmMObject *_impl;
	RTRDLinkList<RTRShmProxyManagedObjectHandle_Mdk10, RTRDLink1> _childHandles;
	RTRShmProxyManagedObject_Mdk10 *_mo;
	int _transactionLevel;

// Friends
	friend class RTRShmProxyManagedObjectDirectory_Mdk10;
	friend class RTRShmProxyManagedObject_Mdk10;

private:
// Don't implement
	RTRShmProxyManagedObjectHandle_Mdk10(const RTRShmProxyManagedObjectHandle_Mdk10&);
	RTRShmProxyManagedObjectHandle_Mdk10& operator=(const RTRShmProxyManagedObjectHandle_Mdk10&);
}; 

inline
RTRShmProxyManagedObjectDirectory_Mdk10& RTRShmProxyManagedObjectHandle_Mdk10::directory() const
{
	return _directory;
}

inline
RTRShmMObject *RTRShmProxyManagedObjectHandle_Mdk10::impl() const
{
	return _impl;
}

inline
RTRShmProxyManagedObjectHandle_Mdk10 *RTRShmProxyManagedObjectHandle_Mdk10::parent() const
{
	return _parent;
}

#endif /* _rtr_shmpmosh0_h */
