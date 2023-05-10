//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|
//|       1400 Kensington Road, Oak Brook IL  60521       
//|
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Definition of a test driver class
//
// Author: Tom Hansen
// Created:
// Version: 1.0
//

#ifndef RTR_TEST_DRIVER 
#define RTR_TEST_DRIVER



#include "rtr/rtrdefs.h"
#include "rtr/rttstcas.h"
#include "rtr/rtllist.h"


class RTRTestDriver:public RTRTestCase
{

private:

protected:

public:

// Constructor
	RTRTestDriver();

// Destructor
	virtual ~RTRTestDriver();

// From RTRTestCase
	void		execute();

// New
	virtual	RTRLinkedList<RTRTestCase> * tests() = 0;
	virtual	void	loadTests()=0;
};




#endif /* RTR_TEST_DRIVER */


