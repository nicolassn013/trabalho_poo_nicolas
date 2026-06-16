#ifndef SENSORFACTORY_HPP
#define SENSORFACTORY_HPP
#include <string>
#include <memory>
#include "Sensor.hpp"

class SensorFactory {
public:
    static std::unique_ptr<Sensor> criar(const std::string& tipo);
};

#endif
