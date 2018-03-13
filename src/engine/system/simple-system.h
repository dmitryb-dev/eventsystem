// The same name as in prioritized-system.h to avoid using of both systems
#ifndef SYSTEM_ENGINE_H
#define SYSTEM_ENGINE_H

#include "system.h"

#define registerEvent(EventName) _evs_handle##EventName()

#define HighPriority(eventRegistration) while(eventRegistration)

#define EventSystem void _evs_systemStep()


#endif
