#ifndef SENSORPRESSAO_HPP
#define SENSORPRESSAO_HPP
#include "Sensor.hpp"

//simular pressao da tubolacao
class SensorPressao:public Sensor{

public SensorPressao();

double ler()override;
};
#endif