//
//|---------------------------------------------------------------
//|                Copyright (C) 1996 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//	author:		Robert Bonaguro
//	created:	September 14, 1995
//	version:	1.0

#ifndef __lnsrctbl_h
#define __lnsrctbl_h

#include "rtr/rtrdefs.h"
#include "rtr/os.h"

// Synopsis:
//	This class should be used when you need to store integer,pointer
//	pairs and search for pair based upon the integer value.
//
// Description:
//	This class implements array type storage by putting
//	elements in a single linked list. Elements consist of
//	and integer value and a pointer value (void*). You
//	can get the pointer value associated with any integer value.
//	You can also iterate through the list.
//
//	Destruction: This class cannot destruct objects within it.
//	The user of this class is in charge of destruction of the
//	in the table.
//
//
//  64 Bit:  Uses a unsigned long long, pointer pair
//
// See Also:
//

class RTRLinSrchTbl
{
public:

// Constructor
	RTRLinSrchTbl();
		// _TAG Constructor

// Destructor
	~RTRLinSrchTbl();
		// _TAG Destructor

// Attributes
	inline RTRBOOL isEmpty() const
		// Is the table currently empty?
		// _TAG01 Attributes
	{
		return( _first == 0 );
	};

	inline int count() const
		// The number of items in the table.
		// _TAG01 Attributes
	{
		return(_count);
	};

// Access
#ifdef COMPILE_64BITS
	void *get(rtrUInt64 value) const;
#else
	void *get(int value) const;
#endif
		// Return the pointer associated with the value.
		// _TAG02 Access

#ifdef COMPILE_64BITS
	RTRBOOL get(void *ptr, rtrUInt64 *value) const;
#else
	RTRBOOL get(void *ptr, int *value) const;
#endif
		// Return the value associated with pointer.
		// The value will be filled into the value
		// pointer. Returns RTRTRUE if found, RTRFALSE
		// otherwise.

// Insertion
#ifdef COMPILE_64BITS
	void add(rtrUInt64 value, void *ptr);
#else
	void add(int value, void *ptr);
#endif
		// Add the (value,ptr) pair to the table.
		// REQUIRE: get(value) == 0
		// _TAG03 Insertion

// Deletion
#ifdef COMPILE_64BITS
	void remove(rtrUInt64 value);
#else
	void remove(int value);
#endif
		// Remove the (value,ptr) pair associated with value.
		// _TAG04 Deletion

// Traversal
	inline void start()
		// Move the cursor to the beginning of the list.
		// _TAG05 Traversal
	{
		_current = _first;
		_currentWasDeleted = 0;
	};

	inline RTRBOOL off() const
		// Is the cursor out-of-bounds?
		// _TAG05 Traversal
	{
		return(_current == 0);
	};

	inline void forth()
		// Move the cursor toward the end of the list.
		// REQUIRE : !off()
		// _TAG05 Traversal
	{
		RTPRECONDITION(!off());

			// If the previous _current was deleted, we have already
			// moved to the next item, so don't move the cursor again.
		if ( ! _currentWasDeleted && _current )
			_current = _current->next;
		_currentWasDeleted = 0;
	};

	inline void *current() const
		// The ptr value at the current cursor position.
		// REQUIRE : !off()
		// _TAG05 Traversal
	{
		RTPRECONDITION(!off());
		RTPRECONDITION(!_currentWasDeleted);
		return(_current->ptr_value);
	};

#ifdef COMPILE_64BITS
	inline rtrUInt64 curValue() const
#else
	inline int curValue() const
#endif
		// The value at the current cursor position.
		// REQUIRE : !off()
		// _TAG05 Traversal
	{
		RTPRECONDITION(!off());
		RTPRECONDITION(!_currentWasDeleted);
		return(_current->value);
	};


protected:

	class linStore
	{
	public:
		void		*ptr_value;
#ifdef COMPILE_64BITS
		rtrUInt64	value;
#else
		int			value;
#endif
		linStore	*next;

		inline linStore() : next(0) {};
	};


		// For storage
	linStore	*_first;
	linStore	*_last;
	int			_count;

		// For Traversing
	linStore	*_current;
	unsigned short	_currentWasDeleted:1;
		// Set if the _current was deleted since the last call to forth().
};


#endif
