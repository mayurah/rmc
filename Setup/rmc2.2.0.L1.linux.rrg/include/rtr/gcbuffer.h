//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Nov. 30 1995"
// Version: 1.0

#ifndef _gcbuffer_h
#define _gcbuffer_h

#include "rtr/rtbuffer.h"
#include "rtr/gc.h"

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRGCBuffer :
	public RTRBuffer,
	public RTRGCObj
{ 
public:
// Constructor
	RTRGCBuffer();
		// _TAG Constructor

	RTRGCBuffer(int buf_size);
		// _TAG Constructor

	RTRGCBuffer(const RTRBuffer&);
		// _TAG Constructor

// Destructor
	virtual ~RTRGCBuffer();
		// _TAG Destructor

}; 

#endif
