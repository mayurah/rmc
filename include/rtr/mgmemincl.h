//
//|---------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       July 18, 1997
//  version:       1.0
//
//	defines:
//	RTR_MEM_NO_THREAD     - No Thread Safety.
//	RTR_MEM_SINGLE_LOCK   - Use single lock per base allocator (5).
//	RTR_MEM_MULTIPLE_LOCK - Use lock per memory size chunk.
//
//	RTR_MEM_STATS         - Turn on memory statistics.
//

#ifndef __rtr_mgmemincl_h
#define __rtr_mgmemincl_h

#include "rtr/rtrmutx.h"
#include "rtr/rtratomic.h"

// If no options are given and this is a threaded system.
// By default build the best memory manager.
#if !defined(RTR_MEM_NO_THREAD) && !defined(RTR_MEM_SINGLE_LOCK) && \
	!defined(RTR_MEM_MULTIPLE_LOCK)
#if defined(RTR_MUTEX_INIT)
#define RTR_MEM_MULTIPLE_LOCK
//#define RTR_MEM_SINGLE_LOCK
#endif
#endif

#if defined(RTR_MEM_MULTIPLE_LOCK) && defined(RTR_MEM_SINGLE_LOCK)
#error "Cannot define RTR_MEM_MULTIPLE_LOCK and RTR_MEM_SINGLE_LOCK"
#endif

#if defined(RTR_MEM_MULTIPLE_LOCK) && defined(RTR_MEM_NO_THREAD)
#error "Cannot define RTR_MEM_MULTIPLE_LOCK and RTR_MEM_NO_THREAD"
#endif

#if defined(RTR_MEM_SINGLE_LOCK) && defined(RTR_MEM_NO_THREAD)
#error "Cannot define RTR_MEM_SINGLE_LOCK and RTR_MEM_NO_THREAD"
#endif

#if defined(RTR_MEM_SINGLE_LOCK) && !defined(RTR_MUTEX_INIT)
#error "Cannot define RTR_MEM_SINGLE_LOCK on this system. Do not have mutex definitions"
#endif

#if defined(RTR_MEM_MULTIPLE_LOCK) && !defined(RTR_MUTEX_INIT)
#error "Cannot define RTR_MEM_MULTIPLE_LOCK on this system. Do not have mutex definitions"
#endif

#if defined(RTR_MEM_STATS) || defined(RTR_MEM_DEBUG)
#define RTR_MEM_INCR_STAT(val)	RTR_ATOMIC_INCREMENT(val)
#define RTR_MEM_DECR_STAT(val)	RTR_ATOMIC_DECREMENT(val)
#define RTR_MEM_ADD_STAT(val,incr) RTR_ATOMIC_ADD(val,incr)
#define RTR_MEM_STAT_SET(val,newval) RTR_ATOMIC_SET(val,newval)
#else
#define RTR_MEM_INCR_STAT(val)
#define RTR_MEM_DECR_STAT(val)
#define RTR_MEM_ADD_STAT(val,incr)
#define RTR_MEM_STAT_SET(val,newval)
#endif

#endif
