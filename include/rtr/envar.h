//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Mar. 21 1994"
// Version: 1.0

#ifndef RTR_ENVIRONMENT_VAR

class RTRExternalValue;
class RTRString;

// Synopsis:
//
// Description:
//
// See Also:
//

class RTREnvironmentVar
{
protected:

	RTRExternalValue *_value;

public:

	RTREnvironmentVar(const char *nm, const char *dflt);
		// _TAG Constructor

	RTREnvironmentVar(const char *nm);
		// _TAG Constructor

	~RTREnvironmentVar();
		// _TAG Destructor

	RTRExternalValue& value();
		// _TAG01 Other

};

#define RTR_ENVIRONMENT_VAR
#endif
