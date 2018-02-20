#ifndef EVENT_SYSTEM_UTILS_H
#define EVENT_SYSTEM_UTILS_H

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

#endif
