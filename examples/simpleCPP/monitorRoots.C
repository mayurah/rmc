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
#include <regex.h>
using namespace std;

#include "monitorRoots.h"
#include <unistd.h>

#define DBG(x) x

Monitor::Monitor( RTRProxyManagedObjectServerPool& p, char *szClassList )
	: _pmosp(p)
{
	setFilterList(szClassList);
	// Register with the Server Pool to receive events.
	_pmosp.addClient(*this);
	RTRLinkedListCursor<RTRProxyManagedObjectServer> iter = _pmosp.servers();
	int count = 0;
	for (iter.start(); !iter.off(); iter.forth()) {
		processProxyManagedObjectServerAdded(_pmosp, (RTRProxyManagedObjectServer&)*iter);
		count++;
	}
	this->varSyncedCnt = 0;
	this->objSyncedCnt = 0;
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
	// Register with each Server to receive events
	// processObjectServerSync will be called
	if(pmos.inSync() == RTRTRUE)
	{
		DBG(cout << "[INFO] [SERVER] server is inSync, " << pmos.text() << endl;)
		processObjectServerSync(pmos);
	}
	else
	{
		DBG(cout << "[INFO] [SERVER] server is not inSync " << pmos.text() << endl;)
	}
	pmos.addClient(*this);
}

void Monitor::processProxyManagedObjectServerRemoved(
		RTRProxyManagedObjectServerPool& pmosp,
		RTRProxyManagedObjectServer& pmos
		)
{
	DBG(cout << "pmosp event: Removed a pmos  @" << pmos.text() << endl;)
	// I know that I'm a client (since I received this event)
	// so be sure to drop client when the Server is no longer valid.
	pmos.dropClient(*this);
}


//event processing for RTRProxyManagedObjectServerClient
void Monitor::processObjectServerError(
		RTRProxyManagedObjectServer& pmos
		)
{
	DBG(cout << "pmos event: Error  @" << pmos.text() << endl;)
	// Drop client since this Server is no longer valid.
	pmos.dropClient(*this);
}

void Monitor::processObjectServerSync(
		RTRProxyManagedObjectServer& pmos
		)
{
	DBG(cout << "[INFO] [SERVER] [CALLBACK] " << pmos.text() << endl;)
	// Now that the Server is in Sync I can
	// iterate through all Root Proxy Managed Objects in pmos
	// for each root Proxy Managed Object I will become its client.
	RTRProxyManagedObjectHandleIterator pmosIterator = pmos.roots();
	for ( pmosIterator.start(); !pmosIterator.off(); pmosIterator.forth() )
	{
		//now clone the current Proxy Managed Object
		RTRProxyManagedObjectPtr pmoPtr = pmos.object(pmosIterator.item());
		addToList(pmoPtr);
		pmoPtr->addClient(*this);
		// doLoopObjectList(&pmos);
	}
}

// bool Monitor::hasAnyChildInObjectList()
// {
// 	RTRProxyManagedObjectPtr objPtr;

// 	if ( !_pmoList.empty() )
// 	{
// 		for ( _pmoList.start(); !_pmoList.off(); _pmoList.forth() )
// 		{
// 			objPtr = *(_pmoList.item());
// 			RTRProxyManagedObjectHandleIterator pchildIterator = objPtr->childHandles();
// 			if (pchildIterator.count())
// 			{
// 				return true;
// 			}
// 		}
// 	}
// 	return false;
// }

// void Monitor::clearCheckList()
// {
// 	_pmoRegisteredCheckedList.deleteContents();
// }
// bool Monitor::isCheckListEmpty()
// {
// 	if (_pmoRegisteredCheckedList.count())
// 	{
// 		return false;
// 	}

// 	return true;
// }

bool Monitor::doRegularExpression(const char *szReg, const char *szTxt)
{
	int rc = 0;
	regex_t reegex;

	rc = regcomp( &reegex, szReg, 0);
	rc = regexec( &reegex, szTxt, 0, NULL, 0);

	if (rc == 0)
		return true;

	return false;
}

// bool Monitor::isParent(RTRString strChild,RTRString strParent)
// {
// 	return strChild.contains(strParent);
// }

