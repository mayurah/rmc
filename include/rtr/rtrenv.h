#ifndef __rtrenv_h
#define __rtrenv_h

/****************************************************************************

|---------------------------------------------------------------
|                Copyright (C) 1995 Reuters,                  --
|                                                             --
|         1400 Kensington Road, Oak Brook, IL. 60521          --
|                                                             --
| All rights reserved. Duplication or distribution prohibited --
|---------------------------------------------------------------

  created:     July 19, 1995
  version:

  description:  Header file to support functions defined in rtrenv.c;
  				functions to get and set
  				reuters local machine configuration info, such as
				the fully qualified ipcroute file name, the 
				fully qualified master fid file name.


*******************************************************************************/

#include "rtr/platform.h"


	/* return values */
#define RTR_ENV_SUCCESS		0
#define RTR_ENV_FAILURE		-1


	/* function declarations */
#if defined(__cplusplus)
extern "C" {
#endif

		/* Get Info Prototypes */
short RTRGetEnv(
							const char *envOption, 
							char *retBuf, 
							unsigned short retBufLen);

short RTRGetEnvVal(
							const char * lpszEnvKey,
							const char *envOption, 
							char *retBuf, 
							unsigned short retBufLen);

short RTRGetInCurrentDir(
							const char * envOption,
							char *lpszRetBuf,
							unsigned short retBufLen );

short RTRGetEnvVar(
							const char *envOption, 
							char *lpszRetBuf, 
							unsigned short retBufLen);

short RTRGetEnvDefault(
							const char *envOption, 
							char *lpszRetBuf, 
							unsigned short retBufLen);
#if defined(_WIN32)
short RTRGetEnvRegistry(
							const char *envKey, 
							const char *envOption, 
							char *lpszRetBuf, 
							unsigned short retBufLen);
#endif
#if defined(_WIN32) || defined(_WIN16)
short RTRGetEnvWinIni(
							const char *envOption, 
							char *lpszRetBuf, 
							unsigned short retBufLen);
#endif


		/* Set Info Prototypes */
short RTRSetEnv(const char *envOption, char *value);

short RTRSetEnvVal(const char  *lpszEnvKey,const char *lpszEnvClass, const char *envOption, const char *value);

short RTRSetEnvVar(const char *envOption, char *value);

#if defined(_WIN32)
short RTRSetEnvRegistry(const char *envKey, const char *envClass, const char *envOption, const char *value);
#endif

#if defined(_WIN32) || defined(_WIN16)
short RTRSetEnvWinIni(const char *envOption, char *value);
#endif


#if defined(__cplusplus)
}
#endif

#endif
