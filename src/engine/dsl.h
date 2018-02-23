#ifndef EVENT_SYSTEM_DSL_H
#define EVENT_SYSTEM_DSL_H

#include "component.h"

int _evs_ok;
int _evs_fail;

#define bindData(handler) handler(data)
#define bindDataToComp(component, handler) handler(Get(component), data)

#define publishData(EventName, type, var) \
    for (type* var = _evs_create##EventName(); \
         (var != &_evs_ok && var != &_evs_fail) || \
         (var == &_evs_ok && _evs_commit##EventName()); \
         var = var? &_evs_ok : &_evs_fail \
    ) if (var)


#define bindEvent(listener) listener()
#define bindEventToComp(componentName, handlerName) handlerName(Get(componentName))

#define publishEvent(EventType) if (_evs_publish##EventType()) {}


#endif
