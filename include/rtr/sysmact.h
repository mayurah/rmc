//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/15/98"
// Version: 1.0

#ifndef _rtr_sysmact_h
#define _rtr_sysmact_h

#ifdef _WIN32
#include <windows.h>
#endif

#include "rtr/mgmtact.h"

// The Windows NT implementation of RTRSystemMgmtAction uses this
// log message number for all RTRMgmtEvents.  If the application needs
// to use this log message number for its own use, the log message
// number can be changed by setting RTRSystemMgmtAction::_messageNumber.
#define EVMSG_RTRLOGGER 50

// Message numbers for categories (Windows NT-only).  The
// RTRSystemMgmtAction uses the EventLog category field to display the
// severity of the RTRMgmtEvent.  Windows NT requires that the category
// messages start at message number 1.  If the application needs to use
// message numbers 1 through 8 for its own use, the RTRSystemMgmtAction's
// use of categories can be disabled by setting the static variable
// RTRSystemMgmtAction::_useCategory to RTRFALSE.
#define EVCAT_DEBUG	1
#define EVCAT_INFO	2
#define EVCAT_NOTICE	3
#define EVCAT_WARNING	4
#define EVCAT_ERROR	5
#define EVCAT_CRITICAL	6
#define EVCAT_ALERT	7
#define EVCAT_EMERGENCY	8


// Synopsis:
// #include "rtr/sysmact.h"
//
// Description:
// RTRSystemMgmtAction provides a logging mechanism where events can be
// logged to the operating system logging facility.
// For Unix, this logs to syslog().
// For Windows NT, this logs to the application EventLog facility.
//
// See Also:
// RTRSystemConfigMgmtActionCntrl, RTRSystemMgmtActionCntrl
//
// Inherits:
// RTRMgmtAction
//

class RTRSystemMgmtAction
        : public RTRMgmtAction
{
public:
// Constructor
	RTRSystemMgmtAction(
			const RTRObjectId& cid,
			const RTRObjectId& id
			);
                // _TAG Constructor

	RTRSystemMgmtAction(
			const RTRObjectId& cid,
			const RTRObjectId& id,
			const RTRMgmtEventFilter& filter
			);
		// _TAG Constructor

// Destructor
	~RTRSystemMgmtAction();
		// _TAG Destructor

// Operations
	void setLog(const RTRString& appName);
		// _TAG07 Operations

// Operations -- from RTRMgmtAction
	virtual void processFilteredMgmtEvent(const RTRMgmtEvent& me);
		// _TAG08 Operations -- from RTRMgmtAction

// Static Data
	static int messageNumber;
	static RTRBOOL useCategory;
		// _TAG Static Data

protected:
// Utilities
	void setTextSize(int size);
	const char *formatMgmtEvent(const RTRMgmtEvent& me);

// Data
	char *_text;
	int _size;
#ifdef _WIN32
	HANDLE _hEventSource;
#endif

// Don't implement
	RTRSystemMgmtAction(const RTRSystemMgmtAction&);
	RTRSystemMgmtAction& operator=(const RTRSystemMgmtAction&);
};

#endif
