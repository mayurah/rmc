//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refintiiv,                       --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#ifndef _admin_h
#define _admin_h

#include "rtr/triadmin.h"

class MyHelperAdmin
	: public RTRTriarchProcessAdmin
{
public:
	MyHelperAdmin(
			const RTRObjectId& class_id,
			const RTRObjectId& instance
			)
		: RTRTriarchProcessAdmin(class_id, instance, "admin")
	{
	}

	~MyHelperAdmin() {}
};

#endif
