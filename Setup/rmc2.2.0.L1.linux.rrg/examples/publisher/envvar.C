//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#ifdef _WIN32
#include <windows.h>
#pragma warning( disable : 4355 )
#ifdef _RDEV_NO_STL_
#include <stdlib.h>
#endif
#else
#include <stdlib.h>
#endif

#include "envvar.h"

char* getEnvironment(const char* envname);

EnvVariable::EnvVariable(RTRPublicObject& parent,const char* cname)
:RTRPublicObject(parent, cname, "Environment Variables", "EnvironmentVariable",RTRManagedObject::Normal),
_home(*this, "home", "environment variable", getEnvironment("HOME") , RTRFALSE),
_lib(*this, "lib", "environment variable", getEnvironment("LIB"), RTRFALSE),
_path(*this, "path", "environment variable", getEnvironment("PATH"), RTRFALSE),
_classpath(*this, "classpath", "environment variable", getEnvironment("CLASSPATH"), RTRFALSE)
{
}

EnvVariable::~EnvVariable()
{
}

char* getEnvironment(const char* envname)
{
	char* value;
	/* get environment variable */
	value = getenv(envname);
	
	if (!value)
		return "NULL";
	
	return value;
}
