#ifndef EVENT_SYSTEM_DSL_H
#define EVENT_SYSTEM_DSL_H

#include "component.h"

int _evs_ok;
int _evs_fail;

#define bindTo(functionName) functionName(event)
#define bindComponent(componentName, handlerName) handlerName(Get(componentName), event)

#define event(EventName, type, var) \
    for (type* var = create##EventName(); \
         (var != &_evs_ok && var != &_evs_fail) || \
         (var == &_evs_ok && commit##EventName()); \
         var = var? &_evs_ok : &_evs_fail \
    ) if (var)


#define bindEmpty(functionName) functionName()
#define bindEmptyToComponent(componentName, handlerName) handlerName(Get(componentName))

#define publishEmpty(EventType) if (publish##EventType()) {}


#endif
