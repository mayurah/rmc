//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "Oct. 12 1997"
// Version: 1.0

#ifndef _rtr_clnmgr_h
#define _rtr_clnmgr_h

#include "rtr/objid.h"

class RTRMOServerReply;
class RTRMOCloneRequest;
class RTRCloneObjectDirectory;
class RTRCloneMasterDescDict;

//
// Synopsis:
// #include "rtr/clnmgr.h"
//
// Description:
// 
// See Also:
//
// Inherits:
//

class RTRMemCloneMgr
{ 
public:
// Constructor
	RTRMemCloneMgr(const RTRObjectId& iid)
		:_instanceId(iid), _dictionary(0), _directory(0), _requestMsg(0),
		_replyMsg(0){};
		// _TAG Constructor

// Destructor
	virtual ~RTRMemCloneMgr(){};
		// _TAG Destructor

// Identity
	inline const RTRObjectId& instanceId() const;
		// _TAG01 Identity

// Attributes
	inline const RTRString& text() const;
		// The explanation for error
		// REQUIRE : error()
		// _TAG02 Attributes

// State
	inline RTRBOOL error() const;
		// Is this clone mgr. in an error state?
		// _TAG03 State

// Operations -- used by clone parameters
	virtual RTRBOOL setParameter(
			const RTRObjectId&, // Id of containing object
			const char *,       // name of variable
			const char*,        // value as string
			RTRString* = 0		// return txt, storage provided by caller
			) = 0;
		// _TAG07 Operations -- used by clone parameters

	virtual RTRBOOL setParameter(
			const RTRObjectId&, // Id of containing object
			const char *,       // name of variable
			long,        		// value of numeric var 
			RTRString* = 0		// return txt, storage provided by caller
			) = 0;
		// _TAG07 Operations -- used by clone parameters

protected:
// Utilities

// Data
	RTRObjectId _instanceId;
	RTRBOOL _error;
	RTRString _text;
	RTRCloneObjectDirectory* _directory;
	RTRCloneMasterDescDict* _dictionary;
	RTRMOServerReply* _replyMsg;
	RTRMOCloneRequest* _requestMsg;

// Friends
private:
// Don't implement
	RTRMemCloneMgr(const RTRMemCloneMgr&);
	RTRMemCloneMgr& operator=(const RTRMemCloneMgr&);
}; 

inline const RTRObjectId& RTRMemCloneMgr::instanceId() const
{
	return _instanceId;
}

inline const RTRString& RTRMemCloneMgr::text() const
{
	return _text;
}

inline RTRBOOL RTRMemCloneMgr::error() const
{
	return _error;
}

#endif
