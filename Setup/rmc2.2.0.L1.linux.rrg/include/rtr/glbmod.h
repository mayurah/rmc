//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 25 1995"
// Version: 1.0

#ifndef _glbmod_h
#define _glbmod_h

#include "rtr/dir.h"
#include "rtr/mod.h"

// Synopsis:
// #include"rtr/glbmod.h"
//
// Description:
//	RTRGlobalManagedObjectDirectory is a utility class which provides access
//	to a global instance of an RTRManagedObjectDirectory. Classes needing
//	access to the managed object directory may inherit from this class or
//	use the public member function directory().
//
// See Also:
//	RTRManagedObjectDirectory, RTRManagedObject

class RTRGlobalManagedObjectDirectory
{
public:
// Access
	static RTRManagedObjectDirectory& directory();
		// _TAG01 Access

protected:
// Static Data
	static RTRManagedObjectDirectory _directory;
		// Static Data
};

#endif
