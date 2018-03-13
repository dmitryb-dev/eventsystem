#include "unity.h"
#include "event.h"
#include "dsl.h"
#include "utils.h"

int callsCounter;
void call()
{
	callsCounter++;
}

void setUp()
{
	callsCounter = 0;
}

Event(ETest1, 3)
{
	bindListener(call);
}
void test_nothing_to_read()
{
	handleEvent(ETest1);
	TEST_ASSERT_EQUAL(0, callsCounter);
}

Event(ETest2, 5)
{
	bindListener(call);
}
void test_written_3_read_3()
{
	repeat(3) publishEvent(ETest2);

	repeat(7) handleEvent(ETest2);
	TEST_ASSERT_EQUAL(3, callsCounter);
}

Event(ETest3, 5)
{
	bindListener(call);
}
void test_overflow()
{
	repeat(10) publishEvent(ETest3); // max 5, 5 lost

	repeat(2) handleEvent(ETest3); // 2 handled, 3 left in box
	TEST_ASSERT_EQUAL(2, callsCounter);

	repeat(10) publishEvent(ETest3); // 3 existed, 2 added, 8 lost;

	repeat(10) handleEvent(ETest3);
	TEST_ASSERT_EQUAL(7, callsCounter);
}
