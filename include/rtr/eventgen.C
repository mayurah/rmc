//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jun. 15 1998"
// Version: 1.0

#include "rtr/eventgen.h"

template <class G, class C>
RTREventGenerator<G, C>::RTREventGenerator()
	: _notifying(RTRFALSE)
{
}

template <class G, class C>
RTREventGenerator<G, C>::~RTREventGenerator()
{
	_clients.removeAllAndDestroy();
	_tmp.removeAllAndDestroy();
}


template <class G, class C>
int RTREventGenerator<G, C>::count() const
{
	return _clients.count() + _tmp.count();
}

template <class G, class C>
RTRBOOL RTREventGenerator<G, C>::hasClient(const C& client) const
{
	RTREventGenLink<C>* l = 0;
	for ( l = _clients.first(); l; l = _clients.next(l) )
	{
		if ( &l->client() == &client )
			break;
	}
	if ( !l )
	{
		for ( l = _tmp.first(); l; l = _tmp.next(l) )
		{
			if ( &l->client() == &client )
				break;
		}
	}
	return l != 0;
}

template <class G, class C>
RTRDLinkList< RTREventGenLink<C>, RTRDLink0>& 
RTREventGenerator<G, C>::clients() const
{
	RTREventGenerator<G, C> * nct = (RTREventGenerator<G, C> *)this;
	return nct->_clients;
}

template <class G, class C>
void RTREventGenerator<G, C>::addClient(const C& client)
{
	RTPRECONDITION( !hasClient(client) );

	if ( !_notifying )
		_clients.putLast(new RTREventGenLink<C>(client));
	else
		_tmp.putLast(new RTREventGenLink<C>(client));

	RTPOSTCONDITION ( hasClient(client) );
}

template <class G, class C>
void RTREventGenerator<G, C>::dropClient(const C& client)
{
	RTREventGenLink<C>* l = 0;
	RTRBOOL found = RTRFALSE;
	for ( l = _clients.first(); l; l = _clients.next(l) )
	{
		if ( &l->client() == &client )
		{
			_clients.remove(l);
			delete l;
			found = RTRTRUE;
			break;
		}
	}
	for ( l = _tmp.first(); l && !found ; l = _tmp.next(l) )
	{
		if ( &l->client() == &client )
		{
			_tmp.remove(l);
			delete l;
			break;
		}
	}

	RTPOSTCONDITION ( !hasClient(client) );
}

#ifndef WIN32 /* work around VC++ 5.0 compiler bug */

template <class G, class C>
void RTREventGenerator<G, C>::notify(void (G::*callback)(C&), G& g)
{
	_notifying = RTRTRUE;
	for ( RTREventGenLink<C>* l = _clients.first(); l; )
	{
		RTREventGenLink<C>* n = _clients.next(l);
		((&g)->*callback)(l->client());
		l = n;
	}
	_clients.append(&_tmp);
	_notifying = RTRFALSE;
}

	// OBSOLETE
template <class G, class C>
void RTREventGenerator<G, C>::notify(void (G::*callback)(C&))
{
	_notifying = RTRTRUE;
	for ( RTREventGenLink<C>* l = _clients.first(); l; )
	{
		RTREventGenLink<C>* n = _clients.next(l);
		(((G*)this)->*callback)(l->client());
		l = n;
	}
	_clients.append(&_tmp);
	_notifying = RTRFALSE;
}

#endif /* work around VC++ 5.0 compiler bug */
