//|-----------------------------------------------------------
//|              Copyright (C) 2015 Refinitiv                     
//| All rights reserved. Duplication & distribution prohibited 
//|-----------------------------------------------------------
//
// Author(s):  Zbigniew Minciel
// Created: 3/24/2015
//
// Synopsis: 
//
// Description: sorting functions to sort the folowing:
//   RTRDLinkList, RTRLiteDLinkList, RTRSLinkList, RTRLiteSLinkList and array of objects of any type.
//
// Implementation of quick sort, merge sort and insert sort.
// Use RTRSorter helper class for best performance.  
// RTRSorter leverages the Merge sort algorithm and allocates one or two scratch arrays to boost performance.
// Standalone link list Merge sort function performance can be up to 4-5 time worse comparing to RTRSorter.
// Standalone link list Merge sort function supports doubly link list only and sorting is done in place.
// Standalone array Merge sort function allocates one scratch array to boost performance.
//
// Quick sort functions perform poorly as for now, so don't use them.  Not clear if performance can be improved.
//
// See Also: usage at the bottom. It can be compiled and executed.
//

#ifndef __RTRSort
#define __RTRSort

#include "rtr/platform.h"
#include "rtr/rtrdefs.h"

#include "rtr/dlinkl.h"
#include "rtr/ldlinkl.h"
#include "rtr/slinkl.h"

// template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long RTRSorter::sort(LL<T,L> *list, P predicate);
// template<typename T, typename P> long long RTRSorter::sort(T **a, int length, P predicate);
template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long rtrdl_msort(LL<T,L> *list, P predicate);
template<typename T, typename P> long long rtrdl_array_msort(T **ar, int length, P predicate, T **temp_ar);

// Qsort functions, perform poorly  as for now, don't use for now.
template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long rtrsl_qsort(LL<T,L> *list, P predicate);
template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long rtrdl_qsort(LL<T,L> *list, P predicate);

//  Helper class RTRSorter. Best performer, allocates two temporary arrays (of void** elements) of size equal to link list size/count.
class RTRSorter
{
public: 
	RTRSorter() {arr = 0; temp_arr = 0; ar_size = 0; temp_ar_size;};
	~RTRSorter() {delete [] (int**)arr; delete [] (int**)temp_arr;}

	template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long sort(LL<T,L> *list, P predicate)
	{
		T *object;
		long long swap_cnt;
		int i;

		int list_cnt = list->count(); // expensive for lite version of link list
		if (list_cnt <= 1)
			return 0;

		T **ar = (T**)arr; T **temp_ar = (T**)temp_arr;
		if (list_cnt > ar_size)
		{
			delete [] ar; 
			ar_size = list_cnt;
			ar = new T*[ar_size];
			arr = (void**)(ar);
		}
		if (list_cnt > temp_ar_size)
		{
			delete [] temp_ar;
			temp_ar_size = list_cnt;
			temp_ar = new T*[temp_ar_size];
			temp_arr = (void**)(temp_ar);
		}
		
		for (i = 0; object = list->removeFirst(); i++)
			ar[i] = object;

		swap_cnt = rtrdl_array_msort(ar, list_cnt, predicate, temp_ar);

		for (i = 0; i < list_cnt; i++)
		{
			object = ar[i];
			list->putLast(object);
		}
		return swap_cnt;
	}
	template<typename T, typename P> long long sort(T **a, int length, P predicate)
	{
		long long swap_cnt = 0;
		if (length <= 1)
			return 0;

		T **temp_ar = (T**)temp_arr;
		if (length > temp_ar_size)
		{
			delete [] temp_ar;
			temp_ar_size = length;
			temp_ar = new T*[temp_ar_size];
			temp_arr = (void**)(temp_ar);
		}

		swap_cnt = rtrdl_array_msort(a, length, predicate, temp_ar);
		return swap_cnt;
	}
protected:
	void **arr;
	int ar_size;
	void **temp_arr;
	int temp_ar_size;
};

