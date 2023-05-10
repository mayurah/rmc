//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Apr. 05 1995"
// Version: 1.0

#ifdef hp
#undef RTDEBUG	/* work around HP oc-ao compiler bug */
#undef RTPRECONDITION
#undef RTPOSTCONDITION
#undef RTR_GLOBAL_DEFS
#include "rtr/rtrdefs.h"
#endif
#include "rtr/dir.h"

#ifndef _RDEV_NO_STL_
using namespace std;
#endif

//
//RTRClassCategory
//

template <class T>
RTRClassCategory<T>::RTRClassCategory(const RTRObjectId& cc)
	: _classId(cc)
{
	RTPOSTCONDITION ( cc == categoryClass() );
}

template <class T>
RTRClassCategory<T>::~RTRClassCategory()
{
}

template <class T>
const RTRObjectId& RTRClassCategory<T>::categoryClass() const
{
	return _classId;
}

template <class T>
int RTRClassCategory<T>::count() const
{
	RTRLinkedList<T>& l = 
			(RTRLinkedList<T>&)_contents;

	return l.count();
}

template <class T>
RTRBOOL RTRClassCategory<T>::has(const RTRObjectId& id) const
{
	RTRLinkedList<T>& l = 
			(RTRLinkedList<T>&)_contents;

	for (l.start(); 
			!l.off() && !(id == l.item()->instanceId()); 
				l.forth())
		;
	return l.off() ? RTRFALSE : RTRTRUE;
}

template <class T>
T *RTRClassCategory<T>::instance(const RTRObjectId& id) const
{
	RTRLinkedList<T>& l = 
			(RTRLinkedList<T>&)_contents;

	for (l.start(); 
			!l.off() && !(id == l.item()->instanceId()); 
				l.forth())
		;
	T *result =  l.off() ? 0 : l.item();

	RTPOSTCONDITION ( result ? has(id) : !has(id));
	RTPOSTCONDITION ( !result || result->instanceId() == id );

	return result;
}

template <class T>
void RTRClassCategory<T>::put(T& inst)
{
	RTPRECONDITION ( !has(inst.instanceId()) );
	RTPRECONDITION ( inst.classId().conformsTo(categoryClass()) );

	_contents.finish();
	_contents.addRight(&inst);

	RTPOSTCONDITION ( has(inst.instanceId()) );
	RTPOSTCONDITION ( instance(inst.instanceId()) == &inst );
}

template <class T>
void RTRClassCategory<T>::remove(T& inst)
{
	RTRLinkedList<T>& l = (RTRLinkedList<T>&)_contents;

	for (l.start(); !l.off() && !(&inst == l.item()); l.forth())
		;
	if (!_contents.off())
		_contents.remove();

	RTPOSTCONDITION ( !has(inst.instanceId()) );
}

#ifndef _RDEV_NO_STL_
	#ifndef _WIN32
		template <class T>
		ostream& operator<<(ostream& os, const RTRClassCategory<T>& c)
		{
			os << "Class: " << c.categoryClass() << endl;

			RTRLinkedList<T>& l = (RTRLinkedList<T>&)c._contents;

			for (l.start(); !l.off(); l.forth())
			{
				os << "	" << l.item()->instanceId();
				if ( l.position() != l.count() )
					os << endl;
			}
			return os;
		}
	#endif
#else
	#ifndef _WIN32
	template <class T>
	void RTRClassCategory<T>::print(FILE* os)
	{
		fprintf(os, "Class: %s\n", categoryClass().to_c());

		RTRLinkedList<T>& l = (RTRLinkedList<T>&)_contents;

		for (l.start(); !l.off(); l.forth())
		{
			fprintf(os, "	%s", l.item()->instanceId().to_c());
			if ( l.position() != l.count() )
				fprintf(os, "\n");
		}
	}
	#endif
#endif

template <class T>
RTRClassCategoryIterator<T> RTRClassCategory<T>::instanceIterator() 
{
	return RTRClassCategoryIterator<T>(this);
}

//
// RTRClassCategoryIterator
//
template <class T>
RTRClassCategoryIterator<T>::RTRClassCategoryIterator(RTRClassCategory<T>* p)
	:_context(p)
{
	// In future, for MT capability, a rwlock is needed to lock the list
	// and each iterator will keep its own cursor instead of using list's
}

template <class T>
RTRClassCategoryIterator<T>::~RTRClassCategoryIterator()
{
}


