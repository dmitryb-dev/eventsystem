#ifndef EVENT_SYSTEM_DSL_H
#define EVENT_SYSTEM_DSL_H

#include "component.h"


#define bindListener(listener) listener()
#define bindListenerComp(componentName, handlerName) handlerName(Get(componentName))

#define publishEvent(EventType) if (_evs_publish##EventType()) {}


#define getStreamData() data
#define getStreamDataValue() *data


#define bindHandler(handler) handler(getStreamData())
#define bindHandlerComp(component, handler) handler(Get(component), getStreamData())

int _evs_ok;
int _evs_fail;
#define publishData(Event, varDef) \
    for (varDef = _evs_state##Event = _evs_create##Event(); \
         (_evs_state##Event != &_evs_ok && _evs_state##Event != &_evs_fail) ||  /* Not processed yet */ \
         (_evs_state##Event == &_evs_ok && _evs_commit##Event());               /* Commit after processing */ \
         _evs_state##Event = _evs_state##Event? &_evs_ok : &_evs_fail \
    ) if (_evs_state##Event)

#define handleEvent(Name) _evs_handle##Name();

#endif