// bool Monitor::isParentInFilterList(RTRString objParent)
// {
// 	if ( !_pmoFilterList.empty() )
// 	{
// 		for ( _pmoFilterList.start(); !_pmoFilterList.off(); _pmoFilterList.forth() )
// 		{
// 			RTRString objItem = *(_pmoFilterList.item());
// 			if (objItem.contains(objParent))
// 			{
// 				return true;
// 			}
// 		}
// 	}

// 	return false;
// }

bool Monitor::isInFilterList(RTRString objName)
{
	if ( !_pmoFilterList.empty() )
	{
		for ( _pmoFilterList.start(); !_pmoFilterList.off(); _pmoFilterList.forth() )
		{
			RTRString objItem = *(_pmoFilterList.item());
			if (doRegularExpression(objItem.to_c(), objName.to_c()))
			{
				return true;
			}
		}
	}

	return false;
}

void Monitor::addToFilterList(char *szClass)
{
	if (szClass != NULL)
	{
		RTRString string = szClass;
		RTRString *nPtr =  new RTRString;
		*nPtr = string;
		_pmoFilterList.start();
		_pmoFilterList.addRight( nPtr );
	}
}

// void Monitor::showFilterList()
// {
// 	if ( !_pmoFilterList.empty() )
// 	{
// 		DBG(cout << "### printing filter list" << endl;)
// 		for ( _pmoFilterList.start(); !_pmoFilterList.off(); _pmoFilterList.forth() )
// 		{
// 			RTRString objItem = *(_pmoFilterList.item());
// 			DBG(cout << "\"" << objItem << "\", " << endl;)
// 		}
// 	}
// }

