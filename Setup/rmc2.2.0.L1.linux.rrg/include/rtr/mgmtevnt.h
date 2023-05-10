//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Dec. 20 1996"
// Version: 1.0

#ifndef _rtr_mgmtevnt_h
#define _rtr_mgmtevnt_h

#include "rtr/objid.h"
#include "rtr/vardatti.h"

//
// Synopsis:
// #include "rtr/mgmtevnt.h"
//
// RTRMgmtEvent event;
// event.setIdentifier("instanceId_or_string");
// event.setText("Event text");
// event.setSeverity(RTRMgmtEvent::Alert);
// event.log();
//
// Description:
// RTRMgmtEvent provides the means for managed applications to generate 
// events for processing by managing applications. Events have an 
// identifier (component), text, severity, and a timestamp. The identifier is that of
// the component generating the event. Text is descriptive information about the event. 
// Severity is a value between RTRMgmtEvent::Emergency and RTRMgmtEvent::Debug.
// A timestamp will be generated automatically if none is set.
//
// RTRMgmtEvent provides comparison operators based on the timestamp attribute.
// Newer events are greater than older events.
//
// <b>NOTE: This class replaces RTRLogEvent. The old RTRLogEvent methods
// are still available, but are marked as obsolete.</b>
// 
// See Also:
// RTRLogEvent, RTRObjectId, RTRString
//
// Inherits:
// RTRDLink0
//

class RTRMgmtEvent :
	public RTRDLink0
{ 
public:
// Constructor
	RTRMgmtEvent();
		// A blank event.
		// ENSURE: severity() == Info
		// _TAG Constructor

	RTRMgmtEvent(const RTRObjectId&, const RTRString&, int);
		// A new event with the given attributes
		// _TAG Constructor

	RTRMgmtEvent(const RTRObjectId&, const RTRString&, int, unsigned long);
		// A new event with the given attributes (and timestamp).
		// _TAG Constructor

	RTRMgmtEvent(const RTRMgmtEvent&);
		// _TAG Constructor

// Attributes
	inline const RTRObjectId& instanceId() const;
		// The unique instance identifier for this event.
		// _TAG02 Attributes

	inline const RTRString& text() const;
		// The descriptive text for this event.
		// _TAG02 Attributes

	inline int severity() const;
		// Severity of the event. Valid values are:\\
		// Emergency, Alert, Critical, Error, Warning, Notice,
		// Info, Debug, or None
		// _TAG02 Attributes

	inline const RTRDateTime& timestamp() const;
		// _TAG02 Attributes

// Comparison
	inline RTRBOOL operator<(const RTRMgmtEvent&) const;
		// Time based (newer is greater than older).
		// _TAG04 Comparison

	inline RTRBOOL operator>(const RTRMgmtEvent&) const;
		// Time based (newer is greater than older).
		// _TAG04 Comparison

	inline RTRBOOL operator==(const RTRMgmtEvent&) const;
		// Time based (newer is greater than older).
		// _TAG04 Comparison

	inline RTRBOOL operator<=(const RTRMgmtEvent&) const;
		// Time based (newer is greater than older).
		// _TAG04 Comparison

	inline RTRBOOL operator>=(const RTRMgmtEvent&) const;
		// Time based (newer is greater than older).
		// _TAG04 Comparison

// Operations
	void setIdentifier(const RTRObjectId&);
		// Set the unique identifier for this event.
		// _TAG07 Operations

	void setComponent(const char *c);
		// OBSOLETE - Use setIdentifier() instead. 
		// _TAG11 Operations

	void setComponent(const RTRString& c);
		// OBSOLETE - Use setIdentifier() instead. 
		// _TAG11 Operations

	void setSeverity(int);
		// Set the severity level for this event by integer. Valid 
		// values must be in the range from RTRMgmtEvent::Emergency
		// to RTRMgmtEvent::Debug.
		// ENSURE: severity() <= Emergency && severity() >= Debug
		// _TAG07 Operations

	void setSeverity(const RTRString&);
		// Set the severity level for this event by string. Valid 
		// values must be one of the following: "Emergency", "Alert", 
		// "Critical", "Error", "Warning", "Notice", "Info" (default), "Debug".
		// ENSURE: severity() <= Emergency && severity() >= None
		// _TAG07 Operations

	void setText(const char *);
		// Set the descriptive text for this event.
		// _TAG07 Operations

	void setText(const RTRString&);
		// Set the descriptive text for this event.
		// _TAG07 Operations

	void setTimestamp();
		// Set the time at which the event occurred.
		// _TAG07 Operations

	void log();
		// Pass this event to the event routing mechanism.
		// _TAG07 Operations

	RTRBOOL hasAction();
		// Check _severity to determine if log would occur

// Operations
	RTRMgmtEvent& operator=(const RTRMgmtEvent&);
		// _TAG08 Operations -- assignment

// Static utilities
	static int severity(const RTRString&);
		// The integer value of the given severity string. Result will be
		// None if string is otherwise invalid.
		// _TAG09 Static utilities

	static RTRString severityString(int);
		// The string value of the given severity. Result will be
		// "None" if string is invalid.
		// _TAG09 Static utilities

// Static data
	static int Emergency;
		// _TAG10 Static data
	static int Alert;
		// _TAG10 Static data
	static int Critical;
		// _TAG10 Static data
	static int Error;
		// _TAG10 Static data
	static int Warning;
		// _TAG10 Static data
	static int Notice;
		// _TAG10 Static data
	static int Info;
		// _TAG10 Static data
	static int Debug;
		// _TAG10 Static data
	static int None;
		// _TAG10 Static data

protected:
// Data
	RTRObjectId _instanceId;
	RTRString _text;
	int _severity;
	RTRDateTimeUsec _timestamp;

}; 

inline 
const RTRObjectId& RTRMgmtEvent::instanceId() const
{
	return _instanceId;
}

inline 
const RTRString& RTRMgmtEvent::text() const
{
	return _text;
}

inline 
int RTRMgmtEvent::severity() const
{
	return _severity;
}

inline 
const RTRDateTime& RTRMgmtEvent::timestamp() const
{
	return _timestamp;
}

inline 
RTRBOOL RTRMgmtEvent::operator<(const RTRMgmtEvent& rhs) const
{
	return _timestamp < rhs._timestamp;
}

inline 
RTRBOOL RTRMgmtEvent::operator>(const RTRMgmtEvent& rhs) const
{
	return _timestamp > rhs._timestamp;
}

inline 
RTRBOOL RTRMgmtEvent::operator==(const RTRMgmtEvent& rhs) const
{
	return _timestamp == rhs._timestamp;
}

inline 
RTRBOOL RTRMgmtEvent::operator<=(const RTRMgmtEvent& rhs) const
{
	return _timestamp <= rhs._timestamp;
}

inline 
RTRBOOL RTRMgmtEvent::operator>=(const RTRMgmtEvent& rhs) const
{
	return _timestamp >= rhs._timestamp;
}

#endif
