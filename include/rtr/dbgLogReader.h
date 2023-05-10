//
//|---------------------------------------------------------------
//|                Copyright (C) 2000 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60523          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  description:
//


#ifndef __dbgLogReader
#define __dbgLogReader

#ifndef _RDEV_NO_STL_
#include <iostream>
#include <fstream>
#else
#include <stdio.h>
#endif
#include "rtr/dbgLogger.h"
#include "rtr/pointerlist.h"
#include "rtr/lnsrctbl.h"
#include "rtr/gettimeofday.h"


class cBufReadIter;

#ifndef _RDEV_NO_STL_
typedef RTRBOOL (*dbgLogParseFunc)(std::ostream &ostr, char **buf, int *len,
									u_8 flags, u_32 opaque, char *ctime,
									void *closureArg );
#else
typedef RTRBOOL (*dbgLogParseFunc)(FILE*, char **buf, int *len,
									u_8 flags, u_32 opaque, char *ctime,
									void *closureArg );
#endif
class dbgLogReader
{
public:

// Constructor
	dbgLogReader(	const char *filename,
					RTRBOOL dumpTimestamp = RTRTRUE,
					RTRBOOL dumpText = RTRTRUE,
					RTRBOOL dumpGenericHex = RTRTRUE,
					RTRBOOL uSecTimestamps = RTRFALSE,
					const char* timestampFmt= 0);

// Destructor
	~dbgLogReader();

// Operations
	RTRBOOL run();

// Parser Functions
	RTRBOOL addParser( const char *name, dbgLogParseFunc parserFunc, void *closureArg=0 );
		// Add a parser routine to be called for logging types of 'name'.
		// Returns False is that name of id is already registered for.

	RTRBOOL removeParser( const char *name, dbgLogParseFunc parserFunc );
		// Remove the parser routine.

protected:

#ifndef _RDEV_NO_STL_
	std::ifstream	_input;
#else
	FILE			_input;
#endif
	char			*_fileName;
	RTRBOOL			_dumpTimestamp;
	RTRBOOL			_dumpText;
	RTRBOOL			_dumpGenericHex;
	char			*_timestampFmt;
	u_8				_timestampUSecOffset;
	RTRBOOL			_TStampUsecFmtParseFailed;

	char			*_logTypes[RTRDbgLogger::maxLoggingType+1];	
										// Array of log type names indexed
										// by the integer type.

	dbgLogParseFunc	_parseFuncs[RTRDbgLogger::maxLoggingType+1];
										// Array of parse functions.
										// Indexed by logging identifiier.
	void			*_closureArgs[RTRDbgLogger::maxLoggingType+1];
										// The closure arguments for the
										// parser functions.

	rtrPtrList		_logNames;			// A list of log names with unknown id.
	rtrPtrList		_logFunctions;		// The corresponding function for the log
										// name in _logNames.
	rtrPtrList		_closure;			// The corresponding closure for the log
										// name in _logNames.

	RTRLinSrchTbl	_partialMsgs;		// A list of partial messages stored by key.

	u_8				_lastType;


	void readFile();
	RTRBOOL read();
	RTRBOOL readHeader();
	RTRBOOL checkHdr(cBufReadIter &riter);
	void addNewType( u_8 typeId, char * typeName );

#ifndef _RDEV_NO_STL_
	static RTRBOOL textParse(std::ostream &ostr, char **buf, int *len,
								u_8 flags, u_32 opaque, char *ctime,
								void *closureArg);
	static RTRBOOL doHexDump(std::ostream &ostr, char **buf, int *len,
								u_8 flags, u_32 opaque, char *ctime,
								void *closureArg);
#else
	static RTRBOOL textParse(FILE* ostr, char **buf, int *len,
								u_8 flags, u_32 opaque, char *ctime,
								void *closureArg);
	static RTRBOOL doHexDump(FILE* ostr, char **buf, int *len,
								u_8 flags, u_32 opaque, char *ctime,
								void *closureArg);
#endif
};


#endif
