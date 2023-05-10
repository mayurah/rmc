/*
//
//|---------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                  --
//|                                                             --
//|         1111 W. 22nd Street, Oak Brook, IL. 60523			--
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Greg Maxwell
//  created:       1/17/2013
//  version:       1.0
//
//  description:
//  Provides a rtr_gettimeofday() function for MS Windows, with
//  reference to system time, and with microsecond resolution.
//  Linux version wraps gettimeofday() system call.
//
*/

#ifndef __rtr_gettimeofday_h
#define __rtr_gettimeofday_h

#include <time.h>
#include <string.h>
#include "rtr/rtdataty.h"
#include "rtr/rtrdefs.h"

#ifndef _WIN32
#include <sys/time.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef _WIN32

struct rtr_timeval
{
	time_t tv_sec;
	long   tv_usec;
};
typedef struct rtr_timeval rtr_timeval_t;

void rtr_localtime(const time_t *tm, struct tm* tmstruct);
void rtr_ctime(const time_t* tm, char* buf);

#else

#define rtr_localtime localtime_r
#define rtr_ctime ctime_r
typedef struct timeval rtr_timeval_t;

#endif

int rtr_gettimeofday(rtr_timeval_t *tv);
void setTimestampUsecOffset(const char* format, u_8 *uSecOffset);

#if defined(__cplusplus)
}
#endif

#endif
