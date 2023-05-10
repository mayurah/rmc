//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//

#ifndef __rtr_indxable_h 
#define __rtr_indxable_h

#include "rtr/rtrdefs.h"

/**
 * \class RTRIndexableStore indxable.h "rtr/indxable.h"
 * \brief
 * Abstraction which allows generalized iterator.
 * 
 * Iterator descendants can add a custom feature to return
 * a specific type of item.
 * 
 * @see RTRIndexableIterator
 */

class RTRIndexableStore
{
public:
    /** Destructor */
	virtual ~RTRIndexableStore() {};

	///@name Attributes
	//@{
    /** The number of objects in this collection. */
	virtual int count() const = 0;

    /** The lower index number (>=0). */
	virtual int lower() const = 0;

    /** The upper index number. */
	virtual int upper() const = 0;
	//@}

	///@name State
	//@{
    /** Is this collection empty? */
	inline bool empty() const;
	//@}

	///@name Access
	//@{
    /** Return the object at index i (lower() <= i <= upper()) */
	virtual void *operator[](int i) const = 0;
	//@}

};

inline bool RTRIndexableStore::empty() const 
{
	return count() == 0;
}

/**
 * \class RTRIndexableIterator indxable.h "rtr/indxable.h"
 * \brief
 * A generic iterator for the RTRIndexable class.
 * 
 * @see RTRIndexable
 */

class RTRIndexableIterator
{
public:
    /** Constructor */
	RTRIndexableIterator(const RTRIndexableStore&);

    /** Destructor */
	virtual ~RTRIndexableIterator();

	///@name Attributes
	//@{
    /** Is the iterator off the left side of the index array?
     *  (i.e. < lower())
     */
	virtual bool offLeft() const;

    /** Is the iterator off the right side of the index array?
     *  (i.e. > upper())
     */
	virtual bool offRight() const;

    /** Is the itertor off either side of the index array?
     *  (i.e. offLeft() or offRight())
	 */
    virtual bool off() const;

    /** Returns the number of objects in the Index array.
     *  (returns RTRIndexable::count())
     */
    virtual int count() const;

    /** Returns the iterator's current index. */
	inline int currentPosition() const;
	//@}

	///@name Access
	//@{
    /** Returns the object at current index position.
     *  REQUIRE: !off()
     */
	virtual void *item() const;
	//@}

	///@name Operations
	//@{
    /** Move current index to the beginning position.
     *  (i.e. lower()) */
    virtual void start();

    /** Move current index to the last position.
     *  (i.e. upper()) */
    virtual void finish();

    /** Increment the current index position.
     *  REQUIRE: !offRight() */
	virtual void forth();

    /** Decrement the current index position.
     *  REQUIRE: !offLeft() */
    virtual void back();
	//@}

protected:
//@cond SKIP
	const RTRIndexableStore& target;
	int position;
//@endcond
};

inline int RTRIndexableIterator::currentPosition() const
{
	return position;
}

inline void RTRIndexableIterator::start()
{
	position = target.lower();
}

inline void RTRIndexableIterator::finish()
{
	position = target.upper();
}

inline bool RTRIndexableIterator::offLeft() const 
{	
	return position < target.lower();
}

inline bool RTRIndexableIterator::offRight() const 
{
	return position > target.upper();
}

inline void RTRIndexableIterator::forth() 
{
	RTPRECONDITION( !offRight() );
	position++;
}

inline void RTRIndexableIterator::back()
{
	RTPRECONDITION( !offLeft() );
	position--;
}

inline bool RTRIndexableIterator::off() const 
{
	return (offLeft() || offRight() || target.empty());
}

inline void *RTRIndexableIterator::item() const 
{ 
	RTPRECONDITION( !off() );
	return target[position]; 
}

inline int RTRIndexableIterator::count() const 
{ 
	return target.count(); 
}

#endif 
