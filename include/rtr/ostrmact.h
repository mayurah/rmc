//|---------------------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "1/15/98"
// Version: 1.0

#ifndef _rtr_ostrmact_h
#define _rtr_ostrmact_h

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

#include "rtr/mgmtact.h"

// Synopsis:
// #include "rtr/ostrmact.h"
//
// Description:
// RTROStreamMgmtAction is an RTRMgmtAction which formats and sends matching
// RTRMgmtEvent's to an ostream.
//
// See Also:
// RTRFileMgmtAction, RTRStdErrMgmtActionCntrl, RTRConfigStdErrMgmtActionCntrl
//
// Inherits:
// RTRMgmtAction

class RTROStreamMgmtAction
        : public RTRMgmtAction
{
public:
// Constructor
	RTROStreamMgmtAction(
			const RTRObjectId& cid,
			const RTRObjectId& id
			);
                // _TAG Constructor

	RTROStreamMgmtAction(
			const RTRObjectId& cid,
			const RTRObjectId& id,
			const RTRMgmtEventFilter& filter
			);
		// _TAG Constructor

// Destructor
	~RTROStreamMgmtAction();
		// _TAG Destructor

// Attributes
#ifndef _RDEV_NO_STL_
	inline std::ostream *stream() const;
		// _TAG02 Attributes

// Operations
	void setStream(std::ostream& stream);
		// Sets the ostream.
		// _TAG07 Operations
#else
	inline FILE* stream() const;
		// _TAG02 Attributes

// Operations
	void setStream(FILE* stream);
		// Sets the ostream.
		// _TAG07 Operations
#endif

	RTRString& 	TStampFormat() {return _TStampFormat;}
	RTRBOOL TStampUsecFmtParseFailed() {	return _TStampUsecFmtParseFailed;}

	void setFlush(RTRBOOL doFlush);
		// Should the action flush the ostream after each
		// RTRMgmtEvent sent to it.
		// _TAG07 Operations

	void setLogDtMsgTogether(RTRBOOL singleLine);
		// Sets logDtMsgTogether to perform logging of date and message
		// on the same line.

// Operations -- from RTRMgmtAction
	virtual void processFilteredMgmtEvent(const RTRMgmtEvent& me);
		// _TAG08 Operations -- from RTRMgmtAction

protected:
// Utilities
	const RTRString& formatMgmtEvent(const RTRMgmtEvent& me);

	void setTimeStampFormat(const char* format, bool PrintUsecs);
		// Sets the Time Stamp format for logging requirements


// Data
#ifndef _RDEV_NO_STL_
        std::ostream *_stream;
#else
        FILE*		  _stream;
#endif
	RTRBOOL   _doFlush;
	RTRString _output_string;
	RTRBOOL	  _logDtMsgTogether;
	RTRString _TStampFormat;
	RTRBOOL   _TStampUsecFmtParseFailed;
	u_8       _TStampUSecOffset; 		   // for use in printing uSec timestamps.

// Don't implement
	RTROStreamMgmtAction(const RTROStreamMgmtAction&);
	RTROStreamMgmtAction& operator=(const RTROStreamMgmtAction&);
};

#ifndef _RDEV_NO_STL_
inline
std::ostream *RTROStreamMgmtAction::stream() const
{
	return _stream;
}
#else
inline
FILE* RTROStreamMgmtAction::stream() const
{
	return _stream;
}
#endif

#endif
