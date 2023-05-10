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
//	created:	November 10, 1994
//	version:	1.0
//

#ifndef __RTR_FORW_BUFF_READ_ITERATOR
#define __RTR_FORW_BUFF_READ_ITERATOR

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

#include "rtr/bfwrtit.h"

// Synopsis:
//
// Description:
//
//  This class implements a read iterator across a buffer.
//  A read cursor exists which iterators while the user
//  is `get'ting elements from the buffer. The read cursor
//  is automatically incremented.
//
//  This iterator is considered a forward iterator since
//  the iterator itself cannot handle going backwards in
//  the buffer.
//
//  The index in this version of the iterator starts
//  at 0. So valid elements go into index 0 - count()-1.
//  The feature lower() exists for compatability with
//  other versions of the iterator. It should be used
//  in index calculations.
//
// See Also:
//

class RTRFwdBufReadIter
{

#ifndef _RDEV_NO_STL_
friend  std::ostream& operator<<(std::ostream& os, RTRFwdBufReadIter& aIterator);
#else
public:
void print(FILE* os);
#endif

public:


// Constructor
	RTRFwdBufReadIter();
		// Initialize the iterator.
		// ENSURE: ! hasBuffer()
		// _TAG Constructor

	RTRFwdBufReadIter( RTRBuffer& aBuffer );
		// Initialize the iterator with aBuffer.
		// ENSURE: hasBuffer()
		// ENSURE: count() == aBuffer.count()
		// _TAG Constructor

	RTRFwdBufReadIter( RTRBuffer& aBuffer, int offset );
		// Initialize the iterator with aBuffer at an offset.
		// REQUIRE: offset >= 0 && offset < aBuffer.count()
		// ENSURE: hasBuffer()
		// ENSURE: count() == (aBuffer.count() - offset)
		// _TAG Constructor

	RTRFwdBufReadIter( RTRBuffer& aBuffer, int offset, int size );
		// Initialize the iterator with aBuffer at an offset of
		// `offset' in aBuffer with a count() of size.
		// REQUIRE: offset >= 0 && offset < aBuffer.count()
		// REQUIRE: size >= 0 && size <= (aBuffer.count() - offset)
		// ENSURE: hasBuffer()
		// ENSURE: count() == size
		// _TAG Constructor

	RTRFwdBufReadIter( RTRFwdBufReadIter& aIt );
		// Initialize the iterator with another iterator.
		// REQUIRE: aIt.hasBuffer()
		// ENSURE: hasBuffer()
		// ENSURE: count() == aIt.count()
		// _TAG Constructor

	RTRFwdBufReadIter( RTRFwdBufReadIter& aIt, int offset );
		// Initialize the iterator with another iterator
		// at an offset of `offset' in aIt.
		// REQUIRE: aIt.hasBuffer()
		// REQUIRE: offset >= 0 && offset < aIt.count()
		// ENSURE: hasBuffer()
		// ENSURE: count() == (aIt.count() - offset)
		// _TAG Constructor

	RTRFwdBufReadIter( RTRFwdBufReadIter& aIt, int offset, int size );
		// Initialize the iterator with another iterator
		// at an offset of `offset' in aIt and with count() of size.
		// REQUIRE: aIt.hasBuffer()
		// REQUIRE: offset >= 0 && offset < aIt.count()
		// REQUIRE: size >= 0 && size <= (aIt.count() - offset)
		// ENSURE: hasBuffer()
		// ENSURE: count() == size
		// _TAG Constructor

// Destructor
	~RTRFwdBufReadIter();
		// _TAG Destructor

// Initializor
	void reinitialize( RTRBuffer& aBuffer, int offset=0 );
		// Reinitialize the iterator with aBuffer at an
		// offset of `offset' in aBuffer.
		// REQUIRE: offset >= 0 && offset < aBuffer.count()
		// ENSURE: hasBuffer()
		// ENSURE: count() == (aBuffer.count() - offset)
		// _TAG01 Initializor

