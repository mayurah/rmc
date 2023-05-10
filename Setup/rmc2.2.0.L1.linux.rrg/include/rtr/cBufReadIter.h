//
//|---------------------------------------------------------------
//|                Copyright (C) 2000 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//

#ifndef __rtr_cBufReadIter_h
#define __rtr_cBufReadIter_h

#include <memory.h>
#include "rtr/rtrdefs.h"
#include "rtr/rtdataty.h"
#include "rtr/eli_net.h"
#include "rtr/os.h"

// Synopsis:
//
// Description:
//	This class provides generate iterations over a c buffer.
//	Any integer based indices start from position 0.
//
// See Also:
//

class cBufReadIter
{
public:

// Constructor
	inline cBufReadIter() : _area(0), _cursor(0), _end(0) {};
		// Initialize the parser.
		// ENSURE: !hasBuffer()
		// _TAG Constructor

	inline cBufReadIter( char *buffer, int length ) :
			_area(buffer), _cursor(buffer), _end(buffer+length) {};
		// Initialize the parser with buffer and length.
		// ENSURE: hasBuffer()
		// ENSURE: begin() == buffer
		// ENSURE: end() == buffer + length
		// ENSURE: length() == length
		// ENSURE: cursor() == begin()
		// _TAG Constructor

	inline cBufReadIter( char *buffer, char *end ) :
			_area(buffer), _cursor(buffer), _end(end) {};
		// Initialize the parser with buffer and the pointer to
		// one address past the end of the buffer.
		// ENSURE: hasBuffer()
		// ENSURE: begin() == buffer
		// ENSURE: end() == end
		// ENSURE: length() == (end() - begin())
		// ENSURE: cursor() == begin()
		// _TAG Constructor

// Destructor
	inline ~cBufReadIter() {};
		// _TAG Destructor

// Initializor
	inline void clear() { _area=_cursor=_end=0; };
        // _TAG01 Initializor

	inline void reinitialize( char *buffer, int length )
		// Initialize the parser with buffer and length.
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
		// Initialize the parser with buffer and the pointer to
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
	inline int length() const { return (int)(_end-_area); };
		// Number of bytes currently stored.
		// _TAG02 Attributes

	inline char *begin() const { return(_area); };
	inline char *buffer() const { return(_area); };
        // _TAG02 Attributes

	inline char *end() const { return(_end); };
		// One address after the last byte in the buffer;
        // _TAG02 Attributes

	inline RTRBOOL empty() const { return((_area >= _end) ? RTRTRUE : RTRFALSE ); };
		// Is the buffer empty?
        // _TAG02 Attributes

	inline RTRBOOL hasBuffer() const { return((_area == 0) ? RTRFALSE : RTRTRUE); };
        // _TAG02 Attributes

// Cursor
	inline char *cursor() const { return(_cursor); };
		// The address on which the next read operation will take effect.
		// _TAG03 Cursor

	inline void start() { _cursor = _area; };
		// Initialize cursor() to the start of the buffer.
        // _TAG03 Cursor

	inline RTRBOOL off() const { return((_cursor >= _end) ? RTRTRUE : RTRFALSE); };
		// Have the entire contents of Current been read?
        // _TAG03 Cursor

	inline void setReadCursor(char* newpos) { _cursor=newpos; };
		// Move the read cursor to index i.
		// Allowed to be beyond end-of-buffer.
		// ENSURE:	cursor() = newpos
        // _TAG03 Cursor

	inline void incrementReadCursor(int i) { _cursor+=i; };
		// Increment the read cursor by `i' bytes.
		// Allowed to be beyond end-of-buffer.
		// REQUIRE:	i >= 0;
		// ENSURE:	cursor() = old cursor() + i
        // _TAG03 Cursor

	inline RTRBOOL bytesAvailable(int nbytes) const
		// Are `nbytes' bytes left in `this' starting at cursor()?
        // _TAG03 Cursor
	{
		return( ((_cursor+nbytes) <= _end) ? RTRTRUE : RTRFALSE);
	};

	inline RTRBOOL bytesAvailable(int pos, int nbytes) const
		// Are `nbytes' bytes left in `this' starting at position `pos'?
        // _TAG03 Cursor
	{
		return( ((_area+pos+nbytes) <= _end) ? RTRTRUE : RTRFALSE);
	};

