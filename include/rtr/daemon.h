//
//|---------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60523          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:		Kevin Nicodemus
//  created:	December 8, 1997
//  version:    1.0
//

#ifndef __rtr_daemon_h
#define __rtr_daemon_h


#include "rtr/rtrdefs.h"


class RTRDaemonData;		// Hide implementantion data types

#define RTR_DAEMON_USER_CTRL 128	// Windows NT-only 
	// Any command received from the Windows NT Service Control Manager
	// that is above or equal to this value will result in a call to
	// onUserControl().

enum RTRDaemonReturnValue {	RTRDAEMON_SUCCESS,		// Init succeded
							RTRDAEMON_FAILURE,		// Init failed with error
							RTRDAEMON_EXIT };		// Init failed, no error
	// This return value was created to differentiate between:
	//    1. initialization incomplete due to error == RTRDAEMON_FAILURE
	//		 (e.g. could not find config file).
	//	  2. initialization incomplete, no error == RTRDAEMON_EXIT
	//		 (e.g. user specifyied -h option to print usage string).

enum RTRDaemonLogSeverity {	RTRDAEMON_SEV_INFO,		// Info
							RTRDAEMON_SEV_DEBUG,	// Debug
							RTRDAEMON_SEV_WARNING,	// Warning
							RTRDAEMON_SEV_ERROR };	// Error

enum RTRDaemonEventId {	RTRDAEMON_EVENT_NONE,
						RTRDAEMON_EVENT_INITFAILED,	// Initialization failed
						RTRDAEMON_EVENT_STARTED,	// Daemon started
						RTRDAEMON_EVENT_STOPPED,	// Daemon stopped
						RTRDAEMON_EVENT_BADREQUEST};// Bad request to daemon


// Synopsis:
// #include "rtr/daemon.h"
//
// Description:
// This class provides a platform-independent C++ interface for a
// daemon process.
//
// RTRDaemon encapsulates the differences between four different
// types of processes:
//
//    1. Unix process
//    2. Unix daemon process
//    3. Windows NT console application
//    4. Windows NT service application
//
// Using RTRDaemon, an application writer can write platform-independent
// source code that defers the decision to run as a daemon (service, under
// Windows NT) to run-time.
//
// A Windows NT service application has a radically different startup and
// shutdown than a Unix process or a Windows NT console application.  The
// organization of the RTRDaemon class is therefore dictated by the startup
// and shutdown procedures for Windows NT service applications.
//
// Background:
// Unix and Windows NT both provide a method for running applications in
// the background that doesn't require a user to log in.
//
// Under Unix, a "daemon" process provides this functionality.  A daemon
// process is very similar to a normal process, except that a daemon process
// (1) can not be a process group leader and (2) has no controlling terminal.
//
// Under Windows NT, a service application provides this functionality.  A
// service application is a specialized console application that is started
// and stopped by the Windows NT Service Control Manager.  The Service Control
// Manager does not provide command-line parameters, service applications
// normally get their parameters from the registry.
//
//
// Converting a normal C++ program to use RTRDaemon:
//
//    1. Create a class (that inherits from RTRDaemon) that will incorporate
//       the functionality in main().
//    2. Override the onInit() virtual function to contain the
//       initialization from main() (_argc and _argv contain the arguments).
//    3. Override the onRun() virtual function to call the "main loop" of
//       the program.
//    4. Create a new main() that instantiates the new daemon class.
//
// For a Windows NT executable:
//
//    5. Create a message file that contains the messages in ntsrvmsg.mc.
//       Compile the message file and link the resulting resource into the
//       executable.  The service message IDs can be adjusted by changing
//       _baseLogMessageNumber.  The logEvent() virtual function can be
//       overridden to log messages differently.
//
//
// WindowsNT Installation:
// A RTRDaemon application retrieves its command-line parameters from a
// space-delimited string in the registry:
//   Key: HKEY_LOCAL_MACHINE
//   Subkey: SYSTEM\CurrentControlSet\Services\<daemonName>\Parameters
//   Variable: CmdLineArgs
// where the <daemonName> is the service name set during installation.
// A RTRDaemon application gets its service name from the Service Control
// Manager at run-time.  This allows a RTRDaemon application to be installed
// as more than one service, each with its own set of command-line parameters.
//
//
// See Also:
//		RTRDaemonInstaller
//

class RTRDaemon 
{
public:


// Constructor(s)
	RTRDaemon(const char* daemonName);
		// A daemon with specified name (name may be changed later).
		// _TAG Constructor

	RTRDaemon(const char* daemonName, int argc, char **argv);
		// Construct RTRDaemon, call setCmdLineArgs() and autoSetDaemon().
		// _TAG Constructor


// Destructor
	virtual ~RTRDaemon();
		// _TAG Destructor


// Initialization
	virtual RTRDaemonReturnValue initialize();
		// Initialize as a daemon.
		// _TAG07 Operations

	virtual int start();
		// Start daemon.  If isDaemon() is true, the process becomes a
		// daemon at this point.  This call returns when the process is
		// ready to exit.  The value returned is the exit code.
		// _TAG07 Operations


// Command-line Arguments
	virtual void setCmdLineArgs(int argc, char **argv);
		// Save command-line arguments.
		// _TAG07 Operations

	virtual void readCmdLineArgsFromRegistry();
		// Read command-line arguments from a space-delimited registry
		// string variable (Windows NT only).
		//   Key: HKEY_LOCAL_MACHINE
		//   Subkey: SYSTEM\CurrentControlSet\Services\<daemonName>\Parameters
		//   Variable: CmdLineArgs
		// _TAG07 Operations