	void reinitialize( RTRBuffer& aBuffer, int offset, int size );
		// Reinitialize the iterator with aBuffer at an
		// offset of `offset' in aBuffer and with a count()
		// of size.
		// REQUIRE: offset >= 0 && offset < aBuffer.count()
		// REQUIRE: size >= 0 && size <= (aBuffer.count() - offset)
		// ENSURE: hasBuffer()
		// ENSURE: count() == size
        // _TAG01 Initializor

	void reinitialize( RTRFwdBufReadIter& aIt, int offset=0 );
		// Reinitialize the iterator with another iterator
		// at an offset of `offset' in aIt.
		// REQUIRE: aIt.hasBuffer()
		// REQUIRE: offset >= 0 && offset < aIt.count()
		// ENSURE: hasBuffer()
		// ENSURE: count() == (aIt.count() - offset)
        // _TAG01 Initializor

	void reinitialize( RTRFwdBufReadIter& aIt, int offset, int size );
		// Reinitialize the iterator with another iterator
		// at an offset of `offset' in aIt and with count() of size.
		// REQUIRE: aIt.hasBuffer()
		// REQUIRE: offset >= 0 && offset < aIt.count()
		// REQUIRE: size >= 0 && size <= (aIt.count() - offset)
		// ENSURE: hasBuffer()
		// ENSURE: count() == size
        // _TAG01 Initializor

	void doneReading();
		// ENSURE: ! hasbuffer()
        // _TAG01 Initializor

// State
	int count();
		// Number of bytes currently stored.
		// _TAG02 State

	int lower();
		// The lower index of the iterator.
        // _TAG02 State

	int upper();
		// The maximum index of the iterator.
        // _TAG02 State

	RTRBOOL empty();
		// Is the buffer empty?
        // _TAG02 State

	RTRBOOL hasBuffer();
        // _TAG02 State

	RTRBuffer & buffer();
        // _TAG02 State

	int offset();
        // _TAG02 State

// Read Cursor
	int readCursor();
		// The index on which the next read operation will take effect.
		// _TAG03 Read Cursor

	void start();
		// Initialize readCursor() to the start of the buffer.
        // _TAG03 Read Cursor

	RTRBOOL off();
		// Have the entire contents of Current been read?
        // _TAG03 Read Cursor

	void setReadCursor(int i);
		// Move the read cursor to index i.
		// Allowed to be beyond end-of-buffer.
		// REQUIRE:	i >= 0
		// ENSURE:	readCursor() = i
        // _TAG03 Read Cursor

	void incrementReadCursor(int i);
		// Increment the read cursor by `i'.
		// Allowed to be beyond end-of-buffer.
		// REQUIRE:	i >= 0;
		// ENSURE:	readCursor() = old readCursor() + i
        // _TAG03 Read Cursor

	RTRBOOL bytesAvailable(int nbytes);
		// Are `nbytes' bytes left in `this' starting at readCursor()?
        // _TAG03 Read Cursor

	RTRBOOL bytesAvailable(int pos, int nbytes);
		// Are `nbytes' bytes left in `this' starting at position `pos'?
        // _TAG03 Read Cursor

	RTRBOOL isReadEven();
		// Is readCursor() on an even boundary?
        // _TAG03 Read Cursor

	RTRBOOL isCountEven();
		// Is count() on an event boundary?
        // _TAG03 Read Cursor

	void search(char c);
		// Move readCursor() to the first occurrence of c. Go "off"
		// if no such character is found.
		// ENSURE : off() || ( *(to_c(readCursor())) == c )
        // _TAG03 Read Cursor

	void moveReadEven();
		// Position the read cursor on the next event boundary.
        // _TAG03 Read Cursor

// Access
	operator const char*() const;
		// A pointer to the memory location
		// _TAG04 Access

	char *to_c(int offset, int);
		// A pointer to the len bytes of contiguous data corresponding to 
		// offset.
        // _TAG04 Access