void Monitor::removeChar(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

bool Monitor::setFilterList(char *szInput)
{
	if (strlen(szInput))
	{
		FILE *f;
		f = fopen(szInput, "r");
		if (f)
		{
			char line[1024];
			DBG(cout << "### setup filter from file" << endl;)
			while (fgets(line, sizeof(line), f)) {
				removeChar(line, '\r');
				removeChar(line, '\n');
				removeChar(line, ' ');
				removeChar(line, ',');
				removeChar(line, '"');
				addToFilterList(line);
			}
			fclose(f);
		}
		else
		{
			DBG(cout << "### setup filter from given string" << endl;)
			char delim[] = ",";
			char *token;
			token = strtok(szInput, delim);

			while(token != NULL) 
			{
				DBG(cout << token << endl;)
				addToFilterList(token);
				token = strtok(NULL, delim);
			}
		}
		_isApplyFilter = true;
	}
	else
	{
		_isApplyFilter = false;
	}
}

// bool Monitor::isInCheckList(RTRString objName)
// {
// 	if ( !_pmoRegisteredCheckedList.empty() )
// 	{
// 		for ( _pmoRegisteredCheckedList.start(); !_pmoRegisteredCheckedList.off(); _pmoRegisteredCheckedList.forth() )
// 		{
// 			RTRString objItem = *(_pmoRegisteredCheckedList.item());
			
// 			if (objName.isEqual(objItem) && !objName.isEmpty() && !objItem.isEmpty())
// 			{
// 				return true;
// 			}
// 		}
// 	}

// 	return false;
// }

// void Monitor::addToCheckList(RTRString objName)
// {
// 	RTRString *nPtr =  new RTRString;
// 	*nPtr = objName;

// 	_pmoRegisteredCheckedList.start();
// 	_pmoRegisteredCheckedList.addRight( nPtr );
// }

// bool Monitor::hasObjectInList(RTRString objName)
// {	
// 	RTRProxyManagedObjectPtr objPtr;

// 	if ( !_pmoList.empty() )
// 	{
// 		for ( _pmoList.start(); !_pmoList.off(); _pmoList.forth() )
// 		{
// 			objPtr = *(_pmoList.item());
// 			RTRString itemName = objPtr->name();
// 			if (objName.isEqual(itemName))
// 			{
// 				return true;
// 			}
// 		}
// 	}
// 	return false;
// }

// void Monitor::registerChilds(RTRProxyManagedObjectServer *pmosPtr)
// {
// 	RTRLinkedList<RTRProxyManagedObjectPtr> tmpList = _pmoList;
// 	if ( !tmpList.empty() )
// 	{
// 		for ( tmpList.start(); !tmpList.off(); tmpList.forth() )
// 		{
// 			RTRProxyManagedObjectPtr parentPtr = *(tmpList.item());
// 			if (!isInCheckList(parentPtr->instanceId().string()))
// 			{
// 				// add to check list
// 				addToCheckList(parentPtr->instanceId().string());
// 				// register parent
// 				addToList(parentPtr);
// 				if (parentPtr->inSync() != RTRTRUE)
// 				{
// 					DBG(cout << "[### WARN] parent(" << parentPtr->instanceId().string() << ") is not synced" << endl;)
// 				}
// 				else
// 				{
// 					DBG(cout << "[### INFO] parent(" << parentPtr->instanceId().string() << ") is synced" << endl;)
// 				}
// 				// get all childs
// 				RTRProxyManagedObjectHandleIterator pchildIterator = parentPtr->childHandles();
// 				if (pchildIterator.count())
// 				{
// 					DBG(cout << "[INFO] " << parentPtr->name() << " has " << pchildIterator.count() << " childs" << endl;)
// 					for ( pchildIterator.start(); !pchildIterator.off(); pchildIterator.forth() )
// 					{
// 						// RTRProxyManagedObjectPtr childPtr = parentPtr->childByName(pchildIterator.item().name());
// 						RTRProxyManagedObjectPtr childPtr = pmosPtr->object(pchildIterator.item());
// 						if (childPtr != NULL)
// 						{
// 							if (!hasObjectInList(childPtr->instanceId().string()))
// 							{								
// 								DBG(cout << "###N> add " << childPtr->instanceId() << " to list" << endl;)
// 								addToList(childPtr);
// 							}
// 						}
// 						else
// 							DBG(cout << "###N> add " << childPtr->instanceId() << " return NULL" << endl);
// 					}
// 				}
// 				else
// 				{
// 					DBG(cout << "<<< " << parentPtr->instanceId().string() << " has no childs" << endl);
// 				}
// 			}
// 		}
// 	}	
// }

// void Monitor::doLoopObjectList(RTRProxyManagedObjectServer *pmos)
// {
// 	_lastClassCount = 0;
// 	_isObjectLoopFinished = false;
// 	varSyncedCnt = 0;

// 	while (hasAnyChildInObjectList() && !_isObjectLoopFinished)
// 	{
// 		DBG(cout << "//////////////////////////////////////////" << endl;)
// 		DBG(cout << "///// start new check session" << endl;)
// 		registerChilds(pmos);
// 		checkLoopEnd();
// 		DBG(cout << "///// Terminating session" << endl;)
// 		DBG(cout << "//////////////////////////////////////////" << endl;)
// 		DBG(cout << endl;)
// 		DBG(cout << endl;)
// 		DBG(cout << endl;)
// 	}

// 	printObjectListInfo();

// 	if (_isApplyFilter)
// 	{
// 		DBG(cout << "//////////////////////////////////////////" << endl;)
// 		DBG(cout << "///// Start output data (Apply filter)" << endl;)
// 		showFilterList();
// 		DBG(cout << endl;)
// 	}
// 	else
// 	{
// 		DBG(cout << "//////////////////////////////////////////" << endl;)
// 		DBG(cout << "///// Start output data (no filter, print all instances)" << endl;)
// 	}

	
// 	RTRProxyManagedObjectPtr objPtr;
// 	if ( !_pmoList.empty() )
// 	{
// 		int iFound = 0;
// 		for ( _pmoList.start(); !_pmoList.off(); _pmoList.forth() )
// 		{
// 			objPtr = *(_pmoList.item());
// 			if (_isApplyFilter)
// 			{
// 				if (isInFilterList(objPtr->instanceId().string()))
// 				{
// 					DBG(cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;)
// 					DBG(cout << "!!!!! Found " << objPtr->instanceId().string() << " in filter list" << endl;)
// 					objPtr->addClient( (RTRProxyManagedObjectClient &) *this );
// 					// start wait for callback funtion processProxyManagedObjectSync()
// 					iFound++;
// 				}
// 			}
// 			else
// 			{
// 				objPtr->addClient( (RTRProxyManagedObjectClient &) *this );
// 				// start wait for callback funtion processProxyManagedObjectSync()
// 				iFound++;
// 			}
// 		}

// 		if (iFound == 0) {
// 			DBG(cout << "Not found any matched instanceId in filater list" << endl;)
// 			exit(1);
// 		}

// 		DBG(cout << endl;)
// 	}
// }

// void Monitor::checkLoopEnd()
// {
// 	RTRProxyManagedObjectPtr objPtr;
// 	if ( !_pmoList.empty() )
// 	{
// 		if (_lastClassCount != _pmoList.count())
// 		{
// 			_lastClassCount = _pmoList.count();
// 			DBG(cout << endl;)
// 		}
// 		else
// 		{
// 			DBG(cout << "### No more child " << endl;)
// 			_isObjectLoopFinished = true;
// 		}
// 	}
// }
// #define PRINT_SEPERATE 0
// void Monitor::printObjectListInfo()
// {
// 	RTRProxyManagedObjectPtr objPtr;
// 	if ( !_pmoList.empty() )
// 	{
// 		DBG(cout << "### " << _lastClassCount << " classes in list: ";)
// #if PRINT_SEPERATE		
// 		cout << "*** Instance Id List" << endl;
// 		for ( _pmoList.start(); !_pmoList.off(); _pmoList.forth() )
// 		{
// 			objPtr = *(_pmoList.item());			
// 			cout << "\"" << objPtr->instanceId() << "\", " << endl;
// 		}
// 		cout << "*** Name List" << endl;
// 		for ( _pmoList.start(); !_pmoList.off(); _pmoList.forth() )
// 		{
// 			objPtr = *(_pmoList.item());			
// 			cout << "\"" << objPtr->name() << "\", " << endl;
// 		}
// 		cout << "*** Class Id List" << endl;
// 		for ( _pmoList.start(); !_pmoList.off(); _pmoList.forth() )
// 		{
// 			objPtr = *(_pmoList.item());			
// 			cout << "\"" << objPtr->classId() << "\", " << endl;
// 		}
// #else
// 		DBG(cout << "*** Instance List" << endl;)
// 		for ( _pmoList.start(); !_pmoList.off(); _pmoList.forth() )
// 		{
// 			objPtr = *(_pmoList.item());			
// 			DBG(cout << "\"" << objPtr->instanceId() << "\", ";)
// 			DBG(cout << "\"" << objPtr->name() << "\", ";)
// 			DBG(cout << "\"" << objPtr->classId() << "\", " << endl;)
// 		}
// #endif
// 		DBG(cout << endl;)
// 	}
// }

void Monitor::processObjectServerRootAdded(
		RTRProxyManagedObjectServer& pmos,
		const RTRProxyManagedObjectHandle& pmoH
		)
{
	DBG(cout <<"pmos event: Added a root on pmos  @" << pmos.text() << endl;)

	//now clone the current Proxy Managed Object
	RTRProxyManagedObjectPtr pmoPtr = pmos.object(pmoH);

	// Maintain a smart pointer reference to the Proxy Managed Object
	// or else the object will be garbage collected.
	addToList(pmoPtr);

	pmoPtr->addClient( (RTRProxyManagedObjectClient &) *this );
	// wait for the callback function processProxyManagedObjectSync()		
}

void Monitor::processObjectServerRootRemoved(
		RTRProxyManagedObjectServer& pmos,
		const RTRProxyManagedObjectHandle& pmoh
		)
{
	DBG(cout <<"pmos event: Removed a root from pmos  @" << pmos.text() << endl;)
}


//
// Event processing for RTRProxyManagedObjectClient
//
void Monitor::processProxyManagedObjectError(
		const RTRProxyManagedObject& pmo
		)
{
	DBG(cout << "pmo event: Error  @" << pmo.text() << endl;)
}

void Monitor::processProxyManagedObjectSync(
	const RTRProxyManagedObject& pmo
	)
{
	DBG(cout << "[INFO] [OBJECT] [CALLBACK] " << pmo.instanceId().string() << " is synced" << endl;)
	// check if the object is the parent of given class
	// if no should not register its children, if yes register all its child but not variables
	// if (isParentInFilterList(pmo.instanceId().string()))
	{
		DBG(cout << "[INFO] [OBJECT] [CALLBACK] object(" << pmo.instanceId().string() << ") need to be synced as parent" << endl;)
		RTRProxyManagedObjectHandleIterator pchildIterator = pmo.childHandles();
		if (pchildIterator.count())
		{
			DBG(cout << "[INFO] [OBJECT] [CALLBACK] " << pmo.instanceId().string() << " has " << pchildIterator.count() << " childs" << endl;)
			for ( pchildIterator.start(); !pchildIterator.off(); pchildIterator.forth() )
			{
				RTRProxyManagedObjectPtr childPtr = pmo.childByName(pchildIterator.item().name());
				DBG(
					char strLeft[64];
					char strCenter[64];
					char strRight[64];
					sprintf(strLeft, "(%s)", pmo.instanceId().string().to_c());
					sprintf(strCenter, "(%s)", pchildIterator.item().name().to_c());
					sprintf(strRight, "(%s)", childPtr->instanceId().string().to_c());
					cout.width(50);
					cout << left << strLeft;
					cout.width(50);
					cout << left << strCenter;
					cout.width(50);
					cout << left << strRight;
					cout << endl;
				)

				childPtr->addClient(*this);
				addToList(childPtr);
			}
		}
	}
	
	if (isInFilterList(pmo.instanceId().string()))
	{
		//iterate through all Proxy Managed Variables
		RTRProxyManagedVarHandleIterator pmvIterator = pmo.variableHandles();
		for ( pmvIterator.start(); !pmvIterator.off(); pmvIterator.forth() )
		{
			//clone this Proxy Manged Variable
			RTRProxyManagedVariablePtr pmvPtr = pmo.variableByName(pmvIterator.item().name());

			if (pmvPtr->error())
				return;
			
			//add to pmvList (so there will be no garabage collection with pmvPtr)
			addToList(pmvPtr);			

			pmvPtr->addClient(*this);
		}		
	}
}

void Monitor::processProxyManagedObjectDeleted(
		const RTRProxyManagedObject& pmo
		)
{
	DBG(cout << "pmo event: Deleted" << endl;)
}

void Monitor::processProxyManagedObjectInfo(
		const RTRProxyManagedObject& pmo
		)
{
	DBG(cout << "pmo event: Info   @" << pmo.text() << endl;)
}

void Monitor::processProxyManagedObjectInService(
		const RTRProxyManagedObject& pmo
		)
{
	DBG(cout << "pmo event: InService" << endl;)
}

void Monitor::processProxyManagedObjectRecovering(
		const RTRProxyManagedObject& pmo
		)
{
	DBG(cout << "pmo event: Recovering" << endl;)
}

void Monitor::processProxyManagedObjectWaiting(
		const RTRProxyManagedObject& pmo
		)
{
	DBG(cout << "pmo event: Waiting" << endl;)
}

void Monitor::processProxyManagedObjectDead(
		const RTRProxyManagedObject& pmo
		)
{
	DBG(cout << "pmo event: Dead" << endl;)
}

void Monitor::processProxyManagedObjectChildAdded(
		const RTRProxyManagedObject& pmo,
		const RTRProxyManagedObjectHandle& pmoh
		)
{
	DBG(cout << "pmo event: ChildAdded" << endl;)

	// DBG(cout << "[INFO] [OBJECT] [CALLBACK] " << pmo.instanceId().string() << " is synced" << endl;)
	// check if the object is the parent of given class
	// if no should not register its children, if yes register all its child but not variables
	// if (isParentInFilterList(pmo.instanceId().string()))
	{
		DBG(cout << "[INFO] [OBJECT] [CALLBACK] object(" << pmo.instanceId().string() << ") need to be synced as parent" << endl;)
		RTRProxyManagedObjectHandleIterator pchildIterator = pmo.childHandles();
		if (pchildIterator.count())
		{
			DBG(cout << "[INFO] [OBJECT] [CALLBACK] " << pmo.instanceId().string() << " has " << pchildIterator.count() << " childs" << endl;)
			for ( pchildIterator.start(); !pchildIterator.off(); pchildIterator.forth() )
			{
				RTRProxyManagedObjectPtr childPtr = pmo.childByName(pchildIterator.item().name());
				DBG(
					char strLeft[64];
					char strCenter[64];
					char strRight[64];
					sprintf(strLeft, "(%s)", pmo.instanceId().string().to_c());
					sprintf(strCenter, "(%s)", pchildIterator.item().name().to_c());
					sprintf(strRight, "(%s)", childPtr->instanceId().string().to_c());
					cout.width(50);
					cout << left << strLeft;
					cout.width(50);
					cout << left << strCenter;
					cout.width(50);
					cout << left << strRight;
					cout << endl;
				)

				childPtr->addClient(*this);
				addToList(childPtr);
			}
		}
	}
	
	if (isInFilterList(pmo.instanceId().string()))
	{
		//iterate through all Proxy Managed Variables
		RTRProxyManagedVarHandleIterator pmvIterator = pmo.variableHandles();
		for ( pmvIterator.start(); !pmvIterator.off(); pmvIterator.forth() )
		{
			//clone this Proxy Manged Variable
			RTRProxyManagedVariablePtr pmvPtr = pmo.variableByName(pmvIterator.item().name());

			if (pmvPtr->error())
				return;
			
			//add to pmvList (so there will be no garabage collection with pmvPtr)
			addToList(pmvPtr);			

			pmvPtr->addClient(*this);
		}		
	}


}

void Monitor::processProxyManagedObjectChildRemoved(
		const RTRProxyManagedObject& pmo,
		const RTRProxyManagedObjectHandle& pmoh
		)
{
	DBG(cout << "pmo event: ChildRemoved" << endl;)
}

void Monitor::processProxyManagedObjectVariableAdded(
		const RTRProxyManagedObject& pmo,
		const RTRProxyManagedVariableHandle& pmoh
		)
{
	DBG(cout << "pmo event: VariableAdded" << endl;)
}

void Monitor::processProxyManagedObjectVariableRemoved(
		const RTRProxyManagedObject& pmo,
		const RTRProxyManagedVariableHandle& pmoh
		)
{
	DBG(cout << "pmo event: VariableRemoved" << endl;)
}



//Event processing for RTRProxyManagedVariableClient
void Monitor::processProxyManagedVariableError(
		RTRProxyManagedVariable& pmv
		)
{
	DBG(cout << "pmv event: Error  @" << pmv.text() << endl;)
}

void Monitor::processProxyManagedVariableSync(
		RTRProxyManagedVariable& pmv
		)
{
	cout << "{" << endl;
	cout << "    \"instanceId\" : " << "\"" << pmv.context().instanceId().string() << "\"," << endl;
	cout << "    \"name\" : " << "\"" << pmv.name() << "\"," << endl;
	cout << "    \"type\" : " << "\"" << pmv.typeString() << "\"," << endl;
	cout << "    \"description\" : " << "\"" << pmv.description() << "\"," << endl;		

	//show variable specific values
	showPMVdata(pmv);
	cout << "}," << endl;
	
	// check if it finished sync
	varSyncedCnt++;
	if (varSyncedCnt >= _pmvList.count())
	{
		exit(1);
	}
	// cout << "var synced count :" << varSyncedCnt << "(" << _pmvList.count() << ")" << endl;	
}

void Monitor::processProxyManagedVariableUpdate(
		RTRProxyManagedVariable& pmv
		)
{
	DBG(cout << "pmv event: Update" << endl;)

	DBG(cout << "new value of " << pmv.name()
	     << " (with instance Id " << pmv.context().instanceId() << ") is " 
	     << pmv.toString() << endl;)
}

void Monitor::processProxyManagedVariableDeleted(
		RTRProxyManagedVariable& pmv
		)
{
	DBG(cout << "pmv event: Deleted" << endl;)
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
			DBG(cout << "Invalid Proxy Managed Variable" << endl;)
			break;

		default:
			DBG(cout << "Unknown Proxy Managed Variable" << endl);
	}
}


