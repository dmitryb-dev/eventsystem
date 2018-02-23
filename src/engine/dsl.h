#ifndef EVENT_SYSTEM_DSL_H
#define EVENT_SYSTEM_DSL_H

#include "component.h"


#define bindListener(listener) listener()
#define bindListenerComp(componentName, handlerName) handlerName(Get(componentName))

#define publishEvent(EventType) if (_evs_publish##EventType()) {}


#define bindHandler(handler) handler(data)
#define bindHandlerComp(component, handler) handler(Get(component), data)

int _evs_ok;
int _evs_fail;
#define publishData(EventName, type, var) \
    for (type* var = _evs_create##EventName(); \
         (var != &_evs_ok && var != &_evs_fail) || \
         (var == &_evs_ok && _evs_commit##EventName()); \
         var = var? &_evs_ok : &_evs_fail \
    ) if (var)

#endif
