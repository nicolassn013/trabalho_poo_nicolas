#include "SensorVazao.hpp"
#include <cstdlib>

SensorVazao::SensorVazao()
   : Sensor("vazao", "L/min")
{
}

double SensorVazao::ler(){

  //vazao em litros p/min e de 0 a 499
  valor = rand() % 500;

  return valor;
}