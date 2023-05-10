//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|
//|       1400 Kensington Road, Oak Brook IL  60521       
//|
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: A. MacGaffey, T. Hansen
// Created: 12/16/93
// Version: 1.0
//

#ifndef _rtr_cfgvar_h 
#define _rtr_cfgvar_h

#include "rtr/rtrdefs.h"
#include "rtr/objid.h"
#include "rtr/rtextval.h"

// Synopsis:
// #include"rtr/cfgvar.h"
// "//"RTRConfigVariable& var;
// RTRString value = var;
// int i = var.toInteger();
// float f = var.toFloat();
// RTRBOOL b = var.toBoolean();
//
// Description:
//	Class RTRConfigVariable offers clients a convenient way to
// 	access configuration parameter values. If a value is not available
// 	for the parameter, the config variable will be in an error state.
//
// 	A config variable is typcally obtained from a configuration database.
//
// 	error() returns TRUE if a value is available for the config variable.
// 	value() returns the value of the config variable as an RTRExternalValue.
//
// Inherits:
//  RTRExternalValue -> RTRString
//
// See Also:
//    RTRObjectId, RTRConfigDb, RTRXFileDb, RTRExternalValue
//

class RTRConfigVariable : public RTRExternalValue
{
public:
// Constructor
	RTRConfigVariable(
				const RTRObjectId& classId, 
				const RTRObjectId& instanceId, 
				const RTRString& nm);
		// Create a config variable that is in error.
		// _TAG Constructor

	RTRConfigVariable(
				const RTRObjectId& classId, 
				const RTRObjectId& instanceId, 
				const RTRString& nm, 
				const RTRString& val,
				const RTRString& dflt);
		// Create a config variable using the given string.
		// _TAG Constructor

	RTRConfigVariable(
				const RTRObjectId& classId, 
				const RTRObjectId& instanceId, 
				const RTRString& nm, 
				const char* val, 
				int length,
				const RTRString& dflt);
		// Create a config variable using the given buffer and length.
		// _TAG Constructor

	RTRConfigVariable(const RTRConfigVariable& var);
		// Create a config variable identical to the given 
		// config variable.
		// _TAG Constructor

// Destructor
	virtual ~RTRConfigVariable();
		// _TAG Destructor

// Assignment
	RTRConfigVariable& operator=(const RTRConfigVariable& other);
		// Initialize this variable as a copy of other
		// _TAG03 Assignment

// Attributes
	inline const RTRObjectId& classId() const;
		// _TAG01 Attributes

	inline const RTRObjectId& instanceId() const;
		// _TAG01 Attributes

	inline const RTRString& name() const;
		// _TAG01 Attributes

	inline const RTRString& defaultValue() const;
		// _TAG01 Attributes

	inline RTRBOOL isDefaultValue() const;
		// Was this variable assigned a default value?
		// _TAG01 Attributes

// State
	inline RTRBOOL error() const ;
		// Does the config variable exist? Note that a TRUE response
		// from this function indicates non-existence, it does *not*
		// indicate an empty/null value.
		// _TAG02 State

// Compatiblity 
	RTRConfigVariable();
		// Create a config variable that is in error.
		// For compatibility.
		// _TAG Constructor

	RTRExternalValue value();
		// The value of this configuration variable. This may be
		// an empty value.
		// REQUIRE: !error()
		// _TAG04 Compatibility

protected:
	
	RTRObjectId _classId;
	RTRObjectId _instanceId;
	RTRString _name;
	RTRString _default;
	RTRBOOL	_error;
};

inline const RTRObjectId& RTRConfigVariable::classId() const
{
	return _classId;
}

inline const RTRObjectId& RTRConfigVariable::instanceId() const
{
	return _instanceId;
}

inline const RTRString& RTRConfigVariable::name() const
{
	return _name;
}

inline const RTRString& RTRConfigVariable::defaultValue() const
{
	return _default;
}

inline RTRBOOL RTRConfigVariable::isDefaultValue() const
{
	return !_error && (_default == *this);
}

inline RTRBOOL RTRConfigVariable::error() const
{
	return _error;
}

#endif 
