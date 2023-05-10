//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "11/3/97"
// Version: 1.0

#ifndef _pnthrsmc_h
#define _pnthrsmc_h

#include "rtr/pnthrsm.h"


// Synopsis:
//	#include "rtr/pnthrsmc.h"
//
// Description:
// The base class for components which can register with an
// RTRProxyNumericThresholdMonitor to receive change events
// from that threshold monitor.
//
// See Also:
//	RTRProxyNumericThresholdMonitor
//
// Inherits:
//

class RTRProxyNumericThresholdMonitorClient
{
public:
// Destrcutor
	virtual ~RTRProxyNumericThresholdMonitorClient();
		// _TAG Destructor

// Event processing
	virtual void processProxyNumericThresholdMonitorUpdate(
				RTRProxyNumericThresholdMonitor&
				) = 0;
		// The given threshold has been updated.
		// _TAG01 Event processing

	virtual void processProxyNumericThresholdMonitorError(
				RTRProxyNumericThresholdMonitor&
				) = 0;
		// The given threshold has transitioned to an error state.
		// _TAG01 Event processing
};

#endif
