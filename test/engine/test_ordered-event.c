#include "unity.h"
#include "ordered-event.h"
#include "dsl.h"
#include "utils.h"

int lastCallId;
void call(int* id)
{
	lastCallId = *id;
}

void setUp()
{
	lastCallId = 0;
}

OrderedEvent(OEvent1, int, 2, defaultGroup)
{
    bindTo(call);
}
OrderedEvent(OEvent2, int, 2, defaultGroup)
{
    bindTo(call);
}

void test_ordering()
{   
    // ev1 - 1
    event(OEvent1, int* data)
	{
		*data = 11;
	} publish;
    
    // ev2 - 2
    event(OEvent2, int* data)
	{
		*data = 22;
	} publish;
    
    // ev3 - 2
    event(OEvent2, int* data)
	{
		*data = 32;
	} publish;
    
    // ev4 - 1
    event(OEvent1, int* data)
	{
		*data = 41;
	} publish;
    
    // ev5 -2  - no more place
    event(OEvent2, int* data)
	{
		*data = 51;
	} publish;
    
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
    
    // ev6 -2
    event(OEvent2, int* data)
	{
		*data = 62;
	} publish;
    
     // ev7 - 1
    event(OEvent1, int* data)
	{
		*data = 71;
	} publish;
    
    // ev6 - 2
    handleOEvent2();
	TEST_ASSERT_EQUAL(62, lastCallId);
    
    // ev7 - 1
    handleOEvent2();
	TEST_ASSERT_EQUAL(62, lastCallId);
    handleOEvent1();
    TEST_ASSERT_EQUAL(71, lastCallId);
}
