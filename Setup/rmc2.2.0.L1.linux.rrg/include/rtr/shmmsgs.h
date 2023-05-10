//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 22 1995"
// Version: 1.0

#ifndef _shmmsgs_h
#define _shmmsgs_h

#include "rtr/objid.h"

#ifndef _RDEV_NO_STL_

#else
	#include <stdio.h>
#endif

#define MAX_SET_ID_SIZE 500
#define MAX_VAR_NAME_SIZE 88
#define MAX_VAR_VALUE_SIZE 100
#define MAX_ERROR_TEXT_SIZE 100

//
// Definition for latest "old" version in integration node
//
class RTRParameterSetRequest
{
public:
	char objectIdString[MAX_SET_ID_SIZE];
	char varNameString[MAX_VAR_NAME_SIZE];
	char varValueString[MAX_VAR_VALUE_SIZE];
	long _pad; // padding for quad alignment

	void init(const RTRObjectId&, const char *, const char *);

	void init(const RTRObjectId&, const char *, long);

#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&, const RTRParameterSetRequest&);
#else
	void print(FILE* os);
#endif
};

// Description:
// The older version of the message definition. Need this to look at the old
// version of shared memory.
//

#define MAX_SET_ID_SIZE_EliF21 500
#define MAX_VAR_NAME_SIZE_EliF21 85
#define MAX_VAR_VALUE_SIZE_EliF21 100

class RTRParameterSetRequest_EliF21
{
public:
	char objectIdString[MAX_SET_ID_SIZE_EliF21];
	char varNameString[MAX_VAR_NAME_SIZE_EliF21];
	char varValueString[MAX_VAR_VALUE_SIZE_EliF21];

	void init(const RTRObjectId&, const char *, const char *);
	void init(const RTRObjectId&, const char *, long);
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRParameterSetRequest_EliF21&);
#else
	void print(FILE* os);
#endif
};

#define MAX_SET_ID_SIZE_EliF14 100
#define MAX_VAR_NAME_SIZE_EliF14 50
#define MAX_VAR_VALUE_SIZE_EliF14 100

class RTRParameterSetRequest_EliF14
{
public:
	char objectIdString[MAX_SET_ID_SIZE_EliF14];
	char varNameString[MAX_VAR_NAME_SIZE_EliF14];
	char varValueString[MAX_VAR_VALUE_SIZE_EliF14];

	void init(const RTRObjectId&, const char *, const char *);
	void init(const RTRObjectId&, const char *, long);
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRParameterSetRequest_EliF14&);
#else
	void print(FILE* os);
#endif
};

// Synopsis:
// #include"rtr/shmmsgs.h"
//
// Description:
// See Also:
//  RTRParameterSetRequest, RTRMOMemPoolHeader, RTRShmMNumeric, 
//  RTRShmMNumericConfig, RTRShmMNumericRange, RTRShmMOFake, RTRShmMObject,
//  RTRShmMString, RTRShmMStringConfig, RTRShmMVariable
//

class RTRParameterSetResult
{
public:
	char error;
	long _pad; // padding for quad alignment.
	char text[MAX_ERROR_TEXT_SIZE];

	void init();

	void init(const char *);

#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&, const RTRParameterSetResult&);
#else
	void print(FILE* os);
#endif
};

class RTRParameterSetResult_EliF21
{
public:
	char error;
	char text[MAX_ERROR_TEXT_SIZE];
	void init();
	void init(const char *);
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRParameterSetResult_EliF21&);
#else
	void print(FILE* os);
#endif
};

typedef RTRParameterSetResult_EliF21 RTRParameterSetResult_EliF14;

#endif
