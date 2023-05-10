//
//|---------------------------------------------------------------
//|                Copyright (C) 2001 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60523          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------

//  Description: This class serves as interface to OS blocking system to DNS interface, 
//				calls like gethostbyaddr and getservbyip.  These methods
//				can block within OS and hold up other threads.
//				This class takes care of requesting network info
//				within its own thread (which can block and not cause
//				other timeout issues by main thread).


#ifndef _getnetinfo_h
#define _getnetinfo_h

#include <stdio.h>
#ifndef WIN32
#include <sys/socket.h>
#include <netdb.h>
#endif

#include "rtr/sfevnotf.h"
#include "rtr/timercmd.h"
#include "rtr/rtrhierthr.h"
#include "rtr/rtrcondvar.h"
#include "rtr/rtrmutex.h"
#include "rtr/smallstr.h"
#include "rtr/dlinkht.h"
#include "rtr/objid.h"
#include "rtr/logevnt.h"


class netInfoClient;
class netRequest;


typedef long tagID;

typedef enum hostFunctionCodes
{
	GETHOSTBYADDR,
	GETHOSTBYNAME,
	GETSERVBYNAME,
	GETNAMEINFO,
	GETADDRINFO
} getRequestType;


class UserKey
{
	netInfoClient *_user;
	getRequestType _requestType;

public:
	UserKey(netInfoClient *user, getRequestType requestType);
	~UserKey() {};

	netInfoClient *user(void) {return _user;}
	getRequestType requestType(void) {return _requestType;}
	void requestType(getRequestType reqType) {_requestType = reqType;}
};

class PendingUserRequest :
	public RTRDLink0,
	public RTRDLink1
{
	UserKey				_userReqInfo;
	tagID				_tag;

public:
	PendingUserRequest(netInfoClient *user, getRequestType requestType, tagID id);
	~PendingUserRequest() {};

	tagID	tagId(void) {return _tag;}
	getRequestType requestType(void) {return _userReqInfo.requestType();}
	netInfoClient *user(void) {return _userReqInfo.user();}
	UserKey *userKey(void) {return &_userReqInfo;}

};


class networkInfo :
	public RTRThrdSafeControlThread,
	public RTRPlatHierThread
{

public:
	//Constructor
	networkInfo( RTRPlatHierThread &rootThrd, RTRObjectId &instance, RTRSafeEventNotifier *notifier );
	virtual ~networkInfo();

	// From RTRControlThread
	virtual RTRBOOL processThrdSafeControlThread();

	long gethostbyaddr( netInfoClient *user, void *sockptr);
	long gethostbyname( netInfoClient *user, const char *hostname);
	long getservbyname( netInfoClient *user, const char *serviceName, const char *protocol);

	long getnameinfo( netInfoClient *user, void *sockptr);
	long getaddrinfo( netInfoClient *user, const char *hostname);

	int registerUser(netInfoClient *user, tagID id, getRequestType reqType);

	int unregisterUser(tagID id);

	inline bool error(void) { return _error; }


protected:

	RTRLogEvent				_logEvent;
	RTRString				_logstr;	
	RTRPlatCondVar          _readLock;

	bool			_error:1;
	bool			_is_open:1;
	int						_inputBias;

	RTRDLinkList<netRequest, RTRDLink0> _input_queue;		// Storing incoming requests for net info
	RTRDLinkList<netRequest, RTRDLink0> _output_queue;		// Storing info recvd/replies

	RTRDLinkHashTable<tagID, PendingUserRequest, RTRDLink0>* _pendingReqIdHashTbl;

//From PlatHierThread
	virtual void runThread();
	virtual void threadDead();

	void startWorkerThrd(void);
	int unregisterUser(PendingUserRequest *pUserReq);

	RTRSafeEventNotifier 	*_notif;

	RTRObjectId				_class_name;

	static RTRBOOL compareTagIdToObjectOutbound(tagID *id, PendingUserRequest *uRequest)
		{ return ( uRequest->tagId() == *id) ? RTRTRUE:RTRFALSE; }

	static RTRBOOL compareKeyToObjectOutbound(UserKey *uKey, PendingUserRequest *uRequest)
		{ 
			if ( uRequest->user() == uKey->user() && uRequest->requestType() == uKey->requestType() )
				return RTRTRUE;
			else
				return RTRFALSE;
		}

};


//******************************************************************************
//	Second Generation DNS API interface
//		Tracks array of notifiers associated with one or more threads
//			invoking DNS requests
//		Original class networkInfo is separated out into two classes to handle
//			working thread separate from safe control thread notification

class networkInfoPlatThrd;

