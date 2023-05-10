/*
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
//  created:       APRIL 30, 1997
//  version:       1.0
//
//  description:
//
*/

#ifndef __platmem_h
#define __platmem_h

#include "rtr/platform.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if 1
extern void* (*cutilPlatMemoryAlloc)(unsigned long size);
extern void (*cutilPlatMemoryDealloc)(void *memory);
extern void setcutilPlatMemory( void *(*)(unsigned long), void (*)(void*) );
extern void clearcutilPlatMemory();

#else

extern void* (*cutilPlatMemoryAlloc)();
extern void (*cutilPlatMemoryDealloc)();
extern void setcutilPlatMemory();
extern void clearcutilPlatMemory();

#endif


#define PLATFORM_MEMORY_ALLOC(size) (*cutilPlatMemoryAlloc)((unsigned long)size)
#define PLATFORM_MEMORY_DEALLOC(memory) (*cutilPlatMemoryDealloc)(memory)


#if defined(__cplusplus)
}
#endif


#endif
