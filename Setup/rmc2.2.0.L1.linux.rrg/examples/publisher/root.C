//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#include "root.h"

RootObject::RootObject(
		const RTRApplicationId& appId,
		const char *nm,
		const char *version
		)
	: RTRManagedProcess(
			appId, nm,
			"Publisher",
			"Example program",
			version,
			RTRManagedObject::Normal
			)
{
	/* create child objects */
	_userList = new UserList(*this, "userList");
	_sys = new SysInfo(*this, "systemInfo");
	_envVar = new EnvVariable(*this, "envVar");
}

RootObject::~RootObject()
{
	delete _sys;
	delete _userList;
	delete _envVar;
}

