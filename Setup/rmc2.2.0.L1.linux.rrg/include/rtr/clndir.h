//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "Oct. 11 1997"
// Version: 1.0

#ifndef _rtr_clndir_h
#define _rtr_clndir_h

#include "rtr/rtllist.h"
#include "rtr/objid.h"
#include "rtr/clnobj.h"
#include "rtr/clnvar.h"

#ifndef _RDEV_NO_STL_

#else
	#include <stdio.h>
#endif


class RTRMOMemoryHeader;
class RTRMemCloneMgr;
class RTRMODirImpl;

//
// Synopsis:
// #include "rtr/clndir.h"
//
// Description:
// 
// See Also:
//
// Inherits:
//

class RTRCloneObjectDirectory
{ 
public:
// Constructor
	RTRCloneObjectDirectory(
						RTRMemCloneMgr&, 
						RTRMOMemoryHeader&, 
						const char *prefix = "" 
						);
		// ** Prefix is for debugging and not normally relevant
		// (avoids duplicate instance id.s when working in one process)
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneObjectDirectory();
		// _TAG Destructor

// Identity
	inline const RTRObjectId& instanceId() const;
		// _TAG01 Identity

// Attributes
	inline RTRMemCloneMgr& cloneManager() const;
		// _TAG02 Attributes
		
// State
	inline RTRBOOL isActive() const;
		// _TAG03 State

// Query
	RTRBOOL hasClone(const char *) const;
		// Is this clone dir having a clone root with the given name?
		// _TAG04 Query

// Access
	RTRCloneObject *cloneByName(const char *) const;
		// The clone root object, if any, with the given name.
		// _TAG05 Access

// Operations
	void update();
		// _TAG07 Operations

	void markRootsDead(const char*);
		// _TAG07 Operations

	void addToWatchList(RTRCloneVariable& );
		// _TAG07 Operations

	void dropFromWatchList(RTRCloneVariable& );
		// _TAG07 Operations

	inline void incrementObjCount() ;
		// _TAG07 Operations

	inline void decrementObjCount() ;
		// _TAG07 Operations

	inline void incrementVarCount() ;
		// _TAG07 Operations

	inline void decrementVarCount() ;
		// _TAG07 Operations

protected:
// Utilities

// Data
	RTRObjectId _prefix;
	RTRObjectId _instanceId;
	RTRMOMemoryHeader& _memHeader;
	RTRMemCloneMgr& _clnMgr;
	RTRMODirImpl* _dirMemImpl;
	unsigned long _numberOfAdds;
	unsigned long _numberOfRemoves;
		// For optimizations in update()

	unsigned long _totalCloneObjects;
	unsigned long _totalCloneVariables;
		// For statistics and sanity checking

	RTRLinkedList<RTRCloneObject> _cloneRoots;
	RTRDLinkList<RTRCloneVariable, RTRDLink2> _varWatchList;

// Friends
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream& os, const RTRCloneObjectDirectory&);
#else
public:
	void print(FILE* os);
#endif
private:
// Don't implement
	RTRCloneObjectDirectory(const RTRCloneObjectDirectory&);
	RTRCloneObjectDirectory& operator=(const RTRCloneObjectDirectory&);
}; 

inline const RTRObjectId& RTRCloneObjectDirectory::instanceId() const
{
	return _instanceId;
}

inline RTRMemCloneMgr& RTRCloneObjectDirectory::cloneManager() const
{
	return _clnMgr;
}

inline  RTRBOOL RTRCloneObjectDirectory::isActive() const
{
	return _dirMemImpl? RTRTRUE: RTRFALSE;
}


inline void RTRCloneObjectDirectory::incrementObjCount() 
{
	_totalCloneObjects++;	
}

inline void RTRCloneObjectDirectory::decrementObjCount() 
{
	_totalCloneObjects--;	
}

inline void RTRCloneObjectDirectory::incrementVarCount() 
{
	_totalCloneVariables++;	
}

inline void RTRCloneObjectDirectory::decrementVarCount() 
{
	_totalCloneVariables--;	
}

#endif
