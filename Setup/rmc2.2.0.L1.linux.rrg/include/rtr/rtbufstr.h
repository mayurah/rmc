//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|
//|       1400 Kensington Road, Oak Brook IL  60521       
//|
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: Tom Hansen
// Created: 11/24/93
// Version: 1.0
//

#ifndef RTR_BUFFER_STRING 
#define RTR_BUFFER_STRING



#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif
#include <stdlib.h>
#include "rtr/rtrdefs.h"
#include "rtr/rtstring.h"

// Synopsis:
//
// Description:
//
// 	Definition of a buffer string "buffer_string" class
//
// 	This class allows the client to set the count, thus allowing
// 	for easy use as a buffer.
// 
// See Also:
//

class RTRBufferString
{

#ifndef _RDEV_NO_STL_
friend std::ostream& operator<<(std::ostream& o, RTRBufferString& s);
#else
public:
void print(FILE*);
#endif
private:


protected:
	char 	*area;			// Internal memory for buffer
	int		int_count;  	// Internal memory count
	int     int_capacity; 	// Internal memory capacity
	
public:

// Constructors

	RTRBufferString();	
		// _TAG Constructor

	RTRBufferString(int n);	
		// Create buffer that has space for at least n characters.
		// _TAG Constructor

	RTRBufferString(const char* n);
		// Create buffer containing value of the given null-terminated
		// string n.
		// _TAG Constructor

	RTRBufferString(const RTRBufferString& s);
		// Copy a RTRBufferString
		// _TAG Constructor

// Destructor

	virtual ~RTRBufferString();
		// _TAG Destructor

// Assignment

	const RTRBufferString& operator=(const RTRBufferString& s);
		// _TAG01 Assignment

// Conversion

	operator const char*(); 
		// Can use buff as char*
		// _TAG02 Conversion

// Equality

	RTRBOOL	operator==(const RTRBufferString& str) const;
		// _TAG03 Equality

	RTRBOOL	operator==(const char* str) const;
        // _TAG03 Equality

	RTRBOOL	operator!=(const RTRBufferString& str) const;
        // _TAG03 Equality

	RTRBOOL	operator!=(const char* str) const;
        // _TAG03 Equality

	inline char& operator[](int n);
        // _TAG03 Equality

// Sizing

	inline int 	count();		
		// Number of characters set in buffer.
		// _TAG04 Sizing

	inline int 	length();		
		// Synonym for count.
        // _TAG04 Sizing

	inline void 	setCount(int n);
		// Set count to n
        // _TAG04 Sizing

	int 	capacity(); 	
		// Amount of memory allocated.
        // _TAG04 Sizing

// Set Features

	void	append(char c);			
		// Append character c to this, resizing if necessary.
		// _TAG05 Set Features

	void	append(const char* cstr);	
		// Append null-terminated string cstr.
		// _TAG05 Set Features

	inline void	put(char c, int p);  	
		// Replace character at position p in this with c
        // _TAG05 Set Features

	void	set(const char *t, int n1, int n2);
		// Set buffer to substring of t from indices n1 to n2.
        // _TAG05 Set Features

	void	set(const char *t);	
		// Set to null terminated string t
        // _TAG05 Set Features

// Access

	char	item(int p);	
		// Character value at position p
		// _TAG06 Access

	inline const char *to_c();			
		// Char * value of buffer (based on count()).
		// _TAG06 Access

// Resize
	void	grow(int newsize);	
		// Ensure capacity() is at least newsize
		// _TAG07 Resize

//Transformation
	RTRString subString(int p1, int p2);
		// positions indexed from 0;
		// _TAG08 Transformation

	inline int toInteger();
		// The integer representation of this string.
		// _TAG08 Transformation

};

// Access

inline char RTRBufferString::item(int p)
	// Character value at position `p'. Note indices start at zero.
{
	RTPRECONDITION( 1 <= p );
	RTPRECONDITION( p <= count() );

	return area[p-1];
};

inline const char *RTRBufferString::to_c()
{
	return (const char*)*this;
};


// Sizing

inline int RTRBufferString::count()
	// Number of characters set in buffer.
{
	return int_count;
};

inline int RTRBufferString::length()
	// Synonum for count
{
	return int_count;
};


inline void RTRBufferString::setCount(int n)
	// Set count to `n'
{
	RTPRECONDITION( 0 <= n );
	RTPRECONDITION( n <= capacity() );

	int_count = n;
};

inline int	RTRBufferString::capacity()
	// Amount of memory allocated.
{
	return int_capacity;
};

inline int RTRBufferString::toInteger()
{
	if (int_count == int_capacity)
		grow(int_capacity + 1);
	area[int_count] = '\0';
	int_count++;
	return atoi(area);
};

inline void RTRBufferString::put(char c, int p)
	// Replace character at position `p' in  this with `c'
{
	RTPRECONDITION( (1 <= p) );
	RTPRECONDITION( (p <= count()) ); 
	area[p-1] = c;
};

inline char& RTRBufferString::operator[](int n)
{
	RTPRECONDITION( 1 <= n );
	RTPRECONDITION( n <= count() );

	return area[n - 1];
};


#endif /* RTR_BUFFER_STRING */


