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

#ifndef __RTR_STATIC_BUFFER_POOL
#define __RTR_STATIC_BUFFER_POOL

#include "rtr/rtrdefs.h"
#include "rtr/buffpool.h"
#include "rtr/poolbuff.h"

// Synopsis:
//
// Description:
//
// See Also: 
//

class RTRStaticBufferPool :
	public virtual RTRBufferPool
{

private:


protected:

	RTRPoolableBuffer	**_pool_array;
	int					_max_size;
	int					_end_index;


// Protected functions
	inline RTRBOOL empty()
	{
		return( (_end_index == -1) ? RTRTRUE : RTRFALSE );
	};

	void allocate_buffers( int num_bufs, int buf_size );
		// Allocate `num_bufs' buffers and put into the free pool.


public:


// Constructor
	RTRStaticBufferPool( int max_buffers, int buffer_size );
		// Initialize a buffer pool capable of holding `max_buffers'
		// REQUIRE: max_buffers > 0
		// REQUIRE: buffer_size > 0
		// _TAG Constructor

// Destructor
	~RTRStaticBufferPool();
		// _TAG Destructor

// Access
	RTRPoolableBuffer& getBuffer();
		// Get a buffer from the free pool.
		// REQUIRE: canGetBuffer() implies Result /= 0
		// ENSURE:  !hasBufferInPool( Result );
		// _TAG01 Access

	void putBuffer( RTRPoolableBuffer& aBuffer );
		// Put a buffer into the free pool.
		// REQUIRE: aBuffer != 0
		// REQUIRE: !hasBufferInPool( aBuffer )
		// _TAG01 Access

	RTRBOOL hasBufferInPool( RTRPoolableBuffer& aBuffer );
		// Does the buffer `aBuffer' already exist in the free pool?
		// REQUIRE: aBuffer != 0
		// _TAG01 Access

};

#endif
