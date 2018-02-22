#include "unity.h"
#include "empty-ordered.h"
#include "dsl.h"
#include "utils.h"

int callCounter;
int lastCallId;
void call1()
{
	lastCallId = ++callCounter * 10 + 1;
}
void call2()
{
	lastCallId = ++callCounter * 10 + 2;
}

void setUp()
{
	lastCallId = callCounter = 0;
}

EmptyOrdered(OEvent1, 2, defaultGroup)
{
    bindEvent(call1);
}
EmptyOrdered(OEvent2, 2, defaultGroup)
{
    bindEvent(call2);
}

void test_ordering()
{
    // ev1 - 1
	publishEvent(OEvent1);

    // ev2 - 2
	publishEvent(OEvent2);

    // ev3 - 2
	publishEvent(OEvent2);

    // ev4 - 1
	publishEvent(OEvent1);

    // ev5 -2  - no more place
	publishEvent(OEvent2);


    // ev1 - 1
	_evs_handleOEvent2();
	TEST_ASSERT_EQUAL(0, lastCallId);
    _evs_handleOEvent1();
	TEST_ASSERT_EQUAL(11, lastCallId);

    // ev2 - 2
    _evs_handleOEvent1();
	TEST_ASSERT_EQUAL(11, lastCallId);
    _evs_handleOEvent2();
	TEST_ASSERT_EQUAL(22, lastCallId);

    // ev3 - 2
    _evs_handleOEvent2();
	TEST_ASSERT_EQUAL(32, lastCallId);

    // ev4 - 1
    _evs_handleOEvent2();
	TEST_ASSERT_EQUAL(32, lastCallId);
    _evs_handleOEvent1();
	TEST_ASSERT_EQUAL(41, lastCallId);

    // ev4 - 2 - no more place
    _evs_handleOEvent1();
    TEST_ASSERT_EQUAL(41, lastCallId);
    _evs_handleOEvent2();
	TEST_ASSERT_EQUAL(41, lastCallId);

    // ev6 - 2
	publishEvent(OEvent2);

     // ev7 - 1
	publishEvent(OEvent1);

    // ev6 - 2
    _evs_handleOEvent2();
	TEST_ASSERT_EQUAL(52, lastCallId);

    // ev7 - 1
    _evs_handleOEvent2();
	TEST_ASSERT_EQUAL(52, lastCallId);
    _evs_handleOEvent1();
    TEST_ASSERT_EQUAL(61, lastCallId);
}
