#ifndef RUN_SYSTEM_ENGINE_H
#define RUN_SYSTEM_ENGINE_H

int isEventSystemStopped;

void systemStep();

void runEventSystem()
{
	while(isEventSystemStopped)
	{
		systemStep();
	}
}

#endif
