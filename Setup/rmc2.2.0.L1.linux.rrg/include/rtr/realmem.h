//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       January 22, 1996
//  version:       1.0
//

#ifndef __rtr_realmem_h
#define __rtr_realmem_h

#include "rtr/rgetmem.h"
class RTRManMemStats;

//#define RTR_MEM_DEBUG_PRINT

// Synopsis:
// #include"rtr/realmem.h"
//
// Description:
// 	A RTRAllocRealMem is-a RTRAllocMem that allocates memory
//  from the heap in an efficient way that minimizes wasted
//  memory. It does this be keeping a table of memory pools.
//  Each memory pool contains a list of memory chunks. These
//  memory chunks are what actually give out memory.
//
//  A memoryChunk keeps track of actual allocated memory.
//  It allocates a large chunk of memory and then chunks
//  that memory up based on the needs of the program.
//  It contains the following three data members:
//
//	\bullet
//	o char        *current; --
//      Pointer to next location of memory to be given
//      out of the chunk. Points to the beginning of `bytesLeft'
//      bytes of data left in the chunk.
//	o size_t      bytesLeft; --
//      Bytes left in memory chunk to be given out.
//	o memoryChunk *nextChunk; --
//      Next memory chunk in this list. Used mainly in memoryPool.
//	\endbullet
//
//  The memoryPool is used to access chunks of correct
//  sizes with minimum search for the chunks needed.
//  Each memoryPool entry contains the minimum size (minSize)
//  of the bytesLeft in the chunks that exist in that pool.
//  This means that every memoryChunk in that memoryPool will
//  have at least minSize of bytesLeft in the chunk.
//  Using this we can index into the pool and grab memory
//  directory out of the chunk (without a search). The only
//  time a search is needed is when the bytes needed are
//  greater that the minimum size maintained by the memory
//  pool. This is the minSize of the last memoryPool entry.
//
//  If the bytes needed is greater than the minimum size maintained
//  by the pool, then search must be done on the final memoryPool
//  for a chunk that will fit the bytes needed. For this reason
//  the final memoryPool is limited (default 10) by the number
//  of memoryChunks that may exist in its list.
//
// See Also:
//	RTRFixedAllocator, RTRFixedImpAlloc, RTRFixedMemAlloc, RTRManMemStats,
//	RTRManagedMemory, RTRMemoryDefs, RTRVarAllocator, RTRVarImpAlloc,
//	RTRVarMemAlloc
// 
// Inherits:
//	RTRAllocMem
//

class RTRAllocRealMem :
	public RTRAllocMem
{
public:

// Constructor
	RTRAllocRealMem(int numPages,RTRManMemStats&);
		// _TAG Constructor

// Destructor
	~RTRAllocRealMem();
		// _TAG Destructor

// Operations
	virtual void * getBytes( size_t bytes );
		// _TAG01 Operations

protected:
class memoryPool;
friend class memoryPool;

		// A memoryChunk is used to get memory of various
		// size.
		// A memoryChunk manages an allocated portion of
		// memory. If keeps track of the actual allocated
		// pointer. The pointer of the next free memory
		// position to give away. The number of bytes left
		// out of this chunk. And finally, the next chunk
		// in the list (if one exists).
	class memoryChunk :
		public RTRMallocMemory
	{
	public:
		char		*current;		// Next location to give out
		size_t		bytesLeft;		// Bytes left in memory chunk
		memoryChunk	*nextChunk;		// Next memory chunk in this list
	};

		// A memoryPool manages a pool of memory chunks
		// of ceratin minimum sizes.
	class memoryPool :
		public RTRMallocMemory
	{
	public:
	// Constructor
		memoryPool();

	// Attributes
		unsigned long	elements;	// Number of memory Chunks in list
		size_t			minSize;	// Minimum size of a memory chunk
		int				freePool;	// Index to memory Pool entry
									// in list that will satisfy
									// this request.
		memoryChunk		*chunks;	// List of chunks
	};


// Data members
	char			*_memArrayPtr;	// List of allocated pointers.
	RTRManMemStats	&_stats;		// Statistics.

	memoryPool		*_pool;
	size_t			_granularity;
	short			_size;
	short			_maxLargeChunks;

	size_t			_maxTblSize;
	unsigned char	*_logTable;
	size_t			_shift;

	size_t			_chunkSize;
	int				_numPages;
	size_t			_alignedPtr;

	void			*_lockInfo;		// If thread safe, any lock information.
									// It has to be done this way so we can
									// link in the version after compilation.

// Operations
	RTRBOOL getChunk(size_t bytes);
	void removeChunk(int idx,memoryChunk*,memoryChunk*);

#ifdef RTR_MEM_DEBUG_PRINT
	void dump();
#endif

};


#endif
