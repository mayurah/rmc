//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       September 23, 1996
//  version:       1.0
//
//  description:
//


template<class T,class L>
void RTRDescSortList<T,L>::extend(T *object)
{
	RTPRECONDITION ( object );
	T *cur;
	for (cur=first(); (cur != 0)&&(*object <= *cur); cur=next(cur))
		;
	if (cur == 0)
		RTRDList::putLast(toL(object));
	else
		RTRDList::putPrevious(toL(cur),toL(object));
};

template<class T,class L>
void RTRDescSortList<T,L>::extendFromBehind(T *object)
{
	RTPRECONDITION ( object );
	T *cur;
	for (cur=last(); (cur != 0)&&(*object > *cur); cur=previous(cur))
		;
	if (cur == 0)
		RTRDList::putFirst(toL(object));
	else
		RTRDList::putNext(toL(cur),toL(object));
};

template<class T,class L>
void RTRDescSortList<T,L>::deleteContents()
{
	T *cur;
	for ( cur = first(); cur != 0; cur = first())
	{
		remove(cur);
		delete cur;
	};
	RTPOSTCONDITION(empty());
};

template<class T,class L>
void RTRDescSortList<T,L>::wipeOut()
{
	while (!empty())
		removeFirst();
	RTPOSTCONDITION(empty());
};

