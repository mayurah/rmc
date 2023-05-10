#ifndef	__rtr_hires_thread_h
#define	__rtr_hires_thread_h

#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

#include "rtr/sfevnotf.h"
#include "rtr/rtrthread.h"
#include "rtr/dlinkht.h"
#include "rtr/objid.h"
#include "rtr/cfgvar.h"
#include "rtr/logevnt.h"


class RTRHiResTimerClient
{
public:
	RTRHiResTimerClient();
	virtual ~RTRHiResTimerClient();

	virtual void processRTRHiResTimerEvent(void) = 0;
};

class HiResTimer :
	public RTRThrdSafeControlThread,
	public RTRDLink0
{

public:

	HiResTimer( RTRSafeEventNotifier *notif, RTRHiResTimerClient *pClient);
	virtual ~HiResTimer();

	// From RTRThrdSafeControlThread
	virtual RTRBOOL processThrdSafeControlThread();

	inline RTRSafeEventNotifier *notif(void) {return _notif;}

	RTRHiResTimerClient *client(void) { return _client;}

private:

	RTRSafeEventNotifier 	*_notif;
	RTRHiResTimerClient	*_client;

};

#define	MAX_ERRORTXT_LEN	255

class RTRHiResTimer :
	public RTRPlatThread
{

public:

	typedef enum 
	{
		BIND_NONE = 0,				// No bind information provided
		BIND_UNINT = 1,				// bind info provided, but no bind call yet
		BIND_INITOK = 2,			// bind success
		BIND_INITERR = 3			// bind error - result string stored if memory
	} RTR_HIRES_BIND_STATUS;

	RTRHiResTimer(RTRObjectId &instance, int nanosec_interval, RTRString &className, RTRConfigVariable *bindThread = NULL);
	virtual ~RTRHiResTimer();

	int addClient(HiResTimer &client);
	int delClient(HiResTimer &client);
	
	int start(void);
	void getErrTxt(char *msg, size_t msgLen, int errorNo);
	inline int error(void) {return _errorNum;}

	//From RTRPlatThread
	virtual void runThread();		// Main thead of execution

	RTR_HIRES_BIND_STATUS bindStatus(void) { return _bindStatus;}
	void log(RTRString &text, int strSeverity);

	inline int microsecondInterval(void) { return (_nanosec_interval / 1000); }


private:

	RTRObjectId			_class_name;
	RTRObjectId			_instance;

#ifndef _WIN32
	timer_t				_itimerid;
	sigset_t			_mask;
#endif

	int					_nanosec_interval;

	char				_errorTxt[MAX_ERRORTXT_LEN];
	int					_errorNum;

	bool				_shutdown_pending;

	RTRConfigVariable			_bindHRTThread;
	RTR_HIRES_BIND_STATUS		_bindStatus;

	RTRDLinkList<HiResTimer, RTRDLink0>	 _clientList;

	//int					_timeroverrun;
};


#endif
