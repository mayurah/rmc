//
//|---------------------------------------------------------------
//|                Copyright (C) 2000 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//

#ifndef __rtr_cBufWriteIter_h
#define __rtr_cBufWriteIter_h

#include <memory.h>
#include "rtr/rtrdefs.h"
#include "rtr/rtdataty.h"
#include "rtr/eli_net.h"
#include "rtr/os.h"

// Synopsis:
//
// Description:
//	This class provides write iterations over a c buffer.
//	Any integer based indices start from position 0.
//
// See Also:
//

class cBufWriteIter
{
public:

// Constructor
	inline cBufWriteIter() : _area(0), _cursor(0), _end(0) {};
		// Initialize the iterator.
		// ENSURE: !hasBuffer()
		// _TAG Constructor

	inline cBufWriteIter( char *buffer, int length ) :
			_area(buffer), _cursor(buffer), _end(buffer+length) {};
		// Initialize the iterator with buffer and length.
		// ENSURE: hasBuffer()
		// ENSURE: begin() == buffer
		// ENSURE: end() == buffer + length
		// ENSURE: length() == length
		// ENSURE: cursor() == begin()
		// _TAG Constructor

	inline cBufWriteIter( char *buffer, char *end ) :
			_area(buffer), _cursor(buffer), _end(end) {};
		// Initialize the iterator with buffer and the pointer to
		// one address past the end of the buffer.
		// ENSURE: hasBuffer()
		// ENSURE: begin() == buffer
		// ENSURE: end() == end
		// ENSURE: length() == (end() - begin())
		// ENSURE: cursor() == begin()
		// _TAG Constructor

// Destructor
	inline ~cBufWriteIter() {};
		// _TAG Destructor

// Initializor
	inline void clear() { _area=_cursor=_end=0; };
        // _TAG01 Initializor

	inline void reinitialize( char *buffer, int length )
		// Initialize the iterator with buffer and length.
		// ENSURE: hasBuffer()
		// ENSURE: begin() == buffer
		// ENSURE: end() == buffer + length
		// ENSURE: length() == length
		// ENSURE: cursor() == begin()
        // _TAG01 Initializor
	{
		_area = buffer;
		_cursor = buffer;
		_end = buffer+length;
	};

	inline void reinitialize( char *buffer, char *end )
		// Initialize the iterator with buffer and the pointer to
		// one address past the end of the buffer.
		// ENSURE: hasBuffer()
		// ENSURE: begin() == buffer
		// ENSURE: end() == end
		// ENSURE: length() == (end() - begin())
		// ENSURE: cursor() == begin()
        // _TAG01 Initializor
	{
		_area = buffer;
		_cursor = buffer;
		_end = end;
	};

// Attributes
	inline int maxLength() const { return(_end-_area); };
		// The maximum number of bytes that can be stored.
		// _TAG02 Attributes

	inline char *begin() const { return(_area); };
	inline char *buffer() const { return(_area); };
		// The beginning of the buffer.
        // _TAG02 Attributes

	inline char *end() const { return(_end); };
		// One address after the last byte in the buffer;
        // _TAG02 Attributes

	inline RTRBOOL empty() const { return((_area >= _end) ? RTRTRUE : RTRFALSE ); };
		// Is the buffer empty?
        // _TAG02 Attributes

	inline RTRBOOL hasBuffer() const { return((_area == 0) ? RTRFALSE : RTRTRUE); };
        // _TAG02 Attributes

	inline RTRBOOL validAddress(char *myAdd) const
		// Is 'myAdd' a valid address within this buffer?
        // _TAG02 Attributes
	{
		return(((myAdd >= _area) && (myAdd < _end)) ? RTRTRUE : RTRFALSE );
	};

// Cursor
	inline char *cursor() const { return(_cursor); };
		// The address on which the next write operation will take effect.
		// _TAG03 Cursor

	inline int length() const { return((int)(_cursor - _area)); };
		// The length of the write buffer based on the cursor usage.

	inline void start() { _cursor = _area; };
		// Initialize cursor() to the start of the buffer.
        // _TAG03 Cursor

	inline RTRBOOL off() const { return((_cursor >= _end) ? RTRTRUE : RTRFALSE); };
		// Has the entire contents of Current been written?
        // _TAG03 Cursor

