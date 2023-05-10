//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: A. MacGaffey
// Created: 1/24/94
// Version: 1.0
//

#ifndef _rtr_dfltcfg_h 
#define _rtr_dfltcfg_h

#include "rtr/cfgdb.h"

// Synopsis:
// #include"rtr/dfltcfg.h"
//
// Description:
// 	This descendant of a RTRConfigDb "contains" no values. I.e.
// 	has() will always return FALSE and the results of queries will
// 	only be valid if a default is provided.
//
// See Also:
//	RTRConfig, RTRConfigDb, RTRConfigVariable, RTRDebugConfig
//

class RTRDefaultConfigDb : 
	public RTRConfigDb
{
public:

// Constructor
	RTRDefaultConfigDb();
		// ENSURE: !error()
		// _TAG Constructor

// State 
	RTRBOOL error() const;
		// Is the config db in an error state?
		// -- Never true for this class.
		// _TAG01 State

	const char*	errorText() const;
		// Explanation for the error.
		// _TAG01 State

// Query
	RTRBOOL has(
				const RTRObjectId& classId, 
				const RTRObjectId& instanceId, 
				const RTRString& varName) const;
		// Does db contain a variable corresponding to the class identifier
		// and instance identifier with the given variable name?
		// REQUIRE: !error()
		// ENSURE: Result == RTRFalse
		// _TAG02 Query

// Access 
	RTRConfigVariable variable(
				const RTRObjectId& classId, 
				const RTRObjectId& instanceId,
				const RTRString& varName, 
				const RTRString& dflt,
				RTRBOOL hidden=RTRFALSE ) const;
		// The variable corresponding to the given class identifier and
		// instance identifier with the given variable name. If no value
		// is found, default will be used.
		// REQUIRE: !error()
		// ENSURE: !Result.error()
		// _TAG03 Access

	RTRConfigVariable variable(
				const RTRObjectId& classId, 
				const RTRObjectId& instanceId, 
				const RTRString& varName,
				RTRBOOL hidden=RTRFALSE ) const;
		// The variable corresponding to the given class identifier and
		// instance identifier with the given variable name. If no
		// value is found for these id's, the returned config var
		// will has error() set.
		// REQUIRE: !error()
		// ENSURE: has(classId, instanceId, varName) == !Result.error()
		// i.e. Result.error() always True becase has is always False.
		// _TAG03 Access

// Client management
	virtual void addClient(RTRConfigDbClient& newClient);

	virtual void dropClient(RTRConfigDbClient& oldClient);

	virtual RTRBOOL hasClient() const;

};

#endif  
