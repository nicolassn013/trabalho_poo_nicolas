#ifndef SENSORFACTORY_HPP
#define SENSORFACTORY_HPP
#include "Sensor.hpp"

//factory pra criar sensores da estacao
class SensorFactory {
public:
    static Sensor* criarSensor(const std::string& tipo)
};

#endif