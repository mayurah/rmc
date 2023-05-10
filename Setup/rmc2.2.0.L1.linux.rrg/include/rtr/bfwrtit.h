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
//	created:	April 29, 1994
//	version:	1.0
//

#ifndef __RTR_BUFFER_WRITE_ITERATOR
#define __RTR_BUFFER_WRITE_ITERATOR

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif
#include <memory.h>

#include "rtr/rtrdefs.h"
#include "rtr/rtdataty.h"
#include "rtr/rtstring.h"
#include "rtr/objid.h"
#include "rtr/smallstr.h"
#include "rtr/eli_net.h"
#include "rtr/rtbuffer.h"

// Synopsis:
// #include "rtr/bfwrtit.h"
// 
// "//"RTRBuffer& _buffer;
// RTRString _msgString("This is message text");
// u_16      _msgOpcode = 45;
// RTRBufferWriteIterator writeIt(buffer);
// writeIt.appendUnsigned16(_msgOpcode);
// writeIt.appendUnsigned32(_msgString.count());
// writeIt.appendString(_msgString);
//
// Description:
//	RTRBufferWriteIterator provides methods used to format
//	data into an instance of RTRBuffer.
// 
//	The formatting methods of a message write iterator allow the
//	user to write several different types of data into a message,
//	like different sized numerics, strings, characters and boolean
//	values. Byte swapping is handled automatically so that data
//	written can be properly read on machines with different byte
//	ordering.
//
//	Upon obtaining an instance of RTRBufferWriteIterator, the user
//	calls the various "append" and "put" methods to write data into
//	the underlying message associated with the iterator. When the
//	user is finished formatting data into the buffer, the
//	writingCompleted() method is invoked to reset the count of
//	the underlying buffer.
//
// See Also:
//	RTRBuffer, RTRBufferReadIterator
//

class RTRBufferWriteIterator
{

#ifndef _RDEV_NO_STL_
friend  std::ostream& operator<<(std::ostream& os, const RTRBufferWriteIterator& );
#else
public:
void print(FILE* os);
#endif


protected:

	RTRBuffer	*_buffer;

	char		*_area;
	int			_size;
	int			_count;
	int			_offset;


public:


// Constructor
	RTRBufferWriteIterator();
		// Create a write iterator that has no associated buffer.
		// _TAG Constructor

	RTRBufferWriteIterator( RTRBuffer& aBuffer );
		// Create a write iterator that operators on the fiven buffer,
		// starting at the beginning of the buffer.
		// _TAG Constructor

	RTRBufferWriteIterator( RTRBuffer& aBuffer, int offset, int size );
		// Create a write iterator that operators on the given buffer,
		// starting at the given offset in the buffer.  capacity() is
		// set to size.
		// _TAG Constructor

// Destructor
	~RTRBufferWriteIterator();
		// _TAG Destructor

// Re-initialize

	// Reinitialize the write iterator to operate on the given buffer, starting
	// at the beginning of the buffer.
	// _TAG03 Re-initialize
	inline void reinitialize( RTRBuffer& aBuffer )
	{

		_buffer = &aBuffer;
		_area = _buffer->to_c(1);
		_size = _buffer->capacity();
		_count = 0;
		_offset = 0;
	};

	// Reinitialize the write iterator to operate on the given buffer,
	// starting at the given offset in the buffer.  capacity() is set to size.
	// _TAG03 Re-initialize
	inline void reinitialize( RTRBuffer& aBuffer, int offset, int size )
	{

		_buffer = &aBuffer;
		_area = _buffer->to_c(1) + offset;
		_size = size;
		_count = 0;
		_offset = offset;
	};


// Storage

	// In bytes
	// _TAG02 Storage
	inline int capacity() const
	{
		return(_size);
	};



// State

	// Offset for writing into the buffer.
	// _TAG01 State
	inline int offset() const
	{
		return _offset;
	};

	// Number of bytes currently stored.
	// _TAG01 State
	inline int count() const
	{
		return _count;
	};

