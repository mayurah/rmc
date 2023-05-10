//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     		       	    --
//|               1400 Kensington Road, Oak Brook, Il. 60521   		    --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
// Author: A. MacGaffey
// Created: "Dec. 20 1995"
// Version: 1.0

#ifndef _cmdline_h
#define _cmdline_h

#ifndef _RDEV_NO_STL_
#include <iostream>
#else
#include <stdio.h>
#endif
#include "rtr/rtstring.h"
#include "rtr/dlinkl.h"

class RTRCmdLineArg;
class RTRCmdLineString;
class RTRCmdLineNumeric;
class RTRCmdLineFlag;
class RTRCmdLineHdr;
class RTRCmdLine;

// Synopsis:
// #include "rtr/cmdline.h"
//
// Description:
//  RTRCmdLineData is a linkable descendant of string.
//
// See Also:
// RTRCmdLine
//
// Inherits:
// RTRString, RTRDLink0


class RTRCmdLineData :
	public RTRDLink0,
	public RTRString
{
public:
  
// Constructor
	RTRCmdLineData(char *);
		// _TAG Constructor

};

// Synopsis:
//
//  #include "rtr/cmdline.h"
//
// Description:
//
//  RTRCmdLineArg is the base class for command line arguments.
//  This class includes the base constructor, accessor methods,
//  state checking methods, and stringValue() for getting a
//  RTRString for the argument's value.
//
// See Also:
//  RTRCmdLine, RTRCmdLineData, RTRCmdLineFlag, RTRCmdLineList, 
//  RTRCmdLineNumeric, RTRCmdLineString, RTRCmdLineHdr, RTRDLink
//
// Inherits:
//  RTRDLink0
//

class RTRCmdLineArg :
	public RTRDLink0
{
public:

	enum Required {
			False = 0,
			True = 1
		};

// Constructor
	RTRCmdLineArg(
			const char* tag, 			// e.g config
			const char* name,			// file_name
			const char* purpose,		// load the given file name
			const char* defaultValue,	// default
			Required required = True
			);
		// _TAG Constructor   

// Destructor
	virtual ~RTRCmdLineArg();
		// _TAG Destructor

// Attributes

	inline Required required() const;
		// Is the argument required to be on the command line?
		// _TAG01 Attributes

	inline RTRBOOL hidden() const;
		// Is the argument hidden (not visible in usage text).
		// _TAG01 Attributes

	inline const RTRString& tag() const;
		// The command line tag. Standard string comparisons are used to
		// compare elements of argv with tag(). 
		// E.g. the "config" part of "-config file_name"
		// _TAG01 Attributes

	inline const RTRString& name() const;
		// The name, if any, of the value to be specified.
		// If name() is null then this arg will be interpreted as a 
		// boolean flag. 
		// E.g. the "file_name" part of "-config file_name"
		// _TAG01 Attributes

	inline const RTRString& defaultValue() const;
		// The default, if any, to be used.
		// _TAG01 Attributes

	inline const RTRString& purpose() const;
		// The description to be used in the long part of the usage text. 
		// E.g. The "load ..." part of 
		//   "Usage: foo -config file_name
		//          -config    load the given file name"
		// _TAG01 Attributes

// State
	RTRBOOL valid() const;
		// _TAG02 State

	inline RTRBOOL error() const;
		// _TAG02 State

// Transformation
	inline const RTRString& stringValue() const;
		// REQUIRE: valid()
		// _TAG03 Transformation
	
// Query
	inline RTRBOOL hasDefault() const;
		// _TAG04 Query

// Operations
#ifndef _RDEV_NO_STL_
	virtual void printShortUsage(std::ostream&) const;		
		// _TAG05 Operations

	virtual void printLongUsage(std::ostream&) const;		
		// _TAG05 Operations

	virtual void printLongUsage(std::ostream&, int) const;		
		// _TAG05 Operations
#else
	virtual void printShortUsage(FILE*) const;		
		// _TAG05 Operations

	virtual void printLongUsage(FILE*) const;		
		// _TAG05 Operations

	virtual void printLongUsage(FILE*, int) const;		
		// _TAG05 Operations
#endif
	virtual void resolve(RTRDLinkList<RTRCmdLineData, RTRDLink0>&);
		// _TAG05 Operations

	virtual void hide();
		// Make argument hidden (it won't show up in usage text).
		// _TAG05 Operations

// Static
	static char argumentPrefix;
		// Static

protected:
//Utility
	void install();
	void deinstall();

// Data
	Required	_required;      
	RTRBOOL		_error;
	RTRBOOL		_hidden;
	RTRString	_tag;        
	RTRString	_name;        
	RTRString	_purpose;      
	RTRString	_defaultValue; 
	RTRString	_value;

// Data
	static RTRCmdLine *cmdLine;

// Friends
friend class RTRCmdLine;
};

