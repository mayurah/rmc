//
//|---------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60523          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  description:
//
//	These files implement a TIB/Classic custom main loop that utilizes an
//	RTREventNotifier for its implementation.
//
//	RESTRICTIONS: Currently only handle one context due to the
//	face that timer events are tied to the global main loop. Also,
//	newNotifier is private and cannot be accessed.
//
//

#ifndef __tibevn_h
#define __tibevn_h

#include "TibCstEvm.h"
#include "rtr/rtrnotif.h"
#include "rtr/sfevnotf.h"
#include "rtr/lnsrctbl.h"

#include "rtr/rtrdefs.h"
#include "rtr/timercmd.h"
#include "rtr/ldlinkl.h"
#include "rtr/tmintvl.h"


class TIBTimerGroup;

class TIBTimerGroupMgr : 
		public RTRUnsafeControlThread,
		private RTRTimerCmd
{
	friend class TIBTimerCmd;
private:

	unsigned long		curr_slot;	// Current slot, about to run
	unsigned long		num_slots;	// # slots in the group
	unsigned long		max_interval;	// maximum interval
	unsigned long		gran;		// granule size
	TIBTimerGroup		*slots;		// ptr to array of slots
	TIBTimerGroup		*_lpTimers;
	int					_priority;
	RTRTimeInterval		tick;
	RTRTimeInterval		sysTime;
	RTRTimeInterval		expCallbackTime;

	int computeSlots(long s, short m);
	TIBTimerGroup *getTimerGroup(long s, short m);
	void processTimerEvent();	

// Object Assignment ** DON'T DEFINE THIS!
	TIBTimerGroupMgr& operator=( TIBTimerGroupMgr& rhs);

// Copy ructor ** DON'T DEFINE THIS!
	TIBTimerGroupMgr(TIBTimerGroupMgr& other);

public:
	// Constructor
	TIBTimerGroupMgr(long maximum_interval, long granule, int priority = 0);

	// Destructor
	~TIBTimerGroupMgr();

// From RTRUnsafeControlThread
	RTRBOOL processUnsafeControlThread();
};



class TIBTimerCmd : public RTRDLink0
{
	friend class TIBTimerGroup;
protected:

// Object Assignment ** DON'T DEFINE THIS!
	TIBTimerCmd& operator=( TIBTimerCmd& rhs);

// Copy constructor ** DON'T DEFINE THIS!
	TIBTimerCmd(TIBTimerCmd& other);

	TIBTimerGroupMgr *groupMgr;
	TIBTimerGroup	*group;
	long offset_seconds;
	short offset_milli_seconds;

protected:
	// Event processing:
	// Called (indirectly, perhaps) by the notifier
	// and invokes processTimerEvent().
	// This should not be invoked by application code.
	void execute();

public:

	// Constructor
	TIBTimerCmd();

	// Destructor
	~TIBTimerCmd(void);
 
	// Attributes:
	// Relative time of this event in seconds.
	long offsetSeconds() ;

	// Relative offset milliseconds.
	short offsetMilliseconds() ;

	// State
	// Is cmd() current installed in the notifier?
	RTRBOOL active() ;

	// Operations
	// Set timer offset to s seconds and m milliseconds.
	void setTimerOffset(long s, short m);

	void activate();
		// REQUIRE : ! active()
		// ENSURE : active()

	void deactivate();
		// REQUIRE : active()
		// ENSURE : !active()

	// Event processing:
	// Called (indirectly, perhaps) by the notifier
	// and invokes processTimerEvent().
	// Redefined by descendant classes to provide specific
	// behavior for this timer.
	virtual void processTimerEvent() = 0;
};

//===================================================================
// This class is used to hold timer events that are associated with
// the same Group and which are to go off within the same "granule"
// of time.

class TIBTimerGroup
{
	friend class TIBTimerGroupMgr;
	friend class TIBTimerCmd;
private:
	RTRLiteDLinkList<TIBTimerCmd, RTRDLink0>	list;

	void	addClient(TIBTimerCmd *cmd);
	void	dropClient(TIBTimerCmd *cmd);
	void	process(); // Run the cmds in the slot
	void	process(int maxTimers); // Run the cmds in the slot
	void	append(TIBTimerGroup &timerGroup);
};

inline
void TIBTimerGroup::addClient(TIBTimerCmd *cmd)
{
	//SRCASSERT(!list.has(cmd));
	list.putLast(cmd);
}

inline
void TIBTimerGroup::dropClient(TIBTimerCmd *cmd)
{
	//SRCASSERT(list.has(cmd));
	list.remove(cmd);
}


class rtrTibContext
{
public:

// Constructor
	rtrTibContext();

// Destructor
	~rtrTibContext();

	RTREventNotifier	*evm;
	RTRLinSrchTbl		ioTable;
	TIBTimerGroupMgr	*_timerCmdNotifier;
	TIBTimerGroupMgr	*_timerNotif0;
	TIBTimerGroupMgr	*_timerNotif10;
	TIBTimerGroupMgr	*_timerNotif100;
	TIBTimerGroupMgr	*_timerNotif10000;
	//================================================
	// SAI [ 1 Dec 2006 ]
	//================================================
	TIBTimerGroupMgr	*_timerNotif200000;
	//================================================
	int loopDepth;

	static int numContexts;

};


class tibTimer :
	public TIBTimerCmd
{
public:
// Constructor
	tibTimer();

// Destructor
	~tibTimer();

// Operations
	void setTimer( 
		rtrTibContext	*cntxt,
		unsigned long	interval,
		TibTimerProc	proc,
		void			*closureArg,
		RTRBOOL			repeating=RTRFALSE);

	void resetTimer( unsigned long interval );

	void cancelTimer();

protected:

	rtrTibContext	*_cntxt;
	TibTimerProc	_proc;
	void			*_closureArg;
	int				_repeating:1;
	int				_dispatching:1;
	int				_resetting:1;
	int				_cancelled:1;


// From TIBTimerCmd
	virtual void processTimerEvent();

};


class tibIoEvent;


class tibIoEventId
{
public:
	inline tibIoEventId() : idx(-1), ioEvent(0) {};

	int			idx;
	tibIoEvent	*ioEvent;
};

class tibIoEventInfo
{
public:
	inline tibIoEventInfo() :
		_proc(0),
		_condition(TIBEVENT_NONE),
		_closureArg(0),
		_inUse(0),
		_id()
	{
	};

	TibIoProc		_proc;
	TibEventMask	_condition;
	void*				_closureArg;
	tibIoEventId			_id;
	short				_inUse:1;
};

#define tibIoEventInfoMax 3


class tibIoEvent :
	public RTRIOClient
{
public:
// Constructor
	tibIoEvent();

// Destructor
	~tibIoEvent();

// Operations
	void initIoEvent( rtrTibContext *cntxt, /*TibEventSource*/ int source );

	tibIoEventId * settibIoEvent( 
		TibEventMask	condition,
		TibIoProc		proc,
		void				*closureArg );

	EvmReturns clearIoEvent( tibIoEventId * id );

	void recheckClients();

protected:

	rtrTibContext	*_cntxt;
	tibIoEventInfo	_infoArray[tibIoEventInfoMax];
	int				_tibIoEventInfoCnt;
	int				_source;

	int				_dispatching:1;
	int				_recheckClients:1;
	int				_isReadClient:1;
	int				_isWriteClient:1;
	int				_isExceptClient:1;

// Protected
	void setUpClients(TibEventMask condition);

// From RTRIOClient
	virtual void processIORead(int);
	virtual void processIOWrite(int);
	virtual void processIOException(int);

};


#endif
