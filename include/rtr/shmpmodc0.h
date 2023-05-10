//|---------------------------------------------------------------------------
//|                Copyright (C) 2001 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60523                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "06/26/01"
// Version: 1.0

#ifndef _rtr_shmpmodc0_h
#define _rtr_shmpmodc0_h

class RTRShmProxyManagedObjectDirectory_EliF21;
class RTRShmProxyManagedObjectHandle_EliF21;
class RTRShmProxyManagedObjectDirectory_Mdk10;
class RTRShmProxyManagedObjectHandle_Mdk10;

class RTRShmProxyManagedObjDirClient_EliF21
{
public:
// Destructor
	virtual ~RTRShmProxyManagedObjDirClient_EliF21();
		// _TAG Destructor

// Event processing
	virtual void processProxyManagedObjDirEliF21Error(
			const RTRShmProxyManagedObjectDirectory_EliF21& dir
			) = 0;
		// _TAG08 Event processing

	virtual void processProxyManagedObjDirEliF21HandleAdded(
			const RTRShmProxyManagedObjectDirectory_EliF21& dir,
			const RTRShmProxyManagedObjectHandle_EliF21& pmoh
			) = 0;
		// _TAG08 Event processing

	virtual void processProxyManagedObjDirEliF21HandleRemoved(
			const RTRShmProxyManagedObjectDirectory_EliF21& dir,
			const RTRShmProxyManagedObjectHandle_EliF21& pmoh
			) = 0;
		// _TAG08 Event processing
};

class RTRShmProxyManagedObjDirClient_Mdk10
{
public:
// Destructor
	virtual ~RTRShmProxyManagedObjDirClient_Mdk10();
		// _TAG Destructor

// Event processing
	virtual void processProxyManagedObjDirMdk10Error(
			const RTRShmProxyManagedObjectDirectory_Mdk10& dir
			) = 0;
		// _TAG08 Event processing

	virtual void processProxyManagedObjDirMdk10HandleAdded(
			const RTRShmProxyManagedObjectDirectory_Mdk10& dir,
			const RTRShmProxyManagedObjectHandle_Mdk10& pmoh
			) = 0;
		// _TAG08 Event processing

	virtual void processProxyManagedObjDirMdk10HandleRemoved(
			const RTRShmProxyManagedObjectDirectory_Mdk10& dir,
			const RTRShmProxyManagedObjectHandle_Mdk10& pmoh
			) = 0;
		// _TAG08 Event processing
};

#endif

