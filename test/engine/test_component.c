#include "unity.h"
#include "component.h"
#include "dsl.h"
#include "utils.h"

int id;

void setUp()
{
	id = 0;
}

Component(double, TestComp)
{
    return ++id;
}

void test_ordering()
{
	TEST_ASSERT_EQUAL(1, Create(TestComp));
    TEST_ASSERT_EQUAL(2, Create(TestComp));
    
    TEST_ASSERT_EQUAL(3, *Get(TestComp));
    TEST_ASSERT_EQUAL(3, *Get(TestComp));
    
    TEST_ASSERT_EQUAL(4, Create(TestComp));
}
