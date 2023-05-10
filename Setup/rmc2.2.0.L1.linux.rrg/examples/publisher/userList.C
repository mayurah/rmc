//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#ifdef _WIN32
#pragma warning( disable : 4355 )
#endif

#include <iostream>
using namespace std;

#include "rtr/mgmtevnt.h"
#include "rtr/rtstring.h"
#include "userList.h"

UserList::UserList(RTRPublicObject& parent,const char* cname)
:RTRPublicObject(parent, cname, "List of users", "UserList",RTRManagedObject::Init),
_deleteUser(*this,"Delete Users", "Delete users?", RTRFALSE, RTRTRUE),
_createUser(*this,"Create Users", "Create users?", RTRTRUE, RTRTRUE),
_goNormal(*this,"Set Normal State", "Set to Normal?", RTRFALSE, RTRTRUE),
_goRecovering(*this,"Set Recovering State", "Set to Recovering?", RTRFALSE, RTRTRUE),
_goWaiting(*this,"Set Waiting State", "Set to Waiting?", RTRFALSE, RTRTRUE),
_goDead(*this,"Set Dead State", "Set to Dead?", RTRFALSE, RTRTRUE)
{
	_user[0] = new User(*this,"user1");
	_user[1] = new User(*this,"user2");
	_user[2] = new User(*this,"user3");
}

UserList::~UserList()
{
	delete _user[0];
	delete _user[1];
	delete _user[2];
}

void UserList::processParameterChange( RTRManagedVariable & var) 
{
	RTRString text;
	RTRMgmtEvent event;

	if(var.name()=="Delete Users")
	{
		for (int i=0;i<3;i++)
		{
			if (_user[i])
			{
				delete _user[i]; 
				_user[i]=0;
			}
		}
		_deleteUser = RTRTRUE;
		_createUser = RTRFALSE;	
	}

	if(var.name()=="Create Users")
	{
		_user[0] = new User(*this,"user1");
		_user[1] = new User(*this,"user2");
		_user[2] = new User(*this,"user3");
		_createUser = RTRTRUE;
		_deleteUser = RTRFALSE;
	}

	if(var.name()=="Set Normal State")
	{
		_goNormal = RTRTRUE;
		_goRecovering = RTRFALSE;
		_goWaiting = RTRFALSE;
		_goDead = RTRFALSE;
		markNormal("The object goes Normal");
	}

	if(var.name()=="Set Recovering State")
	{
		_goNormal = RTRFALSE;
		_goRecovering = RTRTRUE;
		_goWaiting = RTRFALSE;
		_goDead = RTRFALSE;
		markRecovering("The object goes Recovering");
	}
	
	if(var.name()=="Set Waiting State")
	{
		_goNormal = RTRFALSE;
		_goRecovering = RTRFALSE;
		_goWaiting = RTRTRUE;
		_goDead = RTRFALSE;
		markWaiting("The object goes Waiting");
	}
	
	if(var.name()=="Set Dead State")
	{
		_goNormal = RTRFALSE;
		_goRecovering = RTRFALSE;
		_goWaiting = RTRFALSE;
		_goDead = RTRTRUE;
		markDead("The object goes Dead");
	}

	text.append(var.name());
	text.append(" has been triggered.");
	event.setIdentifier(_instanceId);
	event.setSeverity("Info");
	event.setText(text);
    	event.log();
}

