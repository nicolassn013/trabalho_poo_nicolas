#include "SensorPressao.hpp"
#include <cstdlib>

SensorPressao::SensorPressao()
  : Sensor("pressao","bar")
{
}
 
double SensorPressao::ler() {

 //valor bar entre 0 e 7.9
  valor = (rand() %80)/ 10.0;

  return valor;
}