//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.06.21"
// Version: 1.0

#ifndef _rtr_shmpmoh_h
#define _rtr_shmpmoh_h

#include "rtr/dlinkl.h"
#include "rtr/prxyh.h"
#include "rtr/moimpl.h"

class RTRProxyManagedObjectServer;
class RTRShmProxyManagedObjectDirectory;
class RTRShmProxyManagedObject;

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

class RTRShmProxyManagedObjectHandle :
	public RTRProxyManagedObjectHandle,
	public RTRDLink1
{ 
public:
// Constructor
	RTRShmProxyManagedObjectHandle(
			RTRShmProxyManagedObjectDirectory& dir,
			const RTRObjectId& classId,
			const RTRObjectId& instanceId,
			const RTRString& name,
			MOAddr *impl
			);
		// A root handle.
		// _TAG Constructor

	RTRShmProxyManagedObjectHandle(
			RTRShmProxyManagedObjectHandle& parent,
			const RTRObjectId& classId,
			const RTRObjectId& instanceId,
			const RTRString& name,
			MOAddr *impl
			);
		// A child handle.
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObjectHandle();
		// _TAG Destructor

	inline RTRShmProxyManagedObjectDirectory& directory() const;

	inline RTRMOImpl *impl() const;

	inline RTRShmProxyManagedObjectHandle *parent() const;

// Operations
	RTRShmProxyManagedObject *object(const RTRProxyManagedObjectServer&);

protected:
	void update();
	void removeObject();
	void checkForRemovedHandles();
	void checkForAddedHandles();
	void updateHandles();
	RTRBOOL hasChildHandle(const RTRString&) const;

// Data
	RTRShmProxyManagedObjectDirectory& _directory;
	RTRShmProxyManagedObjectHandle *_parent;
	RTRMOImpl *_impl;
	RTRDLinkList<RTRShmProxyManagedObjectHandle, RTRDLink1> _childHandles;
	RTRShmProxyManagedObject *_mo;
	unsigned short _totalChildrenAdded;
	unsigned short _totalChildrenRemoved;

// Friends
	friend class RTRShmProxyManagedObjectDirectory;
	friend class RTRShmProxyManagedObject;

private:
// Don't implement
	RTRShmProxyManagedObjectHandle(const RTRShmProxyManagedObjectHandle&);
	RTRShmProxyManagedObjectHandle& operator=(const RTRShmProxyManagedObjectHandle&);
}; 

inline
RTRShmProxyManagedObjectDirectory& RTRShmProxyManagedObjectHandle::directory() const
{
	return _directory;
}

inline
RTRMOImpl *RTRShmProxyManagedObjectHandle::impl() const
{
	return _impl;
}

inline
RTRShmProxyManagedObjectHandle *RTRShmProxyManagedObjectHandle::parent() const
{
	return _parent;
}

#endif /* _rtr_shmpmosh_h */
