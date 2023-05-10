//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 27 1996"
// Version: 1.0

#ifndef _rtr_prxymvc_h
#define _rtr_prxymvc_h

class RTRProxyManagedVariable;

// Synopsis:
// #include"rtr/proxymo.h"
//
// Description:
// The base class for components which can register with a variable
// to receive change events from that variable.  The notifications
// are grouped into three categories:
// (1) proxy variable state changes,
// (2) the variable has been updated, and
// (3) the variable has been deleted by the managed application.
//
// See Also:
// RTRProxyManagedVariable,
// RTRProxyManagedCounter, RTRProxyManagedGauge,
// RTRProxyManagedNumeric, RTRProxyManagedString,
// RTRProxyManagedBoolean, RTRProxyManagedNumericRange,
// RTRProxyManagedNumericConfig, RTRProxyManagedStringConfig,
// RTRProxyManagedBooleanConfig, RTRProxyManagedGaugeConfig
//

class RTRProxyManagedVariableClient
{ 
public:
// Destructor
	virtual ~RTRProxyManagedVariableClient();
		// _TAG Destructor

// Event processing
	virtual void processProxyManagedVariableError(
			RTRProxyManagedVariable&
			) = 0;
		// The given variable has transitioned to an unrecoverable
		// error state.
		// _TAG01 Event processing

	virtual void processProxyManagedVariableSync(
			RTRProxyManagedVariable&
			) = 0;
		// The given variable has transitioned to the Sync state.
		// _TAG01 Event processing

	virtual void processProxyManagedVariableUpdate(
			RTRProxyManagedVariable&
			) = 0;
		// The given variable has changed.
		// _TAG01 Event processing

	virtual void processProxyManagedVariableDeleted(
			RTRProxyManagedVariable&
			) = 0;
		// The given variable has been deleted.
		// _TAG01 Event processing

}; 

#endif
