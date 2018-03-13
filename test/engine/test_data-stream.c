#include "unity.h"
#include "data-stream.h"
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

DataStream(Test1, int, 2)
{
	bindHandler(lastCallSetter);
}
void test_workflow()
{
	publishData(Test1, int, data)
	{
		*data = 4;
	}

	TEST_ASSERT_EQUAL(0, lastCallValue);

	handleEvent(Test1);
	TEST_ASSERT_EQUAL(4, lastCallValue);
}


DataStream(Test2, int, 2)
{
	bindHandler(lastCallSetter);
}
void test_write_until_end()
{
	publishData(Test2, int, data) *data = 4;

	publishData(Test2, int, data) *data = 7;

	// Lost
	publishData(Test2, int, data) *data = 11;
    
	handleEvent(Test2);
	TEST_ASSERT_EQUAL(4, lastCallValue);
    
	handleEvent(Test2);
	TEST_ASSERT_EQUAL(7, lastCallValue);

	handleEvent(Test2);
	TEST_ASSERT_EQUAL(7, lastCallValue);
}

DataStream(Test3, int, 2)
{
	bindHandler(lastCallSetter);
}
void test_write_on_free_again_space()
{
	publishData(Test3, int, data) *data = 3;

	handleEvent(Test3);
	TEST_ASSERT_EQUAL(3, lastCallValue);

	publishData(Test3, int, data) *data = 11;
	publishData(Test3, int, data) *data = 12;

	// Lost
	publishData(Test3, int, data) *data = 14;

	handleEvent(Test3);
	TEST_ASSERT_EQUAL(11, lastCallValue);

	handleEvent(Test3);
	TEST_ASSERT_EQUAL(12, lastCallValue);

	handleEvent(Test3);
	TEST_ASSERT_EQUAL(12, lastCallValue);

	publishData(Test3, int, data) *data = 15;

	handleEvent(Test3);
	TEST_ASSERT_EQUAL(15, lastCallValue);
}

DataStream(Test4, int, 2)
{
	bindHandler(lastCallSetter);
}
void test_on_fail()
{
	int isFail = 0;

	forInts(1, 3, i)
	{
		publishData(Test4, int, data)
		{
			*data = i;
		}
		else
		{
			isFail = i + 1;
		}
	}

	TEST_ASSERT_EQUAL(0, lastCallValue);
	TEST_ASSERT_EQUAL(0, isFail);

	publishData(Test4, int, data)
	{
		*data = 3;
	}
	else
	{
		isFail = 4;
	}

	TEST_ASSERT_EQUAL(0, lastCallValue);
	TEST_ASSERT_EQUAL(4, isFail);

	handleEvent(Test4);

	publishData(Test4, int, data)
	{
		*data = 4;
	}
	else
	{
		isFail = 5;
	}

	TEST_ASSERT_EQUAL(1, lastCallValue);
	TEST_ASSERT_EQUAL(4, isFail);
}
