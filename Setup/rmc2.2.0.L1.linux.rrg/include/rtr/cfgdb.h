//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: A. MacGaffey, T. Hansen
// Created: 11/24/93
// Version: 1.0
//

#ifndef _rtr_cfgdb_h 
#define _rtr_cfgdb_h


#include "rtr/rtrdefs.h"
#include "rtr/objid.h"
#include "rtr/cfgvar.h"

	// For compatability with RTRObjId and RTRIdImp
#include "rtr/rtidimp.h"

class RTRConfigDb;

class RTRConfigDbClient
{
public:
	virtual void processConfigDbVariableRetrieved(RTRConfigDb&, RTRConfigVariable&) = 0;
		// The callback function should not maintain 
		// a reference to the given RTRConfigVariable.

	virtual void processConfigDbDeleted(RTRConfigDb&) = 0;
};


// Synopsis:
// #include"rtr/cfgdb.h"
// 
// "//"RTRConfigDb& configDb;
// 
// RTRObjectId classId("Class"); 
// RTRObjectId instanceId("instance"); 
// RTRString name("name"); 
// RTRString default("100");
//   
// if ( !configDb.error() ) 
// {
// 	RTRConfigVariable var = configDb.variable(
//	                                classId, 
//	                                instanceId,
//	                                name,
//	                                default);
//	int v = var.toInteger();
// }
//
// Description:
// 	This class provides an abstract definition of a configuration
// 	database from which configuration variables may be obtained.
//
// 	Clients use has() to determine if a config variable exists in
// 	the database and variable() to obtain a config variable.
//
// 	There are two ways a client can access a config variable. The client
// 	may ask for a config variable and provide no default value. If no
// 	value is found in the database, the config variable will be in an
// 	error state. Alternatively, the client can provide a default value
// 	that will be assigned as the value of the config variable if no
// 	value is found in the database.
//
// 	Descendants of this class implement the features used to obtatin
// 	configuration variables.
//
// 	Application components which use configuration variables have associated
// 	with them both a class identifier and an instance identifier. This allows
// 	system components to be configured (by means of variables) on a class
// 	basis and on a per instance basis. The precendence of class identifiers
// 	relative to instance identifiers is an implementation issue determined by
// 	descendents of this class.
//
// See Also:
//	RTRConfig, RTRConfigVariable, RTRDebugConfig, RTRDefaultConfigDb
//

class RTRConfigDb
{
public:

	// _TAG Constructor	
	RTRConfigDb(){};

	virtual ~RTRConfigDb();
		// _TAG Destructor

	virtual RTRBOOL error() const = 0;	
		// Is the config db in an error state?
		// _TAG01 State 
			
	virtual const char*	errorText() const = 0;
		// Explanation for the error.
		// _TAG01 State 

// Query
	virtual RTRBOOL	has(
				const RTRObjectId& classId, 
				const RTRObjectId& instanceId, 
				const RTRString& varName) const = 0;
		// Does db contain a variable corresponding to the class identifier
		// and instance identifier with the given variable name?
		// REQUIRE: !error()
		// _TAG02 Query

// Access
	virtual RTRConfigVariable variable(
				const RTRObjectId& classId, 
				const RTRObjectId& instanceId,
				const RTRString& varName, 
				const RTRString& dflt,
				RTRBOOL hidden=RTRFALSE ) const = 0;
		// The variable corresponding to the given class identifier and 
		// instance identifier along with the given variable name. 
		// If no value is available, the returned config variable will use 
		// the default value. 
		// REQUIRE: !error()
		// ENSURE: !Result.error()
		// _TAG03 Access

	virtual RTRConfigVariable variable(
				const RTRObjectId& classId, 
				const RTRObjectId& instanceId, 
				const RTRString& varName,
				RTRBOOL hidden=RTRFALSE ) const = 0;
		// The variable corresponding to the given class identifier and 
		// instance identifier along with the given variable name. 
		// If no value is available, the returned config variable will 
		// have its error set. 
		// REQUIRE: !error()
		// ENSURE: has(classId, instanceId, varName) == !Result.error()
		// _TAG03 Access 

// Client management
	virtual void addClient(RTRConfigDbClient& newClient) = 0;

	virtual void dropClient(RTRConfigDbClient& oldClient) = 0;

	virtual RTRBOOL hasClient() const = 0;

};

#endif 
