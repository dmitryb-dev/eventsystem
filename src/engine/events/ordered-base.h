#ifndef SYSTEM_ORDERED_BASE_H
#define SYSTEM_ORDERED_BASE_H

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
 * See data-stream.h for details.
 */
#define OrderedBase(Name, type, bufSize, group, Wrapper)  \
\
void _evs_on##Name(Wrapper *data); \
DataStream(NonOrdered##Name, Wrapper, bufSize) \
{ \
    _evs_on##Name(data); \
} \
\
void* _evs_create##Name() \
{ \
	Wrapper* wrapper = _evs_createNonOrdered##Name(); \
    if (wrapper) \
    { \
        wrapper->id = group.nextWriteId++; \
        return wrapper; \
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
		Wrapper* wrapper = &_evs_NonOrdered##Name._eventBuf[index]; \
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
void _evs_on##Name(Wrapper *data)

#endif
