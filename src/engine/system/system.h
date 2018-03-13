#ifndef RUN_SYSTEM_ENGINE_H
#define RUN_SYSTEM_ENGINE_H

int _evs_isEventSystemStopped;
char _evs_systemStepId;

int _evs_handleSystemStart();
int _evs_handleSystemTick();
int _evs_handleSystemStop();

void _evs_systemStep();

void runEventSystem()
{
    #ifdef SYSTEM_LIFECYCLE
	   _evs_handleSystemStart();
    #endif
    
	while(!_evs_isEventSystemStopped)
	{
        #ifdef SYSTEM_LIFECYCLE
            _evs_handleSystemTick();
        #endif
        
		_evs_systemStepId++;
		_evs_systemStep();
        
        #ifdef SYSTEM_LIFECYCLE
	       _evs_handleSystemStop();
        #endif
	}
}

#endif
