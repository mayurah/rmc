//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,                              --
//|               1400 Kensington Road, Oak Brook, Il. 60521                --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 10 1995"
// Version: 1.0

#ifndef _shmprxv_h
#define _shmprxv_h

#include "rtr/mo.h"
#include "rtr/mnumvar.h"
#include "rtr/mnumrvar.h"
#include "rtr/mnumcvar.h"
#include "rtr/mgvar.h"
#include "rtr/mcntrvar.h"
#include "rtr/mstrvar.h"
#include "rtr/mstrcvar.h"
#include "rtr/shmmo.h"

class RTRShmProxyMgr;

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//	RTRProxyStringParameter, RTRProxyStringConfig, RTRProxyString, 
//	RTRProxyNumeric, RTRProxyCounter, RTRProxyNumericParameter,
//	RTRProxyNumericConfig, RTRProxyGauge, RTRProxyObject,
//	RTRShmProxyMgr
//
// Inherits:
//	RTRDLink2
//

class RTRProxyVariable  : 
	public RTRDLink2
{ 
public:
// Constructor
	RTRProxyVariable() {};
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyVariable() {};
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
// See Also:
//  RTRProxyStringConfig, RTRProxyString, 
//  RTRProxyNumeric, RTRProxyCounter, RTRProxyNumericParameter,
//  RTRProxyNumericConfig, RTRProxyGauge, RTRProxyObject,
//  RTRShmProxyMgr  
//
// Inherits:
// 	RTRManagedString, RTRProxyVariable 
//

class RTRProxyStringParameter : 
	public RTRManagedString,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyStringParameter(
			RTRManagedObject&, 
			RTRShmMString&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyStringParameter();
		// _TAG Destructor

// Assignment
	virtual RTRManagedString& operator=(const char *);
		// _TAG01 Assignment

	virtual RTRManagedString& operator=(const RTRString&);
		// _TAG01 Assignment

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG02 Operations

	virtual void set(const char *);
		// _TAG02 Operations

	virtual void set(const RTRString&);
		// _TAG02 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyStringParameter(const RTRProxyStringParameter&);
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRProxyStringParameter, RTRProxyString, 
//  RTRProxyNumeric, RTRProxyCounter, RTRProxyNumericParameter,
//  RTRProxyNumericConfig, RTRProxyGauge, RTRProxyObject,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedStringConfig, RTRProxyVariable 
//

class RTRProxyStringConfig : 
	public RTRManagedStringConfig,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyStringConfig(
			RTRManagedObject&, 
			RTRShmMStringConfig&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyStringConfig();

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG01 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG01 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyStringConfig(const RTRProxyStringConfig&);
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// 	Provides set operations for basic string variable.
//
// See Also:
//  RTRProxyStringParameter, RTRProxyStringConfig, 
//  RTRProxyNumeric, RTRProxyCounter, RTRProxyNumericParameter,
//  RTRProxyNumericConfig, RTRProxyGauge, RTRProxyObject,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedString, RTRProxyVariable 
//

class RTRProxyString : 
	public RTRManagedString,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyString(
			RTRManagedObject&, 
			RTRShmMString&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyString();
		// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG01 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG01 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyString(const RTRProxyString&);

}; 

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRProxyStringParameter, RTRProxyStringConfig, 
//  RTRProxyString, RTRProxyCounter, RTRProxyNumericParameter,
//  RTRProxyNumericConfig, RTRProxyGauge, RTRProxyObject,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedNumeric, RTRProxyVariable
//

class RTRProxyNumeric : 
	public RTRManagedNumeric,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyNumeric(
			RTRManagedObject&, 
			RTRShmMNumeric&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyNumeric();
		// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG01 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG01 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyNumeric(const RTRProxyNumeric&);
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
//  RTRProxyStringParameter, RTRProxyStringConfig, 
//  RTRProxyString, RTRProxyNumeric, RTRProxyNumericParameter,
//  RTRProxyNumericConfig, RTRProxyGauge, RTRProxyObject,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedCounter, RTRProxyVariable
//

class RTRProxyCounter : 
	public RTRManagedCounter,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyCounter(
			RTRManagedObject&, 
			RTRShmMNumeric&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyCounter();
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
		// _TAG01 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG01 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyCounter(const RTRProxyCounter&);
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
//  RTRProxyStringParameter, RTRProxyStringConfig, 
//  RTRProxyString, RTRProxyNumeric, RTRProxyCounter,
//  RTRProxyNumericConfig, RTRProxyGauge, RTRProxyObject,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedNumericRange, RTRProxyVariable
//

class RTRProxyNumericParameter : 
	public RTRManagedNumericRange,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyNumericParameter(
			RTRManagedObject&, 
			RTRShmMNumericRange&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyNumericParameter();
		// _TAG Destructor

// Assignment
	virtual RTRManagedNumericRange& operator=(long rhs);
		// REQUIRE : rhs >= minValue()
		// REQUIRE : rhs <= maxValue()
		// _TAG01 Assignment

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG02 Operations

	virtual void set(long rhs);
		// _TAG02 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyNumericParameter(const RTRProxyNumericParameter&);
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRProxyStringParameter, RTRProxyStringConfig, 
//  RTRProxyString, RTRProxyNumeric, RTRProxyCounter, RTRProxyNumericParameter,
//  RTRProxyGauge, RTRProxyObject,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedNumericConfig, RTRProxyVariable
//

class RTRProxyNumericConfig : 
	public RTRManagedNumericConfig,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyNumericConfig(
			RTRManagedObject&, 
			RTRShmMNumericConfig&,
			RTRShmProxyMgr&
			);
        	// _TAG Constructor

// Destructor
	virtual ~RTRProxyNumericConfig();
        	// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
        	// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG01 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG01 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyNumericConfig(const RTRProxyNumericConfig&);
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// 	An implementation of the ManagedGauge base class which
// 	provides modification operations.
// 
// See Also:
//  RTRProxyStringParameter, RTRProxyStringConfig, 
//  RTRProxyString, RTRProxyNumeric, RTRProxyCounter, RTRProxyNumericParameter,
//  RTRProxyNumericConfig, RTRProxyObject,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedGauge, RTRProxyVariable
//

class RTRProxyGauge : 
	public RTRManagedGauge,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyGauge(
			RTRManagedObject&, 
			RTRShmMNumericRange&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyGauge();
		// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG01 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG01 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyGauge(const RTRProxyGauge&);
}; 

/////////////////////////////////////////////////////////////////////////
//
// For backward compatibility: support EliF21 version
//
/////////////////////////////////////////////////////////////////////////

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRProxyStringConfig_EliF21, RTRProxyString_EliF21, RTRProxyNumeric_EliF21, 
//  RTRProxyCounter_EliF21,  RTRProxyNumericParameter_EliF21,
//  RTRProxyNumericConfig_EliF21, RTRProxyGauge_EliF21, RTRProxyObject_EliF21,
//  RTRShmProxyMgr  
//
// Inherits:
// 	RTRManagedString, RTRProxyVariable 
//

class RTRProxyStringParameter_EliF21 : 
	public RTRManagedString,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyStringParameter_EliF21(
			RTRManagedObject&, 
			RTRShmMString_EliF21&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyStringParameter_EliF21();
		// _TAG Destructor

// Assignment
	virtual RTRManagedString& operator=(const char *);
		// _TAG01 Assignment

	virtual RTRManagedString& operator=(const RTRString&);
		// _TAG01 Assignment

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG02 Operations

	virtual void set(const char *);
		// _TAG02 Operations

	virtual void set(const RTRString&);
		// _TAG02 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyStringParameter_EliF21(const RTRProxyStringParameter_EliF21&);
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRProxyStringConfig_EliF21, RTRProxyString_EliF21, RTRProxyNumeric_EliF21, 
//  RTRProxyCounter_EliF21,  RTRProxyNumericParameter_EliF21,
//  RTRProxyNumericConfig_EliF21, RTRProxyGauge_EliF21, RTRProxyObject_EliF21,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedStringConfig, RTRProxyVariable 
//

class RTRProxyStringConfig_EliF21 : 
	public RTRManagedStringConfig,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyStringConfig_EliF21(
			RTRManagedObject&, 
			RTRShmMStringConfig_EliF21&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyStringConfig_EliF21();

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyStringConfig_EliF21(const RTRProxyStringConfig_EliF21&);
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// 	Provides set operations for basic string variable.
//
// See Also:
//  RTRProxyStringConfig_EliF21, RTRProxyString_EliF21, RTRProxyNumeric_EliF21, 
//  RTRProxyCounter_EliF21,  RTRProxyNumericParameter_EliF21,
//  RTRProxyNumericConfig_EliF21, RTRProxyGauge_EliF21, RTRProxyObject_EliF21,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedString, RTRProxyVariable 
//

class RTRProxyString_EliF21 : 
	public RTRManagedString,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyString_EliF21(
			RTRManagedObject&, 
			RTRShmMString_EliF21&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyString_EliF21();
		// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyString_EliF21(const RTRProxyString_EliF21&);

}; 

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRProxyStringConfig_EliF21, RTRProxyString_EliF21, RTRProxyNumeric_EliF21, 
//  RTRProxyCounter_EliF21,  RTRProxyNumericParameter_EliF21,
//  RTRProxyNumericConfig_EliF21, RTRProxyGauge_EliF21, RTRProxyObject_EliF21,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedNumeric, RTRProxyVariable
//

class RTRProxyNumeric_EliF21 : 
	public RTRManagedNumeric,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyNumeric_EliF21(
			RTRManagedObject&, 
			RTRShmMNumeric_EliF21&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyNumeric_EliF21();
		// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyNumeric_EliF21(const RTRProxyNumeric_EliF21&);
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
//  RTRProxyStringConfig_EliF21, RTRProxyString_EliF21, RTRProxyNumeric_EliF21, 
//  RTRProxyCounter_EliF21,  RTRProxyNumericParameter_EliF21,
//  RTRProxyNumericConfig_EliF21, RTRProxyGauge_EliF21, RTRProxyObject_EliF21,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedCounter, RTRProxyVariable
//

class RTRProxyCounter_EliF21 : 
	public RTRManagedCounter,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyCounter_EliF21(
			RTRManagedObject&, 
			RTRShmMNumeric_EliF21&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyCounter_EliF21();
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
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyCounter_EliF21(const RTRProxyCounter_EliF21&);
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
//  RTRProxyStringConfig_EliF21, RTRProxyString_EliF21, RTRProxyNumeric_EliF21, 
//  RTRProxyCounter_EliF21,  RTRProxyNumericParameter_EliF21,
//  RTRProxyNumericConfig_EliF21, RTRProxyGauge_EliF21, RTRProxyObject_EliF21,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedNumericRange, RTRProxyVariable
//

class RTRProxyNumericParameter_EliF21 : 
	public RTRManagedNumericRange,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyNumericParameter_EliF21(
			RTRManagedObject&, 
			RTRShmMNumericRange_EliF21&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyNumericParameter_EliF21();
		// _TAG Destructor

// Assignment
	virtual RTRManagedNumericRange& operator=(long rhs);
		// REQUIRE : rhs >= minValue()
		// REQUIRE : rhs <= maxValue()
		// _TAG01 Assignment

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG02 Operations

	virtual void set(long rhs);
		// _TAG02 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyNumericParameter_EliF21(const RTRProxyNumericParameter_EliF21&);
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// See Also:
//  RTRProxyStringConfig_EliF21, RTRProxyString_EliF21, RTRProxyNumeric_EliF21, 
//  RTRProxyCounter_EliF21,  RTRProxyNumericParameter_EliF21,
//  RTRProxyNumericConfig_EliF21, RTRProxyGauge_EliF21, RTRProxyObject_EliF21,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedNumericConfig, RTRProxyVariable
//

class RTRProxyNumericConfig_EliF21 : 
	public RTRManagedNumericConfig,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyNumericConfig_EliF21(
			RTRManagedObject&, 
			RTRShmMNumericConfig_EliF21&,
			RTRShmProxyMgr&
			);
        	// _TAG Constructor

// Destructor
	virtual ~RTRProxyNumericConfig_EliF21();
        	// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
        	// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyNumericConfig_EliF21(const RTRProxyNumericConfig_EliF21&);
};

// Synopsis:
// #include"rtr/shmprxv.h"
//
// Description:
// 	An implementation of the ManagedGauge base class which
// 	provides modification operations.
// 
// See Also:
//  RTRProxyStringConfig_EliF21, RTRProxyString_EliF21, RTRProxyNumeric_EliF21, 
//  RTRProxyCounter_EliF21,  RTRProxyNumericParameter_EliF21,
//  RTRProxyNumericConfig_EliF21, RTRProxyGauge_EliF21, RTRProxyObject_EliF21,
//  RTRShmProxyMgr  
//
// Inherits:
//  RTRManagedGauge, RTRProxyVariable
//

class RTRProxyGauge_EliF21 : 
	public RTRManagedGauge,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyGauge_EliF21(
			RTRManagedObject&, 
			RTRShmMNumericRange_EliF21&,
			RTRShmProxyMgr&
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRProxyGauge_EliF21();
		// _TAG Destructor

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.
		// _TAG01 Operations

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyGauge_EliF21(const RTRProxyGauge_EliF21&);
}; 

/////////////////////////////////////////////////////////////////////////
//
// For backward compatibility: support EliF14 version
//
/////////////////////////////////////////////////////////////////////////

//
// RTRProxyStringParameter_EliF14
//

class RTRProxyStringParameter_EliF14 : 
	public RTRManagedString,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyStringParameter_EliF14(
				RTRManagedObject&, 
				RTRShmMString_EliF14&,
				RTRShmProxyMgr&
				);

// Destructor
	virtual ~RTRProxyStringParameter_EliF14();

// Assignment
	virtual RTRManagedString& operator=(const char *);

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyStringParameter_EliF14(const RTRProxyStringParameter_EliF14&);
};

//
// RTRProxyString_EliF14
//

class RTRProxyString_EliF14 : 
	public RTRManagedString,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyString_EliF14(
				RTRManagedObject&, 
				RTRShmMString_EliF14&,
				RTRShmProxyMgr&
				);

// Destructor
	virtual ~RTRProxyString_EliF14();

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyString_EliF14(const RTRProxyString_EliF14&);

}; 

//
// RTRProxyNumeric_EliF14
//

class RTRProxyNumeric_EliF14 : 
	public RTRManagedNumeric,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyNumeric_EliF14(
			RTRManagedObject&, 
			RTRShmMNumeric_EliF14&,
			RTRShmProxyMgr&
			);

// Destructor
	virtual ~RTRProxyNumeric_EliF14();

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyNumeric_EliF14(const RTRProxyNumeric_EliF14&);
}; 


//
// RTRProxyCounter_EliF14
//

class RTRProxyCounter_EliF14 : 
	public RTRManagedCounter,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyCounter_EliF14(
			RTRManagedObject&, 
			RTRShmMNumeric_EliF14&,
			RTRShmProxyMgr& 
			);

// Destructor
	virtual ~RTRProxyCounter_EliF14();

// Operations
	virtual void reset();

	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyCounter_EliF14(const RTRProxyCounter_EliF14&);
}; 

//
// RTRProxyNumericParameter_EliF14
//

class RTRProxyNumericParameter_EliF14 : 
	public RTRManagedNumericRange,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyNumericParameter_EliF14(
			RTRManagedObject&, 
			RTRShmMNumericRange_EliF14&,
			RTRShmProxyMgr&
			);

// Destructor
	virtual ~RTRProxyNumericParameter_EliF14();

// Assignment
	virtual RTRManagedNumericRange& operator=(int rhs);
		// REQUIRE : rhs >= minValue()
		// REQUIRE : rhs <= maxValue()

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyNumericParameter_EliF14(const RTRProxyNumericParameter_EliF14&);
};

//
// RTRProxyGauge_EliF14
//

class RTRProxyGauge_EliF14 : 
	public RTRManagedGauge,
	public RTRProxyVariable
{ 
public:
// Constructor
	RTRProxyGauge_EliF14(
			RTRManagedObject&, 
			RTRShmMNumericRange_EliF14&,
			RTRShmProxyMgr&
			);

// Destructor
	virtual ~RTRProxyGauge_EliF14();

// Operations
	virtual void pollForChange();
		// Poll shared memory for changes and notify clients if necessary.

	virtual void addClient(RTRManagedVariableClient& newClient);
		// _TAG02 Operations

	virtual void dropClient(RTRManagedVariableClient& oldClient);
		// _TAG02 Operations
protected:
	RTRShmProxyMgr& _mgr;

private:
		// Don't define these.
	RTRProxyGauge_EliF14(const RTRProxyGauge_EliF14&);
}; 

#endif
