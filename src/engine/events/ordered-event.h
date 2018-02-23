#ifndef SYSTEM_ORDERED_EVENT_H
#define SYSTEM_ORDERED_EVENT_H

#include "ordered-stream.h"

/*
 * See ordered-stream.h for details.
 */
#define OrderedEvent(Name, bufSize, group)  \
\
void _evs_on##Name(); \
OrderedDataStream(Stream##Name, char, bufSize, group) \
{ \
	_evs_on##Name(); \
} \
int _evs_publish##Name() \
{ \
	if (_evs_createStream##Name()) \
	{ \
		_evs_commitStream##Name(); \
		return 1; \
	} \
	return 0; \
} \
int _evs_handle##Name() \
{ \
	return _evs_handleStream##Name(); \
} \
void _evs_on##Name()

#endif
