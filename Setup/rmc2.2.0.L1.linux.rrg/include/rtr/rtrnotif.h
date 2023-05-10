//|---------------------------------------------------------------------------
//|                Copyright (C) 1994 Reuters,     							--
//|               1400 Kensington Road, Oak Brook, Il. 60521				--
//|        All rights reserved. Duplication or distribution prohibited      --
//|---------------------------------------------------------------------------
//
// By including this header, system components have access to the
// global event notifier, which provides facillities to access io and timing
// events. 
//
// E.g. 
//    notifier->addReadIOCmd(int fd = 1, RTRIOCmd& someCmd);
// or
//    notifier->addEvent(RTRCmd, 10L /* seconds */, 500L /* milliseconds */);
//
//
// The exact implementation of the notifier is decided at link time.
// Specifically, the static member function newNotifier() of 
// class RTREventNotifierInit must be provided by the application designer. 
// Typically, the RTREventNotifierInit::newNotifier() is defined in the
// source files which implements a particular type of notifier. The
// object file for that source code then provides everything needed for
// linking a notifier into an executable program. Please refer to the
// notifier documentation for more details.
//
// Author: A. MacGaffey
// Created: "Feb. 07 1994"
// Version: 1.0

#ifndef RTR_GLOBAL_EVENT_NOTIFIER
#define RTR_GLOBAL_EVENT_NOTIFIER

#include "rtr/evtnotif.h"
#include "rtr/ninit.h"

static RTREventNotifierInit eventNotifierInit;

#endif /* RTR_GLOBAL_EVENT_NOTIFIER */
