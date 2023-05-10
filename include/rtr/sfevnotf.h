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
//  created:       September 17, 1996
//  version:       1.0
//

#ifndef _sfevnotf_h
#define _sfevnotf_h

#include "rtr/evtnotif.h"
#include "rtr/linkl.h"

class RTRControlThread;
class RTRUnsafeControlThread;
class RTRSigSafeControlThread;
class RTRThrdSafeControlThread;

// Synopsis:
//
// Description:
// A RTRSafeEventNotifier is-a RTREventNotifier that adds the
// functionality for threads of control outside the notifiers
// control to get the notifiers thread of control.
//
// Note - Do not mix signals and threads as RTRControlThreads. 
//
// See Also:
//

class RTRSafeEventNotifier :
	public virtual RTREventNotifier
{
public:

// instance
	static RTRSafeEventNotifier * instance;
		// If a descendant of this class is created as
		// a notifier. It must set this instance
		// value for classes to access this specilization
		// of the notifier.

// Destructor
	virtual ~RTRSafeEventNotifier() ;
		// _TAG Destructor

// Query
	virtual RTRBOOL hasSigSafeControlThread(RTRSigSafeControlThread& client) const = 0;
		// Does the given client exist as a control client
		// at this time?
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// REQUIRE : !client.isControlThread()
		// _TAG01 Query

	virtual RTRBOOL unsafeHasSigSafeControlThread(RTRSigSafeControlThread& client) const = 0;
		// Does the given client exist as a control client
		// at this time?
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// REQUIRE : !client.isControlThread()
		// _TAG01 Query

	virtual RTRBOOL hasThrdSafeControlThread(RTRThrdSafeControlThread& client) = 0;
		// Does the given client exist as a control client
		// at this time?
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// REQUIRE : !client.isControlThread()
		// _TAG01 Query

	virtual RTRBOOL unsafeHasThrdSafeControlThread(RTRThrdSafeControlThread& client) const = 0;
		// Does the given client exist as a control client
		// at this time?
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// REQUIRE : !client.isControlThread()
		// _TAG01 Query

	virtual RTRBOOL hasUnsafeControlThread(RTRUnsafeControlThread& client) const = 0;
		// Does the given client exist as a control client
		// at this time?
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// REQUIRE : !client.isControlThread()
		// _TAG01 Query

// Insert
	virtual void addSigSafeControlThread(RTRSigSafeControlThread& client) = 0;
		// Register the given client to be given a notification
		// of control from the notifier.
		// Note - This member function cannot be called from the
		// notifier thread of control. Use zero length timer events
		// in that case.
		// REQUIRE : !client.isControlThread()
		// REQUIRE : !client.isControlClient()
		// _TAG02 Insert
	
	virtual void unsafeAddSigSafeControlThread(RTRSigSafeControlThread& client) = 0;
		// Register the given client to be given a notification
		// of control from the notifier.
		// Note - This member function cannot be called from the
		// notifier thread of control. Use zero length timer events
		// in that case.
		// REQUIRE : !client.isControlThread()
		// REQUIRE : !client.isControlClient()
		// _TAG02 Insert
	
	virtual void addThrdSafeControlThread(RTRThrdSafeControlThread& client) = 0;
		// Register the given client to be given a notification
		// of control from the notifier.
		// Note - This member function cannot be called from the
		// notifier thread of control. Use zero length timer events
		// in that case.
		// REQUIRE : !client.isControlThread()
		// REQUIRE : !client.isControlClient()
		// _TAG02 Insert

	virtual void unsafeAddThrdSafeControlThread(RTRThrdSafeControlThread& client) = 0;
		// Register the given client to be given a notification
		// of control from the notifier.
		// Note - This member function cannot be called from the
		// notifier thread of control. Use zero length timer events
		// in that case.
		// REQUIRE : !client.isControlThread()
		// REQUIRE : !client.isControlClient()
		// _TAG02 Insert

	virtual void addUnsafeControlThread(RTRUnsafeControlThread& client, int priority) = 0;
		// Register the given client to be given a notification
		// of control from the notifier.
		// Note - This member function cannot be called from the
		// notifier thread of control. Use zero length timer events
		// in that case.
		// REQUIRE : !client.isControlThread()
		// REQUIRE : !client.isControlClient()
		// _TAG02 Insert

// Remove
	virtual void dropSigSafeControlThread(RTRSigSafeControlThread& client) = 0;
		// Drop the given client as a control client.
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// REQUIRE : !client.isControlThread()
		// REQUIRE : client.isControlClient()
		// _TAG03 Remove

	virtual void unsafeDropSigSafeControlThread(RTRSigSafeControlThread& client) = 0;
		// Drop the given client as a control client.
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// REQUIRE : !client.isControlThread()
		// REQUIRE : client.isControlClient()
		// _TAG03 Remove
	
	virtual void dropThrdSafeControlThread(RTRThrdSafeControlThread& client) = 0;
		// Drop the given client as a control client.
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// REQUIRE : !client.isControlThread()
		// REQUIRE : client.isControlClient()
		// _TAG03 Remove

	virtual void unsafeDropThrdSafeControlThread(RTRThrdSafeControlThread& client) = 0;
		// Drop the given client as a control client.
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// REQUIRE : !client.isControlThread()
		// REQUIRE : client.isControlClient()
		// _TAG03 Remove

	virtual void dropUnsafeControlThread(RTRUnsafeControlThread& client) = 0;
		// Drop the given client as a control client.
		// Note - This member function cannot be called from the
		// notifier thread of control within a processControl()
		// callback.
		// REQUIRE : !client.isControlThread()
		// REQUIRE : client.isControlClient()
		// _TAG03 Remove

// Lock
	virtual void lockThrdSafeControlThread() = 0;
		// Lock shared resources.
		// _TAG04 Lock

// Un-Lock
	virtual void unlockThrdSafeControlThread() = 0;
		// Un-lock shared resources
		// _TAG05 Un-Lock

protected:

// Implementation
	inline void setControlClient(RTRControlThread&);
	inline void clearControlClient(RTRControlThread&);
	inline void setControlThread(RTRControlThread&);
	inline void clearControlThread(RTRControlThread&);
	inline int priority(RTRUnsafeControlThread&);
	inline void setPriority(RTRUnsafeControlThread&, int priority);

		// _TAG06 Implementation

};


