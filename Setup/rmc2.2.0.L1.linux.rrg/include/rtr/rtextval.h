//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|
//|       1400 Kensington Road, Oak Brook IL  60521       
//|
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: A. MacGaffey, T. Hansen
// Created: 11/24/93
// Version: 1.0
//

#ifndef RTR_EXTERNAL_VALUE 
#define RTR_EXTERNAL_VALUE




#include "rtr/rtrdefs.h"
#include "rtr/voiddef.h"
#include "rtr/rtstring.h"


class RTRListOfExternalValue;

// Synopsis:
// #include"rtr/rtextval.h"
//
// Description:
// 	This class provides the same capabilities as the RTRString
// 	class plus the following:
//
//	\bullet
//		o return whether the value is "true" or "false"
//		o if this value is delimited, return a list of the delimited
//		  values based on a given delimiter character
//		o conversion from integer to hexidecimal or octal value
//	\endbullet	
//
// 	See RTRString for a listing of other features.
//
// See Also: 
//	RTRListOfExternalValue
//
// Inherits:
//	RTRString
//

class RTRExternalValue: public RTRString
{

private:

protected:
		
public:
	// Constructor

	RTRExternalValue();
		// An empty value.
		// _TAG Constructor

	RTRExternalValue(const char* n);
		// A copy of the given null terminated string.
        // _TAG Constructor

	RTRExternalValue(const char* n, int i);
		// A copy of the first n characters of s.
        // _TAG Constructor

	RTRExternalValue(unsigned int n);
		// A empty value with capacity n.
        // _TAG Constructor

	RTRExternalValue(const RTRString& n);
		// A copy of the given string.
        // _TAG Constructor

	RTRExternalValue(const RTRExternalValue& n);
		// A copy of the given value.
        // _TAG Constructor

	// Destructor

	virtual ~RTRExternalValue();
		// _TAG Destructor

	// Assignment

    RTRExternalValue&	operator=(const RTRExternalValue& n);
		// _TAG01 Assignment

	// Conversion Functions

	int	integer_from_hexidecimal();	
		// Int value of hex ASCII number in this 
		// _TAG02 Conversion Functions

	int integer_from_octal();		
		// Int value of octal ASCII number in thiso
        // _TAG02 Conversion Functions

	RTRBOOL	isTrue();		
		// Boolean interpretation, false if value "FALSE" . 
        // _TAG02 Conversion Functions

	RTRBOOL isFalse();		
		// Boolean interpretation, true if value "TRUE"
        // _TAG02 Conversion Functions

	RTRListOfExternalValue	list(char delimiter);
		// Current value as a list of external based
		// on the given delimiter character
        // _TAG02 Conversion Functions

	RTRExternalValue* duplicate();
		// Return a copy of this instance. The caller
		// is responsible for memory managing the returned
		// object.
        // _TAG02 Conversion Functions

};

// Synopsis:
// #include "rtr/config.h"
// 
// "//"RTRConfigVar& var;
// RTRListOfExternalValue list = var.list(',');
// for (list.start(); !list.off(); list.forth())
//	cout << list.item() << endl;
//
// Description:
//	A simple list of RTRExternalValue instances.
//
// See Also:
//	RTRExternalValue, RTRString
//

class RTRListOfExternalValue
{

private:

protected:
	char	delimiter; // The delimiter used to parse the value
	int		int_count; // Internal count of number of delimited values 
	int		position;  // Current index for interating
	int		*startIndex; // Pointer to array of indices 
	char 	*value;	     // char * representation of given external value
		
public:

// Constructor
	RTRListOfExternalValue();
		// An empty list.
		// _TAG Constructor

	RTRListOfExternalValue(RTRExternalValue& ev, char delim);
		// Create a list of delimited values using the given external value
		// and the given delimiter.
		// _TAG Constructor

	RTRListOfExternalValue(const RTRListOfExternalValue& lev);
		// Copy constructor
        // _TAG Constructor

// Destructor

	virtual ~RTRListOfExternalValue();
		// _TAG Destructor

// Assignment operator

  RTRListOfExternalValue&	operator=(const RTRListOfExternalValue& lev);
		// _TAG01 Assignment operator

// Iteration

	void	start();
		// Move to first external value
		// _TAG02 Iteration

	void	forth();
		// Move to next external value
		// REQUIRE:
		// 			not_off: !off()
        // _TAG02 Iteration

	RTRBOOL	off();
		// Is there no item at current position?
        // _TAG02 Iteration

// Extraction

	RTRExternalValue	item();
		// Return item at current position
		// REQUIRE:
		//			not_off: !off()
		// _TAG03 Extraction

	RTRExternalValue	iTh(int index);
		// Return item at position "index"
		// REQUIRE:
		//			big_enough: index >= 1
		// REQUIRE:	small_enough: index <= count()
        // _TAG03 Extraction

// Limits

	int		count() const;
		// Number of items in  list.
		// ENSURE:
		//			positive_result: Result > 0
		// _TAG04 Limits

};

#endif /* RTR_EXTERNAL_VALUE */
