//
//|---------------------------------------------------------------
//|                Copyright (C) 1998 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60523          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:		Kevin Nicodemus
//  created:	June 25, 1998
//  version:    1.0
//

#ifndef __rtr_daemon_installer_h
#define __rtr_daemon_installer_h

// Synopsis:
// #include "rtr/dmninst.h"
//
// Description:
// This class provides a platform-independent C++ interface that
// applications can use to install themselves as services under
// Windows NT.  The Unix version of this class does nothing.
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
//		RTRDaemon
//


#include "rtr/rtrdefs.h"


class RTRDaemonInstaller
{
public:
    RTRDaemonInstaller(const char * serviceName, const char* description);

    virtual ~RTRDaemonInstaller();

    RTRBOOL parseStandardArgs(int argc, char ** argv);
    RTRBOOL isInstalled();
    RTRBOOL install(RTRBOOL, RTRBOOL, const char * , const char *, const char * cmdLineArgs = 0);
    RTRBOOL uninstall();

	void setCategoryCount( int count );

    // data members
	char *		_installServiceName;
	char *		_installDescription;
	int			_categoryCount;
		// number of categories for log events.
};

#endif // _RTR_DAEMON_INSTALLER_
