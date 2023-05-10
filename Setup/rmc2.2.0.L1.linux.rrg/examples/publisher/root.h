//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#ifndef _root_h
#define _root_h

#include "rtr/mngdproc.h"

#include "sysinfo.h"
#include "envvar.h"
#include "userList.h"

// Synopsis:
//	root.h
//
// Description:
//	A root object of the program
//
// See Also:
//
// Inherits:
//	RTRManagedProcess

class RootObject :
	public RTRManagedProcess
{
public:
// Constructor
	RootObject(
		const RTRApplicationId& appId,
   		const char *name,
		const char *version
		);

// Destructor
	~RootObject();

protected:

// Data
	EnvVariable *_envVar;
	SysInfo *_sys;
	UserList *_userList;

};

#endif
