#ifndef SYSTEM_EMPTY_EVENT_H
#define SYSTEM_EMPTY_EVENT_H

#include "read-write-buf.h"

/*
 * See event.h for more info.
 */ 
#define OnSystemStart \
\
int _evs_isSystemStarted; \
\
void_evs_onOnSystemStart(); \
int _evs_handle##OnSystemStart() \
{ \
	if (!_evs_isSystemStarted) \
    { \
        _evs_isSystemStarted++; \
        _evs_onOnSystemStart(); \
    } \
    return 0; \
} \
\
void _evs_onOnSystemStart()

#endif
