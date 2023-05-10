//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|
//|       1400 Kensington Road, Oak Brook IL  60521       
//|
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
//
// Author: Tom Hansen
// Created: Wed Nov 17 09:42:52 1993
// Version: 1.0

template<class G> 
RTRSortedTwoWayList<G>::RTRSortedTwoWayList()
{
	listRep = new RTRLinkedList<G>;
}

template<class G> 
RTRSortedTwoWayList<G>::~RTRSortedTwoWayList()
{
	delete listRep;
}

template<class G> 
G* RTRSortedTwoWayList<G>::operator[](int i) const
{
	RTPRECONDITION( (i > 0) && (i <= count()) );
	return listRep->iTh(i);
}

template<class G> 
G* RTRSortedTwoWayList<G>::iTh(int i) const
{
	RTPRECONDITION( (i > 0) && (i <= count()) );
	return listRep->iTh(i);
}

template<class G> 
G* RTRSortedTwoWayList<G>::first() const
{
	RTPRECONDITION( !empty() );
	return listRep->first();
}

template<class G> 
G* RTRSortedTwoWayList<G>::last() const
{
	RTPRECONDITION( !empty() );
	return listRep->last();
}

template<class G> 
RTRBOOL RTRSortedTwoWayList<G>::empty() const
{
	return listRep->empty();
}

template<class G> 
RTRBOOL RTRSortedTwoWayList<G>::has(G* item) const
{
	RTPRECONDITION( item != 0 );
	return listRep->has(item);
}

template<class G> 
int RTRSortedTwoWayList<G>::count() const
{
	return listRep->count();
}

template<class G> 
RTRSortedTwoWayList<G>& RTRSortedTwoWayList<G>::merge(RTRSortedTwoWayList<G>& aList)
{
	for (int i=1; i<aList.count(); i++)
		extend(aList.iTh(i));
	return *this;
}

template<class G> 
RTRSortedTwoWayList<G>& RTRSortedTwoWayList<G>::search(G* item)
{
	RTPRECONDITION( !off() );
	listRep->search(item);
	return *this;
}

template<class G> 
int RTRSortedTwoWayList<G>::index() const
{
	return listRep->index();
}

template<class G> 
RTRBOOL RTRSortedTwoWayList<G>::off() const
{
	return listRep->off();
}

template<class G> 
G* RTRSortedTwoWayList<G>::item() const
{
	RTPRECONDITION( !off() );
	return listRep->item();
}

template<class G> 
RTRSortedTwoWayList<G>& RTRSortedTwoWayList<G>::start()
{
	listRep->start();
	return *this;
}

template<class G> 
RTRSortedTwoWayList<G>& RTRSortedTwoWayList<G>::finish()
{
	listRep->finish();
	return *this;
}

template<class G> 
RTRSortedTwoWayList<G>& RTRSortedTwoWayList<G>::forth()
{
	RTPRECONDITION( index() <= count() ); 
	listRep->forth();
	return *this;
}

template<class G> 
RTRSortedTwoWayList<G>& RTRSortedTwoWayList<G>::back()
{
	RTPRECONDITION( index() >= 0 ); 
	listRep->back();
	return *this;
}

template<class G> 
RTRSortedTwoWayList<G>& RTRSortedTwoWayList<G>::remove()
{
	RTPRECONDITION( !off() );
	listRep->remove();
	return *this;
}

template<class G> 
RTRSortedTwoWayList<G>& RTRSortedTwoWayList<G>::goITh(int i)
{
	RTPRECONDITION( !empty() );
	RTPRECONDITION( i <= count() );
	RTPRECONDITION( i > 0 );
	listRep->goITh(i);
	return *this;
}

template<class G> 
RTRSortedTwoWayList<G>& RTRSortedTwoWayList<G>::extend(G* it)
{
	for (listRep->start(); 
			!listRep->off() && *it < *listRep->item();
				listRep->forth())
		;
	if (listRep->off())
	{
		listRep->finish();
		listRep->addRight(it);
	}
	else
		listRep->addLeft(it);
	return *this;
}


template<class G> 
RTRSortedTwoWayList<G>& RTRSortedTwoWayList<G>::extendFromBehind(G* it)
{
     for (listRep->finish(); 
               !listRep->off() && *it > *listRep->item();
                   listRep->back())
       ;
    if (listRep->off())
        listRep->addFront(it);
    else
        listRep->addRight(it);
	return *this;
}
