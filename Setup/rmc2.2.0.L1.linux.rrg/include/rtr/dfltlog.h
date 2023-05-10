//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/23/98"
// Version: 1.0

#ifndef _rtr_dfltlog_h
#define _rtr_dfltlog_h

#include "rtr/rtrdefs.h"
//#include "rtr/merouter.h"
#include "rtr/config.h"
#include "rtr/dfltacts.h"

// Synopsis:
// #include"rtr/dfltlog.h"
//
// Description:
// This class provides three types of management event actions
// (file, std err and system).  This logger consults the configuration
// database, passed on construction, to determine wether it is
// enabled and wether it is supposed to display its configuration
// on stdout.
//
// The default installation results in a stderr logger which
// is instantiated but disabled, and a file logger which is
// instantiated and traps events of all severity levels (except
// debug) from all components.
// The instance name of defaultFileAction is "defaultFileAction"
// and the instance name of the defaultStdErrorAction
// is "defaultStdErrorAction".
// The instance id of each depends on the name given to the logger on
// its instantiation
// E.g. if the name of the logger is "logger" the instance id of
// the defaultFileAction will be "logger.defaultFileAction".
//
// Class id:  SSLDispatcher     Instance Id: -- assigned from constructor --
//
// \verbatim
// Variable Name         Type      Default   Use
// --------------------- -------   -------   ---------------------------------
// enable                Boolean   True      enables event processing
//
// display_configuration Boolean   False     print configuration to
//                                           stdout on startup
//
// install_file_action   Boolean   True      installs an instance of
//                                           RTRDefaultFileAction on startup
//
// install_stderr_action Boolean   False     installs an instance of
//                                           RTRDefaultStdErrAction on startup
//
// install_system_action Boolean   False     installs an instance of
//                                           RTRDefaultSystemAction on startup
// \endverbatim
//
// See Also:
// RTRDefaultFileAction, RTRDefaultStdErrAction,
// RTRMgmtEvent, RTRMgmtAction, RTRMgmtEventRouter
//
// Inherits:
// N/A

class RTRDefaultLogger
{
public:
// Constructor
	RTRDefaultLogger(
			const RTRObjectId& appid,
			const RTRString& name,
			const RTRConfigDb& configDb = RTRConfig::configDb()
			);
		// Construct a default logger and associated default log actions
		// as per configuration.
		// _TAG Constructor

	RTRDefaultLogger(
			const RTRObjectId& appid,
			const RTRString& name,
			const RTRString& appName,
			const RTRConfigDb& configDb = RTRConfig::configDb()
			);
		// Construct a default logger and associated default log actions
		// as per configuration.
		// The appName value will be used by all log actions which require an
		// application name.
		// _TAG Constructor
	
// Destructor
	~RTRDefaultLogger();
		// _TAG Destructor

// Attributes
	RTRDefaultFileAction *defaultFileAction();
		// The file action used by the logger.
		// Creation of this action can be determined by configuration.
		// The default is to create this action.
		// _TAG02 Attributes

	RTRDefaultStdErrAction *defaultStdErrorAction();
		// The standard error output action used by the logger. 
		// Creation of this action can be determined by configuration.
		// The default is to *not* create this action.
		// _TAG02 Attributes

	RTRDefaultSystemAction *defaultSystemAction();
		// The system logger action used by the logger. 
		// Creation of this action can be determined by configuration.
		// The default is to *not* create this action.
		// _TAG02 Attributes

// Utilities
	RTRString getSelectorName();
		// _TAG03 Utilities
	
	void setSelectorName(const RTRString& name);
		// _TAG03 Utilities

	void displayConfiguration() const;
		// displays logger on stdout
		// _TAG03 Utilities

	void setSelector(RTRString & name);
		// sets the logger selector 
		// _TAG03 Utilities

// Static data
	static RTRString displayConfigurationDefault;
	static RTRString displayConfigurationVarName;
	static RTRString installDfltFileActionVarName;
	static RTRString installDfltStdErrActionVarName;
	static RTRString installDfltSystemActionVarName;
	static RTRString dfltFileActionName;
	static RTRString dfltStdErrActionName;
	static RTRString dfltSystemActionName;
		// Static data

protected:
// Utilities
	void initialize(
			const RTRObjectId& appid,
			const RTRString& name,
			const RTRConfigDb& configDb );
		// Complete the initialization process.

// Data
	RTRString _appName;
	RTRObjectId _classId;
	RTRDefaultFileAction *_defaultFileAction;
	RTRDefaultStdErrAction *_defaultStdErrorAction;
	RTRDefaultSystemAction *_defaultSystemAction;
		// Data

private:
// Do not implement
	RTRDefaultLogger(const RTRDefaultLogger&);
	RTRDefaultLogger& operator=(const RTRDefaultLogger&);
};

#endif
