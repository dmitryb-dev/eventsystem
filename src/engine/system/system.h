#ifndef RUN_SYSTEM_ENGINE_H
#define RUN_SYSTEM_ENGINE_H

int _evs_isEventSystemStopped;
char _evs_currentStepId;

void systemStep();

void runEventSystem()
{
	while(_evs_isEventSystemStopped)
	{
        _evs_currentStepId++;
		systemStep();
	}
}

#endif
