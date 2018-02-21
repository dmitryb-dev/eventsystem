#ifndef EVENT_SYSTEM_DSL_H
#define EVENT_SYSTEM_DSL_H

#include "component.h"

#define bindTo(functionName) functionName(event)
#define bindComponent(componentName, handlerName) handlerName(Get(componentName), event)

#define event(EventType, varDef) \
	{ \
		void (*_commitFunction)(void) = 0; \
		void* __data = create##EventType(); \
		varDef = __data; \
		if (__data) \
		{ \
			_commitFunction = &commit##EventType; \
		} \
		if (__data)

#define publish if (_commitFunction) _commitFunction(); }
#define onFail if (!_commitFunction)


#define bindEmpty(functionName) functionName()
#define bindEmptyToComponent(componentName, handlerName) handlerName(Get(componentName))

#define publishEmpty(EventType) if (publish##EventType()) {}
#define orElse else


#endif
