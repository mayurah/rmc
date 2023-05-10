//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_ARRAY_NOTIF_IMP 
#define RTR_ARRAY_NOTIF_IMP


#include "rtr/platform.h"
#include "rtr/clinotif.h"
#include "rtr/notifarr.h"

// Synopsis:
//
// Description:
//
// 	"Array" based implementation of a function notifier
//
// 	No virtual functions but not meant to be instantiated, hence the
// 	private constructors.
//
// See Also:
//

template<class R> class RTRArrayNotifier : 
	public virtual RTRClientNotifier<R>
{
private:

// Object Assignment ** DON'T DEFINE THIS!
	RTRArrayNotifier<R>& 
		operator=(const RTRArrayNotifier<R>& rhs);

// Copy Constructor ** DON'T DEFINE THIS!
	RTRArrayNotifier(RTRArrayNotifier<R>& other);

protected:

	RTRNotifierArray<R> *adds;
	RTRNotifierArray<R> *clients;

public:

// Constructor
	RTRArrayNotifier();
		// _TAG Constructor

// Flags
	RTRBOOL notifying;
		// Flag

// From RTRClientNotifier
	int count();
		// _TAG01 From RTRClient Notifier

	void addClient(R *);
        // _TAG01 From RTRClient Notifier

	void dropClient(R *);
        // _TAG01 From RTRClient Notifier

	RTRBOOL hasClient(R *);
        // _TAG01 From RTRClient Notifier

	// _TAG01 From RTRClient Notifier
	RTRBOOL constrained() { return RTRFALSE;};

	int maxClients(){return -1;};
        // _TAG01 From RTRClient Notifier

};


#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("arrnotif.C")
#else
#include "rtr/arrnotif.C"
#endif
#endif

#endif /* RTR_ARRAY_NOTIF_IMP */


