#ifndef SYSTEM_DATA_STREAM_H
#define SYSTEM_DATA_STREAM_H

#include "read-write-buf.h"
#include "aliases.h"

/*
 * It describes an event. It is thread safe when you have one
 * reading and one writing thread. \
 * Example: main thread and interrupts. If you have
 * prioritized interrupts you should declare separate events
 * for every priority.
 */
#define DataStream(Name, type, bufSize) \
\
struct \
{ \
	ReadWriteBufManager _bufManager; \
	type _eventBuf[bufSize]; \
} _evs_##Name; \
\
/**	\
 * Allocates memory for new event. Returns pointer to allocated memory \
 * or EVENT_DENIED (0) if no place for new event in buffer.	\
 */	\
void* _evs_create##Name() \
{ \
	return bufMan_hasSpace(&_evs_##Name._bufManager) \
			? &_evs_##Name._eventBuf[_evs_##Name._bufManager.writePos] \
	        : EVENT_DENIED;	\
} \
\
/* \
 * After writing to allocated memory is finished you must call function	\
 * below. \
 */	\
int _evs_commit##Name() \
{ \
	bufMan_writeStep(&_evs_##Name._bufManager, bufSize); \
    return 0; \
} \
\
void _evs_on##Name(type *data); \
\
/**	\
 * If event buffer has new message, it takes that message and call \
 * onEvent##(..) for it \
 */	\
int _evs_handle##Name() \
{ \
	if (bufMan_hasNew(&_evs_##Name._bufManager)) \
	{ \
		_evs_on##Name(&_evs_##Name._eventBuf[_evs_##Name._bufManager.readPos]);	\
        bufMan_readStep(&_evs_##Name._bufManager, bufSize); \
		return 1; \
	} \
	return 0; \
} \
/* For dsl, see dsl.h, publishData */ \
void* _evs_state##Name; \
\
void _evs_on##Name(type *data)

#endif
