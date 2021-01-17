#include "Common_State.hpp"

static e_state state;

e_state* __getstate(void)
{
    return (&state);
}
