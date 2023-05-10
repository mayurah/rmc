//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Jan. 07 1994"
// Version: 1.0

#ifndef RTR_SEQUENCE_ITERATOR 
#define RTR_SEQUENCE_ITERATOR




#include "rtr/rtrdefs.h"

// Synopsis:
//
// Description:
//
// 	SEQUENCE_ITERATOR [ G ]
//
// 	A generic iterator with no commitment to implementation
//
// See Also:
//

template<class T> class RTRSequenceIterator
{
private:

protected:

public:

//
	virtual void start() = 0;
		// Make the first item available as item().
		// _TAG01 Other

	virtual void finish() = 0;
		// Make the last item available as item().
        // _TAG01 Other

	virtual void forth() = 0;
		// Go forth to the next item().
        // _TAG01 Other

	virtual void back() = 0;
		// Go forth to the previous item().
        // _TAG01 Other

	virtual int count() = 0;
		// The number of items in the sequence.
        // _TAG01 Other

	virtual RTRBOOL empty() = 0;
		// Is the sequence empty.
        // _TAG01 Other

	virtual RTRBOOL off() = 0;
		// Has the iteration been completed?
        // _TAG01 Other

	virtual T *item() = 0;
		// The currently available item.
        // _TAG01 Other

};


#endif /* RTR_SEQUENCE_ITERATOR */


