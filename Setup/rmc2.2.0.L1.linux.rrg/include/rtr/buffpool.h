//
//|---------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//	author:		Robert Bonaguro
//	created:	May 4, 1994
//	version:	1.0
//

#ifndef __RTR_BUFFER_POOL
#define __RTR_BUFFER_POOL

#include "rtr/rtrdefs.h"
#include "rtr/rtstring.h"
//#inlucde "rtpoolbf.h"

class RTRPoolableBuffer;

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRBufferPool
{

private:


protected:

	RTRBOOL	_empty;


public:


// Destructor
	virtual ~RTRBufferPool(){};
		// _TAG Destructor

// Access

	inline RTRBOOL canGetBuffer()
		// Can a buffer be retrieved from the pool?
		// _TAG01 Access	
	{
		return( (_empty == RTRFALSE) ? RTRTRUE : RTRFALSE);
	};

	virtual RTRPoolableBuffer &getBuffer() = 0;
		// Get a buffer from the free pool.
		// REQUIRE: canGetBuffer() implies Result /= 0
		// ENSURE:  !hasBufferInPool( Result );
		// _TAG01 Access

	virtual void putBuffer( RTRPoolableBuffer &aBuffer ) = 0;
		// Put a buffer into the free pool.
		// REQUIRE: aBuffer != 0
		// REQUIRE: !hasBufferInPool( aBuffer )
		// _TAG01 Access

// Error checking
	virtual RTRBOOL hasBufferInPool( RTRPoolableBuffer &aBuffer ) = 0;
		// Does the buffer `aBuffer' already exist in the free pool?
		// REQUIRE: aBuffer != 0
		// _TAG02 Error checking

};

#endif
