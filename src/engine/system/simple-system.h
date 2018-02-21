// The same name as in prioritized-system.h to avoid using of both systems
#ifndef SYSTEM_ENGINE_H
#define SYSTEM_ENGINE_H

#include "system.h"

#define registerEvent(EventName) handle##EventName()

#define EventSystem void systemStep()


#endif
