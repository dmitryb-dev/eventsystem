#ifndef RUN_SYSTEM_ENGINE_H
#define RUN_SYSTEM_ENGINE_H

int _evs_isEventSystemStopped;

void systemStep();

void runEventSystem()
{
	while(_evs_isEventSystemStopped)
	{
		systemStep();
	}
}

#endif
