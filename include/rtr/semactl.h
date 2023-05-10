//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/16/98"
// Version: 1.0

#ifndef _rtr_semactl_h
#define _rtr_semactl_h

#include "rtr/objid.h"
#include "rtr/ostrmact.h"


// Synopsis:
// #include "rtr/semactl.h"
//
// Description:
// Creates an instance of RTROStreamMgmtAction and uses parameters
// passed in the constructor and methods to configure it.
//
// See Also:
// RTRStdErrConfigMgmtActionCntrl, RTROStreamMgmtAction
//
// Inherits:
//

class RTRStdErrMgmtActionCntrl
{
public:
// Constructor
	RTRStdErrMgmtActionCntrl(
			const RTRObjectId& context,
			const RTRString& nm,
			const RTRString& filter=""
			);
		// ENSURE: enabled()
		// _TAG Constructor

// Destructor
	~RTRStdErrMgmtActionCntrl();
		// _TAG Destructor

// Identity
	inline const RTRObjectId& classId() const;
		// _TAG01 Identity

	inline const RTRObjectId& instanceId() const;
		// _TAG01 Identity

// Attributes
	RTRBOOL enabled() const;
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
	RTROStreamMgmtAction _action;

private:
// Do not implement
	RTRStdErrMgmtActionCntrl(const RTRStdErrMgmtActionCntrl&);
	RTRStdErrMgmtActionCntrl& operator=(const RTRStdErrMgmtActionCntrl&);
};

inline
RTRBOOL RTRStdErrMgmtActionCntrl::enabled() const
{
	return _action.installed();
}

inline
const RTRObjectId& RTRStdErrMgmtActionCntrl::instanceId() const
{
        return _action.instanceId();
}

inline
const RTRObjectId& RTRStdErrMgmtActionCntrl::classId() const
{
        return _action.classId();
}


#endif
