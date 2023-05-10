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

#ifndef __rtrDistContainer_h
#define __rtrDistContainer_h

#include "rtr/platform.h"
#include "rtr/dlinkl.h"
#include "rtr/gnptrvec.h"
#include "rtr/pointerlist.h"
#include "rtr/rtrmutex.h"
#include "rtr/objid.h"
#include "rtr/rtrDistAgent.h"
#include "rtr/rtrDistUser.h"
#include "rtr/rtrContainerServer.h"

class DEV_SH_LIB_EXPORT rtrDistContainer
{

public:

// Constructor
	rtrDistContainer(RTRObjectId&);

// Destructor
	virtual ~rtrDistContainer();

// Attributes
	RTRObjectId	& instanceId();
		// The instance identifier for this object.

	int numberOfAgents();
		// The number of agents within this container.

// Server Operations
	RTRBOOL addServer( rtrContainerServer & server );
		// Add 'server' to the containter.

	RTRBOOL dropServer( rtrContainerServer & server );
		// Drop 'server' from the containter.

	RTRBOOL hasServer( rtrContainerServer & server );
		// Is 'server' in this container?


protected:

	RTRPlatMutex			_mutex;
	RTRObjectId				_instanceId;
	rtrPtrList				_servers;
	RTRGenericPointerVector	_agentsByProtId;

	RTRDLinkList<rtrDistAgent, RTRDLink0>	_agents;

// Agent Operations
	int addAgent( rtrDistAgent & agent );
		// Add 'agent' to the container.
		// Return protocol Id for agent.
		// Return < 0 if operation failed.

	RTRBOOL dropAgent( rtrDistAgent & agent );
		// Drop 'agent' from the container.

	RTRBOOL hasAgent( rtrDistAgent & agent );
		// Is 'agent' within this container.

// Information
	void dispatchUnregMsg(rtrMsgBlock & msg, rtrDistUser& user);

	void dispatchUnknown(rtrMsgBlock & mblk, rtrDistUser& user);

	void newSession(rtrDistUser& user);
		// Notify agents of new session
	
	void informMaxMountsChanged(int maxMounts);
	void informMountNak();

	RTRBOOL logMounts();

// Friend Definitions
	friend class rtrDistAgent;
	friend class rtrContainerServer;
};

#endif
