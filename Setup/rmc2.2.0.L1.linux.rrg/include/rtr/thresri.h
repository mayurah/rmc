//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "11/3/97"
// Version: 1.0

#ifndef _thresri_h
#define _thresri_h

#include "rtr/thresr.h"
#include "rtr/rtllist.h"


// Synopsis:
//	#include "rtr/thresri.h"
//
// Description:
// Provides sequential access to the RTRThresholdRegions defined
// in a RTRThresholdSpecification.
//
// See Also:
//	RTRThresholdRegion, RTRThresholdSpecification
//
// Inherits:
//

class RTRThresholdRegionIterator
{
public:
// Constrctor
	RTRThresholdRegionIterator(
			const RTRDLinkList<RTRThresholdRegion, RTRDLink0>&
			);
		// _TAG Constructor

// Attributes
	int count() const;
		// The number of regions available via this iterator.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete ?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no regions available via this iterator ?
		// ENSURE: result imples count() == 0
		// _TAG02 State

// Access
	RTRThresholdRegion& item() const;
		// The current item in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void finish();
		// Start an iteration from the last available region.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void forth();
		// Continue the current iteration from start() to finish().
		// REQUIRE: !off()
		// _TAG04 Operations

	void back();
		// Continue the current iteration from finish() to start().
		// REQUIRW: !off()
		// _tag04 Operations

protected:
// Data
	const RTRDLinkList<RTRThresholdRegion, RTRDLink0>& _list;
	RTRThresholdRegion *_current;
};

#endif
