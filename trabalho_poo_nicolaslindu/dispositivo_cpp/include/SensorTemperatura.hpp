#ifndef SENSORTEMPERATURA_HPP
#define SENSORTEMPERATURA_HPP
#include "Sensor.hpp"

//simular temperatura
class SensorTemperatura : public Sensor{
public: 
  SensorTemperatura();
  double ler() override;
};
#endif