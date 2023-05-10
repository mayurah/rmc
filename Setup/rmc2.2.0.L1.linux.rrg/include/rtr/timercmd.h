//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Feb. 08 1994"
// Modified: "May. 26 1994"
// Version: 2.0

#ifndef _timercmd_h 
#define _timercmd_h

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

#include "rtr/rtrdefs.h"
#include "rtr/tmintvl.h"
#include "rtr/linkl.h"

// Synopsis:
//  Implementation
//
// Description:
//  A RTRDLinkTC is a link element that exists in a RTRTimerCmd
//  used for storage.
//
// See Also: RTRDLink
//
 
class RTRDLinkTC
	: public RTRDLink
{
public:
	inline RTRDLinkTC() {};
		// _TAG Constructor
	inline ~RTRDLinkTC() {};
		// _TAG Destructor
};

// Synopsis:
// #include "rtr/timercmd.h"
// 
// "//" Abstract base class
//
// Description:
//	RTRTimerCmd is an abstract base class for components that will receive
//	timer events.
// 
//	Descendants must define the method processTimerEvent() to perform
//	a specific timer related task.
//  
//	The interval to be timed is set using setTimerOffset(). The timer must then
//	be activated using activate(). An active timer may be deactivated. A timer
//	will not automatically repeat. To implement a period timer, invoke activate()
//	in the implemementation of processTimerEvent(). It isn't necessary to
//	reset the offset, the most recently specified value will be used when
//	activated.
//
// See Also:
//	RTRTimerInterval
//

class RTREventNotifier; 

class RTRTimerCmd
	: public RTRDLinkTC
{

#ifndef _RDEV_NO_STL_
friend std::ostream& operator<<(std::ostream& os, RTRTimerCmd& tc);
#else
public:
void print(FILE* os);
#endif
public:
// Constructor
	RTRTimerCmd(RTREventNotifier *notifier = 0);
		// _TAG Constructor

// Destructor
	virtual ~RTRTimerCmd();
		// _TAG Destructor

// Attributes
	static RTRTimeInterval systemTime;
		// System time, set and used by activate().

	inline const RTRTimeInterval& timeOfEvent() const;
		// System time when event will expire. Set by activate().
		// _TAG01 Attributes

	inline long offsetSeconds() const;
		// Relative time of this event in seconds.
		// _TAG01 Attributes

	inline short offsetMilliseconds() const;
		// Relative offset milliseconds.
		// _TAG01 Attributes

// Comparison
	inline RTRBOOL operator==(RTRTimerCmd&) const;
		// _TAG02 Comparison

	inline RTRBOOL operator<(RTRTimerCmd&) const;
		// _TAG02 Comparison

	inline RTRBOOL operator<=(RTRTimerCmd&) const;
		// _TAG02 Comparison

	inline RTRBOOL operator>(RTRTimerCmd&) const;
		// _TAG02 Comparison

	inline RTRBOOL operator>=(RTRTimerCmd&) const;
		// _TAG02 Comparison

// State
	inline RTRBOOL active() const;
		// Is cmd() current installed in the notifier?
		// _TAG03 State

// Operations
	inline void setTimerOffset(long s, short m);
		// Set timer offset to s seconds and m milliseconds.
		// _TAG04 Operations

	void activate();
		// REQUIRE : ! active()
		// ENSURE : active()
		// _TAG04 Operations

	void deactivate();
		// REQUIRE : active()
		// ENSURE : !active()
		// _TAG04 Operations

// Event processing
	virtual void processTimerEvent() = 0;
		// Redefined by descendants to provide specific behaviour for this
		// timer.
		// _TAG05 Event processing

// Implementation
	inline RTRTimeInterval& eventTime();
		// Reset the time the event will expire.
		// _TAG06 Implementation

// Implementation
		// Set notifier
		// _TAG07 Implementation
	inline void setNotifier( RTREventNotifier *notifier );

protected:

	RTRTimeInterval toe;

	long offset_seconds;
	short offset_milli_seconds;

	RTREventNotifier *_timerCmd_notifier; 

private:

// Object Assignment ** DON'T DEFINE THIS!
	RTRTimerCmd& operator=(const RTRTimerCmd& rhs);

// Copy constructor ** DON'T DEFINE THIS!
	RTRTimerCmd(const RTRTimerCmd& other);

};

inline RTRBOOL RTRTimerCmd::operator==(RTRTimerCmd& other) const
{
	return (toe == other.toe);
}

inline RTRBOOL RTRTimerCmd::operator<(RTRTimerCmd& other) const
{
	return (toe < other.toe);
}

inline RTRBOOL RTRTimerCmd::operator<=(RTRTimerCmd& other) const
{
	return (toe <= other.toe);
}

inline RTRBOOL RTRTimerCmd::operator>(RTRTimerCmd& other) const
{
	return (toe > other.toe);
}

inline RTRBOOL RTRTimerCmd::operator>=(RTRTimerCmd& other) const
{
	return (toe >= other.toe);
}

inline const RTRTimeInterval& RTRTimerCmd::timeOfEvent() const
{
	return toe;
}

inline RTRTimeInterval& RTRTimerCmd::eventTime()
{
	return toe;
}

inline long RTRTimerCmd::offsetSeconds() const
{
	return offset_seconds;
}

inline short RTRTimerCmd::offsetMilliseconds() const
{
	return offset_milli_seconds;
}

inline void RTRTimerCmd::setTimerOffset(long s, short m)
{
	RTPRECONDITION( (s >= 0) && (m >= 0));
	offset_seconds = s;
	offset_milli_seconds = m;
}

inline RTRBOOL RTRTimerCmd::active() const
{
	return(RTRDLinkTC::isActive());
}

inline void RTRTimerCmd::setNotifier( RTREventNotifier *notifier)
{
	_timerCmd_notifier = notifier;
}

#endif  // _timercmd_h
