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
//  This header file is meant to define platform-specific function calls.
//	This file would likely be included in .[cC] files, whereas
//	systypes.h might be included in header files.
//
//  NOTE : This header file MUST use old style comments since
//  it is used by K&R, ANSI, and C++ compilers.
//
*/

#ifndef __rtr_dev_syscalls_h
#define __rtr_dev_syscalls_h

#ifdef __cplusplus
extern "C" {
#endif 

#include "rtr/systypes.h"
#include <string.h>

#ifdef SOLARIS2
#ifdef __CLCC__
/* CenterLine compiler */
int gettimeofday(struct timeval* tp ...);
#endif /* __SUNPRO_CC */
#endif /* SOLARIS2 */

#ifdef _WIN32
#include <sys/timeb.h>
/* This should really be a function and return 0 or -1,
   but we don't yet have a libdev.a for this code to live in.
   So we'll just assume that the return value is not needed.
*/
#define gettimeofday(tp, tzp) { \
	struct _timeb tstruct; \
	if ((tp) != 0) { \
		_ftime(&tstruct); \
		(tp)->tv_sec = (long)tstruct.time; \
		(tp)->tv_usec = tstruct.millitm * 1000; \
	} \
}
#endif /* _WIN32 */

#ifdef IBMRS
#ifdef __cplusplus
#include <sys/time.h>
#else
int gettimeofday(struct timeval* tp, struct timezone* tzp);
#endif /* __cplusplus */
#endif /* IBMRS */

#ifdef sun4_SunOS_41X
int gettimeofday(struct timeval* tp, struct timezone* tzp);
#endif

#ifdef __cplusplus
};
#endif 

#endif /* __DEV_SYSCALLS */
