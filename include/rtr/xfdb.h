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

#ifndef _rtr_xfdb_h 
#define _rtr_xfdb_h

#include "rtr/cfgdb.h"
#include "rtr/lock.h"

// Synopsis:
// #include "rtr/xfdb.h"
// 
// RTRXFileDb configDb("path_name");
//
// Description:
// 	This descendant of a RTRFileConfigDb implements an "X" version
// 	of a file based configuration database. The X11 library configuration
// 	utilites are used to parse and maintain config variables retrieved
// 	from a disk file.
//
// 	Application components which use configuration variables have associated
// 	with them both a class identifier and an instance identifier. This allows
// 	system components to be configured (by means of variables) on a class
// 	basis and on a per instance basis. The precedence of the class identifiers
// 	relative to instance identifiers is based on the X11 configuration utility.
// 	(See the "Xlib Reference Manual - Volume Two" under "XrmGetResource" for
// 	details).
//
// See Also:
//	RTRConfig
//
// Inherits:
//	RTRConfigDb
//

class RTRXDb;

class RTRXFileDb : public RTRConfigDb
{
public:

// Constructor
	RTRXFileDb();
		// Create an empty config database.
		// _TAG Constructor

	RTRXFileDb(const char * p);
		// Create the config database using the pathname p to retrieve
		// configuration info. Upon completion, the client should call the
		// error() feature. 
		// _TAG Constructor

// Destructor
	~RTRXFileDb();
		// _TAG Destructor

// State 
	RTRBOOL error() const;
		// Is the config db in an error state?
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
		// <Synchronized>
		// REQUIRE: !error()
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
		// <Synchronized>
		// REQUIRE: not_in_error: !error()
		// ENSURE: has(classId, instanceId, varName)? !Result.error() : 1
		// ENSURE: !has(classId, instanceId, varName)? !Result.error(): 1
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
		// <Synchronized>
		// REQUIRE: not_in_error: !error()
		// ENSURE: has(classId, instanceId, varName)? !Result.error() : 1
		// ENSURE: !has(classId, instanceId) ? Result.error(): 1
		// _TAG03 Access

// Client management
	virtual void addClient(RTRConfigDbClient& newClient);

	virtual void dropClient(RTRConfigDbClient& oldClient);

	virtual RTRBOOL hasClient() const;

// File features
	void old_load(const char *fileName);
		// <Synchronized>
		// _TAG05 File features

// File features
	void load(const char *fileName);
		// <Synchronized>
		// _TAG05 File features

	RTRXDb& XDb() const { return *_xdb; }

protected:
	
	static const char* cannotOpenFileText;

// Attributes
	RTRString _filePath;
	const char	*_error_text; 			// Internal error text
	char	*_db_ptr;					// Pointer to external x_db handle.
	RTRBOOL _error;						// Internal error representation
	RTRString *_temp_buf; 				// Internal buffer.
	RTRBOOL _isEmpty;    				// Is this db empty?
	RTRLockableObj _dbLock;

	RTRXDb* _xdb;
	RTRConfigDbClient *_client; // allow 1 client

// Methods
	virtual int old_retrieve(
					const RTRObjectId& classId, 
					const RTRObjectId& instanceId) const;
		// Retrieve value from x db

	void old_initDb();	
		// Initialize the x file db.

	virtual int retrieve(
					const RTRObjectId& classId, 
					const RTRObjectId& instanceId) const;
		// Retrieve value from x db

	void initDb();	
		// Initialize the x db.

};

#endif  // _rtxfdb_h
