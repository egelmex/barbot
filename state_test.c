
#include "CuTest.h"
#include "state.h"

/*-------------------------------------------------------------------------*
* CuString Test
*-------------------------------------------------------------------------*/



void t(CuTest* tc, struct state *state);

void StateTestSize(CuTest* tc) {
        struct state s = { 0 };
        struct state *state = &s;
        state_init(state);

        CuAssertIntEquals(tc, 0, stateSize);

        CuAssertTrue(tc, state_push(state, 1));
        CuAssertIntEquals(tc, 1, stateSize);

        CuAssertTrue(tc, state_push(state, 1));
        CuAssertIntEquals(tc, 2, stateSize);


        uint8_t x;
        CuAssertTrue(tc, statePop(&x));

        CuAssertIntEquals(tc, 1, stateSize);
        CuAssertTrue(tc, statePop(&x));

        CuAssertIntEquals(tc, 0, stateSize);
}


void StateTestInit(CuTest* tc)
{

        struct state s = { 0 };
        struct state *state = &s;

        CuAssertIntEquals(tc, 0, stateSize);
        statePush(1);

        CuAssertIntEquals(tc, 1, stateSize);
        statePush(2);

        CuAssertIntEquals(tc, 2, stateSize);
        uint8_t x;
        statePop(&x);
        CuAssertIntEquals(tc, 1, stateSize);

        CuAssertIntEquals(tc, 2, x);
        statePop(&x);

        CuAssertIntEquals(tc, 0, stateSize);
        CuAssertIntEquals( tc, 1, x);

}

CuSuite* getStateSuite(void)
{
        CuSuite* suite = CuSuiteNew();

        SUITE_ADD_TEST(suite, StateTestInit);
        SUITE_ADD_TEST(suite, StateTestSize);


        return suite;
}
