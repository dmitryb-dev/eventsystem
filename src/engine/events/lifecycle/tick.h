#ifndef SYSTEM_ON_TICK_EVENT_H
#define SYSTEM_ON_TICK_EVENT_H

#include "system.h"

/*
 * See event.h for more info.
 */ 
#define SystemTick \
\
char _evs_currentStepId; \
\
void _evs_onSystemTick(); \
int _evs_handleSystemTick() \
{ \
	if (_evs_currentStepId != _evs_systemStepId) \
    { \
        _evs_currentStepId = _evs_systemStepId; \
        _evs_onSystemTick(); \
    } \
    return 0; \
} \
\
void _evs_onSystemTick()

#endif
