#include "Common/Errno.hpp"

static e_errno errno;

e_errno* __geterrno(void)
{
    return (&errno);
}
