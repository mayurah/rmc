//|---------------------------------------------------------------------------
//|                        Copyright (c) 1999 Reuters                       --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.05.13"
// Version: 1.0

#ifndef _rtr_shmpmosd_h
#define _rtr_shmpmosd_h

#include "rtr/pmosc.h"
#include "rtr/pmocd.h"
#include "rtr/shmpmodc.h"	// RTRShmProxyManagedObjDirClient
#include "rtr/shmpmodc0.h"	// RTRShmProxyManagedObjDirClient_EliF21
#include "rtr/timercmd.h"	// RTRTimerCmd
#include "rtr/dlinkl.h"		// RTRDLink0

class RTRShmProxyManagedObjectClassDirectory;
class RTRShmProxyManagedObjectServer;

// Synopsis:
// #include "rtr/shmpmosd.h"
//
// Description:
// A utility class used to monitor a "sub-directory" of an associated
// class directory.
//
// See Also:
// RTRShmProxyManagedObjectClassDirectory
//
// Inherits:
// RTRProxyManagedObjectServerClient, RTRSharedMemoryClient, RTRTimerCmd,
// RTRDLink0
//

class RTRShmProxyMOSDirectory :
	public RTRShmProxyManagedObjDirClient,
	public RTRShmProxyManagedObjDirClient_EliF21,
	public RTRShmProxyManagedObjDirClient_Mdk10,
	public RTRTimerCmd,
	public RTRDLink0
{ 
public:
// Constructor
	RTRShmProxyMOSDirectory(
			RTRShmProxyManagedObjectClassDirectory&,
			RTRShmProxyManagedObjectServer&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRShmProxyMOSDirectory();
		// _TAG Destructor

// Attributes
	inline const RTRProxyManagedObjectServer& server() const;
		// The server monitored by this sub-directory.
		// _TAG02 Attributes

protected:
// Access
	RTRShmProxyManagedObjectClassDirectory& classDirectory() const;
	const RTRObjectId& classFilter() const;

// Query
	RTRBOOL hasRootHandleByName(const RTRString&) const;

// Operations
	void enable();
	void disable();

// Event Processing -- from RTRShmProxyManagedObjDirClient
	virtual void processProxyManagedObjDirError(
		const RTRShmProxyManagedObjectDirectory& dir );
	virtual void processProxyManagedObjDirHandleAdded(
		const RTRShmProxyManagedObjectDirectory& dir,
		const RTRShmProxyManagedObjectHandle& pmoh );
	virtual void processProxyManagedObjDirHandleRemoved(
		const RTRShmProxyManagedObjectDirectory& dir,
		const RTRShmProxyManagedObjectHandle& pmoh );

// Event Processing -- from RTRShmProxyManagedObjDirClient_EliF21
	virtual void processProxyManagedObjDirEliF21Error(
		const RTRShmProxyManagedObjectDirectory_EliF21& dir );
	virtual void processProxyManagedObjDirEliF21HandleAdded(
		const RTRShmProxyManagedObjectDirectory_EliF21& dir,
		const RTRShmProxyManagedObjectHandle_EliF21& pmoh );
	virtual void processProxyManagedObjDirEliF21HandleRemoved(
		const RTRShmProxyManagedObjectDirectory_EliF21& dir,
		const RTRShmProxyManagedObjectHandle_EliF21& pmoh );

// Event Processing -- from RTRShmProxyManagedObjDirClient_Mdk10
	virtual void processProxyManagedObjDirMdk10Error(
		const RTRShmProxyManagedObjectDirectory_Mdk10& dir );
	virtual void processProxyManagedObjDirMdk10HandleAdded(
		const RTRShmProxyManagedObjectDirectory_Mdk10& dir,
		const RTRShmProxyManagedObjectHandle_Mdk10& pmoh );
	virtual void processProxyManagedObjDirMdk10HandleRemoved(
		const RTRShmProxyManagedObjectDirectory_Mdk10& dir,
		const RTRShmProxyManagedObjectHandle_Mdk10& pmoh );

// Event Processing -- from RTRTimerCmd
	virtual void processTimerEvent();

// Data
	RTRBOOL _enabled;
	RTRProxyManagedObjectClassDirectoryPtr _classDirectory;
	RTRShmProxyManagedObjectServer& _server;
	RTRShmProxyManagedObjectDirectory *_directory;
	RTRShmProxyManagedObjectDirectory_EliF21 *_directoryEli;
	RTRShmProxyManagedObjectDirectory_Mdk10 *_directoryMdk;

private:
// Don't implement
	RTRShmProxyMOSDirectory(const RTRShmProxyMOSDirectory&);
	RTRShmProxyMOSDirectory& operator=(const RTRShmProxyMOSDirectory&);
}; 

inline const 
RTRProxyManagedObjectServer& RTRShmProxyMOSDirectory::server() const
{
	return (RTRProxyManagedObjectServer&)_server;
}

#endif /* _rtr_shmpmosd_h */

