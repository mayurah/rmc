//
//|---------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//	author:		Robert Bonaguro
//	created:	May 2, 1994
//	version:	1.0
//

#ifndef __RTR_BUFFER
#define __RTR_BUFFER

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

#include "rtr/rtrdefs.h"
#include "rtr/rtstring.h"
#include "rtr/rthexdmp.h"

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRBuffer :
	public RTRHexDump
{


#ifndef _RDEV_NO_STL_
friend  std::ostream& operator<<(std::ostream& os, RTRBuffer& bbuf)
	// Perform a hex dump of the data stored in the buffer.
{
	RTRString outstring( 5000 );
	bbuf.HexDump( outstring );
	os << outstring.to_c();
	return os;
};
#else
public:
void print(FILE* os)
{
	RTRString outstring( 5000 );
	HexDump( outstring );
	fprintf(os, "%s", outstring.to_c());
};
#endif

protected:

	char	*_area;
	int		_size;
	int		_count;
	RTRBOOL	_allocated;


public:


// Constructor
	RTRBuffer();
		// Create an empty null buffer.
		// _TAG Constructor

	RTRBuffer( int buf_size );
		// _TAG Constructor

	RTRBuffer( const RTRBuffer& );
		// _TAG Constructor

	RTRBuffer( char *memory, int max_size );
		// Construct a buffer using memory
		// for internal storage.
		// _TAG Constructor

// Destructor
	virtual ~RTRBuffer();
		// _TAG Destructor

// Output
	void HexDump(RTRString& aBuffer, int offset=0);
		// _TAG01 Output

// Storage
	inline int capacity();
		// In bytes
		// _TAG02 Storage

	void minimize();
		// Adapt size to accomodate "exactly" count() bytes (or as close as 
		// practical).
		// Copy Data from old buffer to new buffer.
		// REQUIRE : canResize()
        // _TAG02 Storage

	void resize(int newSize);
		// Adapt size to accomodate "exactly" newSize bytes (or as close as 
		// practical). If newSize is < count() truncation will occur.
		// Copy Data from old buffer to new buffer.
		// REQUIRE : canResize()
        // _TAG02 Storage

	void grow(int newSize);
		// Process a hint that newSize bytes may be required.
		// Copy Data from old buffer to new buffer.
		// REQUIRE : canResize()
        // _TAG02 Storage

	void resizeBuffer(int newSize);
		// Adapt size to accomodate "exactly" newSize bytes (or as close as 
		// practical).
		// Data is NOT copied from old buffer.
		// REQUIRE : canResize()
        // _TAG02 Storage


// Comparison
	RTRBOOL operator==(RTRBuffer&);
		// Is other byte-wise identical to Current?
		// _TAG03 Comparison

	RTRBOOL isEqual(char *, int n1, int n2, int position);
		// Are contents of the Current, starting from position, 
		// equal to the contents of other between positions n1 and n2?
		// _TAG03 Comparison


// Transform
	void wipeOut();
		// Re-initialize buffer 
		// This includes zeroing out the buffer memory
		// ENSURE: count() == 0 && readCursor() == 0;
		// _TAG04 Transform

	inline void clear();
		// Clear out the buffer
		// ENSURE: count() == 0 && readCursor() == 0;
        // _TAG04 Transform
	
	void copy(RTRBuffer& other, int n1, int n2);
		// Initialize Current to the contents of other between positions
		// n1 and n2.
		// REQUIRE : n1 >= 1; n1 <= n2; n2 <= other.count()
		// ENSURE : isEqual(other.to_c(1), n1, n2, 1)
        // _TAG04 Transform

// State
	inline int count() const;
		// Number of bytes currently stored.
		// _TAG05 State

	inline RTRBOOL canResize() const;
		// Can the current buffer be resized?
		// _TAG05 State

// Access
	inline char *to_c( int position ) const;
		// Access to character position.
		// TAG06 Access

	inline operator const char *() const;
		// _TAG06 Access

// Setting
	inline void set_count( int new_count );
		// Set the number of bytes currently stored.
		// REQUIRE: new_count <= capacity();
		// _TAG07 Setting

	inline void setMemory(char *mem,int maxSize);
		// Set the memory to be used by this
		// buffer for storage.
		// REQUIRE : !canResize()

};



inline int RTRBuffer::capacity()
{
	return _size;
};

inline void RTRBuffer::clear()
{
	_count = 0;
};

inline int RTRBuffer::count() const
{
	return(_count);
};

inline void RTRBuffer::set_count(int new_size)
{
	RTPRECONDITION( new_size <= capacity() );

	_count = new_size;

	RTPOSTCONDITION( count() == new_size );
};

inline void RTRBuffer::setMemory(char *mem,int maxSize)
{
	RTPRECONDITION(!canResize());
	_area = mem;
	_size = maxSize;
};

inline RTRBOOL RTRBuffer::canResize() const
{
	return(_allocated);
};

inline char *RTRBuffer::to_c( int position ) const
{
	return(_area + position - 1);
};

inline RTRBuffer::operator const char *() const
{
	return _area;
};

#endif
