//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 03 1994"
// Version: 1.0

//
// Definitions for RTRArrayNotifier<R>
//

#include "rtr/rtrdefs.h"

template<class R>
RTRArrayNotifier<R>::RTRArrayNotifier()
{
};

template<class R> 
int RTRArrayNotifier<R>::count()
{
	int result = 0;
	if (adds)
		result += adds->count();
	result += clients->count();
	return result ;
};

template<class R> 
void RTRArrayNotifier<R>::addClient(R *r)
{
	if (notifying)
	{
		if (!adds)
			adds = new RTRNotifierArray<R>(clients->capacity());
		adds->insert(r);
	}
	else
		clients->insert(r);
};

template<class R> 
void RTRArrayNotifier<R>::dropClient(R *r)
{
	int i = clients->indexOf(r);
	if (i >= 0)
		clients->removeItemAt(i);
	else
	{
		if (adds)
			adds->remove(r);
	};
};

template<class R> 
RTRBOOL RTRArrayNotifier<R>::hasClient(R *r)
{
	RTRBOOL result = clients->has(r);

	if (!result && (adds))
		result = adds->has(r);

	return result;
};
