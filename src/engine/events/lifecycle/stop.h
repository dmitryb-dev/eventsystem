#ifndef SYSTEM_ON_STOP_EVENT_H
#define SYSTEM_ON_STOP_EVENT_H

#include "system.h"

/*
 * See event.h for more info.
 */ 
#define SystemStop \
\
int _evs_isSystemStoppedTriggered; \
\
int _evs_publishSystemStop() \
{ \
	_evs_isSystemStoppedTriggered = 1; \
	return 0; \
} \
void _evs_onSystemStop(); \
int _evs_handleSystemStop() \
{ \
	if (_evs_isSystemStoppedTriggered) \
	{ \
		_evs_isEventSystemStopped = 1; \
		_evs_onSystemStop(); \
	} \
    return 0; \
} \
\
void _evs_onSystemStop()

#endif
