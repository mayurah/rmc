//
//|---------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       November 11, 1994
//  version:       1.1
//

#ifndef __RTR_FORW_BUFF_WRITE_ITER
#define __RTR_FORW_BUFF_WRITE_ITER

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif
#include <memory.h>

#include "rtr/rtrdefs.h"
#include "rtr/rtdataty.h"
#include "rtr/rtstring.h"
#include "rtr/smallstr.h"
#include "rtr/eli_net.h"
#include "rtr/rtbuffer.h"

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRFwdBufWriteIter
{

#ifndef _RDEV_NO_STL_
friend  std::ostream& operator<<(std::ostream& os, RTRFwdBufWriteIter& aIterator);
#else
public:
void print(FILE* os);
#endif


public:


// Constructor
	RTRFwdBufWriteIter();
		// Create a writing iterator.
		// _TAG Constructor

	RTRFwdBufWriteIter( RTRBuffer& aBuffer );
		// Create a writing iterator. Initialize
		// with aBuffer.
		// ENSURE: hasBuffer()
		// ENSURE: capacity() == aBuffer.capacity()
		// ENSURE: count() == 0
		// _TAG Constructor

	RTRFwdBufWriteIter( RTRBuffer& aBuffer, int offset, int size );
		// Create a writing iterator. Initialize
		// at an offset of `offset' in aBuffer with a
		// capacity() of size.
		// REQUIRE: offset >= 0 && offset < aBuffer.capacity()
		// REQUIRE: size >= 0 && size <= (aBuffer.capacity() - offset)
		// ENSURE: hasBuffer()
		// ENSURE: capacity() == aBuffer.count() - offset
		// ENSURE: count() == 0
		// _TAG Constructor

// Destructor
	~RTRFwdBufWriteIter();
		// _TAG Destructor

// Re-initialize
	void reinitialize( RTRBuffer& aBuffer );
		// Reinitialize the writing iterator. Initialize
		// with aBuffer.
		// ENSURE: hasBuffer()
		// ENSURE: capacity() == aBuffer.capacity()
		// ENSURE: count() == 0
		// _TAG01 Re-initialize

	void reinitialize( RTRBuffer& aBuffer, int offset, int size );
		// Reinitialize the writing iterator. Initialize
		// at an offset of `offset' in aBuffer with a
		// capacity() of size.
		// REQUIRE: offset >= 0 && offset < aBuffer.capacity()
		// REQUIRE: size >= 0 && size <= (aBuffer.capacity() - offset)
		// ENSURE: hasBuffer()
		// ENSURE: capacity() == aBuffer.capacity() - offset
		// ENSURE: count() == 0
		// _TAG01 Re-initialize

// Storage
	int capacity();
		// Total number of bytes this iterator
		// can put into the buffer.
		// _TAG02 Storage

	int lower();
        // _TAG02 Storage

// Write Complete
	void writingCompleted();
		// The iterator is finished with the buffer.
		// REQUIRE: hasBuffer()
		// ENSURE: ! hasBuffer()
		// _TAG03 Write Complete

// State
	int offset();
		// Offset for writing into the buffer.
		// _TAG04 State

	int count();
		// Number of bytes currently stored in the
		// buffer current is using.
        // _TAG04 State

	RTRBOOL empty();
		// Is the buffer empty?
        // _TAG04 State

	RTRBOOL hasBuffer();
		// Does current have a buffer associate with it?
        // _TAG04 State

	RTRBuffer & buffer();
		// REQUIRE: hasBuffer()
        // _TAG04 State

// Checking
	RTRBOOL isCountEven();
		// Is the current count even?
		// _TAG05 Checking

	RTRBOOL canPutBytes(int nbytes, int pos);
		// Can `nbytes' bytes be put into `this' at
		// position `pos'.
		// REQUIRE: nbytes >= 0
		// REQUIRE: pos >=0 && pos<count()
        // _TAG05 Checking

	RTRBOOL canAppendBytes(int nbytes);
		// Can `nbytes' bytes be appended into `this'?
		// REQUIRE: nbytes >= 0
        // _TAG05 Checking

// Basic Manipulation
	void moveCountEven();
		// Set count() to the next event boundary.
		// _TAG06 Basic Manipulation

	void incrementCount(int nbytes);
		// REQUIRE: nbytes >= 0
		// REQUIRE: canAppendBytes( nbytes )
        // _TAG06 Basic Manipulation

	void setCount(int i);
		// REQUIRE: i < capacity()
		// ENSURE: count() == i
        // _TAG06 Basic Manipulation

// Access
	operator const char*() const;
		// A pointer to the memory location
		// _TAG07 Access

	char *to_c(int i);
		// A pointer to the memory location corresponding to offset i.
		// REQUIRE: i >= 0
		// _TAG07 Access

// Normal Numeric Appending.
	void appendChar(char c);
		// REQUIRE: canAppendBytes( 1 )
		// _TAG08 Normal Numeric Appending

	void appendShort(short i);
		// REQUIRE: canAppendBytes( sizeof(short) )
        // _TAG08 Normal Numeric Appending

	void appendUnsignedShort( unsigned short i);
		// REQUIRE: canAppendBytes( sizeof(unsigned short) )
        // _TAG08 Normal Numeric Appending

	void appendInt(int i);
		// REQUIRE: canAppendBytes( sizeof(int) )
        // _TAG08 Normal Numeric Appending

	void appendUnsignedInt( unsigned int i);
		// REQUIRE: canAppendBytes( sizeof(unsigned int) )
        // _TAG08 Normal Numeric Appending

	void appendLong( long i );
		// REQUIRE: canAppendBytes( sizeof(long) )
        // _TAG08 Normal Numeric Appending

	void appendUnsignedLong( unsigned long i );
		// REQUIRE: canAppendBytes( sizeof(unsigned long) )
        // _TAG08 Normal Numeric Appending

// Network Numeric Appending.
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.
	void appendByte( s_8 i );
		// REQUIRE: canAppendBytes( 1 )
		// _TAG09 Network Numeric Appending

	void appendUnsignedByte( u_8 i );
		// REQUIRE: canAppendBytes( 1 )
        // _TAG09 Network Numeric Appending

	void appendSigned16( s_16 i );
		// REQUIRE: canAppendBytes( 2 )
        // _TAG09 Network Numeric Appending

	void appendUnsigned16( u_16 i );
		// REQUIRE: canAppendBytes( 2 )
        // _TAG09 Network Numeric Appending

	void appendSigned32( s_32 i );
		// REQUIRE: canAppendBytes( 4 )
        // _TAG09 Network Numeric Appending

	void appendUnsigned32( u_32 i );
		// REQUIRE: canAppendBytes( 4 )
        // _TAG09 Network Numeric Appending

// Normal Appending
	void appendFloat(float f);
		// REQUIRE: canAppendBytes( sizeof(float) )
		// _TAG10 Normal Appending

	void appendDouble( double d );
		// REQUIRE: canAppendBytes( sizeof(double) )
        // _TAG10 Normal Appending

	void appendBool(RTRBOOL b);
		// REQUIRE: canAppendBytes( 1 )
        // _TAG10 Normal Appending

	void appendString(RTRString& str);
		// REQUIRE: canAppendBytes( str.length() )
        // _TAG10 Normal Appending

	void appendString(RTRSmallString& str);
		// REQUIRE: canAppendBytes( str.length() )
        // _TAG10 Normal Appending

	void appendBuffer(RTRBuffer& b);
		// REQUIRE: canAppendBytes( b.count() )
        // _TAG10 Normal Appending

	void appendCBuffer( const char *buffer, int len );
		// REQUIRE: canAppendBytes( len )
        // _TAG10 Normal Appending

	void appendCBuffer( char *buffer, int len );
		// REQUIRE: canAppendBytes( len )
        // _TAG10 Normal Appending

// Normal Numeric Insertion
	void putChar(char c, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( 1, pos );
		// _TAG11 Normal Numeric Insertion

	void putShort(short i, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( sizeof(short), pos );
        // _TAG11 Normal Numeric Insertion

	void putUnsignedShort( unsigned short i, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( sizeof(unsigned short), pos );
        // _TAG11 Normal Numeric Insertion

	void putInt(int i, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( sizeof(int), pos );
        // _TAG11 Normal Numeric Insertion

	void putUnsignedInt( unsigned int i, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( sizeof(unsigned int), pos );
        // _TAG11 Normal Numeric Insertion

	void putLong( long i, int pos );
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( sizeof(long), pos );
        // _TAG11 Normal Numeric Insertion

	void putUnsignedLong( unsigned long i, int pos );
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( sizeof(unsigned long), pos );
        // _TAG11 Normal Numeric Insertion

// Network Numeric Insertion
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.
	void putByte( s_8 i, int pos );
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( 1, pos );
		// _TAG12 Network Numeric Insertion

	void putUnsignedByte( u_8 i, int pos );
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( 1, pos );
        // _TAG11 Normal Numeric Insertion

	void putSigned16( s_16 i, int pos );
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( 2, pos );
        // _TAG11 Normal Numeric Insertion

	void putUnsigned16( u_16 i, int pos );
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( 2, pos );
        // _TAG11 Normal Numeric Insertion

	void putSigned32( s_32 i, int pos );
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( 4, pos );
        // _TAG11 Normal Numeric Insertion

	void putUnsigned32( u_32 i, int pos );
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( 4, pos );
        // _TAG11 Normal Numeric Insertion

// Normal Insertion
	void putFloat(float f, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( sizeof(float), pos );
		// _TAG12 Normal Insertion

	void putDouble(double f, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( sizeof(double), pos );
		// _TAG12 Normal Insertion

	void putBool(RTRBOOL b, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( 1, pos );
		// _TAG12 Normal Insertion

	void putString(RTRString& str, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( str.length(), pos );
        // _TAG12 Normal Insertion

	void putString(RTRSmallString& str, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( str.length(), pos );
        // _TAG12 Normal Insertion

	void putString(RTRString& str, int n1, int n2, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( n2-n1+1, pos );
        // _TAG12 Normal Insertion

	void putCString(char *s, int n1, int n2, int pos);
		// REQUIRE: pos >= 0 && pos < count()
		// REQUIRE: canPutBytes( n2-n1+1, pos )
        // _TAG12 Normal Insertion

protected:

	RTRBuffer	*_buffer;

	char		*_area;
	int			_size;
	int			_count;
	int			_offset;


private:


};




//-------------------------------------------------
// Inline declarations
//
inline int RTRFwdBufWriteIter::capacity() { return(_size); };
inline int RTRFwdBufWriteIter::lower() { return 0; };
inline int RTRFwdBufWriteIter::offset() { return _offset; };
inline int RTRFwdBufWriteIter::count() { return _count; };
inline RTRBOOL RTRFwdBufWriteIter::empty() { return( _count == 0); };
inline RTRBOOL RTRFwdBufWriteIter::hasBuffer() { return( _buffer != 0 ); };
inline RTRBuffer & RTRFwdBufWriteIter::buffer()
{
	RTPRECONDITION( hasBuffer() );
	return *_buffer;
};


inline void RTRFwdBufWriteIter::writingCompleted()
{
	RTPRECONDITION( hasBuffer() );
	_buffer->set_count( _count + _offset );
	_buffer = 0;
	_size = _count = 0;
	RTPOSTCONDITION( ! hasBuffer() );
};

inline RTRBOOL RTRFwdBufWriteIter::isCountEven()
{
	return (_count & 1) ? RTRFALSE : RTRTRUE;
};

inline RTRBOOL RTRFwdBufWriteIter::canPutBytes(int nbytes, int pos)
{
	RTPRECONDITION( nbytes >= 0 );
	RTPRECONDITION( pos >=0 && pos<count() );
	return ((pos + nbytes) <= _count);
};

inline RTRBOOL RTRFwdBufWriteIter::canAppendBytes(int nbytes)
{
	RTPRECONDITION( nbytes >= 0 );
	return ((_count + nbytes) <= _size);
};

inline void RTRFwdBufWriteIter::incrementCount(int nbytes)
{
	RTPRECONDITION( nbytes >= 0 );
	RTPRECONDITION( canAppendBytes( nbytes ) );
	_count += nbytes;
}

inline void RTRFwdBufWriteIter::setCount(int i)
{
	RTPRECONDITION( i < capacity() );
	_count = i;
	RTPOSTCONDITION( count() == i );
};

inline RTRFwdBufWriteIter::operator const char*() const
{
	return(_area);
};

inline char *RTRFwdBufWriteIter::to_c(int i)
{
	RTPRECONDITION( i >= 0 );
	return(_area + i - 1);
};

inline void RTRFwdBufWriteIter::appendChar(char c)
{
	RTPRECONDITION( canAppendBytes( 1 ) );
	_area[_count] = c;
	_count++;
};

inline void RTRFwdBufWriteIter::moveCountEven()
{
	if (!isCountEven())
		appendChar( '\0' );
	RTPOSTCONDITION( isCountEven() );
};

inline void RTRFwdBufWriteIter::appendShort(short i)
{
	RTPRECONDITION( canAppendBytes( sizeof(short) ) );
	ELI_MOVE_SHORT((char *)(_area + _count), &i);
	_count += sizeof(short);
};

inline void RTRFwdBufWriteIter::appendUnsignedShort( unsigned short i)
{
	RTPRECONDITION( canAppendBytes( sizeof(unsigned short) ) );
	ELI_MOVE_SHORT((char *)(_area + _count), &i);
	_count += sizeof(unsigned short);
};

inline void RTRFwdBufWriteIter::appendInt(int i)
{
	RTPRECONDITION( canAppendBytes( sizeof(int) ) );
	ELI_MOVE_INT((char *)(_area + _count), &i);
	_count += sizeof(int);
};

inline void RTRFwdBufWriteIter::appendUnsignedInt( unsigned int i)
{
	RTPRECONDITION( canAppendBytes( sizeof(unsigned int) ) );
	ELI_MOVE_INT((char *)(_area + _count), &i);
	_count += sizeof(unsigned int);
};

inline void RTRFwdBufWriteIter::appendLong( long i )
{
	RTPRECONDITION( canAppendBytes( sizeof(long) ) );
	ELI_MOVE_LONG((char *)(_area + _count), &i);
	_count += sizeof(long);
};

inline void RTRFwdBufWriteIter::appendUnsignedLong( unsigned long i )
{
	RTPRECONDITION( canAppendBytes( sizeof(unsigned long) ) );
	ELI_MOVE_LONG((char *)(_area + _count), &i);
	_count += sizeof(unsigned long);
};

inline void RTRFwdBufWriteIter::appendByte( s_8 i )
{
	RTPRECONDITION( canAppendBytes( 1 ) );
	_area[_count] = i;
	_count++;
};

inline void RTRFwdBufWriteIter::appendUnsignedByte( u_8 i )
{
	RTPRECONDITION( canAppendBytes( 1 ) );
	_area[_count] = i;
	_count++;
};

inline void RTRFwdBufWriteIter::appendSigned16( s_16 i )
{
	RTPRECONDITION( canAppendBytes( 2 ) );
	ELI_MOVE_16((char *)(_area + _count), &i);
	_count += 2;
};

inline void RTRFwdBufWriteIter::appendUnsigned16( u_16 i )
{
	RTPRECONDITION( canAppendBytes( 2 ) );
	ELI_MOVE_16((char *)(_area + _count), &i);
	_count += 2;
};

inline void RTRFwdBufWriteIter::appendSigned32( s_32 i )
{
	RTPRECONDITION( canAppendBytes( 4 ) );
	ELI_MOVE_32((char *)(_area + _count), &i);
	_count += 4;
};

inline void RTRFwdBufWriteIter::appendUnsigned32( u_32 i )
{
	RTPRECONDITION( canAppendBytes( 4 ) );
	ELI_MOVE_32((char *)(_area + _count), &i);
	_count += 4;
};

inline void RTRFwdBufWriteIter::appendFloat(float f)
{
	RTPRECONDITION( canAppendBytes( sizeof(float) ) );
	ELI_MOVE_FLOAT((char *)(_area + _count), &f);
	_count += sizeof(float);
};

inline void RTRFwdBufWriteIter::appendDouble( double d )
{
	RTPRECONDITION( canAppendBytes( sizeof(double) ) );
	ELI_MOVE_DOUBLE((char *)(_area + _count), &d);
	_count += sizeof(double);
};

inline void RTRFwdBufWriteIter::appendBool(RTRBOOL b)
{
	RTPRECONDITION( canAppendBytes( 1 ) );
	appendByte((int)b);
};

inline void RTRFwdBufWriteIter::appendString(RTRString& str)
{
	RTPRECONDITION( canAppendBytes( str.length() ) );
	memcpy((char *)(_area + _count), str.to_c(), (unsigned int) str.length()); 
	_count += str.length();
};

inline void RTRFwdBufWriteIter::appendString(RTRSmallString& str)
{
	RTPRECONDITION( canAppendBytes( str.length() ) );
	memcpy((char *)(_area + _count), str.to_c(), (unsigned int) str.length()); 
	_count += str.length();
};

inline void RTRFwdBufWriteIter::appendBuffer(RTRBuffer& b)
{
	RTPRECONDITION( canAppendBytes( b.count() ) );
	memcpy((char *)(_area + _count), b.to_c(1), (unsigned int) b.count()); 
	_count += b.count();
};

inline void RTRFwdBufWriteIter::appendCBuffer( const char *buffer, int len )
{
	RTPRECONDITION( canAppendBytes( len ) );
	memcpy((char *)(_area + _count), buffer, (unsigned int) len); 
	_count += len;
};

inline void RTRFwdBufWriteIter::appendCBuffer( char *buffer, int len )
{
	RTPRECONDITION( canAppendBytes( len ) );
	memcpy((char *)(_area + _count), buffer, (unsigned int) len); 
	_count += len;
};

inline void RTRFwdBufWriteIter::putChar(char c, int pos)
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( 1, pos ) );
	_area[pos] = c;
};

inline void RTRFwdBufWriteIter::putShort(short i, int pos)
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( sizeof(short), pos ) );
	ELI_MOVE_SHORT((char *)(_area + pos), &i);
};

inline void RTRFwdBufWriteIter::putUnsignedShort(
			unsigned short i, int pos)
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( sizeof(unsigned short), pos ) );
	ELI_MOVE_SHORT((char *)(_area + pos), &i);
};

inline void RTRFwdBufWriteIter::putInt(int i, int pos)
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( sizeof(int), pos ) );
	ELI_MOVE_INT((char *)(_area + pos), &i);
};

inline void RTRFwdBufWriteIter::putUnsignedInt(
			unsigned int i, int pos)
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( sizeof(unsigned int), pos ) );
	ELI_MOVE_INT((char *)(_area + pos), &i);
};

inline void RTRFwdBufWriteIter::putLong( long i, int pos )
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( sizeof(long), pos ) );
	ELI_MOVE_LONG((char *)(_area + pos), &i);
};

