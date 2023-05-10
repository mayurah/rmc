//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  version:       1.0
 

#ifndef __envptype_h
#define __envptype_h

class RTRIOClient;
class RTREvNotPollThrd;
class RTRThrdSafeControlThread;
#include "rtr/rtrmutex.h"
#include "rtr/timercmd.h"


class RTREvtNotImplEvent :
	public RTRDLink0
{
public:
	enum EventType { IOEvent, TimerEvent, ThrdEvent };
	RTREvtNotImplEvent( EventType ty ) : type(ty) {};
	EventType   type;
};


class RTREvNotTimerEntry :
	public RTREvtNotImplEvent,
	public RTRDLink1
{
public:
	RTREvNotTimerEntry() :
		RTREvtNotImplEvent(RTREvtNotImplEvent::TimerEvent),
		cmd(0)
	{
	};

// Comparison
	inline RTRBOOL operator==(RTREvNotTimerEntry& other) const
		// _TAG02 Comparison
	{
		return((seconds == other.seconds) &&
				(milliseconds == other.milliseconds));
	};
 
	inline RTRBOOL operator<(RTREvNotTimerEntry& other) const
		// _TAG02 Comparison
	{
		return( (seconds < other.seconds) ||
				((seconds == other.seconds) &&
				(milliseconds < other.milliseconds)));
	};
 
	inline RTRBOOL operator<=(RTREvNotTimerEntry& other) const
		// _TAG02 Comparison
	{
		return( (seconds < other.seconds) ||
				((seconds == other.seconds) &&
				(milliseconds <= other.milliseconds)));
	};
 
	inline RTRBOOL operator>(RTREvNotTimerEntry& other) const
		// _TAG02 Comparison
	{
		return( (seconds > other.seconds) ||
				((seconds == other.seconds) &&
				(milliseconds > other.milliseconds)));
	};
 
	inline RTRBOOL operator>=(RTREvNotTimerEntry& other) const
		// _TAG02 Comparison
	{
		return( (seconds > other.seconds) ||
				((seconds == other.seconds) &&
				(milliseconds >= other.milliseconds)));
	};


// Members
	RTRTimerCmd	*cmd;
	long		seconds;
	long		milliseconds;

};

class RTREvNotThreadEntry :
	public RTREvtNotImplEvent
{
public:
	RTREvNotThreadEntry() :
		RTREvtNotImplEvent(RTREvtNotImplEvent::ThrdEvent),
		controlThread(0)
	{
	};

	RTRThrdSafeControlThread *controlThread;
};


class RTREvNotPollEntry :
	public RTREvtNotImplEvent,
	public RTRDLink1
{
public:
	RTREvNotPollEntry(int filed) :
		RTREvtNotImplEvent(RTREvtNotImplEvent::IOEvent),
		fd(filed),
		index(-1),
		readClient(0),
		wrtClient(0),
		exceptClient(0),
		notification(noNot),
		pollThread(0),
		pendEvents(pendNone)
	{
	};

	int					fd;
	int					index;
	RTRIOClient			*readClient;
	RTRIOClient			*wrtClient;
	RTRIOClient			*exceptClient;
	RTREvNotPollThrd	*pollThread;

	enum {	noNot=0x00,
			readNot=0x01,
			writeNot=0x02,
			exceptNot=0x04,
			lastEvent=0x08 };
	short	notification;

	enum {	pendNone=0x00,
			pendingAdd=0x01,
			pendingChange=0x02,
			pendingDelete=0x04 };
	short	pendEvents;


	inline RTRBOOL isPendingAddition() {return(pendEvents & pendingAdd);};
	inline RTRBOOL isPendingChange() {return(pendEvents & pendingChange);};
	inline RTRBOOL isPendingDelete() {return(pendEvents & pendingDelete);};

	inline void setPendingAddition() {pendEvents |= pendingAdd;};
	inline void setPendingChange() {pendEvents |= pendingChange;};
	inline void setPendingDelete() {pendEvents = pendingDelete;};

	inline void clearPendingAction() {pendEvents = pendNone; };

};


#endif
