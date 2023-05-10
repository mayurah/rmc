//|---------------------------------------------------------------------------
//|                       Copyright (c) 1998 Reuters                        --
//|                1400 Kensington Road, Oak Brook, IL 60523                --
//|      All rights reserved.  Duplication or distribution prohibited.      --
//|---------------------------------------------------------------------------
//
// Author: R. Lagman
// Created: "1999.06.22"
// Version: 1.1

#ifndef _rtr_datetime_h
#define _rtr_datetime_h

#include <time.h>
#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif

#include "rtr/rtrdefs.h"
#include "rtr/tmintvl.h"
#include "rtr/rtstring.h"
#include "rtr/rtbuffer.h"
#include "rtr/gettimeofday.h"

typedef struct tm TMStruct;
	// TMStruct

//
// Synopsis:
// #include "rtr/datetime.h"
//
// Description:
// This class provides an implementation of a date/time object.
//
// Methods are provided to set and get both local and GMT times.  Where
// appropriate, a boolean flag must be passed into set methods and 
// constructors to specify if the value being passed in should be 
// interpreted as a local or GMT time.  Similary, a boolean flag must be
// passed into appropriate get methods to specify that the return value
// should be expressed in local or GMT time.
//
// Note that all assignment operators interpret the right-hand-side of
// the operator as a local date/time.
//
// An error state is provided to indicate that a valid date could
// not be constructed.  The "error date" has been defined as 
// December 31, 1969, 23:59:59 in GMT time and the error() state must be
// in effect so that it is unambiguous.  All instances of
// RTRDateTime should be checked to determine if they are in an
// error state before they are used.
//
// Due to cross-platform compatibility, this class cannot create dates
// prior to January 01, 1970, 00:00:00.
//
// See Also:
// RTRTimeInterval
//
// Inherits:
// N/A
//

class RTRDateTime
{

#ifndef _RDEV_NO_STL_
friend std::ostream& operator<<(std::ostream&, const RTRDateTime&);
#else
public:
void print(FILE*);
#endif

public:
// Constructor
	RTRDateTime();
		// The current date/time.
		// _TAG Constructor

	RTRDateTime(long secsFromEpoch, RTRBOOL isGmtTime=RTRFALSE);
		// A new date/time based on the given number of seconds from the epoch
		// represented in local or GMT time.
		// _TAG Constructor

	RTRDateTime(TMStruct tm, RTRBOOL isGmtTime=RTRFALSE);
		// A new date/time based on the given tm structure represented in
		// local or GMT time.
		// _TAG Constructor

	RTRDateTime(const RTRDateTime& other);
		// A copy of the given date/time.
		// _TAG Constructor

	RTRDateTime(const char *string, RTRBOOL isGmtTime=RTRFALSE);
		// A new date/time based on the given string representation represented
		// in local or GMT time. \\
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

