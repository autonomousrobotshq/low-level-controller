#ifndef INTERFACE_INTERFACE_HPP
#define INTERFACE_INTERFACE_HPP

#include "Common_TimedUpdate.hpp"
#include <stdint.h>

class Interface : public TimedUpdate {
public:
    Interface(const uint16_t sampling_interval);
    ~Interface();

private:
};
#endif
