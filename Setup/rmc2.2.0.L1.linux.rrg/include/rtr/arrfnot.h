//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_ARRAY_FUNCTION_NOTIF_IMP 
#define RTR_ARRAY_FUNCTION_NOTIF_IMP


#include "rtr/platform.h"
#include "rtr/arrnotif.h"
#include "rtr/fnotif.h"

// Synopsis:
//
// Description:
//
// 	"Array" based implementation of a function notifier
//
// See Also:
//

template<class R, class S> class RTRArrayFunctionNotifier : 
	public virtual RTRArrayNotifier<R>,
	public virtual RTRFunctionNotifier<R, S>
{
private:

// Object Assignment ** DON'T DEFINE THIS!
	RTRArrayFunctionNotifier<R, S>& 
		operator=(const RTRArrayFunctionNotifier<R, S>& rhs);

// Copy Constructor ** DON'T DEFINE THIS!
	RTRArrayFunctionNotifier(RTRArrayFunctionNotifier<R, S>& other);

public:

#ifdef WIN32  /* work around VC++5.0 compiler bug on template */

	RTRArrayFunctionNotifier(int numClientsExpected)
	{
		notifying = RTRFALSE;
		adds = (RTRNotifierArray<R> *)0;
		clients = new RTRNotifierArray<R>(numClientsExpected);
	};

	virtual ~RTRArrayFunctionNotifier()
	{
		if (adds)
			delete adds;
		delete clients;
	};

	void notifyClients(void (S::*callback)(R *r, S *s), S *s)
	{
		R *c;
		int m = clients->capacity();
		notifying = RTRTRUE;
		for(int i = 0; i < m; i++)
		{
			c = clients->item(i);
			if (!(c == (R *)0))
				(s->*callback)(c, s);
		};
		notifying = RTRFALSE;
		// Absorb any clients added during the event.
		if (adds)
		{
			clients->absorb(adds);
			delete adds;
			adds = (RTRNotifierArray<R> *)0;
		}
	};
};

#else 

// Constructor
	RTRArrayFunctionNotifier(int numClientsExpected);
		// numClientsExpected is a hint. Storage will be resized if necessary.
		// _TAG Constructor

// Destructor
	virtual ~RTRArrayFunctionNotifier();
		// _TAG Destructor

// From RTRFunctionNotifier
	void notifyClients(void (S::*callback)(R *r, S *s), S *s);
		// _TAG01 From RTRFunctionNotifier

};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("arrfnot.C")
#else
#include "rtr/arrfnot.C"
#endif
#endif

#endif /* work around VC++5.0 compiler bug on template */

#endif /* RTR_ARRAY_FUNCTION_NOTIF_IMP */


