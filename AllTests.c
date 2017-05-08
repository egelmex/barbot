#include <stdio.h>

#include "CuTest.h"

CuSuite* getBufferSuite();
CuSuite* getStateSuite();

void RunAllTests(void)
{
								CuString *output = CuStringNew();
								CuSuite* suite = CuSuiteNew();

								CuSuiteAddSuite(suite, getBufferSuite());
								CuSuiteAddSuite(suite, getStateSuite());

								CuSuiteRun(suite);
								CuSuiteSummary(suite, output);
								CuSuiteDetails(suite, output);
								printf("%s\n", output->buffer);
}

int main(void)
{
								RunAllTests();
}
