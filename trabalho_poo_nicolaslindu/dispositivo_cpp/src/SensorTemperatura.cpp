#include "SensorTemperatura.hpp"
#include <cstdlib>

SensorTemperatura::SensorTemperatura()
    : Sensor("temperatura","C")
{
}

double SensorTemperatura::ler(){

//temp de 20 a 40C
  valor = 20 + (rad() % 21);

  return valor;
}