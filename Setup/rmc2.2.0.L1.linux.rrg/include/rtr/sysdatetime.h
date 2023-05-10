//|---------------------------------------------------------------------------
//|                       Copyright (c) 1998 Reuters                        --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.06.22"
// Version: 1.0

#ifndef _rtr_sysdatetime_h
#define _rtr_sysdatetime_h

#include <time.h>
#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif
#include "rtr/rtrdefs.h"

typedef struct tm TMStruct;

class RTRTimeInterval;
class RTRString;

// Synopsis:
// #include "rtr/sysdatetime.h"
//
// Description:
// This class provides an implementation of a date/time object based
// upon system calls.
//
// Methods are provided to set and get both GMT and local times.  Where
// appropriate, a boolean flag must be passed into set methods and 
// constructors to specify if the value being passed in should be 
// interpreted as a GMT or local time.  Similary, a boolean flag must be
// passed into appropriate get methods to specify that the return value
// should be expressed in GMT or local time.
//
// Note that all assignment operators interpret the right-hand-side of
// the operator as a GMT date/time.
//
// An error state is provided to indicate that a valid date could
// not be constructed.  The "error date" has been defined as 
// December 31, 1969, 23:59:59 in GMT time and the error() state must be
// in effect so that it is unambiguous.  All instances of
// RTRSystemDateTime should be checked to determine if they are in an
// error state before they are used.
//
// Due to cross-platform compatibility, this class cannot create dates
// prior to January 01, 1970, 00:00:00.
//
// See Also:
// RTRTimeInterval
//

class RTRSystemDateTime
{
public:
// Constructor
	RTRSystemDateTime();
		// The current date/time;
		// _TAG Constructor

	RTRSystemDateTime(long secsFromEpoch, RTRBOOL isGmtTime=RTRTRUE);
		// A new date/time based on the given number of seconds from the epoch
		// represented in GMT or local time.
		// _TAG Constructor

	RTRSystemDateTime(TMStruct tm, RTRBOOL isGmtTime=RTRTRUE);
		// A new date/time based on the given tm structure represented in
		// GMT or local time.
		// _TAG Constructor

	RTRSystemDateTime(const RTRSystemDateTime& other);
		// A copy of the given date/time.
		// _TAG Constructor

	RTRSystemDateTime(const char *string, RTRBOOL isGmtTime=RTRTRUE);
		// A new date/time based on the given string representation represented
		// in GMT or local time. \\
		// The following forms are supported based upon the mktime() function
		// conventions: \\
		// \\
		//   a) DD mmm YYYY - e.g. 14 APR 1974 . \\
		//   b) MM/DD/YY - e.g. 04/14/74 (April 14, 1974) . \\
		//      MM/DD/YYY - e.g. 04/14/101 (April 14, 2001) . \\
		//      MM/DD/YYYY - e.g. 04/14/1974 . \\
		//   c) YYYY.MM.DD - e.g. 1974.04.14 . \\
		//   d) YYYY-MM-DD - e.g. 1974-04-14 . \\
		//   e) YYYY/MM/DD - e.g. 1974/04/14 . \\
		//   f) HH:MM - e.g. 23:15 (11:15 p.m. today) . \\
		//      HH:MM:SS - e.g. 23:15:59 (11:15 and 59 seconds p.m. today) .
		// _TAG Constructor

	RTRSystemDateTime(
			const char *dateString,
			const char *timeString,
			RTRBOOL isGmtTime=RTRTRUE
			);
		// A new date/time based on the given date and time strings.  See
		// the above constructor for the supported date and time string
		// formats.
		// _TAG Constructor

// Destructor
	virtual ~RTRSystemDateTime();
		// _TAG Destructor

// Attributes
	float gmtOffset() const;
		// The current offset in hours between local and GMT time.
		// REQUIRE: !error()
		// _TAG01 Attributes

