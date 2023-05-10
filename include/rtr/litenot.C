//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 03 1994"
// Version: 1.0

template<class R, class S> 
RTRLiteNotifier<R, S>::RTRLiteNotifier()
{
	singleClient = (R *)0;
};

template<class R, class S> 
int RTRLiteNotifier<R, S>::count()
{
	return singleClient ? 1 : 0;
};

template<class R, class S> 
void RTRLiteNotifier<R, S>::addClient(R *r)
{
	RTPRECONDITION( count() == 0 );

	singleClient = r;
};

template<class R, class S> 
void RTRLiteNotifier<R, S>::dropClient(R *r)
{
	if (singleClient == r)
		singleClient = (R *)0;
};

template<class R, class S> 
RTRBOOL RTRLiteNotifier<R, S>::hasClient(R *r)
{
	return (singleClient == r);
};

template<class R, class S>
void RTRLiteNotifier<R,S>::notifyClients(void (S::*callback)(R *r, S *s), S *s)
{
	if (count() == 1)
		(s->*callback)(singleClient, s);
};

