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

#ifndef __RTR_BUFFER_READ_ITERATOR
#define __RTR_BUFFER_READ_ITERATOR

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

#include "rtr/bfwrtit.h"


// Synopsis:
// #include "rtr/bfreadit.h"
//
// "//" RTRBuffer& buffer;
// RTRBufferReadIterator readIt(buffer);
// readIt.start();
// u_16 _msgOpcode = readIt.getUnsigned16();
// readIt.forth();
// if (_msgOpcode = 45 && readIt.bytesAvailable(sizeof(u_32)))
// {
//	u_32 _msgTextLength = readIt.getUnsigned32();
//	readIt.forth();
//	if (readIt.bytesAvailable(_stringPartLength))
//	{
//		RTRString tmpStr = readIt.getString( _msgTextLength );
//		cout<<"Got message of type "<<_msgOpcode<<endl;
//		cout<<"Message Text is: "<<tmpStr<<endl;
//	}
//}
//
// Description:
//	RTRBufferReadIterator provides methods used to extract
//	typed data from an instance of RTRBuffer.
// 
//	The buffer upon which the iterator operates may be provided
//	at construction and/or may be provided via one of the
//	reinitialize() methods.
// 
//	Methods are provided to extract data as variable sized numeric
//	values, variable sized strings, characters and boolean values.
//	Byte swapping automatically occurs on these values so the user
//	need not be concerned with the machine architecture of the sender.
//
//	Upon obtaining an instance of RTRBufferReadIterator, the user
//	calls the start() method to position the read cursor at the
//	beginning of the message. The various "get" methods are used to
//	extract typed data from the message. To move to the next data
//	element, the forth() method is invoked. The off() method is
//	called to determine when there is no more message data to be
//	extracted.
//
//	As an example, the getString() method takes a length as a parameter
//	and returns an instance of RTRString that contains the message data
//	starting at readCursor() and ending at readCursor() + length. The
//	getSigned32() method returns a 4-byte signed integer value of type
//	u_32. The getUnsigned16() method returns a 2-byte unsigned integer
//	value of type u_16.
//
// See Also:
//	RTRBuffer, RTRBufferWriteIterator
//

class RTRBufferReadIterator
{

#ifndef _RDEV_NO_STL_
friend  std::ostream& operator<<(std::ostream& os, const RTRBufferReadIterator& );
#else
public:
void print(FILE* os);
#endif

protected:

	RTRBuffer	*_buffer;

	char		*_area;
	int			_count;
	int			_readCursor;
	int			_bytesRead;
	int			_offset;


public:


// Constructor
	RTRBufferReadIterator();
		// Create a read iterator with no underlying buffer.
		// _TAG Constructor

	RTRBufferReadIterator( RTRBuffer& aBuffer );
		// Create a read iterator that operates on the given buffer.  The 
		// readCursor() will start at the beginning of the buffer.
		// _TAG Constructor

	RTRBufferReadIterator( RTRBuffer& aBuffer, int offset );
		// Create a read iterator that operates on the given buffer.  The 
		// readCursor() will start at the offset in the buffer.
		// _TAG Constructor

	RTRBufferReadIterator( RTRBuffer& aBuffer, int offset, int size );
		// Create a read iterator that operates on the given buffer.  The 
		// readCursor() will start at the offset in the buffer.  count()
		// is set to size.
		// _TAG Constructor

// Destructor
	~RTRBufferReadIterator();
		// _TAG Destructor

// Initializor

	// Reinitialize the read iterator to use the given buffer, starting at 
	// the given offset in the buffer. count() is set to size.
	// ENSURE: hasBuffer();
	// _TAG02 Initializor
	inline void reinitialize( RTRBuffer& aBuffer, int offset, int size )
	{

		_buffer = &aBuffer;
		_offset = offset;
		_count = size;

		_area = aBuffer.to_c(1) + offset;

		_readCursor = 0;
		_bytesRead = 0;

		RTPOSTCONDITION( hasBuffer() );
	};

