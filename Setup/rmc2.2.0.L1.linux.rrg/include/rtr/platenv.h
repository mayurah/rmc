
/****************************************************************************

|---------------------------------------------------------------
|                Copyright (C) 1995 Reuters,                  --
|                                                             --
|         1400 Kensington Road, Oak Brook, IL. 60521          --
|                                                             --
| All rights reserved. Duplication or distribution prohibited --
|---------------------------------------------------------------

  Description:  Header file to provide prototypes for C functions defined in
				platenv.c .

				platenv provides functions to Get and Set values from the
				environment.  The environment is defined as the registry
				(WIN32), the win.ini file (WIN16) and the shell environment.

				The function PLATGetEnvSearch() may be used to find an
				environment variable in a platform-independent manner.

				The platenv functions have been written to solve some of
				the problems with the rtrenv functions.  The platenv
				functions allow the caller to specify all of the necessary
				parameters, removing the requirement that the environment
				variables needs to be defined in rtr/environ.h .  The
				platenv PLATGetEnvSearch() function allows the caller
				to disable any part of the environment search.  In
				particular, the rtrenv routines always return a value --
				the PLATGetEnvSearch() routine allows the user to disable
				the default value.


*******************************************************************************/

#ifndef __platenv_h
#define __platenv_h


#include "rtr/platform.h"



	/* function declarations */
#if defined(__cplusplus)
extern "C" {
#endif


#define PLAT_ENV_SUCCESS 0
#define PLAT_ENV_FAILURE -1




/*
 *	For all of the PLATGet functions the return value is:
 *
 *		PLAT_ENV_SUCCESS if a value was copied from the environment
 *			into the supplied buffer.
 *
 *		PLAT_ENV_FAILURE if no value was found in the environment.
 *
 *		OTHER:  If the environment string is too large to fit in the
 *				supplied buffer, the length of the environment string
 *				is returned (including NUL-terminator).
 *
 *	The buffer parameter may be NULL if the buffer_size parameter is 0.
 */



#ifdef _WIN32

/* Registry ROOT keys (categories). */
#define HKEY_CLASSES_ROOT_STR	"HKEY_CLASSES_ROOT"
#define HKEY_CURRENT_USER_STR	"HKEY_CURRENT_USER"
#define HKEY_LOCAL_MACHINE_STR	"HKEY_LOCAL_MACHINE"
#define HKEY_USERS_STR			"HKEY_USERS"

/* 	For both PLATGetEnvWinReg() and PLATSetEnvWinReg() the env_key parameter
 *	specifies the WIN32 registry key with a backslash-delimited string.  If
 *	the first part of the string (left of the first backslash) matches one
 *	of the above ROOT key strings, that will be the ROOT key.  If the first
 *	part of the string does not match one of the ROOT key strings,
 *	HKEY_LOCAL_MACHINE will be the ROOT key.  This means that the env_key
 *	
 *		HKEY_LOCAL_MACHINE\Software\Reuters\Triarch
 *
 *	is the same as the env_key
 *
 *		Software\Reuters\Triarch
 *
 */


int PLATGetEnvWinReg(	const char * env_key,
						const char * env_var,
						char * buffer,
						int buffer_size );

	/* Get value from Win95/WinNT registry specified by env_key and env_var.
	 */


int PLATSetEnvWinReg(	const char * env_key,
						const char * env_var,
						const char * env_class,
						const char * value );
	/* Set value in Win95/WinNT registry specified by env_key and env_var.
	 * The env_class parameter is the lpClass parameter in the WIN32
	 * RegCreateKeyEx() function.
	 */

#endif


#if defined( _WIN32 ) || defined( _WIN16 )

int PLATGetEnvWinIni(	const char * env_section,
						const char * env_var,
						char * buffer,
						int buffer_size );
	/* Get value from Win3.X win.ini file specified by env_key and env_var.
	 */


int PLATSetEnvWinIni(	const char * env_key,
						const char * env_var,
						const char * value );
	/* Set value in Win3.X win.ini file specified by env_key and env_var.
	 */

#endif


int PLATGetEnv(			const char * env_var,
						char * buffer,
						int buffer_size );
	/* Get value from shell environment specified by env_var.
	 */


int PLATSetEnv(	const char * env_var,
				const char * value );
	/* Set value in shell environment specified by env_var.
	 */


int PLATFileInCurrDir( const char * filename );
	/* Returns PLAT_ENV_SUCCESS if specified filename exists in current
	 * working directory, PLAT_ENV_FAILURE otherwise.
	 */


int PLATGetEnvSearch(	const char * filename,
						const char * env_key, 
						const char * env_var,
						const char * default_value,
						char * buffer,
						int buffer_size );

	/* Find value for specified env_var, by searching in the following places
	 * (in this order):
	 *
	 *		1. Current working directory.
	 *				Looks for file specified by filename parameter.
	 *				If found, returns PLAT_ENV_SUCCESS and copies the filename
	 *				parameter to the buffer.
	 *		2. Win95/WinNT Registry (WIN32 only).
	 *				Looks for a registry entry specified by env_key and
	 *				env_var.  If found returns PLAT_ENV_SUCCESS and copies
	 *				the value from the registry into the buffer.
	 *		3. Win.Ini file (Win3.X only).
	 *				Looks for a win.ini entry specified by section env_key
	 *				and variable env_var.  If found returns PLAT_ENV_SUCCESS
	 *				and copies the value from win.ini into the buffer.
	 *		4. Shell environment.
	 *				Looks for a variable defined in the shell environment
	 *				specified by env_var.  If found, returns PLAT_ENV_SUCCESS
	 *				and copies the value from the environment into the buffer.
	 *		5. Supplied default_value parameter.
	 *				Copies the specified default_value into the buffer and
	 *				returns PLAT_ENV_SUCCESS.
	 *
	 *
	 * The caller of the routine can control which steps are performed by
	 * specifying NULL parameters:
	 * 		If filename is NULL, step 1 is skipped.
	 *		If env_var is NULL, steps 2 through 4 are skipped.
	 *		If default_value is NULL, step 5 is skipped.
	 *
	 * If no step returns a value, PLAT_ENV_FAILURE is returned
	 * If a step does find a value, the return value is dictated by the
	 * rules specified for all of the PLATGet functions.
	 *
	 * As an example, the following code searches the environment for the
	 * IPCROUTE variable:
	 * 
	 *		#ifdef _WIN32
	 *			// Win32 registry key
	 *		#define SSLAPI_ENV_KEY "SOFTWARE\\Reuters\\SSL"
	 * 		#elif _WIN16
	 *			// Win16 win.ini section name
	 *		#define SSLAPI_ENV_KEY "SSL"
	 *		#else
	 *			// not used for UNIX
	 *		#define SSLAPI_ENV_KEY NULL
	 *		#endif
	 *
	 *		buffer_size = PLATGetEnvSearch(	"ipcroute",
	 *										SSLAPI_ENV_KEY,
	 *										"IPCROUTE",
	 *										NULL,
	 *										NULL,
	 *										0 );
	 *
	 * If the ipcroute file exists in the current directory or the IPCROUTE
	 * variable exists in the environment, the returned value will be the
	 * buffer size needed to store the ipcroute path/filename.  Otherwise
	 * the returned value will be PLAT_ENV_FAILURE, since the default_value
	 * parameter is specified as NULL.
	 */

#if defined(__cplusplus)
}
#endif

#endif