void Monitor::showBoolean_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedBoolean& pmb = (RTRProxyManagedBoolean&)pmv;
	if ( pmb.value() == RTRTRUE )
		cout << "    \"value\" : \"RTRTRUE\"," << endl;
	else
		cout <<	"    \"value\" : \"RTRFALSE\"," << endl;

}

void Monitor::showBooleanConfig_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedBooleanConfig& pmbc = (RTRProxyManagedBooleanConfig&)pmv;
	if ( pmbc.activeValue() == RTRTRUE )
		cout << "    \"active_value\" : \"RTRTRUE\"," << endl;
	else
		cout << "    \"active_value\" : \"RTRFALSE\"," << endl;
	if ( pmbc.storeValue() == RTRTRUE )
		cout << "    \"store_value\" : \"RTRTRUE\"," << endl;
	else
		cout << "    \"store_value\" : \"RTRFALSE\"," << endl;
	if ( pmbc.factoryDefault() == RTRTRUE )
		cout << "    \"factory_default\" : \"RTRTRUE\"," << endl;
	else
		cout << "    \"factory_default\" : \"RTRFALSE\"," << endl;
}

void Monitor::showCounter_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedCounter& pmc = (RTRProxyManagedCounter&)pmv;
	unsigned long cnt = pmc.value();
	cout << "    \"value\" : \"" << cnt << "\"," << endl;
}

