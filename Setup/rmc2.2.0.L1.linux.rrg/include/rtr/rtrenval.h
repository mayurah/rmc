#ifndef __rtrenval_h
#define __rtrenval_h

//|---------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  created:     November 17, 1995
//  version:
//
//  description:This file declares a C++ class interface to 
//  			functions to the RTRGetEnv() function used to get and set
//  			reuters local machine configuration info, such as
//				the fully qualified ipcroute file name, the 
//				fully qualified master fid file name in a platform
//				independent fashion

#include "rtr/platenv.h"	// included here for HKEY string definitions.


class RTRTriarchEnvironmentValue
{
public:

	RTRTriarchEnvironmentValue(const char *nm, const char *dflt=NULL);
		// nm string must match a pre-defined value in rtr/environ.h

	RTRTriarchEnvironmentValue(	const char *filename,
								const char *env_key,
								const char *env_var,
								const char *default_value );
		// Searches for a value for the specified env_var, by searching
		// in the following places (in this order):
		//
		//		 1. Current working directory.
	 	//			Looks for file specified by filename parameter.
	 	//		 2. Win95/WinNT Registry (WIN32 only).
		//			Looks for a registry entry specified by env_key and
		//			env_var.
		//		 3. Win.Ini file (Win3.X only).
		//			Looks for a win.ini entry specified by section env_key
		//			and variable env_var.
		//		 4. Shell environment.
		//			Looks for a variable defined in the shell environment
		//			specified by env_var.
		//		 5. Supplied default_value parameter.
		//
		//			The caller of the routine can control which steps are
		//			performed by specifying NULL parameters:
		//				If filename is NULL, step 1 is skipped.
		//				If env_var is NULL, steps 2 through 4 are skipped.
		//				If default_value is NULL, step 5 is skipped.
		//			
		//			If no step returns a value, an empty string will be
		//			returned by the value() and to_c() methods.


	~RTRTriarchEnvironmentValue();

	inline const char *value()	const
	{
		return(_value == ((char *)0) ? _empty_val : (const char *)_value);
	};

	inline operator const char *() const
	{
		return(_value == ((char *)0) ? _empty_val : (const char *)_value);
	};

	inline const char *to_c() const
	{
		return(_value == ((char *)0) ? _empty_val : (const char *)_value);
	};


protected:

	char *_value;
	static const char *_empty_val;
};

#endif
