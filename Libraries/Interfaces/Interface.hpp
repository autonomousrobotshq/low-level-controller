#ifndef INTERFACE_INTERFACE_HPP
#define INTERFACE_INTERFACE_HPP

#include <stdint.h>
#include "Common/TimedUpdate.hpp"

class Interface : public TimedUpdate {
public:
    Interface(const uint16_t sampling_interval);
    ~Interface();
private:
};
#endif