template <class T>
int RTRClassCategoryIterator<T>::count() const
{
	return _context->_contents.count();
}

template <class T>
RTRBOOL RTRClassCategoryIterator<T>::off() const
{
	return _context->_contents.off();
}

template <class T>
RTRBOOL RTRClassCategoryIterator<T>::empty() const
{
	return count() == 0;
}

template <class T>
T & RTRClassCategoryIterator<T>::item() const
{
	return *_context->_contents.item();
}

template <class T>
void RTRClassCategoryIterator<T>::start()
{
	_context->_contents.start();
}

template <class T>
void RTRClassCategoryIterator<T>::finish()
{
	_context->_contents.finish();
}

template <class T>
void RTRClassCategoryIterator<T>::forth()
{
	RTPRECONDITION (!off());
	_context->_contents.forth();
}

template <class T>
void RTRClassCategoryIterator<T>::back()
{
	RTPRECONDITION (!off());
	_context->_contents.back();
}

//
// RTRDirectory
//
template <class T>
RTRDirectory<T>::RTRDirectory()
{
}

template <class T>
RTRDirectory<T>::~RTRDirectory()
{
	RTRLock lock(*this);
	_categories.deleteContents();
}

template <class T>
int RTRDirectory<T>::categoryCount() 
{
	RTRLock lock(*this);
	RTRLinkedList<RTRClassCategory<T> >& l = 
			(RTRLinkedList<RTRClassCategory<T> >&)_categories;

	return l.count();
}

template <class T>
int RTRDirectory<T>::instanceCount()
{
	RTRLock lock(*this);
	RTRLinkedList<RTRClassCategory<T> >& l = 
			(RTRLinkedList<RTRClassCategory<T> >&)_categories;
	int result = 0;
	for (l.start(); !l.off(); l.forth())
		result += l.count();
	return result;
}

template <class T>
RTRBOOL RTRDirectory<T>::hasInstance(const RTRObjectId& id)
{
	RTRLock lock(*this);
	RTRLinkedList<RTRClassCategory<T> >& l = 
			(RTRLinkedList<RTRClassCategory<T> >&)_categories;

	for (l.start(); !l.off() && !l.item()->has(id); l.forth())
		;
	return l.off() ? RTRFALSE : RTRTRUE;
}

template <class T>
RTRBOOL RTRDirectory<T>::hasCategory(const RTRObjectId& cid)
{	
	RTRLock lock(*this);
	RTRLinkedList<RTRClassCategory<T> >& l = 
			(RTRLinkedList<RTRClassCategory<T> >&)_categories;

	for ( l.start(); !l.off() ; l.forth() )
		if ( l.item()->categoryClass() == cid )
			break;
	return l.off() ? RTRFALSE : RTRTRUE;
}

template <class T>
T *RTRDirectory<T>::instance(const RTRObjectId& id)
{	
	RTRLock lock(*this);
	RTRLinkedList<RTRClassCategory<T> >& l = 
			(RTRLinkedList<RTRClassCategory<T> >&)_categories;

	T *result = 0;
	for (l.start();!l.off() && !result; l.forth())
		result = l.item()->instance(id);

	RTPOSTCONDITION ( result ? hasInstance(id) : !hasInstance(id) );
	RTPOSTCONDITION ( !result || result->instanceId() == id );

	return result;
}

template <class T>
const RTRClassCategory<T> *
RTRDirectory<T>::category(const RTRObjectId& cid)
{
	RTRLock lock(*this);
	RTRLinkedList<RTRClassCategory<T> >& l = 
			(RTRLinkedList<RTRClassCategory<T> >&)_categories;

	for (l.start(); 
			!l.off() && !(cid == l.item()->categoryClass()); 
				l.forth())
			;

	const RTRClassCategory<T> *result = l.off() ? 0 : l.item();

	RTPOSTCONDITION ( result ? hasCategory(cid) : !hasCategory(cid) );
	RTPOSTCONDITION ( !result || result->categoryClass() == cid );

	return result;
}

