/*
//
//|---------------------------------------------------------------
//|                Copyright (C) 2006 Reuters,                  --
//|         1111 West 22nd Street, Oak Brook, IL. 60523         --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       November 18, 2006
//  version:       1.0
//
//  description:
//  Socket layer initialization routines.
//
*/

#ifndef __rtr_socket_h
#define __rtr_socket_h

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef _WIN32

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <errno.h>
#include <winsock2.h>
#include <stdio.h>
#ifndef EWOULDBLOCK
#define EWOULDBLOCK		WSAEWOULDBLOCK
#endif
#define _IPC_WOULD_BLOCK EWOULDBLOCK

#ifndef snprintf
#define snprintf	_snprintf
#endif

#if defined(FD_SETSIZE)
	#undef FD_SETSIZE
#endif
#define FD_SETSIZE 1024

#if defined(EINTR)
	#undef EINTR
#endif
#define EINTR                   WSAEINTR

#else   // Not defined _WIN32
#include <sys/socket.h>
#define _IPC_WOULD_BLOCK EAGAIN
#endif




extern int rtr_socket_startup(char *errorText);
extern int rtr_socket_shutdown();

#if defined(__cplusplus)
}
#endif


#endif
