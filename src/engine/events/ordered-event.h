#ifndef SYSTEM_ORDERED_EVENT_H
#define SYSTEM_ORDERED_EVENT_H

#include "event.h"

typedef struct Group
{
	char nextWriteId;
	char nextReadId;
} Group;
Group defaultGroup;

#define OrderedEvent(EventName, type, bufSize, group)  \
/* \
 * See event.h for details \
 */ \
typedef struct EventName##Wrapper \
{ \
	 char id; \
	 type wrapped; \
} EventName##Wrapper; \
\
void on##EventName(type *event); \
Event(EventName##NonOrdered, EventName##Wrapper, bufSize) \
{ \
	 on##EventName(&event->wrapped); \
} \
\
void* create##EventName() \
{ \
	EventName##Wrapper* wrapper = create##EventName##NonOrdered(); \
	wrapper->id = group.nextWriteId++; \
	return &wrapper->wrapped; \
} \
\
void commit##EventName() \
{ \
	commit##EventName##NonOrdered(); \
} \
\
void on##EventName(type *event); \
void handle##EventName() \
{ \
	if (bufMan_hasNew(&EventName##NonOrdered._bufManager)) \
	{ \
		int index = EventName##NonOrdered._bufManager.readPos; \
		EventName##Wrapper* wrapper = &EventName##NonOrdered._eventBuf[index]; \
		if (group.nextReadId == wrapper->id) \
		{ \
			handle##EventName##NonOrdered(); \
			group.nextReadId++; \
		} \
	} \
} \
\
void on##EventName(type *event)

#endif
