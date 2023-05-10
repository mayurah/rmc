//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: M. Schwenk
// Created: "Feb. 3 1995"
// Version: 1.0

#ifndef __spinit_h__
#define __spinit_h__

#include "rtr/indxable.h"

// Synopsis:
//
// Description:
//
// 	An abstract base class for iterating over sparse indexable containers.
//
// See Also:
//

class RTRSparseIndexableIterator :
	public RTRIndexableIterator
{
public:
// Constructor
	RTRSparseIndexableIterator(const RTRIndexableStore&);
		// _TAG Constructor

// Destructor
	virtual ~RTRSparseIndexableIterator();
		// _TAG Destructor

// From RTRIndexableIterator
// Operations
	virtual void start();
		// Make the first valid service available as service(); 
		// _TAG01 Operations -- from RTRIndexableIterator

	virtual void finish();
		// Make the last valid service available as service(); 
        // _TAG01 Operations -- from RTRIndexableIterator

	virtual void forth();
		// Make the next valid service available as service(); 
        // _TAG01 Operations -- from RTRIndexableIterator

	virtual void back();
		// Make the next valid service available as service(); 
        // _TAG01 Operations -- from RTRIndexableIterator

};

#endif
