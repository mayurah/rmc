//|---------------------------------------------------------------------------
//|                Copyright (C) 2001 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60523                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "06/26/01"
// Version: 1.0

#ifndef _rtr_shmpmodc_h
#define _rtr_shmpmodc_h

class RTRShmProxyManagedObjectDirectory;
class RTRShmProxyManagedObjectHandle;

class RTRShmProxyManagedObjDirClient
{
public:
// Destructor
	virtual ~RTRShmProxyManagedObjDirClient();
		// _TAG Destructor

// Event processing
	virtual void processProxyManagedObjDirError(
    			const RTRShmProxyManagedObjectDirectory& dir
			) = 0;
		// _TAG08 Event processing

	virtual void processProxyManagedObjDirHandleAdded(
			const RTRShmProxyManagedObjectDirectory& dir,
			const RTRShmProxyManagedObjectHandle& pmoh
			) = 0;
		// _TAG08 Event processing

	virtual void processProxyManagedObjDirHandleRemoved(
			const RTRShmProxyManagedObjectDirectory& dir,
			const RTRShmProxyManagedObjectHandle& pmoh
			) = 0;
		// _TAG08 Event processing
};

#endif

