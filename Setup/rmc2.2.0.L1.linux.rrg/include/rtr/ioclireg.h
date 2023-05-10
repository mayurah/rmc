//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: M. Schwenk
// Created: "Jan. 31 1995"
// Version: 1.0

#ifndef _ioclireg_h 
#define _ioclireg_h

#include "rtr/rtrdefs.h"

class RTRIOClient;

// Synopsis:
//
// Description:
//
// 	Implementation class used to record the registration of a client for
// 	I/O on a specified file descriptor
//
// See Also:
//

class RTRIOClientRegistration
{
public:
// Constructor
	RTRIOClientRegistration(RTRIOClient* client = 0, int fileDescriptor = -1)
	  { _client = client; _fileDescriptor = fileDescriptor; }
		// _TAG Constructor

// Desctructor
	~RTRIOClientRegistration() { }
		// _TAG Destructor

// Attributes
	RTRIOClient* client() const { return _client; }
		// _TAG01 Attributes

	int fileDescriptor() const { return _fileDescriptor; }
		// _TAG01 Attributes

protected:
	RTRIOClient* _client;
	int _fileDescriptor;
};

#endif 
