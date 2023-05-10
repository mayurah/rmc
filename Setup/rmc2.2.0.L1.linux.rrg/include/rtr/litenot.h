//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_LITE_NOTIFIER 
#define RTR_LITE_NOTIFIER


#include "rtr/platform.h"
#include "rtr/fnotif.h"

// Synopsis:
//
// Description:
//
// 	Event (Function) Notifier implementation
//
// 	Light wieght - constrained to a single client.
//
// See Also:
//

template<class R, class S> class RTRLiteNotifier
	: public RTRFunctionNotifier<R, S>
{
private:

// Object Assignment ** DON'T DEFINE THIS!
	RTRLiteNotifier<R, S>& operator=(const RTRLiteNotifier<R, S>& rhs);

// Copy Constructor ** DON'T DEFINE THIS!
	RTRLiteNotifier(RTRLiteNotifier<R, S>& other);

protected:

	R *singleClient;

public:

	// _TAG01 Other
	RTRBOOL constrained() { return RTRTRUE;} ;

	// _TAG01 Other
	int maxClients() {return 1;};

#ifdef WIN32  // work around VC++5.0 compiler bug on template

	RTRLiteNotifier()
	{
		singleClient = (R *)0;
	};

	int count()
	{
		return singleClient ? 1 : 0;
	};

	void addClient(R *r)
	{
		RTPRECONDITION( count() == 0 );
	
		singleClient = r;
	};

	void dropClient(R *r)
	{
		if (singleClient == r)
			singleClient = (R *)0;
	}; 

	RTRBOOL hasClient(R *r)
	{
		return (singleClient == r);
	};

	void notifyClients(void (S::*callback)(R *r, S *s), S *s)
	{
		if (count() == 1)
			(s->*callback)(singleClient, s);
	};

};

#else

// Constructor
	RTRLiteNotifier();
		// _TAG Constructor

	int count();
		// _TAG01 Other

	void addClient(R *);
		// _TAG01 Other

	void dropClient(R *);
		// _TAG01 Other

	RTRBOOL hasClient(R *);
		// _TAG01 Other

// Event propogation
	void notifyClients(void (S::*callback)(R *r, S *s), S *s);
		// _TAG02 Event propogation

};

#ifdef __INCLUDE_TEMPLATE_IMPL__
#ifdef __CSET__
#pragma implementation("litenot.C")
#else
#include "rtr/litenot.C"
#endif
#endif

#endif  // work around VC++5.0 compiler bug on template

#endif /* RTR_LITE_NOTIFIER */


