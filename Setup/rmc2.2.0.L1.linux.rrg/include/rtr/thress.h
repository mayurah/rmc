//|---------------------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "11/3/97"
// Version: 1.0

#ifndef _thress_h
#define _thress_h

#include "rtr/thresr.h"
#include "rtr/thresri.h"
#include "rtr/rtllist.h"


// Synopsis:
//	#include "rtr/thress.h"
//
// Description:
// Specifies a set of regions that are used to delineate the range of values of 
// a Numeric variable. 
// The format of the specification consists of a set of space separated
// threshold/rearm values.  The threshold/rearm values consist of 
// a comma separated pair of long values (threashold,rearm);
// e.g. "20,18 60,58 80,78" will generate a threshold specification with
// 4 regions.
//
//  \verbatim
// region    min     max     rearm
//   1    LONG_MIN   20       18
//   2       20      60       58
//   3       60      80       78
//   4       80    LONG_MAX LONG_MAX
//  \endverbatim
//
//
// The labels parameter consists of a set of space separated labels
// for each region.  If n thresholds are specified then n+1 labels
// need to be provided.  Default values for the labels are 
// "region_1", "region_2", "region_3", ...
// For example "Idle Normal Burdened Busy" is an example of 4 labels for the
// 3 thresholds specified earlier.
//
// See Also:
// 	RTRThresholdRegion, RTRThresholdRegionIterator
//
// Inherits:
//

class RTRThresholdSpecification
{
public:
// Constructor
	RTRThresholdSpecification(const char *specification);
		// _TAG Constructor

	RTRThresholdSpecification(const char *specification, const char *labels);
		// _TAG Constructor

	RTRThresholdSpecification(const RTRThresholdSpecification& spec);
		// REQUIRE: !spec.error()
		// _TAG Constructor

// Destructor
	~RTRThresholdSpecification();
		// _TAG Destructor

// Attributes
	inline const RTRString& text() const;
		// _TAG01 Attributes

// State
	inline RTRBOOL error() const;
		// _TAG02 State

// Access -- sequential
	RTRThresholdRegionIterator regions() const;
		// _TAG03 Access -- sequential

protected:
// Operations
	void init(const char *spec, const char *labels=0);
	void addRegion(long min, long max, long rearm, const RTRString& label);

// Data
	RTRDLinkList<RTRThresholdRegion, RTRDLink0> _regions;
	RTRBOOL _error;
	RTRString _text;

private:
// Don't define these
	RTRThresholdSpecification& operator=(const RTRThresholdSpecification&);
		// Don't define these
};

inline
const RTRString& RTRThresholdSpecification::text() const
{
	return _text;
}

inline
RTRBOOL RTRThresholdSpecification::error() const
{
	return _error;
}

#endif
