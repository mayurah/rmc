//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 03 1995"
// Version: 1.0

#ifndef _shmmo_h
#define _shmmo_h

#include "rtr/objid.h"
#include "rtr/shmmvar.h"
#include "rtr/shmdll.h"


// Synopsis:
// #include"rtr/shmmo.h"
//
// Description:
// 	We need this dummy ancestor because RTRShmMObject wants to declare
// 	its children as a list of "itself". Compiler doesn't like this
// 	(something about templates....)
// 	Clients of RTRShmMObject which access children() will have to
// 	down-cast the elements in the list to RTRShmMObject. Sorry! :-)
//
// See Also:
//	RTRShmMObject, RTRMOMemPoolHeader, RTRParameterSetRequest, 
//	RTRParameterSetResult, RTRShmMNumeric, RTRShmMNumericConfig, 
//	RTRShmMNumericRange, RTRShmMString, RTRShmMStringConfig, RTRShmMVariable
//
// Inherits:
//	RTRShmDLink0, RTRDLink0
//

class RTRShmMOFake : public RTRShmDLink0, public RTRDLink0 {};


// Synopsis:
// #include"rtr/shmmo.h"
//
// Description:
// See Also:
//  RTRMOMemPoolHeader, RTRParameterSetRequest, 
//  RTRParameterSetResult, RTRShmMNumeric, RTRShmMNumericConfig, 
//  RTRShmMNumericRange, RTRShmMString, RTRShmMStringConfig, RTRShmMVariable
//
// Inherits:
// 	RTRShmMOFake, RTRMemPoolObject 
//

class RTRShmMObject :
	public RTRShmMOFake,
	public RTRMemPoolObject
{ 
public:
// Identity
	inline const char *name() const;
		// _TAG01 Identity

	inline const char *className() const;
		// _TAG01 Identity

// Attributes
	inline int transactionLevel() const;
		// _TAG02 Attributes

	inline int usageCounter() const;
		// The number of times this object has been deleted.
		// Used as sanity to keep client proxy in sync with server.
		// _TAG02 Attributes

	inline RTRShmMObject *parent(const char *) const;
		// _TAG02 Attributes

// State
	inline RTRBOOL namesTruncated() const;
		// Did name() or className() get truncated?
		// _TAG03 State

// Query
	RTRBOOL hasChild(const char *nm, const char *base);
		// _TAG04 Query

	RTRBOOL hasChild(const char *nm, const char *base, RTRShmMObject*);
		// _TAG04 Query

	RTRBOOL hasVariable(const char *nm, const char *base);
		// _TAG04 Query

	RTRBOOL hasVariable(const char *nm, const char *base, RTRShmMVariable*);
		// _TAG04 Query

// Access - sequential 
	inline const RTRShmDLinkList<RTRShmMOFake, RTRShmDLink0>& children() const;
		// _TAG05 Access - sequential

	inline const RTRShmDLinkList<RTRShmMVariable, RTRShmDLink0>& variables() const;
		// _TAG05 Access - sequential

// Access - random
	RTRShmMObject *childByName(const char *, const char *);
		// _TAG06 Access - random

protected:
// Data
	long _pad;
	char _name[RTR_MAX_MO_NAME + 2];
	char _className[RTR_MAX_MO_CLASS_NAME + 2];
	int _parentOffset;
	RTRShmDLinkList<RTRShmMOFake, RTRShmDLink0> _children;
	RTRShmDLinkList<RTRShmMVariable, RTRShmDLink0> _variables;
	int _transactionLevel;
	int _usageCounter;
		// Data
}; 

inline 
int RTRShmMObject::transactionLevel() const
{
	return _transactionLevel;
}

inline 
int RTRShmMObject::usageCounter() const
{
	return _usageCounter;
}

inline 
const char *RTRShmMObject::name() const
{
	return _name;
}

inline 
const char *RTRShmMObject::className() const
{
	return _className;
}

