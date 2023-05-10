//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/15/98"
// Version: 1.0

#ifndef _rtr_fmact_h
#define _rtr_fmact_h

#ifndef _RDEV_NO_STL_
#include <iostream>
#include <fstream>
#else
#include <stdio.h>
#endif

#include "rtr/ostrmact.h"

// Synopsis:
// #include"rtr/fmact.h
//
// Description:
// Provides a logging mechanism where events can be logged to a file.  
//
// See Also:
// RTRFileConfigMgmtActionCntrl, RTRFileMgmtActionCntrl
// 
// Inherits:
// RTROStreamMgmtAction
//

class RTRFileMgmtAction 
        : public RTROStreamMgmtAction
{
public:
// Constructor
	RTRFileMgmtAction(
			const RTRObjectId& cid,
			const RTRObjectId& id
			);
                // _TAG Constructor

	RTRFileMgmtAction(
			const RTRObjectId& cid,
			const RTRObjectId& id,
			const RTRMgmtEventFilter& filter
			);
		// _TAG Constructor

// Destructor
	~RTRFileMgmtAction();
		// _TAG Destructor

// Attributes
	inline int maxFileSize() const;
		// _TAG01 Attributes

	inline const RTRString& filename() const;
		// _TAG01 Attributes

	inline int isTimeBased();
		// _TAG01 Attributes

// Operations
	void setTimeBased();
		// _TAG07 Operations

	void setMaxSwapFiles(int size);
		// _TAG07 Operations
	int itoa(char buf[],int val);

	void setMaxFileSize(int bytes);
		// _TAG07 Operations

	void setFileName(const RTRString& nm, RTRBOOL truncate=RTRFALSE);
		// _TAG07 Operations

	void setNumFiles(int num);
		// _TAG07 Operations

	void setLogDtMsgTogether(RTRBOOL singleLine);
		// _TAG07 Operations

	void setTimeStampFormat(const RTRString& format, bool PrintuSecs=false);
		// _TAG07 Operations

	void getCurrentTime(struct tm*);
	void getFileNameBasedOnDate(RTRString&);

// Operations -- from RTRMgmtAction
	virtual void processFilteredMgmtEvent(const RTRMgmtEvent& me);
		// _TAG08 Operations -- from RTRMgmtAction

// Utilities
	virtual void backup(RTRBOOL);
		// backup and create a new file

protected:
// Data
	int _maxSwapFiles;
	int _swapFileCount;
#ifndef _RDEV_NO_STL_	
	std::fstream _fileStream;
#else
	FILE*		 _fileStream;
#endif
	RTRString _filename;
	RTRString _filenameStr;
	int _maxSize;
	int _numFiles;
	int _numDigits;
	int _timeBased:1;
	int _fileCnt;
	RTRString _compName;

// Don't implement
	RTRFileMgmtAction(const RTRFileMgmtAction&);
	RTRFileMgmtAction& operator=(const RTRFileMgmtAction&);
};

inline
int RTRFileMgmtAction::maxFileSize() const
{
	return _maxSize;
}

int RTRFileMgmtAction::isTimeBased() 
{
	return _timeBased;
}

inline
const RTRString& RTRFileMgmtAction::filename() const
{
	return _filename;
}

#endif