	// Reinitialize the read iterator to use the given buffer, starting at 
	// the given offset in the buffer. 
	// ENSURE: hasBuffer(); 
	// _TAG02 Initializor
	inline void reinitialize( RTRBuffer& aBuffer, int offset=0 )
	{
		reinitialize( aBuffer, offset, (aBuffer.count()-offset) );

		RTPOSTCONDITION( hasBuffer() );
	};

	// Sets this iterator to an unitialized state. 
	// REQUIRE: hasBuffer(); 
	// ENSURE: !hasBuffer();
	// _TAG02 Initializor
	inline void doneReading()
	{
		RTPRECONDITION( hasBuffer() );

		_buffer = 0;
		_area = 0;

		RTPOSTCONDITION( !hasBuffer() );
	};


// State

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

	// The buffer currently used for iteration
	// _TAG01 State
	inline RTRBuffer & buffer()
	{
		return(*_buffer);
	};

	// Is this iterator initialized with a buffer?
	// _TAG03 Operation 
	inline RTRBOOL hasBuffer() const
	{
		return((_buffer == 0) ? RTRFALSE : RTRTRUE);
	};

	// The offset into buffer() where readCursor() is set when 
	// start() is called.
	// _TAG01 State
	inline int offset() const
	{
		return( _offset );
	};


// Read Cursor
	// The index on which the next read operation will take effect.
	// _TAG04 Read Cursor
	inline int readCursor() const
	{
		return( _readCursor );
	};

	// Initialize readCursor() to the start of the buffer.
	// _TAG04 Read Cursor
	inline void start()
	{
		_readCursor = (_count == 0) ? 0 : 1;
		_bytesRead = 0;
	};

	// Move the readCursor() to past the last item read.
	// _TAG04 Read Cursor
	inline void forth()
	{
		_readCursor += _bytesRead;
		_bytesRead = 0;
	};

	// Have the entire contents of Current been read?
	// _TAG04 Read Cursor
	inline RTRBOOL off() const
	{
		return (_readCursor > _count || _readCursor == 0) ? RTRTRUE : RTRFALSE;
	};

	// The number of bytes last read from the buffer. Use forth() to
	// move the readCursor()
	// _TAG04 Read Cursor
	inline int bytesRead() const
	{
		return(_bytesRead);
	};

	// Move the read cursor to index i.  Allow the read cursor
	// to be beyond the end of the buffer.
	// REQUIRE: i >= 1 
	// ENSURE:  readCursor() = i
	// _TAG04 Read Cursor
	inline void setReadCursor(int i)
	{
		RTPRECONDITION( i > 0 );

		_readCursor = i;

		RTPOSTCONDITION( readCursor() == i );
	};

	// Increment the read cursor by `i'.  Allow the read cursor
	// to be beyond the end of the buffer. 
	// REQUIRE: i >= 0; 
	// ENSURE:  readCursor() = old readCursor() + i
	// _TAG04 Read Cursor
	inline void incrementReadCursor(int i)
	{
		RTPRECONDITION( i >= 0 );

		_readCursor += i;
	};

	// Are `nbytes' bytes left in `this' starting at readCursor()?
	// _TAG04 Read Cursor
	inline RTRBOOL bytesAvailable(int nbytes) const
	{
		return ((_readCursor + nbytes) - 1 <= _count) ? RTRTRUE : RTRFALSE;
	};

	// Are `nbytes' bytes left in `this' starting at position `pos'?
	// _TAG04 Read Cursor
	inline RTRBOOL bytesAvailable(int pos, int nbytes) const
	{
		return ((pos + nbytes) - 1 <= _count) ? RTRTRUE : RTRFALSE;
	};

	// Is readCursor() on an even boundary?
	// _TAG04 Read Cursor
	inline RTRBOOL isReadEven() const
	{
		return (_readCursor & 1) ? RTRTRUE : RTRFALSE;
	};

	// Is count() on an event boundary?
	// _TAG04 Read Cursor
	inline RTRBOOL isCountEven() const
	{
		return (_count & 1) ? RTRFALSE : RTRTRUE;
	};

