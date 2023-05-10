//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|
//|       1400 Kensington Road, Oak Brook IL  60521       
//|
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Definition of a test case class
//
// Author: Tom Hansen
// Created:
// Version: 1.0
//

#ifndef RTR_TEST_CASE 
#define RTR_TEST_CASE



#include "rtr/rtrdefs.h"
#include "rtr/rtstring.h"


class RTRTestCase
{

private:

protected:
	
	RTRBOOL	  test_executed;
	RTRString int_name;
	RTRString exp_results;
	RTRString act_results;
	
public:
	
			RTRTestCase();
			virtual ~RTRTestCase(){;};

			RTRBOOL		verbose;
			void		setVerbose(RTRBOOL b);
			RTRString&	name();
 virtual void		execute();
//	virtual void		execute() = 0;
			RTRBOOL		failed();
			RTRBOOL		passed();
			RTRString&	expectedResults();
			RTRString&	actualResults();
			RTRBOOL		testExecuted();
			RTRBOOL operator==(const RTRTestCase& other) const;


};




#endif /* RTR_TEST_CASE */


