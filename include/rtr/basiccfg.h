#ifndef __basiccfg_h
#define __basiccfg_h

/*******************************************************************************

|---------------------------------------------------------------
|                Copyright (C) 1997 Reuters,                  --
|                                                             --
|         1400 Kensington Road, Oak Brook, IL. 60521          --
|                                                             --
| All rights reserved. Duplication or distribution prohibited --
|---------------------------------------------------------------

  created:     July 30, 1997
  version:

  description:

*******************************************************************************/

#include "rtr/rtrdefs.h"


	/* function declarations */
#if defined(__cplusplus)
extern "C" {
#endif


void *rtrBasicCfgOpen(char *filename);
void rtrBasicCfgClose(void *filehandle);
RTRBOOL rtrBasicCfgGet(	void *filehandle,char *name,
						char *result, int maxresult);
RTRBOOL rtrBasicCfgGetList( void *filehandler, char *name[], int numNames,
							char *result[], int maxresult);

#if defined(__cplusplus)
}
#endif

#endif
