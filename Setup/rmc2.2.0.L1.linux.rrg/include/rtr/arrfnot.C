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
// Definitions for RTRArrayFunctionNotifier<R, S>
//

template<class R, class S> 
RTRArrayFunctionNotifier<R, S>::RTRArrayFunctionNotifier(int numClientsExpected)
{
	this->notifying = RTRFALSE;
	this->adds = (RTRNotifierArray<R> *)0;
	this->clients = new RTRNotifierArray<R>(numClientsExpected);
};

template<class R, class S> 
RTRArrayFunctionNotifier<R, S>::~RTRArrayFunctionNotifier()
{
	if (this->adds)
		delete this->adds;
	delete this->clients;
};

template<class R, class S> 
void RTRArrayFunctionNotifier<R, S>::notifyClients(void (S::*callback)(R *r, S *s), S *s)
{
	R *c;
	int m = this->clients->capacity();
	this->notifying = RTRTRUE;
	for(int i = 0; i < m; i++)
	{
		c = this->clients->item(i);
		if (!(c == (R *)0))
			(s->*callback)(c, s);
	};
	this->notifying = RTRFALSE;
		// Absorb any clients added during the event.
	if (this->adds)
	{
		this->clients->absorb(this->adds);
		delete this->adds;
		this->adds = (RTRNotifierArray<R> *)0;
	}
};

