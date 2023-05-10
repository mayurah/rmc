//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_ARRAY_CMD_NOTIF_IMP 
#define RTR_ARRAY_CMD_NOTIF_IMP


#include "rtr/platform.h"
#include "rtr/cmdnotif.h"
#include "rtr/arrnotif.h"

// Synopsis:
//
// Description:
//
// 	"Array" based implementation of a function notifier
//
// See Also:
//

template<class R> class RTRArrayCmdNotifier : 
	public RTRArrayNotifier<R>,
	public RTRCmdNotifier<R>
{
private:

// Object Assignment ** DON'T DEFINE THIS!
	RTRArrayCmdNotifier<R>& 
		operator=(const RTRArrayCmdNotifier<R>& rhs);

// Copy Constructor ** DON'T DEFINE THIS!
	RTRArrayCmdNotifier(RTRArrayCmdNotifier<R>& other);

public:

// Constructor
	RTRArrayCmdNotifier(int numClientsExpected);
		// numClientsExpected is a hint. Storage will be resized if necessary.
		// _TAG Constructor

// Destructor
	virtual ~RTRArrayCmdNotifier();
		// _TAG Destructor

// From RTRCmdNotifier
	void notifyClients(RTRClientCmd<R>& cmd);
		// _TAG01 From RTRCmdNotifier

};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("arrcnot.C")
#else
#include "rtr/arrcnot.C"
#endif
#endif


#endif /* RTR_ARRAY_CMD_NOTIF_IMP */


