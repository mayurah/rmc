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

#ifndef _monitorRoots_h
#define _monitorRoots_h

#include "rtr/pmosp.h"		// RTRProxyManagedObjectServerPool
#include "rtr/pmospc.h"		// RTRProxyManagedObjectServerPoolClient
#include "rtr/prxymos.h"	// RTRProxyManagedObjectServer
#include "rtr/pmosc.h"		// RTRProxyManagedObjectServerClient
#include "rtr/proxymo.h"	// RTRProxyManagedObject and all Variables

/* This is a simple class which monitors (by becoming a client)
 * all of the root Managed Objects and their Managed Variables.
 * More complex examples may prefer to have separate classes
 * for each type of client and separate instances of those
 * classes for each Managed Object/Managed Variable.
 */
class Monitor :
	public RTRProxyManagedObjectServerPoolClient,
	public RTRProxyManagedObjectServerClient,
        public RTRProxyManagedObjectClient,
        public RTRProxyManagedVariableClient
{
public:
// Constructor
        Monitor(RTRProxyManagedObjectServerPool& p, char *szClassList);

// Destructor
	~Monitor();


// Event processing -- RTRProxyManagedObjectServerPoolClient
	// The events generated by a RTRProxyManagedObjectServerPool
	void processProxyManagedObjectServerAdded(
			RTRProxyManagedObjectServerPool& pmosp,
	                RTRProxyManagedObjectServer& pmos);
	void processProxyManagedObjectServerRemoved(
			RTRProxyManagedObjectServerPool& pmosp,
	                RTRProxyManagedObjectServer& pmos);

// Event processing -- RTRProxyManagedObjectServerClient
	// The events generated by a RTRProxyManagedObjectServer
	void processObjectServerError(
			RTRProxyManagedObjectServer& pmos);
	void processObjectServerSync(
			RTRProxyManagedObjectServer& pmos);
	void processObjectServerRootAdded(
			RTRProxyManagedObjectServer& pmos,
	                const RTRProxyManagedObjectHandle& pmoh);
	void processObjectServerRootRemoved(
			RTRProxyManagedObjectServer& pmos,
	                const RTRProxyManagedObjectHandle& pmoh);

// Event processing -- RTRProxyManagedObjectClient
	// The events generated by a RTRProxyManagedObject
        void processProxyManagedObjectError(
			const RTRProxyManagedObject& pmo);
        void processProxyManagedObjectSync(
			const RTRProxyManagedObject& pmo);
        void processProxyManagedObjectDeleted(
			const RTRProxyManagedObject& pmo);
        void processProxyManagedObjectInfo(
			const RTRProxyManagedObject& pmo);
        void processProxyManagedObjectInService(
			const RTRProxyManagedObject& pmo);
        void processProxyManagedObjectRecovering(
			const RTRProxyManagedObject& pmo);
        void processProxyManagedObjectWaiting(
			const RTRProxyManagedObject& pmo);
        void processProxyManagedObjectDead(
			const RTRProxyManagedObject& pmo);
        void processProxyManagedObjectChildAdded(
			const RTRProxyManagedObject& pmo,
                        const RTRProxyManagedObjectHandle& pmoh);
        void processProxyManagedObjectChildRemoved(
			const RTRProxyManagedObject& pmo,
                        const RTRProxyManagedObjectHandle& pmoh);
        void processProxyManagedObjectVariableAdded(
			const RTRProxyManagedObject& pmo,
                        const RTRProxyManagedVariableHandle& pmoh);
        void processProxyManagedObjectVariableRemoved(
			const RTRProxyManagedObject& pmo,
                        const RTRProxyManagedVariableHandle& pmoh);


// Event processing -- RTRProxyManagedVariableClient
	// The events generated by a RTRProxyManagedVariable
        void processProxyManagedVariableError(RTRProxyManagedVariable& pmv);
		void processProxyManagedVariableSync(RTRProxyManagedVariable& pmv);
        void processProxyManagedVariableUpdate(RTRProxyManagedVariable& pmv);
        void processProxyManagedVariableDeleted(RTRProxyManagedVariable& pmv);

private:
// Custom added functions
		bool _isApplyFilter;
		// do loop in root and find all sub childs and add to instance list
		void doLoopObjectList(RTRProxyManagedObjectServer *pmosPtr);
		void registerChilds(RTRProxyManagedObjectServer *pmosPtr);
		bool hasAnyChildInObjectList();
		bool hasObjectInList(RTRString name);

		// check list is to store the parent items that already processed
		RTRLinkedList<RTRString> _pmoRegisteredCheckedList;
		bool isInCheckList(RTRString objName);
		void addToCheckList(RTRString objName);
		void clearCheckList();
		bool isCheckListEmpty();

		// Filter related functions
		RTRLinkedList<RTRString> _pmoFilterList;
		void showFilterList();
		bool isInFilterList(RTRString objName);
		bool setFilterList(char *szInput);
		void addToFilterList(char *szString);
		bool doRegularExpression(const char *szIn, const char *szRef);
		bool isParent(RTRString strChild,RTRString strParent);
		bool isParentInFilterList(RTRString objName);


		// some helper functions and vars
		bool _isObjectLoopFinished;
		int _lastClassCount;
		void printObjectListInfo();
		void checkLoopEnd();
		void removeChar(char* str, char c);

		// for terminate
		int objSyncedCnt;
		int varSyncedCnt;
		

// Utilities
        void showPMVdata(RTRProxyManagedVariable& pmv);

        void showBoolean_data(RTRProxyManagedVariable& pmv);
        void showBooleanConfig_data(RTRProxyManagedVariable& pmv);
        void showCounter_data(RTRProxyManagedVariable& pmv);
        void showNumeric_data(RTRProxyManagedVariable& pmv);
        void showLargeNumeric_data(RTRProxyManagedVariable& pmv);	
        void showNumericConfig_data(RTRProxyManagedVariable& pmv);
        void showNumericRange_data(RTRProxyManagedVariable& pmv);
        void showGauge_data(RTRProxyManagedVariable& pmv);
        void showGaugeConfig_data(RTRProxyManagedVariable& pmv);
        void showString_data(RTRProxyManagedVariable& pmv);
        void showStringConfig_data(RTRProxyManagedVariable& pmv);

	void addToList( const RTRProxyManagedObjectPtr obj );
	void addToList( const RTRProxyManagedVariablePtr var );

// Data
        RTRProxyManagedObjectServerPool& _pmosp;
	// Maintain a reference (Smart pointer) to all of the
	// root managed objects and managed variables so that
	// they will not be deleted (garbage collected).
	RTRLinkedList<RTRProxyManagedObjectPtr> _pmoList;
	RTRLinkedList<RTRProxyManagedVariablePtr> _pmvList;

};

#endif

