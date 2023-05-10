//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: J. Arvanites
// Created: "Jun. 1 1998"
// Version: 1.0

#ifndef __rtr_cbitmap_h__
#define __rtr_cbitmap_h__

#include "rtr/rtrdefs.h"
#include "rtr/rtbitmap.h"

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

// Synopsis:
//
// Description:
//
//  A composite bitmap.  Allows bit <= 0 nad bit > 0.
//
// See Also:
//

class RTRSignedBitmap
{
public:
// Constructor
	RTRSignedBitmap( unsigned long bits = 64, unsigned long nbits = 0 );
		// _TAG Constructor

	RTRSignedBitmap( const RTRSignedBitmap &bitmap );
		// _TAG Constructor

// Destructor
	~RTRSignedBitmap();
		// _TAG Destructor

// Query
	RTRBOOL bit( int offset ) const;
		// _TAG01 Query

	RTRBOOL isSubsetOf(const RTRSignedBitmap  &b2) const;
		// _TAG01 Query

// Attributes
	inline unsigned long size() const;
		// _TAG02 Attributes


// Operations
	unsigned int count() const;
		// _TAG02 Operations

	void set( int offset );
		// _TAG03 Operations

	void clear( int offset );
		// _TAG03 Operations

	void clearAll();
		// _TAG03 Operations

	void setAll();
		// _TAG03 Operations

// Resize
	void resize( unsigned long bits, unsigned long nbits = 0 );
		// _TAG04 Resize

// Operators
	RTRSignedBitmap &operator&=(const RTRSignedBitmap &);
		// bitwise AND
		// _TAG05 Operators

	RTRSignedBitmap &operator|=(const RTRSignedBitmap &);
		// bitwise OR
		// _TAG05 Operators

	RTRSignedBitmap &operator^=(const RTRSignedBitmap &);
		// bitwise XOR
		// _TAG05 Operators

	RTRSignedBitmap &operator-=(const RTRSignedBitmap &);
		// difference
		// _TAG05 Operators

	RTRSignedBitmap &operator=(const RTRSignedBitmap &);
		// assignment
		// _TAG05 Operators

	inline RTRSignedBitmap &invert();
		// flips all bits
		// _TAG05 Operators
		
// Output
#ifndef _RDEV_NO_STL_
	std::ostream & print( std::ostream& os ) const;
#else
	void print( FILE* os ) const;
#endif
		// _TAG05 Transformation

protected:
	RTRBitmap *positive;
	RTRBitmap *negative;
	RTRBOOL zero;
};

inline unsigned long RTRSignedBitmap::size() const
{
	return(negative ? (positive->size() + negative->size() + 1) : (positive->size()+1));
}

inline RTRSignedBitmap &RTRSignedBitmap::invert()
{
	zero = !zero;
	positive->invert();
	if ( negative )
		negative->invert();
	return *this;
}

#ifndef _RDEV_NO_STL_
inline std::ostream & operator<<(std::ostream &s, const RTRSignedBitmap & b )
{
	return b.print(s);
}
#endif

#endif

