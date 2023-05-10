//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 03 1995"
// Version: 1.0

#ifndef _shmmvar_h
#define _shmmvar_h

#ifndef _RDEV_NO_STL_

#else
	#include <stdio.h>
#endif

#include <string.h>

#include "rtr/mempmo.h"
#include "rtr/rtstring.h"
#include "rtr/linkl.h"
#include "rtr/shmlinkl.h"

class RTRShmMObject;

// Synopsis:
// #include"rtr/shmmvar.h"
//
// Description:
// See Also:
//	RTRShmMNumeric, RTRShmMNumericRange, RTRShmMNumericConfig, 
//	RTRShmMString, RTRShmMStringConfig, RTRMOMemPoolHeader, 
//	RTRParameterSetRequest, RTRParameterSetResult, RTRShmMOFake,
//	RTRShmMObject
//
// Inherits:
//	RTRShmDLink0, RTRDLink0
//

class RTRShmMVariable :
	public RTRShmDLink0,
	public RTRDLink0
{ 
public:
// Attributes
	inline char type() const;
		// _TAG01 Attributes

	inline const char *name() const;
		// _TAG01 Attributes

	inline RTRShmMObject *context(const char *) const;
		// _TAG01 Attributes

// State
	inline RTRBOOL nameTruncated() const;
		// _TAG02 State

protected:
// Data
	long _pad;
	char _type;
	char _name[RTR_MAX_MV_NAME + 2];
				// >= 2 null char at end means valid name
				// 1 null char means name truncated
	int _contextOffset;
}; 


inline char RTRShmMVariable::type() const
{
	return _type;
}

inline const char *RTRShmMVariable::name() const
{
	return _name;
}

inline RTRShmMObject *RTRShmMVariable::context(const char *basePtr) const
{
	return (RTRShmMObject *)(basePtr + _contextOffset);
}

inline RTRBOOL RTRShmMVariable::nameTruncated() const
{
	return (_name[RTR_MAX_MV_NAME] != '\0' ) ? RTRTRUE : RTRFALSE;
}


class RTRShmMNumeric :
	public RTRShmMVariable,
	public RTRMemPoolNumeric
{ 
public:
	inline long value() const;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMNumeric&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline long RTRShmMNumeric::value() const
{
	return _value;
}


class RTRShmMNumericRange :
	public RTRShmMVariable,
	public RTRMemPoolNumRange
{ 
public:
	inline long value() const;
	inline long maxValue() const;
	inline long minValue() const;
protected:
// Data
	long _min;
	long _max;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMNumericRange&);
#else
public:
	void print(FILE* os);
#endif
};

inline long RTRShmMNumericRange::value() const
{
	return _value;
}

inline long RTRShmMNumericRange::maxValue() const
{
	return _max;
}

inline long RTRShmMNumericRange::minValue() const
{
	return _min;
}

struct ShmMNumericConfig {
	long _pad;
	char _type;
	char _name[RTR_MAX_MV_NAME + 2];
	int _contextOffset;
	long _value;
	long _pad1;
	long _min;
	long _max;
	long _storeValue;
	long _factoryDefault;
	char _storeState;
};

class RTRShmMNumericConfig :
	public RTRShmMVariable,
	public RTRMemPoolNumConfig
{ 
public:
	//virtual void setStore(long);
	//inline virtual void setStoreState(int);
	inline long maxValue() const;
	inline long minValue() const;
	inline long activeValue() const;
	inline long storeValue() const;
	inline long factoryDefault() const;
	inline int getStoreState() const;
protected:
	long _min;
	long _max;
	long _storeValue;
	long _factoryDefault;
	char _storeState;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMNumericConfig&);
#else
public:
	void print(FILE* os);
#endif
};

inline long RTRShmMNumericConfig::activeValue() const
{
	return ((struct ShmMNumericConfig *)&_pad)->_value;
	//return _value;
}

inline long RTRShmMNumericConfig::storeValue() const
{
	return ((struct ShmMNumericConfig *)&_pad)->_storeValue;
	//return _storeValue;
}

inline long RTRShmMNumericConfig::factoryDefault() const
{
	return ((struct ShmMNumericConfig *)&_pad)->_factoryDefault;
	//return _factoryDefault;
}

inline long RTRShmMNumericConfig::maxValue() const
{
	return ((struct ShmMNumericConfig *)&_pad)->_max;
	//return _max;
}

inline long RTRShmMNumericConfig::minValue() const
{
	return ((struct ShmMNumericConfig *)&_pad)->_min;
	//return _min;
}

inline int RTRShmMNumericConfig::getStoreState() const
{
	return ((struct ShmMNumericConfig *)&_pad)->_storeState;
	//return _storeState;
}

/*
*inline void RTRShmMNumericConfig::setStoreState(int state)
*{
*	_storeState = state;
*}
*/


