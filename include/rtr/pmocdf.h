//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "7/8/97"
// Version: 1.0

#ifndef _rtr_pmocdf_h
#define _rtr_pmocdf_h

#include "rtr/pmocd.h"

class RTRProxyManagedObjectServerPool;

//
// Synopsis:
// #include "rtr/proxymos.h"
//
// Description:
// Provides a factory for instantiating RTRProxyManagedObjectClassDirectory
// for a given class filter.
// 
// See Also:
// RTRProxyManagedObjectClassDirectory
//
// Inherits:
//

class RTRProxyManagedObjectClassDirFactory
{ 
public:
// Constructor
	RTRProxyManagedObjectClassDirFactory(
			RTRProxyManagedObjectServerPool& pool
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyManagedObjectClassDirFactory();
		// _TAG Destructor

// Operations
	virtual RTRProxyManagedObjectClassDirectoryPtr newClassDirectory(
			const RTRObjectId& classFilter
			) const = 0;
		// _TAG01 Operations

protected:
// Data
	RTRProxyManagedObjectServerPool& _pool;

private:
// Don't implement
	RTRProxyManagedObjectClassDirFactory(
			const RTRProxyManagedObjectClassDirFactory&);
	RTRProxyManagedObjectClassDirFactory& operator=
			(const RTRProxyManagedObjectClassDirFactory&);
}; 

#endif