	// Is the buffer empty?
	// _TAG01 State
	inline RTRBOOL empty() const
	{
		return( (_count == 0) ? RTRTRUE : RTRFALSE );
	};

	// Is this iterator initialized with a buffer?
	// _TAG01 State
	inline RTRBOOL hasBuffer() const
	{
		return(( _buffer == 0 ) ? RTRFALSE : RTRTRUE);
	};

//

	// Is count() on an event boundary?
	// _TAG01 State
	inline RTRBOOL isCountEven() const
	{
		return (_count & 1) ? RTRFALSE : RTRTRUE;
	};

	// Can `nbytes' bytes be put into `this' at `position'?
	// _TAG01 State
	inline RTRBOOL canPutBytes(int nbytes, int position) const
	{
		return (position + nbytes - 1 <= _count) ? RTRTRUE : RTRFALSE;
	};

	// Can `nbytes' bytes be appended into `this'?
	// _TAG01 State
	inline RTRBOOL canAppendBytes(int nbytes) const
	{
		return (_count + nbytes <= _size) ? RTRTRUE : RTRFALSE;
	};


// Write Complete

	// All data has been written into the buffer. Set the count of the
	// underlying buffer. 
	// REQUIRE: hasBuffer();
	// _TAG04 Write Complete
	inline void writingCompleted()
	{
		RTPRECONDITION( hasBuffer() );

		_buffer->set_count( _count + _offset );

		RTPOSTCONDITION(_buffer->count() == count() + offset());
	};

// Access

	// A pointer to the memory location
	// _TAG05 Access
	inline operator const char*() const
	{
		char *temp=_area;
		return(temp);
	};

	// A pointer to the memory location corresponding to offset i. 
	// REQUIRE: i > 0
	// _TAG05 Access
	inline char *to_c(int i) const
	{
		RTPRECONDITION( i > 0 );

		return(_area + i - 1);
	};



// Normal Numeric Insertion

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( 1, position )
	// _TAG06 Normal Numeric Insertion 
	inline void putChar(char c, int position)
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( 1, position ) );

		_area[position-1] = c;
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( sizeof(short), position )
	// _TAG06 Normal Numeric Insertion
	inline void putShort(short i, int position)
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( sizeof(short), position ) );

		ELI_MOVE_SHORT((char *)((_area + position) - 1), &i);
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( sizeof(unsigned short), position )
	// _TAG06 Normal Numeric Insertion
	inline void putUnsignedShort( unsigned short i, int position)
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( sizeof(unsigned short), position ) );

		ELI_MOVE_SHORT((char *)((_area + position) - 1), &i);
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( sizeof(int), position )
	// _TAG06 Normal Numeric Insertion
	inline void putInt(int i, int position)
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( sizeof(int), position ) );

		ELI_MOVE_INT((char *)((_area + position) - 1), &i);
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( sizeof(unsigned int), position )
	// _TAG06 Normal Numeric Insertion
	inline void putUnsignedInt( unsigned int i, int position)
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( sizeof(unsigned int), position ) );

		ELI_MOVE_INT((char *)((_area + position) - 1), &i);
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( sizeof(long), position )
	// _TAG06 Normal Numeric Insertion
	inline void putLong( long i, int position )
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( sizeof(long), position ) );

		ELI_MOVE_LONG((char *)((_area + position) - 1), &i);
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( sizeof(unsigned long), position )
	// _TAG06 Normal Numeric Insertion
	inline void putUnsignedLong( unsigned long i, int position )
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( sizeof(unsigned long), position ) );

		ELI_MOVE_LONG((char *)((_area + position) - 1), &i);
	};


