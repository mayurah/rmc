//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/16/98"
// Version: 1.0

#ifndef _rtr_fmactl_h
#define _rtr_fmactl_h

#include "rtr/objid.h"
#include "rtr/fmact.h"


// Synopsis:
// #include "rtr/fmactl.h"
//
// Description:
// RTRFileMgmtActionCntrl creates an instance of RTRFileMgmtAction
// and configures it based on parameters passed in the constructor
// and methods.
//
// See Also:
// RTRFileConfigMgmtActionCntrl, RTRFileMgmtAction
//
// Inherits:
//

class RTRFileMgmtActionCntrl
{
public:
// Constructor
	RTRFileMgmtActionCntrl(
			const RTRObjectId& context,
			const RTRString& nm,
			const RTRString& filter="",
			const RTRString& filename="log.out",
			int maxBytes=10000,
			RTRBOOL flush=RTRTRUE,
			RTRBOOL truncate=RTRFALSE
			);
		// ENSURE: enabled()
		// _TAG Constructor

// Destructor
	~RTRFileMgmtActionCntrl();
		// _TAG Destructor

// Identity
	inline const RTRObjectId& classId() const;
		// _TAG01 Identity

	inline const RTRObjectId& instanceId() const;
		// _TAG01 Identity 

// Attributes
	RTRMgmtAction& action();
		// _TAG02 Attributes

	inline RTRBOOL enabled() const;
		// Has the action been installed into the RTRMgmtEventRouter ?
		// _TAG02 Attributes

// Operations
	void enable();
		// REQUIRE: !enabled()
		// ENSURE: enabled()
		// _TAG03 Operations

	void disable();
		// REQUIRE: enabled()
		// ENSURE: !enabled()
		// _TAG03 Operations

// Static data
	static RTRObjectId _classId;
		// Static data

protected:
// Utilities
	void applyFilter(const RTRString&);

// Data
	RTRFileMgmtAction _action;

private:
// Do not implement
	RTRFileMgmtActionCntrl(const RTRFileMgmtActionCntrl&);
	RTRFileMgmtActionCntrl& operator=(const RTRFileMgmtActionCntrl&);
};

inline
RTRBOOL RTRFileMgmtActionCntrl::enabled() const
{
	return _action.installed();
}

inline
const RTRObjectId& RTRFileMgmtActionCntrl::instanceId() const
{
        return _action.instanceId();
}

inline
const RTRObjectId& RTRFileMgmtActionCntrl::classId() const
{
        return _action.classId();
}

#endif
