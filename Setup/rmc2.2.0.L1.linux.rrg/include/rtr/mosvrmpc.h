//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "May. 07 1995"
// Version: 1.0

#ifndef _mosvrmpc_h
#define _mosvrmpc_h

#include "rtr/mosvrmp.h"
  
// Synopsis:
// #include"rtr/mosvrmpc.h"
//
// Description:
// 	Base class for components wishing to access the global instance of
// 	RTRMOServerMemPool via memPool(). If setMemPool() has not been called, a
// 	reference to an instance of RTRDefaultMOServerMemPool is returned.
//
// See Also:
//	RTRMOServerMemPool
//

class RTRMOServerMemPoolClient
{
public:
	inline void setMemPool(RTRMOServerMemPool&);
		// _TAG01 Other
			
	inline RTRMOServerMemPool& memPool() const;
		// _TAG01 Other

protected:
	static RTRDefaultMOServerMemPool _defaultMemPool;
	static RTRMOServerMemPool *_memPool;
};

inline 
void RTRMOServerMemPoolClient::setMemPool(RTRMOServerMemPool& p)
{
	_memPool = &p;
}

inline 
RTRMOServerMemPool& RTRMOServerMemPoolClient::memPool() const
{
	if ( _memPool )
		return *_memPool;
	else
		return _defaultMemPool;
}

#endif
