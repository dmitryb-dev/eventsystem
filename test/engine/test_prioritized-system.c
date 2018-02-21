#include "unity.h"
#include "empty-event.h"
#include "dsl.h"
#include "utils.h"

#include "prioritized-system.h"

int eventsCounter;
int orderOfEvents[10];

void happened(int id)
{
	orderOfEvents[eventsCounter++] = id;
}

EmptyEvent(HighEvent, 3)
{
	happened(1);
}
EmptyEvent(MediumEvent, 3)
{
	happened(2);
}
EmptyEvent(LowEvent, 3)
{
	happened(3);
}

HighestLevel
{
	registerEvent(HighEvent);
}
MediumLevel
{
	registerEvent(MediumEvent);
}
LowLevel
{
	registerEvent(LowEvent);
}

void test_array()
{
	repeat(3) publishEmpty(LowEvent);
	repeat(3) publishEmpty(MediumEvent)
	repeat(4) publishEmpty(HighEvent)


	systemStep();

	int expectedOrderOfEvents1[] = { 2, 1, 1, 1, 2, 2, 3, 0, 0, 0 };
	TEST_ASSERT_EQUAL_INT_ARRAY(expectedOrderOfEvents1, orderOfEvents, 10);


	systemStep();

	int expectedOrderOfEvents2[] = { 2, 1, 1, 1, 2, 2, 3, 3, 0, 0 };
	TEST_ASSERT_EQUAL_INT_ARRAY(expectedOrderOfEvents2, orderOfEvents, 10);


	publishEmpty(HighEvent)
	systemStep();

	int expectedOrderOfEvents3[] = { 2, 1, 1, 1, 2, 2, 3, 3, 1, 3 };
	TEST_ASSERT_EQUAL_INT_ARRAY(expectedOrderOfEvents3, orderOfEvents, 10);
}

