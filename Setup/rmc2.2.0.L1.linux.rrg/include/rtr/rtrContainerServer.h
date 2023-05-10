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

#ifndef __rtrContainerServer_h
#define __rtrContainerServer_h

#include "rtr/platform.h"
#include "rtr/rtstring.h"
#include "rtr/logevnt.h"
#include "rtr/dlinkl.h"
#include "sipc/rtrSipcServer.h"
#include "sipc/rtrSipcClient.h"
#include "rtr/rtrDistUser.h"

class rtrDistContainer;
class RTRPublicObject;

class DEV_SH_LIB_EXPORT rtrContainerServer :
	public rtrSipcSrvrClient
{
public:

// Constructor
	rtrContainerServer( RTRString portName, 
			int portNumber,
			RTRObjectId parentInstance, 
			RTRObjectId name,
			rtrDistContainer *container,
			const int numWriterThreads,
			RTRPublicObject *parent = 0);
		// The parentInstance and name are provided (instead of a single
		// instance), because the name is appended to the parentInstance
		// for configuration and to the (optional) parent public object
		// for manageability.

// Destructor
	virtual ~rtrContainerServer();

	RTRBOOL authRequired() { return _authRequired; }
	RTRBOOL allowCompMode() { return _allowCompMode; }
	rtrSipcServer&	server() { return *_server; }

protected:
	rtrSipcServer	*_server;
	rtrDistContainer *_container;
	RTRObjectId	_instance;
	RTRLogEvent	_logEvent;
	RTRBOOL		_authRequired:1;
	RTRBOOL		_debugLogging:1;
	RTRBOOL		_allowCompMode:1;
	int		_connectDelay;
	int		_heartbeatInterval;
	int		_pingInterval;
	unsigned short	_timeout;
	int		_loginDelay;
	int 	_asyncAuthTimeout;

	void *_iauth;

	eVerifyTicketRet (*_funcAuthVerify)(eVerifyTicketState, unsigned char *, int, AUTH_TICKET_INFO_TYPE *);

	RTRDLinkList<rtrDistUser, RTRDLink0> _users;
	RTRPlatMutex _mutex;

	void dispatchUnregMsg(rtrMsgBlock & mblk, rtrDistUser& user);
	void dispatchUnknown(rtrMsgBlock & mblk, rtrDistUser& user);

	void removeUser(rtrDistUser& user);

// From rtrSipcSrvrClient
	virtual void newSession(rtrSipcServer&,rtrSipcSession&);
		// A session has become active and is ready for
		// communication.

	virtual void failedConnectAttempt(rtrSipcServer&,const char *text);
		// An attempt to connect has failed during the
		// // connection phase.

	virtual void rejectConnectionAttempt(rtrSipcServer&,const char *text);
		// This server has reject a connection attempt.

	virtual void processUserAuthenticated(rtrDistUser&);

	virtual void informMaxMountsChanged(int maxMount);
	virtual void informMountNak();

	virtual RTRBOOL logMounts();

// Friend Definitions
	friend class rtrDistUser;
};

#endif
