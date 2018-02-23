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
	bindEvent(call);
}
void test_nothing_to_read()
{
	_evs_handleETest1();
	TEST_ASSERT_EQUAL(0, callsCounter);
}

Event(ETest2, 5)
{
	bindEvent(call);
}
void test_written_3_read_3()
{
	repeat(3) publishEvent(ETest2);

	repeat(7) _evs_handleETest2();
	TEST_ASSERT_EQUAL(3, callsCounter);
}

Event(ETest3, 5)
{
	bindEvent(call);
}
void test_overflow()
{
	repeat(10) publishEvent(ETest3); // max 5, 5 lost

	repeat(2) _evs_handleETest3(); // 2 _evs_handled, 3 left in box
	TEST_ASSERT_EQUAL(2, callsCounter);

	repeat(10) publishEvent(ETest3); // 3 existed, 2 added, 8 lost;

	repeat(10) _evs_handleETest3();
	TEST_ASSERT_EQUAL(7, callsCounter);
}