// Array insert sort
template<typename T, typename P> long long rtrdl_array_isort(T **ar, int length, P predicate)
{
	long long swap_cnt = 0;
	register T *l_object_1;
	register T *l_object_2;
	register int i, j;

	// Use rtrdl_array_msort() for lists > 64
	for (i = 0; i < length; i++)
	{
		for (j = i; j > 0; j--)
		{
			l_object_1 = ar[j];
			l_object_2 = ar[j-1];
			if ( predicate(l_object_1, l_object_2) == RTRTRUE)
			{
				ar[j] = l_object_2;
				ar[j-1] = l_object_1;
				swap_cnt++;
			}
		}
	}
	return swap_cnt;
};

// Merge two arrays already sorted
template<typename T, typename P> long long rtrdl_array_merge_sort(T **ar, T **l_ar, int l_length, T **r_ar, int r_length, P predicate, T **sorted_ar)
{
	long long swap_cnt = 0;
	register T *l_object;
	register T *r_object;

	T **merge_ar = sorted_ar;
	int l_i = 0;
	int r_i = 0;

	while ((l_i < l_length) && (r_i  < r_length))
	{
		l_object = l_ar[l_i];
		r_object = r_ar[r_i];
		if (predicate(l_object, r_object))
		{
			*merge_ar++ = l_object; l_i++;
		}
		else
		{
			*merge_ar++ = r_object;	r_i++;
		}
		swap_cnt++;
	}
	while (l_i < l_length)
	{
		*merge_ar++ = l_ar[l_i]; l_i++;
	}
	while (r_i < r_length)
	{
		*merge_ar++ = r_ar[r_i]; r_i++;
	}
	memcpy(ar, sorted_ar, (l_length + r_length) * sizeof(T*));
	return swap_cnt;
};

// Internal Merge array sort
template<typename T, typename P> long long _rtrdl_array_msort(T **ar, int length, P predicate, T **sorted_ar)
{
	long long swap_cnt = 0;
	if (length > 16)
	{
		int partition = length/2;
		T **l_ar = ar;
		T **r_ar = ar + partition;
		int l_partition_size = partition;
		
		swap_cnt += _rtrdl_array_msort(l_ar, l_partition_size, predicate, sorted_ar);
		int r_partition_size = length - partition;
		swap_cnt += _rtrdl_array_msort(r_ar, r_partition_size, predicate, sorted_ar);

		swap_cnt += rtrdl_array_merge_sort(ar, l_ar, l_partition_size, r_ar, r_partition_size, predicate, sorted_ar);
	}
	else
	{
		swap_cnt += rtrdl_array_isort(ar, length, predicate);
	}
	return swap_cnt;
};

// Merge array sort
template<typename T, typename P> long long rtrdl_array_msort(T **ar, int length, P predicate, T **temp_ar)
{
	if (length <= 1)
		return 0;
	T **caller_supplied_ar = temp_ar;
	T **merge_ar = temp_ar;
	if (merge_ar == 0)
		merge_ar = new T*[length];
	long long swap_cnt = _rtrdl_array_msort(ar, length, predicate, merge_ar);
	if (caller_supplied_ar == 0) delete [] merge_ar;
	return swap_cnt;
};

// List Insert sort
template<typename T, typename L, template<typename T, typename  L> class LL, typename P> long long rtrdl_isort(LL<T,L> *list, P predicate)
{
	T *object, *s_object, *first;
	long long swap_cnt = 0;
	LL<T,L> sorted_list;

	// Use rtrdl_msort() for lists > 16
	int begin_list_cnt = list->count();
	if (begin_list_cnt <= 1)
		return 0;

	first = list->removeFirst();
	L *dd = first;  RTRDLink *d = dd;  // force compiler error if rtrdl_isort called for RTRSLinkList and RTRLiteSLinkList
	sorted_list.putFirst(first);

	swap_cnt += begin_list_cnt;
	while (object = list->removeFirst())
	{
		for (s_object = sorted_list.first(); s_object; s_object = sorted_list.next(s_object))
		{
			swap_cnt++;
			if (predicate(s_object, object) == RTRFALSE)
			{
				sorted_list.putPrevious(s_object, object);
				swap_cnt++;
				break;
			}
		}
		if (s_object == 0)
		{
			sorted_list.putLast(object);
			swap_cnt++;
		}
	}
	list->append(&sorted_list);
	swap_cnt += 2;

	RTRASSERT(begin_list_cnt == list->count());
	return swap_cnt;
}

