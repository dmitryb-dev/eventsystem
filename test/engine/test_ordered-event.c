#include "unity.h"
#include "ordered-stream.h"
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

OrderedDataStream(OEvent1, int, 2, defaultGroup)
{
    bindData(call);
}
OrderedDataStream(OEvent2, int, 2, defaultGroup)
{
    bindData(call);
}

void test_ordering()
{   
    // ev1 - 1
    publishData(OEvent1, int, data)
	{
		*data = 11;
	}
    
    // ev2 - 2
    publishData(OEvent2, int, data) *data = 22;
    
    // ev3 - 2
    publishData(OEvent2, int, data) *data = 32;
    
    // ev4 - 1
    publishData(OEvent1, int, data) *data = 41;
    
    // ev5 -2  - no more place
    publishData(OEvent2, int, data) *data = 51;
    
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
    
    // ev6 -2
    publishData(OEvent2, int, data) *data = 62;
    
     // ev7 - 1
    publishData(OEvent1, int, data) *data = 71;
    
    // ev6 - 2
    _evs_handleOEvent2();
	TEST_ASSERT_EQUAL(62, lastCallId);
    
    // ev7 - 1
    _evs_handleOEvent2();
	TEST_ASSERT_EQUAL(62, lastCallId);
    _evs_handleOEvent1();
    TEST_ASSERT_EQUAL(71, lastCallId);
}
