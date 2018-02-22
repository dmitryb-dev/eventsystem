#ifndef SYSTEM_ORDERED_EVENT_H
#define SYSTEM_ORDERED_EVENT_H

#include "aliases.h"
#include "event.h"

/*
 * Ordered events come in order within a group. Ordering of
 * events of differents group is not garanted.
 */
typedef struct Group
{
	char nextWriteId;
	char nextReadId;
} Group;
Group defaultGroup;

/*
 * See event.h for details.
 */
#define OrderedEvent(EventName, type, bufSize, group)  \
\
typedef struct _evs_Wrapper##EventName \
{ \
	 char id; \
	 type wrapped; \
} _evs_Wrapper##EventName; \
\
void on##EventName(type *event); \
Event(NonOrdered##EventName, _evs_Wrapper##EventName, bufSize) \
{ \
	 on##EventName(&event->wrapped); \
} \
\
void* _evs_create##EventName() \
{ \
	_evs_Wrapper##EventName* wrapper = _evs_createNonOrdered##EventName(); \
    if (wrapper) \
    { \
        wrapper->id = group.nextWriteId++; \
        return &wrapper->wrapped; \
    } \
	return EVENT_DENIED; \
} \
\
int _evs_commit##EventName() \
{ \
	return _evs_commitNonOrdered##EventName(); \
} \
\
int _evs_handle##EventName() \
{ \
	if (bufMan_hasNew(&_evs_NonOrdered##EventName._bufManager)) \
	{ \
		int index = _evs_NonOrdered##EventName._bufManager.readPos; \
		_evs_Wrapper##EventName* wrapper = &_evs_NonOrdered##EventName._eventBuf[index]; \
		if (group.nextReadId == wrapper->id) \
		{ \
			_evs_handleNonOrdered##EventName(); \
			group.nextReadId++; \
			return 1; \
		} \
	} \
	return 0; \
} \
\
void on##EventName(type *event)

#endif
