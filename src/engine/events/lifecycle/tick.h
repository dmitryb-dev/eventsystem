#ifndef SYSTEM_ON_TICK_EVENT_H
#define SYSTEM_ON_TICK_EVENT_H

#include "system.h"

/*
 * See event.h for more info.
 */ 
#define SystemTick \
\
void _evs_onSystemTick(); \
int _evs_handleSystemTick() \
{ \
    _evs_onSystemTick(); \
    return 0; \
} \
\
void _evs_onSystemTick()

#define skipTicks(number) if (0 == _evs_systemStepId % number)

#endif
