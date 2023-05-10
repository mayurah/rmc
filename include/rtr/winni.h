//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: M. Schwenk
// Created: "Oct. 25 1994"
// Version: 1.0

#ifndef RTR_WINDOWS_NOTIFIER
#define RTR_WINDOWS_NOTIFIER

// NOTE: 
//
// windows.h (or afx.h if you are using MFC) must be included before this file
//
// The explicit include of windows.h has been removed to make it easier
// for the user to choose whether windows.h or afx.h should be used.

#include "rtr/rtrdefs.h"
#include "rtr/rtrnotif.h"
#include "rtr/enimp.h"

class RTRWindowsNotifier;	// needed below where pointer to self declared

// Synopsis:
// "//"must first #include <windows.h> (or <afx.h> if using MFC)
// #include"rtr/winni.h"
//
// Description:
//	This implementation of RTREventNotifierImp (RTREventNotifier) is based on the
//	Windows library.  The implementation allocates a window (WNDCLASS) which
//	is used to register for I/O and timing events as needed.
// 
//	RTREventNotifierImp maintains a record of all requested timers, only one
//	of which is outstanding at a given time.
//	When a timer event is requested, RTREventNotifierImp will
//	determine what the next required timer interval is and invoke enableTimer().
//	This method is implemented here to register with Windows for a call-back at the
//	requested interval.
//  
//	RTREventNotifierImp requests I/O notification via calls to
//	enable/disableReadNotification(), etc. These routines are implemented here
//	to use the WSAAsyncSelect() to register for Windows I/O events.
//
// See Also:
//	RTREventNotifier, RTRSelectNotifier, RTRXtNotifier, RTRXViewNotifier
//
// Inherits:
//	RTREventNotifierImp
//

class RTRWindowsNotifier : 
	public RTREventNotifierImp
{
public:
// Constructor
	RTRWindowsNotifier();
		// _TAG Constructor

// Destructor
	~RTRWindowsNotifier();
		// _TAG Destructor

// From RTREventNotifier
// Control
	void enable();
		// Enable the notifier.  Note that the notifer is enabled
		// automatically when created, so this is not needed.
		// OBSOLETE - Left for compatibility with older versions.
		// _TAG01 Control -- from RTREventNotifier

	void disable();
		// Stop dispatching events.  In general, components should not use this.
		// Instead, disable I/O notification on any registered file descriptors
		// and cancel timers.  Then when the application exits, the notifier
		// destructor will be called and clean up.  Since everything registered
		// with the notifier has already been unregistered, there will be no
		// callbacks while the process is cleaning up objects.  Use of disable
		// merely avoids the requirement of unregistering before exiting.
		// _TAG01 Control -- from RTREventNotifier

// From RTREventNotifierImp
// System specific methods
	void enableTimer(long seconds, int milliseconds);
		// Establish a timer for the given time, canceling any previous timer.
		// _TAG02 System specific methods -- from RTREventNotifierImp

	virtual void disableTimer();
		// Cancel any previous timer.
        // _TAG02 System specific methods -- from RTREventNotifierImp

	void enableReadNotification(int fd);
        // _TAG02 System specific methods -- from RTREventNotifierImp

	void disableReadNotification(int fd);
        // _TAG02 System specific methods -- from RTREventNotifierImp

	void enableWriteNotification(int fd);
        // _TAG02 System specific methods -- from RTREventNotifierImp

	void disableWriteNotification(int fd);
        // _TAG02 System specific methods -- from RTREventNotifierImp

	void enableExceptNotification(int fd);
        // _TAG02 System specific methods -- from RTREventNotifierImp

	void disableExceptNotification(int fd);
        // _TAG02 System specific methods -- from RTREventNotifierImp

// Attributes
	inline HWND windowHandle() const;
		// _TAG03 Attributes

// State
	RTRBOOL enabled() const { return _enabled; }
		// _TAG04 State

// WindowsNotifier members
	static RTRWindowsNotifier* instance;
		// _TAG05 WindowsNotifier members

private:
// WindowsNotifier members
	static LRESULT CALLBACK windowProcedure(HWND hwnd, UINT uMsg,
	  WPARAM wParam, LPARAM lParam);
	static VOID CALLBACK timerEvent(HWND hwnd, UINT uMsg, UINT idEvent,
	  DWORD dwTime);
	long desiredEvents(int fd);
	void initializeWindowHandle();

	enum {_timerID = 1};

	RTRBOOL _enabled;
	HWND _windowHandle;		// don't access directly, use windowHandle() instead
// Friends
friend class RTREventNotifierInit;
};

inline HWND RTRWindowsNotifier::windowHandle() const
{
	if (_windowHandle == 0)	{
		// initializeWindowHandle changes concrete state but not abstract state
		((RTRWindowsNotifier*)this)->initializeWindowHandle();
	}
	return _windowHandle;
}
#endif
