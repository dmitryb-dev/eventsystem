#include "unity.h"
#include "read-write-buf.h"
#include "utils.h"

ReadWriteBufManager manager;

void setUp(void)
{
	manager.readCount = 0;
	manager.readPos = 0;
	manager.writtenCount = 0;
	manager.writePos = 0;
}

void assertBufMan(char readCount, char writtenCount, char readPos, char writePos,
		ReadWriteBufManager *actual)
{
	TEST_ASSERT_EQUAL(readCount, actual->readCount);
	TEST_ASSERT_EQUAL(writtenCount, actual->writtenCount);
	TEST_ASSERT_EQUAL(readPos, actual->readPos);
	TEST_ASSERT_EQUAL(writePos, actual->writePos);
}

void test_write_until_right_boundary_reached()
{
	TEST_ASSERT_FALSE(bufMan_hasNew(&manager));

	forInts(0, 3, i)
	{
		TEST_ASSERT_TRUE(bufMan_hasSpace(&manager));
		assertBufMan(0, i, 0, i, &manager);
		bufMan_writeStep(&manager, 3);
		assertBufMan(0, i + 1, 0, i < 2? i + 1 : 0, &manager);
	}
	TEST_ASSERT_FALSE(bufMan_hasSpace(&manager));
}

void test_reading_all_written()
{
	repeat(2) bufMan_writeStep(&manager, 3);

	forInts(0, 2, i)
	{
		TEST_ASSERT_TRUE(bufMan_hasNew(&manager));
		assertBufMan(i, 2, i, 2, &manager);
		bufMan_readStep(&manager, 3);
		assertBufMan(i + 1, 2, i + 1, 2, &manager);
	}
	TEST_ASSERT_FALSE(bufMan_hasNew(&manager));
}

void test_write_pos_befor_read_pos()
{
	repeat(3) bufMan_writeStep(&manager, 3);
	repeat(2) bufMan_readStep(&manager, 3);

	assertBufMan(2, 3, 2, 0, &manager);

	forInts(0, 2, i)
	{
		TEST_ASSERT_TRUE(bufMan_hasSpace(&manager));
		assertBufMan(2, 3 + i, 2, i, &manager);
		bufMan_writeStep(&manager, 3);
		assertBufMan(2, 3 + i + 1, 2, i + 1, &manager);
	}
	TEST_ASSERT_FALSE(bufMan_hasSpace(&manager));

	bufMan_readStep(&manager, 3);

	TEST_ASSERT_TRUE(bufMan_hasSpace(&manager));

	repeat(2)
	{
		TEST_ASSERT_TRUE(bufMan_hasNew(&manager));
		bufMan_readStep(&manager, 3);
	}
	TEST_ASSERT_FALSE(bufMan_hasNew(&manager));
	assertBufMan(5, 5, 2, 2, &manager);
}