// Network Numeric Insertion
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( 1, position )
	// _TAG07 Network Numeric Insertion
	inline void putByte( s_8 i, int position )
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( 1, position ) );

		_area[position-1] = i;
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( 1, position )
	// _TAG07 Network Numeric Insertion
	inline void putUnsignedByte( u_8 i, int position )
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( 1, position ) );

		_area[position-1] = i;
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( 2, position )
	// _TAG07 Network Numeric Insertion
	inline void putSigned16( s_16 i, int position )
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( 2, position ) );

		ELI_MOVE_16((char *)((_area + position) - 1), &i);
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( 2, position )
	// _TAG07 Network Numeric Insertion
	inline void putUnsigned16( u_16 i, int position )
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( 2, position ) );

		ELI_MOVE_16((char *)((_area + position) - 1), &i);
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( 4, position )
	// _TAG07 Network Numeric Insertion
	inline void putSigned32( s_32 i, int position )
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( 4, position ) );

		ELI_MOVE_32((char *)((_area + position) - 1), &i);
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( 4, position )
	// _TAG07 Network Numeric Insertion
	inline void putUnsigned32( u_32 i, int position )
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( 4, position ) );

		ELI_MOVE_32((char *)((_area + position) - 1), &i);
	};


// Normal Insertion

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( sizeof(float), position )
	// _TAG08 Normal Insertion
	inline void putFloat(float f, int position)
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( sizeof(float), position ) );

		ELI_MOVE_FLOAT((char *)((_area + position) - 1), &f);
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( sizeof(double), position )
	// _TAG08 Normal Insertion
	inline void putDouble(double f, int position)
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( sizeof(double), position ) );

		ELI_MOVE_DOUBLE((char *)((_area + position) - 1), &f);
	};

	// REQUIRE: position > 0 && position <= count() 
	// REQUIRE: canPutBytes( 1, position )
	// _TAG08 Normal Insertion
	inline void putBool(RTRBOOL b, int position)
	{
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( 1, position ) );

		putChar((char)b, position);
	};

	// REQUIRE : n1 <= n2 
	// REQUIRE : position > 0 && position <= count() 
	// REQUIRE : canPutBytes( n2-n1+1, position );
	// _TAG08 Normal Insertion
	inline void putCString(const char *s, int n1, int n2, int position)
	{
		RTPRECONDITION( n2 >= n1 );
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( n2-n1+1, position ) );

		memcpy((char *)(_area + position - 1), s + n1 - 1, (unsigned int)(n2 - n1 + 1) ); 
	};

	// REQUIRE : canPutBytes( str.length(), position );
	// _TAG08 Normal Insertion
	inline void putString(const RTRSmallString& str, int position)
	{
		RTPRECONDITION( canPutBytes( str.length(), position ) );

		if ( str.length() > 0 )
			putCString((char*)str.to_c(), 1, str.length(), position);
	};

	// REQUIRE : n1 <= n2 
	// REQUIRE : position > 0 && position <= count() 
	// REQUIRE : canPutBytes( n2-n1+1, position );
	// _TAG08 Normal Insertion
	inline void putString(const RTRString& str, int n1, int n2, int position)
	{
		RTPRECONDITION( n2 >= n1 );
		RTPRECONDITION( position > 0 && position <= count() );
		RTPRECONDITION( canPutBytes( n2-n1+1, position ) );

		putCString((char*)str.to_c(), n1, n2, position);
	};

	// REQUIRE : canPutBytes( str.length(), position );
	// _TAG08 Normal Insertion
	inline void putString(const RTRString& str, int position)
	{
		RTPRECONDITION( canPutBytes( str.length(), position ) );

		if ( str.length() > 0 )
			putString(str, 1, str.length(), position);
	};


