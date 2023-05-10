//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "11/3/97"
// Version: 1.0

#ifndef _pnthrsm_h
#define _pnthrsm_h

#include "rtr/thress.h"
#include "rtr/prxymn.h"

class RTRProxyNumericThresholdMonitorClient;


// Synopsis:
//	#include "rtr/pnthrsm.h"
//
// Description:
// Monitors a RTRProxyManagedNumeric variable and notifies clients when threshold
// and rearm values have been crossed.
// The threshold values cannot be dynamically modified,
// The state of the threshold reflects the availability of the numeric variable
// that is being monitored.  If the variable is deleted or transitions to an error
// state then the threshold class will transition to an unrecoverable error
// state. 
//
// See Also:
//	RTRProxyNumericThresholdMonitorClient, RTRThresholdSpecification,
//	RTRThresholdRegion, RTRThresholdRegionIterator
//
// Inherits:
//	public RTRProxyManagedVariableClient
//

class RTRProxyNumericThresholdMonitor :
		public RTRProxyManagedVariableClient
{
public:
// Constructor
	RTRProxyNumericThresholdMonitor(
			RTRProxyManagedNumeric& var,
			const RTRThresholdSpecification& spec
			);
		// REQUIRE: var.inSync();
		// REQUIRE: var.type() == RTRProxyManagedVariableHandle::Numeric
		//       || var.type() == RTRProxyManagedVariableHandle::NumericRange
		//       || var.type() == RTRProxyManagedVariableHandle::NumericConfig
		//       || var.type() == RTRProxyManagedVariableHandle::Gauge
		//       || var.type() == RTRProxyManagedVariableHandle::GaugeConfig
		// ENSURE: value() >  currentRegion().minValue()
		// ENSURE: value() <= currentRegion().maxValue()
		// ENSURE: &(currentRegion()) == &(previousRegion())
		// _TAG Constructor

// Destructor
	~RTRProxyNumericThresholdMonitor();
		// _TAG Destructor
			
// Attributes
	inline const RTRThresholdSpecification& specification() const;
		// The threshold specification used by this threshold monitor.
		// _TAG01 Attributes;

	inline RTRProxyManagedNumericPtr numeric() const;
		// The numeric variable being monitored.
		// _TAG01 Attributes

	inline long value() const;
		// The current value of the numeric variable.
		// _TAG01 Attributes

	inline const RTRThresholdRegion& currentRegion() const;
		// The region that the threshold is currently located.
		// _TAG01 Attributes

	inline const RTRThresholdRegion& previousRegion() const;
		// The region that the threshold was previously located.
		// _TAG01 Attributes

	inline const RTRString& text() const;
		// A textual explaination of the current state.
		// _TAG01 Attributes

// State
	inline RTRBOOL error() const;
		// Is the threshold in an unrecoverable error condition ?
		// _TAG02 State

// Client management
	virtual void addClient(RTRProxyNumericThresholdMonitorClient& client);
		// Register the given client to receive events from 
		// this variable.
		// ENSURE : hasClient(newClient)
		// _TAG03 Client management

	virtual void dropClient(RTRProxyNumericThresholdMonitorClient& client);
		// Un-register the given client to receive events from 
		// this variable.
		// ENSURE : !hasClient(oldClient)
		// _TAG03 Client management

	RTRBOOL hasClient(RTRProxyNumericThresholdMonitorClient& client) const;
		// Is the given client registered to receive events from 
		// this variable.
		// _TAG03 Client management

protected:
// Operations
	RTRBOOL checkForFired(long);
	RTRBOOL checkForRearm(long);

// Utilities -- event propagation
	void indicateUpdate();
	void indicateError();
	void notifyUpdate(
			RTRProxyNumericThresholdMonitorClient*,
			RTRProxyNumericThresholdMonitor*);
	void notifyError(
			RTRProxyNumericThresholdMonitorClient*,
			RTRProxyNumericThresholdMonitor*);

// Event processing
	virtual void processProxyManagedVariableSync(RTRProxyManagedVariable&);
	virtual void processProxyManagedVariableDeleted(RTRProxyManagedVariable&);
	virtual void processProxyManagedVariableError(RTRProxyManagedVariable&);
	virtual void processProxyManagedVariableUpdate(RTRProxyManagedVariable&);

// Data
	RTRProxyManagedNumericPtr _var;
	RTRThresholdRegion *_currentRegion;
	RTRThresholdRegion *_previousRegion;
	RTRThresholdSpecification _spec;
	long _value;
	void *_notifier;
	RTRBOOL _error;
	RTRString _text;

private:
// Don't define these
	RTRProxyNumericThresholdMonitor(const RTRProxyNumericThresholdMonitor&);
	RTRProxyNumericThresholdMonitor& operator=(const RTRProxyNumericThresholdMonitor&);
		// Don't define these
};


inline
const RTRThresholdSpecification&
RTRProxyNumericThresholdMonitor::specification() const
{
	return _spec;
}

inline
RTRProxyManagedNumericPtr RTRProxyNumericThresholdMonitor::numeric() const
{
	return _var;
}

inline
long RTRProxyNumericThresholdMonitor::value() const
{
	return _value;
}

inline
const RTRThresholdRegion& RTRProxyNumericThresholdMonitor::currentRegion() const
{
	RTPRECONDITION(_currentRegion);
	return (RTRThresholdRegion&)(*_currentRegion);
}

inline
const RTRThresholdRegion& RTRProxyNumericThresholdMonitor::previousRegion() const
{
	RTPRECONDITION(_previousRegion);
	return (RTRThresholdRegion&)(*_previousRegion);
}

inline
RTRBOOL RTRProxyNumericThresholdMonitor::error() const
{
	if ( _spec.error() )
	{
		return RTRTRUE;
	}
	else
		return _error;
}

inline
const RTRString& RTRProxyNumericThresholdMonitor::text() const
{
	if ( _spec.error() )
	{
		return _spec.text();
	}
	else
		return _text;
}

#endif