class RTRShmMString :
	public RTRShmMVariable,
	public RTRMemPoolString
{ 
public:
	inline const char *value() const;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMString&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline const char *RTRShmMString::value() const
{
	return _value;
}

struct ShmMStringConfig {
	long _pad;
	char _type;
	char _name[RTR_MAX_MV_NAME + 2];
	int _contextOffset;
	char _value[RTR_MAX_MSC_VALUE + 1];
	long _pad1;
	long _pad2;
	char _storeValue[RTR_MAX_MSC_VALUE + 1];
	char _factoryDefault[RTR_MAX_MSC_VALUE + 1];
	char _storeState;
};

class RTRShmMStringConfig :
	public RTRShmMVariable,
	public RTRMemPoolStringConfig
{ 
public:
	inline const char *activeValue() const;
	inline const char *storeValue() const;
	inline const char *factoryDefault() const;
	//virtual void setStore(const char *);
	//inline virtual void setStoreState(int);
	inline int getStoreState() const;
protected:
	long _pad1;
	char _storeValue[RTR_MAX_MSC_VALUE + 1];
	char _factoryDefault[RTR_MAX_MSC_VALUE + 1];
	char _storeState;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMStringConfig&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline const char *RTRShmMStringConfig::activeValue() const
{
	return ((struct ShmMStringConfig *)&_pad)->_value;
	//return _value;
}

inline const char *RTRShmMStringConfig::storeValue() const
{
	return ((struct ShmMStringConfig *)&_pad)->_storeValue;
	//return _storeValue;
}

inline const char *RTRShmMStringConfig::factoryDefault() const
{
	return ((struct ShmMStringConfig *)&_pad)->_factoryDefault;
	//return _factoryDefault;
}

inline int RTRShmMStringConfig::getStoreState() const
{
	return ((struct ShmMStringConfig *)&_pad)->_storeState;
	//return _storeState;
}

/*
*inline void RTRShmMStringConfig::setStoreState(int state)
*{
*	_storeState = state;
*}
*/

///////////////////////////////////////////////////////////////////////////
//
// RTRShmMVariable_EliF21 -- Backward compatible with eli2.0.F21
//
///////////////////////////////////////////////////////////////////////////
class RTRShmMObject_EliF21;

class RTRShmMVariable_EliF21 :
	public RTRShmDLink0,
	public RTRDLink0
{ 
public:
	inline char type() const;
	inline const char *name() const;
	inline RTRShmMObject_EliF21 *context(const char *) const;
	inline RTRBOOL nameTruncated() const;
protected:
	char _type;
	char _name[RTR_MAX_MV_NAME_EliF21 + 2];
				// >= 2 null char at end means valid name
				// 1 null char means name truncated
	int _contextOffset;
}; 


inline 
char RTRShmMVariable_EliF21::type() const
{
	return _type;
}

inline 
const char *RTRShmMVariable_EliF21::name() const
{
	return _name;
}

inline 
RTRShmMObject_EliF21 *RTRShmMVariable_EliF21::context(const char *basePtr) const
{
	return (RTRShmMObject_EliF21 *)(basePtr + _contextOffset);
}

inline 
RTRBOOL RTRShmMVariable_EliF21::nameTruncated() const
{
	return (_name[RTR_MAX_MV_NAME_EliF21] != '\0' ) ? RTRTRUE : RTRFALSE;
}

//
// RTRShmMNumeric_EliF21
//

class RTRShmMNumeric_EliF21 :
	public RTRShmMVariable_EliF21,
	public RTRMemPoolNumeric
{ 
public:
	inline int value() const;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMNumeric_EliF21&);
#else
public:
	void print(FILE* os);
#endif
}; 


inline 
int RTRShmMNumeric_EliF21::value() const
{
	return _value;
}

//
// RTRShmMNumericRange_EliF21
//

class RTRShmMNumericRange_EliF21 :
	public RTRShmMVariable_EliF21,
	public RTRMemPoolNumRange
{ 
public:
	inline int value() const;
	inline int maxValue() const;
	inline int minValue() const;
protected:
	int _min;
	int _max;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMNumericRange_EliF21&);
#else
public:
	void print(FILE* os);
#endif
};

inline 
int RTRShmMNumericRange_EliF21::value() const
{
	return _value;
}

inline 
int RTRShmMNumericRange_EliF21::maxValue() const
{
	return _max;
}

inline 
int RTRShmMNumericRange_EliF21::minValue() const
{
	return _min;
}


//
// class RTRShmMNumericConfig_EliF21 
//

class RTRShmMNumericConfig_EliF21 :
	public RTRShmMVariable_EliF21,
	public RTRMemPoolNumConfig_EliF21
{ 
public:
	inline int maxValue() const;
	inline int minValue() const;
	inline int activeValue() const;
	inline int storeValue() const;
	inline int factoryDefault() const;
protected:
	int _min;
	int _max;
	int _storeValue;
	int _factoryDefault;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMNumericConfig_EliF21&);