// merge two sorted lists
template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long rtrdl_merge_sort(LL<T,L> *list, LL<T,L> *l_list, LL<T,L> *r_list, P predicate)
{
	T *l_object, *r_object;
	long long swap_cnt = 0;

	r_object = r_list->first();
	if (r_list->first() == 0)
	{
		list->append(l_list);
		return swap_cnt;
	}

	int begin_list_cnt = l_list->count() + r_list->count();

	while (l_object = l_list->removeFirst())
	{
		swap_cnt++;
		for (; r_object;  r_object = r_list->next(r_object))
		{
			swap_cnt++;
			if (predicate(r_object, l_object) == RTRFALSE)
			{
				r_list->putPrevious(r_object, l_object);
				break;
			}
		}
		// if r_object == 0, it means that all remaining objects on l_list are greater, so append what remains
		if (r_object == 0)
		{
			r_list->putLast(l_object);
			r_list->append(l_list);
			swap_cnt += 2;
			break;
		}
	}
	list->append(r_list);
	swap_cnt++;

	RTRASSERT(begin_list_cnt == list->count());
	return swap_cnt;
}

// Internal Merge sort for lists
template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long _rtrdl_msort(LL<T,L> *list, P predicate)
{
	register T *object;
	long long swap_cnt;
	LL<T,L> l_dlist;
	LL<T,L> r_dlist;

	// list->count() is expensive for RTRLiteDLinkList so if you need to sort large list use RTRDLinkList
	int max_cnt = list->count();

	if (list->count() <= 1)
		return 0;
	
	swap_cnt = 0;
	max_cnt = max_cnt >> 1;
	if (max_cnt > 16)
	{
		// find object in th emiddle of the list
		swap_cnt += max_cnt;
		for (object = list->first(); ((object != 0) && (max_cnt-- > 0)); object = list->next(object))  {;};
		
		// create two seprate lists and sort them
		list->split(object, &r_dlist);
		l_dlist.append(list);
		swap_cnt += 2;

		swap_cnt += _rtrdl_msort(&l_dlist, predicate);
		swap_cnt += _rtrdl_msort(&r_dlist, predicate);
		// merge sorted lists
		swap_cnt += rtrdl_merge_sort(list, &l_dlist, &r_dlist, predicate);
	}
	else
	{
		swap_cnt += rtrdl_isort(list, predicate);
	}
	return swap_cnt;
}

// Merge sort for lists
template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long rtrdl_msort(LL<T,L> *list, P predicate)
{
	L *dd = list->first();  RTRDLink *d = dd;  // force compiler error if _rtrdl_msort is called for RTRSLinkList and RTRLiteSLinkList
	long long swap_cnt = _rtrdl_msort(list, predicate);
	return swap_cnt;
}

//---------------------------------------------------------------------------------------------------------------
// quick sort functions can perform poorly. Not clear if performance can be improved. Don't use qsort functions until performance is improved.
//
// We have seprate sorting function for single and doubly link list because doubly link implementation doesn't support the same functions as single list.
// Missing functions could be added and we could have single sorting functions for both types of lists.
template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long rtrdl_qsort(LL<T,L> *list, T *first, T *last, P predicate)
{
	// quick sort simple algorithm to sort doubly link list
	// The complexity of quick sort in the average case in O(n log(n)) and in the worst case is O(n to power of 2) when the list is already sorted.
	L *dd = first;  RTRDLink *d = dd;  // force compiler error if rtrdl_qsort called for RTRSLinkList and RTRLiteSLinkList

	if ((first == 0) || (last == 0) || (first == last))
			return 0;
	long long swap_cnt = 0;
	T *nlast = 0;  // last object of the right partition
	T *nfirst = first;  // first object of the left partition
	register T *pivot_prev, *pivot_next, *object, *object_next;
	
	T *pivot = last;  // select pivot. TODO: Not a good approach if objects are already sorted.
	// initially, all objects are on the left/single partition. Right partition is empty.

	for (object = first; ((object != 0) && (object != pivot)); )
	{
		swap_cnt++;
		object_next = list->next(object);
		if (predicate(object, pivot) == RTRTRUE)
		{
			// add object to the right partition, update nfirst object if needed
			if (object == nfirst) nfirst = object_next;
			list->remove(object);
			list->putNext(pivot, object);
			if (nlast == 0) nlast = object;
			swap_cnt++;
		}
		object = object_next;
	}
	if (nfirst == pivot) nfirst = 0;

	pivot_prev = list->previous(pivot);
	pivot_next = list->next(pivot);

	swap_cnt += rtrdl_qsort(list, nfirst, pivot_prev, predicate);
	swap_cnt += rtrdl_qsort(list, pivot_next, nlast, predicate);

	return swap_cnt;
}

