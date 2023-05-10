//
//|---------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//                 John Arvanites
//  created:       October 11, 1994
//  version:       1.1
//


#ifndef _RTR_SIGNAL_NOTIFIER
#define _RTR_SIGNAL_NOTIFIER

#include "rtr/rtrsig.h"
#include "rtr/sigclnts.h"
#include "rtr/lnsrctbl.h"


//=================================================================

// Synopsis:
//
// Description:
//
//  This defines the signal notifier.
//   
// See Also:
//

class RTRSignalNotifier
{

public:

// Constructor
	RTRSignalNotifier();
		// _TAG Constructor

// Destructor
	~RTRSignalNotifier();
		// _TAG Destructor

// Add clients to signals.
	void addIOClient(	RTRSigIOClient		*callback);
		// REQUIRE: canAddIOClient();
		// _TAG01 Add clients to signals

	void addTERMClient(	RTRSigTERMClient	*callback);
		// REQUIRE: canAddTERMClient();
        // _TAG01 Add clients to signals

	void addINTClient(	RTRSigINTClient		*callback);
		// REQUIRE: canAddINTClient();
        // _TAG01 Add clients to signals

	void addUSR1Client(	RTRSigUSR1Client	*callback);
		// REQUIRE: canAddUSR1Client();
        // _TAG01 Add clients to signals

	void addUSR2Client(	RTRSigUSR2Client	*callback);
		// REQUIRE: canAddUSR2Client();
        // _TAG01 Add clients to signals

	void addPIPEClient(	RTRSigPIPEClient	*callback);
		// REQUIRE: canAddPIPEClient();
        // _TAG01 Add clients to signals

	void addURGClient(	RTRSigURGClient		*callback);
		// REQUIRE: canAddURGClient();
        // _TAG01 Add clients to signals

	void addBUSClient(	RTRSigBUSClient		*callback);
		// REQUIRE: canAddBUSClient();
        // _TAG01 Add clients to signals

	void addSEGVClient(	RTRSigSEGVClient	*callback);
		// REQUIRE: canAddSEGVClient();
        // _TAG01 Add clients to signals

	void addHUPClient(	RTRSigHUPClient	*callback);
		// REQUIRE: canAddHUPClient();
        // _TAG01 Add clients to signals

// Drop clients from signals
	void dropIOClient(	RTRSigIOClient		*callback);
		// _TAG02 Drop clients from signals

	void dropTERMClient(RTRSigTERMClient	*callback);
        // _TAG02 Drop clients from signals

	void dropINTClient(	RTRSigINTClient		*callback);
        // _TAG02 Drop clients from signals

	void dropUSR1Client(RTRSigUSR1Client	*callback);
        // _TAG02 Drop clients from signals

	void dropUSR2Client(RTRSigUSR2Client	*callback);
        // _TAG02 Drop clients from signals

	void dropPIPEClient(RTRSigPIPEClient	*callback);
        // _TAG02 Drop clients from signals

	void dropURGClient(	RTRSigURGClient		*callback);
        // _TAG02 Drop clients from signals

	void dropBUSClient(	RTRSigBUSClient		*callback);
        // _TAG02 Drop clients from signals

	void dropSEGVClient(RTRSigSEGVClient	*callback);
        // _TAG02 Drop clients from signals

	void dropHUPClient(RTRSigHUPClient	*callback);
        // _TAG02 Drop clients from signals

// Check to see if can become a signal client.
	RTRBOOL canAddIOClient()		{return(RTRTRUE);};
		// _TAG03 Check to see if can become a signal client

	RTRBOOL canAddTERMClient()		{return(RTRTRUE);};
        // _TAG03 Check to see if can become a signal client

	RTRBOOL canAddINTClient()		{return(RTRTRUE);};
        // _TAG03 Check to see if can become a signal client

	RTRBOOL canAddUSR1Client()		{return(RTRTRUE);};
        // _TAG03 Check to see if can become a signal client

	RTRBOOL canAddUSR2Client()		{return(RTRTRUE);};
        // _TAG03 Check to see if can become a signal client

	RTRBOOL canAddPIPEClient()		{return(RTRTRUE);};
        // _TAG03 Check to see if can become a signal client

	RTRBOOL canAddURGClient()		{return(RTRTRUE);};
        // _TAG03 Check to see if can become a signal client

	RTRBOOL canAddBUSClient()		{return(RTRTRUE);};
        // _TAG03 Check to see if can become a signal client

	RTRBOOL canAddSEGVClient()		{return(RTRTRUE);};
        // _TAG03 Check to see if can become a signal client

