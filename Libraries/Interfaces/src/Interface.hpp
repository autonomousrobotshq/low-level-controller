#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <stdint.h>
#include "Timer.hpp"

class Interface : public Timer {
public:
    Interface(const unsigned long update_interval);
    virtual ~Interface();
	virtual bool Init();
	virtual bool Update();
private:
};
#endif
