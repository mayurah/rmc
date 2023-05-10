//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Feb. 07 1994"
// Version: 1.0
 
#ifndef RTR_EVENT_NOTIFIER_INIT
#define RTR_EVENT_NOTIFIER_INIT

#include "rtr/evtnotif.h"

// Synopsis:
//
// Description:
// 
// See Also:
//

class RTREventNotifierInit
{
private:
	static unsigned short count;
	   
	static RTREventNotifier* newNotifier();
			
public:
			 
// Constructor
	RTREventNotifierInit();
		// _TAG Constructor

// Destructor
	~RTREventNotifierInit();
		// _TAG Destructor

	static RTREventNotifier *notifier;
							
};


// Export a function to allow DACS's DLL obtain access to the RTREventNotifier
#ifdef _WIN32
#include "rtr/os.h"
#ifdef __cplusplus
extern "C" {
#endif
RTR_API_EXPORT RTREventNotifier *getGlobalEventNotifier();
#ifdef __cplusplus
}
#endif
#endif // _WIN32
							 
#endif /* RTR_EVENT_NOTIFIER_INIT */

