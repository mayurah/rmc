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

#ifndef __platlog_h
#define __platlog_h

#include "rtr/platform.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define PLAT_LOG_DEBUG	1
#define PLAT_LOG_ERROR	2

#if 1  
extern void (*platLogger)(char *className,int logType,char *logtxt);
extern void setPlatLogger(void (*)(char*,int,char*));
extern void clearPlatLogger();
#else
extern void (*platLogger)();
extern void setPlatLogger(void (*)());
extern void clearPlatLogger();
#endif


#define PLATFORM_LOG(className,logType,logtxt) \
	if (platLogger) (*platLogger)((char*)className,(int)logType,(char*)logtxt)

#if defined(__cplusplus)
}
#endif


#endif
