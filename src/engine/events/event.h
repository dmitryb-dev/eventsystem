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
typedef struct EventName##Stream \
{ \
	ReadWriteBufManager _bufManager; \
	type _eventBuf[bufSize]; \
} EventName##Stream; \
EventName##Stream EventName; \
\
/**	\
 * Allocates memory for new event. Returns pointer to allocated memory \
 * or EVENT_DENIED (0) if no place for new event in buffer.	\
 */	\
void* create##EventName() \
{ \
	return bufMan_hasSpace(&EventName._bufManager) \
			? &EventName._eventBuf[EventName._bufManager.writePos] \
	        : EVENT_DENIED;	\
} \
\
/* \
 * After writing to allocated memory is finished you must call function	\
 * below. \
 */	\
void commit##EventName() \
{ \
	bufMan_writeStep(&EventName._bufManager, bufSize); \
} \
\
void on##EventName(type *event); \
\
/**	\
 * If event buffer has new message, it takes that message and call \
 * onEvent(..) for it \
 */	\
void handle##EventName() \
{ \
	if (bufMan_hasNew(&EventName._bufManager)) \
	{ \
		on##EventName(&EventName._eventBuf[EventName._bufManager.readPos]);	\
		bufMan_readStep(&EventName._bufManager, bufSize); \
	} \
} \
\
void on##EventName(type *event)

#endif
