#ifndef COOLINGCONTROLLER_HPP
#define COOLINGCONTROLLER_HPP

class CoolingController {
public:
    CoolingController(const unsigned int pinCooling);
    ~CoolingController();
    void setState(bool state);
    bool getState();

private:
    bool _state;
    const unsigned int _pinCooling;
};

#endif
