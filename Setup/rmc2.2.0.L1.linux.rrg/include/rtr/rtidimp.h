//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------

#ifndef _rtidimp_h 
#define _rtidimp_h

#include "rtr/rtobjid.h"

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRIdImp : public RTRObjId
{
public:
// Constructor
	RTRIdImp() : RTRObjId() {};
		// _TAG Constructor

	RTRIdImp(const RTRObjId& cntxt, const RTRString& nm)
		: RTRObjId(cntxt, nm)
	{
	}
		// _TAG Constructor

//	RTRIdImp(const char* cntxt, const char* nm)
//		: RTRObjId(cntxt, nm)
//	{
//	}

	RTRIdImp(const char* value)
		: RTRObjId(value)
	{
	}
		// _TAG Constructor

	RTRIdImp(const RTRIdImp& id)
		: RTRObjId(id)
	{
	}
		// _TAG Constructor

};

#endif