inline void RTRFwdBufWriteIter::putUnsignedLong(
			unsigned long i, int pos )
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( sizeof(unsigned long), pos ) );
	ELI_MOVE_LONG((char *)(_area + pos), &i);
};

inline void RTRFwdBufWriteIter::putByte( s_8 i, int pos )
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( 1, pos ) );
	_area[pos] = i;
};

inline void RTRFwdBufWriteIter::putUnsignedByte( u_8 i, int pos )
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( 1, pos ) );
	_area[pos] = i;
};

inline void RTRFwdBufWriteIter::putSigned16( s_16 i, int pos )
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( 2, pos ) );
	ELI_MOVE_16((char *)(_area + pos), &i);
};

inline void RTRFwdBufWriteIter::putUnsigned16( u_16 i, int pos )
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( 2, pos ) );
	ELI_MOVE_16((char *)(_area + pos), &i);
};

inline void RTRFwdBufWriteIter::putSigned32( s_32 i, int pos )
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( 4, pos ) );
	ELI_MOVE_32((char *)(_area + pos), &i);
};

inline void RTRFwdBufWriteIter::putUnsigned32( u_32 i, int pos )
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( 4, pos ) );
	ELI_MOVE_32((char *)(_area + pos), &i);
};

inline void RTRFwdBufWriteIter::putFloat(float f, int pos)
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( sizeof(float), pos ) );
	ELI_MOVE_FLOAT((char *)(_area + pos), &f);
};

