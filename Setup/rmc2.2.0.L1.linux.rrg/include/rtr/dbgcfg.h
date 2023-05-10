//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|
//|       1400 Kensington Road, Oak Brook IL  60521       
//|
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: A. MacGaffey, T. Hansen
// Created: 01/04/94
// Version: 1.0
//

#ifndef _rtr_dbgcfg_h 
#define _rtr_dbgcfg_h

#include "rtr/config.h"
#include "rtr/rtrdefs.h"

// Synopsis:
// #include"rtr/dbgcfg.h"
//
// Description:
// 	This class provides a user with a configured parameter that
// 	can be used to determine if debug logging is enabled for this
// 	application component.
//
// 	Descendant classes call the extractConfiguration() feature to
// 	initialize the log debug parameter. The descendant class then
// 	calls loggingEnabled() to determine if the class is configured
// 	to log debug messages.
//
// See Also:
//	RTRConfig, RTRConfigDb, RTRConfigVariable, RTRDefaultConfigDb
//

class RTRDebugConfig
{
public:

	inline RTRBOOL loggingEnabled() const;
		// _TAG01 Other

	void extractConfiguration(
					const RTRObjectId& class_id,
					const RTRObjectId& instance_id,
					const RTRConfigDb& = RTRConfig::configDb());
		// Examine the config db to determine status of logging variable.
		// _TAG01 Other

// Static attributes
	static RTRString debugText;
	static RTRString logDebugVarName;		
		// Static attribute

// Obsolete
	RTRBOOL logDebug() const;
		// _TAG02 Obsolete

protected:
	
	RTRBOOL _log_debug;
	
};

inline RTRBOOL RTRDebugConfig::loggingEnabled() const
{
	return _log_debug;
}

#endif /* _rtr_dbgcfg_h */
