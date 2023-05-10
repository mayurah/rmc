//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#include "rtr/pmo.h"

// Synopsis:
//	sysinfo.h
//
// Description:
//	A class containing a function to get the current working directory.
//
// See Also:
//
// Inherits:
//	RTRPublicObject

class SysInfo: public RTRPublicObject
{
public:
		SysInfo(RTRPublicObject& parent, const char* cname);
		~SysInfo();
protected:
		RTRPublicString _cwd;
};
