//|---------------------------------------------------------------------------
//|                Copyright (C) 1998,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "rtr/cmdline.h"

#include "rtr/rtrnotif.h"

#include "rtr/sighndlr.h"
#include "rtr/appid.h"
#include "rtr/execpath.h"
#include "rtr/xfdb.h"
#include "rtr/config.h"
#include "rtr/dfltlog.h"
#include "rtr/mgmtevnt.h"
#include "rtr/rtrenv.h"
#include "rtr/environ.h"

#include "rtr/shrdmem.h"
#include "rtr/shmmosvr.h"
#include "rtr/shmstats.h"

#include "admin.h"
#include "root.h"

#define MAX_FILENAME_LENGTH 512

RTRCmdLine RTRCmdLine::cmdLine;

using namespace std;

int main(int argc, char **argv)
{
	RTRBOOL useConfig = RTRTRUE;
	RTRMgmtEvent event;

	//-------------------------------------------------------------
	// Process Command line arguments
	//-------------------------------------------------------------
	RTRCmdLineString inst("i", "instance", "instance #", "1", RTRCmdLineArg::False);
	RTRCmdLineString cfg_file("c", "filename", "config filename", "", RTRCmdLineArg::False);

	RTRCmdLine::cmdLine.resolve(argc, argv);
	if ( RTRCmdLine::cmdLine.error() )
	{
		#ifdef _RDEV_NO_STL_
		RTRCmdLine::cmdLine.printUsage(stderr, argv[0]);
		#else
		RTRCmdLine::cmdLine.printUsage(cerr, argv[0]);
		#endif
		return -1;
	}

	RTRObjectId class_id("RMDS.PUBLISHER");
	RTRApplicationId appId((const RTRString&)inst, "Publisher");

	event.setIdentifier(appId);
	event.setSeverity("Info");

	//--------------------------------------------------
	// Configuration file
	//--------------------------------------------------
	// Find which config file to use:
	// 1. Use file specified on command line.
	// 2. Use file specified by env variable
	// 3. Use default file
	char ConfigDBFilename[MAX_FILENAME_LENGTH];
        RTRString configFileName;
        if ( cfg_file.valid() )
		configFileName = cfg_file.stringValue();
	else
	{
		if ( RTRGetEnv( "RMDS_CONFIG",
				ConfigDBFilename,
				MAX_FILENAME_LENGTH ) == RTR_ENV_SUCCESS )
			configFileName = ConfigDBFilename;
		else if ( RTRGetEnv( "DISTRIBUTION_CONFIG",
				ConfigDBFilename,
				MAX_FILENAME_LENGTH ) == RTR_ENV_SUCCESS )
			configFileName = ConfigDBFilename;
		else
			configFileName = "/var/distribution/distribution.cnf";
	}

	RTRExecutablePathName cfgPath(configFileName);
	ifstream configFile( configFileName, ios::in );
	if ( !configFile )
	{
		#ifdef _RDEV_NO_STL_
		fprintf(stderr, "Error opening config file \"%s\"\n", cfgPath.path().to_c());
		RTRCmdLine::cmdLine.printUsage(stderr, "Publisher");
		#else
		cerr << "Error opening config file \"" << cfgPath.path() << "\"" << endl;
                RTRCmdLine::cmdLine.printUsage(cerr, "Publisher");
		#endif
		return -1;
	}
	configFile.close();
	RTRXFileDb configDb(configFileName);
	RTRConfig::setConfigDb(configDb);
	cerr << "Using config file: \"" << cfgPath.path() << "\"" << endl;

		// Create actions for generated mgmt events
	RTRDefaultLogger logger(appId, "logger", "Publisher Example");

	event.setText("Initialization started.");
        event.log();

	RTRString txt("Using config file: ");
	txt.append(configFileName);
	event.setText(txt);
        event.log();

	RTRTermSignalHandler sigHandler;

	// Either use RTRServerSharedMemoryRoot code shown below
	// or utilize the MyHelperAdmin helper class
	/*	
	RTRServerSharedMemoryRoot shm(appId, "sharedmem", "99", "99", 5, 30000, 2);

	if (shm.error()) return -1;

	RTRShmMOServerMemPool moPool(shm, *(shm.semaphoreSet()), 3, 10000);

	if (moPool.error()) return -1;
	
	RTRSharedMemoryStats _memoryStats (
				appId, 
				"MemoryStats", 
				*(shm.header()),
				RTRTRUE,
				5
				);
	
	moPool.useStats(&_memoryStats);
	*/	

	MyHelperAdmin admin(class_id, appId);
	if( admin.error() )
	{
		cerr << "publisher: Initialization Failed -Check Log-" << admin.text() << endl;
		cerr << flush;
		return 0;
	}

	RootObject root(appId, "Publisher", "1.0");

	RTREventNotifierInit::notifier->enable();

	// Shutdown
	event.setText("Terminated.");
	event.log();
 
	return 0;
}
