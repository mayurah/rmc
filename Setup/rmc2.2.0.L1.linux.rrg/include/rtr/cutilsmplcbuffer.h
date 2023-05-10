/*
 *|---------------------------------------------------------------
 *|				Copyright (C) 1995 Reuters,				  --
 *|															 --
 *|		 1400 Kensington Road, Oak Brook, IL. 60521		  --
 *|															 --
 *| All rights reserved. Duplication or distribution prohibited --
 *|---------------------------------------------------------------
 *
 *	author:		"Robert Bonaguro"
 */

#ifndef	__smplecbuffer_h
#define	__smplecbuffer_h

#include "rtr/cutilcbuffer.h"			/* RDEVDIFFOK */

#ifdef __cplusplus
extern "C" {
#endif

#if 1
	/* Default buffer pool to initialize */
extern rtr_bufferpool_t *rtr_smplcAllocatePool( rtr_mutex *mutex );
extern int rtr_smplcAddRef(rtr_bufferpool_t *pool);
extern int rtr_smplcDropRef(rtr_bufferpool_t *pool);
extern rtr_msgb_t *rtr_smplcAllocMsg(rtr_bufferpool_t *pool, size_t size);
extern rtr_msgb_t *rtr_smplcAllocMaxMsg(rtr_bufferpool_t *pool);
extern rtr_msgb_t *rtr_smplcDupMsg(rtr_bufferpool_t *pool, rtr_msgb_t *curmblk);
extern rtr_msgb_t *rtr_smplcCopyMsg(rtr_bufferpool_t *pool, rtr_msgb_t *curmblk);
extern int rtr_smplcFreeMsg(rtr_msgb_t *mblk);

extern int rtr_smplcSetUsed(rtr_bufferpool_t *pool, rtr_msgb_t *curmblk);

#else

extern rtr_bufferpool_t *rtr_smplcAllocatePool();
extern int rtr_smplcAddRef();
extern int rtr_smplcDropRef();
extern rtr_msgb_t *rtr_smplcAllocMsg();
extern rtr_msgb_t *rtr_smplcAllocMaxMsg();
extern rtr_msgb_t *rtr_smplcDupMsg();
extern rtr_msgb_t *rtr_smplcCopyMsg();
extern int rtr_smplcFreeMsg();
extern int rtr_smplcSetUsed();

#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
