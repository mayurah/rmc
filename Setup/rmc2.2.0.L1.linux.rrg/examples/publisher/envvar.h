//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#include "rtr/pmo.h"

// Synopsis:
//	envvar.h
//
// Description:
//	A class containing a function to get environment variables
//
// See Also:
//
// Inherits:
//	RTRPublicObject

class EnvVariable: public RTRPublicObject
{
public:
		EnvVariable(RTRPublicObject& parent, const char* cname);
		~EnvVariable();
protected:
		RTRPublicString _home;
		RTRPublicString _path;
		RTRPublicString _lib;
		RTRPublicString _classpath;
};
