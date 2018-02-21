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

OrderedEvent(OEvent1, int, 3, defaultGroup)
{

}

void test_ordering()
{
	handleOEvent1();
	TEST_ASSERT_EQUAL(0, lastCallId);
}