	inline RTRBOOL isReadEven() const
		// Is cursor() on an even boundary?
        // _TAG03 Cursor
	{
#ifdef COMPILE_64BITS
		return(((!((rtrUInt64)_area & 1)) &&
			((rtrUInt64)_cursor & 1)) || 
			(((rtrUInt64)_area & 1) &&
			(!((rtrUInt64)_cursor & 1))) );
#else
		return(((!((u_32)_area & 1)) && ((u_32)_cursor & 1)) || 
				(((u_32)_area & 1) && (!((u_32)_cursor & 1))) );
#endif
	};

	inline RTRBOOL isLengthEven() const
		// Is length() on an event boundary?
        // _TAG03 Cursor
	{
#ifdef COMPILE_64BITS
		return(((!((rtrUInt64)_area & 1)) &&
			(!((rtrUInt64)_end & 1))) || 
			(((rtrUInt64)_area & 1) &&
			((rtrUInt64)_cursor & 1)) );
#else
		return(((!((u_32)_area & 1)) && (!((u_32)_end & 1))) || 
					(((u_32)_area & 1) && ((u_32)_cursor & 1)) );
#endif
	};

	inline void moveCursorTo(char c)
		// Move cursor() to the first occurrence of c. Go "off"
		// if no such character is found.
		// ENSURE : off() || ( item(cursor() = c )
        // _TAG03 Cursor
	{
		char *ptr = (char*)memchr(_area, c, (_end-_area));
		if (ptr)
			_cursor = ptr;
		else
			_cursor = _end;
	}

	inline void moveReadEven() { if (!isReadEven()) _cursor++; };
		// Position the read cursor on the next event boundary.
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

// Normal Numeric Cursor retrieval
// These member functions should be used when the buffer
// is to stay within a process, or size is not an issue.
	inline char getChar()
		// Character representation at `cursor()'
		// _TAG05 Normal Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable(1) );
		char val=(*_cursor);
		_cursor++;
		return val;
	};

	inline short getShort()
        // _TAG05 Normal Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( sizeof(short) ) );
		short value = 0;
		ELI_MOVE_SHORT(&value, _cursor);
		_cursor += sizeof(short);
		return(value);
	};

	inline unsigned short getUnsignedShort()
        // _TAG05 Normal Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable(sizeof(unsigned short) ) );
		unsigned short value = 0;
		ELI_MOVE_SHORT(&value, _cursor);
		_cursor += sizeof(unsigned short);
		return(value);
	};

	inline int getInt()
        // _TAG05 Normal Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( sizeof(int) ) );
		int value = 0;
		ELI_MOVE_INT(&value, _cursor);
		_cursor += sizeof(int);
		return value;
	};

	inline unsigned int getUnsignedInt()
        // _TAG05 Normal Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( sizeof(unsigned int) ) );
		unsigned int value = 0;
		ELI_MOVE_INT(&value, _cursor);
		_cursor += sizeof(unsigned int);
		return value;
	};

	inline long getLong()
        // _TAG05 Normal Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( sizeof(long) ) );
		long value = 0;
		ELI_MOVE_LONG(&value, _cursor);
		_cursor += sizeof(long);
		return value;
	};

	unsigned long getUnsignedLong()
        // _TAG05 Normal Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( sizeof(unsigned long) ) );
		unsigned long value = 0;
		ELI_MOVE_LONG(&value, _cursor);
		_cursor += sizeof(unsigned long);
		return value;
	};

	inline RTRBOOL getBool()
		// _TAG08 Normal Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( 1 ) );
		char value = *(_cursor);
		_cursor++;
		return(value ? RTRTRUE : RTRFALSE);
	};

	inline float getFloat()
        // _TAG08 Normal Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( sizeof(float) ) );
		float value = 0.0;
		ELI_MOVE_FLOAT (&value, _cursor);
		_cursor += sizeof(float);
		return value;
	};

	inline double getDouble()
        // _TAG08 Normal Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( sizeof(double) ) );
		double value = 0.0;
		ELI_MOVE_DOUBLE (&value, _cursor);
		_cursor += sizeof(double);
		return value;
	};