	// Move readCursor() to the first occurrence of c. Go "off"
	// if no such character is found. 
	// ENSURE : off() || ( *(to_c(readCursor())) == c )
	// _TAG04 Read Cursor
	inline void search(char c)
	{
		char *ptr = (char*)memchr(_area, c, (unsigned int)_count);
		if (ptr)
			_readCursor = (int)(ptr - _area + 1);
		else
			_readCursor = 0;

		_bytesRead = 0;
	};

	// Position the read cursor on the next event boundary.
	// _TAG04 Read Cursor
	inline void moveReadEven()
	{
		if (!isReadEven())
			_readCursor++;
	};


// Access

	// A pointer to the memory location
	// _TAG05 Access
	inline operator const char*() const
	{
		char *temp=_area;
		return(temp);
	};

// Stop warnings about len not used when assertions disabled.

	// A pointer to the len bytes of contiguous data corresponding to
	// offset i. 
	// REQUIRE: offset > 0 
	// REQUIRE: len >= 0 
	// REQUIRE: (offset + len - 1) <= count()
	// _TAG05 Access
#ifdef RTDEBUG
	inline char *to_c(int offset, int len) const
#else
	inline char *to_c(int offset, int) const
#endif
	{
		RTPRECONDITION( offset > 0 );
		RTPRECONDITION( len >= 0 );
		RTPRECONDITION( (offset + len - 1) <= count() );

		return(_area + offset - 1);
	};

	// A pointer to the memory location corresponding to offset i.
	// OBSOLETE: This method is flawed. The interface implies access to a
	// "'C' string", i.e. contiguous data. There is no way for the
	// buffer to implement this properly without knowing the length
	// of data requested. Use to_c(int offset, int len)
	// _TAG05 Access
	inline char *to_c(int i) const
	{
		RTPRECONDITION( i > 0 );

		return(_area + i - 1);
	};

	// The character at position i. 
	// REQUIRE : i >= 0 && i <= count()
	// _TAG05 Access
	inline char item (int i) const
	{
		RTPRECONDITION( i >= 0 && i <= count() );

		return( _area[ i-1 ] );
	};

	// The character at position i. 
	// REQUIRE : i >= 0 && i <= count()
	// _TAG05 Access
	inline char operator[](int i) const
	{
		return( _area[ i-1 ] );
	};



// Normal Numeric Cursor retrieval
// These member functions should be used when the buffer
// is to stay within a process, or size is not an issue.

	// Character representation at `readCursor()' 
	// REQUIRE: bytesAvailable ( readCursor(), 1 ); 
	// _TAG06 Normal Numeric Cursor retrieval -- within process
	inline char getChar()
	{
		RTPRECONDITION( bytesAvailable( readCursor(), 1 ) );

		_bytesRead = 1;
		return _area[ _readCursor - 1 ];
	};

	// REQUIRE: bytesAvailable ( readCursor(), sizeof(short) );
	// _TAG06 Normal Numeric Cursor retrieval -- within process
	inline short getShort()
	{
		short value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), sizeof(short) ) );

		memcpy( (char*)&value, (_area+_readCursor-1), sizeof(short) );
		_bytesRead = sizeof(short);
		return(value);
	};

	// REQUIRE: bytesAvailable ( readCursor(), sizeof(unsigned short) );
	// _TAG06 Normal Numeric Cursor retrieval -- within process
	inline unsigned short getUnsignedShort()
	{
		unsigned short value = 0;

		RTPRECONDITION( bytesAvailable(readCursor(), sizeof(unsigned short) ) );

		memcpy( (char*)&value, (_area+_readCursor-1), sizeof(unsigned short) );
		_bytesRead = sizeof(unsigned short);
		return(value);
	};

	// REQUIRE: bytesAvailable ( readCursor(), sizeof(int) );
	// _TAG06 Normal Numeric Cursor retrieval -- within process
	inline int getInt()
	{
		int value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), sizeof(int) ) );

		memcpy( (char*)&value, (_area+_readCursor-1), sizeof(int) );
		_bytesRead = sizeof(int);
		return value;
	};

	// REQUIRE: bytesAvailable ( readCursor(), sizeof(unsigned int) );
	// _TAG06 Normal Numeric Cursor retrieval -- within process
	inline unsigned int getUnsignedInt()
	{
		unsigned int value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), sizeof(unsigned int) ) );

		memcpy( (char*)&value, (_area+_readCursor-1), sizeof(unsigned int) );
		_bytesRead = sizeof(unsigned int);
		return value;
	};

	// REQUIRE: bytesAvailable ( readCursor(), sizeof(long) );
	// _TAG06 Normal Numeric Cursor retrieval -- within process
	inline long getLong()
	{
		long value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), sizeof(long) ) );

		memcpy( (char*)&value, (_area+_readCursor-1), sizeof(long) );
		_bytesRead = sizeof(long);
		return value;
	};

	// REQUIRE: bytesAvailable ( readCursor(), sizeof(unsigned long) );
	// _TAG06 Normal Numeric Cursor retrieval -- within process
	inline unsigned long getUnsignedLong()
	{
		unsigned long value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), sizeof(unsigned long) ) );

		memcpy( (char*)&value, (_area+_readCursor-1), sizeof(unsigned long) );
		_bytesRead = sizeof(unsigned long);
		return value;
	};