	virtual void resizeArgv( int new_argc );
		// Change the size of the command-line arguments array (_argv).
		// Copy all of the current arguments that will fit.
		// _TAG07 Operations


// Daemon Name
	const char * daemonName();
		// Return the daemon name.
		// _TAG05 Access

	void setDaemonName( const char *name );
		// Set the daemon name.
		// _TAG07 Operations

	RTRBOOL autoSetDaemonName();
		// Set the daemon name from the command-line argument, if present.
		// Returns RTRTRUE if the daemon name was changed.
		// _TAG07 Operations


// Daemon or not to Daemon
	virtual RTRBOOL isDaemon();
		// Is this process a daemon?
		// _TAG05 Access

	virtual void setDaemon();
		// Manually set this process as a daemon process.
		// _TAG07 Operations

	virtual void autoSetDaemon();
		// Automatically determine if this is to be a normal process or a
		// daemon process.
		//   Unix: Run as a normal process if the -nodaemon flag is
		//         specified on the command line.
		//   Windows NT: Run as a normal process if the number of
		//         command-line arguments (including argv[0]) is greater
		//         than one (1).
		// _TAG07 Operations

	RTRBOOL setThreadName( const char *name );
		// Set the daemon process Name.
		// _TAG07 Operations

// Exit Code
	int exitCode();
		// Return exit code.
		// _TAG05 Access

	void setExitCode( int code );
		// Set exit code.
		// _TAG07 Operations


// Error Text
	const char * errorText();
		// Access the error text.
		// _TAG05 Access

	void clearErrorText();
		// Clear the error text.
		// _TAG07 Operations

	void setErrorText( const char * text );
		// Set specified text as the error text.
		// _TAG07 Operations

	void appendErrorText( const char * text );
		// Append specified text to the error text.
		// _TAG07 Operations

// Event Processing
		// Command handlers.  When running as a Windows NT service, the
		// ServiceHandler() calls these routines to process commands
		// received from the Service Control Manager.  When not running as
		// a Windows NT service, these routines are called directly by
		// member functions (e.g. initialize() calls onInit()).
	virtual void onRun();
		// Daemon is initialized and ready to run (onRun() should not
		// return until the daemon is ready to exit).
		// _TAG08 Event Processing
	virtual RTRDaemonReturnValue onInit();
		// Perform application-specific initialization.
		// If initialization takes a long time, may need to call
		// checkPoint() or setStatus().
		// _TAG08 Event Processing
	virtual void onStop();
		// Stop and exit request.
		// _TAG08 Event Processing
	virtual void onInterrogate();
		// Status request.
		// _TAG08 Event Processing
	virtual void onPause();
		// Pause request.
		// _TAG08 Event Processing
	virtual void onContinue();
		// Resume request.
		// _TAG08 Event Processing
	virtual void onShutdown();
		// System is shutting down, stop and exit.
		// _TAG08 Event Processing
	virtual RTRBOOL onUserControl(unsigned int dwOpcode);
		// A command opcode >= RTR_DAEMON_USER_CTRL was received.
		// _TAG08 Event Processing


// Logging and Printing
	virtual void logEvent(	RTRDaemonLogSeverity sev,
							RTRDaemonEventId eventId );
		// Log an event.  This class can't use RTRLogger, because it
		// probably hasn't been created yet (if ever).
		//   Unix: This function does nothing.
		//   Windows NT: Logs a message to the Application EventLog.

	virtual void printEvent(RTRDaemonLogSeverity sev,
							RTRDaemonEventId eventId );
		// Print event to stderr.


// Windows NT Specific
	virtual void setStatus(unsigned int state);
		// Set the daemon status and inform the Service Control Manager.
		// _TAG07 Operations

	virtual void checkPoint();
		// Indicate that the daemon is still initializing.  The application
		// should call this from onInit() if onInit() will take a long time
		// to complete ( > 20 seconds).
		// This informs the Windows NT Service Control Manager that the
		// process is still running.
		// _TAG07 Operations


// Static Data
	static RTRDaemon* gblDaemon;
		// Needed to find daemon from static functions.
		// WARNING: Limits process to one RTRDaemon


// Data
	RTRDaemonData *	_impl;		// hide platform-specific data

	int				_argc;		// command-line argument count
	char **			_argv;		// command-line arguments
		// The command-line arguments are stored in _argc and _argv.
		//   Unix:
		//      The command-line arguments from main() are copied
		//      to _argc and _argv.
		//   Windows NT console application:
		//      The command-line arguments from main() are copied
		//      to _argc and _argv.
		//   Windows NT service application:
		//      _argv[0] is set to argv[0] from main().
		//      _argv[1] ... _argv[_argc] are the parameters (argv[1..n])
		//      from ServiceMain() (usually none) followed by any parameters
		//      in the registry variable (see readCmdLineArgsFromRegistry()).

protected:
	char *			_daemonName;
		// Name of this daemon (needed by Windows NT as the service name)

	char *			_errorText;
		// Error text.

	int				_isDaemon:1;
		// Are we a daemon?

	char *			_cmdLineArgs;
		// Storage for command-line arguments read from the Windows NT
		// registry.

	unsigned int	_baseLogMessageNumber;
		// Stores the base message number of the lowest EventLog service
		// message.  Windows NT-only.  This is provided so the service
		// message numbers (for the Windows NT EventLog messages) can be
		// redefined if they conflict with already defined messages.

};

#endif // _RTR_DAEMON_