	char *to_c(int i);
		// A pointer to the memory location corresponding to offset i.
		// OBSOLETE: This method is flawed. The interface implies access to a 
		// "'C' string", i.e. contiguous data. There is no way for the
		// buffer to implement this properly without knowing the length
		// of data requested. Use to_c(int offset, int len)
        // _TAG04 Access

	char item (int i);
		// The character at position i.
		// REQUIRE : i >= 0 && i < count()
        // _TAG04 Access

	char operator[](int i);
		// The character at position i.
		// REQUIRE : i >= 0 && i < count()
        // _TAG04 Access

// Normal Numeric Cursor retrieval
// These member functions should be used when the buffer
// is to stay within a process, or size is not an issue.
	char getChar();
		// Character representation at `readCursor()'
		// _TAG05 Normal Numeric Cursor retrieval

	short getShort();
        // _TAG05 Normal Numeric Cursor retrieval

	unsigned short getUnsignedShort();
        // _TAG05 Normal Numeric Cursor retrieval

	int getInt();
        // _TAG05 Normal Numeric Cursor retrieval

	unsigned int getUnsignedInt();
        // _TAG05 Normal Numeric Cursor retrieval

	long getLong();
        // _TAG05 Normal Numeric Cursor retrieval

	unsigned long getUnsignedLong();
        // _TAG05 Normal Numeric Cursor retrieval

// Network Numeric Cursor retrieval
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.
	s_8 getSignedByte();
		// _TAG06 Network Numeric Cursor retrieval

	u_8 getUnsignedByte();
        // _TAG06 Network Numeric Cursor retrieval

	s_16 getSigned16();
        // _TAG06 Network Numeric Cursor retrieval

	u_16 getUnsigned16();
        // _TAG06 Network Numeric Cursor retrieval

	s_32 getSigned32();
        // _TAG06 Network Numeric Cursor retrieval

	u_32 getUnsigned32();
        // _TAG06 Network Numeric Cursor retrieval

// Efficient versions.
	void getSignedByte( s_8* );
		// _TAG07 Efficient versions

	void getUnsignedByte( u_8* );
        // _TAG07 Efficient versions

	void getSigned16( s_16* );
        // _TAG07 Efficient versions

	void getUnsigned16( u_16* );
        // _TAG07 Efficient versions

	void getSigned32( s_32* );
        // _TAG07 Efficient versions

	void getUnsigned32( u_32* );
        // _TAG07 Efficient versions

// Normal Cursor retrieval.
	RTRBOOL getBool();
		// _TAG08 Normal Cursor retrieval

	float getFloat();
        // _TAG08 Normal Cursor retrieval

	double getDouble();
        // _TAG08 Normal Cursor retrieval

	RTRString getString(int len);
        // _TAG08 Normal Cursor retrieval

// Normal Cursor retrieval.
// Efficiency routines.
	void getString( RTRString &str, int len );
		// Get len bytes out of current from the read cursor
		// and put them into `str'.
		// _TAG09 Normal Cursor retrieval -- Effieciency routines

	void getString( RTRSmallString &str, int len );
		// Get len bytes out of current from the read cursor
		// and put them into `str'.
        // _TAG09 Normal Cursor retrieval -- Effieciency routines

	void getSubBuffer( RTRBufferWriteIterator& aBuffer, int num_bytes );
        // _TAG09 Normal Cursor retrieval -- Effieciency routines
			
	void getCBuffer( char *buffer, int len );
		// REQUIRE : buffer can hold len bytes.
        // _TAG09 Normal Cursor retrieval -- Effieciency routines

// Non - Cursor retrieval
// More efficiency stuff
	void copyToCBuffer( char *buffer, int offset, int len );
		// REQUIRE : buffer can hold len bytes.
		// _TAG10 Non - Cursor retrieval

protected:

	RTRBuffer	*_buffer;
	char		*_area;
	int			_count;
	int			_readCursor;
	int			_offset;


private:


};




//-------------------------------------------------
// Inline declarations
//

