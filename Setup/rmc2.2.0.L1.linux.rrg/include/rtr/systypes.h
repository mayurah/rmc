/*
//
//|---------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  created:     June 8, 1995
//  version:
//
//  description:
//  This header file is meant to define platform-specific types.
//	This file might be included in header files, whereas syscalls.h
//	would more likely be included in .[cC] files.
//
//  NOTE : This header file MUST use old style comments since
//  it is used by K&R, ANSI, and C++ compilers.
//
*/

#ifndef __rtr_dev_systypes_h
#define __rtr_dev_systypes_h

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif /*_WIN32*/

#endif /* __DEV_SYSTYPES */
