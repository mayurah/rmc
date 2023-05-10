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
//	These files implement a RV custom main loop that utilizes an
//	RTREventNotifier for its implementation.
//
//	RESTRICTIONS: Currently only handle one context due to the
//	face that timer events are tied to the global main loop. Also,
//	newNotifier is private and cannot be accessed.
//
//

#ifndef __rvevn_h
#define __rvevn_h

#include "rvevmcst.h"
#include "rvevmglu.h"
#include "rtr/rtrnotif.h"
#include "rtr/sfevnotf.h"
#include "rtr/lnsrctbl.h"

#include "rtr/rtrdefs.h"
#include "rtr/timercmd.h"
#include "rtr/ldlinkl.h"
#include "rtr/tmintvl.h"


class rvTimerGroup;

class rvTimerGroupMgr : 
		public RTRUnsafeControlThread,
		private RTRTimerCmd
{
	friend class rvTimerCmd;
private:

	unsigned long		curr_slot;	// Current slot, about to run
	unsigned long		num_slots;	// # slots in the group
	unsigned long		max_interval;	// maximum interval
	unsigned long		gran;		// granule size
	rvTimerGroup		*slots;		// ptr to array of slots
	rvTimerGroup		*_lpTimers;
	int					_priority;
	RTRTimeInterval		tick;
	RTRTimeInterval		sysTime;
	RTRTimeInterval		expCallbackTime;

	int computeSlots(long s, short m);
	rvTimerGroup *getTimerGroup(long s, short m);
	void processTimerEvent();	

// Object Assignment ** DON'T DEFINE THIS!
	rvTimerGroupMgr& operator=( rvTimerGroupMgr& rhs);

// Copy ructor ** DON'T DEFINE THIS!
	rvTimerGroupMgr(rvTimerGroupMgr& other);

public:
	// Constructor
	rvTimerGroupMgr(long maximum_interval, long granule, int priority = 0);

	// Destructor
	~rvTimerGroupMgr();

// From RTRUnsafeControlThread
	RTRBOOL processUnsafeControlThread();
};



class rvTimerCmd : public RTRDLink0
{
	friend class rvTimerGroup;
protected:

// Object Assignment ** DON'T DEFINE THIS!
	rvTimerCmd& operator=( rvTimerCmd& rhs);

// Copy constructor ** DON'T DEFINE THIS!
	rvTimerCmd(rvTimerCmd& other);

	rvTimerGroupMgr *groupMgr;
	rvTimerGroup	*group;
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
	rvTimerCmd();

	// Destructor
	~rvTimerCmd(void);
 
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

class rvTimerGroup
{
	friend class rvTimerGroupMgr;
	friend class rvTimerCmd;
private:
	RTRLiteDLinkList<rvTimerCmd, RTRDLink0>	list;

	void	addClient(rvTimerCmd *cmd);
	void	dropClient(rvTimerCmd *cmd);
	void	process(); // Run the cmds in the slot
	void	process(int maxTimers); // Run the cmds in the slot
	void	append(rvTimerGroup &timerGroup);
};

inline
void rvTimerGroup::addClient(rvTimerCmd *cmd)
{
	//SRCASSERT(!list.has(cmd));
	list.putLast(cmd);
}

inline
void rvTimerGroup::dropClient(rvTimerCmd *cmd)
{
	//SRCASSERT(list.has(cmd));
	list.remove(cmd);
}


class rtrRvContext
{
public:

// Constructor
	rtrRvContext();

// Destructor
	~rtrRvContext();

	RTREventNotifier	*evm;
	RTRLinSrchTbl		ioTable;
	rvTimerGroupMgr	*_timerCmdNotifier;
	rvTimerGroupMgr	*_timerNotif10;
	rvTimerGroupMgr	*_timerNotif100;
	rvTimerGroupMgr	*_timerNotif10000;
	int loopDepth;

	static int numContexts;

};


class rvTimer :
	public rvTimerCmd
{
public:
// Constructor
	rvTimer();

// Destructor
	~rvTimer();

// Operations
	void setTimer( 
		rtrRvContext	*cntxt,
		unsigned long	interval,
		_rvevmCallback	proc,
		void			*closureArg,
		RTRBOOL			repeating=RTRFALSE);

	void resetTimer( unsigned long interval );

	void cancelTimer();

protected:

	rtrRvContext	*_cntxt;
	_rvevmCallback	_proc;
	void			*_closureArg;
	int				_repeating:1;
	int				_dispatching:1;
	int				_resetting:1;
	int				_cancelled:1;


// From rvTimerCmd
	virtual void processTimerEvent();

};


class rvIoEvent;


class rvIoEventId
{
public:
	inline rvIoEventId() : idx(-1), ioEvent(0) {};

	int			idx;
	rvIoEvent	*ioEvent;
};

class rvIoEventInfo
{
public:
	inline rvIoEventInfo() :
		_proc(0),
		_closureArg(0),
		_inUse(0),
		_id()
	{
	};

	_rvevmCallback		_proc;
	rvevm_IoEventType	_condition;
	void*				_closureArg;
	rvIoEventId			_id;
	short				_inUse:1;
};

#define rvIoEventInfoMax 3


class rvIoEvent :
	public RTRIOClient
{
public:
// Constructor
	rvIoEvent();

// Destructor
	~rvIoEvent();

// Operations
	void initIoEvent( rtrRvContext *cntxt, int source );

	rvIoEventId * setrvIoEvent( 
		rvevm_IoEventType	condition,
		_rvevmCallback		proc,
		void				*closureArg );

	rvevm_Returns clearIoEvent( rvIoEventId * id );

	void recheckClients();

protected:

	rtrRvContext	*_cntxt;
	rvIoEventInfo	_infoArray[rvIoEventInfoMax];
	int				_rvIoEventInfoCnt;
	int				_source;

	int				_dispatching:1;
	int				_recheckClients:1;
	int				_isReadClient:1;
	int				_isWriteClient:1;
	int				_isExceptClient:1;

// Protected
	void setUpClients(rvevm_IoEventType condition);

// From RTRIOClient
	virtual void processIORead(int);
	virtual void processIOWrite(int);
	virtual void processIOException(int);

};


#endif
