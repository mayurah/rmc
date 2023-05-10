//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 03 1995"
// Version: 1.0

#ifndef _mempmo_h
#define _mempmo_h

#include "rtr/mempdefs.h"


// Synopsis:
// #include"rtr/mempmo.h"
//
// Description:
// See Also:
//	RTRMemPoolNumeric, RTRMemPoolNumRange, RTRMemPoolNumConfig, 
//	RTRMemPoolString, RTRMemPoolStringConfig
//

class RTRMemPoolObject
{ 
public:

};

// Synopsis:
// #include"rtr/mempmo.h"
//
// Description:
// See Also:
//  RTRMemPoolObject, RTRMemPoolNumRange, RTRMemPoolNumConfig, 
//  RTRMemPoolString, RTRMemPoolStringConfig
//

class RTRMemPoolNumeric
{ 
public:
// Access
	inline long *store();
		// _TAG01 Access

protected:
// Data
	long _value;
		// Data
}; 

inline 
long *RTRMemPoolNumeric::store()
{
	return &_value;
}

// Synopsis:
// #include"rtr/mempmo.h"
//
// Description:
// See Also:
//  RTRMemPoolObject, RTRMemPoolNumeric, RTRMemPoolNumConfig, 
//  RTRMemPoolString, RTRMemPoolStringConfig
//

class RTRMemPoolNumRange
{ 
public:
// Access
	inline long *store();
		// _TAG01 Access

protected:
// Data
	long _value;
		// Data
};

inline 
long *RTRMemPoolNumRange::store()
{
	return &_value;
}

// Synopsis:
// #include"rtr/mempmo.h"
//
// Description:
// See Also:
//  RTRMemPoolObject, RTRMemPoolNumeric, RTRMemPoolNumRange, 
//  RTRMemPoolString, RTRMemPoolStringConfig
//

class RTRMemPoolNumConfig
{ 
public:
// Access
	inline long *store();
		// _TAG01 Access

	virtual void setStore(long) = 0;
	virtual void setStoreState(int state) = 0;

protected:
// Data
	long _value;
		// Data
};

inline 
long *RTRMemPoolNumConfig::store()
{
	return &_value;
}


// For backward compatible
class RTRMemPoolNumConfig_EliF21
{ 
public:
	inline long *store();
protected:
	long _value;
};

inline long *RTRMemPoolNumConfig_EliF21::store()
{
	return &_value;
}

// Synopsis:
// #include"rtr/mempmo.h"
//
// Description:
// See Also:
//  RTRMemPoolObject, RTRMemPoolNumeric, RTRMemPoolNumRange, 
//  RTRMemPoolNumConfig, RTRMemPoolStringConfig
//

class RTRMemPoolString
{ 
public:
// Transformation
	inline char *store();
		// _TAG01 Transformation

protected:
// Data
	char _value[RTR_MAX_MS_VALUE + 1];
		// Data
}; 

inline 
char *RTRMemPoolString::store()
{
	return (char *)_value;
}


//  For backward compatible 

class RTRMemPoolString_EliF21
{ 
public:
	inline char *store();
protected:
	char _value[RTR_MAX_MS_VALUE_EliF21 + 1];
}; 

inline char *RTRMemPoolString_EliF21::store()
{
	return (char *)_value;
}

typedef RTRMemPoolString_EliF21 RTRMemPoolString_EliF14 ;
	// Since RTR_MAX_MS_VALUE_EliF21 == RTR_MAX_MS_VALUE_EliF14

// Synopsis:
// #include"rtr/mempmo.h"
//
// Description:
// See Also:
//  RTRMemPoolObject, RTRMemPoolNumeric, RTRMemPoolNumRange, 
//  RTRMemPoolNumConfig, RTRMemPoolString
//

class RTRMemPoolStringConfig
{ 
public:
// Transformation
	inline char *store();
		// _TAG01 Transformation

	virtual void setStore(const char *) = 0;
	virtual void setStoreState(int state) = 0;

protected:
// Data
	char _value[RTR_MAX_MSC_VALUE + 1];
		// Data
}; 

inline 
char *RTRMemPoolStringConfig::store()
{
	return (char *)_value;
}

// For backward compatible
class RTRMemPoolStringConfig_EliF21
{ 
public:
	inline char *store();
protected:
	char _value[RTR_MAX_MS_VALUE_EliF21 + 1];
}; 

inline char *RTRMemPoolStringConfig_EliF21::store()
{
	return (char *)_value;
}

#endif
