#include "unity.h"
#include "component.h"
#include "dsl.h"
#include "utils.h"

int id;

Component(double, TestComp)
{
    return ++id;
}

void setUp()
{
	id = 0;
}
void tearDown()
{
    Reset(TestComp)
}

void test_get()
{
	TEST_ASSERT_EQUAL(1, Create(TestComp));
    TEST_ASSERT_EQUAL(2, Create(TestComp));
    
    TEST_ASSERT_EQUAL(3, *Get(TestComp));
    TEST_ASSERT_EQUAL(3, *Get(TestComp));
    
    TEST_ASSERT_EQUAL(4, Create(TestComp));
}

void test_set()
{
    TEST_ASSERT_EQUAL(1, *Get(TestComp));
    TEST_ASSERT_EQUAL(2, Set(TestComp, 2));
    TEST_ASSERT_EQUAL(2, *Get(TestComp));
}

