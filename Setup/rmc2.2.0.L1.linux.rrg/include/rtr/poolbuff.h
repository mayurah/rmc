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
//	created:	April 29, 1994
//	version:	1.0
//

#ifndef __RTR_POOLABLE_BUFFER
#define __RTR_POOLABLE_BUFFER

#include "rtr/rtbuffer.h"
#include "rtr/buffpool.h"

// Synopsis:
//
// Description:
//
// See Also:
// 

class RTRPoolableBuffer :
	public RTRBuffer
{

protected:

	RTRBufferPool&	_buffer_pool;


public:


// Constructor
	RTRPoolableBuffer( int buf_size, RTRBufferPool& aPool );
		// _TAG Constructor

// Destructor
	~RTRPoolableBuffer();
		// _TAG Destructor

// Buffer pool
	void release();
		// Release the buffer back to the pool.
		// _TAG01 Buffer pool

};

#endif
