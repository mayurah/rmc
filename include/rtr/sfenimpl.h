//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       September 16, 1996
//  version:       1.0
//
//  description:
//


#ifndef _sfenimpl_h 
#define _sfenimpl_h

#include "rtr/enimpl.h"
#include "rtr/sfevnotf.h"
#include "rtr/ldlinkl.h"
#include "rtr/mutex.h"

// Synopsis:
//
// Description:
//
// See Also:
//


// Pipe to support low latency event signaling 

class	EVNPipe
{
public:

	/// Default Constructor
	EVNPipe( void );

	/// Destructor
	virtual ~EVNPipe();

	RTRBOOL create();
	void close();

	void signal();
	void clear();
	int readFD() const { return _rfds; }
	int writeFD() const { return _wfds; }

	int initialized() const { return _initialized; }
	char *errtext() const { return _etext; };

protected:

private:
	int	_rfds;
	int	_wfds;
	RTRBOOL	_initialized;
	char	*_etext;

#ifdef _WIN32
	RTRBOOL socketpair( int& rfds, int& wfds, int& port, 
	 	    int startport, int maxport );
#endif

private:
// Do not implement
	EVNPipe( const EVNPipe & );
	EVNPipe & operator= ( const EVNPipe & );
};

// End of Pipe


class RTRSigSafeEvNotImp : 
	public RTRIOClient,
	public virtual RTRSafeEventNotifier,
	public virtual RTREvtNotImpl
{
public:

// Constructor
	RTRSigSafeEvNotImp(bool singleton = true);
		// _TAG Constructor

// Desctructor
	virtual ~RTRSigSafeEvNotImp();
		// _TAG Destructor

// From RTREventNotifier && RTRSafeEventNotifier
	virtual void enable();
// Query
	virtual RTRBOOL hasSigSafeControlThread(RTRSigSafeControlThread& client) const;
		// Does the given client exist as a control client
		// at this time?
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// _TAG01 Query

	virtual RTRBOOL unsafeHasSigSafeControlThread(RTRSigSafeControlThread& client) const;
		// Does the given client exist as a control client
		// at this time?
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// _TAG01 Query

	virtual RTRBOOL hasThrdSafeControlThread(RTRThrdSafeControlThread& client);
		// Does the given client exist as a control client
		// at this time?
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// _TAG01 Query

	virtual RTRBOOL unsafeHasThrdSafeControlThread(RTRThrdSafeControlThread& client) const;
		// Does the given client exist as a control client
		// at this time?
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// _TAG01 Query

	virtual RTRBOOL hasUnsafeControlThread(RTRUnsafeControlThread& client) const;
		// Does the given client exist as a control client
		// at this time?
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// _TAG01 Query

// Insert
	virtual void addSigSafeControlThread(RTRSigSafeControlThread& client);
		// Register the given client to be given a notification
		// of control from the notifier.
		// Note - This member function cannot be called from the
		// notifier thread of control. Use zero length timer events
		// in that case.
		// _TAG02 Insert

	virtual void unsafeAddSigSafeControlThread(RTRSigSafeControlThread& client);
		// Register the given client to be given a notification
		// of control from the notifier.
		// Note - This member function cannot be called from the
		// notifier thread of control. Use zero length timer events
		// in that case.
		// _TAG02 Insert

	virtual void addThrdSafeControlThread(RTRThrdSafeControlThread& client);
		// Register the given client to be given a notification
		// of control from the notifier.
		// Note - This member function cannot be called from the
		// notifier thread of control. Use zero length timer events
		// in that case.
		// _TAG02 Insert

	virtual void unsafeAddThrdSafeControlThread(RTRThrdSafeControlThread& client);
		// Register the given client to be given a notification
		// of control from the notifier.
		// Note - This member function cannot be called from the
		// notifier thread of control. Use zero length timer events
		// in that case.
		// _TAG02 Insert

	virtual void addUnsafeControlThread(RTRUnsafeControlThread& client, int priority);
		// Register the given client to be given a notification
		// of control from the notifier.
		// Note - This member function cannot be called from the
		// notifier thread of control. Use zero length timer events
		// in that case.
		// _TAG02 Insert

// Remove
	virtual void dropSigSafeControlThread(RTRSigSafeControlThread& client);
		// Drop the given client as a control client.
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// _TAG03 Remove
	
	virtual void unsafeDropSigSafeControlThread(RTRSigSafeControlThread& client);
		// Drop the given client as a control client.
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// _TAG03 Remove
	
	virtual void dropThrdSafeControlThread(RTRThrdSafeControlThread& client);
		// Drop the given client as a control client.
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// _TAG03 Remove

	virtual void unsafeDropThrdSafeControlThread(RTRThrdSafeControlThread& client);
		// Drop the given client as a control client.
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// _TAG03 Remove

	virtual void dropUnsafeControlThread(RTRUnsafeControlThread& client);
		// Drop the given client as a control client.
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// _TAG03 Remove

// Lock
	virtual void lockThrdSafeControlThread();
		// Lock shared resources.
		// _TAG04 Lock

// Un-Lock
	virtual void unlockThrdSafeControlThread();
		// Un-lock shared resources
		// _TAG05 Un-Lock

protected:

// Functions inherited from RTRIOClient
	void processIORead(int);
	void processIOWrite(int);
	void processIOException(int);

// IO client management
	RTRLiteDLinkList<RTRUnsafeControlThread,RTRDLink7> _controlList;
	RTRLiteDLinkList<RTRSigSafeControlThread,RTRDLink8> _sigControlList;
	RTRLiteDLinkList<RTRThrdSafeControlThread,RTRDLink9> _thrdControlList;

	RTRUnsafeControlThread *_current,*_next;
	RTRSigSafeControlThread *_sigCurrent,*_sigNext;
	RTRThrdSafeControlThread *_thrCurrent,*_thrNext;
	RTRMutex _lock;
	int _controlThreadsPerInvocation;
	EVNPipe	_pipe;

	virtual void extraProc();

private:

// Object Assignment ** DON'T DEFINE THIS!
	RTRSigSafeEvNotImp& operator=(const RTRSigSafeEvNotImp& rhs);

// Copy constructor ** DON'T DEFINE THIS!
	RTRSigSafeEvNotImp(const RTRSigSafeEvNotImp& other);

};

#endif

