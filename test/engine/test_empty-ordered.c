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
    bindEmpty(call1);
}
EmptyOrdered(OEvent2, 2, defaultGroup)
{
    bindEmpty(call2);
}

void test_ordering()
{
    // ev1 - 1
	publishEmpty(OEvent1);

    // ev2 - 2
	publishEmpty(OEvent2);

    // ev3 - 2
	publishEmpty(OEvent2);

    // ev4 - 1
	publishEmpty(OEvent1);

    // ev5 -2  - no more place
	publishEmpty(OEvent2);


    // ev1 - 1
	handleOEvent2();
	TEST_ASSERT_EQUAL(0, lastCallId);
    handleOEvent1();
	TEST_ASSERT_EQUAL(11, lastCallId);

    // ev2 - 2
    handleOEvent1();
	TEST_ASSERT_EQUAL(11, lastCallId);
    handleOEvent2();
	TEST_ASSERT_EQUAL(22, lastCallId);

    // ev3 - 2
    handleOEvent2();
	TEST_ASSERT_EQUAL(32, lastCallId);

    // ev4 - 1
    handleOEvent2();
	TEST_ASSERT_EQUAL(32, lastCallId);
    handleOEvent1();
	TEST_ASSERT_EQUAL(41, lastCallId);

    // ev4 - 2 - no more place
    handleOEvent1();
    TEST_ASSERT_EQUAL(41, lastCallId);
    handleOEvent2();
	TEST_ASSERT_EQUAL(41, lastCallId);

    // ev6 - 2
	publishEmpty(OEvent2);

     // ev7 - 1
	publishEmpty(OEvent1);

    // ev6 - 2
    handleOEvent2();
	TEST_ASSERT_EQUAL(52, lastCallId);

    // ev7 - 1
    handleOEvent2();
	TEST_ASSERT_EQUAL(52, lastCallId);
    handleOEvent1();
    TEST_ASSERT_EQUAL(61, lastCallId);
}
