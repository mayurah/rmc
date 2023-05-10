//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//

#ifndef _rtobjid_h 
#define _rtobjid_h

#include "rtr/objid.h"

// Synopsis:
//
// Description:
//
// See Also:
//

class RTRObjId : public RTRObjectId
{
public:
// Constructor
	RTRObjId() : RTRObjectId() {};
	RTRObjId(const RTRObjId& cntxt, const RTRString& nm)
		: RTRObjectId(cntxt, nm)
	{
	}
		// _TAG Constructor

//	RTRObjId(const char* cntxt, const char* nm)
//		: RTRObjectId(cntxt, nm)
//	{
//	}

	RTRObjId(const char* value)
		: RTRObjectId(value)
	{
	}
		// _TAG Constructor

	RTRObjId(const RTRObjId& id)
		: RTRObjectId(id)
	{
	}
		// _TAG Constructor

};


#endif
