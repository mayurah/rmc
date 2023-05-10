//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Dec. 23 1996"
// Version: 1.0

#ifndef _rtr_meselect_h
#define _rtr_meselect_h

#include "rtr/mgmtevnt.h"
#include "rtr/linkl.h"

//
// Synopsis:
// #include "rtr/meselect.h"
//
// Description:
// RTRMgmtEventSelector selects management events based on a combination
// of component and severity. Used by instances of RTRMgmtEventFilter.
// 
// See Also:
// RTRMgmtEvent, RTRMgmtEventFilter
//
// Inherits:
//

class RTRMgmtEventSelector :	
	public RTRDLink0
{ 
public:
// Constructor
	inline RTRMgmtEventSelector();
		// A default selector. Equivalent to 
		// RTRMgmtEventSelector(RTRMgmtEvent::Error)
		// _TAG Constructor

	inline RTRMgmtEventSelector(const RTRObjectId& componentId);
		// A selector which will match events of any severity from components 
		// which are identified as descendants of componentId.
		// _TAG Constructor

	inline RTRMgmtEventSelector(int s);
		// A selector which will match an event from any component wherein
		// the severity of the event is greater than s.
		// _TAG Constructor

	inline RTRMgmtEventSelector(const RTRObjectId& componentId, int s);
		// A selector which will match events of severity s or greater
		// from components which are identified as descendants of componentId.
		// _TAG Constructor

	inline RTRMgmtEventSelector(const RTRMgmtEventSelector&);
		// _TAG Constructor

// Destructor
	inline ~RTRMgmtEventSelector();
		// _TAG Destructor

// Attributes
	inline const RTRObjectId& instanceId() const;
		// _TAG02 Attributes

	inline int severity() const;
		// _TAG02 Attributes

// Query
	inline RTRBOOL selectsComponent(const RTRMgmtEvent&);
		// _TAG03 Query

	inline RTRBOOL selectsSeverity(const RTRMgmtEvent&);
		// _TAG03 Query

	inline RTRBOOL selects(const RTRMgmtEvent&);
		// _TAG03 Query

// Comparison
	inline RTRBOOL operator>(const RTRMgmtEventSelector& other) const;
		// Is this selector more likely to match an event than other?
		// _TAG04 Comparison

	inline RTRBOOL operator>=(const RTRMgmtEventSelector& other) const;
		// Is this selector more or equally likely to match an event than other?
		// _TAG04 Comparison

	inline RTRBOOL operator<(const RTRMgmtEventSelector& other) const;
		// Is this selector less likely to match an event than other?
		// _TAG04 Comparison

	inline RTRBOOL operator<=(const RTRMgmtEventSelector& other) const;
		// Is this selector less or equally likely to match an event than other?
		// _TAG04 Comparison

	inline RTRBOOL operator==(const RTRMgmtEventSelector& other) const;
		// Is this selector equivalent to other?
		// _TAG04 Comparison

// Transformation
	inline RTRString toString(const char delim=',') const;
		// _TAG05 Transformation
	
// Operations
	inline RTRMgmtEventSelector& operator=(const RTRMgmtEventSelector&);
		// _TAG07 Operations
	
// Static data
	static const RTRObjectId InstanceWildCard;

protected:
// Data
	RTRObjectId _instanceId;
	int _severity;

}; 

inline 
RTRMgmtEventSelector::RTRMgmtEventSelector()
	: _instanceId(InstanceWildCard), _severity(RTRMgmtEvent::Error)
{
}

inline 
RTRMgmtEventSelector::RTRMgmtEventSelector(const RTRObjectId& id)
	: _instanceId(id), _severity(RTRMgmtEvent::Error)
{
}

inline 
RTRMgmtEventSelector::RTRMgmtEventSelector(int s)
	: _instanceId(InstanceWildCard), _severity(s)
{
}

inline 
RTRMgmtEventSelector::RTRMgmtEventSelector(const RTRObjectId& id, int s)
	: _instanceId(id), _severity(s)
{
}

inline 
RTRMgmtEventSelector::RTRMgmtEventSelector(const RTRMgmtEventSelector& me)
	: _instanceId(me._instanceId), _severity(me._severity)
{
}

inline RTRMgmtEventSelector::~RTRMgmtEventSelector() { }

inline 
const RTRObjectId& RTRMgmtEventSelector::instanceId() const
{
	return _instanceId;
}

inline 
int RTRMgmtEventSelector::severity() const
{
	return _severity;
}

inline 
RTRBOOL RTRMgmtEventSelector::selectsComponent(const RTRMgmtEvent& me)
{
	return (_instanceId == InstanceWildCard || me.instanceId().isDescendant(_instanceId));
}

inline 
RTRBOOL RTRMgmtEventSelector::selectsSeverity(const RTRMgmtEvent& me)
{
	return _severity <= me.severity();
}

inline 
RTRBOOL RTRMgmtEventSelector::selects(const RTRMgmtEvent& me)
{
	return selectsComponent(me) && selectsSeverity(me);
}

inline 
RTRBOOL RTRMgmtEventSelector::operator==(const RTRMgmtEventSelector& rhs) const
{
	return  ( ( (_instanceId == rhs._instanceId) ||
		        ((!(_instanceId == InstanceWildCard))  &&
		        (!(rhs._instanceId == InstanceWildCard))
		        )
		  ) 
		  &&
		  ( _severity == rhs._severity)
		);
}

inline 
RTRBOOL RTRMgmtEventSelector::operator<(const RTRMgmtEventSelector& rhs) const
{
	// NOTE: greater severity matches fewer events and is 
	// therefore (from viewpoint of selector) < lower severity.
	return ( ( (!(_instanceId == InstanceWildCard))  &&
					(rhs._instanceId == InstanceWildCard)
			 ) 
			 ||
			 (_severity > rhs._severity)
			);
}

inline 
RTRBOOL RTRMgmtEventSelector::operator<=(const RTRMgmtEventSelector& rhs) const
{
	return ((*this) < rhs) || ((*this) == rhs);
}

inline 
RTRBOOL RTRMgmtEventSelector::operator>(const RTRMgmtEventSelector& rhs) const
{
	return !((*this) <= rhs);
}

inline 
RTRBOOL RTRMgmtEventSelector::operator>=(const RTRMgmtEventSelector& rhs) const
{
	return !((*this) < rhs);
}

inline 
RTRString RTRMgmtEventSelector::toString(const char delim) const
{
	RTRString result;
	result += _instanceId;
	result += delim;
	result += RTRMgmtEvent::severityString(_severity);
	return result;
}

inline 
RTRMgmtEventSelector& 
RTRMgmtEventSelector::operator=(const RTRMgmtEventSelector& me)
{
	_instanceId = me._instanceId;
	_severity = me._severity;
	return *this;
}

#endif
