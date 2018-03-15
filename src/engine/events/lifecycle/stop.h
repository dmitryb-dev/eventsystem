#ifndef SYSTEM_ON_STOP_EVENT_H
#define SYSTEM_ON_STOP_EVENT_H

#include "system.h"

#ifndef SYSTEM_LIFECYCLE

    #define SystemStop \
    \
    int _evs_isSystemStoppedTriggered; \
    \
    int _evs_publishSystemStop() \
    { \
        _evs_isSystemStoppedTriggered = 1; \
        return 0; \
    } \
    void _evs_onSystemStop(); \
    int _evs_handleSystemStop() \
    { \
        if (_evs_isSystemStoppedTriggered) \
        { \
            _evs_isEventSystemStopped = 1; \
            _evs_isSystemStoppedTriggered = 0; \
            _evs_onSystemStop(); \
        } \
        return 0; \
    } \
    \
    void _evs_onSystemStop()

#else

    #define SystemStop \
    \
    int _evs_publishSystemStop() \
    { \
        _evs_isEventSystemStopped = 1; \
        return 0; \
    } \
    void _evs_onSystemStop(); \
    int _evs_handleSystemStop() \
    { \
        if (_evs_isEventSystemStopped) \
        { \
            _evs_isEventSystemStopped = 0; \
            _evs_onSystemStop(); \
        } \
        return 0; \
    } \
    \
    void _evs_onSystemStop()

#endif

#endif
