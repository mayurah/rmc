//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "2/2/98"
// Version: 1.0

#ifndef _rtr_sighndlr_h
#define _rtr_sighndlr_h

#include "rtr/sigclnts.h"

// Synopsis:
// #include "rtr/sighndlr.h"
//
// Description:
// RTRTermSignalHandler is a utility class which traps
// the TERM, INT and HUP signals.  The notifier is disabled
// when a TERM or INT signal is received.  The HUP signal
// is ignored.
//
// See Also:
// RTRSigBUSClient, RTRSigIOClient, RTRSigPIPEClient,
// RTRSigSEGVClient, RTRSigURGClient, RTRSigUSR1Client,
// RTRSigUSR2Client
//
// Inherits:
// RTRSigTERMClient, RTRSigINTClient, RTRSigHUPClient
//

class RTRTermSignalHandler : 
	public RTRSigTERMClient,
	public RTRSigINTClient,
	public RTRSigHUPClient
{
public:
// Constructor
	RTRTermSignalHandler();
		// _TAG Constructor

// Destructor
	~RTRTermSignalHandler();
		// _TAG Destructor

// Event processing
	virtual void processSigTERM();
		// Catches the TERM signal and disables the notifier.
		// _TAG01 Event processing -- from RTRSigTERMClient

	virtual void processSigINT();
		// Catches the INT signal and disables the notifier.
		// _TAG01 Event processing -- from RTRSigINTClient

	virtual void processSigHUP();
		// Catches the HUP signal and ignores it.
		// _TAG01 Event processing -- from RTRSigHUPClient

// Static methods
	static RTRTermSignalHandler *instance();
		// Static methods

protected:
// static data
	static RTRTermSignalHandler *_instance;

private:
	// Do not define
	RTRTermSignalHandler(const RTRTermSignalHandler&);
	RTRTermSignalHandler& operator=(const RTRTermSignalHandler&);
};

#endif
