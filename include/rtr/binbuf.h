//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey, R. Bonaguro
// Created: "Apr. 05 1994"
// Version: 1.0

#ifndef RTR_IPC_BUFFER 
#define RTR_IPC_BUFFER



#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

#include "rtr/rtrdefs.h"
#include "rtr/rtdataty.h"
#include "rtr/rtstring.h"
#include "rtr/rthexdmp.h"

class RTRString;

// Synopsis:
//
// Description:
//
// 	Abstract base class for a buffer which provides facillities to
// 	store arbitrary sequences of data. Storage and retrieval are
// 	architecture independent for use in networking.
// 	No memory allocation scheme is implied.
//
// 	Descendants provide the memory management scheme.
//
// See Also:
//

class RTRIPCBuffer :
	private RTRHexDump
{

#ifndef _RDEV_NO_STL_
friend  std::ostream& operator<<(std::ostream& os, RTRIPCBuffer& bbuf)
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

private:

protected:

public:

// Destructor
	virtual ~RTRIPCBuffer();
		// _TAG Destructor

// Output
	void HexDump(RTRString& aBuffer);
		// _TAG01 Output

// Storage
	virtual int capacity() = 0;
		// In bytes
		// _TAG02 Storage

	virtual void minimize() = 0;
		// Adapt size to accomodate "exactly" count() bytes (or as close as 
		// practical).
        // _TAG02 Storage

	virtual void resize(int newSize) = 0;
		// Adapt size to accomodate "exactly" newSize bytes (or as close as 
		// practical). If newSize is < count() truncation will occur.
        // _TAG02 Storage

	virtual void grow(int newSize) = 0;
		// Process a hint that newSize bytes may be required.
        // _TAG02 Storage

// Comparison
	virtual RTRBOOL operator==(RTRIPCBuffer&) = 0;
		// Is other byte-wise identical to Current?
		// _TAG03 Comparison

	virtual RTRBOOL isEqual(char *, int n1, int n2, int position) = 0;
		// Are contents of the Current, starting from position, 
		// equal to the contents of other between positions n1 and n2?
        // _TAG03 Comparison

// Transform
	virtual void wipeOut() = 0;
		// Re-initialize buffer 
		// This includes zeroing out the buffer memory.
		// ENSURE: count() == 0 && readCursor() == 0;
		// _TAG04 Transform

	virtual void clear() = 0;
		// Clear out the buffer
		// ENSURE: count() == 0 && readCursor() == 0;
        // _TAG04 Transform

	virtual void copy(RTRIPCBuffer& other, int n1, int n2) = 0;
		// Initialize Current to the contents of other between positions
		// n1 and n2.
		// REQUIRE : n1 >= 1; n1 <= n2; n2 <= other.count()
		// ENSURE : isEqual(other.to_c(1), n1, n2, 1)
        // _TAG04 Transform

// State
	virtual int count() = 0;
		// Number of bytes currently stored.
		// _TAG05 State

	virtual RTRBOOL empty() = 0;
		// Is the buffer empty?
		// _TAG05 State

// Read Cursor
	virtual int readCursor() = 0;
		// The index on which the next read operation will take effect.
		// Starts at 1.
		// _TAG06 Read Cursor

	virtual void start() = 0;
		// Initialize readCursor() to the start of the buffer.
        // _TAG06 Read Cursor

	virtual void forth() = 0;
		// Move the readCursor() to past the last item read.
        // _TAG06 Read Cursor

	virtual RTRBOOL off() = 0;
		// Have the entire contents of Current been read?
        // _TAG06 Read Cursor

	virtual int bytesRead() = 0;
		// The number of bytes last read from the buffer. Use forth() to
		// move the readCursor()
        // _TAG06 Read Cursor

	virtual void setReadCursor(int i) = 0;
		// Move the read cursor to index i.
		// REQUIRE: i >= 1;
		// ENSURE : i <= count()
        // _TAG06 Read Cursor

	virtual RTRBOOL bytesAvailable(int cplusplus) = 0;
		// Are cplusplus bytes left in Current.
        // _TAG06 Read Cursor

	virtual RTRBOOL isReadEven() = 0;
		// Is readCursor() on an event boundary?
        // _TAG06 Read Cursor

	virtual RTRBOOL isCountEven() = 0;
		// Is count() on an event boundary?
        // _TAG06 Read Cursor

	virtual RTRBOOL canPutBytes(int reality, int position) = 0;
		// Can reality bytes be put into buffer at position?
        // _TAG06 Read Cursor

	virtual void search(char c) = 0;
		// Move readCursor() to the first occurrence of c. Go "off"
		// if no such character is found.
		// ENSURE : off() || ( *(to_c(readCursor())) == c )
        // _TAG06 Read Cursor

	virtual void moveReadEven() = 0;
		// Position the read cursor on the next event boundary.
        // _TAG06 Read Cursor

// Basic Manipulation

	virtual void moveCountEven() = 0;
		// Set count() to the next event boundary.
		// _TAG07 Basic Manipulation

	virtual void incrementCount(int nbytes) = 0;
		// _TAG07 Basic Manipulation

	virtual void setCount(int i) = 0;
		// _TAG07 Basic Manipulation

// Access
	virtual operator const char*() const = 0;
		// A pointer to the memory location
		// _TAG08 Access

	virtual char *to_c(int i) = 0;
		// A pointer to the memory location corresponding to offset i.
        // _TAG08 Access

	virtual char item (int i) = 0;
		// The character at position i.
		// REQUIRE : i >= 0 && i <= count()
        // _TAG08 Access

	virtual char operator[](int i) = 0;
		// The character at position i.
		// REQUIRE : i >= 0 && i <= count()
        // _TAG08 Access

// Normal Numeric Cursor retrieval
// These member functions should be used when the buffer
// is to stay within a process, or size is not an issue.

	virtual char getChar() = 0;
		// Character representation at `readCursor()'
		// _TAG09 Normal Numeric Cursor retrieval

	virtual short getShort() = 0;
        // _TAG09 Normal Numeric Cursor retrieval

	virtual unsigned short getUnsignedShort() = 0;
        // _TAG09 Normal Numeric Cursor retrieval

	virtual int getInt() = 0;
        // _TAG09 Normal Numeric Cursor retrieval

	virtual unsigned int getUnsignedInt() = 0;
        // _TAG09 Normal Numeric Cursor retrieval

	virtual long getLong() = 0;
        // _TAG09 Normal Numeric Cursor retrieval

	virtual unsigned long getUnsignedLong() = 0;
        // _TAG09 Normal Numeric Cursor retrieval

// Network Numeric Cursor retrieval
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.

	virtual s_8 getSignedByte() = 0;
		// _TAG10 Network Numeric Cursor retrieval

	virtual u_8 getUnsignedByte() = 0;
        // _TAG10 Network Numeric Cursor retrieval

	virtual s_16 getSigned16() = 0;
        // _TAG10 Network Numeric Cursor retrieval

	virtual u_16 getUnsigned16() = 0;
        // _TAG10 Network Numeric Cursor retrieval

	virtual s_32 getSigned32() = 0;
        // _TAG10 Network Numeric Cursor retrieval

	virtual u_32 getUnsigned32() = 0;
        // _TAG10 Network Numeric Cursor retrieval

// Normal Cursor retrieval.

	virtual RTRBOOL getBool() = 0;
		// _TAG11 Normal Cursor retrieval

	virtual float getFloat() = 0;
        // _TAG11 Normal Cursor retrieval

	virtual double getDouble() = 0;
        // _TAG11 Normal Cursor retrieval

	virtual RTRString getString(int len) = 0;
        // _TAG11 Normal Cursor retrieval

// Normal Cursor retrieval.
// Efficiency routines.
	virtual void getSubBuffer( RTRIPCBuffer& aBuffer, int num_bytes ) = 0;
		// _TAG12 Normal Cursor retrieval -- Efficiency routines

	virtual void getCBuffer( char *buffer, int len ) = 0;
		// REQUIRE : buffer can hold len bytes.
        // _TAG12 Normal Cursor retrieval -- Efficiency routines

// NOT IMPLEMENTED
//	virtual void substituteChar(RTRString& str, char c) = 0;
		// Replace all occurrences of str with c and adjust count.

//	virtual void substituteString(RTRString& ostr, RTRString& nstr) = 0;
		// Replace all occurrences of ostr with nstr and adjust count.

//	virtual void substituteString(char c, RTRString& str) = 0;
		// Replace all occurrences of c with str and adjust count.

//	virtual void substituteChar(char o, char n) = 0;
		// Replace all occurrences of o with n.


// Normal Numeric Appending.
	virtual void appendChar(char c) = 0;
		// _TAG13 Normal Numeric Appending

	virtual void appendShort(short i) = 0;
        // _TAG13 Normal Numeric Appending

	virtual void appendUnsignedShort( unsigned short i) = 0;
        // _TAG13 Normal Numeric Appending

	virtual void appendInt(int i) = 0;
        // _TAG13 Normal Numeric Appending

	virtual void appendUnsignedInt( unsigned int i) = 0;
        // _TAG13 Normal Numeric Appending

	virtual void appendLong( long i ) = 0;
        // _TAG13 Normal Numeric Appending

	virtual void appendUnsignedLong( unsigned long i ) = 0;
        // _TAG13 Normal Numeric Appending

// Network Numeric Appending.
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.

	virtual void appendByte( s_8 i ) = 0;
		// _TAG14 Network Numeric Appending

	virtual void appendUnsignedByte( u_8 i ) = 0;
        // _TAG14 Network Numeric Appending

	virtual void appendSigned16( s_16 i ) = 0;
        // _TAG14 Network Numeric Appending

	virtual void appendUnsigned16( u_16 i ) = 0;
        // _TAG14 Network Numeric Appending

	virtual void appendSigned32( s_32 i ) = 0;
        // _TAG14 Network Numeric Appending

	virtual void appendUnsigned32( u_32 i ) = 0;
        // _TAG14 Network Numeric Appending

// Normal Appending

	virtual void appendFloat(float f) = 0;
		// _TAG15 Normal Appending

	virtual void appendDouble( double d ) = 0;
        // _TAG15 Normal Appending

	virtual void appendBool(RTRBOOL b) = 0;
        // _TAG15 Normal Appending

	virtual void appendString(RTRString&) = 0;
        // _TAG15 Normal Appending

	virtual void appendBuffer(RTRIPCBuffer&) = 0;
        // _TAG15 Normal Appending

	virtual void appendCBuffer( char *buffer, int len ) = 0;
        // _TAG15 Normal Appending

// Normal Numeric Insertion
	virtual void putChar(char c, int position) = 0;
		// _TAG16 Normal Numeric Insertion

	virtual void putShort(short i, int position) = 0;
        // _TAG16 Normal Numeric Insertion

	virtual void putUnsignedShort( unsigned short i, int position) = 0;
        // _TAG16 Normal Numeric Insertion

	virtual void putInt(int i, int position) = 0;
        // _TAG16 Normal Numeric Insertion

	virtual void putUnsignedInt( unsigned int i, int position) = 0;
        // _TAG16 Normal Numeric Insertion

	virtual void putLong( long i, int position ) = 0;
        // _TAG16 Normal Numeric Insertion

	virtual void putUnsignedLong( unsigned long i, int position ) = 0;
        // _TAG16 Normal Numeric Insertion

// Network Numeric Insertion
// These member functions should be used when a specific size
// is needed. Such as when sending messages over a network.

	virtual void putByte( s_8 i, int position ) = 0;
		// _TAG17 Network Numeric Insertion

	virtual void putUnsignedByte( u_8 i, int position ) = 0;
        // _TAG17 Network Numeric Insertion

	virtual void putSigned16( s_16 i, int position ) = 0;
        // _TAG17 Network Numeric Insertion

	virtual void putUnsigned16( u_16 i, int position ) = 0;
        // _TAG17 Network Numeric Insertion

	virtual void putSigned32( s_32 i, int position ) = 0;
        // _TAG17 Network Numeric Insertion

	virtual void putUnsigned32( u_32 i, int position ) = 0;
        // _TAG17 Network Numeric Insertion

// Normal Insertion

	virtual void putFloat(float f, int position) = 0;
		// _TAG18 Normal Insertion

	virtual void putDouble(double f, int position) = 0;
        // _TAG18 Normal Insertion

	virtual void putBool(RTRBOOL b, int position) = 0;
        // _TAG18 Normal Insertion

	virtual void putString(RTRString&, int position) = 0;
        // _TAG18 Normal Insertion

	virtual void putString(RTRString& str, int n1, int n2, int position) = 0;
		// REQUIRE : n1 >= 1; n1 <= n2; n2 <= str.count()
        // _TAG18 Normal Insertion

	virtual void putCString(const char *s, int n1, int n2, int p) = 0;
		// REQUIRE : n1 >= 1; n1 <= n2
        // _TAG18 Normal Insertion

};


#endif /* RTR_IPC_BUFFER */


