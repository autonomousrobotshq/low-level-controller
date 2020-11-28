#ifndef ACTUATOR_RELAY_HPP
#define ACTUATOR_RELAY_HPP

class CoolingController {
public:
    CoolingController(const byte pinCooling);
    ~CoolingController();
    void setState(bool state);
    bool getState();

private:
    bool _state;
    const byte _pinCooling;
};

#endif
