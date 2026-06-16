#ifndef SENSORPRESSAO_HPP
#define SENSORPRESSAO_HPP
#include "Sensor.hpp"

class SensorPressao : public Sensor {
public:
    SensorPressao();
    double ler() override;
};

#endif
