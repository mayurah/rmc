//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "11/3/97"
// Version: 1.0

#ifndef _thresr_h
#define _thresr_h

#include "rtr/rtllist.h"
#include "rtr/rtstring.h"


// Synopsis:
//	#include "rtr/thresr.h"
//
// Description:
// Used by a RTRThresholdSpecification to identify a range
// of values (min-max) that are valid for a particular region.
// The rearm value is used as a hysteresis to prevent excessive
// triggering when the value fluctuates near the thresholds.
//
// See Also:
//	RTRThresholdRegionIterator, RTRThresholdSpecification
//
// Inherits:
//	RTRDLink0
//

class RTRThresholdRegion :
		public RTRDLink0
{
public:
// Constructor
	RTRThresholdRegion(long min, long max, long rearm, const char *label);
		// REQUIRE: min < max
		// REQUIRE: min < rearm
		// REQUIRE: rearm <= max
		// _TAG Constructor

// Destructor
	~RTRThresholdRegion();
		// _TAG Destructor

// Attributes
	inline long minValue() const;
		// _TAG01 Attributes

	inline long maxValue() const;
		// _TAG01 Attributes

	inline long rearmValue() const;
		// _TAG01 Attributes

	inline const RTRString& label() const;
		// _TAG01 Attributes

protected:
// Data
	long _min;
	long _max;	// threshold
	long _rearm;	// rearm
	RTRString _label;

private:
// Don't define these
	RTRThresholdRegion(const RTRThresholdRegion&);
	RTRThresholdRegion& operator=(const RTRThresholdRegion&);
		// Don't define these
};

inline
long RTRThresholdRegion::minValue() const
{
	return _min;
}

inline
long RTRThresholdRegion::maxValue() const
{
	return _max;
}

inline
long RTRThresholdRegion::rearmValue() const
{
	return _rearm;
}

inline
const RTRString& RTRThresholdRegion::label() const
{
	return _label;
}

#endif