void Monitor::showNumeric_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedNumeric& pmn = (RTRProxyManagedNumeric&)pmv;
	cout << "    \"value\" : \"" << pmn.value() << "\"," << endl;
}

void Monitor::showLargeNumeric_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedLargeNumeric& pmln = (RTRProxyManagedLargeNumeric&)pmv;

	#if defined (_WIN32) || defined (_WIN64) 
		char buf[30];	//There is no operator << for __int64 type defined for the ostream class.
		sprintf(buf, "%I64d", pmln.value());
		cout << "    \"value\" : \"" << buf << "\"" << endl;
	#else
		cout << "    \"value\" : \"" << pmln.value() << "\"," << endl;
	#endif

}

void Monitor::showNumericConfig_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedNumericConfig& pmnc = (RTRProxyManagedNumericConfig&)pmv;
	cout << "    \"active_value\" : \"" << pmnc.activeValue() << "\"," << endl;
	cout << "    \"min_value\" : \"" << pmnc.minValue() << "\"," << endl;
	cout << "    \"max_value\" : \"" << pmnc.maxValue() << "\"," << endl;
	cout << "    \"store_value\" : \"" << pmnc.storeValue() << "\"," << endl;
	cout << "    \"factory_default\" : \"" << pmnc.factoryDefault() << "\"," << endl;
}

