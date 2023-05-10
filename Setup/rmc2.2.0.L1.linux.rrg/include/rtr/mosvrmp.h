//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 07 1995"
// Version: 1.0

#ifndef _mosvrmp_h
#define _mosvrmp_h

class RTRObjectId;
class RTRString;
class RTRStringConfig;
class RTRPublicObject;
class RTRMemPoolObject;
class RTRMemPoolString;
class RTRMemPoolStringConfig;
class RTRMemPoolNumeric;
class RTRMemPoolNumRange;
class RTRMemPoolNumConfig;

// Synopsis:
// #include"rtr/mosvrmp.h"
//
// Description:
// 	An abstract base class which hides how storage is allocated for Public
// 	objects and variables.
//
// See Also:
//	RTRMOServerMemPoolClient,
//	RTRMemPoolObject, RTRMemPoolString, RTRMemPoolStringConfig, 
//	RTRMemPoolNumeric, RTRMemPoolNumRange, RTRMemPoolNumConfig
//

#include "rtr/lock.h"

class RTRMOServerMemPool : public RTRLockableObj
{
public:
// Allocate operations
	virtual RTRMemPoolObject *newMemPoolObject(
			const RTRObjectId&, 
			const RTRString&, 
			const RTRObjectId&) = 0;
		// _TAG01 Allocate operations

	virtual RTRMemPoolObject *newMemPoolObject(
			const RTRPublicObject&, 
			const RTRString&, 
			const RTRObjectId&) = 0;
        	// _TAG01 Allocate operations

	virtual RTRMemPoolString *newMemPoolString(
			const RTRPublicObject&, 
			const RTRString&,
			char) = 0;
        	// _TAG01 Allocate operations

	virtual RTRMemPoolStringConfig *newMemPoolStringConfig(
			const RTRPublicObject&, 
			const RTRString&,
			const char *,
			char) = 0;
        	// _TAG01 Allocate operations

	virtual RTRMemPoolNumeric *newMemPoolNumeric(
			const RTRPublicObject&, 
			const RTRString&,
			char) = 0;
        	// _TAG01 Allocate operations

	virtual RTRMemPoolNumRange *newMemPoolNumRange(
			const RTRPublicObject&, 
			const RTRString&,
			long,
			long,
			char) = 0;
        	// _TAG01 Allocate operations

	virtual RTRMemPoolNumConfig *newMemPoolNumConfig(
			const RTRPublicObject&, 
			const RTRString&,
			long,
			long,
			long,
			char) = 0;
        	// _TAG01 Allocate operations

// Release operations
	virtual void deleteMemPoolObject(RTRMemPoolObject *obj) = 0;
		// REQUIRE : obj != NULL
		// _TAG02 Release operations

	virtual void deleteMemPoolString(RTRMemPoolString *v) = 0;
		// REQUIRE : v != NULL
        	// _TAG02 Release operations

	virtual void deleteMemPoolStringConfig(RTRMemPoolStringConfig *v) = 0;
		// REQUIRE : v != NULL
        	// _TAG02 Release operations

	virtual void deleteMemPoolNumeric(RTRMemPoolNumeric *v) = 0;
		// REQUIRE : v != NULL
        	// _TAG02 Release operations

	virtual void deleteMemPoolNumRange(RTRMemPoolNumRange *v) = 0;
		// REQUIRE : v != NULL
        	// _TAG02 Release operations

	virtual void deleteMemPoolNumConfig(RTRMemPoolNumConfig *v) = 0;
		// REQUIRE : v != NULL
        	// _TAG02 Release operations

};

// Synopsis:
// #include"rtr/mosvrmp.h"
//
// Description:
// 	An implementation of RTRMOServerMemPool which provides no implementation.
//
// See Also:
//  RTRMOServerMemPoolClient,
//	RTRMemPoolObject, RTRMemPoolString, RTRMemPoolStringConfig,
//  RTRMemPoolNumeric, RTRMemPoolNumRange, RTRMemPoolNumConfig
//
// Inherits:
//	RTRMOServerMemPool
//

class RTRDefaultMOServerMemPool :
	public RTRMOServerMemPool 
{
public:
// Allocate objects
	RTRMemPoolObject *newMemPoolObject(
			const RTRObjectId&, 
			const RTRString&, 
			const RTRObjectId&); 
        	// _TAG01 Allocate objects

	RTRMemPoolObject *newMemPoolObject(
			const RTRPublicObject&, 
			const RTRString&, 
			const RTRObjectId&);
        	// _TAG01 Allocate objects

	RTRMemPoolString *newMemPoolString(
			const RTRPublicObject&, 
			const RTRString&,
			char);
        	// _TAG01 Allocate objects

	RTRMemPoolStringConfig *newMemPoolStringConfig(
			const RTRPublicObject&, 
			const RTRString&,
			const char *,
			char);
        	// _TAG01 Allocate objects

	RTRMemPoolNumeric *newMemPoolNumeric(
			const RTRPublicObject&, 
			const RTRString&,
			char);
        	// _TAG01 Allocate objects

	RTRMemPoolNumRange *newMemPoolNumRange(
			const RTRPublicObject&, 
			const RTRString&,
			long,
			long,
			char);
        	// _TAG01 Allocate objects

	RTRMemPoolNumConfig *newMemPoolNumConfig(
			const RTRPublicObject&, 
			const RTRString&,
			long,
			long,
			long,
			char);
        	// _TAG01 Allocate objects

// Free (but not easy!) objects
	void deleteMemPoolRootObject(RTRMemPoolObject *);
		// _TAG02 Free objects

	void deleteMemPoolObject(RTRMemPoolObject *);
        	// _TAG02 Free objects

	void deleteMemPoolString(RTRMemPoolString *);
        	// _TAG02 Free objects

	void deleteMemPoolStringConfig(RTRMemPoolStringConfig *);
        	// _TAG02 Free objects

	void deleteMemPoolNumeric(RTRMemPoolNumeric *);
        	// _TAG02 Free objects

	void deleteMemPoolNumRange(RTRMemPoolNumRange *);
        	// _TAG02 Free objects

	void deleteMemPoolNumConfig(RTRMemPoolNumConfig *);
        	// _TAG02 Free objects

};

#endif
