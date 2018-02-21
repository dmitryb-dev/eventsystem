#ifndef SYSTEM_EMPTY_EVENT_H
#define SYSTEM_EMPTY_EVENT_H

#define EmptyEvent(EventName, bufSize) 										\
/*																			\
 * See event.h for more info													\
 */																			\
typedef struct EventName##Stream												\
{																			\
	unsigned char _read;														\
	unsigned char _written;													\
} EventName##Stream;															\
EventName##Stream EventName;													\
																			\
void publish##EventName()													\
{																			\
	if (EventName._written >= 100)											\
	{																		\
		EventName._written -= 100;											\
		EventName._read -= 100;												\
	}																		\
	if (EventName._written - EventName._read < bufSize)						\
	{																		\
		EventName._written++;												\
	}																		\
}																			\
																			\
void on##EventName();														\
void handle##EventName()														\
{																			\
	if (EventName._read < EventName._written)								\
	{																		\
		on##EventName();														\
		EventName._read++;													\
	}																		\
}																			\
																			\
void on##EventName()

#endif
