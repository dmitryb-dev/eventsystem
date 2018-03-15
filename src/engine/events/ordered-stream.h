#ifndef SYSTEM_ORDERED_STREAM_H
#define SYSTEM_ORDERED_STREAM_H

#include "aliases.h"
#include "ordered-base.h"

/*
 * See data-stream.h for details.
 */
#define OrderedDataStream(Name, type, bufSize, group) \
\
typedef struct _evs_DataWrapper##Name \
{ \
	 char id; \
	 type wrapped; \
} _evs_DataWrapper##Name; \
\
void _evs_on##Name(type *_evs_data); \
OrderedBase(__Base##Name, _evs_Wrapper##Name, bufSize, group, _evs_DataWrapper##Name) \
{ \
	 _evs_on##Name(&_evs_data->wrapped); \
} \
\
void* _evs_create##Name() \
{ \
	_evs_DataWrapper##Name* wrapper = _evs_create__Base##Name(); \
	return wrapper? &wrapper->wrapped : EVENT_DENIED; \
} \
\
int _evs_commit##Name() \
{ \
	return _evs_commit__Base##Name(); \
} \
\
int _evs_handle##Name() \
{ \
	return _evs_handle__Base##Name(); \
} \
\
void* _evs_state##Name; \
\
void _evs_on##Name(type *_evs_data)

#endif