inline int RTRFwdBufReadIter::count() { return( _count ); };
inline int RTRFwdBufReadIter::lower() { return(0); };
inline int RTRFwdBufReadIter::upper() { return( _count-1 ); };
inline RTRBOOL RTRFwdBufReadIter::empty() { return( _count == 0 ); };
inline RTRBOOL RTRFwdBufReadIter::hasBuffer() { return( _buffer != 0 ); };
inline RTRBuffer &RTRFwdBufReadIter::buffer() { return( *_buffer ); };
inline int RTRFwdBufReadIter::offset() { return( _offset ); };

inline void RTRFwdBufReadIter::reinitialize(
				RTRFwdBufReadIter& aIt, int offset, int size )
{
	RTPRECONDITION( aIt.hasBuffer());
	reinitialize( *(aIt._buffer), (aIt._offset + offset), size );
};

inline void RTRFwdBufReadIter::reinitialize(
				RTRBuffer& aBuffer, int offset )
{
	reinitialize( aBuffer, offset, (aBuffer.count()-offset) );
	RTPOSTCONDITION( hasBuffer() );
};

inline void RTRFwdBufReadIter::reinitialize(
				RTRFwdBufReadIter& aIt, int offset )
{
	RTPRECONDITION( aIt.hasBuffer());
	reinitialize( *(aIt._buffer), (aIt._offset + offset) );
};


inline void RTRFwdBufReadIter::doneReading()
{
	_buffer = 0;
	_area = 0;
	RTPOSTCONDITION( !hasBuffer() );
};

inline int RTRFwdBufReadIter::readCursor()
{
	return( _readCursor );
};

inline void RTRFwdBufReadIter::start()
{
	_readCursor = 0;
};

inline RTRBOOL RTRFwdBufReadIter::off()
{
	return ( _readCursor >= _count );
};

inline void RTRFwdBufReadIter::setReadCursor(int i)
{
	RTPRECONDITION( i >= 0 );
	_readCursor = i;
	RTPOSTCONDITION( readCursor() == i );
};

inline void RTRFwdBufReadIter::incrementReadCursor(int i)
{
	RTPRECONDITION( i >= 0 );
	_readCursor += i;
};

inline RTRBOOL RTRFwdBufReadIter::bytesAvailable(int nbytes)
{
		// Subtracting one and checking for < is the same
		// as just checking <=.
	return ((_readCursor + nbytes) <= _count);
};

inline RTRBOOL RTRFwdBufReadIter::bytesAvailable(int pos, int nbytes)
{
		// Subtracting one and checking for < is the same
		// as just checking <=.
	return ((pos + nbytes) <= _count);
};

inline RTRBOOL RTRFwdBufReadIter::isReadEven()
{
	return (_readCursor & 1) ? RTRFALSE : RTRTRUE;
};

inline RTRBOOL RTRFwdBufReadIter::isCountEven()
{
	return (_count & 1) ? RTRFALSE : RTRTRUE;
};

inline void RTRFwdBufReadIter::search(char c)
{
	char *ptr = (char*)memchr(_area, c, (unsigned int) _count);
	if (ptr)
		_readCursor = ptr - _area;
	else
		_readCursor = _count;
};

inline void RTRFwdBufReadIter::moveReadEven()
{
	if (!isReadEven())
		_readCursor++;
};


inline RTRFwdBufReadIter::operator const char*() const
{
	char *temp=_area;
	return(temp);
};

#ifdef RTDEBUG
inline char *RTRFwdBufReadIter::to_c(int offset, int len)
#else
inline char *RTRFwdBufReadIter::to_c(int offset, int)
#endif
{
	RTPRECONDITION( offset >= 0 );
	RTPRECONDITION( len >= 0 );
	RTPRECONDITION( (offset + len) < count() );
	return(_area + offset);
};

inline char *RTRFwdBufReadIter::to_c(int i)
{
	RTPRECONDITION( i > 0 );
	return(_area + i);
};

inline char RTRFwdBufReadIter::item(int i)
{
	RTPRECONDITION( i >= 0 && i < count() );
	return( _area[ i ] );
};

