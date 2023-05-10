//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: J. Arvanites
// Created: "Jun. 1 1998"
// Version: 1.0

#ifndef __rtr_bitmap_h__
#define __rtr_bitmap_h__

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

#include "rtr/rtrdefs.h"
#include "rtr/rtdataty.h"

// Synopsis:
//
// Description:
//
//  A simple implementation of a bitmap.
//  You can set/clear and dynamically resize.
//
// See Also:
//

class RTRBitmap
{
public:
// Constructor
	RTRBitmap(u_32 bits = 32);
		// _TAG Constructor

	RTRBitmap(const RTRBitmap &b2);
		// _TAG Constructor

// Destructor
	virtual ~RTRBitmap();
		// _TAG Destructor

// Query
	RTRBOOL bit(u_32 offset) const;
		// _TAG01 Query

	RTRBOOL isSubsetOf(const RTRBitmap &b2) const;
		// _TAG01 Query

	RTRBOOL isEmpty();
		// _TAG01 Query

// Attributes
	u_32 size() { return _bits; }
		// _TAG02 Attributes

	u_32 bytes() { return _bytes; }
		// _TAG02 Attributes

	u_32 count() const;
		// _TAG02 Attributes

// Operations
	void set(u_32 offset);
		// _TAG03 Operations

	void clear(u_32 offset);
		// _TAG03 Operations

	void clearAll();
		// _TAG03 Operations

	void setAll();
		// _TAG03 Operations

// Resize
	void resize(u_32 bits);
		// _TAG04 Resize

// Operators
	RTRBitmap& operator&=(const RTRBitmap &b2);
		// bitwise AND
		// _TAG05 Operators

	RTRBitmap& operator|=(const RTRBitmap &b2);
		// bitwise OR
		// _TAG05 Operators

	RTRBitmap& operator^=(const RTRBitmap &b2);
		// bitwise XOR
		// _TAG05 Operators

	RTRBitmap& operator-=(const RTRBitmap &b2);
		// difference
		// _TAG05 Operators

	RTRBitmap& operator=(const RTRBitmap &b2);
		// assignment
		// _TAG05 Operators

// Comparision
	RTRBOOL operator==(const RTRBitmap &b2);
		// _TAG06 Comparision

	RTRBOOL operator!=(const RTRBitmap &b2);
		// _TAG06 Comparision

// Transformation
	RTRBitmap& invert();
		// flips all bits
		// _TAG07 Transformation

// Output
#ifndef _RDEV_NO_STL_
	std::ostream& print(std::ostream& os) const;
#else
	void print(FILE* os) const;
#endif
		// _TAG08 Output

protected:

	void needToGrow(const RTRBitmap &b2);

	u_32 _bits;
	u_32 _bytes;
	u_8 *_area;
};

#ifndef _RDEV_NO_STL_
inline std::ostream& operator<<(std::ostream &s, const RTRBitmap &b)
{
	return b.print(s);
}
#endif

#endif
