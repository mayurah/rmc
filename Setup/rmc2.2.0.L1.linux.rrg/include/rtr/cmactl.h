//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/21/98"
// Version: 1.0

#ifndef _rtr_cmactl_h
#define _rtr_cmactl_h

#include "rtr/objid.h"
#include "rtr/mgmtact.h"

// Synopsis:
// #include "rtr/cmactl.h"
//
// Description:
// An abstract base class for action controllers which utilize the 
// configuration database for configuring a management action.
//
// Descendants should inherit in this implementation. This implementation
// checks a configuration database to determine whether it is enabled
// or not, and sets up the component/severity pairs.  Decendants should call
// extractConfiguration() to setup the mgmt action properly.
// 
// \verbatim
// enable:          boolean - This variable determines whether the action
//                  is to be enabled by installing it into the 
//                  RTRMgmtEventRouter.
//
// selector:        List - A comma seperated list of "dot pairs".
// \endverbatim
// 
// E.g. To match "Info" events from the component with name "component_name"
// and also match "Emergency" events from all other components use
// the following line in the config file:
// \bullet
// o *selector: component_name.Info, *.Emergency
// \endbullet
//
// See Also:
// RTRFileConfigMgmtActionCntrl, RTRSystemConfigMgmtActionCntrl,
// RTRStdErrConfigMgmtActionCntrl
//
// Inherits:
//

class RTRConfigMgmtActionCntrl
{
public:
// Constructor
	RTRConfigMgmtActionCntrl();
                // _TAG Constructor

// Destructor
	~RTRConfigMgmtActionCntrl();
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

	virtual void displayConfiguration() const;
		// _TAG02 Attributes

	RTRString getSelectorName();
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

	void setSelector(RTRString& level);
		// _TAG03 Operations

// Static Data
	static RTRString enableVarName;
	static RTRString selectorVarName;
	static RTRString defaultEnable;
	static RTRString defaultSelector;
		// _TAG03 Static Data

protected:
// Attributes
	virtual RTRMgmtAction& action() const = 0;

// Utilities
	void applyFilter(const RTRString&);
	virtual void extractConfiguration();

private:
// Don't implement
	RTRConfigMgmtActionCntrl(const RTRConfigMgmtActionCntrl&);
	RTRConfigMgmtActionCntrl& operator=(const RTRConfigMgmtActionCntrl&);
};

inline
RTRBOOL RTRConfigMgmtActionCntrl::enabled() const
{
        return ((RTRConfigMgmtActionCntrl*)this)->action().installed();
}

inline
const RTRObjectId& RTRConfigMgmtActionCntrl::instanceId() const
{
        return ((RTRConfigMgmtActionCntrl*)this)->action().instanceId();
}

inline
const RTRObjectId& RTRConfigMgmtActionCntrl::classId() const
{
        return ((RTRConfigMgmtActionCntrl*)this)->action().classId();
}

#endif