template <class T>
void RTRDirectory<T>::put(T& inst)
{
	RTPRECONDITION ( !hasInstance(inst.instanceId()) );

	RTRString tmpStr;
	RTRLinkedList<RTRString> *lineage = inst.classId().lineage();
	lineage->start();
	do
	{
		tmpStr.append(*(lineage->item()));
		RTRObjectId tmpId(tmpStr);
		RTRClassCategory<T> *cat = (RTRClassCategory<T> *)category(tmpId);
		if (!cat)
		{
			cat = new RTRClassCategory<T>(tmpId);
			putCategory(*cat);
		}
		cat->put(inst);

			// FIX ME : RTRObjectId should make static data member 
			// "defaultDelimiter" public.
		tmpStr.append('.');
		lineage->forth();
	}
	while ( !lineage->off() );
	lineage->deleteContents();
	delete lineage;

	RTPOSTCONDITION ( hasInstance(inst.instanceId()) );
	RTPOSTCONDITION ( hasCategory(inst.classId()) );
	RTPOSTCONDITION ( instance(inst.instanceId()) == &inst );
}

template <class T>
void RTRDirectory<T>::remove(T& inst)
{
	RTRString tmpStr;
	RTRLinkedList<RTRString> *lineage = inst.classId().lineage();
	lineage->start();
	do
	{
		tmpStr.append(*(lineage->item()));
		RTRObjectId tmpId(tmpStr);
		RTRClassCategory<T> *cat = (RTRClassCategory<T> *)category(tmpId);
		cat->remove(inst);

			// FIX ME : RTRObjectId should make static data member 
			// "defaultDelimiter" public.
		tmpStr.append('.');
		lineage->forth();
	}
	while ( !lineage->off() );
	lineage->deleteContents();
	delete lineage;

	RTPOSTCONDITION ( !hasInstance(inst.instanceId()) );
}

template <class T>
const RTRLinkedList< RTRClassCategory<T> >& RTRDirectory<T>::contents() const
{
	return _categories;
}

template <class T>
void RTRDirectory<T>::putCategory(RTRClassCategory<T>& cat)
{
	RTRLock lock(*this);
	_categories.finish();
	_categories.addRight(&cat);
}

#ifndef _RDEV_NO_STL_
	#ifndef _WIN32
		template <class T>
		ostream& operator<<(ostream& os, const RTRDirectory<T>& d)
		{
			RTRLinkedList<RTRClassCategory<T> >& l = 
					(RTRLinkedList<RTRClassCategory<T> >&)d._categories;

			os << "Directory Contents:" << endl;
			for (l.start(); !l.off(); l.forth())
			{
				os << *(l.item());
				if ( l.position() != l.count() )
					os << endl;
			}
			return os;
		}
	#endif
#else
	#ifndef _WIN32
	template <class T>
	void RTRDirectory<T>::print(FILE* os)
	{
			RTRLinkedList<RTRClassCategory<T> >& l = 
					(RTRLinkedList<RTRClassCategory<T> >&)_categories;

			fprintf(os, "Directory Contents:\n");
			for (l.start(); !l.off(); l.forth())
			{
				((RTRClassCategory<T>*) l.item())->print(os);
				
				if ( l.position() != l.count() )
					fprintf(os, "\n");
			}
	}
	#endif
#endif

template <class T>
RTRDirectoryIterator<T> RTRDirectory<T>::categoryIterator() 
{
	return RTRDirectoryIterator<T>(this);
}

//
// RTRDirectoryIterator
//
template <class T>
RTRDirectoryIterator<T>::RTRDirectoryIterator(RTRDirectory<T>* p)
	:_context(p)
{
	// In future, for MT capability, a rwlock is needed to lock the list
	// and each iterator will keep its own cursor instead of using list's
}

template <class T>
RTRDirectoryIterator<T>::~RTRDirectoryIterator()
{
}


template <class T>
int RTRDirectoryIterator<T>::count() const
{
	return _context->_categories.count();
}

template <class T>
RTRBOOL RTRDirectoryIterator<T>::off() const
{
	return _context->_categories.off();
}

template <class T>
RTRBOOL RTRDirectoryIterator<T>::empty() const
{
	return count() == 0;
}

template <class T>
RTRClassCategory<T> & RTRDirectoryIterator<T>::item() const
{
	return *_context->_categories.item();
}

template <class T>
void RTRDirectoryIterator<T>::start()
{
	_context->_categories.start();
}

template <class T>
void RTRDirectoryIterator<T>::finish()
{
	_context->_categories.finish();
}

template <class T>
void RTRDirectoryIterator<T>::forth()
{
	RTPRECONDITION (!off());
	_context->_categories.forth();
}

template <class T>
void RTRDirectoryIterator<T>::back()
{
	RTPRECONDITION (!off());
	_context->_categories.back();
}