inline 
RTRShmMObject *RTRShmMObject::parent(const char *basePtr) const
{
	return (RTRShmMObject *)
		(_parentOffset >= 0 ? (basePtr + _parentOffset) : 0);
}

inline 
const RTRShmDLinkList<RTRShmMOFake, RTRShmDLink0>& 
RTRShmMObject::children() const
{
	return _children;
}

inline 
const RTRShmDLinkList<RTRShmMVariable, RTRShmDLink0>& 
RTRShmMObject::variables() const
{
	return _variables;
}

inline 
RTRBOOL RTRShmMObject::namesTruncated() const
{
	return (_name[RTR_MAX_MO_NAME] != '\0' || 
				_className[RTR_MAX_MO_CLASS_NAME] != '\0') 
					? RTRTRUE : RTRFALSE;
}


// Synopsis:
// #include"rtr/shmmo.h"
//
// Description:
// Backward compatible with eli2.0.F21
//
// See Also:
//
// Inherits:
// 	RTRShmMOFake, RTRMemPoolObject 
//

class RTRShmMObject_EliF21 :
	public RTRShmMOFake,
	public RTRMemPoolObject
{ 
public:
// Identity
	inline const char *name() const;
		// _TAG01 Identity

	inline const char *className() const;
		// _TAG01 Identity

// Attributes
	inline int transactionLevel() const;
		// _TAG02 Attributes

	inline int usageCounter() const;
		// _TAG02 Attributes

	inline RTRShmMObject_EliF21 *parent(const char *) const;
		// _TAG02 Attributes

// State
	inline RTRBOOL namesTruncated() const;
		// _TAG03 State

// Query
	RTRBOOL hasChild(const char *nm, const char *base);
		// _TAG04 Query

	RTRBOOL hasChild(const char *nm, const char *base, RTRShmMObject_EliF21*);
		// _TAG04 Query

	RTRBOOL hasVariable(const char *nm, const char *base);
		// _TAG04 Query

	RTRBOOL hasVariable(const char *nm, const char *base, RTRShmMVariable_EliF21*);
		// _TAG04 Query

// Access - sequential
	inline const RTRShmDLinkList<RTRShmMOFake, RTRShmDLink0>& children() const;
		// _TAG05 Access - sequential

	inline const RTRShmDLinkList<RTRShmMVariable_EliF21, RTRShmDLink0>& variables() const;
		// _TAG05 Access - sequential

// Access - random
	RTRShmMObject_EliF21 *childByName(const char *, const char *);
		// _TAG06 Access - random

protected:
// Data
	char _name[RTR_MAX_MO_NAME_EliF21 + 2];
	char _className[RTR_MAX_MO_CLASS_NAME_EliF21 + 2];
	int _parentOffset;
	RTRShmDLinkList<RTRShmMOFake, RTRShmDLink0> _children;
	RTRShmDLinkList<RTRShmMVariable_EliF21, RTRShmDLink0> _variables;
	int _transactionLevel;
	int _usageCounter;
		// Data
}; 

inline 
int RTRShmMObject_EliF21::transactionLevel() const
{
	return _transactionLevel;
}

inline 
int RTRShmMObject_EliF21::usageCounter() const
{
	return _usageCounter;
}


inline 
const char *RTRShmMObject_EliF21::name() const
{
	return _name;
}

inline 
const char *RTRShmMObject_EliF21::className() const
{
	return _className;
}

inline 
RTRShmMObject_EliF21 *RTRShmMObject_EliF21::parent(const char *basePtr) const
{
	return (RTRShmMObject_EliF21 *)
		(_parentOffset >= 0 ? (basePtr + _parentOffset) : 0);
}

inline 
const RTRShmDLinkList<RTRShmMOFake, RTRShmDLink0>& 
RTRShmMObject_EliF21::children() const
{
	return _children;
}

inline 
const RTRShmDLinkList<RTRShmMVariable_EliF21, RTRShmDLink0>& 
RTRShmMObject_EliF21::variables() const
{
	return _variables;
}