// Network Numeric Cursor retrieval
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.
	
	// REQUIRE: bytesAvailable ( readCursor(), 1 );
	// _TAG07 Network Numeric Cursor retrieval
	inline s_8 getSignedByte()
	{
		s_8 value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), 1 ) );

		ELI_MOVE_8 (&value, (char *)(_area + _readCursor - 1));
		_bytesRead = 1;
		return value;
	};

	// REQUIRE: bytesAvailable ( readCursor(), 1 );
	// _TAG07 Network Numeric Cursor retrieval
	inline u_8 getUnsignedByte()
	{
		u_8 value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), 1 ) );

		ELI_MOVE_8 (&value, (char *)(_area + _readCursor - 1));
		_bytesRead = 1;
		return value;
	};

	// REQUIRE: bytesAvailable ( readCursor(), 2 );
	// _TAG07 Network Numeric Cursor retrieval
	inline s_16 getSigned16()
	{
		s_16 value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), 2 ) );

		ELI_MOVE_16 (&value, (char *)(_area + _readCursor - 1));
		_bytesRead = 2;
		return value;
	};

	// REQUIRE: bytesAvailable ( readCursor(), 2 );
	// _TAG07 Network Numeric Cursor retrieval
	inline u_16 getUnsigned16()
	{
		u_16 value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), 2 ) );

		ELI_MOVE_16 (&value, (char *)(_area + _readCursor - 1));
		_bytesRead = 2;
		return value;
	};

	// REQUIRE: bytesAvailable ( readCursor(), 4 );
	// _TAG07 Network Numeric Cursor retrieval
	inline s_32 getSigned32()
	{
		s_32 value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), 4 ) );

		ELI_MOVE_32 (&value, (char *)(_area + _readCursor - 1));
		_bytesRead = 4;
		return value;
	};

	// REQUIRE: bytesAvailable ( readCursor(), 4 );
	// _TAG07 Network Numeric Cursor retrieval
	inline u_32 getUnsigned32()
	{
		u_32 value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), 4 ) );

		ELI_MOVE_32 (&value, (char *)(_area + _readCursor - 1));
		_bytesRead = 4;
		return value;
	};


