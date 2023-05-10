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


#ifndef __rtrDistContAccess_h
#define __rtrDistContAccess_h

#include "rtr/platform.h"
#include "rtr/dlinkl.h"
#include "rtr/pointerlist.h"
#include "rtr/objid.h"
#include "rtr/rtrDistContProxy.h"
#include "sipc/rtrSipcAddr.h"
#include "sipc/rtrSipcMgr.h"

class rtrDistAgentProxy;
class RTRBuffer;


	// An application that wishes to receive events from the
	// container access interface would inherit from
	// rtrDistContAccessClient and define the appropriate
	// member functions.
class DEV_SH_LIB_EXPORT rtrDistContAccessClient
{
public:

// Destructor
	virtual ~rtrDistContAccessClient() {};

// Callbacks

  // Authentication informational events
	virtual void processAuthenticated() = 0;
		// This user has been authenticated.

	virtual void processAuthenticationDenied( const char *reason ) = 0;
		// This user authentication request has been denied.


  // Container connection informational events
	virtual void processConnectionFailure(
					rtrSipcAddr & address, const char * reason ) = 0;
		// A connection failure has occured with the container
		// at the address.

	virtual void processConnectionReject(
					rtrSipcAddr & address, const char * reason ) = 0;
		// A connection rejection has occured with the container
		// at the address. We were able to connect, however the
		// session was rejected.
};



class rtrDistContAccess :
	public rtrSipcMgr
{
public:

// Constructor
	rtrDistContAccess(	RTRObjectId& instanceId,
						RTRBOOL requiresAuthentication=RTRFALSE,
						RTRPlatMutex *mtx = 0 );

// Destructor
	virtual ~rtrDistContAccess();


// Attributes
	const RTRObjectId & instanceId() const;
		// The instance identifier for this object.

	RTRBOOL requiresAuthentication() const;
		// Does this container access interface require authentication?

	RTRBOOL isAuthenticated() const;
		// Is this container access interface authenticated?

// Authentication Operations
	RTRBOOL authenticate();
		// This method tells the container access interface
		// to attempt authentication.
		// This will also force the requiresAuthentication()
		// attribute if is wasn't set on the constructor.


// Agent Proxy Operations
	rtrDistAgentProxy *agentProxy( const char *agentName, short compressionType );
		// Create and new agent proxy and attempt to initialize
		// with the default container.


// Default Server Locations
	enum serverType {
		authentication = 0,		// Authentication server.
		server = 1,				// Container server.
		proxy = 2				// When the container server is proxy, this is the idist addr behind proxy
	};

	RTRBOOL addServerAddr( serverType stype, rtrSipcAddr &addr );
		// Add an entry to the serverType locations list.

	RTRBOOL removeServerAddr( serverType stype, rtrSipcAddr &addr );
		// Remove an entry from the serverType locations list.

	RTRBOOL hasServerAddr( serverType stype, rtrSipcAddr & addr );
		// Does the entry exist in the serverType locations list?


// Explicit Container Operations
	rtrDistAgentProxy *agentProxy( const char *agentName, rtrSipcAddr &addr, short compre );
		// Create a new agent proxy and attempt to intialize with
		// the container at addr.
		// This is meant for legacy applications. Should not normally
		// be used.

//New
	void setUserNamePassword(const char*u, const char* p);
	static rtrDistContAccess* getContainerAccess();
	void removeAgentProxy( rtrDistAgentProxy& agp );

	void addClient(rtrDistContAccessClient& client);
	void dropClient(rtrDistContAccessClient& client);
	RTRBOOL hasClient(rtrDistContAccessClient& client) const;


protected:
	static RTRObjectId glbContainerId ;
	static RTRPlatMutex glbLock ;
	static rtrDistContAccess* glbContInstance ;

	const RTRObjectId		_instanceId;
	rtrPtrList				_serverAddresses[3];
	RTRDLinkList<rtrDistContProxy, RTRDLink0>	_contProxies;
	RTRLinkedList<rtrDistContAccessClient>	_clients;

	unsigned short			_requiresAuthentication:1;
	unsigned short			_isAuthenticated:1;

	RTRBuffer				*_authTicket;
	RTRString				_errorText;
	RTRString				*_userName;
	RTRString				*_passWord;

// Operations
	inline void lock() { refDoLock(); };
	inline void unlock() { refDoUnlock(); };


// Information
	int intServerLoc( rtrPtrList &list, rtrSipcAddr & addr );
		// Does the entry exist in the default server locations 'list'.

	rtrDistContProxy *findFreeContainer(const char *agentName, rtrSipcAddr *addr=0);
		// Find a container proxy that this agentName can utilize.


// Authentication Operations
	void setAuthenticated( char * ticket, int length );
		// Set this container access point as "authenticated" with
		// the appropriate 'ticket'.

	void setAuthFailure( const char *reason );
		// Set this container access point as failed to "authenticate"
		// for 'reason'.


// Failures
	void connFailure(rtrSipcAddr &addr, const char *reason, RTRBOOL reject);
		// A connection attempt to a container has failed.

// Implementation
	RTRBOOL getTicketHttpImpl(RTRString& ticket,const char* service, const char* resource,int port);
	RTRBOOL getTicketHttpsImpl(RTRString& ticket,const char* service, const char* resource, int port);
	RTRBOOL parseURL(RTRString& url, RTRString& webAddr, RTRString& resource, int* sslFlag, int* port, RTRBOOL* tunnel);
	RTRBOOL retrieveData(RTRString& ticket,long hResourceHandle);
	RTRBOOL retrieveHeader(long hdl);

// Friend
friend class rtrDistContProxy;

};


#endif