template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long rtrdl_qsort(LL<T,L> *list, P predicate)
{
	T *first = list->first();
	T *last = list->last();
	L *dd = first;  RTRDLink *d = dd;  // force compiler error if rtrdl_qsort called for RTRSLinkList and RTRLiteSLinkList
	long long swap_cnt = rtrdl_qsort(list, first, last, predicate);
	return swap_cnt;
}

// We have seprate sorting function for single and doubly link list because doubly link implementation doesn't support the same functions as single list.
// Missing functions could be added and we could have single sorting functions for both types of lists.
template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long rtrsl_qsort(LL<T,L> *list, T *first, T *last, P predicate)
{
	// quick sort simple algorithm to sort doubly link list
	// The complexity of quick sort in the average case in O(n log(n)) and in the worst case is O(n to power of 2) when the list is already sorted.
	L *dd = first;  RTRSLink *d = dd;  // force compiler error if rtrsl_qsort called for RTRDLinkList and RTRLiteDLinkList

	if ((first == 0) || (last == 0) || (first == last))
			return 0;
	long long swap_cnt = 0;
	T *nlast = 0;  // last object of the right partition
	T *nfirst = first;  // first object of the left partition
	register T *pivot_prev, *pivot_next, *object, *object_next, *object_prev;
		
	T *pivot = last;  // select pivot. TODO: Not a good approach if objects are already sorted.
	// initially, all objects are on the left/single partition. Right partition is empty.
	object_prev = 0;
	for (object = first; ((object != 0) && (object != pivot)); )
	{
		swap_cnt++;
		object_next = list->next(object);
		if (predicate(object, pivot) == RTRTRUE)
		{
			// add object to the right partition, update nfirst object if needed
			if (object == nfirst) nfirst = object_next;
			if (object_prev)
			{
				list->removeNext(object_prev, object);
			}
			else
				list->remove(object);  // very expensive
			list->putNext(pivot, object);
			if (nlast == 0) nlast = object;
			swap_cnt++;
		}
		else
			object_prev = object;
		object = object_next;
	}
	if (nfirst == pivot) nfirst = 0;

	pivot_prev = object_prev;
	pivot_next = list->next(pivot);

	swap_cnt += rtrsl_qsort(list, nfirst, pivot_prev, predicate);
	swap_cnt += rtrsl_qsort(list, pivot_next, nlast, predicate);
	return swap_cnt;
}

template<typename T, typename L, template<typename T, typename L> class LL, typename P> long long rtrsl_qsort(LL<T,L> *list, P predicate)
{
	T *first = list->first();
	T *last = list->last();
	L *dd = first;  RTRSLink *d = dd;  // force compiler error if rtrsl_qsort called for RTRDLinkList and RTRLiteDLinkList
	long long swap_cnt = rtrsl_qsort(list, first, last, predicate);
	return swap_cnt;
}


/////////////////////////////////////  Example usage
// include this header in the C file and define RUN_SORT_MAIN to build test program
// #define RUN_SORT_MAIN
#ifdef RUN_SORT_MAIN
#include <stdlib.h>
#include <stdio.h>
#include "rtr/dlinkl.h"
#include "rtr/ldlinkl.h"
#include "rtr/slinkl.h"

template<typename T> struct MyPredicateLess  // will sort items from samllest to largest
{
    RTRBOOL operator()(T *o1, T *o2)
    {
        if (o1->_count < o2->_count)  // make sure < is used and mot <=
            return RTRTRUE;
        else
            return RTRFALSE;
    }
};