	inline void setWriteCursor(char* newpos) { _cursor=newpos; };
		// Move the write cursor to index i.
		// Allowed to be beyond end-of-buffer.
		// ENSURE:	cursor() = newpos
        // _TAG03 Cursor

	inline void incrementWriteCursor(int i) { _cursor+=i; };
		// Increment the write cursor by `i' bytes.
		// Allowed to be beyond end-of-buffer.
		// REQUIRE:	i >= 0;
		// ENSURE:	cursor() = old cursor() + i
        // _TAG03 Cursor

	inline RTRBOOL canAppendBytes(int nbytes) const
		// Can nbytes be written at the current cursor() position.
        // _TAG03 Cursor
	{
		return( ((_cursor+nbytes) <= _end) ? RTRTRUE : RTRFALSE);
	};

	inline RTRBOOL canPutBytes(int pos, int nbytes) const
		// Can nbytes be written at 'pos' index.
        // _TAG03 Cursor
	{
		return( ((_area+pos+nbytes) <= _end) ? RTRTRUE : RTRFALSE);
	};

	inline RTRBOOL canPutBytes(char *loc, int nbytes) const
		// Can nbytes be written at 'pos' index.
        // _TAG03 Cursor
	{
		return( ((loc+nbytes) < _end) ? RTRTRUE : RTRFALSE);
	};

	inline RTRBOOL isWriteEven() const
		// Is cursor() on an even boundary?
        // _TAG03 Cursor
	{
#ifdef COMPILE_64BITS
		return(((!((rtrUInt64)_area & 0x01)) &&
			((rtrUInt64)_cursor & 0x01)) || 
			(((rtrUInt64)_area & 0x01) &&
			(!((rtrUInt64)_cursor & 0x01))) );
#else
		return(((!((u_32)_area & 0x01)) && ((u_32)_cursor & 0x01)) || 
				(((u_32)_area & 0x01) && (!((u_32)_cursor & 0x01))) );
#endif
	};

	inline RTRBOOL isLengthEven() const
		// Is length() on an event boundary?
        // _TAG03 Cursor
	{
#ifdef COMPILE_64BITS
		return(((!((rtrUInt64)_area & 0x01)) &&
			(!((rtrUInt64)_end & 0x01))) || 
			(((rtrUInt64)_area & 0x01) &&
			((rtrUInt64)_cursor & 0x01)) );
#else
		return(((!((u_32)_area & 0x01)) && (!((u_32)_end & 0x01))) || 
					(((u_32)_area & 0x01) && ((u_32)_cursor & 0x01)) );
#endif
	};

	inline void moveWriteEven() { if (!isWriteEven()) _cursor++; };
		// Position the write cursor on the next event boundary.
        // _TAG03 Cursor

// Access
	inline operator const char*() const {return((const char*)_area);};
		// A pointer to the memory location
		// _TAG04 Access

	inline char *to_c(int offset) const { return(_area+offset); };
		// A pointer to the len bytes of contiguous data corresponding to 
		// offset.
        // _TAG04 Access

	inline char item (int i) const { return(_area[i]); };
		// The character at position i.
		// REQUIRE : i >= 0 && i < length()
        // _TAG04 Access

	inline char operator[](int i) const { return(_area[i]); };
		// The character at position i.
		// REQUIRE : i >= 0 && i < length()
        // _TAG04 Access


// Normal Numeric Appending
// These member functions should be used when the buffer
// is to stay within a process, or size is not an issue.
	inline void appendChar(char c)
		// Character representation at `cursor()'
		// _TAG05 Normal Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes(1) );
		(*_cursor) = c;
		_cursor++;
	};

	inline void appendShort(short i)
        // _TAG05 Normal Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( sizeof(short) ) );
		ELI_MOVE_SHORT(_cursor,&i);
		_cursor += sizeof(short);
	};

	inline void appendUnsignedShort(unsigned short i)
        // _TAG05 Normal Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes(sizeof(unsigned short) ) );
		ELI_MOVE_SHORT(_cursor,&i);
		_cursor += sizeof(unsigned short);
	};

	inline void appendInt(int i)
        // _TAG05 Normal Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( sizeof(int) ) );
		ELI_MOVE_INT(_cursor,&i);
		_cursor += sizeof(int);
	};

	inline void appendUnsignedInt(unsigned int i)
        // _TAG05 Normal Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( sizeof(unsigned int) ) );
		ELI_MOVE_INT(_cursor,&i);
		_cursor += sizeof(unsigned int);
	};

	inline void appendLong(long i)
        // _TAG05 Normal Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( sizeof(long) ) );
		ELI_MOVE_LONG(_cursor,&i);
		_cursor += sizeof(long);
	};

	inline void appendUnsignedLong(unsigned long i)
        // _TAG05 Normal Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( sizeof(unsigned long) ) );
		ELI_MOVE_LONG(_cursor,&i);
		_cursor += sizeof(unsigned long);
	};

	inline void appendBool(RTRBOOL b)
		// _TAG08 Normal Cursor Appending
	{
		appendSignedByte((s_8)b);
	};

	inline void appendFloat( float f)
        // _TAG08 Normal Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( sizeof(float) ) );
		ELI_MOVE_FLOAT( _cursor, &f );
		_cursor += sizeof(float);
	};

	inline void appendDouble( double d )
        // _TAG08 Normal Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( sizeof(double) ) );
		ELI_MOVE_DOUBLE( _cursor, &d );
		_cursor += sizeof(double);
	};

