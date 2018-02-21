#include "unity.h"
#include "empty-event.h"
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

EmptyEvent(ETest1, 3)
{
	bindEmpty(call);
}
void test_nothing_to_read()
{
	handleETest1();
	TEST_ASSERT_EQUAL(0, callsCounter);
}

EmptyEvent(ETest2, 5)
{
	bindEmpty(call);
}
void test_written_3_read_3()
{
	repeat(3) publishEmpty(ETest2);

	repeat(7) handleETest2();
	TEST_ASSERT_EQUAL(3, callsCounter);
}

EmptyEvent(ETest3, 5)
{
	bindEmpty(call);
}
void test_overflow()
{
	repeat(10) publishEmpty(ETest3); 		// max 5, 5 lost

	repeat(2) handleETest3();				// 2 handled, 3 left in box
	TEST_ASSERT_EQUAL(2, callsCounter);

	repeat(10) publishEmpty(ETest3);			// 3 existed, 2 added, 8 lost;

	repeat(10) handleETest3();
	TEST_ASSERT_EQUAL(7, callsCounter);
}
