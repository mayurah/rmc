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

#ifndef __rtrvcustom_h
#define __rtrvcustom_h

#include "rvevmcst.h"
#include "rvevmglu.h"
#include "rtr/rtrnotif.h"
#include "rtr/lnsrctbl.h"


class rtrRvContext
{
public:

// Constructor
	rtrRvContext();

// Destructor
	~rtrRvContext();

	RTREventNotifier	*evm;
	RTRLinSrchTbl		ioTable;

	static int numContexts;

};


class rvTimer :
	public RTRTimerCmd
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


// From RTRTimerCmd
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
		_condition((rvevm_IoEventType)0),
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

#define rvIoEventInfoMax 10


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
	int				_source;

	int				_dispatching:1;
	int				_hadClear:1;
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
