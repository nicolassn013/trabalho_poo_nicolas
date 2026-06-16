#ifndef SENSORVAZAO_HPP
#define SENSORVAZAO_HPP
#include "Sensor.hpp"

class SensorVazao : public Sensor {
public:
    SensorVazao();
    double ler() override;
};

#endif