// Synopsis:
//
// Description:
//
// See Also:
//

class RTRControlThread 
{
public:

// Constructor
	RTRControlThread();

// Destructor
	virtual ~RTRControlThread();
		// _TAG Destructor

// Attributes
	inline RTRBOOL isControlClient() { return(_isControlClient); };
		// Is current a control thread client?
		// _TAG01 Attributes

	inline RTRBOOL isControlThread() { return(_isControlThread); };
		// Is current the current notifying control thread?
		// i.e is it within its processControlThread() callback?
		// _TAG01 Attributes

protected:

	RTRBOOL		_isControlClient;
	RTRBOOL		_isControlThread;

// Friend Definitions
friend class RTRSafeEventNotifier;
};

class   RTRSigSafeControlThread:
			public RTRDLink8,
			public RTRControlThread
{

public:
// Constructor
	RTRSigSafeControlThread(){};

// Destructor
	~RTRSigSafeControlThread(){};
	// _TAG Destructor

// Events

	virtual RTRBOOL processSigSafeControlThread() = 0;

	// The main thread of control is being given to
	// you. Return whether or not you still want
	// to be a control client. Since the return
	// value informs the notifier whether or not
	// you are still a client. It does not make sense
	// to call addControlThread() or dropControlThread()
	// within this thread on control.
	// REQUIRE : isControlClient()
	// REQUIRE : isControlThread()
	// _TAG01 Other
// Friend Definitions
friend class RTRSafeEventNotifier;
};

class   RTRThrdSafeControlThread:
			public RTRDLink9,
			public RTRControlThread
{

public:
// Constructor
	RTRThrdSafeControlThread(){};

// Destructor
	~RTRThrdSafeControlThread(){};
	// _TAG Destructor

// Events
	virtual RTRBOOL processThrdSafeControlThread() = 0;

	// The main thread of control is being given to
	// you. Return whether or not you still want
	// to be a control client. Since the return
	// value informs the notifier whether or not
	// you are still a client. It does not make sense
	// to call addControlThread() or dropControlThread()
	// within this thread on control.
	// REQUIRE : isControlClient()
	// REQUIRE : isControlThread()
	// _TAG01 Other
	// Friend Definitions

friend class RTRSafeEventNotifier;
};

class   RTRUnsafeControlThread:
			public RTRDLink7,
			public RTRControlThread
{

public:
// Constructor
	RTRUnsafeControlThread(){};

// Destructor
	~RTRUnsafeControlThread(){};
	// _TAG Destructor

// Events
	virtual RTRBOOL processUnsafeControlThread() = 0;

	// The main thread of control is being given to
	// you. Return whether or not you still want
	// to be a control client. Since the return
	// value informs the notifier whether or not
	// you are still a client. It does not make sense
	// to call addControlThread() or dropControlThread()
	// within this thread on control.
	// REQUIRE : isControlClient()
	// REQUIRE : isControlThread()
	// _TAG01 Other
	// Friend Definitions

private:

	int _priority;

friend class RTRSafeEventNotifier;
};



inline void RTRSafeEventNotifier::setControlClient(RTRControlThread& ct)
{
	ct._isControlClient = RTRTRUE;
};

inline void RTRSafeEventNotifier::clearControlClient(RTRControlThread& ct)
{
	ct._isControlClient = RTRFALSE;
};

inline void RTRSafeEventNotifier::setControlThread(RTRControlThread& ct)
{
	ct._isControlThread = RTRTRUE;
};

inline void RTRSafeEventNotifier::clearControlThread(RTRControlThread& ct)
{
	ct._isControlThread = RTRFALSE;
};

inline int RTRSafeEventNotifier::priority(RTRUnsafeControlThread& ct)
{
	return(ct._priority);
};

inline void RTRSafeEventNotifier::setPriority(RTRUnsafeControlThread& ct, int priority)
{
	ct._priority = priority;
};

#endif

