//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T.L. Zhang
// Created: "Jun. 08 1996"
// Version: 1.0
//
// Description:
// Included here are the platform dependent header files and typedefs to be 
// used by lock and thread classes. The flag MULTI_THREAD_SUPPORTED is 
// set/unset accordingly to direct the definitions of those classes 
//

#ifndef _synch_h
#define _synch_h

#include "rtr/rtrdefs.h"

enum RTRLockState { RTRLockSuccess = 0, RTRLockTimeout, RTRLockFailure };
#define MICROSEC 1000000

#undef MULTI_THREAD_SUPPORTED

#if defined(DEV_POS_THR)
#	define MULTI_THREAD_SUPPORTED
#	include <pthread.h>
#	include <signal.h>
#	include <errno.h>
#ifndef Linux /* synch.h is not a GNU/Redhat standard file */
#	include <synch.h>
#endif
	typedef pthread_mutex_t RTRMutexType; 
	typedef pthread_cond_t RTRCondVarType;
	typedef pthread_t RTRThreadId;
	typedef pthread_attr_t RTRThreadAttributeObject;
	typedef pthread_condattr_t RTRCondAttributeObject;
	typedef pthread_mutexattr_t RTRMutexAttributeObject;
	typedef void* RTRThrdFuncRetType;
	typedef void*(* RTRThreadFuncPtr)(void*) ;
#	define RTRThrdSigKill SIGKILL
#elif defined(_WIN32)
#	define MULTI_THREAD_SUPPORTED
#	include <windows.h>
#	if !defined(_WIN_NO_CRIT_SEC) && !defined(_WIN32_WINNT)
#		if (WINVER >= 0x0400)
#			ifdef __cplusplus
extern "C" {
#			endif

			WINBASEAPI BOOL WINAPI TryEnterCriticalSection(LPCRITICAL_SECTION);
#			ifdef __cplusplus
};
#			endif
#		else
#			define _WIN_NO_CRIT_SEC
#		endif
#	endif
	typedef CRITICAL_SECTION RTRMutexType;
	typedef HANDLE RTRCondVarType ;
	typedef DWORD RTRThreadId;
	typedef DWORD RTRThrdFuncRetType;
	typedef DWORD(* RTRThreadFuncPtr)(LPVOID) ;
#	define RTRThrdSigKill 3
#elif defined(SOLARIS2)
#	define MULTI_THREAD_SUPPORTED
#	include <thread.h>
#	include <errno.h>
#	include <synch.h>
	typedef mutex_t RTRMutexType; 
	typedef cond_t RTRCondVarType ;
	typedef thread_t RTRThreadId;
	typedef void* RTRThrdFuncRetType;
	typedef void*(* RTRThreadFuncPtr)(void*) ;
#	define RTRThrdSigKill SIGKILL
#elif	defined(OS2)
#	define MULTI_THREAD_SUPPORTED
#	define INCL_DOS
#	define INCL_DOSPROCESS
#	define INCL_DOSERRORS
#	include <os2.h>
	typedef HMTX RTRMutexType; 
	typedef HEV RTRCondVarType;
	typedef TID RTRThreadId;
	typedef VOID RTRThrdFuncRetType;
	typedef PFNTHREAD RTRThreadFuncPtr;
#	define RTRThrdSigKill SIGKILL

//#elif defined(IBMRS)
//#	include <pthread.h>
//	typedef pthread_mutex_t RTRMutexType; 
// Later


#endif


#endif
