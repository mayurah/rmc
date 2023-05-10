//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 03 1994"
// Version: 1.0

#include "rtr/rtrdefs.h"
#include "rtr/clicmd.h"

//
// Definitions for RTRArrayCmdNotifier<R>
//

template<class R> 
RTRArrayCmdNotifier<R>::RTRArrayCmdNotifier(int numClientsExpected)
{
	notifying = RTRFALSE;
	adds = (RTRNotifierArray<R> *)0;
	clients = new RTRNotifierArray<R>(numClientsExpected);
};

template<class R> 
RTRArrayCmdNotifier<R>::~RTRArrayCmdNotifier()
{
	if (adds)
		delete adds;
	delete clients;
};

template<class R> 
void RTRArrayCmdNotifier<R>::notifyClients(RTRClientCmd<R>& cmd)
{
	R *c;
	int m = clients->capacity();
	notifying = RTRTRUE;
	for(int i = 0; i < m; i++)
	{
		c = clients->item(i);
		if (!(c == (R *)0))
			cmd.execute(*c);
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

