//|---------------------------------------------------------------------------
//|                Copyright (C) 1997,2020 Refinitiv                        --
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
//
//Functionality:  This C++ RMC1.0 consumer application displays all the
//                root managed object information, all the corresponding
//                managed variable information , and all the root
//                man. object and man. variable updates as they are generated.


#include <iostream>
using namespace std;

#include "monitorRoots.h"


Monitor::Monitor( RTRProxyManagedObjectServerPool& p )
	: _pmosp(p)
{
	// Register with the Server Pool to receive events.
	_pmosp.addClient(*this);
	RTRLinkedListCursor<RTRProxyManagedObjectServer> iter = _pmosp.servers();
	for (iter.start(); !iter.off(); iter.forth())
		processProxyManagedObjectServerAdded(_pmosp, (RTRProxyManagedObjectServer&)*iter);
	//_pmosp.addClient(*this);
}

Monitor::~Monitor()
{
	// Be sure to drop client
	if ( _pmosp.hasClient(*this) )
		_pmosp.dropClient(*this);
}


// Event processing for RTRProxyManagedObjectServerPoolClient
void Monitor::processProxyManagedObjectServerAdded(
		RTRProxyManagedObjectServerPool& pmosp,
		RTRProxyManagedObjectServer& pmos
		)
{
	cout << "pmosp event: Added a pmos  @" << pmos.text() << endl;
	// Register with each Server to receive events
	if(pmos.inSync() == RTRTRUE)
	{
		cout << "pmos is inSync" << endl;
		processObjectServerSync(pmos);
	}
	else
	{
		cout << "pmos is not inSync" << endl;
	}
	pmos.addClient(*this);
}

void Monitor::processProxyManagedObjectServerRemoved(
		RTRProxyManagedObjectServerPool& pmosp,
		RTRProxyManagedObjectServer& pmos
		)
{
	cout << "pmosp event: Removed a pmos  @" << pmos.text() << endl;
	// I know that I'm a client (since I received this event)
	// so be sure to drop client when the Server is no longer valid.
	pmos.dropClient(*this);
}


//event processing for RTRProxyManagedObjectServerClient
void Monitor::processObjectServerError(
		RTRProxyManagedObjectServer& pmos
		)
{
	cout << "pmos event: Error  @" << pmos.text() << endl;
	// Drop client since this Server is no longer valid.
	pmos.dropClient(*this);
}

void Monitor::processObjectServerSync(
		RTRProxyManagedObjectServer& pmos
		)
{
	cout << "pmos event: in Sync  @" << pmos.text() << endl;

	// Now that the Server is in Sync I can
	// iterate through all Root Proxy Managed Objects in pmos
	// for each root Proxy Managed Object I will become its client.
	RTRProxyManagedObjectHandleIterator pmosIterator = pmos.roots();
	for ( pmosIterator.start(); !pmosIterator.off(); pmosIterator.forth() )
	{
		// pmosIterator.item() is the handle to the current mo
		cout << "found handle to an mo: " << endl
			<< "     instance identifier is " << pmosIterator.item().instanceId() << endl
			<< "     name is " << pmosIterator.item().name() << endl
			<< "     class identifier is " << pmosIterator.item().classId() << endl;

		//now clone the current Proxy Managed Object
		RTRProxyManagedObjectPtr pmoPtr = pmos.object(pmosIterator.item());

		// Maintain a smart pointer reference to the Proxy Managed Object
		// or else the object will be garbage collected.
		addToList(pmoPtr);

		pmoPtr->addClient( (RTRProxyManagedObjectClient &) *this );
		/* If the Object is already inSync() then I will not receive
		 * the 'Sync' event, so I need to check it here.
		 */
		if ( pmoPtr->inSync() == RTRTRUE )
		{
			cout << "pmoPtr is inSync" << endl;
			processProxyManagedObjectSync(*pmoPtr);
		}
		else
		{
			cout << "pmoPtr is not inSync" << endl;
		}
	}
}

