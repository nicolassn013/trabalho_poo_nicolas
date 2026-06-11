#ifndef SENSORVAZAO_HPP
#define SENSORVAZAO_HPP
#include "Sensor.hpp"

//simular vazao
class SensorVazao : public Sensor{
public: SensorVazao()

        double ler() override;
};
#endif