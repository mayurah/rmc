//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#ifdef _WIN32
#pragma warning( disable : 4355 )
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#endif

#include "sysinfo.h"

char* getCurrentDirectory (void);

SysInfo::SysInfo(RTRPublicObject& parent,const char* cname)
:RTRPublicObject(parent, cname, "System Information", "System",RTRManagedObject::Normal),
_cwd(*this, "Current Directory", "directory", getCurrentDirectory(), RTRFALSE)
{
}

SysInfo::~SysInfo()
{
}

#ifdef _WIN32
char* getCurrentDirectory(void)
{
   char* buffer = new char[100];

   /* Get the current working directory: */
   if( _getcwd( buffer, 100 ) == NULL )
      perror( "_getcwd error" );
   return buffer;
}
#else
char* getCurrentDirectory(void)
{
	char *cwd;
	if ((cwd = getcwd(NULL, 200)) == NULL)
	  return "NULL";
	return cwd;
}
#endif

