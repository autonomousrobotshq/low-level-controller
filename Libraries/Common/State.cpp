#include "Common/State.hpp"

static e_state state;

e_state* __getstate(void)
{
    return (&state);
}