// Normal Numeric Appending.

	// REQUIRE : canAppendBytes( 1 )
	// _TAG09 Normal Numeric Appending
	inline void appendChar(char c)
	{
		RTPRECONDITION( canAppendBytes( 1 ) );

		int cnt = _count;
		_count++;
		putChar(c, cnt+1);
	};

	// REQUIRE : canAppendBytes( sizeof(short) )
	// _TAG09 Normal Numeric Appending
	inline void appendShort(short i)
	{
		RTPRECONDITION( canAppendBytes( sizeof(short) ) );

		int cnt = _count;
		_count += (unsigned int) sizeof(short);
		putShort(i, (cnt+1));
	};

	// REQUIRE : canAppendBytes( sizeof(unsigned short) )
	// _TAG09 Normal Numeric Appending
	inline void appendUnsignedShort( unsigned short i)
	{
		RTPRECONDITION( canAppendBytes( sizeof(unsigned short) ) );

		int cnt = _count;
		_count += (unsigned int) sizeof(unsigned short);
		putUnsignedShort(i, (cnt+1));
	};

	// REQUIRE : canAppendBytes( sizeof(int) )
	// _TAG09 Normal Numeric Appending
	inline void appendInt(int i)
	{
		RTPRECONDITION( canAppendBytes( sizeof(int) ) );

		int cnt = _count;
		_count += (unsigned int) sizeof(int);
		putInt(i, (cnt+1));
	};

	// REQUIRE : canAppendBytes( sizeof(unsigned int) )
	// _TAG09 Normal Numeric Appending
	inline void appendUnsignedInt( unsigned int i)
	{
		RTPRECONDITION( canAppendBytes( sizeof(unsigned int) ) );

		int cnt = _count;
		_count += (unsigned int) sizeof(unsigned int);
		putUnsignedInt(i, (cnt+1));
	};

	// REQUIRE : canAppendBytes( sizeof(long) )
	// _TAG09 Normal Numeric Appending
	inline void appendLong( long i )
	{
		RTPRECONDITION( canAppendBytes( sizeof(long) ) );

		int cnt = _count;
		_count += (unsigned int) sizeof(long);
		putLong(i, (cnt+1));
	};

	// REQUIRE : canAppendBytes( sizeof(unsigned long) )
	// _TAG09 Normal Numeric Appending
	inline void appendUnsignedLong( unsigned long i )
	{
		RTPRECONDITION( canAppendBytes( sizeof(unsigned long) ) );

		int cnt = _count;
		_count += (unsigned int) sizeof(unsigned long);
		putUnsignedLong(i, (cnt+1));
	};


// Network Numeric Appending.
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.

	// REQUIRE : canAppendBytes( 1 )
	// _TAG10 Network Numeric Appending
	inline void appendByte( s_8 i )
	{
		RTPRECONDITION( canAppendBytes( 1 ) );

		int cnt = _count;
		_count++;
		putByte(i, (cnt+1));
	};

	// REQUIRE : canAppendBytes( 1 )
	// _TAG10 Network Numeric Appending
	inline void appendUnsignedByte( u_8 i )
	{
		RTPRECONDITION( canAppendBytes( 1 ) );

		int cnt = _count;
		_count++;
		putUnsignedByte(i, (cnt+1));
	};

	// REQUIRE : canAppendBytes( 2 )
	// _TAG10 Network Numeric Appending
	inline void appendSigned16( s_16 i )
	{
		RTPRECONDITION( canAppendBytes( 2 ) );

		int cnt = _count;
		_count += 2;
		putSigned16(i, cnt+1);
	};

	// REQUIRE : canAppendBytes( 2 )
	// _TAG10 Network Numeric Appending
	inline void appendUnsigned16( u_16 i )
	{
		RTPRECONDITION( canAppendBytes( 2 ) );

		int cnt = _count;
		_count += 2;
		putUnsigned16(i, cnt+1);
	};

	// REQUIRE : canAppendBytes( 4 )
	// _TAG10 Network Numeric Appending
	inline void appendSigned32( s_32 i )
	{
		RTPRECONDITION( canAppendBytes( 4 ) );

		int cnt = _count;
		_count += 4;
		putSigned32(i, cnt+1);
	};

	// REQUIRE : canAppendBytes( 4 )
	// _TAG10 Network Numeric Appending
	inline void appendUnsigned32( u_32 i )
	{
		RTPRECONDITION( canAppendBytes( 4 ) );

		int cnt = _count;
		_count += 4;
		putUnsigned32(i, cnt+1);
	};