void Monitor::processObjectServerRootAdded(
		RTRProxyManagedObjectServer& pmos,
		const RTRProxyManagedObjectHandle& pmoH
		)
{
	    cout <<"pmos event: Added a root on pmos  @" << pmos.text() << endl;

        //now clone the current Proxy Managed Object
		RTRProxyManagedObjectPtr pmoPtr = pmos.object(pmoH);

		// Maintain a smart pointer reference to the Proxy Managed Object
		// or else the object will be garbage collected.
		addToList(pmoPtr);

		pmoPtr->addClient( (RTRProxyManagedObjectClient &) *this );
		/* If the Object is already inSync() then I will not receive
		 * the 'Sync' event, so I need to check it here.
		 */
		if ( pmoPtr->inSync() == RTRTRUE )
		{
		  cout << "pmoPtr is inSync" << endl;
		  processProxyManagedObjectSync(*pmoPtr);
		}
		else
		{
		  cout << "pmoPtr is not inSync" << endl;
		}

}

void Monitor::processObjectServerRootRemoved(
		RTRProxyManagedObjectServer& pmos,
		const RTRProxyManagedObjectHandle& pmoh
		)
{
	cout <<"pmos event: Removed a root from pmos  @" << pmos.text() << endl;
}


//
// Event processing for RTRProxyManagedObjectClient
//
void Monitor::processProxyManagedObjectError(
		const RTRProxyManagedObject& pmo
		)
{
	cout << "pmo event: Error  @" << pmo.text() << endl;
}

void Monitor::processProxyManagedObjectSync(
	const RTRProxyManagedObject& pmo
	)
{
	cout << "pmo event: Sync" << endl;

	//iterate through all Proxy Managed Variables
	RTRProxyManagedVarHandleIterator pmvIterator = pmo.variableHandles();
	for ( pmvIterator.start(); !pmvIterator.off(); pmvIterator.forth() )
	{
		cout << "         found a variable of type   " << pmvIterator.item().typeString() << endl
		 	 << "                          with name " << pmvIterator.item().name() << endl;

		//clone this Proxy Manged Variable
		RTRProxyManagedVariablePtr pmvPtr = pmo.variableByName(pmvIterator.item().name());

		if (pmvPtr->error())
			return;
		
		//add to pmvList (so there will be no garabage collection with pmvPtr)
		addToList(pmvPtr);

		pmvPtr->addClient(*this);
        /* If the Variable is already inSync() then I will not receive
		 * the 'Sync' event, so I need to check it here.
	 	 */
		 if ( pmvPtr->inSync() == RTRTRUE )
		 {
			cout << "pmvPtr is inSync" << endl;
			processProxyManagedVariableSync(*pmvPtr);
		 }
		 else
		 {
			cout << "pmvPtr is not inSync" << endl;
	   	 }
	}
}

void Monitor::processProxyManagedObjectDeleted(
		const RTRProxyManagedObject& pmo
		)
{
	cout << "pmo event: Deleted" << endl;
}

void Monitor::processProxyManagedObjectInfo(
		const RTRProxyManagedObject& pmo
		)
{
	cout << "pmo event: Info   @" << pmo.text() << endl;
}

void Monitor::processProxyManagedObjectInService(
		const RTRProxyManagedObject& pmo
		)
{
	cout << "pmo event: InService" << endl;
}

void Monitor::processProxyManagedObjectRecovering(
		const RTRProxyManagedObject& pmo
		)
{
	cout << "pmo event: Recovering" << endl;
}

void Monitor::processProxyManagedObjectWaiting(
		const RTRProxyManagedObject& pmo
		)
{
	cout << "pmo event: Waiting" << endl;
}

void Monitor::processProxyManagedObjectDead(
		const RTRProxyManagedObject& pmo
		)
{
	cout << "pmo event: Dead" << endl;
}

void Monitor::processProxyManagedObjectChildAdded(
		const RTRProxyManagedObject& pmo,
		const RTRProxyManagedObjectHandle& pmoh
		)
{
	cout << "pmo event: ChildAdded" << endl;
}

void Monitor::processProxyManagedObjectChildRemoved(
		const RTRProxyManagedObject& pmo,
		const RTRProxyManagedObjectHandle& pmoh
		)
{
	cout << "pmo event: ChildRemoved" << endl;
}

void Monitor::processProxyManagedObjectVariableAdded(
		const RTRProxyManagedObject& pmo,
		const RTRProxyManagedVariableHandle& pmoh
		)
{
	cout << "pmo event: VariableAdded" << endl;
}