#else
public:
	void print(FILE* os);
#endif
};

inline 
int RTRShmMNumericConfig_EliF21::activeValue() const
{
	return _value;
}

inline 
int RTRShmMNumericConfig_EliF21::storeValue() const
{
	return _storeValue;
}

inline 
int RTRShmMNumericConfig_EliF21::factoryDefault() const
{
	return _factoryDefault;
}

inline 
int RTRShmMNumericConfig_EliF21::maxValue() const
{
	return _max;
}

inline 
int RTRShmMNumericConfig_EliF21::minValue() const
{
	return _min;
}

//
// RTRShmMString_EliF21
// 
class RTRShmMString_EliF21 :
	public RTRShmMVariable_EliF21,
	public RTRMemPoolString_EliF21
{ 
public:
	inline const char *value() const;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMString_EliF21&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
const char *RTRShmMString_EliF21::value() const
{
	return _value;
}

//
// RTRShmMStringConfig_EliF21
//

class RTRShmMStringConfig_EliF21 :
	public RTRShmMVariable_EliF21,
	public RTRMemPoolStringConfig_EliF21
{ 
public:
	inline const char *activeValue() const;
	inline const char *storeValue() const;
	inline const char *factoryDefault() const;
protected:
	char _storeValue[RTR_MAX_MS_VALUE_EliF21 + 1];
	char _factoryDefault[RTR_MAX_MS_VALUE_EliF21 + 1];
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMStringConfig_EliF21&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
const char *RTRShmMStringConfig_EliF21::activeValue() const
{
	return _value;
}

inline 
const char *RTRShmMStringConfig_EliF21::storeValue() const
{
	return _storeValue;
}

inline 
const char *RTRShmMStringConfig_EliF21::factoryDefault() const
{
	return _factoryDefault;
}


///////////////////////////////////////////////////////////////////////////
//
// RTRShmMVariable_EliF14 -- Backward compatible with eli2.0.F14
//
///////////////////////////////////////////////////////////////////////////

class RTRShmMObject_EliF14;

class RTRShmMVariable_EliF14 :
	public RTRShmDLink0,
	public RTRDLink0
{ 
public:
	inline char type() const;
	inline const char *name() const;
	inline RTRShmMObject_EliF14 *context(const char *) const;
	inline RTRBOOL nameTruncated() const;
protected:
	char _type;
	char _name[RTR_MAX_MV_NAME_EliF14 + 2];
				// >= 2 null char at end means valid name
				// 1 null char means name truncated
	int _contextOffset;
}; 


inline 
char RTRShmMVariable_EliF14::type() const
{
	return _type;
}

inline 
const char *RTRShmMVariable_EliF14::name() const
{
	return _name;
}

inline 
RTRShmMObject_EliF14 *RTRShmMVariable_EliF14::context(const char *basePtr) const
{
	return (RTRShmMObject_EliF14 *)(basePtr + _contextOffset);
}
inline 
RTRBOOL RTRShmMVariable_EliF14::nameTruncated() const
{
	return (_name[RTR_MAX_MV_NAME] != '\0' ) ? RTRTRUE : RTRFALSE;
}

//
// RTRShmMNumeric
// --------------------

class RTRShmMNumeric_EliF14 :
	public RTRShmMVariable_EliF14,
	public RTRMemPoolNumeric
{ 
public:
	inline int value() const;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMNumeric_EliF14&);
#else
public:
	void print(FILE* os);
#endif
}; 


inline 
int RTRShmMNumeric_EliF14::value() const
{
	return _value;
}

//
// RTRShmMNumericRange_EliF14
// --------------------

class RTRShmMNumericRange_EliF14 :
	public RTRShmMVariable_EliF14,
	public RTRMemPoolNumRange
{ 
public:
	inline int value() const;
	inline int maxValue() const;
	inline int minValue() const;

protected:
	int _min;
	int _max;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMNumericRange_EliF14&);
#else
public:
	void print(FILE* os);
#endif
};


inline 
int RTRShmMNumericRange_EliF14::value() const
{
	return _value;
}

inline 
int RTRShmMNumericRange_EliF14::maxValue() const
{
	return _max;
}

inline 
int RTRShmMNumericRange_EliF14::minValue() const
{
	return _min;
}

//
// RTRShmMString_EliF14
// --------------------

class RTRShmMString_EliF14 :
	public RTRShmMVariable_EliF14,
	public RTRMemPoolString_EliF14
{ 
public:
	inline const char *value() const;
#ifndef _RDEV_NO_STL_	
	friend std::ostream& operator<<(std::ostream&, const RTRShmMString_EliF14&);
#else
public:
	void print(FILE* os);
#endif
}; 

inline 
const char *RTRShmMString_EliF14::value() const
{
	return _value;
}

#endif