// Synopsis:
//
//  #include "rtr/cmdline.h"
//
//  int main(int argc, char **argv)
//  {
//     RTRCmdLineNumeric i("instance", "#", "instance number to use", 1);
//
//     "//" resolve and check command line
//
//     long value = i;
//
//     "//" ...
//
// Description:
//
// Descendant of RTRCmdLineArg which provides type checking. Provides
// cast operator to long.
//
// See Also:
//  RTRCmdLine
//
// Inherits:
//  RTRCmdLineArg

class RTRCmdLineNumeric :
	public RTRCmdLineArg
{
public:
// Constructor
	RTRCmdLineNumeric(
			const char* tag, 		// e.g size
			const char* name,		// watch_list_size
			const char* purpose,
			Required req = True
			);
		// _TAG Constructor

	RTRCmdLineNumeric(
			const char* tag, 		// e.g size
			const char* name,		// watch_list_size
			const char* purpose,
			long defaultValue,
			Required req = True
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCmdLineNumeric();
		// _TAG Destructor

// Transformation
	operator long() const;
		// REQUIRE : valid();
		// _TAG01 Transformation
};

// Synopsis:
//
//  #include "rtr/cmdline.h"
//
//  int main(int argc, char **argv)
//  {
//      RTRCmdLineString string("config", "file_name", "load the given file", "default");
//
//      "//" resolve and check command line
//
//      RTRString &value = string;
//
//      "//" ...
//
// Description:
//
// Descendant of RTRCmdLineArg which provides type checking.  Strings provide 
// cast operator to RTRString.
//
// See Also:
//  RTRCmdLine
//
// Inherits:
//  RTRCmdLineArg

class RTRCmdLineString :
	public RTRCmdLineArg
{
public:
// Constructor
	RTRCmdLineString(
			const char* tag, 			// e.g config
			const char* name,			// e.g. file_name
			const char* purpose,
			Required req = True
			);
		// _TAG Constructor

	RTRCmdLineString(
			const char* tag, 			// e.g config
			const char* name,			// e.g. file_name
			const char* purpose,
			const char* defaultValue,
			Required req = True
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCmdLineString();
		// _TAG Destructor

// Transformation
	operator const RTRString&() const;
		// REQUIRE : valid();
		// _TAG01 Transformation
};

// Synopsis:
//
//  #include "rtr/cmdline.h"
//
// Description:
//
//  RTRCmdLineStringFlag is similar to a RTRCmdLineString except:
//
// \bullet
//     1. The tag can appear on the command-line without a string value.
//        In this case the default value becomes the value.
//     2. If the tag does not appear on the command-line the value is
//        empty, the default is not used.
// \endbullet
//
//  Example:
//
// \verbatim
//    RTRCmdLineStringFlag inst("install", "svc_name", "install a service",
//                              "MyService", RTRCmdLineArg::False);
//
//    Command Line                       inst value()
//    myprog -install SSL_LITE           "SSL_LITE"
//    myprog -install                    "MyService"
//    myprog                             ""
// \endverbatim
//
// See Also:
//  RTRCmdLine, RTRCmdLineArg, RTRCmdLineFlag,
//
// Inherits:
//  RTRCmdLineArg

class RTRCmdLineStringFlag :
	public RTRCmdLineArg
{
public:
// Constructor
	RTRCmdLineStringFlag(
			const char* tag, 			// e.g config
			const char* name,			// e.g. file_name
			const char* purpose,
			Required req = True
			);
		// _TAG Constructor

	RTRCmdLineStringFlag(
			const char* tag, 			// e.g config
			const char* name,			// e.g. file_name
			const char* purpose,
			const char* defaultValue,
			Required req = True
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCmdLineStringFlag();
		// _TAG Destructor

// Operations
#ifndef _RDEV_NO_STL_
	virtual void printShortUsage(std::ostream&) const;		
		// _TAG05 Operations
#else
	virtual void printShortUsage(FILE*) const;		
#endif

	virtual void resolve(RTRDLinkList<RTRCmdLineData, RTRDLink0>&);
		// _TAG05 Operations

// Static
// Transformation
	operator const RTRString&() const;
		// REQUIRE : valid();
		// _TAG01 Transformation
};


// Synopsis:
//
//  #include "rtr/cmdline.h"
//  RTRCmdLine RTRCmdLine::cmdLine; // Create static first
//
//  int main(int argc, char **argv)
//  {
//     RTRCmdLineFlag trace("trace", "Enable tracing");
//
//     "//" parse and check command line paramenters
//
//     RTRBOOL trc = trace;
//
//     "//" ...
//
// Description:
//
// It is assumed that there is only one instance of RTRCmdLine in an 
// application. Provides built in help flag (tag is "?"). Unused elements 
// of argv are available from leftOvers() (a list of RTRCmdLineData).
//
// Descendant of RTRCmdLineArg which provides type checking.  Flags provide 
// cast to int (and default to True).
//
// See Also:
//  RTRCmdLine, RTRCmdLineStringFlag
//
// Inherits:
//  RTRCmdLineArg
//

class RTRCmdLineFlag :
	public RTRCmdLineArg
{
public:
// Constructor
	RTRCmdLineFlag(
			const char* tag,			// e.g d
			const char* purpose
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCmdLineFlag();
		// _TAG Destructor

// Transformation
	operator RTRBOOL() const;
		// REQUIRE : valid();
		// _TAG01 Transformation    
 
// Operations -- from RTRCmdLineArg
	virtual void resolve(RTRDLinkList<RTRCmdLineData, RTRDLink0>&);
		// _TAG02 Operations -- from RTRCmdLineArg

};

// Synopsis:
//
//  #include "rtr/cmdline.h"
//  RTRCmdLine RTRCmdLine::cmdLine; // Create static first
//
//  int main(int argc, char **argv)
//  {
//     RTRCmdLineHdr hdr1("hdr1", "TRACING OPTIONS");
//				or
//     RTRCmdLineHdr hdr1("hdr1", "==== TRACING OPTIONS =====================");
//				etc.
//
//     "//" parse and check command line paramenters
//     "//" ...
//
// Description:
//
// It is assumed that there is only one instance of RTRCmdLine in an 
// application. Provides built in help flag (tag is "?"). Unused elements 
// of argv are available from leftOvers() (a list of RTRCmdLineData).
//
// Descendant of RTRCmdLineArg which provides a header for the long list of
// options to categorize command line options.  The header should appear prior
// the options.  The header command line option is not printed on the 
// short list.  The "tag" should be a short description as to not interfere
// with the width of printing the long list parameters, but should also be unique
// such that it should not be used as a command line parameter.
//
// See Also:
//  RTRCmdLine, RTRCmdLineStringFlag, RTRCmdLineFlag
//
// Inherits:
//  RTRCmdLineArg
//

class RTRCmdLineHdr :
	public RTRCmdLineArg
{
public:
// Constructor
	RTRCmdLineHdr(
			const char* tag,			// e.g. xxHDRxx1
			const char* purpose			// e.g. "TRACING OPTIONS"
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCmdLineHdr();
		// _TAG Destructor

// Operations
#ifndef _RDEV_NO_STL_
	virtual void printShortUsage(std::ostream&) const	{ }					//not printed
		// _TAG01 Operations

	virtual void printLongUsage(std::ostream&, int) const;		
		// _TAG01 Operations
#else
	virtual void printShortUsage(FILE*) const		{ }						//not printed
		// _TAG01 Operations

	virtual void printLongUsage(FILE*, int) const;		
		// _TAG01 Operations
#endif
	virtual void resolve(RTRDLinkList<RTRCmdLineData, RTRDLink0>&) { }		//nothing to resolve
		// _TAG01 Operations

};

// Synopsis:
//
//  #include <iostream.h>
//  #include "rtr/cmdline.h"
//
//  int main(int argc, char **argv)
//  {
//      RTRCmdLineNumeric i("instance", "#", "instance number to use", 1);
//      RTRCmdLineList files("files", "input files");
//
//      "//" resolve command line and check for errors.
//
//      cout << "outFiles are ";
//      const RTRDLinkList<RTRCmdLineData, RTRDLink0>& l = files.values();
//      for (RTRCmdLineData *d = l.first(); d; d = l.next(d) )
//      {
//           cout << *d; 
//           if ( d != l.last() )
//               cout << ",";
//      }
//      cout << endl;
//
//      "//" ...
//
// Description:
//
//  This descendant of RTRCmdLineArg which provides type checking.  List has no tag
//  and consumes all arguments which remain after others have been processed.  So,
//  only one RTRCmdLineList can be in a command line.
//
// See Also:
//  RTRCmdLine, RTRCmdLineFlag, RTRCmdLineNumeric, RTRCmdLineString
//
// Inherits:
//  RTRCmdLineArg

class RTRCmdLineList :
	public RTRCmdLineArg
{
public:
// Constructor
	RTRCmdLineList(
			const char* name,		// e.g. file
			const char* purpose,	// e.g. "One or more input files"
			Required req = True
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCmdLineList();
		// _TAG Destructor

// State
	RTRBOOL valid() const;
		// _TAG01 State

// Access
	inline const RTRDLinkList<RTRCmdLineData, RTRDLink0>& values() const;
		// REQUIRE: valid()
		// _TAG02 Access

// Operations -- from RTRCmdLineArg
	virtual void resolve(RTRDLinkList<RTRCmdLineData, RTRDLink0>&);
		// _TAG03 Operations

protected:
// Data
	RTRDLinkList<RTRCmdLineData, RTRDLink0> _values;
};

// Synopsis:
//
//  #include "rtr/cmdline.h"
//
//  RTRCmdLine RTRCmdLine::cmdLine;  // Create static first
//  "//"other includes
//
//  int main(int argc, char **argv)
//  {
//     "//" Declare command line arguments 
//     "//" ...
// 
//         "//" resolve the command line
//     RTRCmdLine::cmdLine.resolve(argc, argv);
//
//        "//" check for errors
//     if ( RTRCmdLine::cmdLine.error() )
//     { 
//         RTRCmdLine::cmdLine.printUsage(cerr, argv[0]);
//         return -1;
//     }
//
//     "//" ...
//
//
// Description:
//
//  It is assumed that there is only one instance of RTRCmdLine in an 
//  application. That instance should be accessed from RTRCmdLine::cmdLine.
//  RTRCmdLine provides built in help flag (tag is "?"). Unused elements 
//  of argv are available from leftOvers() (a list of RTRCmdLineData). 
//
// See Also:
//  RTRCmdLine, RTRCmdLineArg, RTRCmdLineFlag, RTRCmdLineList, 
//  RTRCmdLineNumeric, RTRCmdLineString, RTRCmdLineData
//


class RTRCmdLine
{ 
public:
// Constructor
	RTRCmdLine();
		// _TAG Constructor
	
// Destructor
	~RTRCmdLine();
		// _TAG Destructor

// Access
	inline const RTRDLinkList<RTRCmdLineData, RTRDLink0>& leftOvers() const;
		// arguments found on the command line that did not may to 
		// a RTRCmdLineArg.  RTRCmdLineData is a descendant of RTRString.
		// _TAG02 Access

// State
	RTRBOOL error() const; 
		// Was there an error when parsing the command line?
		// _TAG01 State
           
	inline RTRBOOL resolved() const;
		// Has this command line been resolved?
		// _TAG01 State

// Operations
	void resolve(int argc, char **argv);
		// parse the command line parameters.  Assign values to descendants
		// of RTRCmdLineArg that have been created.
		// REQUIRE: !resolved()
		// ENSURE: resolved()
		// _TAG03 Operations

#ifndef _RDEV_NO_STL_
	void printUsage(std::ostream&, const char *argv0) const;
		// called when '-?' option is specified on the command line
		// _TAG03 Operations
#else
	void printUsage(FILE*, const char *argv0) const;
#endif
	
// Data
	static RTRCmdLine cmdLine;
		// The command line

protected:
// Utilities
	void put(RTRCmdLineArg& arg);
		// REQUIRE: !has(arg)

	void remove(RTRCmdLineArg& arg);
		// REQUIRE: has(arg)

	RTRBOOL has(RTRCmdLineArg&);
		// Does it have it?

// Data
	RTRDLinkList<RTRCmdLineData, RTRDLink0> _data;
	RTRDLinkList<RTRCmdLineArg, RTRDLink0> _args;
	RTRBOOL _resolved;
	RTRCmdLineFlag* _help;
		// Help!

// Friends
friend class RTRCmdLineArg;
}; 


inline 
RTRCmdLineArg::Required RTRCmdLineArg::required() const
{
	return _required;
}

inline 
RTRBOOL RTRCmdLineArg::hidden() const
{
	return _hidden;
}

inline 
RTRBOOL RTRCmdLineArg::error() const
{
	return _error;
}

inline 
const RTRString& RTRCmdLineArg::tag() const
{
	return _tag;
}

inline 
const RTRString& RTRCmdLineArg::name() const
{
	return _name;
}

inline 
const RTRString& RTRCmdLineArg::purpose() const
{
	return _purpose;
}

inline 
const RTRString& RTRCmdLineArg::defaultValue() const
{
	return _defaultValue;
}

inline 
RTRBOOL RTRCmdLineArg::hasDefault() const
{
	return ( _defaultValue.count() > 0 ) ? RTRTRUE : RTRFALSE;
}

inline 
const RTRString& RTRCmdLineArg::stringValue() const
{
	RTPRECONDITION ( valid() );
	return _value;
}

inline 
const RTRDLinkList<RTRCmdLineData, RTRDLink0>& RTRCmdLineList::values() const
{
	RTPRECONDITION ( valid() );
	return _values;
}

inline 
RTRBOOL RTRCmdLine::resolved() const
{
	return _resolved;
}

inline 
const RTRDLinkList<RTRCmdLineData, RTRDLink0>& RTRCmdLine::leftOvers() const
{
	return _data;
}

#endif



