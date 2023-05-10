//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 11 1995"
// Version: 1.0

#ifndef _random_h
#define _random_h

#include "rtr/rtrdefs.h"

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRRandomNumberGenerator
{
public:
// Constructor
	RTRRandomNumberGenerator();
		// Default range and default seed (gmt seconds of current time).
		// _TAG Constructor

	RTRRandomNumberGenerator(int s);
		// With the given seed
		// REQUIRE: s >= 1
        // _TAG Constructor

	RTRRandomNumberGenerator(long l, long u);
		// With the given range
		// REQUIRE: u >= l
		// ENSURE: upper() == u && lower() == l
        // _TAG Constructor

	RTRRandomNumberGenerator(int s, long l, long u);
		// With the given seed and range
		// REQUIRE: s >= 1
		// REQUIRE: u >= l
		// ENSURE: upper() == u && lower() == l
        // _TAG Constructor

// Attributes
	inline long upper() const;
		// Current upper bound of possible numbers to generate.
		// _TAG01 Attributes

	inline long lower() const;
		// Current lower bound of possible numbers to generate.
		// _TAG01 Attributes

// Access
	inline long value() const;
		// _TAG02 Access

// Transformation
	operator long() const;
		// _TAG03 Transformation

// Operations
	void getNext();
		// Make a new value available
		// _TAG04 Operations

	void setRange(long u, long l);
		// REQUIRE: l >= 0 && u >= l;
		// ENSURE: upper() == u && lower() == l
        // _TAG04 Operations

protected:
	long _lower;
	long _upper;
	long _value;
	long _rawValue;
	unsigned int _seed;
};

inline long RTRRandomNumberGenerator::upper() const {return _upper;}
inline long RTRRandomNumberGenerator::lower() const {return _lower;}
inline long RTRRandomNumberGenerator::value() const {return _value;}

#endif
