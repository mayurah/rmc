//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. Zhang
// Created: "Jul. 10 1997"
// Version: 1.0

#ifndef _clnvar_h
#define _clnvar_h

#include "rtr/mvimpl.h"

#include "rtr/mcntrvar.h"
#include "rtr/mstrvar.h"
#include "rtr/mstrcvar.h"
#include "rtr/mnumvar.h"
#include "rtr/mnumrvar.h"
#include "rtr/mnumcvar.h"
#include "rtr/mlnumvar.h"
#include "rtr/mgvar.h"
#include "rtr/mgcvar.h"
#include "rtr/mbvar.h"
#include "rtr/mbcvar.h"

class RTRShmCloneMgr;

// Synopsis:
// #include"rtr/shmclnv.h"
//
// Description:
// See Also:
//	RTRCloneStringParameter, RTRCloneStringConfig, RTRCloneString, 
//	RTRCloneNumeric, RTRCloneCounter, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//	RTRDLink2
//

class RTRCloneVariable  : 
	public RTRDLink2
{ 
public:
// Destructor
	virtual ~RTRCloneVariable() ;
	// _TAG Destructor

// Operations
	virtual void pollForChange() = 0;
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// 	An implementation of the ManagedCounter base class which
// 	provides increment capability. Note: counters can be
// 	reset to 0 and incremented, but not decremented.
//
// See Also:
//  RTRCloneStringParameter, RTRCloneStringConfig, 
//  RTRCloneString, RTRCloneNumeric, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//  RTRManagedCounter, RTRCloneVariable
//

class RTRCloneCounter : 
	public RTRManagedCounter,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneCounter(
			RTRManagedObject&, 
			RTRNumericImpl*
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneCounter();
		// _TAG Destructor

// Operations
	virtual void reset();
		// Reset this counter to 0.
		// ENSURE : value() == 0
		// _TAG01 Operations

	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);
private:
		// Don't define these.
	RTRCloneCounter(const RTRCloneCounter&);
}; 

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRCloneStringParameter, RTRCloneStringConfig, 
//  RTRCloneString, RTRCloneCounter, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//  RTRManagedNumeric, RTRCloneVariable
//

class RTRCloneNumeric : 
	public RTRManagedNumeric,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneNumeric(
			RTRManagedObject&, 
			RTRNumericImpl*
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneNumeric();
		// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);
protected:

private:
		// Don't define these.
	RTRCloneNumeric(const RTRCloneNumeric&);
}; 


// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRCloneStringParameter, RTRCloneStringConfig, RTRCloneNumeric,
//  RTRCloneString, RTRCloneCounter, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//  RTRManagedLargeNumeric, RTRCloneVariable
//

class RTRCloneLargeNumeric : 
	public RTRManagedLargeNumeric,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneLargeNumeric(
			RTRManagedObject&, 
			RTRLargeNumericImpl*
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneLargeNumeric();
		// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);
protected:

private:
		// Don't define these.
	RTRCloneLargeNumeric(const RTRCloneLargeNumeric&);
}; 


// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
//  An implementation of the ManagedCounter base class which
//  provides increment capability. Note: counters can be
//  reset to 0 and incremented, but not decremented.
//
// See Also:
//  RTRCloneStringParameter, RTRCloneStringConfig, 
//  RTRCloneString, RTRCloneNumeric, RTRCloneCounter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//  RTRManagedNumericParameter, RTRCloneVariable
//
class RTRCloneNumericRange : 
	public RTRManagedNumericRange,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneNumericRange(
			RTRManagedObject&, 
			RTRNumRangeImpl*
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneNumericRange();
		// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG02 Operations

	virtual void set(long rhs);
		// REQUIRE : rhs >= minValue()
		// REQUIRE : rhs <= maxValue()
		// _TAG02 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);
private:
		// Don't define these.
	RTRCloneNumericRange(const RTRCloneNumericRange&);
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRCloneStringParameter, RTRCloneStringConfig, 
//  RTRCloneString, RTRCloneNumeric, RTRCloneCounter, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//  RTRManagedNumericConfig, RTRCloneVariable
//

class RTRCloneNumericConfig : 
	public RTRManagedNumericConfig,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneNumericConfig(
			RTRManagedObject&, 
			RTRNumConfigImpl*
			);
        	// _TAG Constructor

// Destructor
	virtual ~RTRCloneNumericConfig();
        	// _TAG Destructor

// Operations
	virtual void set(long newValue);
		// REQUIRE: modifyEnabled()
		// REQUIRE: newValue >= minValue()
		// REQUIRE: newValue <= maxVa

	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
        	// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);
private:
		// Don't define these.
	RTRCloneNumericConfig(const RTRCloneNumericConfig&);
};


// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRCloneStringConfig, RTRCloneString, 
//  RTRCloneNumeric, RTRCloneCounter, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
// 	RTRManagedStringParameter, RTRCloneVariable 
//

class RTRCloneString :
	public RTRManagedString,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneString(
			RTRManagedObject&, 
			RTRStringImpl*
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneString();
		// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG02 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);

	virtual void set(const char *);
		// REQUIRE: modifyEnabled()
		// _TAG02 Operations

protected:
	unsigned short _transLevel;

private:
		// Don't define these.
	RTRCloneString(const RTRCloneString&);
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRCloneStringParameter, RTRCloneString, 
//  RTRCloneNumeric, RTRCloneCounter, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//  RTRManagedStringConfig, RTRCloneVariable 
//

class RTRCloneStringConfig : 
	public RTRManagedStringConfig,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneStringConfig(
				RTRManagedObject&, 
				RTRStrConfigImpl*
				);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneStringConfig();

// Operations
	virtual void set(const char *);
		// REQUIRE: modifyEnabled()
		// _TAG02 Operations

	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);
protected:
	unsigned short _transLevel;

private:
		// Don't define these.
	RTRCloneStringConfig(const RTRCloneStringConfig&);
};


// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// 	An implementation of the ManagedGauge base class which
// 	provides modification operations.
// 
// See Also:
//  RTRCloneStringParameter, RTRCloneStringConfig, 
//  RTRCloneString, RTRCloneNumeric, RTRCloneCounter, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//  RTRManagedGauge, RTRCloneVariable
//

class RTRCloneGauge : 
	public RTRManagedGauge,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneGauge(
			RTRManagedObject&, 
			RTRGaugeImpl*
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneGauge();
		// _TAG Destructor

// Operations
	virtual void setRange(long newMin, long newMax);
		// REQUIRE: modifyEnabled()
		// REQUIRE: newMin <= newMax

	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);
private:
		// Don't define these.
	RTRCloneGauge(const RTRCloneGauge&);
}; 

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// 	An implementation of the ManagedGaugeConfig base class which
// 	provides modification operations.
// 
// See Also:
//  RTRCloneStringParameter, RTRCloneStringConfig, 
//  RTRCloneString, RTRCloneNumeric, RTRCloneCounter, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//  RTRManagedGaugeConfig, RTRCloneVariable
//

class RTRCloneGaugeConfig : 
	public RTRManagedGaugeConfig,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneGaugeConfig(
			RTRManagedObject&, 
			RTRGaugeConfigImpl*
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneGaugeConfig();
		// _TAG Destructor

// Operations
	virtual void setRange(long newMin, long newMax);
		// REQUIRE: modifyEnabled()
		// REQUIRE: newMin <= newMax

	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);

private:
		// Don't define these.
	RTRCloneGaugeConfig(const RTRCloneGaugeConfig&);
}; 



// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// 	An implementation of the ManagedBoolean base class which
// 	provides modification operations.
// 
// See Also:
//  RTRCloneStringParameter, RTRCloneStringConfig, 
//  RTRCloneString, RTRCloneNumeric, RTRCloneCounter, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//  RTRManagedBoolean, RTRCloneVariable
//

class RTRCloneBoolean : 
	public RTRManagedBoolean,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneBoolean(
			RTRManagedObject&, 
			RTRBoolImpl*
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneBoolean();
		// _TAG Destructor

// Operations
	virtual void set();
		// REQUIRE: modifyEnabled()

	virtual void clear();
		// REQUIRE: modifyEnabled()

	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);
protected:
private:
		// Don't define these.
	RTRCloneBoolean(const RTRCloneBoolean&);
}; 

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// 	An implementation of the ManagedBooleanConfig base class which
// 	provides modification operations.
// 
// See Also:
//  RTRCloneStringParameter, RTRCloneStringConfig, 
//  RTRCloneString, RTRCloneNumeric, RTRCloneCounter, RTRCloneNumericParameter,
//  RTRCloneNumericConfig, RTRCloneBoolean, RTRCloneObject, RTRShmCloneMgr  
//
// Inherits:
//  RTRManagedBooleanConfig, RTRCloneVariable
//

class RTRCloneBooleanConfig : 
	public RTRManagedBooleanConfig,
	public RTRCloneVariable
{ 
public:
// Constructor
	RTRCloneBooleanConfig(
			RTRManagedObject&, 
			RTRBoolConfigImpl*
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRCloneBooleanConfig();
		// _TAG Destructor

// Operations
	virtual void set();
		// REQUIRE: modifyEnabled()

	virtual void clear();
		// REQUIRE: modifyEnabled()

	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);

	virtual void dropClient(RTRManagedVariableClient& oldClient);

private:
		// Don't define these.
	RTRCloneBooleanConfig(const RTRCloneBooleanConfig&);
}; 



#endif
