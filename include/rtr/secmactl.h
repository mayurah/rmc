//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/16/98"
// Version: 1.0

#ifndef _rtr_secmactl_h
#define _rtr_secmactl_h

#include "rtr/cmactl.h"
#include "rtr/ostrmact.h"
#include "rtr/objid.h"
#include "rtr/config.h"


// Synopsis:
// #include "rtr/secmactl.h"
//
// Description:
// This class creates an RTROStreamMgmtAction and configures it 
// based on entries found in the configuration database.
//
// Class identifier: "LogAction.StderrAction"
//
// See Also:
// RTRStdErrMgmtActionCntrl, RTROStreamMgmtAction
//
// Inherits:
// RTRConfigMgmtActionCntrl
//

class RTRStdErrConfigMgmtActionCntrl
	: public RTRConfigMgmtActionCntrl
{
public:
// Constructor
	RTRStdErrConfigMgmtActionCntrl(
			const RTRObjectId& context,
			const RTRString& nm
			);
		// _TAG Constructor

// Destructor
	~RTRStdErrConfigMgmtActionCntrl();
		// _TAG Destructor

// Attributes
	RTRMgmtAction& action() const;
		// _TAG01 Attributes

// Static Data
	static RTRObjectId _classId;
		// _TAG02 Static Data

protected:
// Data
	RTROStreamMgmtAction _action;

private:
// Do not implement
	RTRStdErrConfigMgmtActionCntrl(const RTRStdErrConfigMgmtActionCntrl&);
	RTRStdErrConfigMgmtActionCntrl& operator=(const RTRStdErrConfigMgmtActionCntrl&);
};

#endif
