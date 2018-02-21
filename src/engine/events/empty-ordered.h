#ifndef SYSTEM_EMPTY_ORDERED_EVENT_H
#define SYSTEM_EMPTY_ORDERED_EVENT_H

#include "ordered-event.h"

#define EmptyOrdered(EventName, bufSize, group)  \
/* \
 * See ordered-event.h for details \
 */ \
void on##EventName(); \
OrderedEvent(EventName##NotEmpty, char, bufSize, group) \
{ \
	on##EventName(); \
} \
int publish##EventName() \
{ \
	if (create##EventName##NotEmpty()) \
	{ \
		commit##EventName##NotEmpty(); \
		return 1; \
	} \
	return 0; \
} \
int handle##EventName() \
{ \
	return handle##EventName##NotEmpty(); \
} \
void on##EventName()

#endif
