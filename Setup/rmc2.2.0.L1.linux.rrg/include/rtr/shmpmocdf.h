//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.05.19"
// Version: 1.0

#ifndef _rtr_shmpmocdf_h
#define _rtr_shmpmocdf_h

#include "rtr/pmocdf.h"

class RTRShmProxyManagedObjectServerPool;

// Synopsis:
// #include "rtr/shmpmocdf.h"
//
// Description:
// A utility class used to obtain instances of 
// RTRProxyManagedObjectClassDirectory.
// 
// See Also:
// RTRProxyManagedObjectClassDirectory
//
// Inherits:
// RTRProxyManagedObjectClassDirFactory
//

class RTRShmProxyManagedObjectClassDirFactory :
	public RTRProxyManagedObjectClassDirFactory
{ 
public:
// Constructor
	RTRShmProxyManagedObjectClassDirFactory(
			RTRShmProxyManagedObjectServerPool&
			);
		// _TAG Constructor	

// Destructor
	virtual ~RTRShmProxyManagedObjectClassDirFactory();
		// _TAG Destructor	

// Operations -- from RTRProxyManagedObjectDirFactory
	RTRProxyManagedObjectClassDirectoryPtr newClassDirectory(
			const RTRObjectId& classFilter
			) const;
		// _TAG07 Operations -- from RTRProxyManagedObjectDirFactory

protected:

private:
// Don't implement
	RTRShmProxyManagedObjectClassDirFactory(const RTRShmProxyManagedObjectClassDirFactory&);
	RTRShmProxyManagedObjectClassDirFactory& operator=(const RTRShmProxyManagedObjectClassDirFactory&);
}; 

#endif /* _rtr_shmpmocdf_h */