// Network Numeric Cursor retrieval
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.
	inline s_8 getSignedByte()
		// _TAG06 Network Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( 1 ) );
		s_8 value = 0;
		ELI_MOVE_8 (&value, _cursor);
		_cursor++;
		return value;
	};

	inline u_8 getUnsignedByte()
        // _TAG06 Network Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( 1 ) );
		u_8 value = 0;
		ELI_MOVE_8 (&value, _cursor);
		_cursor++;
		return value;
	};

	inline s_16 getSigned16()
        // _TAG06 Network Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( 2 ) );
		s_16 value = 0;
		ELI_MOVE_16 (&value, _cursor);
		_cursor += 2;
		return value;
	};

	inline u_16 getUnsigned16()
        // _TAG06 Network Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( 2 ) );
		u_16 value = 0;
		ELI_MOVE_16 (&value, _cursor);
		_cursor += 2;
		return value;
	};

	inline s_32 getSigned32()
        // _TAG06 Network Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( 4 ) );
		s_32 value = 0;
		ELI_MOVE_32 (&value, _cursor);
		_cursor += 4;
		return value;
	};

	inline u_32 getUnsigned32()
        // _TAG06 Network Numeric Cursor retrieval
	{
		RTPRECONDITION( bytesAvailable( 4 ) );
		u_32 value = 0;
		ELI_MOVE_32 (&value, _cursor);
		_cursor += 4;
		return value;
	};

// Efficient versions.
	inline void getSignedByte( s_8* valptr)
		// _TAG07 Efficient versions
	{
		RTPRECONDITION( bytesAvailable( 1 ) );
		ELI_MOVE_8 (valptr, _cursor);
		_cursor++;
	};

	inline void getUnsignedByte( u_8* valptr)
        // _TAG07 Efficient versions
	{
		RTPRECONDITION( bytesAvailable( 1 ) );
		ELI_MOVE_8 (valptr, _cursor);
		_cursor++;
	};

	inline void getSigned16( s_16* valptr)
        // _TAG07 Efficient versions
	{
		RTPRECONDITION( bytesAvailable( 2 ) );
		ELI_MOVE_16 (valptr, _cursor);
		_cursor += 2;
	};

	inline void getUnsigned16( u_16* valptr)
        // _TAG07 Efficient versions
	{
		RTPRECONDITION( bytesAvailable( 2 ) );
		ELI_MOVE_16 (valptr, _cursor);
		_cursor += 2;
	};

	inline void getSigned32( s_32* valptr)
        // _TAG07 Efficient versions
	{
		RTPRECONDITION( bytesAvailable( 4 ) );
		ELI_MOVE_32 (valptr, _cursor);
		_cursor += 4;
	};

	inline void getUnsigned32( u_32* valptr)
        // _TAG07 Efficient versions
	{
		RTPRECONDITION( bytesAvailable( 4 ) );
		ELI_MOVE_32 (valptr, _cursor);
		_cursor += 4;
	};

// Network Numeric Cursor Appending
// These operations are used for bandwidth efficient
// transmission of numeric values.
	inline u_16 getChainU15()
        // _TAG09 Special Cursor retrieval -- Effieciency routines
		// Retrieve a chained 15 bit value. Any value
		// less than 128 will be transmitted in one byte.
		// The high order bit of the first byte tells you if
		// there is another byte in the value.
	{
		RTPRECONDITION( bytesAvailable( 2 ) );	// Worst case.
		u_16 value;
		_cursor += ELI_GET_CHAIN_U15(&value,_cursor);
		return(value);
	};

	inline void getChainU15( u_16* valptr )
        // _TAG09 Special Cursor retrieval -- Effieciency routines
		// Retrieve a chained 15 bit value. Any value
		// less than 128 will be transmitted in one byte.
		// The high order bit of the first byte tells you if
		// there is another byte in the value.
	{
		RTPRECONDITION( bytesAvailable( 1 ) );	// Worst case.
		_cursor += ELI_GET_CHAIN_U15(valptr,_cursor);
	};

// Normal Cursor retrieval.
// Efficiency routines.
	inline void getBuffer( char *buffer, int len )
		// REQUIRE : buffer can hold len bytes.
        // _TAG09 Normal Cursor retrieval -- Effieciency routines
	{
		RTPRECONDITION( bytesAvailable( len ) );
		(void)memcpy( buffer, _cursor, (unsigned int)len );
		_cursor += len;
	};

// Non - Cursor retrieval
// More efficiency stuff
	inline void copyToBuffer( char *buffer, int offset, int len )
		// REQUIRE : buffer can hold len bytes.
		// _TAG10 Non - Cursor retrieval
	{
		RTPRECONDITION( offset > 0 );
		RTPRECONDITION( bytesAvailable( offset, len ) );
		(void)memcpy( buffer, (char *)(_area + offset), (unsigned int)len );
	};

protected:

	char *_area;
	char *_cursor;
	char *_end;

};

#endif
