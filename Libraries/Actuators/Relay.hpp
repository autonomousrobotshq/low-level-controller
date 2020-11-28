#ifndef ACTUATOR_RELAY_HPP
#define ACTUATOR_RELAY_HPP

class ActuatorRelay {
public:
    ActuatorRelay(const byte pinCooling);
    ~ActuatorRelay();
    void setState(const bool state);
    bool getState();

private:
    bool _state;
    const byte _pinCooling;
};

#endif
