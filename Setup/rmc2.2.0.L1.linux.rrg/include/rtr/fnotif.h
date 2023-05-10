//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_FUNCTION_NOTIFIER 
#define RTR_FUNCTION_NOTIFIER


#include "rtr/clinotif.h"

// Synopsis:
//
// Description:
//
// 	An abstract base class descendant of RTRClientNotifier which assumes that
// 	a call-back function will be used to propogate events from a Sender
// 	to a Receiver.
//
// 	The implementation of notifyClients() must iterate over all clients (R) and
// 	invoke the call-back with each R and S, the event "sender".
//
// See Also:
//

template<class R, class S> class RTRFunctionNotifier : 
	public virtual RTRClientNotifier<R>
{

public:

	virtual void notifyClients(void (S::*callback)(R *r, S *s), S *s) = 0;
		// _TAG01 Other

};


#endif /* RTR_FUNCTION_NOTIFIER */


