//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 10 1995"
// Version: 1.0

#ifndef _rtr_config_h
#define _rtr_config_h

#include "rtr/cfgdb.h"

class RTRDefaultConfigDb;

// Synopsis:
// #include"rtr/config.h"
//
// Description:
// 	Provides "global" access to a configuration database via the static function
//	configDb().  By default, the available database will be an instance of 
//  RTRDefaultConfigDb. The application can override this by instantiating some
//	other type of RTRConfigDb and "installing" it using the setConfigDb() function.
//
// See Also:
//	RTRConfigDb, RTRConfigVariable, RTRDebugConfig, RTRDefaultConfigDb
//

class RTRConfig
{
public:

	static void setConfigDb(const RTRConfigDb& db);
		// Set the global config database.
		// REQUIRE : !db.error()
		// _TAG01 Operation 

	static const RTRConfigDb& configDb();
		// _TAG02 Access 

protected:

	static const RTRConfigDb *_configDb;
	static const RTRDefaultConfigDb _defaultConfig;

};


// Export a function to allow DACS's DLL obtain access to the RTRConfigDb
#ifdef _WIN32
#include "rtr/os.h"
#ifdef __cplusplus
extern "C" {
#endif
RTR_API_EXPORT const RTRConfigDb *getGlobalConfigDb();
#ifdef __cplusplus
}
#endif
#endif // _WIN32

#endif // _rtr_config_h