// Network Numeric Cursor Appending
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.
	inline void appendSignedByte( s_8 i)
		// _TAG06 Network Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( 1 ) );
		(*_cursor) = i;
		_cursor++;
	};

	inline void appendUnsignedByte( u_8 i)
        // _TAG06 Network Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( 1 ) );
		(*_cursor) = i;
		_cursor++;
	};

	inline void appendSigned16( s_16 i)
        // _TAG06 Network Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( 2 ) );
		ELI_MOVE_16(_cursor,&i);
		_cursor += 2;
	};

	inline void appendUnsigned16( u_16 i)
        // _TAG06 Network Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( 2 ) );
		ELI_MOVE_16(_cursor,&i);
		_cursor += 2;
	};

	inline void appendSigned32( s_32 i)
        // _TAG06 Network Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( 4 ) );
		ELI_MOVE_32(_cursor,&i);
		_cursor += 4;
	};

	inline void appendUnsigned32( u_32 i)
        // _TAG06 Network Numeric Cursor Appending
	{
		RTPRECONDITION( canAppendBytes( 4 ) );
		ELI_MOVE_32(_cursor,&i);
		_cursor += 4;
	};

// Network Numeric Cursor Appending
// These operations are used for bandwidth efficient
// transmission of numeric values.
	inline void appendChainU15( u_16 value )
		// Put a chained 15 bit value. Any value
		// less than 128 will be transmitted in one byte.
		// The high order bit of the first byte tells you if
		// there is another byte in the value.
	{
		RTPRECONDITION( canAppendBytes( 2 ) );	// Worst case.
		_cursor += ELI_PUT_CHAIN_U15(_cursor,&value);
	};

// Normal Cursor Appending.
// Efficiency routines.
	inline void appendBuffer( char *buffer, int len )
		// Append 'buffer' at the cursor.
		// REQUIRE : buffer can hold len bytes.
        // _TAG09 Normal Cursor Appending -- Effieciency routines
	{
		RTPRECONDITION( canAppendBytes( len ) );
		(void)memcpy( _cursor, buffer, (unsigned int) len );
		_cursor += len;
	};

	inline void appendBuffer( const char *buffer, int len )
		// Append 'buffer' at the cursor.
		// REQUIRE : buffer can hold len bytes.
        // _TAG09 Normal Cursor Appending -- Effieciency routines
	{
		RTPRECONDITION( canAppendBytes( len ) );
		(void)memcpy( _cursor, buffer, (unsigned int) len );
		_cursor += len;
	};

// Non-cursor based writing
	inline void putChar(char c, char *loc)
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(char) );
		// _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes(loc, 1) );
		(*loc) = c;
	};

	inline void putShort(short i, char *loc)
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(short) );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, sizeof(short) ) );
		ELI_MOVE_SHORT(loc,&i);
	};

	inline void putUnsignedShort( unsigned short i, char *loc )
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(unsigned short) );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes(loc, sizeof(unsigned short) ) );
		ELI_MOVE_SHORT(loc,&i);
	};

	inline void putInt(int i, char *loc )
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(int) );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes(loc, sizeof(int) ) );
		ELI_MOVE_INT(loc,&i);
	};

	inline void putUnsignedInt( unsigned int i, char *loc )
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(unsigned int) );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, sizeof(unsigned int) ) );
		ELI_MOVE_INT(loc,&i);
	};

	inline void putLong( long i, char *loc )
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(long) );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, sizeof(long) ) );
		ELI_MOVE_LONG(loc,&i);
	};

	inline void putUnsignedLong( unsigned long i, char *loc)
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(unsigned long) );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, sizeof(unsigned long) ) );
		ELI_MOVE_LONG(loc,&i);
	};

	inline void putBool( RTRBOOL i, char *loc)
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(RTRBOOL) );
        // _TAG11 Normal Numeric Insertion
	{
		putChar((char)i,loc);
	};

	inline void putFloat( float i, char *loc)
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(unsigned) );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, sizeof(float) ) );
		ELI_MOVE_FLOAT(loc,&i);
	};

	inline void putDouble( double i, char *loc)
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(double) );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, sizeof(double) ) );
		ELI_MOVE_DOUBLE(loc,&i);
	};


