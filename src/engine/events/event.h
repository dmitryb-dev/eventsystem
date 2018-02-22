#ifndef SYSTEM_EVENT_H
#define SYSTEM_EVENT_H

#include "read-write-buf.h"
#include "aliases.h"

#define Event(EventName, type, bufSize) \
/* \
 * It describes an event. It is thread safe when you have one \
 * reading and one writing thread. \
 * Example: main thread and interrupts. If you have	\
 * prioritized interrupts you should declare separate events \
 * for every priority. \
 */ \
struct \
{ \
	ReadWriteBufManager _bufManager; \
	type _eventBuf[bufSize]; \
} _evs_##EventName; \
\
/**	\
 * Allocates memory for new event. Returns pointer to allocated memory \
 * or EVENT_DENIED (0) if no place for new event in buffer.	\
 */	\
void* _evs_create##EventName() \
{ \
	return bufMan_hasSpace(&_evs_##EventName._bufManager) \
			? &_evs_##EventName._eventBuf[_evs_##EventName._bufManager.writePos] \
	        : EVENT_DENIED;	\
} \
\
/* \
 * After writing to allocated memory is finished you must call function	\
 * below. \
 */	\
int _evs_commit##EventName() \
{ \
	bufMan_writeStep(&_evs_##EventName._bufManager, bufSize); \
    return 0; \
} \
\
void _evs_on##EventName(type *event); \
\
/**	\
 * If event buffer has new message, it takes that message and call \
 * onEvent(..) for it \
 */	\
int _evs_handle##EventName() \
{ \
	if (bufMan_hasNew(&_evs_##EventName._bufManager)) \
	{ \
		_evs_on##EventName(&_evs_##EventName._eventBuf[_evs_##EventName._bufManager.readPos]);	\
        bufMan_readStep(&_evs_##EventName._bufManager, bufSize); \
		return 1; \
	} \
	return 0; \
} \
\
void _evs_on##EventName(type *event)

#endif
