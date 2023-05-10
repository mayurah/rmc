//
//|---------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//                 John Arvanites
//  created:       October 11, 1994
//  version:       1.1
//


#ifndef _RTR_SIGNAL_CLIENTS
#define _RTR_SIGNAL_CLIENTS

// Synopsis:
//
// Description:
//
//  This defines the different clients available from
//  the signal notifier.
//
// See Also:
//

class RTRSigIOClient
{
public:
	virtual void processSigIO() = 0;
		// _TAG01 Other

};

// Synopsis:
//
// Description:
//
//  This defines the different clients available from
//  the signal notifier.
//
// See Also:
//

class RTRSigTERMClient
{
public:
	virtual void processSigTERM() = 0;
		// _TAG01 Other
		
};

// Synopsis:
//
// Description:
//
//  This defines the different clients available from
//  the signal notifier.
//
// See Also:
//

class RTRSigINTClient
{
public:
	virtual void processSigINT() = 0;
		// _TAG01 Other

};

// Synopsis:
//
// Description:
//
//  This defines the different clients available from
//  the signal notifier.
//
// See Also:
//

class RTRSigUSR1Client
{
public:
	virtual void processSigUSR1() = 0;
		// _TAG01 Other
};

// Synopsis:
//
// Description:
//
//  This defines the different clients available from
//  the signal notifier.
//
// See Also:
//

class RTRSigUSR2Client
{
public:
	virtual void processSigUSR2() = 0;
		// _TAG01 Other

};

// Synopsis:
//
// Description:
//
//  This defines the different clients available from
//  the signal notifier.
//
// See Also:
//

class RTRSigPIPEClient
{
public:
	virtual void processSigPIPE() = 0;
		// _TAG01 Other
};

// Synopsis:
//
// Description:
//
//  This defines the different clients available from
//  the signal notifier.
//
// See Also:
//

class RTRSigURGClient
{
public:
	virtual void processSigURG() = 0;
		// _TAG01 Other

};

// Synopsis:
//
// Description:
//
//  This defines the different clients available from
//  the signal notifier.
//
// See Also:
//

class RTRSigBUSClient
{
public:
	virtual void processSigBUS() = 0;
		// _TAG01 Other

};

// Synopsis:
//
// Description:
//
//  This defines the different clients available from
//  the signal notifier.
//
// See Also:
//

class RTRSigSEGVClient
{
public:
	virtual void processSigSEGV() = 0;
		// _TAG01 Other

};


// Synopsis:
//
// Description:
//
//  This defines the different clients available from
//  the signal notifier.
//
// See Also:
//

class RTRSigHUPClient
{
public:
	virtual void processSigHUP() = 0;
		// _TAG01 Other

};


#endif
