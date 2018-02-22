#ifndef SYSTEM_ON_START_EVENT_H
#define SYSTEM_ON_START_EVENT_H

/*
 * See event.h for more info.
 */ 
#define SystemStart \
\
int _evs_isSystemStarted; \
\
void _evs_onSystemStart(); \
int _evs_handleSystemStart() \
{ \
	if (!_evs_isSystemStarted) \
    { \
        _evs_isSystemStarted++; \
        _evs_onSystemStart(); \
    } \
    return 0; \
} \
\
void _evs_onSystemStart()

#endif
