//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.05.17"
// Version: 1.0

#ifndef _rtr_shmpmocd_h
#define _rtr_shmpmocd_h

#include "rtr/pmocd.h"
#include "rtr/shmpmosd.h"

class RTRShmProxyManagedObjectServerPool;

// Synopsis:
// #include "rtr/shmpmocd.h"
//
// Description:
// A shared memory based implementation of a 
// RTRProxyManagedObjectClassDirectory.
//
// See Also:
// RTRProxyManagedObjectClassDirectoryClient
//
// Inherits:
// RTRProxyManagedObjectClassDirectory
//

class RTRShmProxyManagedObjectClassDirectory :
	public RTRProxyManagedObjectClassDirectory
{ 
public:
// Constructor
	RTRShmProxyManagedObjectClassDirectory(
			RTRShmProxyManagedObjectServerPool& pool,
			const RTRObjectId& filter
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyManagedObjectClassDirectory();
		// _TAG Destructor

	void processHandleAdded(
			RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle& pmoh);

	void processHandleRemoved(
			RTRProxyManagedObjectServer&,
			const RTRProxyManagedObjectHandle& pmoh);

protected:
// Operations -- from RTRProxyManagedObjectClassDirectory
	void serverAdded(RTRProxyManagedObjectServer&);

// Data
	RTRDLinkList<RTRShmProxyMOSDirectory, RTRDLink0> _subDirectories;

// Friends
	friend class RTRShmProxyMOSDirectory;

private:
// Don't implement
	RTRShmProxyManagedObjectClassDirectory(const RTRShmProxyManagedObjectClassDirectory&);
	RTRShmProxyManagedObjectClassDirectory& operator=(const RTRShmProxyManagedObjectClassDirectory&);
}; 

#endif /* _rtr_shmpmocd_h */
