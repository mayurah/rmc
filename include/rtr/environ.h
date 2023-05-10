#ifndef __rtr_dev_environ_h
#define __rtr_dev_environ_h

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

  description:  Platform dependent environment storage parameters,
  				e.g, IPCROUTE file environment variable name,
				Master Fid File name win32 Registry storage parameters.
  modified:

  Date	    Modifier	  MR		Description
  -----------------------------------------------------------------------
  04/01/97  J. Merrick    plat0009	Added the SSL API config info

****************************************************************************/




	/* default values, conditionally redefined depending on platform */

	/* ipcroute file info */
#define	IPCROUTE_DEF_DIR			"/var/triarch"
#define	IPCROUTE_DEF_FILENAME		"ipcroute"
#define	IPCROUTE_ENV_VAR_NAME		"IPCROUTE"

	/* master fid info */
#define	MASTER_FID_DEF_DIR			"."
#define	MASTER_FID_DEF_FILENAME		"appendix_a"
#define	MASTER_FID_ENV_VAR_NAME		"MASTER_FID_FILE"

	/* enum type info */
#define	ENUMTYPE_DEF_DIR			"."
#define	ENUMTYPE_DEF_FILENAME		"enumtype.def"
#define	ENUMTYPE_ENV_VAR_NAME		"ENUM_FILE"

	/* rrbp protocols info */
#define	RRBP_PROTOCOLS_DEF_DIR		"."
#define	RRBP_PROTOCOLS_DEF_FILENAME	"RRBP_PROTOCOLS"
#define	RRBP_PROTOCOLS_ENV_VAR_NAME	"RRBP_PROTOCOLS"

	/* triarch config info */
#define TRIARCHCONFIG_DEF_DIR           "/var/triarch/config"
#define TRIARCHCONFIG_DEF_FILENAME      "triarch.cnf"
#define TRIARCHCONFIG_ENV_VAR_NAME      "TRIARCH_CONFIG"

        /* ssl api config info */
#define SSLAPI_DEF_DIR           "."
#define SSLAPI_DEF_FILENAME      "sslapi.cnf"
#define SSLAPI_ENV_VAR_NAME      "SSLAPI_CONFIG"

	/* dacs config info */
#define DACS_ISIS_LOC_ENV_VAR_NAME	"ISIS HOST"
#define DACS_DEF_ISIS_LOC		"NotDefined"
 
#define DACS_ISIS_PORT_ENV_VAR_NAME	"ISIS PORT"
#define DACS_DEF_ISIS_PORT		"6102"
 
#define DACS_SITE_ID_ENV_VAR_NAME	"DACS SITE ID"
#define DACS_DEF_SITE_ID		"DACS"

	/* triarch control info */
#define TRIARCHCONTROL_DEF_FILENAME      "tcproc.exe"
#define TRIARCHCONTROL_ENV_VAR_NAME      "TRIARCH_CONTROL_EXE"

#define TRIARCH_SW_DEF_PATH		"/ssl4.0/triarch"
#define TRIARCH_SW_ENV_VAR_NAME		"TRIARCH_SW"

	/* Definitions for Sun hardware. */
#if defined(sun4) || defined(i86pc)
		/* Definitions for Solaris 1 */
#ifdef sun4_SunOS_41X
#endif
		/* Definitions for Solaris 2 */
#ifdef sun4_SunOS_5X
#endif

#endif



	/* Definitions for HP hardware. */
#ifdef hp
		/* Definitions for hp-ux versions 9.x */
#ifdef hp_HPUX_09X
#endif

#endif



	/* Definitions for Ibmrs hardware. */
#ifdef ibmrs
		/* Definitions for aix 3.2 */
#ifdef ibmrs_AIX_32
#endif

#endif



	/* Definitions for alpha_OSF1 hardware. */
#ifdef alpha_OSF1
		/* Definitions for alpha_OSF1 3.X */
#ifdef alpha_OSF1_3X
#endif

#endif



	/* Definitions for MS-Windows Platforms (Win16) (win32) */
#if defined( _WIN32 )

	#undef	MASTER_FID_DEF_DIR
	#define	MASTER_FID_DEF_DIR				"\\var\\triarch"

	#undef	ENUMTYPE_DEF_DIR
	#define	ENUMTYPE_DEF_DIR				"\\var\\triarch"

	#undef	IPCROUTE_DEF_DIR
	#define	IPCROUTE_DEF_DIR				"\\var\\triarch"

	#undef	RRBP_PROTOCOLS_DEF_DIR
	#define	RRBP_PROTOCOLS_DEF_DIR			"\\var\\triarch"

	#undef  TRIARCHCONFIG_DEF_DIR
	#define TRIARCHCONFIG_DEF_DIR               "\\var\\triarch\\config"

	#define REUTERS_REG_SUBKEY				"Reuters"	

		/* triarch network configuration data - win32 registery storage */
	#define TRIARCH_REG_SUBKEY				REUTERS_REG_SUBKEY"\\Triarch"
	#define TRIARCH_REG_CLASS				"Triarch Config Info"

	#define DACS_REG_SUBKEY				REUTERS_REG_SUBKEY"\\Dacs\\dacs_snkd"
	#define DACS_REG_CLASS				"Dacs Config Info"

	#define SSLAPI_REG_SUBKEY			REUTERS_REG_SUBKEY"\\SSL"
	#define SSLAPI_REG_CLASS			"SSL API Config Info"

	#define TRIARCH_ENV_KEY	"HKEY_LOCAL_MACHINE\\SOFTWARE\\"TRIARCH_REG_SUBKEY
	#define DACS_ENV_KEY	"HKEY_LOCAL_MACHINE\\SOFTWARE\\"DACS_REG_SUBKEY
	#define SSLAPI_ENV_KEY	"HKEY_LOCAL_MACHINE\\SOFTWARE\\"SSLAPI_REG_SUBKEY

		/* win.ini information */
	#define	WIN_INI_TRIARCH_SECTION			"Triarch"

#elif defined( _WIN16 )  /* win16 */

		/* use \\ directory seperators */
	#undef	IPCROUTE_DEF_DIR
	#define	IPCROUTE_DEF_DIR				"\\var\\triarch"

	#undef	MASTER_FID_DEF_FILENAME
	#define	MASTER_FID_DEF_FILENAME			"appendix.a"

		/* win.ini information */
	#define	WIN_INI_TRIARCH_SECTION			"Triarch"

	#define TRIARCH_ENV_KEY					WIN_INI_TRIARCH_SECTION
	#define DACS_ENV_KEY					"Dacs"
	#define SSLAPI_ENV_KEY					"SSL"

#else

	#define TRIARCH_ENV_KEY					""
	#define DACS_ENV_KEY					""
	#define SSLAPI_ENV_KEY					""

#endif


	/* Definitions for VMS */
#ifdef VMS

#undef	IPCROUTE_DEF_DIR
#define	IPCROUTE_DEF_DIR			"var_triarch"

#undef	MASTER_FID_DEF_DIR
#define	MASTER_FID_DEF_DIR			"sys$etc"

#endif


#endif
