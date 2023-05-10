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
//  created:       July 18, 1997
//  version:       1.0
//
//  description:
//	Public Mutex
//
//	This header file defines the macros used to define public mutex's.
//	A public mutex can exist in multiple processes. It crosses the
//	process boundary. Because of this it is a little slower than
//	a private mutex.
//
//
//	Expected Use:
//
//	main()
//	{
//		rtr_pub_mutex		mutex;
//		rtr_pub_mutex_error	mutex_error;
//
//		if (RTR_PUB_MUTEX_INIT(mutex,&mutex_error))
//		{
//			printf("Mutex initialized\n");
//		}
//		else
//		{
//			printf("Could not initialize mutex error %d\n",RTR_PUB_MUTEX_ERROR(mutex_error));
//			exit(1);
//		}
//
//		if (!RTR_PUB_MUTEX_LOCK(mutex,mutex_error))
//		{
//			printf("Could not lock mutex error %d\n",RTR_PUB_MUTEX_ERROR(mutex_error));
//			exit(1);
//		}
//
//		if (!RTR_PUB_MUTEX_UNLOCK(mutex,mutex_error))
//		{
//			printf("Could not unlock mutex error %d\n",RTR_PUB_MUTEX_ERROR(mutex_error));
//			exit(1);
//		}
//
//		if (!RTR_PUB_MUTEX_TRYLOCK(mutex,mutex_error))
//		{
//			if (!RTR_PUB_MUTEX_BUSY(mutex_error))
//			{
//				printf("Could not trylock mutex error %d\n",RTR_PUB_MUTEX_ERROR(mutex_error));
//				exit(1);
//			}
//		}
//		else if (!RTR_PUB_MUTEX_UNLOCK(mutex,mutex_error))
//		{
//			printf("Could not unlock mutex error %d\n",RTR_PUB_MUTEX_ERROR(mutex_error));
//			exit(1);
//		}
//
//		if (!RTR_PUB_MUTEX_DESTROY(mutex,mutex_error))
//			printf("Could no destroy mutex error %d\n",RTR_PUB_MUTEX_ERROR(mutex_error));
//	}
*/

#ifndef __rtrpubmutx_h
#define __rtrpubmutx_h

#include "rtr/rtrdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEV_POS_THR
/***************************************************************************/
/* Posix threads definitions */

#include <pthread.h>

typedef pthread_mutex_t	rtr_pub_mutex;
typedef int rtr_pub_mutex_error;

#define RTR_PUB_MUTEX_ERROR(error)	error

#define RTR_PUB_MUTEX_INIT(mutex,error) \
	(((error = pthread_mutex_init(&mutex,PTHREAD_PROCESS_SHARED)) == 0 ) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_DESTROY(mutex,error) \
	(((error = pthread_mutex_destroy(&mutex)) == 0 ) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_LOCK(mutex,error) \
	(((error = pthread_mutex_lock(&mutex)) == 0) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_UNLOCK(mutex,error) \
	(((error = pthread_mutex_unlock(&mutex)) == 0) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_TRYLOCK(mutex,error) \
	(((error = pthread_mutex_trylock(&mutex)) == 0) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_BUSY(error) (error == EBUSY)

/* End posix threads definitions */
/***************************************************************************/
#endif



#if defined(DEV_SOL_THR)
/***************************************************************************/
/* Solaris threads definitions */

#include <thread.h>
#include <synch.h>

typedef mutex_t	rtr_pub_mutex;
typedef int rtr_pub_mutex_error;

#define RTR_PUB_MUTEX_ERROR(error)	error

#define RTR_PUB_MUTEX_INIT(mutex,error) \
	(((error = mutex_init(&mutex,USYNC_PROCESS,0)) == 0 ) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_DESTROY(mutex,error) \
	(((error = mutex_destroy(&mutex)) == 0 ) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_LOCK(mutex,error) \
	(((error = mutex_lock(&mutex)) == 0) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_UNLOCK(mutex,error) \
	(((error = mutex_unlock(&mutex)) == 0) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_TRYLOCK(mutex,error) \
	(((error = mutex_trylock(&mutex)) == 0) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_BUSY(error) (error == EBUSY)

/* End solaris threads definitions */
/***************************************************************************/
#endif



#ifdef _WIN32
/***************************************************************************/
/* win32 thread definitions */

#include <windows.h>

typedef HANDLE	rtr_pub_mutex;
typedef DWORD rtr_pub_mutex_error;

#define RTR_PUB_MUTEX_ERROR(error)	GetLastError()

#define RTR_PUB_MUTEX_INIT(mutex,error) \
	(((mutex = CreateMutex(NULL,FALSE,NULL)) == 0 ) ? RTRFALSE : RTRTRUE)

#define RTR_PUB_MUTEX_DESTROY(mutex,error) \
	((CloseHandle(mutex)) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_LOCK(mutex,error) \
	(((error = WaitForSingleObject(mutex,INFINITE)) == WAIT_OBJECT_0) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_UNLOCK(mutex,error) \
	((ReleaseMutex(mutex)) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_TRYLOCK(mutex,error) \
	(((error = WaitForSingleObject(mutex,0)) == WAIT_OBJECT_0) ? RTRTRUE : RTRFALSE)

#define RTR_PUB_MUTEX_BUSY(error) (error == WAIT_TIMEOUT)

/* End win32 threads definitions */
/***************************************************************************/
#endif

#ifdef __cplusplus
}
#endif

#endif