inline void RTRFwdBufWriteIter::putDouble(double f, int pos)
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( sizeof(double), pos ) );
	ELI_MOVE_DOUBLE((char *)(_area + pos), &f);
};

inline void RTRFwdBufWriteIter::putBool(RTRBOOL b, int pos)
{
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( 1, pos ) );
	putChar((char)b, pos);
};

inline void RTRFwdBufWriteIter::putCString(
		char *s, int n1, int n2, int pos)
{
	RTPRECONDITION( n2 >= n1 );
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( n2-n1+1, pos ) );
	memcpy((char *)(_area + pos), s + n1, (unsigned int) (n2 - n1 + 1)); 
};

inline void RTRFwdBufWriteIter::putString(RTRString& str, int pos)
{
	RTPRECONDITION( str.length() > 0 );
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( str.length(), pos ) );
	putCString((char*)str.to_c(), 0, str.length()-1, pos);
};

inline void RTRFwdBufWriteIter::putString(
		RTRSmallString& str, int pos)
{
	RTPRECONDITION( str.length() > 0 );
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( str.length(), pos ) );
	putCString((char*)str.to_c(), 0, str.length()-1, pos);
};

inline void RTRFwdBufWriteIter::putString(
		RTRString& str, int n1, int n2, int pos)
{
	RTPRECONDITION( n2 >= n1 );
	RTPRECONDITION( pos >= 0 && pos < count() );
	RTPRECONDITION( canPutBytes( n2-n1+1, pos ) );
	putCString((char*)str.to_c(), n1, n2, pos);
};

#endif
