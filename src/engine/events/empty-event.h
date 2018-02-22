#ifndef SYSTEM_EMPTY_EVENT_H
#define SYSTEM_EMPTY_EVENT_H

#include "read-write-buf.h"

/*
 * See event.h for more info.
 */ 
#define EmptyEvent(EventName, bufSize) \
\
ReadWriteBufManager _evs_##EventName; \
\
int _evs_publish##EventName() \
{ \
	if (bufMan_hasSpace(&_evs_##EventName)) \
	{ \
		bufMan_writeStep(&_evs_##EventName, bufSize); \
		return 1; \
	} \
	return 0; \
} \
\
void _evs_on##EventName(); \
int _evs_handle##EventName() \
{ \
	if (bufMan_hasNew(&_evs_##EventName)) \
	{ \
		_evs_on##EventName();	\
        bufMan_readStep(&_evs_##EventName, bufSize); \
		return 1; \
	} \
	return 0; \
} \
\
void _evs_on##EventName()

#endif
