#include "unity.h"
#include "events-engine.h"
#include "prioritized-system.h"
#include <time.h>
#include <stdlib.h>

Component(int, ticksCounter) { return 0; }
Component(int, eventsCounter) { return 0; }
Component(int, lostEventsCounter) { return 0; }

void accessData(int* value);
void randomStep();
void stop(int* value);

SystemTick
{
	bindListenerComp(ticksCounter, stop);
}
SystemStart
{
    bindListener(randomStep);
}
SystemStop {}

Event(E1, 3)
{
	bindListener(randomStep);
}
Event(E2, 2)
{
	bindListener(randomStep);
}
DataStream(E3, int, 4)
{
	bindHandler(accessData);
	bindListener(randomStep);
}
DataStream(E4, int, 3)
{
	bindHandler(accessData);
	bindListener(randomStep);
}

Event(E5, 1)
{
	bindListener(randomStep);
}
Event(E6, 1)
{
	bindListener(randomStep);
}
DataStream(E7, int, 1)
{
	bindHandler(accessData);
	bindListener(randomStep);
}
DataStream(E8, int, 1)
{
	bindHandler(accessData);
	bindListener(randomStep);
}

void stop(int* value)
{
	if ((*value)++ == 10000)
	{
		publishEvent(SystemStop);
	}
}
void accessData(int* value)
{
	*value = rand();
}
void randomStep()
{
    int failOccurs = 0;
	switch(rand() % 8)
	{
	case 0: publishEvent(E1) else failOccurs++; break;
	case 1: publishEvent(E2) else failOccurs++; break;
	case 2: publishData(E3, int, data) *data = rand(); else failOccurs++; break;
	case 3: publishData(E4, int, data) *data = rand(); else failOccurs++; break;

	case 4: publishEvent(E5) else failOccurs++; break;
	case 5: publishEvent(E6) else failOccurs++; break;
	case 6: publishData(E7, int, data) *data = rand(); else failOccurs++; break;
	case 7: publishData(E8, int, data) *data = rand(); else failOccurs++; break;
	}
    if (failOccurs)
    {
        Value(lostEventsCounter)++;
        randomStep();
    }
    else
    {
        Value(eventsCounter)++;
    }
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
        
        registerEvent(SystemStart);
		registerEvent(SystemStop);
		registerEvent(SystemTick);
	}
}

void test_run_without_fails()
{
	srand(time(0));
	runEventSystem();
    printf("Ticks: %d, events: %d, lost events: %d\n", 
           Value(ticksCounter), 
           Value(eventsCounter),
           Value(lostEventsCounter)
    );
}
