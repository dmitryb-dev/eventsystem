#include "unity.h"
#include "event.h"
#include "dsl.h"
#include "utils.h"

int lastCallValue;
void lastCallSetter(int* value)
{
	lastCallValue = *value;
}

void setUp()
{
	lastCallValue = 0;
}

Event(Test1, int, 2)
{
	bindTo(lastCallSetter);
}
void test_workflow()
{
	event(Test1, int* data)
	{
		*data = 4;
	} publish;

	TEST_ASSERT_EQUAL(0, lastCallValue);

	handleTest1();
	TEST_ASSERT_EQUAL(4, lastCallValue);
}


Event(Test2, int, 2)
{
	bindTo(lastCallSetter);
}
void test_write_until_end()
{
	event(Test2, int* data)
	{
		*data = 4;
	} publish;

	event(Test2, int* data)
	{
		*data = 7;
	} publish;

	// Lost
	event(Test2, int* data)
	{
		*data = 11;
	} publish;

	handleTest2();
	TEST_ASSERT_EQUAL(4, lastCallValue);

	handleTest2();
	TEST_ASSERT_EQUAL(7, lastCallValue);

	handleTest2();
	TEST_ASSERT_EQUAL(7, lastCallValue);
}

Event(Test3, int, 2)
{
	bindTo(lastCallSetter);
}
void test_write_on_free_again_space()
{
	event(Test3, int* data)
	{
		*data = 3;
	} publish;

	handleTest3();
	TEST_ASSERT_EQUAL(3, lastCallValue);

	event(Test3, int* data)
	{
		*data = 11;
	} publish;

	event(Test3, int* data)
	{
		*data = 12;
	} publish;

	// Lost
	event(Test3, int* data)
	{
		*data = 14;
	} publish;

	handleTest3();
	TEST_ASSERT_EQUAL(11, lastCallValue);

	handleTest3();
	TEST_ASSERT_EQUAL(12, lastCallValue);

	handleTest3();
	TEST_ASSERT_EQUAL(12, lastCallValue);

	event(Test3, int* data)
	{
		*data = 15;
	} publish;

	handleTest3();
	TEST_ASSERT_EQUAL(15, lastCallValue);
}
