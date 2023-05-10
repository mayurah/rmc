//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Dec. 20 1996"
// Version: 1.0

#ifndef _rtr_maction_h
#define _rtr_maction_h

#include "rtr/mgmteflt.h"

//
// Synopsis:
// #include "rtr/mgmtact.h"
//
// Description:
// RTRMgmtAction is the abstact base class for components which can be 
// installed with an instance of RTRMgmtEventRouter in order to processes
// application generated management events.
// 
// Descendants must implement processFilteredMgmtEvent(), and may override
// the default implementation of processMgmtEvent() in order to provide
// specialized filtering. RTRMgmtAction creates a default filter 
// (passes RTRMgmtError::Error and above from all components) which may be 
// overridden on the constructor or via the setFilter() method.
//
// An action must be installed with the router. The install() method is 
// provided for this purpose. The base class destructor calls deinstall() 
// if necessary.
//
// See Also:
// RTRMgmtEvent, RTRMgmtEventRouter
//
// Inherits:
//

class RTRMgmtAction
{ 
public:
// Constructor
	RTRMgmtAction(
			const RTRObjectId& classOfAction, // Type of this action
			const RTRObjectId& id	          // Id of this action
			);
		// _TAG Constructor

	RTRMgmtAction(
			const RTRObjectId& classOfAction, // Type of this action
			const RTRObjectId& id,	  	  // Id of this action
			const RTRMgmtEventFilter& filter  // Filter for this action
			);
		// An action with the given filter (copied).
		// _TAG Constructor

// Destructor
	virtual ~RTRMgmtAction();
		// _TAG Destructor

// Identity
	inline const RTRObjectId& classId() const;
		// Type of this action.
		// _TAG01 Identity

	inline const RTRObjectId& instanceId() const;
		// Identifier for this action.
		// _TAG01 Identity

// Attributes
	inline const RTRMgmtEventFilter& filter() const;
		// The current filter.
		// _TAG03 Attributes

// State
	inline RTRBOOL installed() const; 
		// Is this action installed with its event router?
		// _TAG04 Attributes

// Operations
	virtual void processMgmtEvent(const RTRMgmtEvent&);
		// Filter the given event with filter(). If passed, invoke
		// processFilteredMgmtEvent()
		// _TAG07 Operations

	virtual void processFilteredMgmtEvent(const RTRMgmtEvent&) = 0;
		// Take action on the given event.
		// _TAG07 Operations

	void install();
		// Install this action its router.
		// REQUIRE: !installed()
		// ENSURE: installed()
		// _TAG07 Operations

	void deinstall();
		// Deinstall this action.
		// REQUIRE: installed()
		// ENSURE: !installed()
		// _TAG07 Operations

	void setFilter(const RTRMgmtEventFilter&);
		// Use the given filter (copied).
		// _TAG07 Operations

protected:
// Data
	RTRObjectId _classId;
	RTRObjectId _instanceId;
	RTRMgmtEventFilter _filter;
	RTRBOOL _installed;

private:
// Don't implement
	RTRMgmtAction(const RTRMgmtAction&);
	RTRMgmtAction& operator=(const RTRMgmtAction&);
}; 

inline 
const RTRObjectId& RTRMgmtAction::classId() const
{
	return _classId;
}

inline 
const RTRObjectId& RTRMgmtAction::instanceId() const
{
	return _instanceId;
}

inline 
const RTRMgmtEventFilter& RTRMgmtAction::filter() const
{
	return _filter;
}

inline 
RTRBOOL RTRMgmtAction::installed() const
{
	return _installed;
}

#endif
