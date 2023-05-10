//|---------------------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "May. 14 1997"
// Version: 1.0

#ifndef _rtr_mvdes_h
#define _rtr_mvdes_h

#include "rtr/rtstring.h"

#ifndef _RDEV_NO_STL_

#else
	#include <stdio.h>
#endif

class RTRMOClassDescription;
class RTRVarDescImplPub;
class RTRManagedMemAllocator;

//
// Synopsis:
// #include "rtr/mvdes.h"
//
// Description:
// 
// See Also:
//
// Inherits:
//

class RTRMVariableDescription
{ 
public:
// Destructor
	~RTRMVariableDescription();
		// _TAG Destructor

// Identity
	inline const RTRString& name() const ;
		// _TAG01 Identity

// Attributes
	inline char type() const ;
		// _TAG02 Attributes

	inline const RTRString& definition() const ;
		// _TAG02 Attributes

	inline RTRMOClassDescription& context() const;
		// _TAG02 Attributes

// Private Implementation
	RTRVarDescImplPub *storeImplPub(RTRManagedMemAllocator&) const;
		// Don't ask.
		// _TAG08 Private Implementation

protected:
// Constructor
	RTRMVariableDescription(
			RTRMOClassDescription&, 
			const char* nm, 
			const char* def, 
			char type);
				// Constructed using values 
				// _TAG Constructor

	void cleanUpImplPub(RTRManagedMemAllocator& alc);

	RTRBOOL initImplPub(RTRManagedMemAllocator& alc);

// Data
	RTRString _name;
	RTRString _definition;
	char _type;
	RTRVarDescImplPub* _storeImplPub; // Store server side impl
	RTRMOClassDescription& _context;

private:
// Friends
#ifndef _RDEV_NO_STL_
	friend std::ostream& operator<<(std::ostream& os, const RTRMVariableDescription& );
#else
public:
	void print(FILE* os);
#endif
private:
	friend class RTRMOClassDescription;
	friend class RTRMODescrDictionary;

// Don't implement
RTRMVariableDescription(const RTRMVariableDescription&);
RTRMVariableDescription& operator=(const RTRMVariableDescription&);
}; 

inline
const RTRString& RTRMVariableDescription::name() const 
{
	return _name;
}

inline
char RTRMVariableDescription::type() const 
{
	return _type;
}

inline
const RTRString& RTRMVariableDescription::definition() const 
{
	return _definition;
}

inline 
RTRMOClassDescription& RTRMVariableDescription::context() const
{
	return _context;
}


#endif
