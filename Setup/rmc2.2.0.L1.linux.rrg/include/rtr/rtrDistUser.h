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


#ifndef __rtrDistUser_h
#define __rtrDistUser_h

#include "rtr/platform.h"
#include "rtr/linkl.h"
#include "rtr/logevnt.h"
#include "rtr/timercmd.h"

#include "sipc/rtrSipcClient.h"

class rtrSipcSession;
class rtrContainerServer;
class rtrReAuthTimer;
	  
enum UserStatus {
  	userCreated = 0, 
	userLoginPending = 1,
	userAuthPending = 2,
	userActive = 3,
	userShutdown = 4,
	userActiveComp = 5,
	userPingRespPending = 6,
	userAsyncAuthPending = 7,
	userActiveWaitTkt = 8,
	userActiveAsyncAuthPending = 9,
	userActiveAuthPending = 10
};

enum TimerState {
	waitingToNotify = 0,
	waitingToExpire = 1,
	stopped	=2
};

#ifndef __IAUTH_LIB__

#define	AUTH_MAX_USER_NAME	32 /* Maximum length of the users name */

typedef struct {
	char		AuthUserName[AUTH_MAX_USER_NAME+1];
	unsigned long	AsyncHandle;
	long		timeout_time;  /* GMT time() */
	long            delay_time;    /* In seconds */
}	AUTH_TICKET_INFO_TYPE;

typedef enum {
	AUTHENTICATION_SUCCESS = 1,
	AUTHENTICATION_FAILURE = 2,
	AUTHENTICATION_ASYNC = 3
} eVerifyTicketRet;

typedef enum {
	AUTHENTICATION_START = 1,
	AUTHENTICATION_CONTINUE = 2,
	AUTHENTICATION_ABORT = 3
} eVerifyTicketState;

#endif

class DEV_SH_LIB_EXPORT rtrDistUser :
	public RTRDLink0,
	public RTRTimerCmd,
	public rtrSipcClient
{

public:

// Constructor
	rtrDistUser( rtrContainerServer&, rtrSipcSession& );

// Destructor
	virtual ~rtrDistUser();

// Attributes
	inline rtrSipcSession &session(){ return _session; }

	const char* userName() const;

// Operations
	void setCompatibiltyMode();
		// Set to work in a comtability mode with old ssl applications.
	void sendNewTktRequest();
		// The old tkt is about to expire and we need to auth a new one
	void sendTktExpired();
		// The ticket has expired.

protected:
	AUTH_TICKET_INFO_TYPE	_ticketInfo;
	rtrContainerServer	&_containerServer;
	rtrSipcSession		&_session;
	rtrReAuthTimer		*_reAuthTimer;
	RTRLogEvent		_logEvent;
	UserStatus		_status;
	unsigned long		_numMsgsRcvd;
	int			_pingInterval;
	int			_pingCounter;
	int			_pingRespCounter;
	int			_timeout;
	int			_heartbeatInterval;
	int			_asyncAuthTimeout;
	int			_numAsyncAuth;
	int			_loginAttempts;

// Member Functions
	void processContainerMsg( rtrSipcSession&, rtrMsgBlock&);
	void processAuthLoginMsg( rtrSipcSession&, unsigned char* data, int dataLen);
	void processLoginMsg( rtrSipcSession&, unsigned char* data, int dataLen);
	void processVerifyTicketRet( eVerifyTicketRet eRet);
	void processUserAuthenticated();
	void processUserReAuthenticated();
	void sendLoginAck();
	void sendLoginNak(const char *);


// From rtrSipcClient
	virtual void processNewDescriptor( rtrSipcSession&, int oldDesc);
		// This session has received a new descriptor.

	virtual void processConnectionActive( rtrSipcSession&);
		// This session has become active.

	virtual void processConnectionFailure( rtrSipcSession&, const char*);
		// This connection attempt has failed.

	virtual void processConnectionReject( rtrSipcSession&, const char*);
		// This connection attempt was rejected.

	virtual void processDisconnect( rtrSipcSession&, const char *text);
		// This session has been disconnected.

	virtual void processMessage( rtrSipcSession&, rtrMsgBlock&);
		// A message is ready.
// From rtrTimerCmd
	void processTimerEvent();

// Friend Definitions
};

class rtrReAuthTimer :
	public  RTRTimerCmd
{

public:

// Constructor
	rtrReAuthTimer(rtrDistUser&, unsigned long, unsigned long);

// Destructor
	~rtrReAuthTimer();

// Operations
	inline void stopTimer() 
	{ 
		if (active()) 
        	deactivate(); 
		_state = stopped;
	};

	void reset(unsigned long, unsigned long);

protected:
	rtrDistUser             &_distUser;
	TimerState              _state;

	// Time in seconds to notify that the tkt will expire
	// and to req a new one for auth
	unsigned long   _notifyTime;    
	
	// Seconds to wait to expire the tkt after
	// the new tkt req is made
	unsigned long   _delayTime;     

	// From RTRTimerCmd
	void processTimerEvent();

};										

#endif

