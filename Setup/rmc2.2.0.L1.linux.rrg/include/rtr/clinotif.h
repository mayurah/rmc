//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_CLIENT_NOTIFIER 
#define RTR_CLIENT_NOTIFIER


#include "rtr/rtrdefs.h"

// Synopsis:
//
// Description:
//
// 	Absract base class by which clients can register/de-register to receive
//	events. No implementation assumed
//
// 	The implementation must handle cases where propagation of an event causes
// 	clients to register or de-register (add/drop) during the event.
//
// 	Clients which drop during the event but before they are notified will not
// 	receive the event.
//
// 	Clients which add during the event will not be receive the event.
//
// See Also:
//

template<class T> class RTRClientNotifier
{

public:

	virtual int count() = 0;
		// The number of clients currently registered.
		// _TAG01 Other

	virtual void addClient(T *t) = 0;
		// Ensure that client t receives subsequent events.
		// REQUIRE : constained == FALSE OR ELSE
		//            count() < maxClients()
		// ENSURE : hasClient(t)
		// _TAG01 Other

	virtual void dropClient(T *) = 0;
		// Ensure that client t does not receive any more events.
		// REQUIRE : hasClient(t)
		// ENSURE : ! hasClient(t)
		// _TAG01 Other

	virtual RTRBOOL hasClient(T *t) = 0;
		// Is client t registered to receive events?
		// _TAG01 Other

	virtual RTRBOOL constrained() = 0;
		// Is this notifier constrained in the number of clients which may
		// register?
		// _TAG01 Other

	virtual int maxClients() = 0;
		// If constrained, the maximum number of clients allowed for this
		// notifier.
		// REQUIRE : constrained()
		// _TAG01 Other

};


#endif /* RTR_CLIENT_NOTIFIER */


