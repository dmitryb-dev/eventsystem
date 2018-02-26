#ifndef SYSTEM_ORDERED_EVENT_H
#define SYSTEM_ORDERED_EVENT_H

#include "ordered-base.h"

/*
 * See ordered-stream.h for details.
 */
#define OrderedEvent(Name, bufSize, group)  \
\
typedef struct _evs_EventWrapper##Name \
{ \
	 char id; \
} _evs_EventWrapper##Name; \
\
void _evs_on##Name(); \
OrderedBase(__Base##Name, char, bufSize, group, _evs_EventWrapper##Name) \
{ \
	_evs_on##Name(); \
} \
int _evs_publish##Name() \
{ \
	if (_evs_create__Base##Name()) \
	{ \
		_evs_commit__Base##Name(); \
		return 1; \
	} \
	return 0; \
} \
int _evs_handle##Name() \
{ \
	return _evs_handle__Base##Name(); \
} \
void _evs_on##Name()

#endif