inline char RTRFwdBufReadIter::operator[](int i)
{
	RTPRECONDITION( i >= 0 && i < count() );
	return( _area[ i ] );
};

inline char RTRFwdBufReadIter::getChar()
{
	RTPRECONDITION( bytesAvailable( 1 ) );
	char val=_area[ _readCursor ];
	_readCursor++;
	return val;
};

inline short RTRFwdBufReadIter::getShort()
{
	RTPRECONDITION( bytesAvailable( sizeof(short) ) );
	short value = 0;
	memcpy( (char*)&value, (_area+_readCursor), sizeof(short) );
	_readCursor += sizeof(short);
	return(value);
};

inline unsigned short RTRFwdBufReadIter::getUnsignedShort()
{
	RTPRECONDITION( bytesAvailable(sizeof(unsigned short) ) );
	unsigned short value = 0;
	memcpy( (char*)&value, (_area+_readCursor), sizeof(unsigned short) );
	_readCursor += sizeof(unsigned short);
	return(value);
};

inline int RTRFwdBufReadIter::getInt()
{
	RTPRECONDITION( bytesAvailable( sizeof(int) ) );
	int value = 0;
	memcpy( (char*)&value, (_area+_readCursor), sizeof(int) );
	_readCursor += sizeof(int);
	return value;
};

inline unsigned int RTRFwdBufReadIter::getUnsignedInt()
{
	RTPRECONDITION( bytesAvailable( sizeof(unsigned int) ) );
	unsigned int value = 0;
	memcpy( (char*)&value, (_area+_readCursor), sizeof(unsigned int) );
	_readCursor += sizeof(unsigned int);
	return value;
};

inline long RTRFwdBufReadIter::getLong()
{
	RTPRECONDITION( bytesAvailable( sizeof(long) ) );
	long value = 0;
	memcpy( (char*)&value, (_area+_readCursor), sizeof(long) );
	_readCursor += sizeof(long);
	return value;
};

inline unsigned long RTRFwdBufReadIter::getUnsignedLong()
{
	RTPRECONDITION( bytesAvailable( sizeof(unsigned long) ) );
	unsigned long value = 0;
	memcpy( (char*)&value, (_area+_readCursor), sizeof(unsigned long) );
	_readCursor += sizeof(unsigned long);
	return value;
};

inline s_8 RTRFwdBufReadIter::getSignedByte()
{
	RTPRECONDITION( bytesAvailable( 1 ) );
	s_8 value = 0;
	ELI_MOVE_8 (&value, (char *)(_area + _readCursor));
	_readCursor++;
	return value;
};

inline u_8 RTRFwdBufReadIter::getUnsignedByte()
{
	RTPRECONDITION( bytesAvailable( 1 ) );
	u_8 value = 0;
	ELI_MOVE_8 (&value, (char *)(_area + _readCursor));
	_readCursor++;
	return value;
};

inline s_16 RTRFwdBufReadIter::getSigned16()
{
	RTPRECONDITION( bytesAvailable( 2 ) );
	s_16 value = 0;
	ELI_MOVE_16 (&value, (char *)(_area + _readCursor));
	_readCursor += 2;
	return value;
};

inline u_16 RTRFwdBufReadIter::getUnsigned16()
{
	RTPRECONDITION( bytesAvailable( 2 ) );
	u_16 value = 0;
	ELI_MOVE_16 (&value, (char *)(_area + _readCursor));
	_readCursor += 2;
	return value;
};

inline s_32 RTRFwdBufReadIter::getSigned32()
{
	RTPRECONDITION( bytesAvailable( 4 ) );
	s_32 value = 0;
	ELI_MOVE_32 (&value, (char *)(_area + _readCursor));
	_readCursor += 4;
	return value;
};

inline u_32 RTRFwdBufReadIter::getUnsigned32()
{
	RTPRECONDITION( bytesAvailable( 4 ) );
	u_32 value = 0;
	ELI_MOVE_32 (&value, (char *)(_area + _readCursor));
	_readCursor += 4;
	return value;
};