// Network Numeric Insertion
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.
	void putSignedByte(s_8 i, char *loc)
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(char) );
		// _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes(loc, 1) );
		(*loc) = i;
	};

	void putUnsignedByte(u_8 i, char *loc)
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, sizeof(char) );
		// _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes(loc, 1) );
		(*loc) = i;
	};

	void putSigned16(s_16 i, char *loc)
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, 2 );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, 2 ) );
		ELI_MOVE_16(loc,&i);
	};

	void putUnsigned16( u_16 i, char *loc )
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, 2 );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, 2 ) );
		ELI_MOVE_16(loc,&i);
	};

	void putSigned32(s_32 i, char *loc)
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, 4 );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, 4 ) );
		ELI_MOVE_32(loc,&i);
	};

	void putUnsigned32( u_32 i, char *loc )
		// REQUIRE: validAddress(loc);
		// REQUIRE: canPutBytes( loc, 4 );
        // _TAG11 Normal Numeric Insertion
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, 4 ) );
		ELI_MOVE_32(loc,&i);
	};


// Network Numeric Cursor Appending
// These operations are used for bandwidth efficient
// transmission of numeric values.
	inline int putChainU15( u_16 value, char *loc )
		// Put a chained 15 bit value. Any value
		// less than 128 will be transmitted in one byte.
		// The high order bit of the first byte tells you if
		// there is another byte in the value.
		// Returns : number of bytes used to transmit the
		// value.
	{
		RTPRECONDITION( validAddress(loc) );
		RTPRECONDITION( canPutBytes( loc, 2 ) );
		return(ELI_PUT_CHAIN_U15(loc,&value));
	};


// Non - Cursor Appending
// More efficiency stuff
	void copyToBuffer( char *buffer, int offset, int len )
		// Copy 'buffer' into this buffer starting at my local
		// (buffer()+offset) address.
		// REQUIRE : buffer can hold len bytes.
		// _TAG10 Non - Cursor Appending
	{
		RTPRECONDITION( offset > 0 );
		RTPRECONDITION( canAppendBytes( offset, len ) );
		(void)memcpy( (char *)(_area + offset), buffer, (unsigned int) len );
	};

	void copyToBuffer( const char *buffer, int offset, int len )
		// Copy 'buffer' into this buffer starting at my local
		// (buffer()+offset) address.
		// REQUIRE : buffer can hold len bytes.
		// _TAG10 Non - Cursor Appending
	{
		RTPRECONDITION( offset > 0 );
		RTPRECONDITION( canAppendBytes( offset, len ) );
		(void)memcpy( (char *)(_area + offset), buffer, (unsigned int) len );
	};

	void copyToBuffer( char *buffer, char *myLoc, int len )
		// Copy 'buffer' into this buffer starting at my local
		// myLoc address.
		// _TAG10 Non - Cursor Appending
	{
		RTPRECONDITION( validAddress(myLoc) );
		RTPRECONDITION( canAppendBytes(loc,len) );
		(void)memcpy( myLoc, buffer, (unsigned int) len );
	};

	void copyToBuffer( const char *buffer, char *myLoc, int len )
		// Copy 'buffer' into this buffer starting at my local
		// myLoc address.
		// _TAG10 Non - Cursor Appending
	{
		RTPRECONDITION( validAddress(myLoc) );
		RTPRECONDITION( canAppendBytes(loc,len) );
		(void)memcpy( myLoc, buffer, (unsigned int) len );
	};


protected:

	char *_area;
	char *_cursor;
	char *_end;

};

#endif
