//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: J. Arvanites, A. MacGaffey
// Created: "Jun. 8 1995"
// Version: 1.0
//

#ifndef _mngdproc_h
#define _mngdproc_h

#include "rtr/pmo.h"
#include "rtr/vardatti.h"
#include "rtr/rtstring.h"
#include "rtr/appid.h"

// Synopsis:
// #include "rtr/mngdproc.h"
//
// Description:
// RTRManagedProcess is a descendant of RTRPublicObject which:
// provides a minimum set of variables relating to process state.
// 
// See Also:
//
// Inherits:
//  RTRPublicObject
//

class RTRManagedProcess :
	public RTRPublicObject
{
public:
// Constructor
	RTRManagedProcess(
			const RTRObjectId& appId,
	       		const char *execName,
			const char *subClassName,
			const char *description,
			const char *version,
			MOState startState=RTRManagedObject::Normal
			);
       		// _TAG Constructor

	RTRManagedProcess(
			const RTRObjectId& appId,
	       		const char *execName,
			const char *description,
			const char *version,
			MOState startState=RTRManagedObject::Normal
			);
       		// _TAG Constructor

	RTRManagedProcess(
			int argc, 
			char **argv, 
			const char *subClassName,
			const RTRApplicationId& appId,
			const RTRString version
			);
		// For backward-compatibility
		// _TAG Constructor

// Destructor
	virtual ~RTRManagedProcess();
		// _TAG Destructor

protected:
// Data
	RTRVariableDateTime	_start_time;

// Variables
	RTRPublicNumeric	_processId;
	RTRPublicNumeric	_groupId;
	RTRPublicNumeric	_userId;
	RTRPublicString		_startTime;
	RTRPublicString		_pathName;
	RTRPublicString		_versionId;
	RTRPublicString		_instanceId;

// Utility functions used internally.
	int getProcessId();
	int getUserId();
	int getGroupId();

private:
		// Do not define
	RTRManagedProcess(const RTRManagedProcess&);
	RTRManagedProcess& operator=(const RTRManagedProcess&);
};

#endif
