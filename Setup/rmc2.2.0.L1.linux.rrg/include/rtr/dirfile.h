//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Doornbos
// Created: "Jan. 2 1997"
// Version: 1.0
//

#ifndef _rtr_dirfile_h
#define _rtr_dirfile_h

#if !defined(_WIN32) && !defined(OS2)
#include <dirent.h>
#endif

#include "rtr/rtstring.h"
#include "rtr/rtllist.h"

class RTRFileSystemFileIterator;

//
// Synopsis:
// #include "rtr/dirfile.h"
//
// RTRFileSystemDirectory dir("somedir");
// if ( dir.exists() && dir.writeable() )
//	cout << dir.toString() << endl;
//
// Description:
//	RTRFileSystemDirectory is a class which represents a directory
//	in a file system.
// 
// See Also:
//	RTRFileSystemFile, RTRFileSystemFileIterator
//

class RTRFileSystemDirectory
{ 
public:
// Constructor
	RTRFileSystemDirectory(const RTRString& dir);
		// _TAG Constructor

// Destructor
	~RTRFileSystemDirectory();
		// _TAG Destructor

// Attributes
	RTRBOOL readable() const;
		// Is the directory writeable ?
		// REQUIRE: exists()
		// _TAG01 Attributes

	RTRBOOL writeable() const;
		// Is the directory writeable ?
		// REQUIRE: exists()
		// _TAG01 Attributes

	RTRBOOL exists() const;
		// Does the directory exist ?
		// _TAG01 Attributes

// Access Sequential
	RTRFileSystemFileIterator fileIterator();
		// Provides sequential access to the files in this directory.
		// _TAG02 Access Sequential

// Transformation
	inline const RTRString& toString() const;
		// Transform to a string
		// _TAG03 Transformation

protected:
// Data
	RTRString _directory;
}; 

inline
const RTRString& RTRFileSystemDirectory::toString() const
{
	return _directory;
}

//
// Synopsis:
// #include "rtr/dirfile.h"
//
// RTRFileSystemFile file("somefile");
// if ( file.exists() && file.writeable() )
//	cout << file.toString() << endl;
//
// Description:
//	RTRFileSystemFile is a class which represents the name of a file
//	in a file system.
// 
// See Also:
//	RTRFileSystemDirectory, RTRFileSystemFileIterator
//

class RTRFileSystemFile
{ 
public:
// Constructor
	RTRFileSystemFile(
			const RTRString& name);
		// Constructor

	RTRFileSystemFile(
			const RTRFileSystemDirectory& dir,
			const RTRString& name);
		// Constructor

	RTRFileSystemFile(
			const RTRFileSystemDirectory& dir,
			const RTRString& name,
			const RTRString& ext );
		// Constructor

// Destructor
	~RTRFileSystemFile();
		// _TAG Destructor

// Attributes
	RTRBOOL readable() const;
		// Is the file writeable ?
		// REQUIRE: exists()
		// _TAG01 Attributes

	RTRBOOL writeable() const;
		// Is the file writeable ?
		// REQUIRE: exists()
		// _TAG01 Attributes

	RTRBOOL exists() const;
		// Does the file exist ?
		// _TAG01 Attributes

	RTRBOOL isDirectory() const;
		// Is the file a directory ?
		// REQUIRE: exists()
		// _TAG01 Attributes

	RTRBOOL isRegularFile() const;
		// Is the file a regular file ?
		// REQUIRE: exists()
		// _TAG01 Attributes

        RTRFileSystemDirectory path() const;
		// The directory portion of the filename.
		// _TAG01 Attributes
		 
	RTRString name() const;
		// The name portion of the filename.
		// _TAG01 Attributes
				  
// Operations
	void remove();
		// Removes the file.
		// _TAG02 Operations

// Transformation
	inline const RTRString& toString() const;
		// Transform to a string
		// _TAG03 Transformation

// Assignment
	RTRFileSystemFile& operator=(const RTRFileSystemFile& rhs);
	RTRFileSystemFile& operator=(const RTRString& rhs);
	RTRFileSystemFile& operator=(const char *rhs);

protected:
// Data
	RTRString _filename;

// Friends
}; 

inline 
const RTRString& RTRFileSystemFile::toString() const
{
	return _filename;
}

//
// Synopsis:
// #include "rtr/dirfile.h"
//
// // RTRFileSystemDirectory dir("some_dir");
// RTRFileSystemFileIterator iter = dir.fileIterator();
// for(iter.start(); !iter.off(); iter.forth())
// {
//	if ( iter.item().isRegularFile() )
//		do_something();
// }
//
// Description:
//	RTRFileSystemFileIterator provides sequential access to zero or more
//	instances of RTRFileSystemFile.
// 
// See Also:
//	RTRFileSystemDirectory, RTRFileSystemFile
//
class RTRFileSystemFileIterator
{
public:
// Constructor
	RTRFileSystemFileIterator(const RTRFileSystemDirectory& dir);
		// REQUIRE: dir.exists()
		// _TAG Constructor

// Copy Constructor
	RTRFileSystemFileIterator(const RTRFileSystemFileIterator&);
		// _TAG Constructor

// Destructor
	~RTRFileSystemFileIterator();
		// _TAG Destructor

// Attributes
	int count() const;
		// The number of instance configurations available via
		// this iteratr.
		// _TAG01 Attributes

// State
	RTRBOOL off() const;
		// Is this iteration complete?
		// _TAG02 State

	RTRBOOL empty() const;
		// Are there no instance configurations available via
		// this iterator.
		// ENSURE: result implies count() == 0
		// _TAG02 State

// Access
	RTRFileSystemFile& item() const;
		// The current item in the current iteration.
		// _TAG03 Access

// Operations
	void start();
		// Start a new iteration.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void finish();
		// Start an iteration from the last available file.
		// ENSURE: off() implies empty()
		// _TAG04 Operations

	void forth();
		// Continue the current iteration from start() to finish().
		// REQUIRE: !off()
		// _TAG04 Operations

	void back();
		// Continue the current iteration from finish() to start().
		// REQUIRE: !off()
		// _TAG04 Operations

protected:
// Data
	RTRLinkedList<RTRFileSystemFile> _list;
};

#endif
