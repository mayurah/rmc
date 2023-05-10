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


#ifndef __rtrDistAgentProxy_h
#define __rtrDistAgentProxy_h

#include "rtr/platform.h"
#include "rtr/linkl.h"
#include "rtr/rtstring.h"
#include "rtr/pointerlist.h"

class rtrDistContProxy;

class DEV_SH_LIB_EXPORT rtrAgentProxyClient
{
public:

// Destructor
	virtual ~rtrAgentProxyClient();

// Callbacks
	virtual void processAgentActive(unsigned short protocolId) = 0;
		// The agent has gone active.

	virtual void processAgentInactive(const char *reason) = 0;
		// The agent has gone inactive.

};



class rtrDistAgentProxy :
	public RTRDLink0
{

public:

// Constructor
	rtrDistAgentProxy(const char *name);

// Destructor
	~rtrDistAgentProxy();

// Attributes
	inline const RTRString & name() const
	{
			// No need to lock since never changes.
		return(_name);
	};

	rtrDistContProxy *contProxy();
		// The container proxy this agent proxy is associated.

	RTRBOOL isActive() const;
		// Is this agent proxy active?

	unsigned short protocolId() const;
		// The protocol identifier for this agent.
		// Returns 0 if the agent proxy is not active.

// Client Operations
	RTRBOOL addClient( rtrAgentProxyClient &client );
	RTRBOOL dropClient( rtrAgentProxyClient &client );
	RTRBOOL hasClient( rtrAgentProxyClient &client );

protected:

	const RTRString		_name;
	rtrDistContProxy	*_contProxy;
	unsigned short		_protocolId;
	rtrAgentProxyClient	*_client;


// rtrDistContProxy operations
	RTRBOOL setContProxy( rtrDistContProxy & contProxy );
	RTRBOOL clearContProxy(rtrDistContProxy & contProxy );

	void setActive( unsigned short protocolId );
		// Set the agent proxy as active

	void setInactive(const char *reason);
		// Set the agent proxy inactive.


// Friend Definitions
	friend class rtrDistContProxy;
};

#endif

