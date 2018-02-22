#include "unity.h"
#include "events-engine.h"
#include "prioritized-system.h"
#include <time.h>
#include <stdlib.h>

Component(int, ticksCounter) { return 0; }

void accessData(int* value);
void systemStep();
void stop(int* value);

SystemTick
{
	bindEventToComp(ticksCounter, stop);
}
SystemStop {}

EmptyEvent(E1, 3)
{
	bindEvent(systemStep);
}
EmptyOrdered(E2, 2, defaultGroup)
{
	bindEvent(systemStep);
}
Event(E3, int, 4)
{
	bindData(accessData);
	bindEvent(systemStep);
}
OrderedEvent(E4, int, 3, defaultGroup)
{
	bindData(accessData);
	bindEvent(systemStep);
}

EmptyEvent(E5, 1)
{
	bindEvent(systemStep);
}
EmptyOrdered(E6, 1, defaultGroup)
{
	bindEvent(systemStep);
}
Event(E7, int, 1)
{
	bindData(accessData);
	bindEvent(systemStep);
}
OrderedEvent(E8, int, 1, defaultGroup)
{
	bindData(accessData);
	bindEvent(systemStep);
}

void stop(int* value)
{
	if ((*value)++ == 100000)
	{
		publishEvent(SystemStop);
	}
}
void accessData(int* value)
{
	*value = rand();
}
void systemStep()
{
	switch(rand() % 8)
	{
	case 0: publishEvent(E1); break;
	case 1: publishEvent(E2); break;
	case 2: publishData(E3, int, data) *data = rand(); break;
	case 3: publishData(E4, int, data) *data = rand(); break;

	case 4: publishEvent(E5); break;
	case 5: publishEvent(E6); break;
	case 6: publishData(E7, int, data) *data = rand(); break;
	case 7: publishData(E8, int, data) *data = rand(); break;
	}
}

void setUp()
{
	int start = 0;
	int tick = 0;
	int stop = 0;
}

EventSystem
{
	HighestPriority
	{
		registerEvent(E1);
		registerEvent(E4);
	}
	MediumPriority
	{
		registerEvent(E2);
		registerEvent(E5);
		registerEvent(E7);
	}
	LowPriority
	{
		registerEvent(E3);
		registerEvent(E6);
		registerEvent(E8);
		registerEvent(SystemStop);
		registerEvent(SystemTick);
	}
}

void test_run_without_fails()
{
	srand(time(0));
	runEventSystem();
}
