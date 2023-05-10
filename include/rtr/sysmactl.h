//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/23/98"
// Version: 1.0

#ifndef _rtr_sysmactl_h
#define _rtr_sysmactl_h

#include "rtr/objid.h"
#include "rtr/sysmact.h"


// Synopsis:
// #include "rtr/sysmactl.h"
//
// Description:
// This class creates an RTRSystemMgmtAction and configures it
// based on parameters passed in the constructor and method calls.
//
// Class identifier: "LogAction.SystemLogAction";
//
// See Also:
// RTRSystemConfigMgmtActionCntrl, RTRSystemMgmtAction
//
// Inherits:
//

class RTRSystemMgmtActionCntrl
{
public:
// Constructor
	RTRSystemMgmtActionCntrl(
			const RTRObjectId& context,
			const RTRString& nm,
			const RTRString& appName,
			const RTRString& filter=""
			);
		// ENSURE: enabled()
		// _TAG Constructor

// Destructor
	~RTRSystemMgmtActionCntrl();
		// _TAG Destructor

// Identity
	inline const RTRObjectId& instanceId() const;
		// _TAG01 Identity

	inline const RTRObjectId& classId() const;
		// _TAG01 Identity

// Attributes
	inline RTRBOOL enabled() const;
		// Has the action been installed into the RTRMgmtEventRouter ?
		// _TAG02 Attributes

	RTRMgmtAction& action();
		// _TAG02 Attributes

// Operations
	void enable();
		// REQUIRES: !enabled()
		// ENSURE: enabled()
		// _TAG03 Operations

	void disable();
		// REQUIRES: enabled()
		// ENSURE: !enabled()
		// _TAG03 Operations

// Static data
	static RTRObjectId _classId;
		// Static data

protected:
// Utilities
	void applyFilter(const RTRString&);

// Data
	RTRSystemMgmtAction _action;

private:
// Do not implement
	RTRSystemMgmtActionCntrl(const RTRSystemMgmtActionCntrl&);
	RTRSystemMgmtActionCntrl& operator=(const RTRSystemMgmtActionCntrl&);
};

inline
RTRBOOL RTRSystemMgmtActionCntrl::enabled() const
{
	return _action.installed();
}

inline
const RTRObjectId& RTRSystemMgmtActionCntrl::instanceId() const
{
        return _action.instanceId();
}

inline
const RTRObjectId& RTRSystemMgmtActionCntrl::classId() const
{
        return _action.classId();
}

#endif