void Monitor::processProxyManagedObjectVariableRemoved(
		const RTRProxyManagedObject& pmo,
		const RTRProxyManagedVariableHandle& pmoh
		)
{
	cout << "pmo event: VariableRemoved" << endl;
}



//Event processing for RTRProxyManagedVariableClient
void Monitor::processProxyManagedVariableError(
		RTRProxyManagedVariable& pmv
		)
{
	cout << "pmv event: Error  @" << pmv.text() << endl;
}

void Monitor::processProxyManagedVariableSync(
		RTRProxyManagedVariable& pmv
		)
{
	cout << "pmv event: Sync" << endl;
	cout << "cloned mv information:   name        = " << pmv.name() << endl;
	cout << "                         type        = " << pmv.typeString() << endl;
	cout << "                         description = " << pmv.description() << endl;

	//show variable specific values
	showPMVdata(pmv);
}

void Monitor::processProxyManagedVariableUpdate(
		RTRProxyManagedVariable& pmv
		)
{
	cout << "pmv event: Update" << endl;

	cout << "new value of " << pmv.name()
	     << " (with instance Id " << pmv.context().instanceId() << ") is " 
	     << pmv.toString() << endl;
}

void Monitor::processProxyManagedVariableDeleted(
		RTRProxyManagedVariable& pmv
		)
{
	cout << "pmv event: Deleted" << endl;
	pmv.dropClient(*this);
}

// showPMVdata calls the specific variable member function, which
//                            shows some specific variable data
void Monitor::showPMVdata(
		RTRProxyManagedVariable& pmv
		)
{
	switch ( pmv.type() )
	{
		case RTRProxyManagedVariableHandle::Boolean:
			showBoolean_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::BooleanConfig:
			showBooleanConfig_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::Counter:
			showCounter_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::Numeric:
			showNumeric_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::LargeNumeric:
			showLargeNumeric_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::NumericConfig:
			showNumericConfig_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::NumericRange:
			showNumericRange_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::Gauge:
			showGauge_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::GaugeConfig:
			showGaugeConfig_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::String:
			showString_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::StringConfig:
			showStringConfig_data(pmv);
			break;

		case RTRProxyManagedVariableHandle::Invalid:
			cout << "Invalid Proxy Managed Variable" << endl;
			break;

		default:
			cout << "Unknown Proxy Managed Variable" << endl;
	}
}


void Monitor::showBoolean_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedBoolean& pmb = (RTRProxyManagedBoolean&)pmv;
	if ( pmb.value() == RTRTRUE )
		cout << "                         value       = RTRTRUE" << endl;
	else
		cout <<	"                         value       = RTRFALSE" << endl;
}

void Monitor::showBooleanConfig_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedBooleanConfig& pmbc = (RTRProxyManagedBooleanConfig&)pmv;
	if ( pmbc.activeValue() == RTRTRUE )
		cout << "                         active value = RTRTRUE" << endl;
	else
		cout <<	"                         active value = RTRFALSE" << endl;
	if ( pmbc.storeValue() == RTRTRUE )
		cout << "                         store value  = RTRTRUE" << endl;
	else
		cout <<	"                         store value  = RTRFALSE" << endl;
	if ( pmbc.factoryDefault() == RTRTRUE )
		cout << "                         factory default = RTRTRUE" << endl;
	else
		cout <<	"                         factory default = RTRFALSE" << endl;
}

void Monitor::showCounter_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedCounter& pmc = (RTRProxyManagedCounter&)pmv;
	unsigned long cnt = pmc.value();
	cout << "                         value       = " << cnt << endl;
}

void Monitor::showNumeric_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedNumeric& pmn = (RTRProxyManagedNumeric&)pmv;
	cout << "                         value       = " << pmn.value() << endl;
}

void Monitor::showLargeNumeric_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedLargeNumeric& pmln = (RTRProxyManagedLargeNumeric&)pmv;

	#if defined (_WIN32) || defined (_WIN64) 
		char buf[30];	//There is no operator << for __int64 type defined for the ostream class.
		sprintf(buf, "%I64d", pmln.value());
		cout << "                         value       = " << buf << endl;
	#else
		cout << "                         value       = " << pmln.value() << endl;
	#endif

}

