//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "Oct. 11 1997"
// Version: 1.0

#ifndef _rtr_clndict_h
#define _rtr_clndict_h

#include "rtr/moddict.h"
#include "rtr/moddimpl.h"

class RTRMOMemoryHeader;
class RTRMemCloneMgr;
class RTRCloneDescriptionDict;

//
// Synopsis:
// #include "rtr/clndict.h"
//
// Description:
// 
// See Also:
//
// Inherits:
//

class RTRCloneMasterDescDict
	: public RTRMasterDictionary
{
public:
	RTRCloneMasterDescDict(
						RTRMemCloneMgr&, 
						RTRMOMemoryHeader&,
						const char* prefix = ""
						);
		// ** Prefix is for debugging (avoids duplicate instance id when 
		// working in one process with the server)
		// _TAG Constructor
	~RTRCloneMasterDescDict();

	inline RTRMemCloneMgr& cloneManager() const;

	void update();

	RTRBOOL hasCloneDict(RTRCloneDescriptionDict& dict) const;
		//  Is the dict still a valid clone of the memory
protected:
	RTRObjectId _prefix;
	RTRMOMemoryHeader& _memHdr;
	RTRMemCloneMgr& _clnMgr;
};

inline RTRMemCloneMgr& RTRCloneMasterDescDict::cloneManager() const
{
	return _clnMgr;
}

//
// Synopsis:
// #include "rtr/clndict.h"
//
// Description:
// 
// See Also:
//
// Inherits:
//

class RTRCloneDescriptionDict
	: public RTRMODescrDictionary
{ 
public:
// Constructor
	RTRCloneDescriptionDict(
		RTRCloneMasterDescDict& master,
		MODDAddr & store,
		rtrUIntPtr base,
		const RTRObjectId& id);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneDescriptionDict();
		// _TAG Destructor

// Attributes
	inline RTRCloneMasterDescDict& cloneMasterDictionary() const;
		// _TAG02 Attributes

	inline RTRMemCloneMgr& cloneManager() const;
		// _TAG02 Attributes
		
	inline RTRDescDictImpl* storeImpl() const;
		// _TAG02 Attributes

// Operations
	void update();
		// _TAG07 Operations

	inline void incrementVarDescCount() ;
		// _TAG07 Operations

protected:
// Utilities

// Data
	RTRCloneMasterDescDict& _context;
	RTRDescDictImpl* _dictMemImpl;

	unsigned long _totalCloneVarDescs;
		// For optimizations in update(), statistics and sanity checking

// Friends

private:
// Don't implement
	RTRCloneDescriptionDict(const RTRCloneDescriptionDict&);
	RTRCloneDescriptionDict& operator=(const RTRCloneDescriptionDict&);
}; 


inline RTRCloneMasterDescDict& RTRCloneDescriptionDict::cloneMasterDictionary() const
{
	return _context;
}

inline RTRMemCloneMgr& RTRCloneDescriptionDict::cloneManager() const
{
	return _context.cloneManager();
}

inline RTRDescDictImpl* RTRCloneDescriptionDict::storeImpl() const
{
	return _dictMemImpl;
}

inline void RTRCloneDescriptionDict::incrementVarDescCount() 
{
	_totalCloneVarDescs++;	
}

#endif
