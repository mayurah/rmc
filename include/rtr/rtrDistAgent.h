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

#ifndef __rtrDistAgent_h
#define __rtrDistAgent_h

#include "rtr/platform.h"
#include "rtr/linkl.h"
#include "rtr/rtstring.h"

class rtrDistContainer;
class rtrDistUser;
class rtrMsgBlock;

class DEV_SH_LIB_EXPORT rtrDistAgent :
	public RTRDLink0
{

public:

// Constructor
	rtrDistAgent(RTRString & nm, rtrDistContainer & cont);

// Destructor
	virtual ~rtrDistAgent();

// Attributes
	inline const RTRString & name() const
	{
		return(_name);
	};

	inline unsigned short protocolId() const
	{
		return(_protocolId);
	};

	inline RTRBOOL isInitializedWithContainer() const
	{
		return(_protocolId > 0);
	};

// Operations
	RTRBOOL initializeWithContainer();
		// Initialize this agent with the container.

protected:

	const RTRString		_name;
	short				_protocolId;
	rtrDistContainer &	_container;

// Member Functions
	virtual void processNewUser( rtrDistUser & user ) = 0;
		// Process this new container user.

	virtual void processContainerMsg( rtrDistUser&, rtrMsgBlock&) = 0;
		// Process this message tagged with your protocolId
		// and you have not yet registered for this protocolId
		// from this session.

	virtual void processUnknownFirstMsg( rtrDistUser&, rtrMsgBlock&);
		// Process this unknown first message. This will happen in the
		// case when old ssl applications attempt to connect to the
		// idist.

	virtual void processInformMaxMountsChanged(int newMaxMounts);
		// Inform agents that the maxMounts has been changed.
		// The agent which has license manager can compare new 
		// maxMounts with the NUM_OF_SSL_CONNECTIONS value in license file.

	virtual void processInformMountNak();
		// Inform agents about the mount nak. So, the agent can 
		// check if this nak is from exceeding of NUM_OF_SSL_CONNECTIONS
		// value in license file.

	virtual RTRBOOL logMounts() = 0;

// Friend Definitions
	friend class rtrDistContainer;
};

#endif
