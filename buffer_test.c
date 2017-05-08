#include "buffer.h"
#include "CuTest.h"


/*-------------------------------------------------------------------------*
* CuString Test
*-------------------------------------------------------------------------*/

void TestInit(CuTest* tc)
{
								struct byteBuffer buffer;
								init(&buffer);
}

void Test(CuTest* tc)
{
								struct byteBuffer buffer;
								init(&buffer);
								push(&buffer, 1);
								uint8_t x;
								pop(&buffer, &x);
								CuAssertIntEquals(tc, 1, x);
}

void Test2(CuTest* tc)
{
								struct byteBuffer buffer;
								init(&buffer);
								push(&buffer, 1);
								push(&buffer, 2);
								uint8_t x;
								pop(&buffer, &x);
								CuAssertIntEquals(tc, 1, x);
								pop(&buffer, &x);
								CuAssertIntEquals(tc, 2, x);
}

void TestPushDirect(CuTest* tc)
{
								struct byteBuffer buffer;
								init(&buffer);
								push(&buffer, 1);
								push(&buffer, 2);
								uint8_t x;
								pop(&buffer, &x);
								CuAssertIntEquals(tc, 1, *buffer.head);
								pop(&buffer, &x);
								CuAssertIntEquals(tc, 2, *(buffer.head+1));
}


void TestEmpty(CuTest* tc)
{
								struct byteBuffer buffer;
								init(&buffer);
								isEmpty(&buffer);
								uint8_t _;
								CuAssertTrue(tc, !pop(&buffer,&_));
}

CuSuite* getBufferSuite(void)
{
								CuSuite* suite = CuSuiteNew();

								SUITE_ADD_TEST(suite, TestInit);

								SUITE_ADD_TEST(suite, Test);
								SUITE_ADD_TEST(suite, Test2);
								SUITE_ADD_TEST(suite, TestPushDirect);
								SUITE_ADD_TEST(suite, TestEmpty);

								return suite;
}