// Normal Cursor retrieval.

	// REQUIRE: bytesAvailable ( readCursor(), 1 );
	// _TAG08 Normal Cursor retrieval
	inline RTRBOOL getBool()
	{
		char value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), 1 ) );

		value = _area[ _readCursor - 1 ];
		return((RTRBOOL)value);
	};

	// REQUIRE: bytesAvailable ( readCursor(), sizeof(float) );
	// _TAG08 Normal Cursor retrieval
	inline float getFloat()
	{
		float value = (float)0;

		RTPRECONDITION( bytesAvailable( readCursor(), sizeof(float) ) );

		ELI_MOVE_FLOAT (&value, (char *)(_area + _readCursor - 1));
		_bytesRead = sizeof(float);
		return value;
	};

	// REQUIRE: bytesAvailable ( readCursor(), sizeof(double) );
	// _TAG08 Normal Cursor retrieval
	inline double getDouble()
	{
		double value = 0;

		RTPRECONDITION( bytesAvailable( readCursor(), sizeof(double) ) );

		ELI_MOVE_DOUBLE (&value, (char *)(_area + _readCursor - 1));
		_bytesRead = sizeof(double);
		return value;
	};

	// REQUIRE: bytesAvailable ( readCursor(), len );
	// _TAG08 Normal Cursor retrieval
	inline RTRString getString(int len)
	{
		RTPRECONDITION( bytesAvailable( readCursor(), len ) );

		_bytesRead = len;
		return RTRString((char *)(_area + _readCursor - 1), len);
	};

	// REQUIRE: bytesAvailable ( readCursor(), 2 );
	// _TAG08 Normal Cursor retrieval
	inline RTRString getCountedString()
	{
		RTPRECONDITION( bytesAvailable( readCursor(), 2 ) );

		int l = getUnsigned16();
		forth();
		_bytesRead = l;
		return RTRString((char *)(_area + _readCursor - 1), l);
	};

	// REQUIRE: bytesAvailable ( readCursor(), 2 );
	// _TAG08 Normal Cursor retrieval
	inline RTRObjectId getObjectId()
	{
		RTPRECONDITION( bytesAvailable( readCursor(), 2 ) );

		int l = getUnsigned16();
		forth();
		_bytesRead = l;
		return RTRObjectId((char *)(_area + _readCursor - 1), l);
	};

// Normal Cursor retrieval.
// Efficiency routines.

	// Get len bytes out of current from the read cursor
	// and put them into `str'. 
	// REQUIRE: bytesAvailable ( readCursor(), len ); 
	// REQUIRE: str.capacity() >= (unsigned int)len; 
	// _TAG09 Normal Cursor retrieval -- Efficiency routines
	inline void getString( RTRString &str, int len )
	{
		RTPRECONDITION( bytesAvailable( readCursor(), len ) );
		RTPRECONDITION( str.capacity() >= (unsigned int)len );

		_bytesRead = len;
		str.set( (_area + _readCursor - 1), len );
	};

	// Get len bytes out of current from the read cursor
	// and put them into `str'. 
	// REQUIRE: bytesAvailable ( readCursor(), len ); 
	// REQUIRE: str.capacity() >= (unsigned int)len;
	// _TAG09 Normal Cursor retrieval -- Efficiency routines
	inline void getString( RTRSmallString &str, int len )
	{
		RTPRECONDITION( bytesAvailable( readCursor(), len ) );
		RTPRECONDITION( str.capacity() >= len );

		_bytesRead = len;
		str.set( (_area + _readCursor - 1), len );
	};

	// _TAG09 Normal Cursor retrieval -- Efficiency routines
	inline void getSubBuffer( RTRBufferWriteIterator& aBuffer, int num_bytes )
	{
		_bytesRead = num_bytes;
		aBuffer.appendCBuffer( (char*)(_area + _readCursor - 1), num_bytes);
	};

	// REQUIRE: bytesAvailable ( readCursor(), len );
	// _TAG09 Normal Cursor retrieval -- Efficiency routines
	inline void getCBuffer( char *buffer, int len )
	{
		RTPRECONDITION( bytesAvailable( readCursor(), len ) );

		_bytesRead = len;
		(void)memcpy( buffer, (char *)(_area + _readCursor - 1), (unsigned int)len );
	};


// Non - Cursor retrieval
// More efficiency stuff

	// REQUIRE: bytesAvailable ( readCursor(), len ); 
	// REQUIRE: offset > 0; 
	// REQUIRE: offset < readCursor() || (offset == readCursor()) && len == 0;
	// _TAG10 Non - Cursor retrieval
	inline void copyToCBuffer( char *buffer, int offset, int len )
	{
		RTPRECONDITION( offset > 0 );
		RTPRECONDITION( offset < readCursor() || \
						 (offset == readCursor()) && len == 0);
		RTPRECONDITION( bytesAvailable( offset, len ) );

		(void)memcpy( buffer, (char *)(_area + offset - 1), (unsigned int)len );
	};


};

#endif
