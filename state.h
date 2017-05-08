#ifndef __state_h
#define __state_h

#include "stddef.h"
#include "stdint.h"
#include <stdbool.h>

#define MAX_DATA 8

struct state;

typedef void state_fn (struct state *);

struct state
{
        state_fn * next;
        uint8_t data[MAX_DATA];
        size_t data_count;
};

bool state_push(struct state *state, uint8_t data);
bool state_pop(struct state *state, uint8_t *data);
size_t state_size(struct state *state);

#define setNextState(nextState) state->next = nextState
#define statePush(data) state_push(state, data)
#define statePop(s) state_pop(state, s)
#define stateSize state_size(state)

#endif
