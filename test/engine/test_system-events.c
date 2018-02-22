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
	bindEventToComp(start, increment);
}
SystemTick
{
	bindEventToComp(tick, increment);
	bindEventToComp(tick, stopSystemOn3);
}
SystemStop
{
	bindEventToComp(stop, increment);
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
	int start = 0;
	int tick = 0;
	int stop = 0;
}

EventSystem {
	registerEvent(SystemStop);
	registerEvent(SystemStart);
	registerEvent(SystemTick);
}

void test_on_start()
{
	runEventSystem();

	TEST_ASSERT_EQUAL(1, *Get(start)); // triggered
	TEST_ASSERT_EQUAL(1, *Get(stop)); // triggered

	// 3 ticks before publishing stop and 1 extra,
	// because tick event registered after stop event
	TEST_ASSERT_EQUAL(4, *Get(tick));
}
