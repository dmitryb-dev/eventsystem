#ifndef SYSTEM_EMPTY_ORDERED_EVENT_H
#define SYSTEM_EMPTY_ORDERED_EVENT_H

#include "ordered-event.h"

/*
 * See ordered-event.h for details.
 */
#define EmptyOrdered(EventName, bufSize, group)  \
\
void _evs_on##EventName(); \
OrderedEvent(NotEmpty##EventName, char, bufSize, group) \
{ \
	_evs_on##EventName(); \
} \
int _evs_publish##EventName() \
{ \
	if (_evs_createNotEmpty##EventName()) \
	{ \
		_evs_commitNotEmpty##EventName(); \
		return 1; \
	} \
	return 0; \
} \
int _evs_handle##EventName() \
{ \
	return _evs_handleNotEmpty##EventName(); \
} \
void _evs_on##EventName()

#endif
