//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "May. 15 1997"
// Version: 1.0

#ifndef _rtr_glbmodd_h
#define _rtr_glbmodd_h

#include "rtr/lock.h"
#include "rtr/rtllist.h"
#include "rtr/moddict.h"

//
// Synopsis:
// #include "rtr/glbmodd.h"
//
// Description:
// RTRGlobalMODescrDictionary is a utility class which provides "global" access
// to instances of RTRMODescrDictionary.
// 
// See Also:
//	RTRMODescrDictionary
//
// Inherits:
//

class RTRGlobalMODescrDictionary
{ 
public:
// Access
	static RTRMODescrDictionary& dictionary(const RTRObjectId& instanceId);
		// _TAG01 Access

	static RTRMasterDictionary& masterDictionary();
		// _TAG01 Access

protected:
// Data
	static RTRMasterDictionary _masterDictionary;
		// Static Data
}; 

#endif
