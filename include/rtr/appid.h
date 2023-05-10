//|-------------------------------------------------------
//|              Copyright (C) 1994 Reuters
//|       1400 Kensington Road, Oak Brook IL  60521
//| All rights rsvd.Duplication & distribution prohibited
//|-------------------------------------------------------
//
// Author: J. Arvanites, A. MacGaffey
// Created:
// Version: 1.0
//

#ifndef _rtr_appid_h
#define _rtr_appid_h

#include "rtr/rtobjid.h"

// Synopsis:
// #include "rtr/appid"
//
// RTRApplicationId appId1(argc, argv);
// RTRApplicationId appId2(argc, argv, "applicationName");
// RTRApplicationId appId3("instance1", "applicationName");
//
// Description:
//
// 	The class RTRApplicationId is a descendant of RTRObjectId that set's
// 	itself up as <hostname>.<instance>.<appName> where appName is the name
// 	of this application (typically the name of the executable) and instance is
// 	a numeric identifier which uniquely identifies this executable from other
// 	similar executables on the same host.
//
// 	An instance of RTRApplicationId is used as the root context for all
// 	object identifiers in application.
//
// See Also:
// RTRObjectId
//
// Inherits:
// RTRObjectId
//

class RTRApplicationId :	
	public RTRObjectId
{
public:
// Constructor
	RTRApplicationId(int argc, char **argv);
		// Construct an id of the form <hostname>.<instance>.<appName>,
		// where hostname is retrieved from the system, appName is
		// the name of the executable (from the command line) and instance is
		// extracted from the argv argument vector (using
		// -instance, or -Instance, or -INSTANCE).
		// _TAG Constructor

	RTRApplicationId(int argc, char **argv, const char *appName);
		// Construct an id of the form <hostname>.<instance>.<appName>,
		// where hostname is retrieved from the system and instance is
		// extracted from the argv argument vector. (using
		// -instance, or -Instance, or -INSTANCE).
		// _TAG Constructor

	RTRApplicationId(const char *instance, const char *appName);
		// Construct an id of the form <hostname>.<instance>.<appName>,
		// using the given instance and application name and retrieving
		// hostname from the system.
		// _TAG Constructor

// Destructor
	virtual ~RTRApplicationId();
		// _TAG Destructor

		// _TAG01 Attributes
		// _TAG01 Attributes
		// _TAG01 Attributes
protected:
// Utilities
	const char *instanceString(int argc, char **argv) const;
		// The instance argument, if any.
		// Looks for -instance, or -Instance, or -INSTANCE.

};

#endif