	RTRDateTime(
			const char *dateString,
			const char *timeString,
			RTRBOOL isGmtTime=RTRFALSE
			);
		// A new date/time based on the given date and time strings.  See
		// the above constructor for the supported date and time string
		// formats.
		// _TAG Constructor

// Destructor
	virtual ~RTRDateTime();
		// _TAG Destructor

// Attributes
	virtual float gmtOffset() const;
		// The current offset in hours between local and GMT time.
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual long epochSeconds(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The number of seconds since the epoch represented as local or
		// GMT time.
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual int seconds() const;
		// The seconds into the current minute (0-59).
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual int minutes(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The minutes into the current hour (0-59).
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual int hours(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The current hour of the day representated as local or GMT time
		// (0-23).
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual int dayOfMonth(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The current day of the month represented as local or GMT time
		// (1-31).
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual int monthNumber(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The current month in the year (1-12).
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual RTRString monthAbbr(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The abbreviated month name.
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual RTRString monthName(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The month name.
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual int year(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The current year (e.g. 1999).
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual int dayOfWeekNumber(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The numeric day of the week (Sunday = 0).
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual RTRString dayAbbr(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The abbreviated day of the week name.
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual RTRString dayOfWeek(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The day of the week name.
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual int dayOfYear(RTRBOOL returnAsGmt=RTRFALSE) const;
		// The current day of the year (0-365).
		// REQUIRE: !error()
		// _TAG01 Attributes

	virtual RTRBOOL inDST() const;
		// Is the local date in daylight savings time?
		// REQUIRE: !error()
		// _TAG01 Attributes

// State
	inline RTRBOOL error() const;
		// Could a valid date be formed?
		// _TAG02 State

// Transformation
	virtual RTRString string(
			const char *format,
			RTRBOOL returnAsGmt=RTRFALSE,
			u_8 uSecsOffset=0
			) const;
		// A new string constructed using the given format (uses
		// strftime() conventions) represented as a local or GMT time.
		// REQUIRE: !error()
		// _TAG03 Transformation

	virtual TMStruct tm(RTRBOOL returnAsGmt=RTRFALSE) const;
		// A tm structure representation of this date.
		// REQUIRE: !error()
		// _TAG03 Transformation

// Operations
	virtual void setToSystemTime();
		// Sets the date to the system time.
		// _TAG04 Operations

	void setEpochSeconds(long secsFromEpoch, RTRBOOL isGmtTime=RTRFALSE);
		// Sets the date from the given number of seconds since the epoch
		// represented as local or GMT time.
		// _TAG04 Operations

	void setTMStruct(TMStruct tm, RTRBOOL isGmtTime=RTRFALSE);
		// Sets the date from the given TMStruct represented as local or
		// GMT time.
		// _TAG04 Operations

	void fromDateString(const char *dateString, RTRBOOL isGmtTime=RTRFALSE);
		// Sets the date from the given string represented in local or
		// GMT time. \\
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

	void fromTimeString(const char *timeString, RTRBOOL isGmtTime=RTRFALSE);
		// Sets the date from the given string represented in local or
		// GMT time. \\
		// The following form is supported: \\
		// \\
		//   a) HH:MM - e.g. 23:15 (11:15 p.m. today) . \\
		//      HH:MM:SS - e.g. 23:15:59 (11:15 and 59 seconds p.m. today) .
		// _TAG04 Operations

	void fromDateTimeString(
			const char *dateString,
			const char *timeString,
			RTRBOOL isGmtTime=RTRFALSE
			);
		// Sets the date from the given date and time strings represented in
		// local or GMT time. \\
		// \\
		// See fromDateString() and fromTimeString() for supported formats.
		// _TAG04 Operations

// Operators
	RTRBOOL operator>(const RTRDateTime& rhs) const;
		// _TAG05 Operators

	RTRBOOL operator>=(const RTRDateTime& rhs) const;
		// _TAG05 Operators

	RTRBOOL operator==(const RTRDateTime& rhs) const;
		// _TAG05 Operators

	RTRBOOL operator!=(const RTRDateTime& rhs) const;
		// _TAG05 Operators

	RTRBOOL operator<(const RTRDateTime& rhs) const;
		// _TAG05 Operators

	RTRBOOL operator<=(const RTRDateTime& rhs) const;
		// _TAG05 Operators

	RTRDateTime& operator=(const RTRDateTime& rhs);
		// _TAG05 Operators

	RTRDateTime& operator=(unsigned long rhs);
		// _TAG05 Operators

	RTRDateTime& operator=(TMStruct rhs);
		// _TAG05 Operators

	RTRDateTime operator+(unsigned long rhs);
		// _TAG05 Operators

	RTRDateTime operator+(const RTRTimeInterval& rhs);
		// _TAG05 Operators

	RTRDateTime& operator+=(unsigned long rhs);
		// _TAG05 Operators

	RTRDateTime& operator+=(const RTRTimeInterval& rhs);
		// _TAG05 Operators

	RTRTimeInterval operator-(const RTRDateTime& rhs);
		// _TAG05 Operators

	RTRDateTime operator-(const RTRTimeInterval& rhs);
		// _TAG05 Operators

	RTRDateTime& operator-=(unsigned long rhs);
		// _TAG05 Operators

	RTRDateTime& operator-=(const RTRTimeInterval& rhs);
		// _TAG05 Operators

// OBSOLETE
	virtual long gmtSeconds() const;
		// Use epochSeconds(RTRTRUE) .
		// _TAG06 OBSOLETE

	virtual long gmtEpochSeconds() const;
		// Use epochSeconds(RTRTRUE) .
		// _TAG06 OBSOLETE

	virtual long localEpochSeconds() const;
		// Use epochSeconds(RTRFALSE) .
		// _TAG06 OBSOLETE

	void setGmtTime(long secs);
		// Use setEpochSeconds(secs, RTRTRUE) .
		// _TAG06 OBSOLETE
	
	void setGmtEpochSeconds(long secs);
		// Use setEpochSeconds(secs, RTRTRUE) .
		// _TAG06 OBSOLETE

	void setLocalEpochSeconds(long secs);
		// Use setEpochSeconds(secs, RTRFALSE) .
		// _TAG06 OBSOLETE

	void fromTimesecString(const char *);
		// Use fromTimeString() .
		// _TAG06 OBSOLETE

protected:
// Utilities
	RTRString getDateStringElement(const char *, struct tm *) const;

	void initializeDate(int, int, int, RTRBOOL);

	void initializeErrorDate();

#if (sun4 && !SOLARIS2)
	void calculateOffset();
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

inline RTRBOOL RTRDateTime::error() const
{
	return _error;
}

inline RTRBOOL RTRDateTime::operator>(const RTRDateTime& rhs) const
{
	return epochSeconds(RTRFALSE) > rhs.epochSeconds(RTRFALSE);
}

inline RTRBOOL RTRDateTime::operator>=(const RTRDateTime& rhs) const
{
	return epochSeconds(RTRFALSE) >= rhs.epochSeconds(RTRFALSE);
}

inline RTRBOOL RTRDateTime::operator==(const RTRDateTime& rhs) const
{
	return epochSeconds(RTRFALSE) == rhs.epochSeconds(RTRFALSE);
}

inline RTRBOOL RTRDateTime::operator!=(const RTRDateTime& rhs) const
{
	return epochSeconds(RTRFALSE) != rhs.epochSeconds(RTRFALSE);
}

inline RTRBOOL RTRDateTime::operator<(const RTRDateTime& rhs) const
{
	return epochSeconds(RTRFALSE) < rhs.epochSeconds(RTRFALSE);
}

inline RTRBOOL RTRDateTime::operator<=(const RTRDateTime& rhs) const
{
	return epochSeconds(RTRFALSE) <= rhs.epochSeconds(RTRFALSE);
}


//
// Class RTRDateTimeUsec
// Added for logging purposes.
// For complete class, override comparison operators to account for microseconds
//
class RTRDateTimeUsec : public RTRDateTime
{
public:
	RTRDateTimeUsec();
	RTRDateTimeUsec(const RTRDateTimeUsec& other);

	RTRDateTimeUsec(
			unsigned long secsFromEpoch,
			RTRBOOL isGmtTime=RTRFALSE
			);

	void setToSystemTime();
	RTRString string(
			const char *format,
			RTRBOOL returnAsGmt,
			u_8 uSecsOffset=0
			) const;

	RTRString getDateStringElement(
			const char *element,
			const struct tm *t,
			long usecs,
			u_8 uSecsOffset
			) const;

protected:
	rtr_timeval_t _tv;
};

#endif /* _rtr_datetime_h */
