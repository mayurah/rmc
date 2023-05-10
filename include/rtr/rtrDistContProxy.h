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


#ifndef __rtrDistContProxy_h
#define __rtrDistContProxy_h

#include "rtr/platform.h"
#include "rtr/dlinkl.h"
#include "rtr/rtrDistAgentProxy.h"
#include "rtr/lnsrctbl.h"
#include "rtr/timercmd.h"
#include "sipc/rtrSipcClient.h"
#include "sipc/rtrSipcSession.h"
#include "sipc/rtrSipcAddr.h"

class rtrDistContAccess;

class DEV_SH_LIB_EXPORT rtrDistContProxy :
	public RTRDLink0,
	protected rtrSipcClient,
	protected RTRTimerCmd
{

public:

// Constructor
	rtrDistContProxy(rtrDistContAccess & contAccess, short compressionType = 0 );

	rtrDistContProxy(rtrDistContAccess & contAccess, rtrSipcAddr &addr, short compressionType = 0 );

// Destructor
	virtual ~rtrDistContProxy();

// Attributes
	inline RTRBOOL isConnected() const
		// Is the container proxy attached to a container? This
		// does not mean the proxy is active. It may still need
		// to be authenticated.
	{
		return( (_session && _session->isSessActive()) ? RTRTRUE : RTRFALSE );
	};

	inline RTRBOOL isActive() const
		// Is the container proxy active? This implies a session
		// exists, the proxy has been authenticated and a agent table
		// has been received.
	{
		return( _isActive ? RTRTRUE : RTRFALSE );
	};

	inline rtrSipcSession *session()
	{
		return(_session);
	};

	inline rtrSipcAddr & address()
	{
		return(_address);
	};

	inline void invalidServer()
	{
		_contLocIndex++;
	};

	inline RTRBOOL endOfServers()
	{
		return (_wrappedServList ? RTRTRUE : RTRFALSE);
	};

// Agent Table Access
	int protocolIdByName( const char *agentName );
		// Get the protocol id by the agent Name.
		// REQUIRE : isActive();
		// returns -1 on failure.

protected:

	rtrDistContAccess &	_contAccess;
	rtrSipcError		_sipcError;
	rtrSipcSession		*_session;
							// The current sipc session.

	rtrSipcAddr			_address;
							// The current address of the container to attempt
							// connection or is connected.

	RTRLinSrchTbl		_agentTable;
							// Table of remote agents. They are stored by protocolId
							// and the agent name. This is information received
							// by the real container about the agents that
							// can be used. It will be empty until the agent
							// table has been received.

	unsigned short		_contLocIndex;
							// The current index into the _serverAddresses table
							// for containers. This table is used to find
							// addresses of containers to attempt connections.
							// This index is locked by the rtrDistContAccess
							// mutex.

	unsigned short		_proxyLocIndex;
							// The current index into the _serverAddresses table
							// for proxy servers. This table is used to find
							// addresses of proxy servers to attempt connections.
							// This index is locked by the rtrDistContAccess
							// mutex.

	RTRBOOL				_wrappedServList;
							// identifies if container has wrapped arround the server list

	unsigned short		_reconnectInterval;
							// The time (seconds) to wait before reconnection attempts.

	unsigned short		_isActive:1;
							// Is the container proxy active.

	unsigned short		_staticAddress:1;
							// Is the _address a static value. If true the
							// address cannot change.

	RTRDLinkList<rtrDistAgentProxy, RTRDLink0>  _agents;
							// List of current agent proxies.

	short		_compressionType;
							// compression type for session 0 is no compression

	unsigned short	_peerAliveCount;
							// For timing out server

	RTRString		_text;
							// Store error text, etc

//	rtrMsgBlock *mblk; 
						//used to send container message out

// Initialization.
	void initialize();
	void findConnection();

	void cleanup(RTRBOOL setRetryTimer=RTRFALSE);

	void setAuthenticated();
		// The access point has been authenticated.

	RTRBOOL sendLoginReq();
	void deActivateAgents(const char* reason);
	void activateAgents();
	RTRBOOL sendPingResponse();
	RTRBOOL sendNewTicket();

// Agent Operations
	RTRBOOL addAgent( rtrDistAgentProxy & agent );
	RTRBOOL dropAgent( rtrDistAgentProxy & agent );
	RTRBOOL hasAgent( rtrDistAgentProxy & agent );
	RTRBOOL hasAgent( const char * agentName );

// From RTRTimerCmd
	virtual void processTimerEvent();
		// Timer callback

// From rtrSipcClient
  // Connection Setup Events
	virtual void processNewDescriptor( rtrSipcSession&, int oldDesc);
		// This session has received a new descriptor.

	virtual void processConnectionActive( rtrSipcSession&);
		// This session has become active.

	virtual void processConnectionFailure( rtrSipcSession&, const char*);
		// This connection attempt has failed.

	virtual void processConnectionReject( rtrSipcSession&, const char*);
		// This connection attempt was rejected.

  // Connection Active Events
	virtual void processDisconnect( rtrSipcSession&, const char *text);
		// This session has been disconnected.

	virtual void processMessage( rtrSipcSession&, rtrMsgBlock&);
		// A message is ready.

	virtual void processOutputThresholdBreach( rtrSipcSession &);
	virtual void processOutputThresholdOK( rtrSipcSession &);
	virtual void processInputThresholdBreach( rtrSipcSession &);
	virtual void processInputThresholdOK( rtrSipcSession &);

// Friend Definitions
	friend class rtrDistContAccess;
	friend class rtrDistAgentProxy;
	
};

#endif

