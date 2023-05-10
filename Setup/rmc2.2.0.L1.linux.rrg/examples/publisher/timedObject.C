//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#ifdef _WIN32
#pragma warning( disable : 4355 )
#endif

#include "timedObject.h"

TimedObject::TimedObject(RTRPublicObject& parent, const char* cname)
	:RTRPublicObject(parent, cname, "Value Changing Object", "TimedObject", RTRManagedObject::Normal),
	_num(*this, "dynamic", "Changing value", 65),
#ifdef x86_Linux_4X 
	_lnum(*this, "large dynamic", "Changing value", 123456789101112LL),
#else
	_lnum(*this, "large dynamic", "Changing value", 123456789101112),
#endif
	_poll(5)
{
	/* set and activate the timer to go off after _poll seconds */
	setTimerOffset(_poll, 0);
	activate();
}

TimedObject::~TimedObject()
{
	if(active())
		deactivate();
}

void TimedObject::update()
{
#ifdef x86_Linux_4X
	if (_lnum.value() == 123456789101112LL)
		_lnum = 30;
	else
		_lnum = 123456789101112LL;
#else
	if (_lnum.value() == 123456789101112)
		_lnum = 30;
	else
		_lnum = 123456789101112;
#endif
	if (_num.value() == 65)
		_num = 20;
	else
		_num = 65;
}

void TimedObject::processTimerEvent()
{
	/* update _num and activate the timer */
	update();
	activate();
}
