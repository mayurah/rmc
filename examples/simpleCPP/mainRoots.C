//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
//
//Functionality:  This C++ RMC1.0 consumer application displays all the
//                root managed object information, all the corresponding
//                managed variable information , and all the root
//                man. object and man. variable updates as they are generated.


#include <iostream>
#include <unistd.h>
using namespace std;

#include "rtr/selectni.h"		// Event loop implementation
#include "rtr/shmpmosp.h"		// RTRShmProxyManagedObjectServerPool

#include "monitorRoots.h"



int main(int argc, char **argv)
{	
	char *szServerId = NULL;
	char szClassList[4096] = {0};
	if (argc == 3)
	{
		szServerId = argv[1];
		strcpy(szClassList, argv[2]);
	}
	else if (argc == 2)
	{
		szServerId = argv[1];
	}
	else
	{
		fprintf(stderr, "Usage: %s [memoryId] [className1,className2,className3..]\n", argv[0]);
		return 0;
	}
	cout << "argc" << argc << endl;
	cout << "arg1" << szServerId << endl;
	cout << "arg2" << szClassList << endl;

	// Create a base instance identifier

	// You could just pass a hard-coded literal string into the
	// constructors below. The appId approach is more elegant.

	RTRObjectId instanceId("shmApp");
	RTRShmProxyManagedObjectServerPool *pool =
			new RTRShmProxyManagedObjectServerPool(instanceId, "pool");

	// char *keyPtr[] = {(char *)"82", (char *)"456", (char *)"999"};
	// int len = 3;
	// for (int i = 0; i < len; i++)
		// pool->addServer(keyPtr[i]);
	pool->addServer(szServerId);

	// Monitor the server pool
	Monitor mon(*pool, szClassList);	

	// This application uses the select() based event loop.
	// You may choose a different implementation (e.g. Windows main loop
	// XWindows Event Notifier, you're own implementation etc.).
	RTRSelectNotifier::run();

	delete pool;

	return 0;
}

