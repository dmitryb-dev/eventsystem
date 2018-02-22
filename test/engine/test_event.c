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
	bindData(lastCallSetter);
}
void test_workflow()
{
	publishData(Test1, int, data)
	{
		*data = 4;
	}

	TEST_ASSERT_EQUAL(0, lastCallValue);

	_evs_handleTest1();
	TEST_ASSERT_EQUAL(4, lastCallValue);
}


Event(Test2, int, 2)
{
	bindData(lastCallSetter);
}
void test_write_until_end()
{
	publishData(Test2, int, data) *data = 4;

	publishData(Test2, int, data) *data = 7;

	// Lost
	publishData(Test2, int, data) *data = 11;
    
	_evs_handleTest2();
	TEST_ASSERT_EQUAL(4, lastCallValue);
    
	_evs_handleTest2();
	TEST_ASSERT_EQUAL(7, lastCallValue);

	_evs_handleTest2();
	TEST_ASSERT_EQUAL(7, lastCallValue);
}

Event(Test3, int, 2)
{
	bindData(lastCallSetter);
}
void test_write_on_free_again_space()
{
	publishData(Test3, int, data) *data = 3;

	_evs_handleTest3();
	TEST_ASSERT_EQUAL(3, lastCallValue);

	publishData(Test3, int, data) *data = 11;
	publishData(Test3, int, data) *data = 12;

	// Lost
	publishData(Test3, int, data) *data = 14;

	_evs_handleTest3();
	TEST_ASSERT_EQUAL(11, lastCallValue);

	_evs_handleTest3();
	TEST_ASSERT_EQUAL(12, lastCallValue);

	_evs_handleTest3();
	TEST_ASSERT_EQUAL(12, lastCallValue);

	publishData(Test3, int, data) *data = 15;

	_evs_handleTest3();
	TEST_ASSERT_EQUAL(15, lastCallValue);
}

Event(Test4, int, 2)
{
	bindData(lastCallSetter);
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

	_evs_handleTest4();

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
