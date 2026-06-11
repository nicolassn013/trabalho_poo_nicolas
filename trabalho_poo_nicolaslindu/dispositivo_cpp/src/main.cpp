#include <iostream>
#include "SensorNivel.hpp"
#include "SensorPressao.hpp"
#include "SensorVazao.hpp"
#include "SensorTemperatura.hpp"

int main() {

//sensores da estacao
  SensorNivel nivel;
  SensorPressao pressao;
  SensorVazao vazao;
  SensorTemperatura temperatura;

  //mostra leituras
  std::cout << nivel.ler() << std::endl;
  std::cout << pressao.ler() << std::endl;
  std::cout << vazao.ler() << std::endl;
  std::cout << temperatura.ler() << std::endl;

  return 0;

}