class networkInfoSafeCtrl :
	public RTRThrdSafeControlThread
{

public:
	networkInfoSafeCtrl( RTRSafeEventNotifier *notif );
	virtual ~networkInfoSafeCtrl();

	// From RTRControlThread
	virtual RTRBOOL processThrdSafeControlThread();

	int registerUser(netInfoClient *user, tagID id, getRequestType reqType);
	int unregisterUser(tagID id);

	static RTRBOOL compareTagIdToObjectOutbound(tagID *id, PendingUserRequest *uRequest)
		{ return ( uRequest->tagId() == *id) ? RTRTRUE:RTRFALSE; }

	static RTRBOOL compareKeyToObjectOutbound(UserKey *uKey, PendingUserRequest *uRequest)
		{ 
			if ( uRequest->user() == uKey->user() && uRequest->requestType() == uKey->requestType() )
				return RTRTRUE;
			else
				return RTRFALSE;
		}

	inline RTRSafeEventNotifier *notif(void) {return _notif;}

	void doRunThreadWork(networkInfoPlatThrd *parent);
	long addRequest(netRequest *inbuf);

	inline void isopen(bool open) {_is_open = open;}
	inline bool isopen(void) {return _is_open;}

	inline void setflagthread(RTRPlatFlagThread &parent) {_readLock.setFlagThread(parent);}

protected:

	int unregisterUser(PendingUserRequest *pUserReq);


	RTRPlatCondVar          _readLock;
	bool                    _is_open:1;
	int			_inputBias;

	RTRDLinkList<netRequest, RTRDLink0> _input_queue;		// Storing incoming requests for net info
	RTRDLinkList<netRequest, RTRDLink0> _output_queue;		// Storing info recvd/replies

	RTRDLinkHashTable<tagID, PendingUserRequest, RTRDLink0>* _pendingReqIdHashTbl;

	RTRSafeEventNotifier 	*_notif;
};

class networkInfoPlatThrd :
	public RTRPlatHierThread
{

public:
	//Constructor
	networkInfoPlatThrd( RTRPlatHierThread &rootThrd, RTRObjectId &instance, int numNotif, RTRSafeEventNotifier **notifier, const char* comp_name = NULL );
	virtual ~networkInfoPlatThrd();

	long gethostbyaddr( netInfoClient *user, void *sockptr, RTRSafeEventNotifier *notifier );
	long gethostbyname( netInfoClient *user, const char *hostname, RTRSafeEventNotifier *notifier );
	long getservbyname( netInfoClient *user, const char *serviceName, const char *protocol, RTRSafeEventNotifier *notifier );

	long getnameinfo( netInfoClient *user, void *sockptr, RTRSafeEventNotifier *notifier );
	long getaddrinfo( netInfoClient *user, const char *hostname, RTRSafeEventNotifier *notifier );

	inline bool error(void) { return _error; }
	networkInfoSafeCtrl *findSafeCtrlThrd(RTRSafeEventNotifier *notif);

	int unregisterUser(tagID id, RTRSafeEventNotifier *notifier);

protected:

	RTRLogEvent				_logEvent;
	RTRString				_logstr;	
	bool					_error:1;
	bool					_is_open:1;
	char 					_comp_name[16];

//From PlatHierThread
	virtual void runThread();
	virtual void threadDead();

	void startWorkerThrd(void);

	RTRObjectId				_class_name;

	networkInfoSafeCtrl		**_notifCtrlThrds;
	int				_numNotifCtrlThrds;
	RTRPlatCondVar          _waitLock;

};

class netInfoClient :
	public RTRDLink1
{
public:
	netInfoClient();
	virtual ~netInfoClient();

	virtual void processNetworkInfo(netRequest *replyInfo) = 0;

};

class netRequest :
	public RTRDLink0
{

protected:
	getRequestType		_requestType;
	int					_serverPort;
	int					_error;

	netInfoClient		*_user;

	tagID				_tag;
	struct sockaddr		*_sockptr;

	RTRString			_name;				// stores serviceName for BYSERV hostName for BYNAME
	RTRString			_protocol;	


	static tagID		_tagCounter;

	tagID			nextUniqueTag(void);

public:
	netRequest(getRequestType fcode, netInfoClient *user, void *socket = NULL);
	netRequest(getRequestType fcode, netInfoClient *user, const char *hostname);
	netRequest(getRequestType fcode, netInfoClient *user, const char *serviceName, const char *protocol);
	~netRequest();

	inline getRequestType funcCode(void) {return _requestType;}
	inline getRequestType requestType(void) {return _requestType;}

	inline struct sockaddr *sockPtr(void) {return _sockptr; }
	inline void sockPtr( struct sockaddr *socket ) { _sockptr = socket; }

	inline RTRString *hostName(void) {return &_name;}
	inline void hostName( RTRString &hostName ) { _name = hostName; }
	inline void hostName( char *hostName) { _name = hostName; }

	inline netInfoClient *user(void) { return _user; }
	inline void user(netInfoClient *ptr) { _user = ptr; }
	inline tagID id(void) {return _tag;}

	inline void error(int errorCode) { _error = errorCode;}
	inline int error(void) { return _error; }

	inline void serverPort(int sPort) { _serverPort = sPort; }
	inline int serverPort(void) { return _serverPort; }

	inline void serviceName(RTRString &serviceName) { _name = serviceName; }
	inline void serviceName(const char *serviceName) { _name = serviceName; }
	inline RTRString *serviceName(void) { return &_name; }

	inline void protocol(RTRString &protocol) {_protocol = protocol;}
	inline void protocol(const char *protocol) {_protocol = protocol;}
	inline RTRString *protocol(void) { return &_protocol; }

};

#endif