	RTRBOOL canAddHUPClient()		{return(RTRTRUE);};
        // _TAG03 Check to see if can become a signal client

// Block all signals
	inline void blockAllSignals()
		// REQUIRE: !signalsBlocked()
		// _TAG04 Block all signals
	{
	#ifdef RTR_PROC_BLOCK
		RTPRECONDITION( !signalsBlocked() );
		RTR_PROC_BLOCK(&_full_mask, &_old_mask);
		_signals_blocked = RTRTRUE;
		RTPOSTCONDITION( signalsBlocked() );
	#endif
	};

	inline void unblockAllSignals()
		// REQUIRE: signalsBlocked()
		// _TAG04 Block all signals
	{
	#ifdef RTR_PROC_SETMASK
		RTPRECONDITION( signalsBlocked() );
		_signals_blocked = RTRFALSE;
		RTR_PROC_SETMASK(&_old_mask,0);
		RTPOSTCONDITION( !signalsBlocked() );
	#endif
	};

	inline RTRBOOL signalsBlocked()
		// Are signals currently blocked?
		// _TAG04 Block all signals
	{
		return( _signals_blocked );
	};

// Ignore Signals
	void ignoreIO(	RTRSigIOClient	*callback );
		// ignore signals for `callback'.
		// _TAG05 Ignore Signals

	void acceptIO(	RTRSigIOClient	*callback );
		// accept signals for `callback'.
		// _TAG05 Ignore Signals

// Needed for Windows NT.
	inline RTRBOOL enabledINT()
		// _TAG06 Needed for Windows NT
	{
		return ( _enabledINT ? RTRTRUE : RTRFALSE );
	};

	inline RTRBOOL enabledTERM()
		// _TAG06 Needed for Windows NT
	{
		return ( _enabledTERM ? RTRTRUE : RTRFALSE );
	};

	void causeINT();
		// _TAG06 Needed for Windows NT

	void causeTERM();
		// _TAG06 Needed for Windows NT

protected:

// Data members
#ifdef RTR_SIG_HANDLER
	rtr_sigset	_old_mask;
	rtr_sigset	_full_mask;
#endif

		// Signal clients.
		// For now there is one client per signal.
	RTRLinSrchTbl		_IOlist;
	RTRLinSrchTbl		_TERMlist;
	RTRLinSrchTbl		_INTlist;
	RTRLinSrchTbl		_USR1list;
	RTRLinSrchTbl		_USR2list;
	RTRLinSrchTbl		_PIPElist;
	RTRLinSrchTbl		_URGlist;
	RTRLinSrchTbl		_BUSlist;
	RTRLinSrchTbl		_SEGVlist;
	RTRLinSrchTbl		_HUPlist;

	RTRBOOL				_signals_blocked;

	int		_enabledTERM:1;
	int		_enabledINT:1;


// Static Data members
	static RTRSignalNotifier *_rtrsignals;
		// static attribute to which C callbacks are applied.


// Member functions
// Actual system signal handler functions.
// Static member functions for callbacks from C.
#ifdef RTR_SIG_HANDLER
	static RTR_SIG_HANDLER(IO_function,sig);
	static RTR_SIG_HANDLER(TERM_function,sig);
	static RTR_SIG_HANDLER(INT_function,sig);
	static RTR_SIG_HANDLER(USR1_function,sig);
	static RTR_SIG_HANDLER(USR2_function,sig);
	static RTR_SIG_HANDLER(PIPE_function,sig);
	static RTR_SIG_HANDLER(URG_function,sig);
	static RTR_SIG_HANDLER(BUS_function,sig);
	static RTR_SIG_HANDLER(SEGV_function,sig);
	static RTR_SIG_HANDLER(HUP_function,sig);
#endif


// Initialization
	void setBlockAllMask();


// Enable certain signal usage.
	void enableIO();
	void enableTERM();
	void enableINT();
	void enableUSR1();
	void enableUSR2();
	void enablePIPE();
	void enableURG();
	void enableBUS();
	void enableSEGV();
	void enableHUP();

// Disable certain signal usage.
	void disableIO();
	void disableTERM();
	void disableINT();
	void disableUSR1();
	void disableUSR2();
	void disablePIPE();
	void disableURG();
	void disableBUS();
	void disableSEGV();
	void disableHUP();


private:
};




//=================================================================

// Synopsis:
//
// Description:
//
//  This defines the signal notifier.
//
// See Also:
//

class RTRSignalNotifierInit
{

public:

// Constructor
	RTRSignalNotifierInit();
		// _TAG Constructor

// Destructor
	~RTRSignalNotifierInit();
		// _TAG Destructor

	static RTRSignalNotifier * signalNotifier;


private:

	static unsigned short count;

};


static RTRSignalNotifierInit signalNotifierInit;


#endif