void Monitor::showNumericRange_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedNumericRange& pmnr = (RTRProxyManagedNumericRange&)pmv;
	cout << "    \"min_value\" : \"" << pmnr.minValue() << "\"," << endl;
	cout << "    \"max_value\" : \"" << pmnr.maxValue() << "\"," << endl;
}

void Monitor::showGauge_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedGauge& pmg = (RTRProxyManagedGauge&)pmv;
	cout << "    \"min_value\" : \"" << pmg.minValue() << "\"," << endl;
	cout << "    \"max_value\" : \"" << pmg.maxValue() << "\"," << endl;
	cout << "    \"low_water_mark\" : \"" << pmg.lowWaterMark() << "\"," << endl;
	cout << "    \"high_water_mark\" : \"" << pmg.highWaterMark() << "\"," << endl;
	cout << "    \"value\" : \"" << pmg.value() << "\"," << endl;
}

void Monitor::showGaugeConfig_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedGaugeConfig& pmgc = (RTRProxyManagedGaugeConfig&)pmv;
	cout << "    \"min_store_value\" : \"" << pmgc.minStoreValue() << "\"," << endl;
	cout << "    \"min_factory_default\" : \"" << pmgc.minFactoryDefault() << "\"," << endl;
	cout << "    \"max_store_value\" : \"" << pmgc.maxStoreValue() << "\"," << endl;
	cout << "    \"max_factore_default\" : \"" << pmgc.maxFactoryDefault() << "\"," << endl;
}

void Monitor::showString_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedString& pms = (RTRProxyManagedString&)pmv;
	cout << "    \"value\" : \"" << pms.value() << "\"," << endl;
}

void Monitor::showStringConfig_data(RTRProxyManagedVariable& pmv)
{
	RTRProxyManagedStringConfig& pmsc = (RTRProxyManagedStringConfig&)pmv;
	RTRString active = pmsc.activeValue();
	cout << "    \"active_value\" : \"" << pmsc.activeValue() << "\"," << endl;
	RTRString store = pmsc.storeValue();
	cout << "    \"store_value\" : \"" << pmsc.storeValue() << "\"," << endl;
	RTRString fDflt = pmsc.factoryDefault();
	cout << "    \"factory_default\" : \"" << pmsc.factoryDefault() << "\"," << endl;
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
