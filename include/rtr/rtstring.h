//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Nov. 30 1994"
// Version: 1.0

#ifndef _rtstring_h
#define _rtstring_h

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

#include "rtr/rtrdefs.h"
#include "rtr/os.h"

#undef index	// may be #defined as strchr

// Synopsis:
// #include"rtr/rtstring.h"
//
// Description:
//	A representation for a sequence of characters. The sequence may contain
//	embedded null characters.
//
// See Also:
//	RTRExternalValue, RTRListOfExternalValue
//

class RTRString
{

#ifndef _RDEV_NO_STL_
friend std::ostream& operator<<(std::ostream&, const RTRString&); 
#else
public:
void print(FILE*);
#endif
public:
// Constructors
	RTRString();
		// An empty string.
		// _TAG Constructor

	RTRString(unsigned int n);
		// A string with capacity n.
        // _TAG Constructor

	RTRString(char c, unsigned int n);
		// A string with capacity n, initialized with character c.
        // _TAG Constructor

	RTRString(const char *str);
		// A string with a copy of the null terminated string str.
        // _TAG Constructor

	RTRString(const char *str, unsigned int n);
		// A string with a copy of the n bytes from null terminated string str.
        // _TAG Constructor

	RTRString(const RTRString&);
		// A string with a copy of the n bytes from null terminated string str.
        // _TAG Constructor

// Destructor
	~RTRString();
		// _TAG Destructor

// Static attributes
	static int defaultCapacity;
		// The size of area allocated when using the default constructor.
	
	static char *trueString;
		// The value to which strings are compared when converting to a boolean.

// Attributes
	inline const unsigned int capacity() const;
		// The current capacity of this string.
		// _TAG01 Attributes

	inline unsigned int count() const;
		// The number of characters in this string.
        // _TAG01 Attributes

	inline RTRBOOL isEmpty() const;
		// Is this string empty. (result == RTRTRUE imples count() == 0)
        // _TAG01 Attributes

	unsigned long hash() const;
		// A hash value for this string.
        // _TAG01 Attributes

	inline int lower() const;
		// Minimum valid index for accessing this string.
        // _TAG01 Attributes

	inline int upper() const;
		// Maximmum valid index for accessing this string.
        // _TAG01 Attributes

// Modify - in entirety
	RTRString& set(const char *str, unsigned int p1, unsigned int p2);
		// Initialize this string to the contents of str, starting a position
		// p1 (0 based) and ending at position p2
		// REQUIRE : p1 <= p2
		// _TAG02 Modify - in entirety

	RTRString& set(const char *str, unsigned int n);
		// Initialize this string to the first n bytes of str.
        // _TAG02 Modify - in entirety

#ifndef _RDEV_NO_STL_
	RTRString& readLine(std::istream&, RTRBOOL skipWhite=1);
		// Set this string to a line extracted from the given stream.
        // _TAG02 Modify - in entirety
#endif

	inline RTRString& clear();
		// Empty this string.
		// ENSURE : isEmpty()
        // _TAG02 Modify - in entirety

	RTRString& fromNumeric(int i);
        // _TAG02 Modify - in entirety

	RTRString& fromNumeric(unsigned int i);
        // _TAG02 Modify - in entirety

	RTRString& fromNumeric(long i);
        // _TAG02 Modify - in entirety

	RTRString& fromNumeric(RTR_I64 i);
   		// _TAG02 Modify - in entirety

	RTRString& fromNumeric(unsigned long i);
        // _TAG02 Modify - in entirety

	RTRString& fromNumeric(double i);
		// Set this string to the ASCII representation of i.
        // _TAG02 Modify - in entirety

// Modify - in part
	char& operator[](int i);
		// Set the i'th character in this string.
		// REQUIRE: i >= lower()
		// REQUIRE: i <= upper()
		// _TAG03 Modify - in part

	RTRString& prepend(const char *);
        // _TAG03 Modify - in part

	RTRString& prepend(char);
        // _TAG03 Modify - in part

	RTRString& prepend(long);
        // _TAG03 Modify - in part

	RTRString& prepend(unsigned long);
        // _TAG03 Modify - in part

	RTRString& prepend(double);
		// Prepend the given value to this string.
        // _TAG03 Modify - in part

	RTRString& append(const char *);
        // _TAG03 Modify - in part

	RTRString& append(const char *, int);
        // _TAG03 Modify - in part

	RTRString& append(const RTRString&);
        // _TAG03 Modify - in part

	RTRString& append(const char);
        // _TAG03 Modify - in part

	RTRString& append(const unsigned char);
        // _TAG03 Modify - in part

	RTRString& append(const short);
        // _TAG03 Modify - in part

	RTRString& append(const unsigned short);
        // _TAG03 Modify - in part

	RTRString& append(const int);
        // _TAG03 Modify - in part

	RTRString& append(const unsigned int);
        // _TAG03 Modify - in part

	RTRString& append(const long);
        // _TAG03 Modify - in part

