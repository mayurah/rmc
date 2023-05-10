//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Sep. 27 1995"
// Version: 1.0

#ifndef _execpath_h
#define _execpath_h

#include "rtr/rtstring.h"

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRExecutablePathName
{ 
public:
// Constructor
	RTRExecutablePathName(const RTRString& dir, const RTRString& nm);
		// _TAG Constructor

	RTRExecutablePathName(const char *argv0);
        // _TAG Constructor

	RTRExecutablePathName(const RTRExecutablePathName&);
        // _TAG Constructor

// Attributes
	inline const RTRString& path() const;
		// _TAG01 Attributes

	inline const RTRString& directory() const;
        // _TAG01 Attributes

	inline const RTRString& name() const;
        // _TAG01 Attributes

// Assignment
	RTRExecutablePathName& operator=(const RTRExecutablePathName&);
		// _TAG02 Assignment

protected:
	RTRString _path;
	RTRString _directory;
	RTRString _name;
}; 

inline
const RTRString& RTRExecutablePathName::path() const
{
	return _path;
}

inline
const RTRString& RTRExecutablePathName::directory() const
{
	return _directory;
}

inline
const RTRString& RTRExecutablePathName::name() const
{
	return _name;
}

#endif
