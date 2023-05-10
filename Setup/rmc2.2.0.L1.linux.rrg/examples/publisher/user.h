//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#include "timedObject.h"
#include "rtr/pmo.h"

// Synopsis:
//	user.h
//
// Description:
//	A class containing various types of managed variables:
//		RTRPublicBoolean
//		RTRPublicString
//		RTRPublicNumeric
//		RTRPublicLargeNumeric
//		RTRPublicCounter
//		RTRPublicGauge
//		RTRPublicNumericRange
//		RTRPublicLargeNumericRange
//		RTRPublicStringConfig
//		RTRPublicNumericConfig
//		RTRPublicLargeNumericConfig
//		RTRPublicBooleanConfig
//		RTRPublicGaugeConfig.
//	Some types of managed variables are able to be modified
//	by the managing application.
//	
// See Also:
//
// Inherits:
//	RTRPublicObject

class User: public RTRPublicObject
{
public:
	User(RTRPublicObject& parent, const char* cname);
	~User();
protected:
	TimedObject	*_timedObject;

	RTRPublicBoolean _bool;
	RTRPublicString _str;
	RTRPublicNumeric _num;
	RTRPublicLargeNumeric _lnum;	
	RTRPublicCounter _cnt;
	RTRPublicGauge _gauge;
	RTRPublicNumericRange _numrng;
	RTRPublicStringConfig _strcfg;
	RTRPublicNumericConfig _numcfg;
	RTRPublicBooleanConfig _boolcfg;
	RTRPublicGaugeConfig _gaugecfg;
	void processParameterChange( RTRManagedVariable & ) ;
};
