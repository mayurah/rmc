//
//|---------------------------------------------------------------
//|                Copyright (C) 2000 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60523          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  description:
//

#ifndef __rtrContDbgLogRdr_h
#define __rtrContDbgLogRdr_h

#include "rtr/platform.h"
#include "sipc/rtrSipcDbgLogRdr.h"

class DEV_SH_LIB_EXPORT rtrContDbgLogRdr
{
public:

// Constructor
	rtrContDbgLogRdr(rtrSipcDbgLogRdr&);

// Destructor
	~rtrContDbgLogRdr();

protected:

	rtrSipcDbgLogRdr	&_dbgReader;

	static RTRBOOL contDump(std::ostream &ostr, char *buf, int len,
							u_8 protId, void *closureArg );

};

#endif
