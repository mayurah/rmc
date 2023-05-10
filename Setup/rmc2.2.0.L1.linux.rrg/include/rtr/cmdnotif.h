//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_CMD_NOTIFIER 
#define RTR_CMD_NOTIFIER


#include "rtr/clinotif.h"
#include "rtr/clicmd.h"

// Synopsis:
//
// Description:
//
// 	An abstract base class descendant of RTRClientNotifier which assumes that
// 	a isntance of "RTRClientCmd" will be used to propogate events from a Sender
// 	to a Receiver.
// 	An abstract base class descendant of RTRClientNotifier which assumes that
// 	a call-back function will be used to propogate events from a Sender
// 	to a Receiver.
//
// 	The implementation of notifyClients() must iterate over all clients (R) and
// 	invoke the execute() method of the RTRClientCmd with each R.
//
// See Also:
//

template<class R> class RTRCmdNotifier : 
	public virtual RTRClientNotifier<R>
{

public:

	virtual void notifyClients(RTRClientCmd<R>& cmd) = 0;
		// _TAG01 Other

};


#endif /* RTR_CMD_NOTIFIER */