inline 
RTRBOOL RTRShmMObject_EliF21::namesTruncated() const
{
	return (_name[RTR_MAX_MO_NAME_EliF21] != '\0' || 
				_className[RTR_MAX_MO_CLASS_NAME_EliF21] != '\0') 
					? RTRTRUE : RTRFALSE;
}


// Synopsis:
// #include"rtr/shmmo.h"
//
// Description:
// Backward compatible with eli2.0.F14
//
// See Also:
//
// Inherits:
// 	RTRShmMOFake, RTRMemPoolObject 
//

class RTRShmMObject_EliF14 :
	public RTRShmMOFake,
	public RTRMemPoolObject
{ 
public:
// Identity
	inline const char *name() const;
		// _TAG01 Identity

	inline const char *className() const;
		// _TAG01 Identity

// Attributes
	inline int transactionLevel() const;
		// _TAG02 Attributes

	inline int usageCounter() const;
		// _TAG02 Attributes

	inline RTRShmMObject_EliF14 *parent(const char *) const;
		// _TAG02 Attributes

// State
	inline RTRBOOL namesTruncated() const;
		// _TAG03 State

// Query
	RTRBOOL hasChild(const char *nm, const char *base);
		// _TAG04 Query

	RTRBOOL hasChild(const char *nm, const char *base, RTRShmMObject_EliF14*);
		// _TAG04 Query

	RTRBOOL hasVariable(const char *nm, const char *base);
		// _TAG04 Query

	RTRBOOL hasVariable(const char *nm, const char *base, RTRShmMVariable_EliF14*);
		// _TAG04 Query

// Access - sequential
	inline const RTRShmDLinkList<RTRShmMOFake, RTRShmDLink0>& children() const;
		// _TAG05 Access - sequential

	inline const RTRShmDLinkList<RTRShmMVariable_EliF14, RTRShmDLink0>& variables() const;
		// _TAG05 Access - sequential

// Access - random
	RTRShmMObject_EliF14 *childByName(const char *, const char *);
		// _TAG06 Access - random

protected:
// Data
	char _name[RTR_MAX_MO_NAME_EliF14 + 2];
	char _className[RTR_MAX_MO_CLASS_NAME_EliF14 + 2];
	int _parentOffset;
	RTRShmDLinkList<RTRShmMOFake, RTRShmDLink0> _children;
	RTRShmDLinkList<RTRShmMVariable_EliF14, RTRShmDLink0> _variables;
	int _transactionLevel;
	int _usageCounter;
		// Data
}; 

inline 
int RTRShmMObject_EliF14::transactionLevel() const
{
	return _transactionLevel;
}

inline 
int RTRShmMObject_EliF14::usageCounter() const
{
	return _usageCounter;
}

inline 
const char *RTRShmMObject_EliF14::name() const
{
	return _name;
}

inline 
const char *RTRShmMObject_EliF14::className() const
{
	return _className;
}

inline 
RTRShmMObject_EliF14 *RTRShmMObject_EliF14::parent(const char *basePtr) const
{
	return (RTRShmMObject_EliF14 *)
		(_parentOffset >= 0 ? (basePtr + _parentOffset) : 0);
}

inline 
const RTRShmDLinkList<RTRShmMOFake, RTRShmDLink0>& 
RTRShmMObject_EliF14::children() const
{
	return _children;
}

inline 
const RTRShmDLinkList<RTRShmMVariable_EliF14, RTRShmDLink0>& 
RTRShmMObject_EliF14::variables() const
{
	return _variables;
}

inline 
RTRBOOL RTRShmMObject_EliF14::namesTruncated() const
{
	return (_name[RTR_MAX_MO_NAME_EliF14] != '\0' || 
				_className[RTR_MAX_MO_CLASS_NAME_EliF14] != '\0') 
					? RTRTRUE : RTRFALSE;
}

#endif
