#include "state.h"

bool
state_push(struct state *state, uint8_t data)
{
        if (state->data_count == MAX_DATA) {
                return false;
        }

        state->data[state->data_count] = data;
        state->data_count++;

        return true;
}

bool
state_pop(struct state *state, uint8_t *data) {
        if (state->data_count == 0) {
                return false;
        }

        *data = state->data[--state->data_count];
        return true;
}

size_t
state_size(struct state *state) {
        return state->data_count;
}
