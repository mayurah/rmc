//|---------------------------------------------------------------------------
//|                Copyright (C) 1995 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// Author: A. MacGaffey
// Created: "Nov. 08 1995"
// Version: 1.0

#ifndef _logedsp_h
#define _logedsp_h

#include "rtr/dspfrm.h"
#include "rtr/mgmtact.h"
#include "rtr/mgmtevnt.h"
#include "rtr/rtllist.h"
#include "rtr/dlinkl.h"

class RTRLogHistoryDisplay;
class RTRLogEventDisplay;

// Synopsis:
// #include"rtr/logedsp.h"
//
// Description:
// See Also:
//	RTRLogHistoryDisplay, RTRLogEventDisplay, RTRLogEventDisplayFrame
//
// Inherits:
//	RTRDLink0
//

class RTRLogEventRegion :
	public RTRDLink0
{
public:
// Constructor
	RTRLogEventRegion(const RTRLogHistoryDisplay&);
		// _TAG Constructor

// Destructor
	~RTRLogEventRegion();
		// _TAG Destructor

// Attributes
	inline const RTRMgmtEvent *event() const;
		// _TAG01 Attributes

	inline int height() const;
        // _TAG01 Attributes

	inline int row() const;
        // _TAG01 Attributes

	inline int column() const;
        // _TAG01 Attributes

// State
	inline RTRBOOL visible() const;
		// _TAG02 State

// Modify
	void setMgmtEvent(const RTRMgmtEvent *e);
		// ENSURE: event() == e
		// _TAG03 Modify

// Operations - positioning
	void translate(int r, int c);
		// Move by r and c
		// _TAG04 Operations - positioning

	void moveTo(int r, int c);
		// Move to the given row and column.
		// _TAG04 Operations - positioning

// Operations - drawing
	void draw();
		// ENSURE: visible()
		// _TAG05 Operations - drawing

	void erase();
		// ENSURE: !visible()
		// _TAG05 Operations - drawing

	void markDeleted();
		// REQUIRE: visible()
		// _TAG05 Operations - drawing

protected:
// Data
	const RTRLogHistoryDisplay& _display;
	const RTRMgmtEvent *_mgmtEvent;
	RTRBOOL _visible;
	int _row;
	int _column;
	int _height;
	RTRBOOL _deleted;

private:
// Don't define
	RTRLogEventRegion(const RTRLogEventRegion&);
	RTRLogEventRegion& operator=(const RTRLogEventRegion&);
};

inline 
const RTRMgmtEvent *RTRLogEventRegion::event() const
{
	return _mgmtEvent;
}

inline 
int RTRLogEventRegion::height() const
{
	return _height;
}

inline 
int RTRLogEventRegion::row() const
{
	return _row;
}

inline 
int RTRLogEventRegion::column() const
{
	return _column;
}

inline 
RTRBOOL RTRLogEventRegion::visible() const
{
	return _visible;
}

class RTRLogEventDisplay;

// Synopsis:
// #include"rtr/logedsp.h"
//
// Description:
// See Also:
//  RTRLogEventRegion, RTRLogEventDisplay, RTRLogEventDisplayFrame
//
// Inherits:
//	RTRMBrowserDisplay, RTRLogAction
//

