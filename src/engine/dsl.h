#ifndef EVENT_SYSTEM_DSL_H
#define EVENT_SYSTEM_DSL_H

#define bindTo(functionName) functionName(event)

#define event(EventType, varDef)							\
	{													\
		void (*_commitFunction)(void) = 0;				\
		void* __data = create##EventType();				\
		varDef = __data;									\
		if (__data)										\
		{												\
			_commitFunction = &commit##EventType;		\
		}												\
		if (__data)

#define publish if (_commitFunction) _commitFunction(); }


#define bindEmpty(functionName) functionName()

#define publishEmpty(EventType) publish##EventType()

#endif