	RTRString& append(const unsigned long);
        // _TAG03 Modify - in part

	RTRString& append(const RTR_I64);
		// _TAG03 Modify - in part 

	RTRString& append(const unsigned RTR_I64);
		// _TAG03 Modify - in part 

	RTRString& append(const float);
        // _TAG03 Modify - in part

	RTRString& append(const double);
		// Append the given value to this string.
        // _TAG03 Modify - in part

	RTRString& appendHex(const char);
        // _TAG03 Modify - in part

	RTRString& appendHex(const unsigned char);
        // _TAG03 Modify - in part

	RTRString& appendHex(const short);
        // _TAG03 Modify - in part

	RTRString& appendHex(const unsigned short);
        // _TAG03 Modify - in part

	RTRString& appendHex(const int);
        // _TAG03 Modify - in part

	RTRString& appendHex(const unsigned int);
        // _TAG03 Modify - in part

	RTRString& appendHex(const long);
		// _TAG03 Modify - in part 

	RTRString& appendHex(const unsigned long);
		// _TAG03 Modify - in part 

	RTRString& appendHex(const RTR_I64);
		// _TAG03 Modify - in part 

	RTRString& appendHex(const unsigned RTR_I64);
		// _TAG03 Modify - in part 
	
	RTRString& toLower();
		// Put this string in lower case.
        // _TAG03 Modify - in part

	RTRString& toUpper();
		// Put this string in upper case.
        // _TAG03 Modify - in part

// Truncate
	void leftAdjust();	
		// Remove leading white-space from this string.
		// _TAG04 Truncate

	void rightAdjust();	
		// Remove trailing white-space from this string.
        // _TAG04 Truncate

	RTRString& head(unsigned int n); 	
		// Trim this string to the first n characters.
		// ENSURE : count() = n \\
		//          head(0) implies isEmpty()
        // _TAG04 Truncate

	RTRString& tail(unsigned int n); 	
		// Trim the first count() - n characters from this string.
		// ENSURE : count() = n \\
		//          tail(0) implies isEmpty()
        // _TAG04 Truncate

// Comparison
 	int compare(const char *) const;
		// Is this string greater than (result == 1), equal to (result == 0), 
		// or less than (result == 1) the given string?
		// _TAG05 Comparison

// Access
	char operator[](int i) const;
		// The i'th character in this string.
		// REQUIRE : i >= lower()
		// REQUIRE : i <= upper()
		// _TAG06 Access

	operator const char *() const;
		// A pointer to the storage for this string. 
		// Result is null terminated ( i.e. result[count()] == '\0'). 
		// Note: Nulls may be imbedded in data.
        // _TAG06 Access

	RTRString subString(int p1, int p2);
		// A new string which characters from positions p1 through p2
		// REQUIRE: p1 >= lower()
		// REQUIRE: p2 <= upper()
		// REQUIRE: p1 <= p2
        // _TAG06 Access

	inline const char *to_c() const;
		// A pointer to the internal storage.
		// Note: unlike use of the cast operator (const char *) storage 
		// is not null terminated by this call.
        // _TAG06 Access

// Query
	RTRBOOL contains(const char *) const;
		// Does this string contain a sub-string equal to the given string?
		// _TAG07 Query

	RTRBOOL contains(const char) const;
		// Does this string contain the given character?
        // _TAG07 Query

	int	indexOf(char c, int p1);
		// The index of the first instance c found in this string after 
		// position p1
		// REQUIRE: p1 >= lower()
		// REQUIRE: p1 <= upper()
		// ENSURE : result >= lower() implies operator[](result) == c
        // _TAG07 Query

// Transform
	int toInteger() const;
		// This string as an integer.
		// _TAG08 Transform

	float toFloat() const;
		// This string as a float.
		// _TAG08 Transform

	double toDouble() const;
		// This string as a double.
        // _TAG08 Transform

	RTRBOOL toBoolean() const;
		// This string as a boolean.
        // _TAG08 Transform

// Operators
	RTRString& operator=(const char *);
		// _TAG09 Operators

	RTRString& operator=(const RTRString&);
		// Assign this string to other string.
        // _TAG09 Operators

	RTRBOOL operator==(const char *) const;
        // _TAG09 Operators

	RTRBOOL operator==(const RTRString&) const;
        // _TAG09 Operators

	RTRBOOL operator!=(const char *) const;
        // _TAG09 Operators

	RTRBOOL operator!=(const RTRString&) const;
        // _TAG09 Operators

	RTRBOOL operator>(const char *) const;
        // _TAG09 Operators

	RTRBOOL operator>(const RTRString&) const;
        // _TAG09 Operators

	RTRBOOL operator>=(const char *) const;
        // _TAG09 Operators

	RTRBOOL operator>=(const RTRString&) const;
        // _TAG09 Operators

	RTRBOOL operator<(const char *) const;
        // _TAG09 Operators

	RTRBOOL operator<(const RTRString&) const;
        // _TAG09 Operators

