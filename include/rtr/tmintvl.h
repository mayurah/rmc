//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Dec. 29 1993"
// Version: 1.0

#ifndef _rtr_tmintvl_h 
#define _rtr_tmintvl_h

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif
#include "rtr/rtrdefs.h"

// Synopsis:
// #include "rtr/tmintvl.h"
//
// Description:
// A class representing an interval of time specified seconds and 
// milliseconds.\\
// \\
// To be used correctly and efficiently, RTRTimeIntervals should be
// created and set with normalized values (e.g. (1 s, 0 ms) vs.
// (0 s, 1000 ms)).\\
// \\
// For efficiency reasons, the normalization is not performed.  Use
// the static methods to retrieve normalized values.  For example,
// an RTRTimeInterval of 0 seconds 2000 milliseconds should be
// normalized to 2 seconds 0 milliseconds. \\
// \\
// Comparison operators document a precondition, however, for efficiency
// the preconditions are not implemented.
//
// See Also:
// RTRDateTime
//

class RTRTimeInterval
{

#ifndef _RDEV_NO_STL_
friend std::ostream& operator<<(std::ostream& os, const RTRTimeInterval& ri);
#else
public:
void print(FILE*);
#endif
public:

// Static Data
	static const long MSPERSEC;
	static const long MSPERMIN;
	static const long MSPERHOUR;
	static const long MSPERDAY;
	static const long MSPERWEEK;
	static const long SECSPERMIN;
	static const long SECSPERHOUR;
	static const long SECSPERDAY;
	static const long SECSPERWEEK;
	static const long MINSPERHOUR;
	static const long MINSPERDAY;
	static const long MINSPERWEEK;
	static const long HOURSPERDAY;
	static const long HOURSPERWEEK;
	static const long DAYSPERWEEK;


	RTRTimeInterval(long s = 0L, long ms = 0L);
		// _TAG Constructor

	RTRTimeInterval(const RTRTimeInterval& other);
		// Copy constructor.
        // _TAG Constructor

// Attributes
	inline long seconds() const;
		// _TAG01 Attributes

	inline long milliSeconds() const;
		// _TAG01 Attributes

// State
	inline RTRBOOL normalized() const;
		// Is this time interval normalized?
		// _TAG02 State

// Static Methods
	static long weeks(const RTRTimeInterval&);
		// The normalized number of weeks in the given interval.
		// _TAG03 Static Methods

	static long days(const RTRTimeInterval&);
		// The normalized number of days in the given interval.
		// _TAG03 Static Methods

	static long hours(const RTRTimeInterval&);
		// The normalized number of hours in the given interval.
		// _TAG03 Static Methods

	static long minutes(const RTRTimeInterval&);
		// The normalized number of minutes in the given interval.
		// _TAG03 Static Methods

	static long seconds(const RTRTimeInterval&);
		// The normalized number of seconds in the given interval.
		// _TAG03 Static Methods

	static long milliSeconds(const RTRTimeInterval&);
		// The normalized number of milliseconds in the given interval.
		// _TAG03 Static Methods

// Transformation
	double asMilliSeconds() const;
		// The total number of milliseconds in this interval.
		// _TAG04 Transformation

// Operators
	inline RTRBOOL operator==(const RTRTimeInterval& rhs) const;
		// REQUIRE: normalized() && rhs.normalized()
		// _TAG05 Operators

	inline RTRBOOL operator!=(const RTRTimeInterval& rhs) const;
		// REQUIRE: normalized() && rhs.normalized()
		// _TAG05 Operators

	inline RTRBOOL operator<(const RTRTimeInterval& rhs) const;
		// REQUIRE: normalized() && rhs.normalized()
		// _TAG05 Operators

	inline RTRBOOL operator<=(const RTRTimeInterval& rhs) const;
		// REQUIRE: normalized() && rhs.normalized()
		// _TAG05 Operators

	inline RTRBOOL operator>(const RTRTimeInterval& rhs) const;
		// REQUIRE: normalized() && rhs.normalized()
		// _TAG05 Operators

	inline RTRBOOL operator>=(const RTRTimeInterval& rhs) const;
		// REQUIRE: normalized() && rhs.normalized()
		// _TAG05 Operators

	inline RTRTimeInterval& operator=(const RTRTimeInterval& rhs);
		// _TAG05 Operators

	inline RTRTimeInterval operator+(const RTRTimeInterval& rhs) const;
		// A new interval, the sum of this interval and other.
		// _TAG05 Operators

	RTRTimeInterval& operator+=(const RTRTimeInterval& rhs);
		// Increment this interval by other.
		// _TAG05 Operators
	
	inline RTRTimeInterval operator-(const RTRTimeInterval& rhs) const;
		// A new interval, the difference between this interval and other.
		// _TAG05 Operators

