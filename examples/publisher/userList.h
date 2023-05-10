//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------

#include "user.h"

// Synopsis:
//	userList.h
//
// Description:
//	A class describing the states of objects: 
//		Init, Normal, Recovering, Waiting and Dead.
//
// See Also:
//
// Inherits:
//	RTRPublicObject

class UserList: 
	public RTRPublicObject
{
public:
	UserList(RTRPublicObject& parent, const char* cname);
	~UserList();

protected:
	// Utilities
	void processParameterChange( RTRManagedVariable & var);

	// Data
	User *_user[3];

	RTRPublicBoolean	_deleteUser;
	RTRPublicBoolean	_createUser;
	RTRPublicBoolean	_goNormal;
	RTRPublicBoolean	_goRecovering;
	RTRPublicBoolean	_goWaiting;
	RTRPublicBoolean	_goDead;

};
