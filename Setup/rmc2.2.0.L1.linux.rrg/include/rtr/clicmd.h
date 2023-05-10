//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 3 1994"
// Version: 1.0

#ifndef RTR_CLIENT_CMD

// Synopsis:
//
// Description:
//
// 	An abstract base class for "commands" which are used to propogate events
// 	to a client.
//
// See Also:
//

template<class C> class RTRClientCmd
{

public:

	virtual void execute(C& client) = 0;
		// _TAG01 Other

};

#define RTR_CLIENT_CMD
#endif
