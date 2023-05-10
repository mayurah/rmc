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
//	This class provides fast and generic logging capabilities
//	for programmer level debugging on applications. Many different
//	logging types may be logged that can be parsed by a parsing program.
//	The default logging types are text and binary data.
//	Components extend the logging types by registering a logging
//	type and then utilizing this type when logging the event.
//	Another program can then be compiled that understands these new
//	logging events, along with the previous ones, that allows
//	postprocessing of the information.
//

#ifndef __RTRDbgLogger
#define __RTRDbgLogger

#ifndef _RDEV_NO_STL_
#include <fstream>
#else
#include <stdio.h>
#endif
#include "rtr/rtrdefs.h"
#include "rtr/eli_net.h"

#define MAX_FILENAME_LENGTH 40

class RTRDbgLogger;
class RTRPlatMutex;


	// This class provides access to a global debug logger class.
	// This is used when a single class is shared across an application.
	// This should be initialized and cleared in the main loop of
	// the program. Multilple calls will fail.
	// This class is not protected by a mutex. It is the programmers
	// responsability to make sure the setDebugLogger is called
	// before anybody needs it and that clearDebugLogger is called
	// when everybody is done with it.
class gblDbgLogger
{
public:

	static RTRDbgLogger *debugLogger;
	static unsigned long setDebugLogger( RTRDbgLogger& );
	static RTRBOOL clearDebugLogger( unsigned long key );

protected:

	static unsigned long	_key;
		// Used to make sure the user that created the
		// global logger is the one that deletes it.
};



	// This class actually represents the logger. By default
	// the class is thread safe. The constructor option makeThreadSafe
	// can be turned of is thread safety is not needed.
class RTRDbgLogger
{
public:

// Constructor
	RTRDbgLogger(const char * fileNameBase, RTRBOOL makeThreadSafe = RTRTRUE);

// Destructor
	~RTRDbgLogger();

// Attributes
	RTRBOOL enabled();

// Configuration
	enum configVars {
		numberOfFiles = 1,		// Max number of files created (default 10).
		fileSize = 2,			// Max file size (default 1000000).
		flushAfterWrite = 3,	// Flush after each write (default RTRFALSE).
		appendToFile = 4,		// Append to existing files (default RTRTRUE).
		fileName = 5			// Base filename (default from constructor)
	};

	RTRBOOL configure( configVars var, int value );
	RTRBOOL configure( configVars var, const char * value );
		// Configuration

// Logging Types
	int addType( const char *typeName );
		// Add a new logging type.
		// Returns the logTypeIdentifier if success.
		// Example: this->addType("sipc"); For adding a logging type for sipc.
		// If fails returns -1.

// Operations
	void enable();
		// Enable the debug logger for a client.
		// This add a reference the the output file.
		// Each enable should be followed by a disable
		// if the file is to be closed properly.

	void disable();
		// Disable the debug logger for a client.
		// Drop a reference from the logger.

	void flushData();
		// Flush data

	enum HdrFlags {
		MoreData    = 0x01,		// The next event is associated with this one.
		DataSent    = 0x02,		// This event is data being sent.
		DataRcvd    = 0x04,		// This event is data being received.
		EndMoreData = 0x08,		// The end of the data. Only used with MoreData.
		MicrosecTS	= 0x10		// Include Microseconds in log data
								// For single log events, no flags are needed.
	};

	// The following describes the MoreData and EndMoreData flags.
	// for the logging calls.
	//
	// If singular event don't need MoreData or EndMoreData.
	// this->textLen( "The only line", 13, 3 );
	//
	// If multiple events logged with seperate calls then all calls
	// need MoreData flags, except the last call which needs the
	// EndMoreData flag. These operations are thread safe if
	// thread safety is enabled (log the thread id with the events
	// and use this information when parsing). When using more data
	// must use the same logging event type.
	//
	// this->textLen( "First", 5, 0, RTRDbgLogger::MoreData )
	// this->textLen( "Second", 6, 0, RTRDbgLogger::MoreData )
	// this->textLen( "Last", 4, 0, RTRDbgLogger::EndMoreData )
	//

// Information
	void textLen( const char *, u_16 len, u_32 opaque, u_8 headerFlags = 0 );
		// Log the textual event with length 'len' and opaque value.

	void text( const char *, u_32 opaque, u_8 headerFlags = 0 );
		// Log the textual event, use strlen() for length, and opaque value.

	void binary( const char *, u_16 len, u_32 opaque, u_8 headerFlags = 0 );
		// Log the binary event with length 'len' and opaque value.

	void generic( int logTypeId, const char *, u_16 len, u_32 opaque, u_8 headerFlags = 0 );
		// Log the generic event logTypeId with length 'len' and opaque value.

// Version
	static const u_32 DbgVersion;

// Message Types
	static const u_8 DbgHeader;
	static const u_8 DbgNewType;
	static const u_8 DbgText;
	static const u_8 DbgBinary;
	static const u_8 DbgFirstFreeId;

// Logging Types
	static const int maxLogType;
	enum {
		maxLoggingType = 255
	};

protected:

#ifndef _RDEV_NO_STL_
	std::ofstream _outStream;
#else
	FILE		  _outStream;
#endif
	char		*_baseName;
	int			_baseNameLen;
	char		*_fileName;

	int			_clients;
	int 		_numFiles;
	int			_numDigits;	// number of ASCII digits necessary for _numFiles
	int			_fileSize;
	int			_fileNumber;

	int			_enabled:1;
	int			_appendToFile:1;
	int			_flush_after_write:1;
	int			_errorLogged:1;
	char		*_logTypes[256];
	RTRPlatMutex	*_mutex;

	void		makeFileName();

	RTRBOOL	openLog( RTRBOOL append );
		// Open the debugging file

	void	closeLog();
		// Close the debugging file

	void	checkFile();
		// Check to see if the file is full. 

	void	writeFileHdr();
		// Write out the file header.

	void 	writeNewType(u_8 type, const char *name, RTRBOOL flush);
		// Write a new log type information to the file.
};

#endif
