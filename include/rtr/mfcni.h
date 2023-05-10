//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: T. McSwine
// Version: 1.0

#define _AFX_NOFORCE_LIBS
#include "rtr/enimp.h"
#include <afxwin.h>


// Synopsis:
//
// Description:
//
// 	Implementation of RTREventNotifierImp for Microsoft Windows.
//
// See Also:
//
class RTRMFCNotifier 
	: public CWnd, 
	  public RTREventNotifierImp
{
// Constructor
public:
	RTRMFCNotifier();
		// _TAG Constructor

public:
	virtual ~RTRMFCNotifier();
		// _TAG Destructor

// Attributes
	BOOL enabled()		const	{ return _enabled; }
		// _TAG01 Attributes

	HWND windowHandle();
		// _TAG01 Attributes

// From RTREventNotifierImp
// System specific methods
	virtual void disable();
		// Stop dispatching events.  In general, components should not use this.
		// Instead, disable I/O notification on any registered file descriptors
		// and cancel timers.  Then when the application exits, the notifier
		// destructor will be called and clean up.  Since everything registered
		// with the notifier has already been unregistered, there will be no
		// callbacks while the process is cleaning up objects.  Use of disable
		// merely avoids the requirement of unregistering before exiting.
		// _TAG02 System specific methods -- from RTREventNotifierImp

	// From RTREventNotifierImp
	virtual void enableTimer(long seconds, int milliseconds);
		// _TAG02 System specific methods -- from RTREventNotifierImp
	virtual void disableTimer();
		// _TAG02 System specific methods -- from RTREventNotifierImp

	virtual void enableReadNotification(int fd);
		// _TAG02 System specific methods -- from RTREventNotifierImp
	virtual void disableReadNotification(int fd);
		// _TAG02 System specific methods -- from RTREventNotifierImp

	virtual void enableWriteNotification(int fd);
		// _TAG02 System specific methods -- from RTREventNotifierImp
	virtual void disableWriteNotification(int fd);
		// _TAG02 System specific methods -- from RTREventNotifierImp

	virtual void enableExceptNotification(int fd);
		// _TAG02 System specific methods -- from RTREventNotifierImp
	virtual void disableExceptNotification(int fd);
		// _TAG02 System specific methods -- from RTREventNotifierImp

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RTRMFCNotifier)
	//}}AFX_VIRTUAL

	static RTRMFCNotifier* instance;

protected:
// Implementation
// Attributes
	BOOL _enabled;

	// From RTREventNotifier
	virtual void enable();
		// Enable the notifier.  Note that the notifer is enabled
		// automatically when created, so this is not needed.
		// OBSOLETE - Left for compatibility with older versions.

	enum {_timerID = 1};

	long desiredEvents(int socketId);
		// Events Currently of Interest on the Specified Socket
	BOOL createWindow(void);
		// Create Hidden Dispatcher Window


	// Generated message map functions
	//{{AFX_MSG(RTRMFCNotifier)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnSfcEvent(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Friends
friend class RTREventNotifierInit;

};

inline HWND RTRMFCNotifier::windowHandle()
{
	if ( m_hWnd == NULL )
		createWindow();

	return m_hWnd;
}

