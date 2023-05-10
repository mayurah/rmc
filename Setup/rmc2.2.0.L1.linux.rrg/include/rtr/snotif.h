//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_SIMPLE_NOTIFIER 
#define RTR_SIMPLE_NOTIFIER


#include "rtr/cmdnotif.h"
#include "rtr/clicmd.h"

// Synopsis:
//
// Description:
//
// 	SIMPLE_NOTIFIER
//
// See Also:
//

template<class T> class RTRSimpleNotifier : 
				public RTRCmdNotifier<T>, 
				public RTRClientCmd<T>
{

};


#endif /* RTR_SIMPLE_NOTIFIER */


