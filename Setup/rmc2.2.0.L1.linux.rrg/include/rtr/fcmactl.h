//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/16/98"
// Version: 1.0

#ifndef _rtr_fcmactl_h
#define _rtr_fcmactl_h

#include "rtr/cmactl.h"
#include "rtr/objid.h"
#include "rtr/config.h"
#include "rtr/fmact.h"


// Synopsis:
// #include "rtr/fcmactl.h"
//
// Description:
// RTRFileConfigMgmtActionCntrl creates an instance of RTRFileMgmtAction
// which is configured based on entries found in the configuration
// database.  It provides several different customizations
// which can be changed via the configuration database.
//
// Class identifier: "LogAction.FileAction";
//
// \verbatim
// max_bytes:       integer - the file size at which the file will be saved
//                  to a ".old" version.
//
// truncate:        boolean - This variable determines whether an existing log
//                  file will be appended (default) to or cleared out before
//                  logging begins. If the truncate variable is set to "True",
//                  it will be completely cleared out before logging.
//
// file:            string - The pathname of the log file.
//
// flush:           boolean - enable(default)/disable the flushing of output
//                  on each event.
// \endverbatim
//
// See Also:
// RTRFileMgmtActionCntrl, RTRFileMgmtAction
//
// Inherits:
// RTRConfigMgmtActionCntrl
//

class RTRFileConfigMgmtActionCntrl
	: public RTRConfigMgmtActionCntrl
{
public:
// Constructor
	RTRFileConfigMgmtActionCntrl(
			const RTRObjectId& context,
			const RTRString& nm
			);
		// _TAG Constructor

// Destructor
	~RTRFileConfigMgmtActionCntrl();
		// _TAG Destructor

// Attributes
	RTRMgmtAction& action() const;
		// _TAG01 Attributes

	void displayConfiguration() const;
		// print configuration to stdout
		// (kept for compatibility).
		// _TAG01 Attributes

//For time based rollover of log files
	void rollover();
	double calcTimeUntilMidnight();
	int isTimeBased();

// Static
	static RTRString maxSwapFilesVarName;
	static RTRString defaultMaxSwapFiles;
	static RTRString logFileVarName;
	static RTRString baseFileVarName;
	static RTRString filePathVarName;
	static RTRString maxBytesVarName;
	static RTRString fileSizeVarName;
	static RTRString numFileVarName;
	static RTRString truncateVarName;
	static RTRString flushVarName;
	static RTRString dtMsgLoggingVarName;
	static RTRString dateTimeformatVarName;
	static RTRString uSecTimeStampsVarName;
	static RTRString defaultLogFile;
	static RTRString defaultMaxBytes;
	static RTRString defaultTruncate;
	static RTRString defaultFlush;
	static RTRString defaultDtMsgLogging;
	static RTRString defaultDateTimeFormat;
	static RTRString defaultuSecTimeStamps;

	static RTRObjectId _classId;

protected:
// Utilities
	virtual void extractConfiguration();

// Data
	RTRFileMgmtAction _action;

private:
// Do not implement
	RTRFileConfigMgmtActionCntrl(const RTRFileConfigMgmtActionCntrl&);
	RTRFileConfigMgmtActionCntrl& operator=(const RTRFileConfigMgmtActionCntrl&);
};

#endif