// Normal Appending

	// REQUIRE : canAppendBytes( sizeof(float) )
	// _TAG11 Normal Appending
	inline void appendFloat(float f)
	{
		RTPRECONDITION( canAppendBytes( sizeof(float) ) );

		int cnt = _count;
		_count += (unsigned int) sizeof(float);
		putFloat(f, cnt+1);
	};

	// REQUIRE : canAppendBytes( sizeof(double) )
	// _TAG11 Normal Appending
	inline void appendDouble( double d )
	{
		RTPRECONDITION( canAppendBytes( sizeof(double) ) );

		int cnt = _count;
		_count += (unsigned int) sizeof(double);
		putDouble(d, cnt+1);
	};

	// REQUIRE : canAppendBytes( 1 )
	// _TAG11 Normal Appending
	inline void appendBool(RTRBOOL b)
	{
		RTPRECONDITION( canAppendBytes( 1 ) );
		
		appendByte((int)b);
	};

	// REQUIRE : canAppendBytes( str.length() )
	// _TAG11 Normal Appending
	inline void appendString(const RTRString& str)
	{
		RTPRECONDITION( canAppendBytes( str.length() ) );

		int cnt = _count;
		_count += str.length();
		putString(str, cnt+1);
	};

	// REQUIRE : canAppendBytes( str.count() + 2) 
	// REQUIRE : str.count() <= 65536
    // _TAG11 Normal Appending
	inline void appendCountedString(const RTRString& str)
	{
		RTPRECONDITION( str.count() <= 65536 );
		RTPRECONDITION( canAppendBytes( str.count() + 2) );

		appendUnsigned16(str.count());
		int cnt = _count;
		_count += str.count();
		putString(str, cnt+1);
		memcpy((char *)(_area + cnt), (char*)(str.to_c()), str.count());
	};

	// REQUIRE : canAppendBytes( str.length() )
    // _TAG11 Normal Appending
	inline void appendString(const RTRSmallString& str)
	{
		RTPRECONDITION( canAppendBytes( str.length() ) );

		int cnt = _count;
		_count += str.length();
		putString(str, cnt+1);
	};

	// REQUIRE : canAppendBytes( oid.count() + 2) 
	// REQUIRE : oid.count() <= 65536
    // _TAG11 Normal Appending
	inline void appendObjectId(const RTRObjectId& oid)
	{
		RTPRECONDITION( oid.count() <= 65536 );
		RTPRECONDITION( canAppendBytes( oid.count() + 2) );

		appendUnsigned16(oid.count());
		int cnt = _count;
		_count += oid.count();
		memcpy((char *)(_area + cnt), (char*)(oid.to_c()), (unsigned int)oid.count());
	};

	// REQUIRE : canAppendBytes( b.count() )
	// _TAG11 Normal Appending
	inline void appendBuffer(const RTRBuffer& b)
	{
 		RTPRECONDITION( canAppendBytes( b.count() ) );

		int cnt = _count;
		_count += b.count();
		putCString( b.to_c(1), 1, b.count(), (cnt+1) );
	};

	// REQUIRE : canAppendBytes( len )
	// _TAG11 Normal Appending
	inline void appendCBuffer( char *buffer, int len )
	{
		RTPRECONDITION( canAppendBytes( len ) );

		int cnt = _count;
		_count += len;
		putCString( buffer, 1, len, (cnt+1));
	};


// Basic Manipulation

	// Set count() to the next event boundary. 
	// ENSURE: isCountEven()
	// _TAG12 Basic Manipulation
	inline void moveCountEven()
	{
		if (!isCountEven())
			appendChar('\0');

		RTPOSTCONDITION( isCountEven() );
	};

	// REQUIRE: nbytes >= 0
	// _TAG12 Basic Manipulation
	inline void incrementCount(int nbytes)
	{
		RTPRECONDITION( nbytes >= 0 );

		_count += nbytes;
	}

	// REQUIRE: i <= capacity()
	// _TAG12 Basic Manipulation
	inline void setCount(int i)
	{
		RTPRECONDITION( i <= capacity() );
		_count = i;

		RTPOSTCONDITION( count() == i );
	};

};

#endif