template<typename T> struct MyPredicateGreater  // will sort items from largest to smallest
{
    RTRBOOL operator()(T *o1, T *o2)
    {
        if (o1->_count > o2->_count)  // make sure > is used and not >=
            return RTRTRUE;
        else
            return RTRFALSE;
    }
};

class ITEM: public RTRDLink0, public RTRDLink1, public RTRSLink0 {
public:
	ITEM(int count) { _count = count;}
	int _count;
};

int main(int argc, char **argv)
{
	long long swap_cnt;
	RTRDLinkList<ITEM,RTRDLink0> dlist;
	RTRLiteDLinkList<ITEM,RTRDLink1> ldlist;
	RTRSLinkList<ITEM,RTRSLink0> slist;
	ITEM **item_array = 0;
	
	RTRSorter sorter;
	const int max_items = 31;
	item_array = new ITEM*[max_items];

	ITEM *item;
	int i;
	for (i = 0; i < max_items; i++)
	{
		item = new ITEM(10);
		item->_count = i;

		dlist.putLast(item); 
		ldlist.putLast(item); 
		slist.putLast(item);
		item_array[i] = item;
	}

	for (item = dlist.first(); item != 0; item = dlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d\n", dlist.count());
	for (item = ldlist.first(); item != 0; item = ldlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d\n", ldlist.count());
	for (item = slist.first(); item != 0; item = slist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d\n", slist.count());

	MyPredicateLess<ITEM> predicateLess;
	MyPredicateGreater<ITEM> predicateGreater;

	swap_cnt = sorter.sort(item_array, max_items, MyPredicateGreater<ITEM>());
	// or swap_cnt = sorter.sort(item_array, max_items, predicateGreater);
	for (i = 0; i < max_items; i++)
		{ item = item_array[i]; fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", max_items, swap_cnt);

	swap_cnt = sorter.sort(&dlist, MyPredicateLess<ITEM>());
	// or swap_cnt = sorter.sort(&dlist, predicateLess);
	for (item = dlist.first(); item != 0; item = dlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", dlist.count(), swap_cnt);

	swap_cnt = sorter.sort(&ldlist, MyPredicateGreater<ITEM>());
	for (item = ldlist.first(); item != 0; item = ldlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", ldlist.count(), swap_cnt);

	swap_cnt = sorter.sort(&slist, MyPredicateLess<ITEM>());
	for (item = slist.first(); item != 0; item = slist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", slist.count(), swap_cnt);

	swap_cnt = rtrdl_isort(&dlist, MyPredicateLess<ITEM>());
	for (item = dlist.first(); item != 0; item = dlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", dlist.count(), swap_cnt);

	swap_cnt = rtrdl_isort(&dlist, MyPredicateGreater<ITEM>());
	for (item = dlist.first(); item != 0; item = dlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", dlist.count(), swap_cnt);

	swap_cnt = rtrdl_msort(&dlist, MyPredicateLess<ITEM>());
	for (item = dlist.first(); item != 0; item = dlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", dlist.count(), swap_cnt);

	swap_cnt = rtrdl_msort(&ldlist, MyPredicateLess<ITEM>());
	for (item = ldlist.first(); item != 0; item = ldlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", ldlist.count(), swap_cnt);

	swap_cnt = rtrdl_qsort(&dlist, MyPredicateGreater<ITEM>());
	// or swap_cnt = rtrdl_qsort<ITEM,RTRDLink0>(&dlist, MyPredicateGreater<ITEM>());
	for (item = dlist.first(); item != 0; item = dlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", dlist.count(), swap_cnt);

	swap_cnt = rtrdl_qsort(&ldlist, MyPredicateLess<ITEM>());
	for (item = ldlist.first(); item != 0; item = ldlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", ldlist.count(), swap_cnt);

	swap_cnt = rtrdl_qsort(&ldlist, MyPredicateLess<ITEM>());
	for (item = ldlist.first(); item != 0; item = ldlist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", ldlist.count(), swap_cnt);

	swap_cnt = rtrsl_qsort(&slist, MyPredicateLess<ITEM>());
	for (item = slist.first(); item != 0; item = slist.next(item))  
		{ fprintf(stdout, "%d ", item->_count); } fprintf(stdout, "list_cnt=%d swap_cnt=%lld\n", slist.count(), swap_cnt);
	
}
#endif

#endif

