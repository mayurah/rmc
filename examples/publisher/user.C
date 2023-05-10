//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#ifdef _WIN32
#pragma warning( disable : 4355 )
#endif

#include "rtr/mgmtevnt.h"
#include "rtr/rtstring.h"

#include "user.h"

User::User(RTRPublicObject& parent,const char* cname)
:RTRPublicObject(parent, cname, "A User", "User" ,RTRManagedObject::Normal),
_bool(*this,"myBoolean", "Public Boolean", RTRTRUE, RTRTRUE),
_str(*this, "myString", "Public String", "string" , RTRTRUE),
_num(*this, "myNumeric", "Public Numeric", 50),
#ifdef x86_Linux_4X
_lnum(*this, "myLargeNumeric", "Public Large Numeric", 765432123445LL),
#else
_lnum(*this, "myLargeNumeric", "Public Large Numeric", 765432123445),
#endif
_cnt(*this, "myCounter", "Public Counter", 0),
_gauge(*this, "myGauge", "Public Gauge", 0, 0, 20000, RTRTRUE),
_numrng(*this, "myNumericRange", "Public Numeric Range", 0, 0, 30000),
_strcfg(*this, "myStringConfig", "Public String Config", "string config" , RTRTRUE),
_numcfg(*this, "myNumericConfig", "Public Numeric Config", 50, 0, 20000),
_boolcfg(*this,"myBooleanConfig", "Public Boolean Config", RTRFALSE, RTRTRUE),
_gaugecfg(*this, "myGaugeConfig", "Public Gauge Config", 100, 0, 20000, RTRTRUE)
{
	_timedObject = new TimedObject(*this, "timedObject");
}

User::~User()
{
	delete _timedObject;
}

void User::processParameterChange( RTRManagedVariable & var) 
{
	RTRString text;
	RTRMgmtEvent event;

	text.append("The value of the managed variable ");
	text.append(var.name());
	text.append(" is now ");
	text.append(var.toString());
	text.append(".");

	/* log the change of the managed variable */
	event.setIdentifier(_instanceId);
	event.setSeverity(RTRMgmtEvent::Info);
	event.setText(text);
	event.log();
}