	long epochSeconds(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The number of seconds since the epoch represented as GMT or
		// local time.
		// REQUIRE: !error()
		// _TAG01 Attributes

	int seconds() const;
		// The seconds into the current minute (0-59).
		// REQUIRE: !error()
		// _TAG01 Attributes

	int minutes(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The minutes into the current hour (0-59).
		// REQUIRE: !error()
		// _TAG01 Attributes

	int hours(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The current hour of the day representated as GMT or local time
		// (0-23).
		// REQUIRE: !error()
		// _TAG01 Attributes

	int dayOfMonth(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The current day of the month represented as GMT or local time
		// (1-31).
		// REQUIRE: !error()
		// _TAG01 Attributes

	int monthNumber(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The current month in the year (1-12).
		// REQUIRE: !error()
		// _TAG01 Attributes

	RTRString monthAbbr(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The abbreviated month name.
		// REQUIRE: !error()
		// _TAG01 Attributes

	RTRString monthName(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The month name.
		// REQUIRE: !error()
		// _TAG01 Attributes

	int year(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The current year (e.g. 1999).
		// REQUIRE: !error()
		// _TAG01 Attributes

	int dayOfWeekNumber(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The numeric day of the week (Sunday = 0).
		// REQUIRE: !error()
		// _TAG01 Attributes

	RTRString dayAbbr(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The abbreviated day of the week name.
		// REQUIRE: !error()
		// _TAG01 Attributes

	RTRString dayOfWeek(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The day of the week name.
		// REQUIRE: !error()
		// _TAG01 Attributes

	int dayOfYear(RTRBOOL returnAsGmt=RTRTRUE) const;
		// The current day of the year (0-365).
		// REQUIRE: !error()
		// _TAG01 Attributes

	RTRBOOL inDST() const;
		// Is the local date in daylight savings time?
		// REQUIRE: !error()
		// _TAG01 Attributes

// State
	inline RTRBOOL error() const;
		// Could a valid date be formed?
		// _TAG02 State

// Transformation
	RTRString string(const char *format, RTRBOOL returnAsGmt=RTRTRUE) const;
		// A new string constructed using the given format (uses
		// strftime() conventions) represented as a GMT or local time.
		// REQUIRE: !error()
		// _TAG03 Transformation

	TMStruct tm(RTRBOOL returnAsGmt=RTRTRUE) const;
		// A tm structure representation of this date.
		// REQUIRE: !error()
		// _TAG03 Transformation

// Operations
	void setToSystemTime();
		// Sets the date to the system time.
		// _TAG04 Operations

	void setEpochSeconds(long secsFromEpoch, RTRBOOL isGmtTime=RTRTRUE);
		// Sets the date from the given number of seconds since the epoch
		// represented as GMT or local time.
		// _TAG04 Operations

	void setTMStruct(TMStruct tm, RTRBOOL isGmtTime=RTRTRUE);
		// Sets the date from the given TMStruct.
		// _TAG04 Operations

	void fromDateString(const char *dateString, RTRBOOL isGmtTime=RTRTRUE);
		// Sets the date from the given string represented in GMT or
		// local time. \\
		// The following forms are supported based upon the mktime() function
		// conventions: \\
		// \\
		//   a) DD mmm YYYY - e.g. 14 APR 1974 . \\
		//   b) MM/DD/YY - e.g. 04/14/74 (April 14, 1974) . \\
		//      MM/DD/YYY - e.g. 04/14/101 (April 14, 2001) . \\
		//      MM/DD/YYYY - e.g. 04/14/1974 . \\
		//   c) YYYY.MM.DD - e.g. 1974.04.14 . \\
		//   d) YYYY-MM-DD - e.g. 1974-04-14 . \\
		//   e) YYYY/MM/DD - e.g. 1974/04/14 . \\
		// _TAG04 Operations

	void fromTimeString(const char *timeString, RTRBOOL isGmtTime=RTRTRUE);
		// Sets the date from the given string represented in GMT or
		// local time. \\
		// The following form is supported: \\
		// \\
		//   a) HH:MM - e.g. 23:15 (11:15 p.m. today) . \\
		//      HH:MM:SS - e.g. 23:15:59 (11:15 and 59 seconds p.m. today) .
		// _TAG04 Operations

	void fromDateTimeString(
			const char *dateString,
			const char *timeString,
			RTRBOOL isGmtTime=RTRTRUE
			);
		// Sets the date from the given date and time strings represented in
		// GMT or local time. \\
		// \\
		// See fromDateString() and fromTimeString() for supported formats.
		// _TAG04 Operations

// Operators
	RTRBOOL operator>(const RTRSystemDateTime& rhs) const;
		// _TAG05 Operators

	RTRBOOL operator>=(const RTRSystemDateTime& rhs) const;
		// _TAG05 Operators

	RTRBOOL operator==(const RTRSystemDateTime& rhs) const;
		// _TAG05 Operators

	RTRBOOL operator!=(const RTRSystemDateTime& rhs) const;
		// _TAG05 Operators

	RTRBOOL operator<(const RTRSystemDateTime& rhs) const;
		// _TAG05 Operators

	RTRBOOL operator<=(const RTRSystemDateTime& rhs) const;
		// _TAG05 Operators

	RTRSystemDateTime& operator=(const RTRSystemDateTime& rhs);
		// _TAG05 Operators

	RTRSystemDateTime& operator=(unsigned long rhs);
		// _TAG05 Operators

	RTRSystemDateTime& operator=(TMStruct rhs);
		// _TAG05 Operators

	RTRSystemDateTime operator+(unsigned long rhs);
		// _TAG05 Operators

	RTRSystemDateTime operator+(const RTRTimeInterval& rhs);
		// _TAG05 Operators

	RTRSystemDateTime& operator+=(unsigned long rhs);
		// _TAG05 Operators

	RTRSystemDateTime& operator+=(const RTRTimeInterval& rhs);
		// _TAG05 Operators

	RTRTimeInterval operator-(const RTRSystemDateTime& rhs);
		// _TAG05 Operators

	RTRSystemDateTime operator-(const RTRTimeInterval& rhs);
		// _TAG05 Operators

	RTRSystemDateTime& operator-=(unsigned long rhs);
		// _TAG05 Operators

	RTRSystemDateTime& operator-=(const RTRTimeInterval& rhs);
		// _TAG05 Operators

protected:
// Utilities
	RTRString getDateStringElement(const char *, struct tm *) const;

	void initializeDate(int, int, int, RTRBOOL);

	void initializeErrorDate();

#if (sun4 && !SOLARIS2)
	void calculateOffset();
#endif

// Friends
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream&, const RTRSystemDateTime&);
#else
public:
	void print(FILE*);
#endif
// Data
	struct tm _tm;
	RTRBOOL _error;
	static RTRString mdyFmt;
	static RTRString dmyFmt;
	static RTRString ymdDotFmt;
	static RTRString ymdDashFmt;
	static RTRString hmsFmt;
};

inline RTRBOOL RTRSystemDateTime::error() const
{
	return _error;
}

inline RTRBOOL RTRSystemDateTime::operator>(const RTRSystemDateTime& rhs) const
{
	return epochSeconds(RTRTRUE) > rhs.epochSeconds(RTRTRUE);
}

inline RTRBOOL RTRSystemDateTime::operator>=(const RTRSystemDateTime& rhs) const
{
	return epochSeconds(RTRTRUE) >= rhs.epochSeconds(RTRTRUE);
}

inline RTRBOOL RTRSystemDateTime::operator==(const RTRSystemDateTime& rhs) const
{
	return epochSeconds(RTRTRUE) == rhs.epochSeconds(RTRTRUE);
}

inline RTRBOOL RTRSystemDateTime::operator!=(const RTRSystemDateTime& rhs) const
{
	return epochSeconds(RTRTRUE) != rhs.epochSeconds(RTRTRUE);
}

inline RTRBOOL RTRSystemDateTime::operator<(const RTRSystemDateTime& rhs) const
{
	return epochSeconds(RTRTRUE) < rhs.epochSeconds(RTRTRUE);
}

inline RTRBOOL RTRSystemDateTime::operator<=(const RTRSystemDateTime& rhs) const
{
	return epochSeconds(RTRTRUE) <= rhs.epochSeconds(RTRTRUE);
}

#endif /* _rtr_sysdatetime_h */
