#include "unity.h"
#include "start.h"
#include "stop.h"
#include "tick.h"
#include "simple-system.h"
#include "component.h"
#include "dsl.h"
#include "utils.h"

Component(int, start) { return 0; }
Component(int, tick) { return 0; }
Component(int, stop) { return 0; }

void increment(int* value);
void stopSystemOn3(int* value);

SystemStart
{
	bindListenerComp(start, increment);
}
SystemTick
{
	bindListenerComp(tick, increment);
	bindListenerComp(tick, stopSystemOn3);
}
SystemStop
{
	bindListenerComp(stop, increment);
}

void increment(int* value)
{
	(*value)++;
}
void stopSystemOn3(int* value)
{
	if (*value == 3) // stop system after 3 ticks;
	{
		publishEvent(SystemStop);
	}
}

void setUp()
{
	Set(start, 0);
	Set(tick, 0);
	Set(stop, 0);
}

EventSystem
{
	registerEvent(SystemStop);
	registerEvent(SystemStart);
	registerEvent(SystemTick);
}

void test_system_events()
{
	runEventSystem();

	TEST_ASSERT_EQUAL(1, *Get(start)); // triggered
	TEST_ASSERT_EQUAL(1, *Get(stop)); // triggered

	// 3 ticks before publishing stop and 1 extra,
	// because tick event registered after stop event
	TEST_ASSERT_EQUAL(4, *Get(tick));
}