	RTRBOOL operator<=(const char *) const;
        // _TAG09 Operators

	RTRBOOL operator<=(const RTRString&) const;
		// Compare this string with other
        // _TAG09 Operators

	RTRString& operator+=(const char *);
        // _TAG09 Operators

	RTRString& operator+=(const RTRString&);
        // _TAG09 Operators

	RTRString& operator+=(const char);
		// Append other string or character to this string.
        // _TAG09 Operators

// Operations
	void grow(unsigned int n);
		// Increase the capacity of this string to accomodate n bytes.
		// ENSURE : capacity() >= n
		// _TAG10 Operations

	void trim(unsigned int);
		// Decrease the capacity of this string to accomodate n bytes.
		// ENSURE : capacity() <= n
		//          count() <= n
        // _TAG10 Operations

	void setCount(unsigned int i);
		// Set count to i.
		// [Useful when using the string storage (via to_c()) as a buffer]
		// REQUIRE : i <= capacity()
        // _TAG10 Operations

// Compatiblity - OBSOLETE

	RTRString(const char *str, int n);
		// A string with a copy of the n bytes from null terminated string str.
		// Compatibility of using "int" rather than "unsigned int" \\
		// Compatitbility - OBSOLETE
		// _TAG Constructor

 	RTRBOOL isEqual(const char *) const;
		// Use compare()
        // _TAG11 Compatibility - OBSOLETE

	RTRString& empty();
		// Use clear()
        // _TAG11 Compatibility - OBSOLETE

	inline int length() const;
		// Use count()
        // _TAG11 Compatibility - OBSOLETE

	int	index(char c, int start);
		// Use indexOf
        // _TAG11 Compatibility - OBSOLETE

	RTRString& set(RTRString&, unsigned int p1, unsigned int p2);
        // _TAG11 Compatibility - OBSOLETE

	RTRString& fromInteger(int i);
		// Use fromNumeric
        // _TAG11 Compatibility - OBSOLETE

	void appendNumeric(const char);
        // _TAG11 Compatibility - OBSOLETE

	void appendNumeric(const unsigned char);
        // _TAG11 Compatibility - OBSOLETE

	void appendNumeric(const short);
        // _TAG11 Compatibility - OBSOLETE

	void appendNumeric(const unsigned short);
        // _TAG11 Compatibility - OBSOLETE

	void appendNumeric(const int);
        // _TAG11 Compatibility - OBSOLETE

	void appendNumeric(const unsigned int);
        // _TAG11 Compatibility - OBSOLETE

	void appendNumeric(const long);
        // _TAG11 Compatibility - OBSOLETE

	void appendNumeric(const RTR_I64);
    	// _TAG11 Compatibility - OBSOLETE
	
	void appendNumeric(const unsigned long);
        // _TAG11 Compatibility - OBSOLETE

	void appendNumeric(const float);
        // _TAG11 Compatibility - OBSOLETE

	void appendNumeric(const double);
		// Use append
        // _TAG11 Compatibility - OBSOLETE

protected:
// Methods
	void allocate(unsigned int);
		// Allocate new storage

	void reallocate(unsigned int);
		// Allocate new storage, copying current.

// Data
	char *_area;		// Don't change the order of these!
	unsigned int _capacity;
	unsigned int _count; 
};

inline void RTRString::appendNumeric(const char i) { append(i); };
inline void RTRString::appendNumeric(const unsigned char i) { append(i); };
inline void RTRString::appendNumeric(const short s) { append(s); };
inline void RTRString::appendNumeric(const unsigned short s) { append(s); };
inline void RTRString::appendNumeric(const int i) { append(i); };
inline void RTRString::appendNumeric(const unsigned int i) { append(i); };
inline void RTRString::appendNumeric(const long l) { append(l); };
inline void RTRString::appendNumeric(const RTR_I64 i) { append(i); };
inline void RTRString::appendNumeric(const unsigned long l) { append(l); };
inline void RTRString::appendNumeric(const float f) { append(f); };
inline void RTRString::appendNumeric(const double d) { append(d); };

inline RTRString& RTRString::clear()
{
	_count = 0;
	_area[_count] = '\0';

	RTPOSTCONDITION ( isEmpty() );
	return *this;
}

inline const char *RTRString::to_c() const
{
		// Don't null terminate here for backwards compatibility
		// Clients may have been using this as a "buffer" and storing
		// data without setting _count.
	return _area;
}


inline RTRString& RTRString::empty()
{
	clear();
	return *this;
}

inline int RTRString::length() const
{
	return count();
}

inline const unsigned int RTRString::capacity()const
{
	return _capacity;
}

inline unsigned int RTRString::count() const
{
	return _count;
}

inline RTRBOOL RTRString::isEmpty() const
{
	return count() == 0;
}


inline int RTRString::lower() const
{
	return 1;
}

inline int RTRString::upper() const
{
	return _count;
}


#endif // _rtstring_h