void Monitor::showNumericConfig_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedNumericConfig& pmnc = (RTRProxyManagedNumericConfig&)pmv;
	cout << "                         active value = " << pmnc.activeValue() << endl
	<< "                         min value    = " << pmnc.minValue() << endl
	<< "                         max value    = " << pmnc.maxValue() << endl
	<< "                         store value  = " << pmnc.storeValue() << endl
	<< "                         factory default = " << pmnc.factoryDefault() << endl;
}

void Monitor::showNumericRange_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedNumericRange& pmnr = (RTRProxyManagedNumericRange&)pmv;
	cout << "                         min value   = " << pmnr.minValue() << endl
	<< "                         max value   = " << pmnr.maxValue() << endl;
}

void Monitor::showGauge_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedGauge& pmg = (RTRProxyManagedGauge&)pmv;
	cout << "                         min value   = " << pmg.minValue() << endl
	<< "                         max value   = " << pmg.maxValue() << endl
	<< "                         lowWaterMark  = " << pmg.lowWaterMark() << endl
	<< "                         highWaterMark = " << pmg.highWaterMark() << endl;
}

void Monitor::showGaugeConfig_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedGaugeConfig& pmgc = (RTRProxyManagedGaugeConfig&)pmv;
	cout << "                         min store value     = " << pmgc.minStoreValue() << endl
	<< "                         min factory default = " << pmgc.minFactoryDefault() << endl
	<< "                         max store value     = " << pmgc.maxStoreValue() << endl
	<< "                         max factory default = " << pmgc.maxFactoryDefault() << endl;
}

void Monitor::showString_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedString& pms = (RTRProxyManagedString&)pmv;
	cout << "                         value       = " << pms.value() << endl;
}

void Monitor::showStringConfig_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedStringConfig& pmsc = (RTRProxyManagedStringConfig&)pmv;
	RTRString active = pmsc.activeValue();
	cout << "                         active value = " << pmsc.activeValue() << endl;
	RTRString store = pmsc.storeValue();
	cout << "                         store value  = " << pmsc.storeValue() << endl;
	RTRString fDflt = pmsc.factoryDefault();
	cout << "                         factory default = " << pmsc.factoryDefault() << endl;
}


//create a linked list that contains
//all the proxy managed objects and their children
void Monitor::addToList( const RTRProxyManagedObjectPtr obj )
{
	RTRProxyManagedObjectPtr objPtr;
	RTRBOOL done = RTRFALSE;  //used to maintain correct managed object tree structure

	RTRProxyManagedObjectPtr *nPtr =  new RTRProxyManagedObjectPtr;
	*nPtr = obj;
	if ( _pmoList.empty() )
	{
		_pmoList.addRight( nPtr );
	}
	else
	{
		for ( _pmoList.start(); !_pmoList.off(); _pmoList.forth() )
		{
			objPtr = *(_pmoList.item());

			if ( obj->instanceId().parent() == objPtr->instanceId() )
			{
				_pmoList.addRight( nPtr );
				done = RTRTRUE;
				break;
			}
		}
		if ( !done )
		{
			_pmoList.start();
			_pmoList.addRight( nPtr );
		}
	}
}


//create a linked list that contains
//all the proxy managed variables
void Monitor::addToList( const RTRProxyManagedVariablePtr var )
{
	RTRProxyManagedVariablePtr   ptr;
	RTRBOOL variable_found = RTRFALSE;  //used to ensure that the variables
					    //added in the same order as we see them

	RTRProxyManagedVariablePtr *nPtr =  new RTRProxyManagedVariablePtr;
	*nPtr = var;

	if ( _pmvList.empty() )
	{
		_pmvList.addRight( nPtr );
	}
	else
	{
		for ( _pmvList.start(); !_pmvList.off(); _pmvList.forth() )
		{
			ptr = *(_pmvList.item());
		    if (ptr->error()) {
				if (ptr->hasClient(*this))
					ptr->dropClient(*this);
				_pmvList.remove();
				return;
			}
			
			if ( var->context().instanceId() == ptr->context().instanceId() )
				variable_found = RTRTRUE;
			
			if ( ( variable_found ) &&
			     (var->context().instanceId() != ptr->context().instanceId()) )
			{
				_pmvList.addLeft( nPtr );
				return;
			}
		}

		// New variable added to list
		_pmvList.extend( nPtr );
	}
}
