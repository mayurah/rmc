//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Dec. 21 1996"
// Version: 1.0

#ifndef _rtr_mgmteflt_h
#define _rtr_mgmteflt_h

#include "rtr/mgmtevnt.h"
#include "rtr/meselect.h"
#include "rtr/dslist.h"

//
// Synopsis:
// #include "rtr/mgmteflt.h"
//
// Description:
// RTRMgmtEventFilter is a utility class used by RTRMgmtAction to select
// instances of RTRMgmtEvent for processing.
// 
// See Also:
// RTRMgmtAction, RTRMgmtEventSelector, RTRMgmtEventRouter
//
// Inherits:
//

class RTRMgmtEventFilter
{ 
public:
// Constructor
	RTRMgmtEventFilter();
		// A default filter, matching events of severity RTRMgmtEvent::Error
		// or greater from any component.
		// _TAG Constructor

	RTRMgmtEventFilter(const RTRObjectId&, const RTRString&);
		// A filter with a single selector constructied with the given id 
		// and severity level.
		// _TAG Constructor

	RTRMgmtEventFilter(const RTRMgmtEventFilter&);
		// _TAG Constructor

// Destructor
	virtual ~RTRMgmtEventFilter();
		// _TAG Destructor

// Query
	virtual RTRBOOL selects(const RTRMgmtEvent&) const;
		// Does this filter pass (allow) the given event?
		// _TAG04 Query

	RTRBOOL hasSelector(const RTRObjectId& id, int sev) const;
		// Does this filter have a selector matching the given instanceId
		// and severity?
		// _TAG04 Query

	RTRBOOL hasSelector(const RTRObjectId&, const RTRString&) const;
		// Does this filter have a selector matching the given instanceId
		// and severity?
		// _TAG04 Query

	RTRBOOL hasSelector(const RTRMgmtEventSelector& s) const;
		// Does this filter select events selected by s?
		// _TAG04 Query

// Transformation
	RTRString toString(const char selDelim=' ', const char delim=',') const;
		//_TAG05 Transformation

// Operations
	RTRMgmtEventFilter& operator=(const RTRMgmtEventFilter&);
		//_TAG07 Operations

	RTRMgmtEventFilter operator|(const RTRMgmtEventFilter& other);
		// A new filter which is the join of this filter and other.
		//_TAG07 Operations

	RTRMgmtEventFilter& operator|=(const RTRMgmtEventFilter& other);
		// Merge the selectors of other with this filter.
		//_TAG07 Operations

	void addSelector(const RTRObjectId& id, int sev = RTRMgmtEvent::Error);
		// Add a new selector to this filter.
		// ENSURE: hasSelector(id, sev)
		//_TAG07 Operations
		
	void addSelector(const RTRObjectId& id, const RTRString& sevString);
		// Add a new selector to this filter.
		// ENSURE: hasSelector(id, sevString)
		//_TAG07 Operations
		
	void addSelector(int sev);
		// Add a new selector to this filter.
		// ENSURE: hasSelector("*", sev)
		//_TAG07 Operations
		
	void addSelector(const RTRString& sevString);
		// Add a new selector to this filter.
		// ENSURE: hasSelector("*", sevString)
		//_TAG07 Operations
		
	void addSelector(const RTRMgmtEventSelector& s);
		// Add a new selector to this filter (copied).
		// ENSURE: hasSelector(s.instanceId(), s.severity())
		//_TAG07 Operations

	void addSelectors(const RTRString& s, char d1=',', char d2='.');
		// Add selectors extracted from the given string. For example:
		// if d1 = ' ' and d2 = ',' then s might be "Foo.Error, Bar.Info".
		// ENSURE: hasSelector(s.instanceId(), s.severity())
		//_TAG07 Operations

	void normalizeSelectors();
		// Eliminate redundant selectors.
		//_TAG07 Operations

	void removeAllSelectors();
		// Revert this filter to the default.
		//_TAG07 Operations

	void passAll();
		// Make this filter pass everything except debug events.
		// ENSURE: hasSelector("*", "Info");
		//_TAG07 Operations

	void passAllAndDebug();
		// Make this filter pass everything including debug events.
		// ENSURE: hasSelector("*", "Debug");
		//_TAG07 Operations

protected:
// Data
	RTRDescSortList<RTRMgmtEventSelector, RTRDLink0> _selectors;
}; 

#endif
