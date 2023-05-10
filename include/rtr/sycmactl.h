//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/16/98"
// Version: 1.0

#ifndef _rtr_sycmactl_h
#define _rtr_sycmactl_h

#include "rtr/cmactl.h"
#include "rtr/mgmtact.h"
#include "rtr/objid.h"
#include "rtr/config.h"
#include "rtr/sysmact.h"


// Synopsis:
// #include "rtr/sycmactl.h"
//
// Description:
// This class creates an RTRSystemMgmtAction and configures it based
// on entries found in the configuration database.
//
// Class identifier: "LogAction.SystemLogAction";
//
// See Also:
// RTRSystemMgmtActionCntrl, RTRSystemMgmtAction
//
// Inherits:
// RTRConfigMgmtActionCntrl
//

class RTRSystemConfigMgmtActionCntrl
	: public RTRConfigMgmtActionCntrl
{
public:
// Constructor
	RTRSystemConfigMgmtActionCntrl(
			const RTRObjectId& context,
			const RTRString& nm,
			const RTRString& appName
			);
		// _TAG Constructor

// Destructor
	~RTRSystemConfigMgmtActionCntrl();
		// _TAG Destructor

// Attributes
	RTRMgmtAction& action() const;
		// _TAG01 Attributes

// Static Data
	static RTRObjectId _classId;
		// _TAG02 Static Data

protected:
// Data
	RTRSystemMgmtAction _action;

private:
// Do not implement
	RTRSystemConfigMgmtActionCntrl(const RTRSystemConfigMgmtActionCntrl&);
	RTRSystemConfigMgmtActionCntrl& operator=(const RTRSystemConfigMgmtActionCntrl&);
};

#endif
