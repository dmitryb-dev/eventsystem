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
#define publishData(EventName, varDef) \
    for (varDef = _evs_state##EventName = _evs_create##EventName(); \
         (_evs_state##EventName != &_evs_ok && _evs_state##EventName != &_evs_fail) || \
         (_evs_state##EventName == &_evs_ok && _evs_commit##EventName()); \
         _evs_state##EventName = _evs_state##EventName? &_evs_ok : &_evs_fail \
    ) if (_evs_state##EventName)

#define handleEvent(Name) _evs_handle##Name();

#endif