class RTRLogHistoryDisplay :
	public RTRMBrowserDisplay,
	public RTRMgmtAction
{ 
public:
// Constructor
	RTRLogHistoryDisplay(
			const RTRString&,	// name
			RTRDisplayFrame&,	// frame owning this display
			RTRLogEventDisplay&,	// Log event detail display
			int			// height
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRLogHistoryDisplay();
		// _TAG Destructor

// Attributes
	inline int maxEvents() const;
		// _TAG01 Attributes

	inline int skipCount() const;
        // _TAG01 Attributes

	inline const RTRLogEventRegion *currentRegion() const;
        // _TAG01 Attributes

	inline RTRLogEventRegion *first() const;
        // _TAG01 Attributes

	inline RTRLogEventRegion *last() const;
        // _TAG01 Attributes

	int scrollHeight() const;
        // _TAG01 Attributes

	int firstScrollingRow() const;
        // _TAG01 Attributes

	int lastScrollingRow() const;
        // _TAG01 Attributes

// Cursor/paging
	virtual void goHome();
		// _TAG04 Cursor/paging

	virtual void moveCursorUp();
        // _TAG04 Cursor/paging

	virtual void moveCursorDown();
        // _TAG04 Cursor/paging

	virtual void nextPage();
        // _TAG04 Cursor/paging

	virtual void previousPage();
        // _TAG04 Cursor/paging

// Operations
	virtual void selectCurrent();
		// _TAG05 Operations

// Operations -- from RTRMBrowserDisplay
	virtual void draw();
		// REQUIRE : onTop()
		// ENSURE : visible()
		// _TAG06 Operations -- from RTRMBrowserDisplay

	virtual void erase();
		// REQUIRE: visible();
		// ENSURE: !visible()
        // _TAG06 Operations -- from RTRMBrowserDisplay

	virtual void internalMoveTo(int, int);
        // _TAG06 Operations -- from RTRMBrowserDisplay

// Operations -- from RTRMgmtAction
	virtual void processFilteredMgmtEvent(const RTRMgmtEvent& event);
		// _TAG07 Operations -- from RTRMgmtAction

// Static data
	static int defaultMaxEvents;
		// Static data

// Should be protected but CSet doesn't like the calls to constructors
// by descendant classes (says they're protected).
//protected: // Nested classes
	class LHCmd :
		public RTRSimpleKeyClient
	{
	public:
		LHCmd(RTRLogHistoryDisplay& d, int c)
			: RTRSimpleKeyClient(c), _display(d)
		{ }
	protected:
		RTRLogHistoryDisplay& _display;
	};

	class HomeCmd : 
		public LHCmd
	{
	public:
		HomeCmd(RTRLogHistoryDisplay& d, int c) : LHCmd(d, c) {}

		virtual void processKey();
	protected:
	};

	class UpCmd : 
		public LHCmd
	{
	public:
		UpCmd(RTRLogHistoryDisplay& d, int c) : LHCmd(d, c) {}

		virtual void processKey();
	protected:
	};

	class DownCmd : 
		public LHCmd
	{
	public:
		DownCmd(RTRLogHistoryDisplay& d, int c) : LHCmd(d, c) {}

		virtual void processKey();
	protected:
	};

	class NextPageCmd : 
		public LHCmd
	{
	public:
		NextPageCmd(RTRLogHistoryDisplay& d, int c) : LHCmd(d, c) {}

		virtual void processKey();
	protected:
	};

	class PreviousPageCmd : 
		public LHCmd
	{
	public:
		PreviousPageCmd(RTRLogHistoryDisplay& d, int c) : LHCmd(d, c) {}

		virtual void processKey();
	protected:
	};

	class SelectCmd : 
		public LHCmd
	{
	public:
		SelectCmd(RTRLogHistoryDisplay& d, int c) : LHCmd(d, c) {}

		virtual void processKey();
	protected:
	};

protected:
// Operations
	virtual void update();
		// REQUIRE: visible()

	void showDeleted(const RTRMgmtEvent *);

// Data
	int _maxEvents;
	int _skipCount;
	RTRString _title;
	RTRDLinkList<RTRLogEventRegion, RTRDLink0> _regionList;
	RTRLinkedList<RTRMgmtEvent> _eventList;
	HomeCmd _homeCmd;
	UpCmd _upCmd;
	DownCmd _downCmd;
	NextPageCmd _nextPageCmd;
	PreviousPageCmd _previousPageCmd;
	SelectCmd _selectCmd;
	RTRLogEventDisplay& _logEventDisplay;
	RTRLogEventRegion *_currentRegion;

private:
// Don't define
	RTRLogHistoryDisplay(const RTRLogHistoryDisplay&);
	RTRLogHistoryDisplay& operator=(const RTRLogHistoryDisplay&);
}; 

inline 
int RTRLogHistoryDisplay::maxEvents() const
{
	return _maxEvents;
}

inline 
int RTRLogHistoryDisplay::skipCount() const
{
	return _skipCount;
}

inline 
const RTRLogEventRegion *RTRLogHistoryDisplay::currentRegion() const
{
	return _currentRegion;
}

inline 
RTRLogEventRegion *RTRLogHistoryDisplay::first() const
{
	return _regionList.first();
}

inline 
RTRLogEventRegion *RTRLogHistoryDisplay::last() const
{
	return _regionList.last();
}

// Synopsis:
// #include"rtr/logedsp.h"
//
// Description:
// See Also:
//  RTRLogEventRegion, RTRLogHistoryDisplay, RTRLogEventDisplayFrame
//
// Inherits:
//  RTRMBrowserDisplay
//

class RTRLogEventDisplay :
	public RTRMBrowserDisplay
{
public:
// Constructor
	RTRLogEventDisplay(
			const RTRString&,	// name
			RTRDisplayFrame&,	// frame owning this display
			int			// height
			);
		// _TAG Constructor

// Destructor
	virtual ~RTRLogEventDisplay();
		// _TAG Destructor

// Attributes
	inline const RTRMgmtEvent* event() const;
		// _TAG01 Attributes 

// Operations
	void setEvent(const RTRMgmtEvent *);
		// _TAG02 Operations

	void update();
		// _TAG02 Operations

// Operations -- from RTRMBrowserDisplay
	virtual void draw();
		// REQUIRE : onTop()
		// ENSURE : visible()
		// _TAG03 Operations -- from RTRMBrowserDisplay

	virtual void erase();
		// REQUIRE: visible();
		// ENSURE: !visible()
		// _TAG03 Operations -- from RTRMBrowserDisplay

protected:
// Data
	RTRString _title;
	const RTRMgmtEvent *_event;
		// Data
};

inline 
const RTRMgmtEvent* RTRLogEventDisplay::event() const
{
	return _event;
}

// Synopsis:
// #include"rtr/logedsp.h"
//
// Description:
// See Also:
//  RTRLogEventRegion, RTRLogHistoryDisplay, RTRLogEventDisplay
//
// Inherits:
//  RTRDisplayFrame, RTRLoggerClient
//

class RTRLogEventDisplayFrame :
	public RTRDisplayFrame
{
public:
// Constructor
	RTRLogEventDisplayFrame(RTRMBrowserApplication&);
		// _TAG Constructor

// Destructor
	virtual ~RTRLogEventDisplayFrame();
		// _TAG Destructor

protected:
// Data
	RTRLogHistoryDisplay _historyDisplay;
	RTRLogEventDisplay _eventDisplay;
};

#endif
