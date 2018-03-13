#ifndef SYSTEM_EVENT_H
#define SYSTEM_EVENT_H

#include "read-write-buf.h"

/*
 * See data-stream.h for more info.
 */ 
#define Event(Name, bufSize) \
\
ReadWriteBufManager _evs_##Name; \
\
int _evs_publish##Name() \
{ \
	if (bufMan_hasSpace(&_evs_##Name)) \
	{ \
		bufMan_writeStep(&_evs_##Name, bufSize); \
		return 1; \
	} \
	return 0; \
} \
\
void _evs_on##Name(); \
int _evs_handle##Name() \
{ \
	if (bufMan_hasNew(&_evs_##Name)) \
	{ \
		_evs_on##Name();	\
        bufMan_readStep(&_evs_##Name, bufSize); \
		return 1; \
	} \
	return 0; \
} \
\
void _evs_on##Name()

#endif
