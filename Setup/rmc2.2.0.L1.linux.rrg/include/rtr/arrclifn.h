//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_ARRAY_CLIENT_FUNCTION_NOTIF_IMP 
#define RTR_ARRAY_CLIENT_FUNCTION_NOTIF_IMP


#include "rtr/platform.h"
#include "rtr/arrnotif.h"

// Synopsis:
//
// Description:
//
// 	"Array" based implementation of a function notifier.
// 	Implements notification using address of client method passed to
// 	the notify routine.
//
// 	Useful when event processing requires one argument which corresponds to
// 	the sender of the event.
//
// See Also:
//

template<class R, class S> class RTRArrClientFuncNotifier : 
	public virtual RTRArrayNotifier<R>
{
private:

// Object Assignment ** DON'T DEFINE THIS!
	RTRArrClientFuncNotifier<R, S>& 
		operator=(const RTRArrClientFuncNotifier<R, S>& rhs);

// Copy Constructor ** DON'T DEFINE THIS!
	RTRArrClientFuncNotifier(RTRArrClientFuncNotifier<R, S>& other);

public:

#ifdef WIN32	/* work around VC++5.0 compiler bug on template */
	RTRArrClientFuncNotifier(int numClientsExpected)
	{
		notifying = RTRFALSE;
		adds = (RTRNotifierArray<R> *)0;
		clients = new RTRNotifierArray<R>(numClientsExpected);
	};
	virtual ~RTRArrClientFuncNotifier()
	{
		if (adds)
			delete adds;
		delete clients;
	};
	void notifyClients(void (R::*f)(S& s), S& s)
	{
		R *c;
		int m = clients->capacity();
		notifying = RTRTRUE;
		for(int i = 0; i < m; i++)
		{
			c = clients->item(i);
			if (!(c == (R *)0))
				(c->*f)(s);
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
	RTRArrClientFuncNotifier(int numClientsExpected);
		// numClientsExpected is a hint. Storage will be resized if necessary.
		// _TAG Constructor

// Destructor
	virtual ~RTRArrClientFuncNotifier();
		// _TAG Destructor

// From RTRFunctionNotifier
	void notifyClients(void (R::*eventFunc)(S& s), S& s);
		// _TAG01 From RTRFunctionNotifier
};


#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("arrclifn.C")
#else
#include "rtr/arrclifn.C"
#endif
#endif

#endif  /* work around VC++5.0 compiler bug on template */

#endif /* RTR_ARRAY_CLIENT_FUNCTION_NOTIF_IMP */