inline void RTRFwdBufReadIter::getSignedByte( s_8 *value )
{
	RTPRECONDITION( bytesAvailable( 1 ) );
	ELI_MOVE_8 (value, (char *)(_area + _readCursor));
	_readCursor++;
};

inline void RTRFwdBufReadIter::getUnsignedByte( u_8 *value )
{
	RTPRECONDITION( bytesAvailable( 1 ) );
	ELI_MOVE_8 (value, (char *)(_area + _readCursor));
	_readCursor++;
};

inline void RTRFwdBufReadIter::getSigned16( s_16 *value )
{
	RTPRECONDITION( bytesAvailable( 2 ) );
	ELI_MOVE_16 (value, (char *)(_area + _readCursor));
	_readCursor += 2;
};

inline void RTRFwdBufReadIter::getUnsigned16( u_16 *value )
{
	RTPRECONDITION( bytesAvailable( 2 ) );
	ELI_MOVE_16 (value, (char *)(_area + _readCursor));
	_readCursor += 2;
};

inline void RTRFwdBufReadIter::getSigned32( s_32 *value )
{
	RTPRECONDITION( bytesAvailable( 4 ) );
	ELI_MOVE_32 (value, (char *)(_area + _readCursor));
	_readCursor += 4;
};

inline void RTRFwdBufReadIter::getUnsigned32( u_32 *value )
{
	RTPRECONDITION( bytesAvailable( 4 ) );
	ELI_MOVE_32 (value, (char *)(_area + _readCursor));
	_readCursor += 4;
};

inline RTRBOOL RTRFwdBufReadIter::getBool()
{
	RTPRECONDITION( bytesAvailable( 1 ) );
	char value = 0;
	value = _area[ _readCursor ];
	_readCursor++;
	return((RTRBOOL)value);
};

inline float RTRFwdBufReadIter::getFloat()
{
	RTPRECONDITION( bytesAvailable( sizeof(float) ) );
	float value = 0.0;
	ELI_MOVE_FLOAT (&value, (char *)(_area + _readCursor));
	_readCursor += sizeof(float);
	return value;
};

inline double RTRFwdBufReadIter::getDouble()
{
	RTPRECONDITION( bytesAvailable( sizeof(double) ) );
	double value = 0.0;
	ELI_MOVE_DOUBLE (&value, (char *)(_area + _readCursor));
	_readCursor += sizeof(double);
	return value;
};

inline RTRString RTRFwdBufReadIter::getString(int len)
{
	RTPRECONDITION( bytesAvailable( len ) );
	int oldread=_readCursor;
	_readCursor += len;
	return RTRString((char *)(_area + oldread), len);
};

inline void RTRFwdBufReadIter::getString(
				RTRString &str, int len )
{
	str.set( (_area + _readCursor), len );
	_readCursor += len;
};

inline void RTRFwdBufReadIter::getString(
				RTRSmallString &str, int len )
{
	RTPRECONDITION( bytesAvailable( len ) );
	RTPRECONDITION( str.capacity() >= len );
	str.set( (_area + _readCursor), len );
	_readCursor += len;
};

inline void RTRFwdBufReadIter::getSubBuffer(
				RTRBufferWriteIterator& aBuffer, int num_bytes )
{
	aBuffer.appendCBuffer( (char*)(_area + _readCursor), num_bytes);
	_readCursor += num_bytes;
};

inline void RTRFwdBufReadIter::getCBuffer(
				char *buffer, int len )
{
	RTPRECONDITION( bytesAvailable( len ) );
	(void)memcpy( buffer, (char *)(_area + _readCursor), (unsigned int) len );
	_readCursor += len;
};

inline void RTRFwdBufReadIter::copyToCBuffer(
				char *buffer, int offset, int len )
{
	RTPRECONDITION( offset > 0 );
	RTPRECONDITION( offset < readCursor() || \
					 (offset == readCursor()) && len == 0);
	RTPRECONDITION( bytesAvailable( offset, len ) );
	(void)memcpy( buffer, (char *)(_area + offset), (unsigned int) len );
};



#endif
