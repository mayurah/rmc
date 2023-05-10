//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey, R. Bonaguro
// Created: "Apr. 05 1994"
// Version: 1.0

#ifndef RTR_CONTIGUOUS_BUFFER 
#define RTR_CONTIGUOUS_BUFFER



#include "rtr/binbuf.h"

// Synopsis:
//
// Description:
//
// 	Implementation class for RTRIPCBuffer which uses a contiguous
// 	memory implementation.
//
// See Also:
// 

class RTRContiguousBuffer :
	public virtual RTRIPCBuffer
{

protected:

	char *_area;
	int _size;
	int _count;
	int _readCursor;
	int _bytesRead;


public:

// Constructors
	RTRContiguousBuffer(int size);
		// _TAG Constructor

	RTRContiguousBuffer(RTRContiguousBuffer&);
		// _TAG Constructor

// Destructor
	virtual ~RTRContiguousBuffer();
		// _TAG Destructor 

// Storage
	int capacity();
		// In bytes
		// _TAG01 Storage

	void minimize();
		// Adapt size to accomodate "exactly" count() bytes (or as close as 
		// practical).
       // _TAG01 Storage

	void resize(int newSize);
		// Adapt size to accomodate "exactly" newSize bytes (or as close as 
		// practical). If newSize is < count() truncation will occur.
       // _TAG01 Storage

	void grow(int newSize);
		// Process a hint that newSize bytes may be required.
       // _TAG01 Storage

// Comparison
	RTRBOOL operator==(RTRIPCBuffer&);
		// Is other byte-wise identical to Current?
		// _TAG02 Comparison

	RTRBOOL isEqual(char *, int n1, int n2, int position);
		// Are contents of the Current, starting from position, 
		// equal to the contents of other between positions n1 and n2?
        // _TAG02 Comparison

// Transform
	void wipeOut();
		// Re-initialize buffer 
		// This includes zeroing out the buffer memory
		// ENSURE: count() == 0 && readCursor() == 0;
		// _TAG03 Transform

	void clear();
		// Clear out the buffer
		// ENSURE: count() == 0 && readCursor() == 0;
		// _TAG03 Transform

	void copy(RTRIPCBuffer& other, int n1, int n2);
		// Initialize Current to the contents of other between positions
		// n1 and n2.
		// REQUIRE : n1 >= 1; n1 <= n2; n2 <= other.count()
		// ENSURE : isEqual(other.to_c(1), n1, n2, 1)
		// _TAG03 Transform

// State
	int count();
		// Number of bytes currently stored.
		// _TAG04 State

	RTRBOOL empty();
		// Is the buffer empty?
		// _TAG04 State

// Read Cursor
	int readCursor();
		// The index on which the next read operation will take effect.
		// _TAG05 Read Cursor

	void start();
		// Initialize readCursor() to the start of the buffer.
		// _TAG05 Read Cursor

	void forth();
		// Move the readCursor() to past the last item read.
        // _TAG05 Read Cursor

	RTRBOOL off();
		// Have the entire contents of Current been read?
        // _TAG05 Read Cursor

	int bytesRead();
		// The number of bytes last read from the buffer. Use forth() to
		// move the readCursor()
        // _TAG05 Read Cursor

	void setReadCursor(int i);
		// Move the read cursor to index i.
		// REQUIRE: i >= 1;
		// ENSURE : i <= count()
        // _TAG05 Read Cursor

	RTRBOOL bytesAvailable(int cplusplus);
		// Are cplusplus bytes left in Current.
        // _TAG05 Read Cursor

	RTRBOOL isReadEven();
		// Is readCursor() on an event boundary?
        // _TAG05 Read Cursor

	RTRBOOL isCountEven();
		// Is count() on an event boundary?
        // _TAG05 Read Cursor

	RTRBOOL canPutBytes(int reality, int position);
		// Can reality bytes be put into buffer at position?
        // _TAG05 Read Cursor

	void search(char c);
		// Move readCursor() to the first occurrence of c. Go "off"
		// if no such character is found.
		// ENSURE : off() || ( *(to_c(readCursor())) == c )
        // _TAG05 Read Cursor

	void moveReadEven();
		// Position the read cursor on the next event boundary.
        // _TAG05 Read Cursor

// Basic Manipulation
	void moveCountEven();
		// Set count() to the next event boundary.
		// _TAG06 Basic Manipulation

	void incrementCount(int nbytes);
		// _TAG06 Basic Manipulation

	void setCount(int i);
		// _TAG06 Basic Manipulation

// Access
	operator const char*() const;
		// A pointer to the memory location
		// _TAG07 Access

	char *to_c(int i);
		// A pointer to the memory location corresponding to offset i.
        // _TAG07 Access

	char item (int i);
		// The character at position i.
		// REQUIRE : i >= 0 && i <= count()
        // _TAG07 Access

	char operator[](int i);
		// The character at position i.
		// REQUIRE : i >= 0 && i <= count()
        // _TAG07 Access

// Normal Numeric Cursor retrieval
// These member functions should be used when the buffer
// is to stay within a process, or size is not an issue.
	char getChar();
		// Character representation at `readCursor()'
		// _TAG08 Normal Numeric Cursor retrieval

	short getShort();
        // _TAG08 Normal Numeric Cursor retrieval

	unsigned short getUnsignedShort();
        // _TAG08 Normal Numeric Cursor retrieval

	int getInt();
        // _TAG08 Normal Numeric Cursor retrieval

	unsigned int getUnsignedInt();
        // _TAG08 Normal Numeric Cursor retrieval

	long getLong();
        // _TAG08 Normal Numeric Cursor retrieval

	unsigned long getUnsignedLong();
        // _TAG08 Normal Numeric Cursor retrieval


// Network Numeric Cursor retrieval
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.
	s_8 getSignedByte();
		// _TAG09 Network Numeric Cursor retrieval

	u_8 getUnsignedByte();
        // _TAG09 Network Numeric Cursor retrieval

	s_16 getSigned16();
        // _TAG09 Network Numeric Cursor retrieval

	u_16 getUnsigned16();
        // _TAG09 Network Numeric Cursor retrieval

	s_32 getSigned32();
        // _TAG09 Network Numeric Cursor retrieval

	u_32 getUnsigned32();
        // _TAG09 Network Numeric Cursor retrieval

// Normal Cursor retrieval.
	RTRBOOL getBool();
		// _TAG10 Normal Cursor retrieval

	float getFloat();
        // _TAG10 Normal Cursor retrieval

	double getDouble();
        // _TAG10 Normal Cursor retrieval

	RTRString getString(int len);
        // _TAG10 Normal Cursor retrieval

// Normal Cursor retrieval.
// Efficiency routines.
	void	getSubBuffer( RTRIPCBuffer& aBuffer, int num_bytes );
		// _TAG11 Normal Cursor retrieval -- Efficiency routines

	void	getCBuffer( char *buffer, int len );
		// REQUIRE : buffer can hold len bytes.
        // _TAG11 Normal Cursor retrieval -- Efficiency routines

// Normal Numeric Appending.
	void appendChar(char c);
		// _TAG12 Normal Numeric Appending

	void appendShort(short i);
        // _TAG12 Normal Numeric Appending

	void appendUnsignedShort( unsigned short i);
        // _TAG12 Normal Numeric Appending

	void appendInt(int i);
        // _TAG12 Normal Numeric Appending

	void appendUnsignedInt( unsigned int i);
        // _TAG12 Normal Numeric Appending

	void appendLong( long i );
        // _TAG12 Normal Numeric Appending

	void appendUnsignedLong( unsigned long i );
        // _TAG12 Normal Numeric Appending

// Network Numeric Appending.
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.
	void appendByte( s_8 i );
		// _TAG13 Network Numeric Appending

	void appendUnsignedByte( u_8 i );
        // _TAG13 Network Numeric Appending

	void appendSigned16( s_16 i );
        // _TAG13 Network Numeric Appending

	void appendUnsigned16( u_16 i );
        // _TAG13 Network Numeric Appending

	void appendSigned32( s_32 i );
        // _TAG13 Network Numeric Appending

	void appendUnsigned32( u_32 i );
        // _TAG13 Network Numeric Appending

// Normal Appending
	void appendFloat(float f);
		// _TAG14 Normal Appending

	void appendDouble( double d );
        // _TAG14 Normal Appending

	void appendBool(RTRBOOL b);
        // _TAG14 Normal Appending

	void appendString(RTRString&);
        // _TAG14 Normal Appending

	void appendBuffer(RTRIPCBuffer&);
        // _TAG14 Normal Appending

	void appendCBuffer( char *buffer, int len );
        // _TAG14 Normal Appending

// Normal Numeric Insertion
	void putChar(char c, int position);
		// _TAG15 Normal Numeric Insertion

	void putShort(short i, int position);
        // _TAG15 Normal Numeric Insertion

	void putUnsignedShort( unsigned short i, int position);
        // _TAG15 Normal Numeric Insertion

	void putInt(int i, int position);
        // _TAG15 Normal Numeric Insertion

	void putUnsignedInt( unsigned int i, int position);
        // _TAG15 Normal Numeric Insertion

	void putLong( long i, int position );
        // _TAG15 Normal Numeric Insertion

	void putUnsignedLong( unsigned long i, int position );
        // _TAG15 Normal Numeric Insertion

// Network Numeric Insertion
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.

	void putByte( s_8 i, int position );
		// _TAG16 Network Numeric Insertion

	void putUnsignedByte( u_8 i, int position );
        // _TAG16 Network Numeric Insertion

	void putSigned16( s_16 i, int position );
        // _TAG16 Network Numeric Insertion

	void putUnsigned16( u_16 i, int position );
        // _TAG16 Network Numeric Insertion

	void putSigned32( s_32 i, int position );
        // _TAG16 Network Numeric Insertion

	void putUnsigned32( u_32 i, int position );
        // _TAG16 Network Numeric Insertion

// Normal Insertion

	void putFloat(float f, int position);
		// _TAG17 Normal Insertion

	void putDouble(double f, int position);
        // _TAG17 Normal Insertion

	void putBool(RTRBOOL b, int position);
        // _TAG17 Normal Insertion

	void putString(RTRString&, int position);
        // _TAG17 Normal Insertion

	void putString(RTRString& str, int n1, int n2, int position);
		// REQUIRE : n1 >= 1; n1 <= n2; n2 <= str.count()
        // _TAG17 Normal Insertion

	void putCString(const char *s, int n1, int n2, int p);
		// REQUIRE : n1 >= 1; n1 <= n2
        // _TAG17 Normal Insertion

};


#endif /* RTR_CONTIGUOUS_BUFFER */


