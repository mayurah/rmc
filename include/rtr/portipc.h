#ifndef _portipc_h
#define _portipc_h

#define	MAX_SEMAPHORE	80

#ifdef	_WIN32
#include <windows.h>
#include <process.h> // for getpid()
typedef	int pid_t;
#define	INVALID_HANDLE	NULL
#define	SEMAPHORE_WAIT_TIMEOUT	0

#else

#ifdef	OS2
#define INCL_DOS
#define INCL_DOSMEMMGR
#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES
#define INCL_DOSERRORS
#include <os2.h>
#include <stdio.h>
#include <string.h>
#include <process.h> // for getpid()
typedef	int pid_t;
#define	INVALID_HANDLE	NULL
#define	SEMAPHORE_WAIT_TIMEOUT	100
typedef	ULONG HANDLE;
#else

#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>

#if defined(x86_Linux_2X) || defined(x86_Linux_3X) || defined(x86_Linux_4X)
#include <string.h>
#endif

#ifdef sun4_SunOS_41X
extern char *shmat();
#else
extern void *shmat();
#endif

#if !defined(sun4_SunOS_41X)
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
#endif

#if !defined(SOLARIS2) && !defined(HP_UX) && !defined(x86_Linux_2X) && !defined(x86_Linux_3X) && !defined(x86_Linux_4X)
extern "C" char *strerror(int errnum);
#endif

typedef	int HANDLE;
#define	INVALID_HANDLE	-1

#endif	/*  __OS__ */
#endif	/*	_WIN32 */
#endif	/*	portipc_h */
