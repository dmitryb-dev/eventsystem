#ifndef SYSTEM_ORDERED_STREAM_H
#define SYSTEM_ORDERED_STREAM_H

#include "aliases.h"
#include "data-stream.h"

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
#define OrderedDataStream(Name, type, bufSize, group)  \
\
typedef struct _evs_Wrapper##Name \
{ \
	 char id; \
	 type wrapped; \
} _evs_Wrapper##Name; \
\
void on##Name(type *event); \
DataStream(NonOrdered##Name, _evs_Wrapper##Name, bufSize) \
{ \
	 on##Name(&event->wrapped); \
} \
\
void* _evs_create##Name() \
{ \
	_evs_Wrapper##Name* wrapper = _evs_createNonOrdered##Name(); \
    if (wrapper) \
    { \
        wrapper->id = group.nextWriteId++; \
        return &wrapper->wrapped; \
    } \
	return EVENT_DENIED; \
} \
\
int _evs_commit##Name() \
{ \
	return _evs_commitNonOrdered##Name(); \
} \
\
int _evs_handle##Name() \
{ \
	if (bufMan_hasNew(&_evs_NonOrdered##Name._bufManager)) \
	{ \
		int index = _evs_NonOrdered##Name._bufManager.readPos; \
		_evs_Wrapper##Name* wrapper = &_evs_NonOrdered##Name._eventBuf[index]; \
		if (group.nextReadId == wrapper->id) \
		{ \
			_evs_handleNonOrdered##Name(); \
			group.nextReadId++; \
			return 1; \
		} \
	} \
	return 0; \
} \
\
void on##Name(type *event)

#endif