	inline RTRTimeInterval& operator-=(const RTRTimeInterval& rhs);
		// Decrement this interval by other.
		// _TAG05 Operators

// Operations
	inline void set(long s, long m);
		// Set seconds to s and milliseconds to m.
		// _TAG06 Modification

	void setToSystemTime();
		// Set this instance to the current system time.
		// _TAG06 Modification

	inline void setToSum(const RTRTimeInterval& first, const RTRTimeInterval& second);
		// Set this interval to the sum of first and second.
		// ENSURE: asMilliSeconds() == 
		//         first.asMilliSeconds() + second.asMilliSeconds()
		// _TAG06 Modification

	void setToDifference(
			const RTRTimeInterval& first, 
			const RTRTimeInterval& second);
		// Set this interval to the difference of first and second.
		// ENSURE: asMilliSeconds() ==
		//         first.asMilliSeconds() - second.asMilliSeconds()
		// _TAG06 Modification

// OBSOLETE
	inline void setInterval(long s, long m);
		// Use set()
		// _TAG06 OBSOLETE

	void addTo(const RTRTimeInterval& other);
		// Use operator+=() .
		// _TAG06 OBSOLETE

	inline void setDifference(const RTRTimeInterval& first, 
							const RTRTimeInterval& second);
		// Use setToDifference() .
		// _TAG06 OBSOLETE

protected: 
// Data
	long _seconds;				// use seconds()
	long _milliSeconds;			// use milliSeconds()
};

inline long RTRTimeInterval::seconds() const 
{
	return _seconds;
};

inline long RTRTimeInterval::milliSeconds() const 
{
	return _milliSeconds;
};

inline RTRBOOL RTRTimeInterval::normalized() const
{
	return (_milliSeconds < MSPERSEC && _milliSeconds >= -MSPERSEC);
};

inline void RTRTimeInterval::set(long s, long m)
{
	_seconds = s;
	_milliSeconds = m;
};

inline void RTRTimeInterval::setInterval(long s, long m)
{
	set(s, m);
};

inline RTRBOOL RTRTimeInterval::operator==(const RTRTimeInterval& other) const
{
	return (_seconds == other.seconds() && _milliSeconds == other.milliSeconds());
};

inline RTRBOOL RTRTimeInterval::operator!=(const RTRTimeInterval& other) const
{
	return (_seconds != other.seconds() || _milliSeconds != other.milliSeconds());
};

inline RTRBOOL RTRTimeInterval::operator<(const RTRTimeInterval& other) const
{
	long s = other.seconds();

	return (_seconds < s || (_seconds == s && _milliSeconds < other.milliSeconds()));
			
};

inline RTRBOOL RTRTimeInterval::operator<=(const RTRTimeInterval& other) const
{
	return (operator<(other) || operator==(other));
};

inline RTRBOOL RTRTimeInterval::operator>=(const RTRTimeInterval& other) const
{
	return (!operator<(other));
};

inline RTRBOOL RTRTimeInterval::operator>(const RTRTimeInterval& other) const
{
	return (!operator<=(other));
};

inline RTRTimeInterval& RTRTimeInterval::operator=(const RTRTimeInterval& other)
{
	set(other.seconds(), other.milliSeconds());
	return *this;
};

inline void RTRTimeInterval::setDifference(const RTRTimeInterval& first,
											const RTRTimeInterval& second)
{
	setToDifference(first, second);
};

inline RTRTimeInterval RTRTimeInterval::operator+(const RTRTimeInterval& other) const
{
	long ts = _seconds + other.seconds();
	long tm = _milliSeconds + other.milliSeconds();

	while (tm > 1000)
	{
		tm -= 1000;
		ts++;
	}

	return RTRTimeInterval(ts, tm);
};

inline void RTRTimeInterval::setToSum(
		const RTRTimeInterval& first, 
		const RTRTimeInterval& second)
{
	long ts = first.seconds() + second.seconds();
	long tm = first.milliSeconds() + second.milliSeconds();

	while (tm > 1000)
	{
		tm -= 1000;
		ts++;
	}
	set(ts, tm);
};

inline RTRTimeInterval RTRTimeInterval::operator-(const RTRTimeInterval& other) const
{
	long ts = _seconds;
	long tm = _milliSeconds;
	long m = other.milliSeconds();

	if (m > tm)
	{
		ts--;
		tm += 1000;
	}

	return RTRTimeInterval(ts - other.seconds(), tm - m);
};

inline RTRTimeInterval& RTRTimeInterval::operator-=(const RTRTimeInterval& other)
{
	setToDifference(*this, other);
	return *this;
};

#endif /* _rtr_tmintvl_h */
